#include "HexLGActionInitialization.hh"

#include "HexLGPrimaryGeneratorAction.hh"
#include "HexLGDetectorConstruction.hh"

#include "HexLGRunAction.hh"
#include "HexLGEventAction.hh"
#include "HexLGTrackingAction.hh"
#include "HexLGSteppingAction.hh"
#include "HexLGStackingAction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGActionInitialization::HexLGActionInitialization(
   const HexLGDetectorConstruction* det)
  : G4VUserActionInitialization(), fDetector(det)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGActionInitialization::~HexLGActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGActionInitialization::BuildForMaster() const
{
  SetUserAction(new HexLGRunAction());
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGActionInitialization::Build() const
{
  SetUserAction(new HexLGPrimaryGeneratorAction());

  HexLGEventAction* eventAction = new HexLGEventAction(fDetector);
  SetUserAction(eventAction);
  SetUserAction(new HexLGStackingAction(eventAction));

  SetUserAction(new HexLGRunAction());
  SetUserAction(new HexLGTrackingAction());
  SetUserAction(new HexLGSteppingAction(eventAction));
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......