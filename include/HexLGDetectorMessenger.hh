#ifndef HexLGDetectorMessenger_h
#define HexLGDetectorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class HexLGDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithAnInteger;
class G4UIcommand;
class G4UIcmdWithABool;
class G4UIcmdWithADouble;

class HexLGDetectorMessenger: public G4UImessenger
{
  public:

    HexLGDetectorMessenger(HexLGDetectorConstruction*);
    virtual ~HexLGDetectorMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:

    HexLGDetectorConstruction*     fDetector;
    G4UIdirectory*               fDetectorDir;
    G4UIdirectory*               fVolumesDir;
    G4UIcmdWith3VectorAndUnit*   fDimensionsCmd;
    G4UIcmdWithADouble*          fGunPosXCmd;
    G4UIcmdWithADouble*          fGunPosYCmd;    
};

#endif