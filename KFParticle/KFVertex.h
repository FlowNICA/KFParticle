//----------------------------------------------------------------------------
// Implementation of the KFParticle class
// .
// @author  S.Gorbunov, I.Kisel, I.Kulakov, M.Zyzak
// @version 1.0
// @since   20.08.13
// 
// 
//  -= Copyright &copy ALICE HLT and CBM L1 Groups =-
//____________________________________________________________________________


#ifndef KFVERTEX_H
#define KFVERTEX_H

#include "KFParticle.h"
#include "KFPVertex.h"

/** @class KFVertex
 ** @brief Mathematics for reconstruction of primary vertices based on KFParticle.
 ** @author  S.Gorbunov, I.Kisel, M.Zyzak
 ** @date 05.02.2019
 ** @version 1.0
 **
 ** The class is inherited from KFParticle, adds functionality for reconstruction of
 ** primary vertices.
 **/

class KFVertex : public KFParticle
{
 public:

  KFVertex():KFParticle(),fIsConstrained(false){ }
  KFVertex( const KFParticle &particle ): KFParticle(particle), fIsConstrained(false) {} ///< Vertex is constructed from the current position of a given particle.
  KFVertex( const KFPVertex &vertex );
  ~KFVertex()= default;

  Int_t GetNContributors() const { return fIsConstrained ?fNDF/2:(fNDF+3)/2; } ///< Returns number of particles used for construction of the vertex.


  void operator +=( const KFParticle &Daughter );  ///< Adds particle to a vertex.
  KFVertex operator -( const KFParticle &Daughter ) const; ///< Subtracts particle from a vertex, returns temporary object. Initial vertex stays untouched.
  void operator -=( const KFParticle &Daughter );  ///< Subtracts particle from a current vertex.

  void SetBeamConstraint( float X, float Y, float Z, 
                          float ErrX, float ErrY, float ErrZ );
  void SetBeamConstraintOff();

  void ConstructPrimaryVertex( const KFParticle *vDaughters[], int nDaughters,
                               Bool_t vtxFlag[], float ChiCut=3.5  );

 protected:

  Bool_t fIsConstrained; ///< Flag showing if the the beam constraint is set
  
#ifndef KFParticleStandalone
  ClassDef( KFVertex, 2 )
#endif
};


//---------------------------------------------------------------------
//
//     Inline implementation of the KFVertex methods
//
//---------------------------------------------------------------------


inline void KFVertex::operator+=( const KFParticle &Daughter )
{
  KFParticle::operator+=( Daughter );
}
  

inline void KFVertex::operator-=( const KFParticle &Daughter )
{
  Daughter.SubtractFromVertex( *this );
}
  
inline KFVertex KFVertex::operator-( const KFParticle &Daughter ) const 
{
  KFVertex tmp = *this;
  Daughter.SubtractFromVertex( tmp );
  return tmp;
}


#endif 
