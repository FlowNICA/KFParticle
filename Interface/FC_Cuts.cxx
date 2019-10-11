#include "FC_Cuts.h"

void FC_Cuts::CancelCuts()
{
  float practInf = 1e9;
  cut_chi2_geo_ = practInf;
  cut_chi2_prim_neg_ = -practInf;
  cut_chi2_prim_pos_ = -practInf;
  cut_chi2_topo_ = practInf;
  cut_cosine_daughter_neg_ = -practInf;
  cut_cosine_daughter_pos_ = -practInf;
  cut_distance_ = practInf;
  cut_l_down_ = -practInf;
  cut_l_up_ =  practInf;
  cut_ldl_ = -practInf;
  cut_ldl_sec_ = -practInf;
  cut_sigma_mass_ratio_ = practInf;
  cut_is_from_pv_ = 799;
}