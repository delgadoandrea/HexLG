#ifndef HexLGActionInitialization_h
#define HexLGActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class HexLGDetectorConstruction;

/// Action initialization class.
///

class HexLGActionInitialization : public G4VUserActionInitialization
{
  public:
    HexLGActionInitialization(HexLGDetectorConstruction*);
    virtual ~HexLGActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:

    HexLGDetectorConstruction* fDetector;
};

#endif