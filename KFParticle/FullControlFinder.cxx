#include "FullControlFinder.h"

#include "KFParticle.h"
#include "KFParticleSIMD.h"

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

float FullControlFinder::GetChiToPrimaryVertex(const KFPTrack &track, const int pid)
{
  KFParticle tmpPart(track, pid);
  const float point[3] = {prim_vx_.X(), prim_vx_.Y(), prim_vx_.Z()};
  tmpPart.TransportToPoint(point);
  
  return tmpPart.GetDeviationFromVertex(prim_vx_);
}

void FullControlFinder::GetParamsInPCA(const KFPTrack &track1, const int pid1, const KFPTrack &track2, const int pid2, std::array<float, 8> &pars1, std::array<float, 8> &pars2)
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
    pars1[i] = parbuf[0];
    parbuf = params2[i];
    pars2[i] = parbuf[0];    
  }
}

float FullControlFinder::GetDistanceBetweenParticles(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2)
{
  float dx = pars1[0] - pars2[0];
  float dy = pars1[1] - pars2[1];
  float dz = pars1[2] - pars2[2];
  float dr = sqrt(dx*dx+dy*dy+dz*dz);
  
  return dr;
}

float FullControlFinder::FindCosMomentumSum(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2)
{
  // Find cosine bitween daughter1 and mother momenta
  const std::array<float, 3> P1 = {pars1[3], pars1[4], pars1[5]};
  const std::array<float, 3> P2 = {pars2[3], pars2[4], pars2[5]};
  const std::array<float, 3> PSum = {P1[0]+P2[0], P1[1]+P2[1], P1[2]+P2[2]};
  
  return (P1[0]*PSum[0] + P1[1]*PSum[1] + P1[2]*PSum[2]) /
         (sqrt(P1[0]*P1[0] + P1[1]*P1[1] + P1[2]*P1[2]) * sqrt(PSum[0]*PSum[0] + PSum[1]*PSum[1] + PSum[2]*PSum[2]));
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
      //if(distance_ > cut_distance_) continue;
      
      cosine_daughter_pos_ = FindCosMomentumSum(pars1, pars2);
      cosine_daughter_neg_ = FindCosMomentumSum(pars2, pars1);

      N++;
    }
  }
  
  std::cout << N << std::endl;
}