#include "FullControlFinder.h"

#include "KFParticleSIMD.h"
#include "KFParticle.h"

#include "Output_interface.h"

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

/*float FullControlFinder::CalculateChiToPrimaryVertex(const KFPTrack &track, const int pid) const
{
  // Scalar version. Not optimal (was written earlier and was not imroved after SIMD'ization of package)
  KFParticle tmpPart(track, pid);
  const float point[3] = {prim_vx_.X(), prim_vx_.Y(), prim_vx_.Z()};
  tmpPart.TransportToPoint(point);
  
  return tmpPart.GetDeviationFromVertex(prim_vx_);
}*/

float FullControlFinder::CalculateChiToPrimaryVertex(const KFPTrack &track, const int pid) const
{
  // SIMD'ized version
  KFParticle tmpPart(track, pid);
  KFParticleSIMD tmpPartSIMD(tmpPart);
  
  KFVertex prim_vx_tmp = prim_vx_;
  const KFParticleSIMD prim_vx_Simd(prim_vx_tmp);  
  const float_v point[3] = {prim_vx_Simd.X(), prim_vx_Simd.Y(), prim_vx_Simd.Z()};
  
  tmpPartSIMD.TransportToPoint(point);
  float_v chi2vec = tmpPartSIMD.GetDeviationFromVertex(prim_vx_Simd);
  
//   std::cout << tmpPartSIMD.X()[0] << "\t" << tmpPartSIMD.Y()[0] << "\t" << tmpPartSIMD.Z()[0] << "\t\t" << chi2vec[0] << std::endl;  
  
  return chi2vec[0];
}

void FullControlFinder::CalculateParamsInPCA(const KFPTrack &track1, const int pid1, const KFPTrack &track2, const int pid2, std::array<float, 8> &pars1, std::array<float, 8> &pars2) const
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

float FullControlFinder::CalculateDistanceBetweenParticles(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2) const
{
  float dx = pars1.at(0) - pars2.at(0);
  float dy = pars1.at(1) - pars2.at(1);
  float dz = pars1.at(2) - pars2.at(2);
  float dr = sqrt(dx*dx+dy*dy+dz*dz);
  
  return dr;
}

float FullControlFinder::CalculateCosMomentumSum(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2) const
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
  particle1.SetId(track1.Id());
  particle2.SetId(track2.Id());
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

float FullControlFinder::CalculateChi2Geo(const KFParticleSIMD mother) const
{
 float_v chi2 = mother.Chi2()/simd_cast<float_v>(mother.NDF());
 
 return chi2[0];
}

void FullControlFinder::CalculateMotherProperties(const KFParticleSIMD mother, float &l, float &ldl, int &isFromPV) const
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
    isFromPV = 1;
  else
    isFromPV = 0;  
}

float FullControlFinder::CalculateCosTopo(const KFParticleSIMD mother) const
{
  float x_mother = mother.GetX()[0];
  float y_mother = mother.GetY()[0];
  float z_mother = mother.GetZ()[0];
  
  float px_mother = mother.GetPx()[0];
  float py_mother = mother.GetPy()[0];
  float pz_mother = mother.GetPz()[0];  
  
  float delta_x = x_mother - prim_vx_.GetX();
  float delta_y = y_mother - prim_vx_.GetY();
  float delta_z = z_mother - prim_vx_.GetZ();
  
  float sp = delta_x*px_mother + delta_y*py_mother + delta_z*pz_mother;
  float norm = sqrt(delta_x*delta_x + delta_y*delta_y + delta_z*delta_z) * sqrt(px_mother*px_mother + py_mother*py_mother + pz_mother*pz_mother);
  
  return sp/norm;  
}

float FullControlFinder::CalculateChi2Topo(const KFParticleSIMD mother) const
{
  KFParticleSIMD motherTopo = mother;
  KFVertex prim_vx_tmp = prim_vx_;
  const KFParticleSIMD prim_vx_Simd(prim_vx_tmp);
  motherTopo.SetProductionVertex(prim_vx_Simd);
  const float_v& chi2 = motherTopo.GetChi2()/simd_cast<float_v>(motherTopo.GetNDF());
  
  return chi2[0];
}

void FullControlFinder::SaveParticle(Output_interface Lambda)
{
  vec_mass_.push_back(mass_);
  vec_lambda_.push_back(Lambda);
}
 
void FullControlFinder::FindParticles()
{
  int nSecPoses = trIndex_[kSecPos].size();
  int nSecNegs  = trIndex_[kSecNeg].size();
  
  int N = 0;
    
  for(int iSecPos=0; iSecPos<nSecPoses; iSecPos++)
  {
    for(int iSecNeg=0; iSecNeg<nSecNegs; iSecNeg++)
    {    
      KFPTrack trackPos;
      tracks_.GetTrack(trackPos, trIndex_[kSecPos][iSecPos]);
      int pidPos = tracks_.PDG()[trIndex_[kSecPos][iSecPos]];
      if(pidPos == -1 || pidPos > 1000000000 || pidPos == 211)
        pidPos = pdg_proton;
      
      KFPTrack trackNeg;
      tracks_.GetTrack(trackNeg, trIndex_[kSecNeg][iSecNeg]);
      const int pidNeg = tracks_.PDG()[trIndex_[kSecNeg][iSecNeg]];
            
      if(!(pidPos==pdg_proton && pidNeg==pdg_pionMinus)) continue;
      
      Output_interface lambda;
            
      lambda.SetChi2PrimPos(CalculateChiToPrimaryVertex(trackPos, pidPos));
      if(lambda.GetChi2PrimPos() <= cuts_.GetCutChi2PrimPos()) continue;
      lambda.SetChi2PrimNeg(CalculateChiToPrimaryVertex(trackNeg, pidNeg));
      if(lambda.GetChi2PrimNeg() <= cuts_.GetCutChi2PrimNeg()) continue;
                  
      std::array<float, 8> pars1;
      std::array<float, 8> pars2;
      CalculateParamsInPCA(trackPos, pidPos, trackNeg, pidNeg, pars1, pars2);
      
      lambda.SetDistance(CalculateDistanceBetweenParticles(pars1, pars2));
      if(lambda.GetDistance() > cuts_.GetCutDistance()) continue;
      
      lambda.SetCosineDaughterPos(CalculateCosMomentumSum(pars1, pars2));
      lambda.SetCosineDaughterNeg(CalculateCosMomentumSum(pars2, pars1));
      if(lambda.GetCosineDaughterPos() < cuts_.GetCutCosineDaughterPos() || lambda.GetCosineDaughterNeg() < cuts_.GetCutCosineDaughterNeg()) continue;
            
      KFParticleSIMD mother = ConstructMother(trackPos, pidPos, trackNeg, pidNeg);
      
      lambda.SetChi2Geo(CalculateChi2Geo(mother));
      if(!finite(lambda.GetChi2Geo()) || lambda.GetChi2Geo() <= 0) continue;
      if(lambda.GetChi2Geo() >= cuts_.GetCutChi2Geo()) continue;
      
      float l, ldl;
      int isfrompv = -1;
      CalculateMotherProperties(mother, l, ldl, isfrompv);
      lambda.SetL(l);
      lambda.SetLdL(ldl);
      lambda.SetIsFromPV(isfrompv);
      
      lambda.SetCosineTopo(CalculateCosTopo(mother));
      
      if(lambda.GetL() >= cuts_.GetCutLUp()) continue;
      if(lambda.GetLdL() <= cuts_.GetCutLdL()) continue;
      //if(lambda.GetIsFromPV() == cuts_.GetCutIsFromPV()) continue;
      if(lambda.GetCosineTopo() <= cuts_.GetCutCosineTopo()) continue;
      if(lambda.GetL() <= cuts_.GetCutLDown()) continue;
      
      lambda.SetChi2Topo(CalculateChi2Topo(mother));
      if(lambda.GetChi2Topo() > cuts_.GetCutChi2Topo()) continue;
      
      KFParticle particle;
      mother.GetKFParticle(particle, 0);
//       std::cout << particle.DaughterIds()[0] << "\t" << particle.DaughterIds()[1] << "\n";
      
      float mass_err; // unused
      particle.GetMass(mass_, mass_err);
      
      particle.SetPDG(pdg_lambda);
      
      N++;
      lambda.SetParticle(particle);
      SaveParticle(lambda);
    }
  }
  
//   std::cout << N << std::endl;
  
}