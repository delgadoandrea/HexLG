#include "G4UserRunAction.hh"

#ifndef HexLGRunAction_h
#define HexLGRunAction_h 1

class HexLGRun;
class HexLGHistoManager;
class G4Run;

class HexLGRunAction : public G4UserRunAction
{
  public:

    HexLGRunAction();
    virtual ~HexLGRunAction();

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

  private:

    HexLGRun*          fRun;
    HexLGHistoManager* fHistoManager;
};

#endif