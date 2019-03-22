#include "HexLGEventMessenger.hh"
#include "HexLGEventAction.hh"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithAnInteger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGEventMessenger::HexLGEventMessenger(HexLGEventAction* event)
 : fHexLGEvent(event)
{
  fVerboseCmd = new G4UIcmdWithAnInteger("/HexLG/eventVerbose",this);
  fVerboseCmd->SetGuidance("Set the verbosity of event data.");
  fVerboseCmd->SetParameterName("verbose",true);
  fVerboseCmd->SetDefaultValue(1);

  fPmtThresholdCmd = new G4UIcmdWithAnInteger("/HexLG/pmtThreshold",this);
  fPmtThresholdCmd->SetGuidance("Set the pmtThreshold (in # of photons)");

  fForceDrawPhotonsCmd=new G4UIcmdWithABool("/HexLG/forceDrawPhotons",this);
  fForceDrawPhotonsCmd->SetGuidance("Force drawing of photons.");
  fForceDrawPhotonsCmd
    ->SetGuidance("(Higher priority than /HexLG/forceDrawNoPhotons)");

  fForceDrawNoPhotonsCmd=new G4UIcmdWithABool("/HexLG/forceDrawNoPhotons",this);
  fForceDrawNoPhotonsCmd->SetGuidance("Force no drawing of photons.");
  fForceDrawNoPhotonsCmd
    ->SetGuidance("(Lower priority than /HexLG/forceDrawPhotons)");
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGEventMessenger::~HexLGEventMessenger(){
  delete fVerboseCmd;
  delete fPmtThresholdCmd;
  delete fForceDrawPhotonsCmd;
  delete fForceDrawNoPhotonsCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGEventMessenger::SetNewValue(G4UIcommand* command, G4String newValue){
  if( command == fVerboseCmd ){
    fHexLGEvent->SetEventVerbose(fVerboseCmd->GetNewIntValue(newValue));
  }
  else if( command == fPmtThresholdCmd ){
    fHexLGEvent->SetPMTThreshold(fPmtThresholdCmd->GetNewIntValue(newValue));
  }
  else if(command == fForceDrawPhotonsCmd){
    fHexLGEvent->SetForceDrawPhotons(fForceDrawPhotonsCmd
                                  ->GetNewBoolValue(newValue));
  }
  else if(command == fForceDrawNoPhotonsCmd){
    fHexLGEvent->SetForceDrawNoPhotons(fForceDrawNoPhotonsCmd
                                  ->GetNewBoolValue(newValue));
  }
}