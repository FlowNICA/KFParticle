#include "FullControlFinder.h"

void FullControlFinder::Init(const KFPTrackVector &tracks, const KFVertex &pv)
{
  tracks_ = tracks;
  prim_vx_ = pv;
}

void FullControlFinder::SortTracks()
{
  const int Size = tracks_.Size();
  std::vector<int> trIndex[4];
  
  for(int iTr = 0; iTr < Size; iTr++)
  {
    if(tracks_.PVIndex()[iTr] < 0)          // secondary
    {
      if(tracks_.Q()[iTr] > 0)              // secondary positive
        trIndex[secPos].push_back(iTr);
      else
        trIndex[secNeg].push_back(iTr);     // secondary negative
    }
    else                                    // primary
    {
      if(tracks_.Q()[iTr] > 0)              // primary positive
        trIndex[primPos].push_back(iTr);
      else                                  // primary negative
        trIndex[primNeg].push_back(iTr);
    }
  }
     
  for(int iTrType=0; iTrType<4; iTrType++)
    sorted_tracks_[iTrType].SetTracks(&tracks_, trIndex[iTrType], trIndex[iTrType].size());
  
  
}