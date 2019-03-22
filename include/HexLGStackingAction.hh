#ifndef HexLGStackingAction_H
#define HexLGStackingAction_H 1

#include "globals.hh"
#include "G4UserStackingAction.hh"

class HexLGEventAction;

class HexLGStackingAction : public G4UserStackingAction
{
  public:

    HexLGStackingAction(HexLGEventAction*);
    virtual ~HexLGStackingAction();
 
    virtual G4ClassificationOfNewTrack ClassifyNewTrack(const G4Track* aTrack);
    virtual void NewStage();
    virtual void PrepareNewEvent();
 
  private:
    HexLGEventAction* fEventAction;
};

#endif