#include "FullControlFinder.h"

#include "KFParticleSIMD.h"
#include "KFParticle.h"

void FullControlFinder::Init(const KFPTrackVector &tracks, const KFVertex &pv)
{
  tracks_ = tracks;
  prim_vx_ = pv;
}

void FullControlFinder::SortTracks()
{
  const int Size = tracks_.Size();
  
  for(int iTr = 0; iTr < Size; iTr++)
  {
    if(tracks_.PVIndex()[iTr] < 0)          // secondary
    {
      if(tracks_.Q()[iTr] > 0)              // secondary positive
        trIndex_[kSecPos].push_back(iTr);
      else                                  // secondary negative
        trIndex_[kSecNeg].push_back(iTr);
    }
    else                                    // primary
    {
      if(tracks_.Q()[iTr] > 0)              // secondary positive
        trIndex_[kPrimPos].push_back(iTr);
      else                                  // secondary negative
        trIndex_[kPrimNeg].push_back(iTr);
    }
  }
}

float FullControlFinder::GetChiToPrimaryVertex(const KFPTrack &track, const int pid) const
{
  KFParticle tmpPart(track, pid);
  const float point[3] = {prim_vx_.X(), prim_vx_.Y(), prim_vx_.Z()};
  tmpPart.TransportToPoint(point);
  
  return tmpPart.GetDeviationFromVertex(prim_vx_);
}

void FullControlFinder::GetParamsInPCA(const KFPTrack &track1, const int pid1, const KFPTrack &track2, const int pid2, std::array<float, 8> &pars1, std::array<float, 8> &pars2) const
{
  KFParticle particle1(track1, pid1);
  KFParticle particle2(track2, pid2);
  KFParticleSIMD particleSIMD1(particle1);    // the same particle is copied to each SIMD element
  KFParticleSIMD particleSIMD2(particle2);
  
  float_v dS[2];
  float_v params1[8], params2[8];
  particleSIMD1.GetDStoParticleFast(particleSIMD2, dS);
  particleSIMD1.TransportFast(dS[0], params1);
  particleSIMD2.TransportFast(dS[1], params2);
  
  float_v parbuf;
  for(int i=0; i<8; i++)
  {
    parbuf = params1[i];
    pars1.at(i) = parbuf[0];
    parbuf = params2[i];
    pars2.at(i) = parbuf[0];    
  }
}

float FullControlFinder::GetDistanceBetweenParticles(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2) const
{
  float dx = pars1.at(0) - pars2.at(0);
  float dy = pars1.at(1) - pars2.at(1);
  float dz = pars1.at(2) - pars2.at(2);
  float dr = sqrt(dx*dx+dy*dy+dz*dz);
  
  return dr;
}

float FullControlFinder::FindCosMomentumSum(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2) const
{
  // Find cosine bitween daughter1 and mother momenta
  const std::array<float, 3> P1 = {pars1.at(3), pars1.at(4), pars1.at(5)};
  const std::array<float, 3> P2 = {pars2.at(3), pars2.at(4), pars2.at(5)};
  const std::array<float, 3> PSum = {P1.at(0)+P2.at(0), P1.at(1)+P2.at(1), P1.at(2)+P2.at(2)};
  
  return (P1.at(0)*PSum.at(0) + P1.at(1)*PSum.at(1) + P1.at(2)*PSum.at(2)) /
         (sqrt(P1.at(0)*P1.at(0) + P1.at(1)*P1.at(1) + P1.at(2)*P1.at(2)) * sqrt(PSum.at(0)*PSum.at(0) + PSum.at(1)*PSum.at(1) + PSum.at(2)*PSum.at(2)));
}

KFParticleSIMD FullControlFinder::ConstructMother(const KFPTrack &track1, const int pid1, const KFPTrack &track2, const int pid2) const
{
  KFParticle particle1(track1, pid1);
  KFParticle particle2(track2, pid2);
  KFParticleSIMD particleSIMD1(particle1);    // the same particle is copied to each SIMD element
  KFParticleSIMD particleSIMD2(particle2);
  
  float_v ds[2] = {0.f,0.f};
  float_v dsdr[4][6];

  particleSIMD1.GetDStoParticle( particleSIMD2, ds, dsdr );
  particleSIMD1.TransportToDS(ds[0], dsdr[0]);
  particleSIMD2.TransportToDS(ds[1], dsdr[3]);
  const KFParticleSIMD* vDaughtersPointer[2] = {&particleSIMD1, &particleSIMD2};
  
  KFParticleSIMD mother;
  mother.Construct(vDaughtersPointer, 2, 0);
  
  return mother;
}

float FullControlFinder::FindChi2Geo(const KFParticleSIMD mother) const
{
 float_v chi2 = mother.Chi2()/simd_cast<float_v>(mother.NDF());
 
 return chi2[0];
}

void FullControlFinder::FindMotherProperties(const KFParticleSIMD mother, float &l, float &ldl, int &isFromPV) const
{
  float_v l_Simd;
  float_v dl_Simd;
  float_m isFromPV_Simd;
  KFVertex prim_vx_tmp = prim_vx_;
  const KFParticleSIMD prim_vx_Simd(prim_vx_tmp);

  mother.GetDistanceToVertexLine(prim_vx_Simd, l_Simd, dl_Simd, &isFromPV_Simd);
  
  l = l_Simd[0];
  ldl = l_Simd[0]/dl_Simd[0];
  if(isFromPV_Simd[0] == true)
    isFromPV = 0;
  else
    isFromPV = -1;  
}

float FullControlFinder::FindChi2Topo(const KFParticleSIMD mother) const
{
  KFParticleSIMD motherTopo = mother;
  KFVertex prim_vx_tmp = prim_vx_;
  const KFParticleSIMD prim_vx_Simd(prim_vx_tmp);
  motherTopo.SetProductionVertex(prim_vx_Simd);
  const float_v& chi2 = motherTopo.GetChi2()/simd_cast<float_v>(motherTopo.GetNDF());
  
  return chi2[0];
}

void FullControlFinder::FindParticles()
{
  int nSecPoses = trIndex_[kSecPos].size();
  int nSecNegs  = trIndex_[kSecNeg].size();
  
  int N = 0;
    
  for(int iSecPos=0; iSecPos<nSecPoses; iSecPos++)
  {
    KFPTrack trackPos;
    tracks_.GetTrack(trackPos, trIndex_[kSecPos][iSecPos]);
    const int pidPos = tracks_.PDG()[trIndex_[kSecPos][iSecPos]];
    chi2_prim_pos_ = GetChiToPrimaryVertex(trackPos, pidPos);
    if(chi2_prim_pos_<=cut_chi2_prim_pos_) continue;
    
    for(int iSecNeg=0; iSecNeg<nSecNegs; iSecNeg++)
    {
      KFPTrack trackNeg;
      tracks_.GetTrack(trackNeg, trIndex_[kSecNeg][iSecNeg]);
      const int pidNeg = tracks_.PDG()[trIndex_[kSecNeg][iSecNeg]];
      chi2_prim_neg_ = GetChiToPrimaryVertex(trackNeg, pidNeg);
      if(chi2_prim_neg_<=cut_chi2_prim_neg_) continue;
      
      if(!(tracks_.PDG()[trIndex_[kSecPos][iSecPos]]==pdg_proton && tracks_.PDG()[trIndex_[kSecNeg][iSecNeg]]==pdg_pionMinus)) continue;
      
      std::array<float, 8> pars1;
      std::array<float, 8> pars2;
      GetParamsInPCA(trackPos, pidPos, trackNeg, pidNeg, pars1, pars2);
      
      distance_ = GetDistanceBetweenParticles(pars1, pars2);
      if(distance_ > cut_distance_) continue;
      
      cosine_daughter_pos_ = FindCosMomentumSum(pars1, pars2);
      cosine_daughter_neg_ = FindCosMomentumSum(pars2, pars1);
      if(cosine_daughter_pos_ < cut_cosine_daughter_pos_ || cosine_daughter_neg_ < cut_cosine_daughter_neg_) continue;
      
      KFParticleSIMD mother = ConstructMother(trackPos, pidPos, trackNeg, pidNeg);
      
      chi2_geo_ = FindChi2Geo(mother);
      if(!finite(chi2_geo_) || chi2_geo_ <= 0) continue;
      if(chi2_geo_ > cut_chi2_geo_) continue;
      
      FindMotherProperties(mother, l_, ldl_, is_from_pv_);
      
      if(l_ > cut_l_up_) continue;
      if(ldl_ < cut_ldl_) continue;
      if(is_from_pv_ == -1) continue;
      if(l_ < cut_l_down_) continue;
      
      KFParticle particle;
      mother.GetKFParticle(particle, 0);
      particle.GetMass(mass_, mass_err_);
      sigma_mass_ratio_ = fabs(mass_ - mass_lambda) / sigma_lambda;
      //if(sigma_mass_ratio_ > cut_sigma_mass_ratio_) continue;
      
      chi2_topo_ = FindChi2Topo(mother);
      if(chi2_topo_ > cut_chi2_topo_) continue;
      //if(ldl_ < cut_ldl_sec_) continue;
      

      N++;
    }
  }
  
  std::cout << N << std::endl;
}