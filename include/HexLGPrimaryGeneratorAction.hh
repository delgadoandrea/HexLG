#ifndef HexLGPrimaryGeneratorAction_h
#define HexLGPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"

class G4ParticleGun;
class G4Event;
class HexLGPrimaryGeneratorMessenger;
class HexLGDetectorConstruction;

class HexLGPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:

    HexLGPrimaryGeneratorAction(HexLGDetectorConstruction*);
    virtual ~HexLGPrimaryGeneratorAction();
 
  public:

    virtual void GeneratePrimaries(G4Event* anEvent);

    void SetOptPhotonPolar();
    void SetOptPhotonPolar(G4double);


  private:

    G4ParticleGun* fParticleGun;
    HexLGPrimaryGeneratorMessenger* fGunMessenger;
    HexLGDetectorConstruction* fDetector;

};

#endif