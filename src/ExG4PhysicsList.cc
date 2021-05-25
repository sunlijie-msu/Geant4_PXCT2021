#include "ExG4PhysicsList.hh"
#include "G4DecayPhysics.hh"
#include "G4RadioactiveDecayPhysics.hh"
#include "G4RadioactiveDecay.hh"
#include "G4EmStandardPhysics.hh" //phote-electric,compton,conversion to e+e- pairs
// #include "G4EmStandardPhysicsGS.hh"
// #include "G4EmStandardPhysics_option1.hh"
// #include "G4EmStandardPhysics_option2.hh"
// #include "G4EmStandardPhysics_option3.hh"
// #include "G4EmStandardPhysics_option4.hh"
// #include "G4EmStandardPhysicsSS.hh"
// #include "G4EmStandardPhysicsWVI.hh"
#include "PhysListEmStandard.hh"

#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "PhysListEmStandard.hh"
#include "G4ParticleDefinition.hh"
#include "G4ProcessManager.hh"
#include "G4PhysicsListHelper.hh"

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"
#include "G4RayleighScattering.hh"
#include "G4KleinNishinaModel.hh"

#include "G4eMultipleScattering.hh"
#include "G4eIonisation.hh"
#include "G4eBremsstrahlung.hh"
#include "G4eplusAnnihilation.hh"

#include "G4MuMultipleScattering.hh"
#include "G4MuIonisation.hh"
#include "G4MuBremsstrahlung.hh"
#include "G4MuPairProduction.hh"

#include "G4hMultipleScattering.hh"
#include "G4hIonisation.hh"
#include "G4hBremsstrahlung.hh"
#include "G4hPairProduction.hh"

#include "G4ionIonisation.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4NuclearStopping.hh"
#include "G4SystemOfUnits.hh"
ExG4PhysicsList::ExG4PhysicsList():G4VModularPhysicsList()
{
  SetVerboseLevel(1);
//   fEmPhysicsList=new G4EmStandardPhysics_option1();//tof=240 fs; final step dx=2.2 um
//   fEmPhysicsList=new G4EmStandardPhysics_option2();//tof=240 fs; final step dx=2.2 um
//   fEmPhysicsList=new G4EmStandardPhysics_option3();//tof=240 fs; final step dx=2.2 um
//   fEmPhysicsList=new G4EmStandardPhysics_option4();//tof=240 fs; final step dx=2.2 um
//   fEmPhysicsList=new G4EmStandardPhysics();//tof=241 fs; final step dx=2.19 um
   //The default final step cut is too large!	   For 100 keV ions, only one step in the entire range.
  fEmPhysicsList=new PhysListEmStandard("local");//modify
  fParticleList = new G4DecayPhysics();
  fRaddecayList = new G4RadioactiveDecayPhysics();
//   RegisterPhysics(new G4DecayPhysics());
//   RegisterPhysics(new G4RadioactiveDecayPhysics());
//  RegisterPhysics(new G4EmStandardPhysics());
}


ExG4PhysicsList::~ExG4PhysicsList()
{

}

#include "G4Gamma.hh"
#include "G4Electron.hh"
#include "G4Positron.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4Deuteron.hh"
#include "G4Alpha.hh"
#include "G4GenericIon.hh"

void ExG4PhysicsList::ConstructParticle()
{//Particle definition
//  G4int Z=8,A=20;
//  G4double eE=0.*keV;
//  G4ParticleDefinition* oxygen20
//    =G4IonTable::GetIonTable()->GetIon(Z,A,eE);
  G4Gamma::GammaDefinition();
  G4Electron::ElectronDefinition();
  G4Positron::PositronDefinition();
  G4Proton::ProtonDefinition();
  G4Neutron::NeutronDefinition();
  G4Deuteron::DeuteronDefinition();
  G4Alpha::AlphaDefinition();
  G4GenericIon::GenericIonDefinition();

}

void ExG4PhysicsList::ConstructProcess()
{
  AddTransportation();
  
  fEmPhysicsList->ConstructProcess();
  fParticleList->ConstructProcess();
  fRaddecayList->ConstructProcess();

//   G4RadioactiveDecay* radioactiveDecay = new G4RadioactiveDecay( ) ;
//   radioactiveDecay->SetHLThreshold(-1.*s);
//   G4ProcessManager* pmanager = G4GenericIon::GenericIon()->GetProcessManager();
//   pmanager->AddProcess(radioactiveDecay , 0, -1, 1);
}

// void ExG4PhysicsList::SetCuts()
// {
// 	defaultCutValue=0.01*mm;
// 	G4int ver=0;
// 	SetVerboseLevel(ver);
// 	SetCutsWithDefault();
// 	//The cut is used to limit the generation of secondaries
// 	//The cut is expressed in equivalent range //This is converted in energy for each material
// 	//default = 1 mm
// 	//Only one value of production threshold distance is needed for all materials because it corresponds to different energies depending on material
// }
