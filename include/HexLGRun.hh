#ifndef HexLGRun_h
#define HexLGRun_h 1

#include "G4Run.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HexLGRun : public G4Run
{
  public:
    HexLGRun();
    ~HexLGRun();

    void IncPhotonCount_Scint(G4int count) {
      fPhotonCount_Scint  += count;
      fPhotonCount_Scint2 += count*count;
    }
    void IncPhotonCount_Ceren(G4int count) {
      fPhotonCount_Ceren  += count;
      fPhotonCount_Ceren2 += count*count;
    }
    void IncEDep(G4double dep) {
      fTotE  += dep;
      fTotE2 += dep*dep;
    }
    void IncAbsorption(G4int count) {
      fAbsorptionCount  += count;
      fAbsorptionCount2 += count*count;
    }
    void IncBoundaryAbsorption(G4int count) {
      fBoundaryAbsorptionCount  += count;
      fBoundaryAbsorptionCount2 += count*count;
    }
    void IncHitCount(G4int count) {
      fHitCount  += count;
      fHitCount2 += count*count;
    }
    void IncHitsAboveThreshold(G4int count) {
      fPMTsAboveThreshold  += count;
      fPMTsAboveThreshold2 += count*count;
    }

    virtual void Merge(const G4Run* run);

    void EndOfRun();


  private:
    G4int fHitCount, fHitCount2;
    G4int fPhotonCount_Scint, fPhotonCount_Scint2;
    G4int fPhotonCount_Ceren, fPhotonCount_Ceren2;
    G4int fAbsorptionCount, fAbsorptionCount2;
    G4int fBoundaryAbsorptionCount, fBoundaryAbsorptionCount2;
    G4int fPMTsAboveThreshold, fPMTsAboveThreshold2;

    G4double fTotE, fTotE2;
};

#endif