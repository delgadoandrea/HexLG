#include "G4Types.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4String.hh"

#include "FTFP_BERT.hh"
#include "G4OpticalPhysics.hh"
#include "G4EmStandardPhysics_option4.hh"

#include "HexLGDetectorConstruction.hh"
#include "HexLGActionInitialization.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char** argv)
{
  //detect interactive mode (if no arguments) and define UI session
  G4UIExecutive* ui = nullptr;
  if (argc == 1) { ui = new G4UIExecutive(argc,argv); }

  G4RunManager * runManager = new G4RunManager;

  HexLGDetectorConstruction* det = new HexLGDetectorConstruction();
  runManager->SetUserInitialization(det);

  G4VModularPhysicsList* physicsList = new FTFP_BERT; //TODO Compare to PROSPECT's Physics List
  physicsList->ReplacePhysics(new G4EmStandardPhysics_option4());
  G4OpticalPhysics* opticalPhysics = new G4OpticalPhysics();
  opticalPhysics->SetWLSTimeProfile("delta");

  opticalPhysics->SetScintillationYieldFactor(1.0);
  opticalPhysics->SetScintillationExcitationRatio(0.0);

  opticalPhysics->SetMaxNumPhotonsPerStep(100);
  opticalPhysics->SetMaxBetaChangePerStep(10.0);

  opticalPhysics->SetTrackSecondariesFirst(kCerenkov, true);
  opticalPhysics->SetTrackSecondariesFirst(kScintillation, true);

  physicsList->RegisterPhysics(opticalPhysics);
  runManager->SetUserInitialization(physicsList);

  runManager->SetUserInitialization(new HexLGActionInitialization(det));

  //initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();

  //get the pointer to the User Interface manager 
  G4UImanager* UImanager = G4UImanager::GetUIpointer();

  if (ui) {
    //interactive mode
    UImanager->ApplyCommand("/control/execute vis.mac");
    //if (ui->IsGUI()) {
    //  UImanager->ApplyCommand("/control/execute gui.mac");
    //}
    ui->SessionStart();
    delete ui;
  } else {
    //batch mode  
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }

  // job termination
  delete visManager;
  delete runManager;
  return 0;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......