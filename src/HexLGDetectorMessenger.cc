#include "HexLGDetectorMessenger.hh"
#include "HexLGDetectorConstruction.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcommand.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4Scintillation.hh"

#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGDetectorMessenger::HexLGDetectorMessenger(HexLGDetectorConstruction* detector)
 : fHexLGDetector(detector)
{
  //Setup a command directory for detector controls with guidance
  fDetectorDir = new G4UIdirectory("/HexLG/detector/");
  fDetectorDir->SetGuidance("Detector geometry control");

  fVolumesDir = new G4UIdirectory("/HexLG/detector/volumes/");
  fVolumesDir->SetGuidance("Enable/disable volumes");
 
  //Various commands for modifying detector geometry
  fDimensionsCmd =
    new G4UIcmdWith3VectorAndUnit("/HexLG/detector/dimensions",this);
  fDimensionsCmd->SetGuidance("Set the dimensions of the detector volume.");
  fDimensionsCmd->SetDefaultUnit("cm");
  fDimensionsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fDimensionsCmd->SetToBeBroadcasted(false);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGDetectorMessenger::~HexLGDetectorMessenger()
{
  delete fDimensionsCmd;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  //if( command == fDimensionsCmd ){
  //  fHexLGDetector->SetDimensions(fDimensionsCmd->GetNew3VectorValue(newValue));
  //}
  G4RunManager::GetRunManager()->ReinitializeGeometry(); //Add here this line
  
}