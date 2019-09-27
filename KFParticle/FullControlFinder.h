#ifndef FullControlFinder_H
#define FullControlFinder_H

#include "KFPTrackVector.h"
#include "KFVertex.h"
#include "KFPTrack.h"
#include "KFParticleSIMD.h"
#include "FullControlConstants.h"

// #include "AnalysisTree/Detector.h"
// #include "AnalysisTree/Configuration.h"

class FullControlFinder{
 public:
  FullControlFinder() = default;
  virtual ~FullControlFinder() = default;
  
  void  Init(const KFPTrackVector &tracks, const KFVertex &pv);
  void  CancelCuts();
  void  SortTracks();
  float CalculateChiToPrimaryVertex(const KFPTrack &track, const int pid) const;
  void  CalculateParamsInPCA(const KFPTrack &track1, const int pid1, const KFPTrack &track2, const int pid2, std::array<float, 8> &pars1, std::array<float, 8> &pars2) const;
  float CalculateDistanceBetweenParticles(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2) const;
  float CalculateCosMomentumSum(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2) const;
  KFParticleSIMD ConstructMother(const KFPTrack &track1, const int pid1, const KFPTrack &track2, const int pid2) const;
  float CalculateChi2Geo(const KFParticleSIMD mother) const;
  void  CalculateMotherProperties(const KFParticleSIMD mother, float &l, float &ldl, int &isFromPV) const;
  float CalculateChi2Topo(const KFParticleSIMD mother) const;
  void  FindParticles();
  void  SaveParticle();
  
  const std::vector<float>& GetMass() const {return vec_mass_;}
  std::vector<float> GetMassErr() const {return vec_mass_err_;}
  std::vector<float> GetChi2PrimPos() const {return vec_chi2_prim_pos_;}
  std::vector<float> GetChi2PrimNeg() const {return vec_chi2_prim_neg_;}
  std::vector<float> GetDistance() const {return vec_distance_;}
  std::vector<float> GetCosineDaiughterPos() const {return vec_cosine_daughter_pos_;}
  std::vector<float> GetCosineDaiughterNeg() const {return vec_cosine_daughter_neg_;}
  std::vector<float> GetChi2Geo() const {return vec_chi2_geo_;}
  std::vector<float> GetL() const {return vec_l_;}
  std::vector<float> GetLdL() const {return vec_ldl_;}
  std::vector<int>   GetIsFromPV() const {return vec_is_from_pv_;}
  std::vector<float> GetSigmaMassRatio() const {return vec_sigma_mass_ratio_;}
  std::vector<float> GetChi2Topo() const {return vec_chi2_topo_;}
  

 protected:

  KFPTrackVector tracks_;
  KFVertex prim_vx_;
  std::array<std::vector<int>, kNumberOfTrackTypes> trIndex_;
  
  float mass_{-999.};
  float mass_err_{-999.};
  std::vector<float> vec_mass_;
  std::vector<float> vec_mass_err_;
  
//   AnalysisTree::TrackDetector* lambdas_{nullptr};
//   AnalysisTree::Configuration* config_{nullptr};
  
  float chi2_prim_pos_{-999.};
  float chi2_prim_neg_{-999.};
  float distance_{-999.};
  float cosine_daughter_pos_{-999.};
  float cosine_daughter_neg_{-999.};
  float chi2_geo_{-999.};
  float l_{-999.};
  float ldl_{-999.};
  int   is_from_pv_{-999};
  float sigma_mass_ratio_{-999.};
  float chi2_topo_{-999.};
  
  std::vector<float> vec_chi2_prim_pos_;
  std::vector<float> vec_chi2_prim_neg_;
  std::vector<float> vec_distance_;
  std::vector<float> vec_cosine_daughter_pos_;
  std::vector<float> vec_cosine_daughter_neg_;
  std::vector<float> vec_chi2_geo_;
  std::vector<float> vec_l_;
  std::vector<float> vec_ldl_;
  std::vector<int>   vec_is_from_pv_;
  std::vector<float> vec_sigma_mass_ratio_;
  std::vector<float> vec_chi2_topo_; 
  
  float cut_chi2_prim_pos_{3.};
  float cut_chi2_prim_neg_{3.};
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