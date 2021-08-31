#ifndef ExG4EventAction_h
#define ExG4EventAction_h
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <map>
#include <TROOT.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TCutG.h>
#include <TChain.h>
#include <TMinuit.h>
#include "TChain.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TEllipse.h"
#include "TString.h"
#include "TGraph.h"
#include "TSpectrum.h"
#include "TVirtualFitter.h"
#include "TRandom.h"
#include <TRandom3.h>
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TF1.h"
#include "TMath.h"
#include "TPaveText.h"
#include "TPad.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "TLegend.h"
#include "TPaletteAxis.h"
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "G4UserEventAction.hh"
#include "globals.hh"

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
	G4double emg_sig,emg_sigp0,emg_sigp1,emg_tau,emg_taup0,emg_taup1;
	G4double ih=-1,jh=-1;  //which strip is hit
	G4double eDep;
	G4double tof=-999;
	G4int totalEmHit = 0;
	G4double totalEmE = 0.;
	G4double px[100],py[100],pz[100],dx[100],length=0;
	G4double t[100],dt[100],velocity=0;
	// length is the sum of all the dx
	// velocity is dx/dt
	// dx is the distance between two step points
	// dt is the time difference between two step points
	// t is the time stamp of each step point
	G4int ring1_hit, ring2_hit, ring3_hit;
	//TFile *eFile;
	//TH1F *histo;
};

#endif
