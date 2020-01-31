#ifndef MF_Map_H
#define MF_Map_H

#include "TFile.h"
#include "TH3.h"

#include "KFParticleDef.h"

// #include "MFHistos.h"

class MFMap
{
public:
  
  static MFMap* Instance() {return instance_;};
  
  void GetField(const float_v xyz[], float_v B[]) const;
     
protected:
  
//   MFMap()    // CBM
//   {
//     fileMF_ =  TFile::Open("/home/user/cbmdir/kfpf/kfpf_analysis_tree_converter/input/field_mapF.root", "read");
// //     fileMF_ =  TFile::Open("/lustre/cbm/users/lubynets/kfpf/macro/field_mapF.root", "read");
//     histoBx_ = (TH3F*)fileMF_->Get("histoBx");
//     histoBy_ = (TH3F*)fileMF_->Get("histoBy");
//     histoBz_ = (TH3F*)fileMF_->Get("histoBz");
//   };
  
  MFMap()     // NA61/SHINE
  {
    fileMF_ =  TFile::Open("/home/user/cbmdir/kfpf/kfpf_analysis_tree_converter/input/na61mf.root", "read");
    histoBx_ = (TH3F*)fileMF_->Get("field_x");
    histoBy_ = (TH3F*)fileMF_->Get("field_y");
    histoBz_ = (TH3F*)fileMF_->Get("field_z");
  };
  
  virtual ~MFMap() = default;
  
private:
  
  static MFMap* instance_;
  
//   float signum(float x);           //TODO WHY not working in singleton?
  
  TFile* fileMF_;
  TH3F* histoBx_;
  TH3F* histoBy_;
  TH3F* histoBz_;
  
};
#endif