/**
 ** @class InputContainer
 ** @brief Container with input information about event (vertex and tracks) and cuts used in the certain event
 ** @authors Oleksii Lubynets, Viktor Klochkov, Ilya Selyuzhenkov
 **
 ** Each event is characterized with primary vertex, set of tracks and set of cuts
 ** (in general case cuts for different events can be different).
 ** Primary vertex is characterized with its coordinates {x, y, z} and optionally with
 ** corresponding covariation matrix.
 ** In order to store primary vertex the KFVertex object is used.
 ** Each track is characterized with:
 ** x, y, z - three coordinates of point where it is defined;
 ** px, py, pz - three components of its momentum in this point;
 ** cov - covariation matrix of parameters mentioned above;
 ** field[0] - field[8] - magnetic field approximation coefficients along the track's trajectory
 ** field[9] - reference point for MF coefficients;
 ** charge - its charge;
 ** pdg - PID hypothesis for the track;
 ** id - its unique number (conserves through all the algorithm);
 ** nhits - number of hits in the tracking system which belong to the track. Is not used in the
 ** current version of KFPSimple, so default value 4 can be used;
 ** passcuts - flag variable which shows whether track satisfies pre-selection criteria. By default
 ** passcuts=1 should be used. 
 ** In order to store tracks the vector of KFParticle objects is used.
 ** In order to store cut values used for current event the CutsContainer object is used.
 **/

#ifndef InputContainer_H
#define InputContainer_H

#include "KFParticle.h"
#include "KFVertex.h"
#include "KFParticleTopoReconstructor.h"
#include "SimpleFinder.h"

class InputContainer{
 public:
  
  InputContainer() = default;
  virtual ~InputContainer() = default;

  void SetPV(float x, float y, float z);
  void SetPV(KFVertex vertex);
  void SetPV(KFPVertex vertex);
  void AddTrack(float x, float y, float z, float px, float py, float pz, std::vector<float> cov, float field[10], int charge, int pdg, int id, int nhits=4, int passcuts=1);
  KFParticleTopoReconstructor* CreateTopoReconstructor();                                                                                                   //^ not good
  SimpleFinder CreateSimpleFinder();

  void SetCuts(const CutsContainer& cuts) { cuts_ = cuts; }

 protected:
  
  double InversedChi2Prob(double p, int ndf) const;
    
  KFVertex vtx_;
  std::vector<KFParticle> tracks_;
  CutsContainer cuts_;

};

#endif//InputContainer_H