#ifndef HexLGDetectorConstruction_h
#define HexLGDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class HexLGDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    HexLGDetectorConstruction();
    virtual ~HexLGDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetDefaults();
    
    //G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }

  //protected:
    //G4LogicalVolume*  fScoringVolume;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif