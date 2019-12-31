#ifndef MF_Map_H
#define MF_Map_H

#include "TFile.h"
#include "TH3.h"

#include "KFParticleDef.h"

// #include "MFHistos.h"

class MFMap
{
public:
  
  static MFMap* Instance()
  {
//     if(instance_==nullptr)
//       instance_ = new MFMap();
    return instance_;
  };
  
  void Pass(){/*std::cout << "NULL\n"*/;};
    
private:
  
  MFMap() = default;
//   {
//     fileMF_ =  TFile::Open("/home/user/cbmdir/kfpf/kfpf_analysis_tree_converter/input/field_mapF.root", "read");
//     histoBx_ = (TH3F*)fileMF_->Get("histoBx");
//     histoBy_ = (TH3F*)fileMF_->Get("histoBy");
//     histoBz_ = (TH3F*)fileMF_->Get("histoBz");
//   };
  
  virtual ~MFMap() = default;
  
 
  static MFMap* instance_;
  
//   TFile* fileMF_;
//   TH3F* histoBx_;
//   TH3F* histoBy_;
//   TH3F* histoBz_;
  
};
#endif