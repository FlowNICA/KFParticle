#ifndef FullControlFinder_H
#define FullControlFinder_H

#include "KFPTrackVector.h"
#include "KFVertex.h"
#include "KFPTrack.h"
#include "FullControlConstants.h"

class FullControlFinder{
 public:
  FullControlFinder() = default;
  virtual ~FullControlFinder() = default;
  
  void  Init(const KFPTrackVector &tracks, const KFVertex &pv);
  void  SortTracks();
  float GetChiToPrimaryVertex(const KFPTrack &track, const int pid);
  void  GetParamsInPCA(const KFPTrack &track1, const int pid1, const KFPTrack &track2, const int pid2, std::array<float, 8> &pars1, std::array<float, 8> &pars2);
  float GetDistanceBetweenParticles(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2);
  float FindCosMomentumSum(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2);
  void  FindParticles();

 protected:

  KFPTrackVector tracks_;
  KFVertex prim_vx_;
  std::array<std::vector<int>, kNumberOfTrackTypes> trIndex_;
  
  float chi2_prim_pos_{-999.};
  float chi2_prim_neg_{-999.};
  float distance_{-999.};
  float chi2_geo_{-999.};
  float l_{-999.};
  float ldl_{-999.};
  float sigma_mass_ratio_{-999.};
  
  float cut_chi2_prim_pos_{3.};
  float cut_chi2_prim_neg_{3.};
  float cut_distance_{10.};
  float cut_chi2_geo_{3.};
  float cut_l_up_{200.}; float cut_l_down_{-5.};
  float cut_ldl_{5.}; float cut_ldl_sec_{10.};
  float cut_sigma_mass_ratio_{3.};
  
  }; 

#endif //FullControlFinder_H