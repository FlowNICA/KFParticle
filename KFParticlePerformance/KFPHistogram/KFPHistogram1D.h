//----------------------------------------------------------------------------
// Structures to collect histograms online
// .
// @author  M.Zyzak
// @version 1.0
// @since   20.08.13
// 
// 
//  -= Copyright &copy ALICE HLT and CBM L1 Groups =-
//____________________________________________________________________________

#ifndef KFPHISTOGRAM1D
#define KFPHISTOGRAM1D

#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <cstdlib>

/** @class KFPHistogram1D
 ** @brief One-dimensional histogram.
 ** @author  M.Zyzak, I.Kisel
 ** @date 05.02.2019
 ** @version 1.0
 **
 ** The class is used to collect one-dimensional histograms in the environment,
 ** where ROOT is not available, for example at Intel Xeon Phi cards.
 ** It contains the histogram itself, number of bins, its name,
 ** minimum and maximum value of the axis. The histogram memory is allocated externally
 ** (by KFPHistogram) for better performance.
 **/

class KFPHistogram1D
{
 public:
   
  KFPHistogram1D(): fHistogram(nullptr), fSize(0), fName(""), fMinBin(0), fMaxBin(0) {}
  KFPHistogram1D(std::string name, int nBins, float minX, float maxX):
    fHistogram(nullptr), fSize(nBins+2), fName(name), fMinBin(minX), fMaxBin(maxX) {} ///< Constructor with user-defined parameters.
  ~KFPHistogram1D() {}
  
  int* GetHistogram() const { return fHistogram; } ///< Returns a pointer to the histogram data.
  std::string Name()  const { return fName; }      ///< Returns name of the histogram.
  float MinBin()      const { return fMinBin; }    ///< returns minimum of the X axis.
  float MaxBin()      const { return fMaxBin; }    ///< Returns maximum of the X axis.
  int   NBins()       const { return (fSize-2); }  ///< Returns number of bins.
  int   DataSize()    const { return fSize; }      ///< Returns number of bins plus underflow and overflow bins.
  int   Size()        const { return fSize; }      ///< Returns number of bins plus underflow and overflow bins.
  
  inline void SetBinContent(int iBin, int value) { fHistogram[iBin] = value; } ///< Sets the value of the bin "iBin".
  inline void SetHistogramMemory(int* pointer)   { fHistogram = pointer; }     ///< Sets the pointer to the memory with the histogram.
  
  /** Adds "value" to the histogram: calculates the corresponding bin and adds one there. */
  void Fill(float value)
  {
    int iBin = floor(float(value - fMinBin)/float(fMaxBin - fMinBin) * float(fSize-2)) + 1;
    
    if(iBin > fSize-1)
      iBin = fSize-1;
    if(iBin < 1)
      iBin = 0;

    fHistogram[iBin]++;
  }
  
  /** Adds histogram "h" to the current histogram bin-by-bin. */
  inline void operator += ( const KFPHistogram1D &h )
  {
    if( fSize != h.fSize )
    {
      std::cout << "Size of 1D histogram " << fName << " is incorrect. Stop the program." << std::endl;
    }
    else
    {
      for(int i=0; i<fSize; i++)
        fHistogram[i] += h.fHistogram[i];
    }
  }
  
  /** The copy-constructor. Memory for the fHistogram is not allocated, only the pointer is copied.*/
  KFPHistogram1D(const KFPHistogram1D& h): fHistogram(h.fHistogram), fSize(h.fSize), fName(h.fName), fMinBin(h.fMinBin), fMaxBin(h.fMaxBin)
  {
  }
  
  /** Copies object "h" to the current object. Memory for the fHistogram is not allocated, only the pointer is copied. Returns the current object.  */
  const KFPHistogram1D& operator=(const KFPHistogram1D& h)
  {
    fHistogram = h.fHistogram;
    fSize = h.fSize;
    fName = h.fName;
    fMinBin = h.fMinBin;
    fMaxBin = h.fMaxBin;
    
    return *this;
  }
  
 private:
  int* fHistogram;   ///< Pointer to the array with the values of the histogram.
  int fSize;         ///< Number of bins +2, additional two bins are reserved for the underflow and overflow.
  
  std::string fName; ///< Name of the histogram.
  float fMinBin;     ///< Minimum value at the X axis.
  float fMaxBin;     ///< Maximum value at the X axis.
};

#endif
