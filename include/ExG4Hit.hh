#ifndef ExG4Hit_h
#define ExG4Hit_h

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4Attdef;
class G4AttValue;

//DSSD1 Hit
//
//Records:
// - the strip ID
// - the deposited energy
// ======================================

class ExG4Hit : public G4VHit//G4VHit class，用于保存每一次hit的信息
{
public:
  ExG4Hit(G4ThreeVector pos, G4double de,G4double tof);
  virtual ~ExG4Hit() {}

  inline void *operator new(size_t);
  inline void operator delete(void*aHit);

  void Print();
  G4ThreeVector GetPos() const { return fPos; }
  G4double GetE() const { return fE;}
  G4double GetTof() const { return fTof;}

private:
  G4ThreeVector fPos;
  G4double fE;
  G4double fTof;
};

typedef G4THitsCollection<ExG4Hit> ExG4HitsCollection;//把所有的hit都保存起来，保存G4VHit的容器，即HitsCollection

extern G4ThreadLocal G4Allocator<ExG4Hit>* ExG4HitAllocator;

inline void* ExG4Hit::operator new(size_t)
{
  if (!ExG4HitAllocator)
     ExG4HitAllocator = new G4Allocator<ExG4Hit>;
  return (void*)ExG4HitAllocator->MallocSingle();
}

inline void ExG4Hit::operator delete(void*aHit)
{
  ExG4HitAllocator->FreeSingle((ExG4Hit*)aHit);
}
#endif
