//----------------------------------------------------------------------------
// Implementation of the KFParticle class
// .
// @author  I.Kisel, I.Kulakov, M.Zyzak
// @version 1.0
// @since   20.08.13
// 
// 
//  -= Copyright &copy ALICE HLT and CBM L1 Groups =-
//____________________________________________________________________________

#include "KFMCParticle.h"

#ifndef KFParticleStandalone
ClassImp(KFMCParticle)
#endif

KFMCParticle::KFMCParticle() :fDaughterIds(), fMCTrackID(-1), fMotherId(-1), fPDG(0), fInitialParticleId(-1)
{
  for(int i=0; i<3; i++)
  {
    fIsReconstructable[i] = false;
    fIsV0[i] = false;
  }
  fIsReconstructable[3] = false;
  fIsReconstructable[4] = false;
}

KFMCParticle::~KFMCParticle()
= default;

void KFMCParticle::AddDaughter( int i )
{
  fDaughterIds.push_back(i);
}
