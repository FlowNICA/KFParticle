#include "General_interface.h"

#include "TMath.h"


void General_interface::SetPV(float x, float y, float z)
{
  KFPVertex primVtx_tmp;
  primVtx_tmp.SetXYZ(x, y, z);
  primVtx_tmp.SetCovarianceMatrix( 0,0,0,0,0,0 );
  primVtx_tmp.SetNContributors( 0 );
  primVtx_tmp.SetChi2( -100 );

  vtx_ = KFVertex(primVtx_tmp);  
}

void General_interface::SetPV(KFVertex vertex)
{
  vtx_ = vertex;
}


void General_interface::SetPV(KFPVertex vertex)
{
  vtx_ = KFVertex(vertex);
}

void General_interface::AddTrack(float x, float y, float z,
                                 float px, float py, float pz,
                                 std::vector<float> cov,
                                 float field[10],
                                 int charge,
                                 int pdg,
                                 int id,
                                 int nhits,
                                 int passcuts)
{
  if(nhits<3 || passcuts == 0 || pdg == 0 || pdg == -2)
    return;  
  
  KFParticle particle;
  particle.X() = x;
  particle.Y() = y;
  particle.Z() = z;
  particle.Px() = px;
  particle.Py() = py;
  particle.Pz() = pz;
  for(int i=0; i<21; i++)
    particle.Covariance(i) = cov[i];
  for(int i=0; i<10; i++)
    particle.SetFieldCoeff(field[i], i);
  particle.Q() = charge;
  particle.SetPDG(pdg);
  
  tracks_.push_back(particle);
}

KFParticleTopoReconstructor* General_interface::CreateTopoReconstructor()
{
  auto* TR = new KFParticleTopoReconstructor;
  TR->SetChi2PrimaryCut( InversedChi2Prob(0.0001, 2) );
    
  KFPTrackVector track_tmp, track_empty;
  track_tmp.Resize(tracks_.size());
  for(int iTr=0; iTr<tracks_.size(); iTr++)
  {
    for(Int_t iP=0; iP<6; iP++)
      track_tmp.SetParameter(tracks_[iTr].GetParameter(iP), iP, iTr);
    for(Int_t iC=0; iC<21; iC++)
      track_tmp.SetCovariance(tracks_[iTr].GetCovariance(iC), iC, iTr);
    for(Int_t iF=0; iF<10; iF++)
      track_tmp.SetFieldCoefficient(tracks_[iTr].GetFieldCoeff()[iF], iF, iTr);
    track_tmp.SetPDG(tracks_[iTr].GetPDG(), iTr);
    track_tmp.SetQ(tracks_[iTr].GetQ(), iTr);
    track_tmp.SetPVIndex(-1, iTr);    
    track_tmp.SetId(tracks_[iTr].Id(), iTr);
  }
  TR->Init(track_tmp, track_empty);
  
  TR->AddPV(vtx_);
  
  return TR;
}

FullControlFinder General_interface::CreateFCFinder()
{
  FullControlFinder FCF;

  KFPTrackVector track_tmp;
  
  track_tmp.Resize(tracks_.size());
  
  for(int iTr=0; iTr<tracks_.size(); iTr++)
  {
    for(Int_t iP=0; iP<6; iP++)
      track_tmp.SetParameter(tracks_[iTr].GetParameter(iP), iP, iTr);
    for(Int_t iC=0; iC<21; iC++)
      track_tmp.SetCovariance(tracks_[iTr].GetCovariance(iC), iC, iTr);
    for(Int_t iF=0; iF<10; iF++)
      track_tmp.SetFieldCoefficient(tracks_[iTr].GetFieldCoeff()[iF], iF, iTr);
    track_tmp.SetPDG(tracks_[iTr].GetPDG(), iTr);
    track_tmp.SetQ(tracks_[iTr].GetQ(), iTr);
    track_tmp.SetPVIndex(-1, iTr);   
    track_tmp.SetId(tracks_[iTr].Id(), iTr);
  }
  FCF.Init(track_tmp, vtx_);
  FCF.SetCuts(cuts_);
  
  return FCF;  
}

double General_interface::InversedChi2Prob(double p, int ndf) const
{
  const double epsilon = 1.e-14;
  double chi2Left = 0.f;
  double chi2Right = 10000.f;
  
  double probLeft = p - TMath::Prob(chi2Left, ndf);
  
  double chi2Centr = (chi2Left+chi2Right)/2.f;
  double probCentr = p - TMath::Prob( chi2Centr, ndf);
  
  while( TMath::Abs(chi2Right-chi2Centr)/chi2Centr > epsilon )
  {
    if(probCentr * probLeft > 0.f)
    {
      chi2Left = chi2Centr;
      probLeft = probCentr;
    }
    else
    {
      chi2Right = chi2Centr;
    }
    
    chi2Centr = (chi2Left+chi2Right)/2.f;
    probCentr = p - TMath::Prob( chi2Centr, ndf);
  }
  
  return chi2Centr;
}
