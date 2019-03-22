#ifndef HexLGScintHit_h
#define HexLGScintHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"

#include "tls.hh"

class HexLGScintHit : public G4VHit
{
  public:
 
    HexLGScintHit();
    HexLGScintHit(G4VPhysicalVolume* pVol);
    virtual ~HexLGScintHit();
    HexLGScintHit(const HexLGScintHit &right);
    const HexLGScintHit& operator=(const HexLGScintHit &right);
    G4int operator==(const HexLGScintHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);
 
    virtual void Draw();
    virtual void Print();

    inline void SetEdep(G4double de) { fEdep = de; }
    inline void AddEdep(G4double de) { fEdep += de; }
    inline G4double GetEdep() { return fEdep; }

    inline void SetPos(G4ThreeVector xyz) { fPos = xyz; }
    inline G4ThreeVector GetPos() { return fPos; }

    inline const G4VPhysicalVolume * GetPhysV() { return fPhysVol; }

  private:
    G4double fEdep;
    G4ThreeVector fPos;
    const G4VPhysicalVolume* fPhysVol;

};

typedef G4THitsCollection<HexLGScintHit> HexLGScintHitsCollection;

extern G4ThreadLocal G4Allocator<HexLGScintHit>* HexLGScintHitAllocator;

inline void* HexLGScintHit::operator new(size_t)
{
  if(!HexLGScintHitAllocator)
      HexLGScintHitAllocator = new G4Allocator<HexLGScintHit>;
  return (void *) HexLGScintHitAllocator->MallocSingle();
}

inline void HexLGScintHit::operator delete(void *aHit)
{
  HexLGScintHitAllocator->FreeSingle((HexLGScintHit*) aHit);
}

#endif