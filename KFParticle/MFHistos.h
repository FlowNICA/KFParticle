#ifndef MFHistos_H
#define MFHistos_H

#include "TH3.h"

class MFHistos
{
public:
  
  MFHistos() = default;
  virtual ~MFHistos() = default;
  
  void SetHistoBx(TH3F* histo){histoBx_ = histo;};
  void SetHistoBy(TH3F* histo){histoBy_ = histo;};
  void SetHistoBz(TH3F* histo){histoBz_ = histo;};
  
private:
  
  TH3F* histoBx_;
  TH3F* histoBy_;
  TH3F* histoBz_;
};
#endif