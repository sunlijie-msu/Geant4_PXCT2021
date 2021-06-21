#ifndef ExG4PrimaryGeneratorAction_hh
#define ExG4PrimaryGeneratorAction_hh
#include <iostream>
#include <fstream>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include <math.h>
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"
#include "CLHEP/Units/SystemOfUnits.h"
#include "TH1.h"
#include "TH2.h"
#include "TFile.h"
#include "TF1.h"
#include "TF2.h"
#include "TRandom.h"
#include "TRandom3.h"

class G4ParticleGun;
class G4Event;


class ExG4PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  ExG4PrimaryGeneratorAction(
    //const G4String& particleName = "geantino",
    //G4double Erecoil = 1.*CLHEP::MeV,
    //G4ThreeVector position= G4ThreeVector(0,0,-40.*CLHEP::cm),
    //G4ThreeVector momentumDirection = G4ThreeVector(0,0,1)
	);
  ~ExG4PrimaryGeneratorAction();

  virtual void GeneratePrimaries(G4Event*);

private:
  G4ParticleGun* fParticleGun;
//	TFile *pFile;
	//FILE *fout;
	int wheretorun;
// 	TH1F *px_impl;
// 	TH1F *py_impl;
//     TH1D *pz_impl;// TH1F *pz = new TH1F("pz","pz",4000,0,4000); The whole sentence cannot be written in .hh
	TF2 *xygaus; // 2D Gaussian beam spot
	double theta_beam, r_beam, Rmax; // 2D Uniform beam spot
	double x0,y0,z0; // 2D beam spot	
	double Eg_lit[100];
	double branch_lit[100];
	double En_lit[100],En1,En2;
	double Halflife_lit[100];
	double branch_lit_integ[100];
	double branch_lit_tot;
	int numpeaks;

	G4double ioncharge;
	G4double lifetime;
	G4double branch_integ;
	G4double Erecoil;
	G4double tau;
	G4int Z_r,A_r,Z_p,A_p;
	G4double excitE;
	G4double resolution;
	G4double costheta_n1,costheta_n2,costheta_recoil;
	G4double phi_n1,phi_n2,phi_recoil;
	G4double sintheta_n1,sintheta_n2,sintheta_recoil;
	G4double dirx;
	G4double diry;
	G4double dirz;
	G4ThreeVector position;
	G4ThreeVector momentumDirection;


};

#endif
