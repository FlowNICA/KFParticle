#include <vector>
#include "KFPTrackVector.h"
#include "KFVertex.h"

class FullControlFinder{
 public:
  FullControlFinder();
  virtual ~FullControlFinder() = default;
  
  void Init(const KFPTrackVector &tracks, const KFVertex &pv);

  KFPTrackVector tracks_;
  KFVertex prim_vx_;

};