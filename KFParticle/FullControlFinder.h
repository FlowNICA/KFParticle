#include <vector>
#include "KFPTrackVector.h"
#include "KFVertex.h"

class FullControlFinder{
 public:
  FullControlFinder();
  virtual ~FullControlFinder() = default;
  
  void Init(const KFPTrackVector &tracks, const KFVertex &pv);
  void SortTracks();

  KFPTrackVector tracks_;
  KFVertex prim_vx_;
  std::vector<KFPTrackVector> sorted_tracks_{4};
  
  enum class eTrackTypes : int
  {
    kSecPos = 0,
    kSecNeg,
    kPrimPos,
    kPrimNeg,
    kNumberOfTrackTypes
  };
  
//  for(eTrackTypes i=eTrackTypes::kSecPos; i<eTrackTypes::kNumberOfTrackTypes; i++)

};