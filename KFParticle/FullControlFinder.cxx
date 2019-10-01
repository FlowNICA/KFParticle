#include "FullControlFinder.h"

#include "KFParticleSIMD.h"
#include "KFParticle.h"

void FullControlFinder::Init(const KFPTrackVector &tracks, const KFVertex &pv)
{
  tracks_ = tracks;
  prim_vx_ = pv;
}

void FullControlFinder::CancelCuts()
{
  float practInf = 1e9;
  cut_chi2_geo_ = practInf;
  cut_chi2_prim_neg_ = -practInf;
  cut_chi2_prim_pos_ = -practInf;
  cut_chi2_topo_ = practInf;
  cut_cosine_daughter_neg_ = -practInf;
  cut_cosine_daughter_pos_ = -practInf;
  cut_distance_ = practInf;
  cut_l_down_ = -practInf;
  cut_l_up_ =  practInf;
  cut_ldl_ = -practInf;
  cut_ldl_sec_ = -practInf;
  cut_sigma_mass_ratio_ = practInf;
  cut_is_from_pv_ = 799;
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
  // Scalar version
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
    isFromPV = 0;
  else
    isFromPV = -1;  
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

void FullControlFinder::SaveParticle()
{
  vec_mass_.push_back(mass_);
  vec_mass_err_.push_back(mass_err_);
  vec_chi2_prim_pos_.push_back(chi2_prim_pos_);
  vec_chi2_prim_neg_.push_back(chi2_prim_neg_);
  vec_distance_.push_back(distance_);
  vec_cosine_daughter_pos_.push_back(cosine_daughter_pos_);
  vec_cosine_daughter_neg_.push_back(cosine_daughter_neg_);
  vec_chi2_geo_.push_back(chi2_geo_);
  vec_l_.push_back(l_);
  vec_ldl_.push_back(ldl_);
  vec_is_from_pv_.push_back(is_from_pv_);
  vec_sigma_mass_ratio_.push_back(sigma_mass_ratio_);
  vec_chi2_topo_.push_back(chi2_topo_); 
}

void FullControlFinder::SetATConfiguration(AnalysisTree::TrackDetector* track_det, AnalysisTree::Configuration* conf)
{
  &lambdas_ = track_det;
  &config_ = conf;
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
      
      chi2_prim_pos_ = CalculateChiToPrimaryVertex(trackPos, pidPos);
      if(chi2_prim_pos_<=cut_chi2_prim_pos_) continue;      
      chi2_prim_neg_ = CalculateChiToPrimaryVertex(trackNeg, pidNeg);
      if(chi2_prim_neg_<=cut_chi2_prim_neg_) continue;
      
      std::array<float, 8> pars1;
      std::array<float, 8> pars2;
      CalculateParamsInPCA(trackPos, pidPos, trackNeg, pidNeg, pars1, pars2);
      
      distance_ = CalculateDistanceBetweenParticles(pars1, pars2);
      if(distance_ > cut_distance_) continue;
      
      cosine_daughter_pos_ = CalculateCosMomentumSum(pars1, pars2);
      cosine_daughter_neg_ = CalculateCosMomentumSum(pars2, pars1);
      if(cosine_daughter_pos_ < cut_cosine_daughter_pos_ || cosine_daughter_neg_ < cut_cosine_daughter_neg_) continue;
      
      KFParticleSIMD mother = ConstructMother(trackPos, pidPos, trackNeg, pidNeg);
      
      chi2_geo_ = CalculateChi2Geo(mother);
      if(!finite(chi2_geo_) || chi2_geo_ <= 0) continue;
      if(chi2_geo_ >= cut_chi2_geo_) continue;
      
      CalculateMotherProperties(mother, l_, ldl_, is_from_pv_);
      
      if(l_ >= cut_l_up_) continue;
      if(ldl_ <= cut_ldl_) continue;
      if(is_from_pv_ == cut_is_from_pv_) continue;
      if(l_ <= cut_l_down_) continue;
      
      auto* Lambda = lambdas_->AddChannel();
      Lambda->Init( config_->GetBranchConfig( lambdas_->GetId() ) );


      KFParticle particle;
      mother.GetKFParticle(particle, 0);
      particle.GetMass(mass_, mass_err_);
      
//--------- cuts unused at the current stage of reconstruction---------------      
//       sigma_mass_ratio_ = fabs(mass_ - mass_lambda) / sigma_lambda;
//       if(sigma_mass_ratio_ > cut_sigma_mass_ratio_) continue;
//      
//       chi2_topo_ = CalculateChi2Topo(mother);
//       if(chi2_topo_ > cut_chi2_topo_) continue;
//       if(ldl_ < cut_ldl_sec_) continue;
//---------------------------------------------------------------------------

      Lambda->SetMomentum( float(particle.GetPx()), float(particle.GetPy()), float(particle.GetPz()) );
      Lambda->SetField( float(particle.GetMass()), mass_field_id_);
      //Lambda->SetField( float(particle.GetRapidity()), rap_field_id_);
      Lambda->SetField( int(3122), pdg_field_id_w_);
      
      N++;
      
      
      
      SaveParticle();
    }
  }
  
//   std::cout << N << std::endl;
  
}