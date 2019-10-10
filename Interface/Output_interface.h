#ifndef Output_interface_H
#define Output_interface_H

#include "KFParticle.h"

class Output_interface
{
  
 public:
  
  Output_interface() = default;
  virtual ~Output_interface() = default;  
  
  //  lambda candidate parameters setters
  void SetChi2PrimPos(float value) {chi2_prim_pos_ = value;};
  void SetChi2PrimNeg(float value) {chi2_prim_neg_ = value;};
  void SetDistance(float value) {distance_ = value;};
  void SetCosineDaughterPos(float value) {cosine_daughter_pos_ = value;};
  void SetCosineDaughterNeg(float value) {cosine_daughter_neg_ = value;};
  void SetChi2Geo(float value) {chi2_geo_ = value;};
  void SetL(float value) {l_ = value;};
  void SetLdL(float value) {ldl_ = value;};
  void SetIsFromPV(int value) {is_from_pv_ = value;};
  void SetSigmaMassRatio(float value) {sigma_mass_ratio_ = value;};
  void SetChi2Topo(float value) {chi2_topo_ = value;};
  
  void SetParticle(KFParticle particle) {particle_ = particle;};
  
  //  lambda candidate parameters getters
  const float GetChi2PrimPos() const {return chi2_prim_pos_;};
  const float GetChi2PrimNeg() const {return chi2_prim_neg_;};
  const float GetDistance() const {return distance_;};
  const float GetCosineDaughterPos() const {return cosine_daughter_pos_;};
  const float GetCosineDaughterNeg() const {return cosine_daughter_neg_;};
  const float GetChi2Geo() const {return chi2_geo_;};
  const float GetL() const {return l_;};
  const float GetLdL() const {return ldl_;};
  const int   GetIsFromPV() const {return is_from_pv_;};
  const float GetSigmaMassRatio() const {return sigma_mass_ratio_;};
  const float GetChi2Topo() const {return chi2_topo_;};
             
  const KFParticle GetParticle() const {return particle_;};

 protected:
   
  //  lambda candidate selection parameters (to be cut)
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

  KFParticle particle_;
  
};

#endif