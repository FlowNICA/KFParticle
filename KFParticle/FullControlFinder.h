#ifndef FullControlFinder_H
#define FullControlFinder_H

#include "KFPTrackVector.h"
#include "KFVertex.h"
#include "KFPTrack.h"
#include "KFParticleSIMD.h"
#include "FullControlConstants.h"
#include "FC_Cuts.h"

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
  
  FC_Cuts& GetCuts() const {return cuts_;};                                        // Is it OK to use setter as getter (not constant reference)
  
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
};

#endif//FullControlFinder_H