#ifndef SimpleFinder_H
#define SimpleFinder_H

#include "KFPTrackVector.h"
#include "KFVertex.h"
#include "KFPTrack.h"
#include "KFParticleSIMD.h"
#include "Constants.h"
#include "CutsContainer.h"
#include "OutputContainer.h"

class SimpleFinder
{
  
 public:
   
  SimpleFinder() = default;
  virtual ~SimpleFinder() = default;
  
  void  Init(const KFPTrackVector &tracks, const KFVertex &pv);
  void  SortTracks();
  
  void  FindParticles();
  
  const KFPTrackVector* GetTracks() const {return &tracks_;};
  
  const std::vector<float>& GetMass() const {return vec_mass_;};            // TODO remove after debug procedure
  
  const std::vector<OutputContainer>& GetLambdas() const {return vec_lambda_;};
  
  void  SetCuts(const CutsContainer& cuts) { cuts_ = cuts; }
  const CutsContainer& GetCuts() const {return cuts_;};

 protected:
   
  float CalculateChiToPrimaryVertex(const KFPTrack &track, const int pid) const;  ///< Calculates \f$\chi^2\f$ of the track to the primary vertex (PV)
  void  CalculateParamsInPCA(const KFPTrack &track1, const int pid1, const KFPTrack &track2, const int pid2, std::array<float, 8> &pars1, std::array<float, 8> &pars2) const;
  ///< Recalculates daughters tracks' parameters in the point of their closest approach
  
  float CalculateDistanceBetweenParticles(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2) const;  ///< Calculates the distance between daughter tracks in their closest approach
  float CalculateCosMomentumSum(const std::array<float, 8> &pars1, const std::array<float, 8> &pars2) const;    ///< Calculates the cosine of the angle between daughter's and mother's momenta
  KFParticleSIMD ConstructMother(const KFPTrack &track1, const int pid1, const KFPTrack &track2, const int pid2) const;   ///< Creates mother particle as the KFParticleSIMD object
  float CalculateChi2Geo(const KFParticleSIMD mother) const;  ///< Calculates \f$\chi^2\f$ of daughters' tracks in their closest approach
  void  CalculateMotherProperties(const KFParticleSIMD mother, float &l, float &ldl, int &isFromPV) const;
  ///< Calculates distance between primary and secondary vertices with error and determines whether mother comes from the PV
  
  float CalculateCosTopo(const KFParticleSIMD mother) const;  ///< Calculates cosine of the angle between reconstructed mother's momentum and mother's radius vector beginning in the PV
  float CalculateChi2Topo(const KFParticleSIMD mother) const; ///< Calculates \f$\chi^2\f$ of the mother's track to the PV
  void  SaveParticle(OutputContainer Lambda);                 ///< Saves selected particle with set of geometrical decay parameters
  
  KFPTrackVector tracks_;
  KFVertex prim_vx_;
  
  std::array<std::vector<int>, kNumberOfTrackTypes> trIndex_;
             
  CutsContainer cuts_;
  
  float mass_;                             // TODO remove after debug procedure
  std::vector<float> vec_mass_;            // TODO remove after debug procedure
  
  std::vector<OutputContainer> vec_lambda_;
};

#endif//SimpleFinder_H