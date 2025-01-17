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


#ifndef KFPHISTOGRAM
#define KFPHISTOGRAM

#include "KFPHistogramSet.h"
#include "KFPartEfficiencies.h"
#include "KFParticleTopoReconstructor.h"
#include <map>
#include <iostream>
#include <fstream>

/** @class KFPHistogram
 ** @brief A common object containing histograms for all particle species.
 ** @author  M.Zyzak, I.Kisel
 ** @date 05.02.2019
 ** @version 1.0
 **
 ** The class is used to collect histograms in the environment,
 ** where ROOT is not available, for example at Intel Xeon Phi cards.
 ** Contains a set of histograms for each decay reconstructed by the
 ** KF Particle Finder package, allocates the memory for all histograms:
 ** This allows faster allocation, faster transfer of the memory,
 ** easier access from the Intel Xeon Phi, better performance.
 **/

class KFPHistogram
{  
 public:
  KFPHistogram(): fPdgToIndex(), fOutFileName("KFPHistograms.txt"), fMemory(nullptr)
  {
    KFPartEfficiencies partEff;
    fPdgToIndex = partEff.GetPdgToIndexMap();
    
    int dataSize = 0;
    for(int iParticle=0; iParticle<KFPartEfficiencies::nParticles; iParticle++)
    {
      fKFPHistogramSet[iParticle] = KFPHistogramSet(iParticle);
      dataSize += fKFPHistogramSet[iParticle].DataSize();
    }
    
    fMemory = new int[dataSize];
    std::memset(fMemory, 0, dataSize);
    
    int* pointer = fMemory;
    for(int iParticle=0; iParticle<KFPartEfficiencies::nParticles; iParticle++)
    {
      fKFPHistogramSet[iParticle].SetHistogramMemory(pointer);
      pointer += fKFPHistogramSet[iParticle].DataSize();
    }
  } ///< Default Constructor. Creates histograms, allocates memory for them.
  ~KFPHistogram() { if(fMemory) delete [] fMemory; }
  
  void SetOutFileName(std::string name) { fOutFileName = name; } ///< Set the name of the output file.
  
  inline void Fill(const KFParticle& particle)
  {
    std::map<int, int>::iterator it;
    it=fPdgToIndex.find(particle.GetPDG());
    if(it != fPdgToIndex.end())
      fKFPHistogramSet[it->second].Fill(particle);
  } ///< Fills histograms using parameters of the given particle.
  
  inline void Fill(const KFParticleTopoReconstructor& topoReconstructor)
  {
    for(unsigned int iParticle=0; iParticle<topoReconstructor.GetParticles().size(); iParticle++)
      Fill(topoReconstructor.GetParticles()[iParticle]);
  } ///< Fills histograms for each particle reconstructed by the KFParticleFinder object from the given KFParticleTopoReconstructor.
    
  KFPHistogramSet GetHistogramSet(int iSet)   const { return fKFPHistogramSet[iSet]; } ///< Returns set of histograms for the decay with index iSet.
  /** \brief Returns "iHistogram" histogram from the set of histograms for the decay with index "iSet". */
  KFPHistogram1D  GetHistogram(int iSet, int iHistogram) const { return fKFPHistogramSet[iSet].GetHistogram1D(iHistogram); }
  
  friend std::fstream & operator<<(std::fstream &strm, KFPHistogram &histograms)
  {
    for(int iParticle=0; iParticle<KFPartEfficiencies::nParticles; iParticle++ )
    {
      strm << iParticle << std::endl;
      const int& nHistograms = histograms.fKFPHistogramSet[iParticle].GetNHisto1D();
      for(int iHistogram = 0; iHistogram<nHistograms; iHistogram++)
      {
        const KFPHistogram1D& histogram = histograms.fKFPHistogramSet[iParticle].GetHistogram1D(iHistogram);
        strm << histogram.Name() << " " << histogram.MinBin() << " " << histogram.MaxBin() << " " << histogram.NBins() << std::endl;
        for(int iBin=0; iBin<histogram.NBins()+2; iBin++)
          strm << histogram.GetHistogram()[iBin] << " ";
        strm << std::endl;
      }
    }

    return strm;
  } ///< Stores all histograms to the output file.
  
  void Save() 
  {
    std::fstream file(fOutFileName.data(),std::fstream::out);
    file << (*this);
    file.close();
  } ///< Stores all histograms to the file with the name defined in KFPHistogram::fOutFileName.
  
  bool FillFromFile( std::string prefix )
  {
    std::fstream ifile(prefix.data(),std::fstream::in);
    if ( !ifile.is_open() ) return false;

    int iSet = 0;
    
    for(int iParticle=0; iParticle<KFPartEfficiencies::nParticles; iParticle++ )
    {
      ifile >> iSet;
      const int& nHistograms = fKFPHistogramSet[iParticle].GetNHisto1D();
      for(int iHistogram = 0; iHistogram<nHistograms; iHistogram++)
      {
        std::string name;
        float minBin = 0.f, maxBin = 0.f;
        int nBins = 0;
        ifile >> name >> minBin >> maxBin >> nBins;
        if(nBins  != fKFPHistogramSet[iParticle].GetHistogram1D(iHistogram).NBins()  || 
           minBin != fKFPHistogramSet[iParticle].GetHistogram1D(iHistogram).MinBin() || 
           maxBin != fKFPHistogramSet[iParticle].GetHistogram1D(iHistogram).MaxBin() ) 
        {
          std::cout << "Fatal error: size of the histograms is not in an agreement with the current version." << std::endl;
          exit(1);
        }
        
        int binContent = 0;
        for(int iBin=0; iBin<nBins+2; iBin++)
        {
          ifile >> binContent;
          fKFPHistogramSet[iParticle].SetHisto1DBinContent(iHistogram, iBin, binContent);
        }
      }
    }
    
    ifile.close();
    return true;
  } ///< Reads object from the file with the name defined by "prefix".
  
  inline void operator += ( const KFPHistogram &h )
  {
    for(int i=0; i<KFPartEfficiencies::nParticles; i++)
      fKFPHistogramSet[i] += h.fKFPHistogramSet[i];
  }///< Adds all histograms from object "h" to the current object.
  
 private:
  std::map<int, int> fPdgToIndex; ///< A map between PDG code and index of the decay in the KF Particle Finder scheme. A copy of an object from KFPartEfficiencies.
  std::string fOutFileName; ///< The name of the output file, where histograms will be stored.
  KFPHistogramSet fKFPHistogramSet[KFPartEfficiencies::nParticles]; ///< A set of histograms for all decays reconstructed by KF Particle Finder.
  int* fMemory; ///< A pointer to the memory for all histograms.
  
  KFPHistogram(const KFPHistogram&); ///< Does not allow copying of the objects of this class.
  KFPHistogram& operator=(const KFPHistogram&); ///< Does not allow copying of the objects of this class.
};

#endif
