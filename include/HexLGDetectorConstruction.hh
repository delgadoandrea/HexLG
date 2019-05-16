#ifndef HexLGDetectorConstruction_h
#define HexLGDetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4Cache.hh"

//#include "HexLGScintSD.hh"
#include "HexLGPMTSD.hh"


class G4VPhysicalVolume;
class G4LogicalVolume;
class HexLGDetectorMessenger;

/// Detector construction class to define materials and geometry.

class HexLGDetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    HexLGDetectorConstruction();
    virtual ~HexLGDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetDefaults();

    void SetGunPosX(G4double);
    void SetGunPosY(G4double);    

    G4double GetGunPosX() const   {return fGunPosX;};
    G4double GetGunPosY() const   {return fGunPosY;};    

   private:

    G4Cache<HexLGPMTSD*> fPmt_SD; //Right

    G4double  fGunPosX;
    G4double  fGunPosY;    
    
    HexLGDetectorMessenger* fDetectorMessenger;



};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif