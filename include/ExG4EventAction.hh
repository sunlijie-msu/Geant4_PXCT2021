#ifndef ExG4EventAction_h
#define ExG4EventAction_h

#include "CLHEP/Units/SystemOfUnits.h"
#include "G4UserEventAction.hh"
#include "globals.hh"
// #include "TH1F.h"
// #include "TFile.h"
#include <iostream>
#include <fstream>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"

class ExG4EventAction : public G4UserEventAction
{
public:
  ExG4EventAction();
  virtual ~ExG4EventAction();

  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);
  
private:
	G4int fDHC1ID;
	G4int fDHC2ID;
	G4int fDHC3ID;
	G4int fDHC4ID;
	//TFile *eFile;
    //TH1F *histo;
};

#endif
