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
  fDimensionsCmd->SetParameterName("scint_x","scint_y","scint_z",false);
  fDimensionsCmd->SetDefaultUnit("cm");
  fDimensionsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fDimensionsCmd->SetToBeBroadcasted(false);

  fHousingThicknessCmd = new G4UIcmdWithADoubleAndUnit
    ("/HexLG/detector/housingThickness",this);
  fHousingThicknessCmd->SetGuidance("Set the thickness of the housing.");
  fHousingThicknessCmd->SetParameterName("d_mtl",false);
  fHousingThicknessCmd->SetDefaultUnit("cm");
  fHousingThicknessCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fHousingThicknessCmd->SetToBeBroadcasted(false);

  fPmtRadiusCmd = new G4UIcmdWithADoubleAndUnit
    ("/HexLG/detector/pmtRadius",this);
  fPmtRadiusCmd->SetGuidance("Set the radius of the PMTs.");
  fPmtRadiusCmd->SetParameterName("radius",false);
  fPmtRadiusCmd->SetDefaultUnit("cm");
  fPmtRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fPmtRadiusCmd->SetToBeBroadcasted(false);

  fNxCmd = new G4UIcmdWithAnInteger("/HexLG/detector/nx",this);
  fNxCmd->SetGuidance("Set the number of PMTs along the x-dimension.");
  fNxCmd->SetParameterName("nx",false);
  fNxCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fNxCmd->SetToBeBroadcasted(false);

  fNyCmd = new G4UIcmdWithAnInteger("/HexLG/detector/ny",this);
  fNyCmd->SetGuidance("Set the number of PMTs along the y-dimension.");
  fNyCmd->SetParameterName("ny",false);
  fNyCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fNyCmd->SetToBeBroadcasted(false);

  fNzCmd = new G4UIcmdWithAnInteger("/HexLG/detector/nz",this);
  fNzCmd->SetGuidance("Set the number of PMTs along the z-dimension.");
  fNzCmd->SetParameterName("nz",false);
  fNzCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fNzCmd->SetToBeBroadcasted(false);

  fSphereCmd = new G4UIcmdWithABool("/HexLG/detector/volumes/sphere",this);
  fSphereCmd->SetGuidance("Enable/Disable the sphere.");
  fSphereCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fSphereCmd->SetToBeBroadcasted(false);

  fReflectivityCmd = new G4UIcmdWithADouble("/HexLG/detector/reflectivity",this);
  fReflectivityCmd->SetGuidance("Set the reflectivity of the housing.");
  fReflectivityCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fReflectivityCmd->SetToBeBroadcasted(false);

  fWlsCmd = new G4UIcmdWithABool("/HexLG/detector/volumes/wls",this);
  fWlsCmd->SetGuidance("Enable/Disable the WLS slab");
  fWlsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fWlsCmd->SetToBeBroadcasted(false);

  fHexLGCmd = new G4UIcmdWithABool("/HexLG/detector/volumes/HexLG",this);
  fHexLGCmd->SetGuidance("Enable/Disable the main detector volume.");
  fHexLGCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fHexLGCmd->SetToBeBroadcasted(false);

  fNFibersCmd = new G4UIcmdWithAnInteger("/HexLG/detector/nfibers",this);
  fNFibersCmd->SetGuidance("Set the number of WLS fibers in the WLS slab.");
  fNFibersCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fNFibersCmd->SetToBeBroadcasted(false);

  fMainScintYield=new G4UIcmdWithADouble("/HexLG/detector/MainScintYield",this);
  fMainScintYield->SetGuidance("Set scinitillation yield of main volume.");
  fMainScintYield->SetGuidance("Specified in photons/MeV");
  fMainScintYield->AvailableForStates(G4State_PreInit,G4State_Idle);
  fMainScintYield->SetToBeBroadcasted(false);

  fWLSScintYield = new G4UIcmdWithADouble("/HexLG/detector/WLSScintYield",this);
  fWLSScintYield->SetGuidance("Set scintillation yield of WLS Slab");
  fWLSScintYield->SetGuidance("Specified in photons/MeV");
  fWLSScintYield->AvailableForStates(G4State_PreInit,G4State_Idle);
  fWLSScintYield->SetToBeBroadcasted(false);

  fSaveThresholdCmd = new G4UIcmdWithAnInteger("/HexLG/saveThreshold",this);
  fSaveThresholdCmd->
SetGuidance("Set the photon count threshold for saving the random number seed");
  fSaveThresholdCmd->SetParameterName("photons",true);
  fSaveThresholdCmd->SetDefaultValue(4500);
  fSaveThresholdCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fDefaultsCmd = new G4UIcommand("/HexLG/detector/defaults",this);
  fDefaultsCmd->SetGuidance("Set all detector geometry values to defaults.");
  fDefaultsCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fDefaultsCmd->SetToBeBroadcasted(false);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGDetectorMessenger::~HexLGDetectorMessenger()
{
  delete fDimensionsCmd;
  delete fHousingThicknessCmd;
  delete fPmtRadiusCmd;
  delete fNxCmd;
  delete fNyCmd;
  delete fNzCmd;
  delete fDetectorDir;
  delete fVolumesDir;
  delete fSphereCmd;
  delete fWlsCmd;
  delete fHexLGCmd;
  delete fNFibersCmd;
  delete fReflectivityCmd;
  delete fMainScintYield;
  delete fWLSScintYield;
  delete fSaveThresholdCmd;
  delete fDefaultsCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  /*if( command == fDimensionsCmd ){
    fHexLGDetector->SetDimensions(fDimensionsCmd->GetNew3VectorValue(newValue));
  }
  else if (command == fHousingThicknessCmd){
    fHexLGDetector->SetHousingThickness(fHousingThicknessCmd
                                     ->GetNewDoubleValue(newValue));
  }
  else if (command == fPmtRadiusCmd){
    fHexLGDetector->SetPMTRadius(fPmtRadiusCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fNxCmd){
    fHexLGDetector->SetNX(fNxCmd->GetNewIntValue(newValue));
  }
  else if (command == fNyCmd){
    fHexLGDetector->SetNY(fNyCmd->GetNewIntValue(newValue));
  }
  else if (command == fNzCmd){
    fHexLGDetector->SetNZ(fNzCmd->GetNewIntValue(newValue));
  }
  else if (command == fSphereCmd){
    fHexLGDetector->SetSphereOn(fSphereCmd->GetNewBoolValue(newValue));
  }
  else if (command == fReflectivityCmd){
    fHexLGDetector
      ->SetHousingReflectivity(fReflectivityCmd->GetNewDoubleValue(newValue));
  }
  else if (command == fWlsCmd){
    fHexLGDetector->SetWLSSlabOn(fWlsCmd->GetNewBoolValue(newValue));
  }
  else if (command == fHexLGCmd){
    fHexLGDetector->SetMainVolumeOn(fHexLGCmd->GetNewBoolValue(newValue));
  }
  else if (command == fNFibersCmd){
    fHexLGDetector->SetNFibers(fNFibersCmd->GetNewIntValue(newValue));
  }
  else if (command == fMainScintYield){
   fHexLGDetector->
              SetMainScintYield(fMainScintYield->GetNewDoubleValue(newValue));
  }
  else if (command == fWLSScintYield){
    fHexLGDetector->SetWLSScintYield(fWLSScintYield->GetNewDoubleValue(newValue));
  }
  else if( command == fSaveThresholdCmd ){
    fHexLGDetector->SetSaveThreshold(fSaveThresholdCmd->GetNewIntValue(newValue));
  }

  else if (command == fDefaultsCmd){
    fHexLGDetector->SetDefaults();
*/
    G4RunManager::GetRunManager()->ReinitializeGeometry(); //Add here this line
  //}
}