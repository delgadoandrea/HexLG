#ifndef HexLGTrackingAction_h
#define HexLGTrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

class HexLGTrackingAction : public G4UserTrackingAction {

  public:

    HexLGTrackingAction();
    virtual ~HexLGTrackingAction() {};

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);

  private:

};

#endif