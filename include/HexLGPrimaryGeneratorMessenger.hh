//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef HexLGPrimaryGeneratorMessenger_h
#define HexLGPrimaryGeneratorMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class HexLGPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HexLGPrimaryGeneratorMessenger: public G4UImessenger
{
  public:
    HexLGPrimaryGeneratorMessenger(HexLGPrimaryGeneratorAction* );
    virtual ~HexLGPrimaryGeneratorMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:
    HexLGPrimaryGeneratorAction* fHexLGAction;
    G4UIdirectory*                  fGunDir;
    G4UIcmdWithADoubleAndUnit*      fPolarCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
