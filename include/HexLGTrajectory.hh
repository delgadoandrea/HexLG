#ifndef HexLGTrajectory_h
#define HexLGTrajectory_h 1

#include "G4Trajectory.hh"
#include "G4Allocator.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4ParticleDefinition.hh"
#include "G4TrajectoryPoint.hh"
#include "G4Track.hh"
#include "G4Step.hh"

class G4Polyline;                   // Forward declaration.

class HexLGTrajectory : public G4Trajectory
{
  public:

    HexLGTrajectory();
    HexLGTrajectory(const G4Track* aTrack);
    HexLGTrajectory(HexLGTrajectory &);
    virtual ~HexLGTrajectory();
 
    virtual void DrawTrajectory() const;
 
    inline void* operator new(size_t);
    inline void  operator delete(void*);

    void SetDrawTrajectory(G4bool b){fDrawit=b;}
    void WLS(){fWls=true;}
    void SetForceDrawTrajectory(G4bool b){fForceDraw=b;}
    void SetForceNoDrawTrajectory(G4bool b){fForceNoDraw=b;}

  private:

    G4bool fWls;
    G4bool fDrawit;
    G4bool fForceNoDraw;
    G4bool fForceDraw;
    G4ParticleDefinition* fParticleDefinition;
};

extern G4ThreadLocal G4Allocator<HexLGTrajectory>* HexLGTrajectoryAllocator;

inline void* HexLGTrajectory::operator new(size_t)
{
  if(!HexLGTrajectoryAllocator)
      HexLGTrajectoryAllocator = new G4Allocator<HexLGTrajectory>;
  return (void*)HexLGTrajectoryAllocator->MallocSingle();
}

inline void HexLGTrajectory::operator delete(void* aTrajectory)
{
  HexLGTrajectoryAllocator->FreeSingle((HexLGTrajectory*)aTrajectory);
}

#endif