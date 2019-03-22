#ifndef HexLGSteppingAction_H
#define HexLGSteppingACtion_H 1

#include "globals.hh"
#include "G4UserSteppingAction.hh"

#include "G4OpBoundaryProcess.hh"

class HexLGEventAction;
class HexLGTrackingAction;
class HexLGSteppingMessenger;

class HexLGSteppingAction : public G4UserSteppingAction
{
  public:

    HexLGSteppingAction(HexLGEventAction*);
    virtual ~HexLGSteppingAction();
    virtual void UserSteppingAction(const G4Step*);

    void SetOneStepPrimaries(G4bool b){fOneStepPrimaries=b;}
    G4bool GetOneStepPrimaries(){return fOneStepPrimaries;}
 
  private:

    G4bool fOneStepPrimaries;
    HexLGSteppingMessenger* fSteppingMessenger;
    HexLGEventAction*       fEventAction;

    G4OpBoundaryProcessStatus fExpectedNextStatus;
};

#endif