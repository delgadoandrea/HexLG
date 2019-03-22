#include "HexLGHistoManager.hh"
#include "G4UnitsTable.hh"

//#include<vector>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGHistoManager::HexLGHistoManager()
  : fFileName("HexLG")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGHistoManager::~HexLGHistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGHistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HexLGHistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);    // enable inactivation of histograms

  // Define histogram indices, titles
  std::vector<std::pair<G4String, G4String> > histograms =
    { std::pair<G4String, G4String>("0", "dummy"),
      std::pair<G4String, G4String>("1", "hits per event"),
      std::pair<G4String, G4String>("2", "hits per event above threshold"),
      std::pair<G4String, G4String>("3", "scintillation photons per event"),
      std::pair<G4String, G4String>("4", "Cerenkov photons per event"),
      std::pair<G4String, G4String>("5", "absorbed photons per event"),
      std::pair<G4String, G4String>
                      ("6", "photons absorbed at boundary per event"),
      std::pair<G4String, G4String>
                      ("7", "energy deposition in scintillator per event"),
     };

  // Default values (to be reset via /analysis/h1/set command)
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;

  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (auto histogram : histograms) {
    G4int ih = analysisManager->
      CreateH1("h" + histogram.first, histogram.second, nbins, vmin, vmax);
    analysisManager->SetH1Activation(ih, false);
  }
}