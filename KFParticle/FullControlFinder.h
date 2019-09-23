#ifndef FullControlFinder_H
#define FullControlFinder_H

#include "KFPTrackVector.h"
#include "KFVertex.h"
#include "FullControlConstants.h"

class FullControlFinder{
 public:
  FullControlFinder() = default;
  virtual ~FullControlFinder() = default;
  
  void Init(const KFPTrackVector &tracks, const KFVertex &pv);
  void SortTracks();
  void FindParticles();

 protected:

  KFPTrackVector tracks_;
  KFVertex prim_vx_;
  
  std::array<std::vector<int>, kNumberOfTrackTypes> trIndex_;
  
  };

#endif //FullControlFinder_H