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
  
  const std::vector<float>& GetMass() const {return vec_mass_;};
  const std::vector<float>& GetPx() const {return vec_px_;};
  const std::vector<float>& GetPy() const {return vec_py_;};
  const std::vector<float>& GetPz() const {return vec_pz_;};
  const std::vector<float>& GetRapidity() const {return vec_rap_;};
  const std::vector<int>  & GetIsSignal() const {return vec_is_signal_;};
  const std::vector<float>& GetChi2PrimPos() const {return vec_chi2_prim_pos_;};
  const std::vector<float>& GetChi2PrimNeg() const {return vec_chi2_prim_neg_;};
  const std::vector<float>& GetDistance() const {return vec_distance_;};
  const std::vector<float>& GetCosDaughterPos() const {return vec_cosine_daughter_pos_;};
  const std::vector<float>& GetCosDaughterNeg() const {return vec_cosine_daughter_neg_;};
  const std::vector<float>& GetChi2Geo() const {return vec_chi2_geo_;};
  const std::vector<float>& GetL() const {return vec_l_;};
  const std::vector<float>& GetLdL() const {return vec_ldl_;};
  const std::vector<int>  & GetIsFromPV() const {return vec_is_from_pv_;};
  const std::vector<float>& GetSigmaMassRatio() const {return vec_sigma_mass_ratio_;};
  const std::vector<float>& GetChi2Topo() const {return vec_chi2_topo_;};
  
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
  
  float mass_ {-999.};
  float px_ {-999.};
  float py_ {-999.};
  float pz_ {-999.};
  float rap_ {-999.};
  int   is_signal_ {-1};
  
  std::vector<float> vec_mass_;
  std::vector<float> vec_px_;
  std::vector<float> vec_py_;
  std::vector<float> vec_pz_;
  std::vector<float> vec_rap_; 
  std::vector<int>   vec_is_signal_;
    
  // lambda candidate selection parameters (to be cut)
  float chi2_prim_pos_ {-1.};
  float chi2_prim_neg_ {-1.};
  float distance_ {-1.};
  float cosine_daughter_pos_ {-1.};
  float cosine_daughter_neg_ {-1.};
  float chi2_geo_ {-1.};
  float l_ {-1.};
  float ldl_ {-1.};
  int   is_from_pv_ {-1};
  float sigma_mass_ratio_ {-1.};
  float chi2_topo_ {-1.};
  
  // vectors with lamda selection parameters (to be written)
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