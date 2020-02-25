#include "MFMap.h"

MFMap* MFMap::instance_ = new MFMap();

float MFMap::signum (float x) const
{
  if(x>0.)
    return 1.;
  else
    return -1.;
};

void MFMap::GetField(const float_v xyz[], float_v B[]) const
{
  const float hXlow = histoBx_ -> GetXaxis() -> GetBinCenter(1);
  const float hYlow = histoBx_ -> GetYaxis() -> GetBinCenter(1);
  const float hZlow = histoBx_ -> GetZaxis() -> GetBinCenter(1);
  const float hXup = histoBx_ -> GetXaxis() -> GetBinCenter(histoBx_ -> GetXaxis() -> GetNbins());
  const float hYup = histoBx_ -> GetYaxis() -> GetBinCenter(histoBx_ -> GetYaxis() -> GetNbins());
  const float hZup = histoBx_ -> GetZaxis() -> GetBinCenter(histoBx_ -> GetZaxis() -> GetNbins());
  
  for(int iv=0; iv<float_vLen; iv++)
  {
    float x = xyz[0][iv];
    float y = xyz[1][iv];
    float z = xyz[2][iv]-40.;
    
    float x_l = fabs(x);        // CBM
    float y_l = fabs(y);
    float z_l = fabs(z);
    
//     float x_l = xyz[0][iv];
//     float y_l = xyz[1][iv];
//     float z_l = xyz[2][iv];     // NA61/SHINE
    
    B[0][iv] = 0.;
    B[1][iv] = 0.;
    B[2][iv] = 0.;
    
    if(x_l<=hXlow || x_l>=hXup || y_l<=hYlow || y_l>=hYup || z_l<=hZlow || z_l>=hZup) continue;      // CBM
    if(x_l!=x_l || y_l!=y_l || z_l!=z_l) continue;
    
    B[0][iv] = 10.*(histoBx_ -> Interpolate(x_l, y_l, z_l)*signum(x)*signum(y));    // CBM
    B[1][iv] = 10.*(histoBy_ -> Interpolate(x_l, y_l, z_l));
    B[2][iv] = 10.*(histoBz_ -> Interpolate(x_l, y_l, z_l)*signum(y)*signum(z));
    
//     B[0][iv] = 10.*(histoBx_ -> Interpolate(x_l, y_l, z_l));                        // NA61/SHINE
//     B[1][iv] = 10.*(histoBy_ -> Interpolate(x_l, y_l, z_l));
//     B[2][iv] = 10.*(histoBz_ -> Interpolate(x_l, y_l, z_l));
  }
};
