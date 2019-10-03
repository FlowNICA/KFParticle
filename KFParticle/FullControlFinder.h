#ifndef FullControlFinder_H
#define FullControlFinder_H

#include "KFPTrackVector.h"
#include "KFVertex.h"
#include "KFPTrack.h"
#include "KFParticleSIMD.h"
#include "FullControlConstants.h"

#include "AnalysisTree/Track.h"
#include "AnalysisTree/Hit.h"
#include "AnalysisTree/Detector.h"
#include "AnalysisTree/Configuration.h"
#include "AnalysisTree/EventHeader.h"

class FullControlFinder{
 public:
   
  FullControlFinder() = default;
  virtual ~FullControlFinder() = default;
  
  void  Init(const KFPTrackVector &tracks, const KFVertex &pv);
  void  CancelCuts();
  void  SortTracks();
  void  SetATConfiguration(AnalysisTree::TrackDetector* track_det, AnalysisTree::Configuration* conf);
  
  void  FindParticles();
  
  std::vector<float> GetMass() const {return vec_mass_;};

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
  std::array<std::vector<int>, kNumberOfTrackTypes> trIndex_;
  
  float mass_{-999.};
  std::vector<float> vec_mass_;
  
  
  AnalysisTree::TrackDetector* lambdas_{nullptr};
  AnalysisTree::Configuration* config_{nullptr};
  
  // lambda candidate selection parameters (to be cut)
  int chi2_prim_pos_field_id_ {-1};
  int chi2_prim_neg_field_id_ {-1};
  int distance_field_id_ {-1};
  int cosine_daughter_pos_field_id_ {-1};
  int cosine_daughter_neg_field_id_ {-1};
  int chi2_geo_field_id_ {-1};
  int l_field_id_ {-1};
  int ldl_field_id_ {-1};
  int is_from_pv_field_id_ {-1};
  int sigma_mass_ratio_field_id_ {-1};
  int chi2_topo_field_id_ {-1};
  
  int mother_is_lambda_field_id_ {-1};
    
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
  
  // lamda selected parameters
  int mass_field_id_{-1};
  int rap_field_id_{-1};
  int pdg_field_id_w_{-1};
  
  }; 

#endif //FullControlFinder_H