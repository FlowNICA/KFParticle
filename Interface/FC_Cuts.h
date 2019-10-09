#ifndef FCCuts_H
#define FCCuts_H

class FC_Cuts
{
  
 public:
   
  FC_Cuts() = default;
  virtual ~FC_Cuts() = default;  
  
  //  lambda candidate parameters setters
  void SetCutChi2PrimPos(float value){cut_chi2_prim_pos_ = value;};
  void SetCutChi2PrimNeg(float value){cut_chi2_prim_neg_ = value;};
  void SetCutDistance(float value){cut_distance_ = value;};
  void SetCutCosineDaughterPos(float value){cut_cosine_daughter_pos_ = value;};
  void SetCutCosineDaughterNeg(float value){cut_cosine_daughter_neg_ = value;};
  void SetCutChi2Geo(float value){cut_chi2_geo_ = value;};
  void SetCutL(float value){cut_l_ = value;};
  void SetCutLdL(float value){cut_ldl_ = value;};
  void SetCutIsFromPV(int value){cut_is_from_pv_ = value;};
  void SetCutSigmaMassRatio(float value){cut_sigma_mass_ratio_ = value;};
  void SetCutChi2Topo(float value){cut_chi2_topo_ = value;};
  
  //  lambda candidate parameters getters
  const float GetCutChi2PrimPos() const {return cut_chi2_prim_pos_;};
  const float GetCutChi2PrimNeg() const {return cut_chi2_prim_neg_;};
  const float GetCutDistance() const {return cut_distance_;};
  const float GetCutCosDaughterPos() const {return cut_cosine_daughter_pos_;};
  const float GetCutCosDaughterNeg() const {return cut_cosine_daughter_neg_;};
  const float GetCutChi2Geo() const {return cut_chi2_geo_;};
  const float GetCutL() const {return cut_l_;};
  const float GetCutLdL() const {return cut_ldl_;};
  const int   GetCutIsFromPV() const {return cut_is_from_pv_;};
  const float GetCutSigmaMassRatio() const {return cut_sigma_mass_ratio_;};
  const float GetCutChi2Topo() const {return cut_chi2_topo_;};

 protected:
   
  // KFPFCuts cuts_;

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
#endif //FCCuts_H