#ifndef FullControlFinder_H
#define FullControlFinder_H

#include "KFPTrackVector.h"
#include "KFVertex.h"
#include "KFPTrack.h"
#include "KFParticleSIMD.h"
#include "FullControlConstants.h"
#include "FC_Cuts.h"
#include "Output_interface.h"

class FullControlFinder
{
  
 public:
   
  FullControlFinder() = default;
  virtual ~FullControlFinder() = default;
  
  void  Init(const KFPTrackVector &tracks, const KFVertex &pv);
  void  SortTracks();
  
  void  FindParticles();
  
  const KFPTrackVector* GetTracks() const {return &tracks_;};
  
  const std::vector<float>& GetMass() const {return vec_mass_;};            // TODO remove after debug procedure
  
  const std::vector<Output_interface>& GetLambda() const {return vec_lambda_;};
  
  void  SetCuts(const FC_Cuts& cuts) { cuts_ = cuts; }
  const FC_Cuts& GetCuts() const {return cuts_;};                                       // Is it OK to use setter as getter (not constant reference)? How to do better?
                                                                            // WHY does not work with 'second' const?
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
             
  FC_Cuts cuts_;
  
  float mass_;                             // TODO remove after debug procedure
  std::vector<float> vec_mass_;            // TODO remove after debug procedure
  
  Output_interface lambda_;                       // IS it ok to make them (global) fields?
  std::vector<Output_interface> vec_lambda_;
};

#endif//FullControlFinder_H