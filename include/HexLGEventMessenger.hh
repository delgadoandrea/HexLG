#ifndef HexLGEventMessenger_h
#define HexLGEventMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class HexLGEventAction;
class G4UIcmdWithAnInteger;
class G4UIcmdWithABool;

class HexLGEventMessenger: public G4UImessenger
{
  public:

    HexLGEventMessenger(HexLGEventAction*);
    virtual ~HexLGEventMessenger();
 
    virtual void SetNewValue(G4UIcommand*, G4String);
 
  private:

    HexLGEventAction*      fHexLGEvent;
    G4UIcmdWithAnInteger*  fVerboseCmd;
    G4UIcmdWithAnInteger*  fPmtThresholdCmd;
    G4UIcmdWithABool*      fForceDrawPhotonsCmd;
    G4UIcmdWithABool*      fForceDrawNoPhotonsCmd;
};

#endif