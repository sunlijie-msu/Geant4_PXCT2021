#ifndef ExG4RunAction_h
#define ExG4RunAction_h

#include "CLHEP/Units/SystemOfUnits.h"
#include "G4UserRunAction.hh"
#include "globals.hh"
//#include "TH1F.h"
//#include "TFile.h"
class G4Run;

class ExG4RunAction : public G4UserRunAction
{
public:
  ExG4RunAction();
  virtual ~ExG4RunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);
 
};

#endif
