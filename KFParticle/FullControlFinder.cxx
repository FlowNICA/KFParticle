#include "FullControlFinder.h"

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

float FullControlFinder::GetChiToPrimaryVertex(const KFPTrack &track, const int pid)
{
  KFParticle tmpPart(track, pid);
  const float point[3] = {prim_vx_.X(), prim_vx_.Y(), prim_vx_.Z()};
  tmpPart.TransportToPoint(point);
  
  return tmpPart.GetDeviationFromVertex(prim_vx_);
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
    chi2_prim_ = GetChiToPrimaryVertex(trackPos, pidPos);
    if(chi2_prim_<=cut_chi2_prim_) continue;
    for(int iSecNeg=0; iSecNeg<nSecNegs; iSecNeg++)
    {
      KFPTrack trackNeg;
      tracks_.GetTrack(trackNeg, trIndex_[kSecNeg][iSecNeg]);
      const int pidNeg = tracks_.PDG()[trIndex_[kSecNeg][iSecNeg]];
      chi2_prim_ = GetChiToPrimaryVertex(trackNeg, pidNeg);
      if(chi2_prim_<=cut_chi2_prim_) continue;
      
      if(!(tracks_.PDG()[trIndex_[kSecPos][iSecPos]]==pdg_proton && tracks_.PDG()[trIndex_[kSecNeg][iSecNeg]]==pdg_pionMinus)) continue;

      N++;
    }
  }
  
  std::cout << N << std::endl;
}



























