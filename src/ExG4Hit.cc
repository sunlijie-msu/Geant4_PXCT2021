#include "ExG4Hit.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"

G4ThreadLocal G4Allocator<ExG4Hit>* ExG4HitAllocator;

ExG4Hit::ExG4Hit(G4ThreeVector pos,G4double de, G4double tof)
: G4VHit(), fPos(pos), fE(de), fTof(tof)
{
	//G4cout<<"(3)[2]$ second in hit, by hit and SD, ExG4Hit::ExG4Hit(G4ThreeVector pos,G4double de, G4double tof)"<<G4endl;
}

void ExG4Hit::Print()
{
}
