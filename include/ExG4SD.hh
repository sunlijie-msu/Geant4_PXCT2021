#ifndef ExG4SD_h
#define ExG4SD_h

#include "G4VSensitiveDetector.hh"
#include "ExG4Hit.hh"

class ExG4SD : public G4VSensitiveDetector
{
public:
  ExG4SD(G4String name);
  virtual ~ExG4SD();

  virtual void Initialize(G4HCofThisEvent *HCE);//G4HCofThisEvent÷∏’Î÷∏œÚHitsCollection
  virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory*ROhist);

private:
  ExG4HitsCollection* fHitsCollection;
  G4int fHCID;
};

#endif
