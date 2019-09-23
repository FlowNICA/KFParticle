#include "FullControlFinder.h"

FullControlFinder::FullControlFinder() {}

void FullControlFinder::Init(const KFPTrackVector &tracks, const KFVertex &pv)
{
  tracks_ = tracks;
  prim_vx_ = pv;
}