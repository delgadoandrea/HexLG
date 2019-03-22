#ifndef HexLGSteppingMessenger_h
#define HexLGSteppingMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class HexLGSteppingAction;
class G4UIcmdWithABool;

class HexLGSteppingMessenger: public G4UImessenger
{
  public:
    HexLGSteppingMessenger(HexLGSteppingAction*);
    virtual ~HexLGSteppingMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);

  private:

    HexLGSteppingAction*        fStepping;
    G4UIcmdWithABool*  fOneStepPrimariesCmd;
 
};

#endif