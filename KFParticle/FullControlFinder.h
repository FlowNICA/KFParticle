#ifndef FullControlFinder_H
#define FullControlFinder_H

#include <vector>

#include "KFPTrackVector.h"
#include "KFVertex.h"

class FullControlFinder{
 public:
  FullControlFinder() = default;
  virtual ~FullControlFinder() = default;
  
  void Init(const KFPTrackVector &tracks, const KFVertex &pv);
  void SortTracks();

  enum class eTrackTypes : int
  {
    kSecPos = 0,
    kSecNeg,
    kPrimPos,
    kPrimNeg,
    kNumberOfTrackTypes
  };

 protected:

  KFPTrackVector tracks_;
  KFVertex prim_vx_;
  std::array<KFPTrackVector, 4> sorted_tracks_;
  
  
//  for(eTrackTypes i=eTrackTypes::kSecPos; i<eTrackTypes::kNumberOfTrackTypes; i++)

};

#endif //FullControlFinder_H