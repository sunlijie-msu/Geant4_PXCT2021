﻿#include "ExG4PrimaryGeneratorAction.hh"

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


G4double rand_energy()
{
	float x = CLHEP::RandFlat::shoot(0.0,1.0);
	//    cout << x << "\n";
	if(x<0.5)return 8.0*CLHEP::keV;
	else return 8.6*CLHEP::keV;
}

ExG4PrimaryGeneratorAction::ExG4PrimaryGeneratorAction()
	:  G4VUserPrimaryGeneratorAction(),
	fParticleGun(0)
{
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
//	To output the data on the unit you wish you must divide the data by the corresponding unit.
	// /CLHEP::keV is equivalent to *1000
	// *CLHEP::keV is equivalent to /1000

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
	//G4cout<<"(1)$ before event, by event, ExG4PrimaryGeneratorAction::GeneratePrimaries(G4Event *anEvent)"<<G4endl;

	//px_impl=(TH1F*)pFile->Get("himpl40px");//Get("hx2");//from implantation root for DSSD2 modify
	//py_impl=(TH1F*)pFile->Get("himpl40py");//Get("hy2");//from implantation root for DSSD2 modify
	//pz_impl=(TH1D*)pFile->Get("himpl40pz");//Get("hz2");//from implantation root for DSSD2 modify
	//	px_impl=(TH1F*)pFile->Get("himpl304px");//Get("hx2");//from implantation root for DSSD3 modify
	//	py_impl=(TH1F*)pFile->Get("himpl304py");//Get("hy2");//from implantation root for DSSD3 modify
	//	pz_impl=(TH1D*)pFile->Get("himpl304pz");//Get("hz2");//from implantation root for DSSD3 modify
	//	x0=px_impl->GetRandom()*CLHEP::mm;//from implantation root for both DSSD2\3
	//	y0=py_impl->GetRandom()*CLHEP::mm;//from implantation root for both DSSD2\3
	//	z0=pz_impl->GetRandom()*0.001*CLHEP::mm;//from implantation root for both DSSD2\3
	//G4cout<<"++++++++++++  x0="<<x0<<"  y0="<<y0<<"  z0="<<z0/CLHEP::mm<<G4endl;
	//	for(;x0>49.5/2||x0<-49.5/2;){x0=px_impl->GetRandom()*CLHEP::mm;}//from implantation root for both DSSD2\3. To ensure an appropriate x0.
	//	for(;y0<-49.5/2||y0>49.5/2;){y0=py_impl->GetRandom()*CLHEP::mm;}//from implantation root for both DSSD2\3. To ensure an appropriate y0.
	//if(x0>49.5/2||x0<-49.5/2||y0<-49.5/2||y0>49.5/2)fprintf(fp, "%f%s%f\n", x0," ",y0); 
	//for(;z0>0.04;){z0=pz_impl->GetRandom()*0.001*CLHEP::mm;};To ensure an appropriate DSSD2 z0.
	//z0=0-0.040/2.0+z0;//from implantation root for DSSD2 modify.
	//	z0=19-0.304/2.0+z0;//from implantation root for DSSD3 modify
	//x0=G4UniformRand();
	//x0=0; y0=0; z0=0*CLHEP::mm;//fixed point
	//G4cout<<pz300->GetMean()<<G4endl;
	//G4cout<<"yangbiao test : RMS of h1 is "<<((TH1F*)pFile->Get("h1"))->GetMean()<<G4endl;

	Z_r=2,A_r=4;//recoil (daughter)
	Z_p=2,A_p=4;//particle
	ExcitationE=0.*CLHEP::keV;
	ioncharge = 0.*CLHEP::eplus;
//	ExcitationE=CLHEP::RandFlat::shoot(100000,100000);
	Erecoil =10*CLHEP::keV;
	tau=0;
//	branch_integ=CLHEP::RandFlat::shoot(0.0,branch_lit_tot);

// 	if (branch_integ<branch_lit_integ[0])
// 	{
// 		ExcitationE=Eg_lit[0]*CLHEP::keV;
// 		Erecoil=En_lit[0]*A_p/(A_r+A_p)*CLHEP::keV;
// 		tau=1.443*Halflife_lit[0]*CLHEP::ns;
// 	} 	
// 	for(int ii=1;ii<numpeaks;ii++)
// 	{
// 		if(branch_integ>=branch_lit_integ[ii-1]&&branch_integ<branch_lit_integ[ii])
// 		{
// 			ExcitationE=Eg_lit[ii]*CLHEP::keV;
// 			Erecoil=En_lit[ii]*A_p/(A_r+A_p)*CLHEP::keV;
// 			tau=1.443*Halflife_lit[ii]*CLHEP::ns;
// 		}
// 	}
//	tau=0.01*CLHEP::ns;//this is lifetime τ = 1.443*T1/2; 1 ps = 0.001 ns; 10 fs = 0.00001 ns //simplified test
//	Erecoil=200*CLHEP::keV; ExcitationE=2000*CLHEP::keV; tau=0.000010*CLHEP::ns;//simplified test
//	resolution=1.010473*pow(ExcitationE/CLHEP::keV,-0.888665);//resolution becomes better for high energy gamma
//	if(ExcitationE<122*CLHEP::keV)
//	{
//		ExcitationE=G4RandGauss::shoot(ExcitationE,0.001414/2.355*ExcitationE);//sigma resolution, 0.01/2.355 means 1%//slow down the speed by a factor of 10
//		//G4cout<<ExcitationE/CLHEP::keV<<"	"<<resolution<<G4endl;
//	}
//	ExcitationE width should be added in PrimaryGeneratorAction.cc, while detector resolution should be added in EventAction.cc
//	ExcitationE=G4RandGauss::shoot(ExcitationE,resolution/2.355*ExcitationE);//sigma resolution, 0.01/2.355 means 1%//slow down the speed by a factor of 10
//	Erecoil=G4RandGauss::shoot(Erecoil,0.01/2.355*Erecoil);
	//G4ParticleDefinition* particle = G4IonTable::GetIonTable()->GetIon(Z_r,A_r,ExcitationE);
	//G4ParticleDefinition* particle = G4IonTable::GetIonTable()->GetIon(12,26,0); //28Mg: GetIon(12,28,0); 
	//G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("proton");
	G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
	//G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("e+");
	//particle->SetProperTime(0.0);
//	particle->SetPDGStable(false);
//	particle->SetPDGLifeTime(tau);//this is lifetime τ = 1.443*T1/2
	//	G4cout<<"------- Er="<<Erecoil/CLHEP::keV<<" keV"<<"	branch_integ="<<branch_integ<<"	Eg=	"<<ExcitationE/CLHEP::keV<<"	T=	"<<0.69315*particle->GetPDGLifeTime()/CLHEP::ns<<"	ns"<<G4endl;
	//G4cout<<"	life=	"<<tau/CLHEP::ns<<"	ns	"<<particle->GetPDGLifeTime()/CLHEP::ns<<"	ns"<<G4endl;
	//G4DynamicParticle* particle = new G4DynamicParticle();
	
//  	costheta_p1=CLHEP::RandFlat::shoot(-1,1);//isotropic particle
//  	phi_p1=CLHEP::RandFlat::shoot(0.,2.*3.14159);//isotropic particle
//  	costheta_recoil=-costheta_p1;//isotropic particle
//  	phi_recoil=phi_p1+3.14159;//isotropic particle

//	costheta_recoil=CLHEP::RandFlat::shoot(-1,1);//isotropic recoil
//	phi_recoil=CLHEP::RandFlat::shoot(0.,2.*3.14159);//isotropic recoil
	//G4cout<<"------------ phi="<<phi<<' '<<"costheta="<<costheta<<G4endl;

// 	sintheta_recoil=sqrt(1.0-costheta_recoil*costheta_recoil);//isotropy
// 	dirx=sintheta_recoil*cos(phi_recoil);//isotropy
// 	diry=sintheta_recoil*sin(phi_recoil);//isotropy
// 	dirz=costheta_recoil;//isotropy

//	costheta_n2=CLHEP::RandFlat::shoot(-1,1);//isotropic particle
//	Erecoil=Erecoil*costheta_n2*costheta_n2;//random deg
	//Erecoil=Erecoil;//0 deg
	//Erecoil=0;//180 deg

	//G4AnalysisManager* analysisManagerin = G4AnalysisManager::Instance();
	//analysisManagerin->OpenFile("ExG4old");
	//G4cout<<"lalala "<<analysisManagerin->GetH1(1)->mean()<<G4endl;
	//position=G4ThreeVector(0.*CLHEP::mm,0.*CLHEP::mm,-26.7/2.0+5.86/1000.*CLHEP::mm);
	

	//single particle isotropic emission
	costheta_p1=CLHEP::RandFlat::shoot(-1,1);//isotropy
	phi_p1=CLHEP::RandFlat::shoot(0.,2.*3.14159);//isotropy
	//G4cout<<"------------ phi="<<phi<<' '<<"costheta="<<costheta<<G4endl;
	sintheta_p1=sqrt(1.0-costheta_p1*costheta_p1);//isotropy
	dirx=sintheta_p1*cos(phi_p1);//isotropy
	diry=sintheta_p1*sin(phi_p1);//isotropy
	dirz=costheta_p1;//isotropy

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
	//momentumDirection = G4ThreeVector(0,0,-1);//(0,0,+1) unidirectional toward Z+ axis, usually for check, validation and test
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleEnergy(rand_energy());
	fParticleGun->SetParticlePosition(position);
	fParticleGun->SetParticleMomentumDirection(momentumDirection);
	fParticleGun->SetParticleCharge(ioncharge);
	//fParticleGun->SetParticleTime(1000*CLHEP::ns);//meaningless, the generation time of particle
	fParticleGun->GeneratePrimaryVertex(anEvent);









	// *** for the second particle emitted in the same event ***
	particle = G4ParticleTable::GetParticleTable()->FindParticle("proton");
	Erecoil = 10000*CLHEP::keV;
	//Erecoil =G4RandGauss::shoot(2.2,0.5)*CLHEP::MeV;

	//single particle isotropic emission
	costheta_p1=CLHEP::RandFlat::shoot(-1,1);//isotropy
	phi_p1=CLHEP::RandFlat::shoot(0.,2.*3.14159);//isotropy
	//G4cout<<"------------ phi="<<phi<<' '<<"costheta="<<costheta<<G4endl;
	sintheta_p1=sqrt(1.0-costheta_p1*costheta_p1);//isotropy
	dirx=sintheta_p1*cos(phi_p1);//isotropy
	diry=sintheta_p1*sin(phi_p1);//isotropy
	dirz=costheta_p1;//isotropy

	//position=G4ThreeVector(x0*CLHEP::mm,y0*CLHEP::mm,z0*CLHEP::mm);// 2D beam spot
	position=G4ThreeVector(0.*CLHEP::mm,0.*CLHEP::mm,0.*CLHEP::mm);// point source, usually for check, validation and test
	momentumDirection = G4ThreeVector(dirx,diry,dirz);//isotropy
	//momentumDirection = G4ThreeVector(0,0,-1);//(0,0,+1) unidirectional toward Z+ axis, usually for check, validation and test
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleEnergy(Erecoil);
	fParticleGun->SetParticlePosition(position);
	fParticleGun->SetParticleMomentumDirection(momentumDirection);
	fParticleGun->SetParticleCharge(ioncharge);
	fParticleGun->GeneratePrimaryVertex(anEvent); // if you do not need the second particle in the same event, comment this statement out











	// *** for the third particle emitted in the same event ***
	particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
	Erecoil =200*CLHEP::keV;

	//single particle isotropic emission
	costheta_p1=CLHEP::RandFlat::shoot(-1,1);//isotropy
	phi_p1=CLHEP::RandFlat::shoot(0.,2.*3.14159);//isotropy
	//G4cout<<"------------ phi="<<phi<<' '<<"costheta="<<costheta<<G4endl;
	sintheta_p1=sqrt(1.0-costheta_p1*costheta_p1);//isotropy
	dirx=sintheta_p1*cos(phi_p1);//isotropy
	diry=sintheta_p1*sin(phi_p1);//isotropy
	dirz=costheta_p1;//isotropy

	//position=G4ThreeVector(x0*CLHEP::mm,y0*CLHEP::mm,z0*CLHEP::mm);// 2D beam spot
	position=G4ThreeVector(0.*CLHEP::mm,0.*CLHEP::mm,0.*CLHEP::mm);// point source, usually for check, validation and test
	momentumDirection = G4ThreeVector(dirx,diry,dirz);//isotropy
	//momentumDirection = G4ThreeVector(0,0,-1);//(0,0,+1) unidirectional toward Z+ axis, usually for check, validation and test
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleEnergy(Erecoil);
	fParticleGun->SetParticlePosition(position);
	fParticleGun->SetParticleMomentumDirection(momentumDirection);
	fParticleGun->SetParticleCharge(ioncharge);
	fParticleGun->GeneratePrimaryVertex(anEvent); // if you do not need the third particle in the same event, comment this statement out





	




	// *** for the fourth particle emitted in the same event ***
	particle = G4ParticleTable::GetParticleTable()->FindParticle("e+");
	//Erecoil =4000*CLHEP::keV;
	Erecoil = G4RandGauss::shoot(2,1)*CLHEP::MeV;

	//single particle isotropic emission
	costheta_p1=CLHEP::RandFlat::shoot(-1,1);//isotropy
	phi_p1=CLHEP::RandFlat::shoot(0.,2.*3.14159);//isotropy
	//G4cout<<"------------ phi="<<phi<<' '<<"costheta="<<costheta<<G4endl;
	sintheta_p1=sqrt(1.0-costheta_p1*costheta_p1);//isotropy
	dirx=sintheta_p1*cos(phi_p1);//isotropy
	diry=sintheta_p1*sin(phi_p1);//isotropy
	dirz=costheta_p1;//isotropy

	//position=G4ThreeVector(x0*CLHEP::mm,y0*CLHEP::mm,z0*CLHEP::mm);// 2D beam spot
	position=G4ThreeVector(0.*CLHEP::mm,0.*CLHEP::mm,0.*CLHEP::mm);// point source, usually for check, validation and test
	momentumDirection = G4ThreeVector(dirx,diry,dirz);//isotropy
	//momentumDirection = G4ThreeVector(0,0,-1);//(0,0,+1) unidirectional toward Z+ axis, usually for check, validation and test
	fParticleGun->SetParticleDefinition(particle);
	//fParticleGun->SetParticleEnergy(Erecoil);
	fParticleGun->SetParticlePosition(position);
	fParticleGun->SetParticleMomentumDirection(momentumDirection);
	fParticleGun->SetParticleCharge(ioncharge);
	//fParticleGun->GeneratePrimaryVertex(anEvent); // if you do not need the fourth particle in the same event, comment this statement out

}

