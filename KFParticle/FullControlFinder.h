#ifndef FullControlFinder_H
#define FullControlFinder_H

#include "KFPTrackVector.h"
#include "KFVertex.h"
#include "KFPTrack.h"
#include "KFParticleSIMD.h"
#include "FullControlConstants.h"

class FullControlFinder{
  
 public:
   
  FullControlFinder() = default;
  virtual ~FullControlFinder() = default;
  
  void  Init(const KFPTrackVector &tracks, const KFVertex &pv);
  void  SetMotherInfo(std::vector<int> motherId, std::vector<int> motherPdg);
  void  CancelCuts();
  void  SortTracks();
  
  void  FindParticles();
  
  const KFPTrackVector* GetTracks() const {return &tracks_;};
  
 protected:
   
  float CalculateChiToPrimaryVertex(const KFPTrack &track, const int pid) const;
  void  CalculateParamsInPCA(const KFPTrack &track1, const int pid1, const KFPTrack &track2, const int pid2, std::array<float, 8> &pars1, std::array<float, 8> &pars2) const;
  float CalculateDistanceBetweenParticles(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2) const;
  float CalculateCosMomentumSum(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2) const;
  KFParticleSIMD ConstructMother(const KFPTrack &track1, const int pid1, const KFPTrack &track2, const int pid2) const;
  float CalculateChi2Geo(const KFParticleSIMD mother) const;
  void  CalculateMotherProperties(const KFParticleSIMD mother, float &l, float &ldl, int &isFromPV) const;
  float CalculateChi2Topo(const KFParticleSIMD mother) const;
  void  SaveParticle();
  
  KFPTrackVector tracks_;
  KFVertex prim_vx_;
  std::vector<int> mother_id_;
  std::vector<int> mother_pdg_;
  
  std::array<std::vector<int>, kNumberOfTrackTypes> trIndex_;
             
  float cut_chi2_prim_pos_{18.4207};
  float cut_chi2_prim_neg_{18.4207};
  float cut_distance_{1.};
  float cut_cosine_daughter_pos_{0.};
  float cut_cosine_daughter_neg_{0.};
  float cut_chi2_geo_{3.};
  float cut_l_up_{200.}; float cut_l_down_{-5.};
  int   cut_is_from_pv_{-1};
  float cut_ldl_{5.}; float cut_ldl_sec_{10.};
  float cut_sigma_mass_ratio_{3.};
  float cut_chi2_topo_{5.};
  
  }; 

#endif //FullControlFinder_H