#ifndef FullControlConstants_H
#define FullControlConstants_H

  enum eTrackTypes
  {
    kSecPos = 0,
    kSecNeg,
    kPrimPos,
    kPrimNeg,
    kNumberOfTrackTypes
  };
  
  namespace PDGs
  {
    int proton = 2212;
    int pionMinus = -211;
    int lambda = 3122;
  }

#endif // FullControlConstants_H