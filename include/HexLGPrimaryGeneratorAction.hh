#ifndef HexLGPrimaryGeneratorAction_h
#define HexLGPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"

class G4ParticleGun;
class G4Event;

class HexLGPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  public:

    HexLGPrimaryGeneratorAction();
    virtual ~HexLGPrimaryGeneratorAction();
 
  public:

    virtual void GeneratePrimaries(G4Event* anEvent);

  private:

    G4ParticleGun* fParticleGun;
};

#endif