#include "HexLGEventAction.hh"
#include "HexLGPMTHit.hh"
#include "HexLGTrajectory.hh"
#include "HexLGRun.hh"
#include "HexLGHistoManager.hh"
#include "HexLGDetectorConstruction.hh"

#include "G4EventManager.hh"
#include "G4SDManager.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4VVisManager.hh"
#include "G4ios.hh"
#include "G4UImanager.hh"
#include "G4SystemOfUnits.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGEventAction::HexLGEventAction(const HexLGDetectorConstruction* det)
  : fDetector(det),fVerbose(0), fPMTThreshold(1),fForcedrawphotons(false),fForcenophotons(false)
{
  fEventMessenger = new HexLGEventMessenger(this);

  fHitCount = 0;
  fAbsorptionCount = 0;
  fBoundaryAbsorptionCount = 0;
  fTotE = 0.0;

  fConvPosSet = false;
  fEdepMax = 0.0;

  fPMTsAboveThreshold = 0;
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HexLGEventAction::~HexLGEventAction(){}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGEventAction::BeginOfEventAction(const G4Event*) {
 
  fHitCount = 0;
  fAbsorptionCount = 0;
  fBoundaryAbsorptionCount = 0;
  fTotE = 0.0;

  fConvPosSet = false;
  fEdepMax = 0.0;

  fPMTsAboveThreshold = 0;

  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  if(fPMTCollID<0)
    fPMTCollID=SDman->GetCollectionID("pmtHitCollection");
}
 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HexLGEventAction::EndOfEventAction(const G4Event* anEvent){

  G4TrajectoryContainer* trajectoryContainer=anEvent->GetTrajectoryContainer();
 
  G4int n_trajectories = 0;
  if (trajectoryContainer) n_trajectories = trajectoryContainer->entries();

  // extract the trajectories and draw them
  if (G4VVisManager::GetConcreteInstance()){
    for (G4int i=0; i<n_trajectories; i++){
      HexLGTrajectory* trj = (HexLGTrajectory*)
        ((*(anEvent->GetTrajectoryContainer()))[i]);
      if(trj->GetParticleName()=="opticalphoton"){
        trj->SetForceDrawTrajectory(fForcedrawphotons);
        trj->SetForceNoDrawTrajectory(fForcenophotons);
      }
      trj->DrawTrajectory();
    }
  }
 
  HexLGPMTHitsCollection* pmtHC = nullptr;
  G4HCofThisEvent* hitsCE = anEvent->GetHCofThisEvent();
 
  //Get the hit collections
  if(hitsCE){
    if(fPMTCollID>=0) {
      pmtHC = (HexLGPMTHitsCollection*)(hitsCE->GetHC(fPMTCollID));
    }
  }
 
  if(pmtHC){
    
    G4int pmts=pmtHC->entries();
    //Gather info from all PMTs
    for(G4int i=0;i<pmts;i++){
      fHitCount += (*pmtHC)[i]->GetPhotonCount();
      //reconPos+=(*pmtHC)[i]->GetPMTPos()*(*pmtHC)[i]->GetPhotonCount();
      if((*pmtHC)[i]->GetPhotonCount()>=fPMTThreshold){
        fPMTsAboveThreshold++;
      }
      else{//wasnt above the threshold, turn it back off
        (*pmtHC)[i]->SetDrawit(false);
      }
    }

    G4AnalysisManager::Instance()->FillH1(1, fHitCount);
    G4AnalysisManager::Instance()->FillH1(2, fPMTsAboveThreshold);

    //G4cout << "Gun x-position, from Event Action: " <<  << G4endl;
    if(fHitCount>0)G4AnalysisManager::Instance()->FillH2(0,fDetector->GetGunPosX(),fDetector->GetGunPosY());

    pmtHC->DrawAllHits();
  }
  G4AnalysisManager::Instance()->FillH1(5, fAbsorptionCount);
  G4AnalysisManager::Instance()->FillH1(6, fBoundaryAbsorptionCount);

  //if(fVerbose>0){
    //End of event output. later to be controlled by a verbose level
    G4cout << "\tNumber of photons that hit PMTs in this event : "
           << fHitCount << G4endl;
    G4cout << "\tNumber of PMTs above threshold("<<fPMTThreshold<<") : "
           << fPMTsAboveThreshold << G4endl;
    G4cout << "\tNumber of photons absorbed (OpAbsorption) in this event : "
           << fAbsorptionCount << G4endl;
    G4cout << "\tNumber of photons absorbed at boundaries (OpBoundary) in "
           << "this event : " << fBoundaryAbsorptionCount << G4endl;
    G4cout << "Unaccounted for photons in this event : "
           << (fPhotonCount_Scint + fPhotonCount_Ceren -
                fAbsorptionCount - fHitCount - fBoundaryAbsorptionCount)
           << G4endl;
  //}

  // update the run statistics
  HexLGRun* run = static_cast<HexLGRun*>(
    G4RunManager::GetRunManager()->GetNonConstCurrentRun());

  run->IncHitCount(fHitCount);
  run->IncEDep(fTotE);
  run->IncAbsorption(fAbsorptionCount);
  run->IncBoundaryAbsorption(fBoundaryAbsorptionCount);
  run->IncHitsAboveThreshold(fPMTsAboveThreshold);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......