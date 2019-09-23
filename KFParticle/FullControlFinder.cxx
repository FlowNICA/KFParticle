#include "FullControlFinder.h"

#include "KFPTrack.h"

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

void FullControlFinder::FindParticles()
{
  int nSecPoses = trIndex_[kSecPos].size();
  int nSecNegs  = trIndex_[kSecNeg].size();
  
  int N = 0;
  
  for(int iSecPos=0; iSecPos<nSecPoses; iSecPos++)
    for(int iSecNeg=0; iSecNeg<nSecNegs; iSecNeg++)
    {
      if(!(tracks_.PDG()[trIndex_[kSecPos][iSecPos]]==pdg_proton && tracks_.PDG()[trIndex_[kSecNeg][iSecNeg]]==pdg_pionMinus)) continue;
      N++;
    }
  std::cout << nSecPoses << "\t" << nSecNegs << "\t" << N << std::endl;
}