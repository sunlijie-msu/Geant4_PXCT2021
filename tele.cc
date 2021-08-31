//===================C++==================//
#include <ctime>// initialize random seed
#include "G4String.hh"
//=================GEANT4=================//
#include "Randomize.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
//==================User==================//
#include "ExG4DetectorConstruction.hh"
#include "ExG4PhysicsList.hh"
//#include "PhysicsList.hh"
//#include "exrdmPhysicsList.hh"
#include "ExG4ActionInitialization.hh"
int main(int argc,char** argv)
{

	//===========================Set the Seed of Random===========================//
	CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine());
	CLHEP::HepRandom::setTheSeed(time(NULL));
	
	//================================Main Codes==================================//
    // construct the default run manager
    G4RunManager* runManager = new G4RunManager;

    // set mandatory initialization classes
    runManager->SetUserInitialization(new ExG4DetectorConstruction);
    runManager->SetUserInitialization(new ExG4PhysicsList);//choose one Main PhysicsList, other physicslists are invoked in PhysicsList.cc
	//runManager->SetUserInitialization(new PhysicsList);
	//runManager->SetUserInitialization(new exrdmPhysicsList);
    runManager->SetUserInitialization(new ExG4ActionInitialization);

    // initialize G4 kernel
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    runManager->Initialize();

	//==========================Control the Verbose Level=========================//
	G4UImanager* UImanager = G4UImanager::GetUIpointer();
	UImanager->ApplyCommand("/run/verbose 0");
	UImanager->ApplyCommand("/event/verbose 0");
	UImanager->ApplyCommand("/tracking/verbose 0");
	
	//===================================BeamOn==================================//
	if(argc==1)
	{
		for(int runid=0;runid<1;runid++)
		{
			runManager->BeamOn(10);//
		}
	}
	else
	{
		G4String fileName=argv[1];
		G4String command1="/control/execute init_";
		G4String command2=".mac";
		G4UIExecutive *ui=new G4UIExecutive(argc,argv);
		UImanager->ApplyCommand(command1+fileName+command2); 	
		ui->SessionStart();
		delete ui;
		ui=NULL;
	}
	
	delete visManager;
	visManager=NULL;	
	delete runManager;
	runManager=NULL;
	
	return 0;
}
