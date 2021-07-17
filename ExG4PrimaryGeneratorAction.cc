#include "ExG4PrimaryGeneratorAction.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"

#include "G4DynamicParticle.hh"
#include "G4PhysicalConstants.hh"
//#include "G4SystemOfUnits.hh"
#include "G4DecayProducts.hh"
#include "G4LorentzVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4PrimaryParticle.hh"
#include "Randomize.hh"
using namespace std;
ExG4PrimaryGeneratorAction::ExG4PrimaryGeneratorAction(G4double E_recoil)
  :  G4VUserPrimaryGeneratorAction(),
     fParticleGun(0)
{
  m_Erecoil = E_recoil;

  // The basic units are :
  //		millimeter              (millimeter)
  // 		nanosecond              (nanosecond)
  // 		Mega electron Volt      (MeV)
  // 		positron charge         (eplus)
  // 		degree Kelvin           (kelvin)
  //      the amount of substance (mole)
  //      luminous intensity      (candela)
  // 		radian                  (radian)
  //      steradian               (steradian)
  G4int nofParticles = 1;
  fParticleGun = new G4ParticleGun(nofParticles);
  xygaus = new TF2("xygaus","xygaus",-15,15,-15,15);// predefined 2D Gaussian function  // 2D Gaussian beam spot
  xygaus->SetParameters(1,0,3,0,3); // amplitude, mean_x, sigma_x, mean_y, sigma_y  in units of mm. // 2D Gaussian beam spot
  xygaus->SetNpx(200);  // 2D Gaussian beam spot
  xygaus->SetNpy(200);  // 2D Gaussian beam spot
  Rmax = 10;  // 2D Uniform beam spot // in units of mm. G4ThreeVector(mm)
  //pFile=new TFile("/mnt/hgfs/HPGe/S27_pz.root","read");
  //pFile=new TFile("/mnt/hgfs/HPGe/P26_pz.root","read");
  //pFile=new TFile("/mnt/hgfs/HPGe/Si25_pz.root","read");
  //pFile=new TFile("/mnt/hgfs/HPGe/Al22_pz.root","read");
  //pFile=new TFile("/mnt/hgfs/HPGe/S27simulate.root","read");
  //fout = fopen ("out.txt", "w");
  
  numpeaks=1;//23 or 53 for 29Na, 46 or 88 for 30Na. with Doppler, 62 for 29Na, 1 for test
  branch_lit_tot=0;
  //fin=fopen ("/mnt/hgfs/HPGe/Gamma30Naprecursor.dat","r");
  wheretorun=3;
  // 	if(wheretorun==1)//fishtank
  // 	{
  // 		ifstream fin("/user/sunli/HPGe/Gamma29Nadoppler.dat",ios::in);//fishtank下fscanf %lf报错
  // 		for(int ii=0;ii<numpeaks;ii++)//fishtank
  // 		{
  // 			fin>>Eg_lit[ii]>>branch_lit[ii]>>En_lit[ii]>>Halflife_lit[ii];//Ecm keV; 1 ps = 0.001
  // 		}//fishtank
  // 	}
  // 	if(wheretorun==2)//VMware
  // 	{
  // 		FILE *fin=fopen ("/mnt/hgfs/HPGe/Gamma29Nadoppler.dat","r");//VMware下ifstream报错
  // 		for(int ii=0;ii<numpeaks;ii++)//VMware
  // 	 	{
  // 	 		fscanf(fin, "%lf", &Eg_lit[ii]);//keV
  // 	 		fscanf(fin, "%lf", &branch_lit[ii]);
  // 	 		fscanf(fin, "%lf", &En_lit[ii]);//Ecm keV
  // 	 		fscanf(fin, "%lf", &Halflife_lit[ii]);//1 ps = 0.001
  // 		}//VMware
  // 	}
  // 	if(wheretorun==3)//VMware test
  // 	{
  // 		FILE *fin=fopen ("/mnt/hgfs/HPGe/Onetest.dat","r");//VMware下ifstream报错
  // 		for(int ii=0;ii<numpeaks;ii++)//VMware
  // 		{
  // 			fscanf(fin, "%lf", &Eg_lit[ii]);//keV
  // 			fscanf(fin, "%lf", &branch_lit[ii]);
  // 			fscanf(fin, "%lf", &En_lit[ii]);//Ecm keV
  // 			fscanf(fin, "%lf", &Halflife_lit[ii]);//1 ps = 0.001
  // 		}//VMware
  // 	}
  // 	for(int ii=0;ii<numpeaks;ii++)
  // 	{
  // 		branch_lit_tot+=branch_lit[ii];
  // 		branch_lit_integ[ii]=branch_lit_tot;
  // 	}
  // 	for(int ii=0;ii<numpeaks+1;ii++)
  // 	{
  // 		G4cout<<"Eg=	"<<Eg_lit[ii]<<"	keV	br=	"<<branch_lit[ii]<<"	integ=	"<<branch_lit_integ[ii]<<"	En=	"<<En_lit[ii]<<"	keV	T=	"<<Halflife_lit[ii]<<"	ns"<<G4endl;
  // 	}
  // 	G4cout<<"brtot=	"<<branch_lit_tot<<G4endl;
  //std::ofstream outfile(filename,std::ios::out);//定义输出文件流对象outfile，以输出方式打开磁盘文件, formerly non-existent file can be created automatically
  // 	px_impl = new TH1F("px_impl","px_impl", 50,-25,25);//unit mm, this statement cannot be eliminated, the new TH1F cannot be named the same as the TH1F in the input root
  // 	py_impl = new TH1F("py_impl","py_impl", 50,-25,25);//unit mm, this statement cannot be eliminated, the new TH1F cannot be named the same as the TH1F in the input root
  // 	pz_impl = new TH1D("pz_impl","pz_impl", 100,0,100);//unit um, this statement cannot be eliminated, the new TH1F cannot be named the same as the TH1F in the input root
  G4cout<<"1$ before run, by run, ExG4PrimaryGeneratorAction::ExG4PrimaryGeneratorAction()"<<G4endl;
}

ExG4PrimaryGeneratorAction::~ExG4PrimaryGeneratorAction()
{
  G4cout<<"8$ after run, by run, ExG4PrimaryGeneratorAction::~ExG4PrimaryGeneratorAction()"<<G4endl;
  //pFile->Close();
  //fclose(fout);
  //	fclose(fin);//VMware
  delete fParticleGun;
}

void ExG4PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)
{
  Z_r=2,A_r=4;//recoil (daughter)
  Z_p=2,A_p=4;//particle
  excitE=0.*CLHEP::keV;
  ioncharge = 0.*CLHEP::eplus;
  //	excitE=CLHEP::RandFlat::shoot(100000,100000);
	
  tau=0;
  //  G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
  G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");

  
  //single particle isotropic emission
  costheta_n1=CLHEP::RandFlat::shoot(-1,1);//isotropy
  phi_n1=CLHEP::RandFlat::shoot(0.,2.*3.14159);//isotropy
  //G4cout<<"------------ phi="<<phi<<' '<<"costheta="<<costheta<<G4endl;
  sintheta_n1=sqrt(1.0-costheta_n1*costheta_n1);//isotropy
  dirx=sintheta_n1*cos(phi_n1);//isotropy
  diry=sintheta_n1*sin(phi_n1);//isotropy
  dirz=costheta_n1;//isotropy
  
  xygaus->GetRandom2(x0,y0); // 2D Gaussian beam spot  // Return two random numbers to x0 and y0 following this function shape.
  r_beam = sqrt(gRandom->Uniform(0,1))*Rmax;  // 2D Uniform beam spot
  theta_beam = gRandom->Uniform(0,2.*3.14159);  // 2D Uniform beam spot
  x0= r_beam*cos(theta_beam);  // 2D Uniform beam spot
  y0 = r_beam*sin(theta_beam);  // 2D Uniform beam spot
  z0=0;
  //G4cout<<"++++++++++++  x0="<<x0/CLHEP::mm<<"  y0="<<y0/CLHEP::mm<<"  z0="<<z0/CLHEP::mm<<G4endl;
  //position=G4ThreeVector(x0*CLHEP::mm,y0*CLHEP::mm,z0*CLHEP::mm);// 2D beam spot
  position=G4ThreeVector(0.*CLHEP::mm,0.*CLHEP::mm,0.*CLHEP::mm);// point source, usually for check, validation and test
  momentumDirection = G4ThreeVector(dirx,diry,dirz);//isotropy
  //momentumDirection = G4ThreeVector(0,0,-1); ///unidirectional toward Z+ axis, usually for check, validation and test
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(m_Erecoil);
  fParticleGun->SetParticlePosition(position);
  fParticleGun->SetParticleMomentumDirection(momentumDirection);
  fParticleGun->SetParticleCharge(ioncharge);
  //fParticleGun->SetParticleTime(1000*CLHEP::ns);//meaningless, the generation time of particle
  fParticleGun->GeneratePrimaryVertex(anEvent);
}
