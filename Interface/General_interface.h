#ifndef General_interface_H
#define General_interface_H

#include "KFParticle.h"
#include "KFVertex.h"
#include "KFParticleTopoReconstructor.h"
#include "FullControlFinder.h"

class General_interface{
 public:
  
  General_interface() = default;
  virtual ~General_interface() = default;

  void SetPV(float x, float y, float z);
  void SetPV(KFVertex vertex);
  void SetPV(KFPVertex vertex);
  void AddTrack(float x, float y, float z, float px, float py, float pz, std::vector<float> cov, float field[10], int charge, int pdg, int nhits=4, int passcuts=1, int motherId=-999, int motherPdg=-999);
  KFParticleTopoReconstructor* CreateTopoReconstructor();                                                                                             //^ not good
  FullControlFinder CreateFCFinder();
  
 protected:
  
  double InversedChi2Prob(double p, int ndf) const;
    
  KFVertex vtx_;
  
  std::vector<KFParticle> tracks_;
  std::vector<int> pdg_;
  std::vector<int> mother_id_;
  std::vector<int> mother_pdg_;
};

#endif //General_interface_H