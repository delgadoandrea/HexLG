#ifndef HeLGDetectorConstruction_h
#define HeLGDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class HeLGDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    HeLGDetectorConstruction();
    virtual ~HeLG1DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    
    //G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  //protected:
    //G4LogicalVolume*  fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif