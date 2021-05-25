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
ExG4PrimaryGeneratorAction::ExG4PrimaryGeneratorAction()
	:  G4VUserPrimaryGeneratorAction(),
	fParticleGun(0)
{
	G4int nofParticles = 1;
	fParticleGun = new G4ParticleGun(nofParticles);
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
	excitE=0.*CLHEP::keV;
	ioncharge = 0.*CLHEP::eplus;
//	excitE=CLHEP::RandFlat::shoot(100000,100000);
	Erecoil = 30000*CLHEP::keV;
	tau=0;
//	branch_integ=CLHEP::RandFlat::shoot(0.0,branch_lit_tot);

// 	if (branch_integ<branch_lit_integ[0])
// 	{
// 		excitE=Eg_lit[0]*CLHEP::keV;
// 		Erecoil=En_lit[0]*A_p/(A_r+A_p)*CLHEP::keV;
// 		tau=1.443*Halflife_lit[0]*CLHEP::ns;
// 	} 	
// 	for(int ii=1;ii<numpeaks;ii++)
// 	{
// 		if(branch_integ>=branch_lit_integ[ii-1]&&branch_integ<branch_lit_integ[ii])
// 		{
// 			excitE=Eg_lit[ii]*CLHEP::keV;
// 			Erecoil=En_lit[ii]*A_p/(A_r+A_p)*CLHEP::keV;
// 			tau=1.443*Halflife_lit[ii]*CLHEP::ns;
// 		}
// 	}
//	tau=0.01*CLHEP::ns;//this is lifetime τ = 1.443*T1/2; 1 ps = 0.001 ns; 10 fs = 0.00001 ns //simplified test
//	Erecoil=200*CLHEP::keV; excitE=2000*CLHEP::keV; tau=0.000010*CLHEP::ns;//simplified test
//	resolution=1.010473*pow(excitE/CLHEP::keV,-0.888665);//resolution becomes better for high energy gamma
//	if(excitE<122*CLHEP::keV)
//	{
//		excitE=G4RandGauss::shoot(excitE,0.001414/2.355*excitE);//sigma resolution, 0.01/2.355 means 1%//slow down the speed by a factor of 10
//		//G4cout<<excitE/CLHEP::keV<<"	"<<resolution<<G4endl;
//	}
//	else
//	excitE=G4RandGauss::shoot(excitE,resolution/2.355*excitE);//sigma resolution, 0.01/2.355 means 1%//slow down the speed by a factor of 10
//	Erecoil=G4RandGauss::shoot(Erecoil,0.01/2.355*Erecoil);
	//G4ParticleDefinition* particle = G4IonTable::GetIonTable()->GetIon(Z_r,A_r,excitE);
	//G4ParticleDefinition* particle = G4IonTable::GetIonTable()->GetIon(12,26,0); //28Mg: GetIon(12,28,0); 
	G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("alpha");
	//G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("gamma");
	//G4ParticleDefinition* particle = G4ParticleTable::GetParticleTable()->FindParticle("e+");
	//particle->SetProperTime(0.0);
//	particle->SetPDGStable(false);
//	particle->SetPDGLifeTime(tau);//this is lifetime τ = 1.443*T1/2
	//	G4cout<<"------- Er="<<Erecoil/CLHEP::keV<<" keV"<<"	branch_integ="<<branch_integ<<"	Eg=	"<<excitE/CLHEP::keV<<"	T=	"<<0.69315*particle->GetPDGLifeTime()/CLHEP::ns<<"	ns"<<G4endl;
	//G4cout<<"	life=	"<<tau/CLHEP::ns<<"	ns	"<<particle->GetPDGLifeTime()/CLHEP::ns<<"	ns"<<G4endl;
	//G4DynamicParticle* particle = new G4DynamicParticle();
	
//  	costheta_n1=CLHEP::RandFlat::shoot(-1,1);//isotropic particle
//  	phi_n1=CLHEP::RandFlat::shoot(0.,2.*3.14159);//isotropic particle
//  	costheta_recoil=-costheta_n1;//isotropic particle
//  	phi_recoil=phi_n1+3.14159;//isotropic particle

//	costheta_recoil=CLHEP::RandFlat::shoot(-1,1);//isotropic recoil
//	phi_recoil=CLHEP::RandFlat::shoot(0.,2.*3.14159);//isotropic recoil
	//G4cout<<"------------ phi="<<phi<<' '<<"costheta="<<costheta<<G4endl;

// 	sintheta_recoil=sqrt(1.0-costheta_recoil*costheta_recoil);//isotropy
// 	dirx=sintheta_recoil*cos(phi_recoil);//isotropy
// 	diry=sintheta_recoil*sin(phi_recoil);//isotropy
// 	dirz=costheta_recoil;//isotropy

	costheta_n1=CLHEP::RandFlat::shoot(-1,1);//isotropy
	phi_n1=CLHEP::RandFlat::shoot(0.,2.*3.14159);//isotropy
	//G4cout<<"------------ phi="<<phi<<' '<<"costheta="<<costheta<<G4endl;
	sintheta_n1=sqrt(1.0-costheta_n1*costheta_n1);//isotropy
	dirx=sintheta_n1*cos(phi_n1);//isotropy
	diry=sintheta_n1*sin(phi_n1);//isotropy
	dirz=costheta_n1;//isotropy

//	costheta_n2=CLHEP::RandFlat::shoot(-1,1);//isotropic particle
//	Erecoil=Erecoil*costheta_n2*costheta_n2;//random deg
	//Erecoil=Erecoil;//0 deg
	//Erecoil=0;//180 deg

	//G4AnalysisManager* analysisManagerin = G4AnalysisManager::Instance();
	//analysisManagerin->OpenFile("ExG4old");
	//G4cout<<"lalala "<<analysisManagerin->GetH1(1)->mean()<<G4endl;
	//position=G4ThreeVector(0.*CLHEP::mm,0.*CLHEP::mm,-26.7/2.0+5.86/1000.*CLHEP::mm);
	position=G4ThreeVector(0.*CLHEP::mm,0.*CLHEP::mm,0.*CLHEP::mm);//usually for check, validation and test
	//G4ThreeVector position=G4ThreeVector(x0,y0,z0);//real position of source
	//momentumDirection = G4ThreeVector(0,0,+1);//(0,0,+1) towards Z+ axis, usually for check, validation and test
	momentumDirection = G4ThreeVector(dirx,diry,dirz);//isotropy
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->SetParticleEnergy(Erecoil);
	fParticleGun->SetParticlePosition(position);
	fParticleGun->SetParticleMomentumDirection(momentumDirection);
	fParticleGun->SetParticleCharge(ioncharge);
	//fParticleGun->SetParticleTime(1000*CLHEP::ns);//meaningless, the generation time of particle
	fParticleGun->GeneratePrimaryVertex(anEvent);









	// *** for the second particle emitted in the same event ***
	//fParticleGun->GeneratePrimaryVertex(anEvent);// if you do not need the second particle in the same event, annotate this statement
}

