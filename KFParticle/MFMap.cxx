#include "MFMap.h"

MFMap* MFMap::instance_ = new MFMap();

void MFMap::GetField(const float_v xyz[], float_v B[]) const
{
  for(int iv=0; iv<float_vLen; iv++)
  {
    float x_l = fabs(xyz[0][iv]);
    float y_l = fabs(xyz[1][iv]);
    float z_l = fabs(xyz[2][iv] - 40.);
    
    // ----- BEGIN no extrapolation ----------------------------------------
//     B[0][iv] = histoBx_ -> GetBinContent(histoBx_->FindBin(x_l, y_l, z_l));
//     B[1][iv] = histoBy_ -> GetBinContent(histoBy_->FindBin(x_l, y_l, z_l));
//     B[2][iv] = histoBz_ -> GetBinContent(histoBz_->FindBin(x_l, y_l, z_l));
    // ----- END no extrapolation ------------------------------------------
    
    if(x_l<0 || x_l>300. || y_l<0 || y_l>300. || z_l<0. || z_l>500.)
    {
      B[0][iv] = 0.;
      B[1][iv] = 0.;
      B[2][iv] = 0.;
      
      continue;
    }      
    
    float stepX = 2.;
    float stepY = 2.;
    float stepZ = 2.;
    
    float delta_X = (x_l - histoBx_->GetXaxis()->GetBinCenter(histoBx_->GetXaxis()->FindBin(x_l)))/stepX;
    float delta_Y = (y_l - histoBx_->GetYaxis()->GetBinCenter(histoBx_->GetYaxis()->FindBin(y_l)))/stepY; // histoBx_ is OK
    float delta_Z = (z_l - histoBx_->GetZaxis()->GetBinCenter(histoBx_->GetZaxis()->FindBin(z_l)))/stepZ; // histoBx_ is OK
        
    
    //--------- X field component --------------------
    float Hx[2][2][2];
    Hx[0][0][0] = histoBx_ -> GetBinContent(histoBx_->FindBin(x_l-stepX/2., y_l-stepY/2., z_l-stepZ/2.));
    Hx[0][0][1] = histoBx_ -> GetBinContent(histoBx_->FindBin(x_l-stepX/2., y_l-stepY/2., z_l+stepZ/2.));
    Hx[0][1][0] = histoBx_ -> GetBinContent(histoBx_->FindBin(x_l-stepX/2., y_l+stepY/2., z_l-stepZ/2.));
    Hx[0][1][1] = histoBx_ -> GetBinContent(histoBx_->FindBin(x_l-stepX/2., y_l+stepY/2., z_l+stepZ/2.));
    Hx[1][0][0] = histoBx_ -> GetBinContent(histoBx_->FindBin(x_l+stepX/2., y_l-stepY/2., z_l-stepZ/2.));
    Hx[1][0][1] = histoBx_ -> GetBinContent(histoBx_->FindBin(x_l+stepX/2., y_l-stepY/2., z_l+stepZ/2.));
    Hx[1][1][0] = histoBx_ -> GetBinContent(histoBx_->FindBin(x_l+stepX/2., y_l+stepY/2., z_l-stepZ/2.));
    Hx[1][1][1] = histoBx_ -> GetBinContent(histoBx_->FindBin(x_l+stepX/2., y_l+stepY/2., z_l+stepZ/2.));
    
    // x-axis interpolation
    float HHx[2][2];
    HHx[0][0] = Hx[0][0][0]*(0.5-delta_X) + Hx[1][0][0]*(0.5+delta_X);
    HHx[0][1] = Hx[0][0][1]*(0.5-delta_X) + Hx[1][0][1]*(0.5+delta_X);
    HHx[1][0] = Hx[0][1][0]*(0.5-delta_X) + Hx[1][1][0]*(0.5+delta_X);
    HHx[1][1] = Hx[0][1][1]*(0.5-delta_X) + Hx[1][1][1]*(0.5+delta_X);
    
    // y-axis interpolation
    float HHHx[2];
    HHHx[0] = HHx[0][0]*(0.5-delta_Y) + HHx[1][0]*(0.5+delta_Y);
    HHHx[1] = HHx[0][1]*(0.5-delta_Y) + HHx[1][1]*(0.5+delta_Y);
    
    B[0][iv] = HHHx[0]*(0.5-delta_Z) + HHHx[1]*(0.5+delta_Z);
    //----------------------------------------------------
    
    //--------- Y field component --------------------
    float Hy[2][2][2];
    Hy[0][0][0] = histoBy_ -> GetBinContent(histoBy_->FindBin(x_l-stepX/2., y_l-stepY/2., z_l-stepZ/2.));
    Hy[0][0][1] = histoBy_ -> GetBinContent(histoBy_->FindBin(x_l-stepX/2., y_l-stepY/2., z_l+stepZ/2.));
    Hy[0][1][0] = histoBy_ -> GetBinContent(histoBy_->FindBin(x_l-stepX/2., y_l+stepY/2., z_l-stepZ/2.));
    Hy[0][1][1] = histoBy_ -> GetBinContent(histoBy_->FindBin(x_l-stepX/2., y_l+stepY/2., z_l+stepZ/2.));
    Hy[1][0][0] = histoBy_ -> GetBinContent(histoBy_->FindBin(x_l+stepX/2., y_l-stepY/2., z_l-stepZ/2.));
    Hy[1][0][1] = histoBy_ -> GetBinContent(histoBy_->FindBin(x_l+stepX/2., y_l-stepY/2., z_l+stepZ/2.));
    Hy[1][1][0] = histoBy_ -> GetBinContent(histoBy_->FindBin(x_l+stepX/2., y_l+stepY/2., z_l-stepZ/2.));
    Hy[1][1][1] = histoBy_ -> GetBinContent(histoBy_->FindBin(x_l+stepX/2., y_l+stepY/2., z_l+stepZ/2.));
    
    // x-axis interpolation
    float HHy[2][2];
    HHy[0][0] = Hy[0][0][0]*(0.5-delta_X) + Hy[1][0][0]*(0.5+delta_X);
    HHy[0][1] = Hy[0][0][1]*(0.5-delta_X) + Hy[1][0][1]*(0.5+delta_X);
    HHy[1][0] = Hy[0][1][0]*(0.5-delta_X) + Hy[1][1][0]*(0.5+delta_X);
    HHy[1][1] = Hy[0][1][1]*(0.5-delta_X) + Hy[1][1][1]*(0.5+delta_X);
    
    // y-axis interpolation
    float HHHy[2];
    HHHy[0] = HHy[0][0]*(0.5-delta_Y) + HHy[1][0]*(0.5+delta_Y);
    HHHy[1] = HHy[0][1]*(0.5-delta_Y) + HHy[1][1]*(0.5+delta_Y);
    
    B[1][iv] = HHHy[0]*(0.5-delta_Z) + HHHy[1]*(0.5+delta_Z);
    //----------------------------------------------------
   
    //--------- Z field component --------------------
    float Hz[2][2][2];
    Hz[0][0][0] = histoBz_ -> GetBinContent(histoBz_->FindBin(x_l-stepX/2., y_l-stepY/2., z_l-stepZ/2.));
    Hz[0][0][1] = histoBz_ -> GetBinContent(histoBz_->FindBin(x_l-stepX/2., y_l-stepY/2., z_l+stepZ/2.));
    Hz[0][1][0] = histoBz_ -> GetBinContent(histoBz_->FindBin(x_l-stepX/2., y_l+stepY/2., z_l-stepZ/2.));
    Hz[0][1][1] = histoBz_ -> GetBinContent(histoBz_->FindBin(x_l-stepX/2., y_l+stepY/2., z_l+stepZ/2.));
    Hz[1][0][0] = histoBz_ -> GetBinContent(histoBz_->FindBin(x_l+stepX/2., y_l-stepY/2., z_l-stepZ/2.));
    Hz[1][0][1] = histoBz_ -> GetBinContent(histoBz_->FindBin(x_l+stepX/2., y_l-stepY/2., z_l+stepZ/2.));
    Hz[1][1][0] = histoBz_ -> GetBinContent(histoBz_->FindBin(x_l+stepX/2., y_l+stepY/2., z_l-stepZ/2.));
    Hz[1][1][1] = histoBz_ -> GetBinContent(histoBz_->FindBin(x_l+stepX/2., y_l+stepY/2., z_l+stepZ/2.));
    
    // x-axis interpolation
    float HHz[2][2];
    HHz[0][0] = Hz[0][0][0]*(0.5-delta_X) + Hz[1][0][0]*(0.5+delta_X);
    HHz[0][1] = Hz[0][0][1]*(0.5-delta_X) + Hz[1][0][1]*(0.5+delta_X);
    HHz[1][0] = Hz[0][1][0]*(0.5-delta_X) + Hz[1][1][0]*(0.5+delta_X);
    HHz[1][1] = Hz[0][1][1]*(0.5-delta_X) + Hz[1][1][1]*(0.5+delta_X);
    
    // y-axis interpolation
    float HHHz[2];
    HHHz[0] = HHz[0][0]*(0.5-delta_Y) + HHz[1][0]*(0.5+delta_Y);
    HHHz[1] = HHz[0][1]*(0.5-delta_Y) + HHz[1][1]*(0.5+delta_Y);
    
    B[2][iv] = HHHz[0]*(0.5-delta_Z) + HHHz[1]*(0.5+delta_Z);
    //----------------------------------------------------
   } 
};
