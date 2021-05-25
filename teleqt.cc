#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"

#include "ExG4DetectorConstruction.hh"
#include "ExG4PhysicsList.hh"
#include "ExG4ActionInitialization.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

int main(int argc,char** argv)
{
  // construct the default run manager
  G4RunManager* runManager = new G4RunManager;

  // set mandatory initialization classes
  runManager->SetUserInitialization(new ExG4DetectorConstruction);
  runManager->SetUserInitialization(new ExG4PhysicsList);

  runManager->SetUserInitialization(new ExG4ActionInitialization);

  // initialize G4 kernel
  runManager->Initialize();

#ifdef G4VIS_USE
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
#endif

  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();
  if(argc==1)
  {
    G4UIExecutive* ui = new G4UIExecutive(argc,argv);
#ifdef G4VIS_USE
    UI->ApplyCommand("/control/execute init_vis.mac");
#else
    UI->ApplyCommand("/run/verbose 0");
    UI->ApplyCommand("/event/verbose 0");
    UI->ApplyCommand("/tracking/verbose 0");
#endif
    ui->SessionStart();
    delete ui;
  }
  else
  {
    //batch mode
    G4String command="/control/execute ";
    G4String fileName=argv[1];
    UI->ApplyCommand(command+fileName);
  }

  // start a run
  //int numberOfEvent = 3;
  //runManager->BeamOn(numberOfEvent);

 
  // job termination
#ifdef G4VIS_USE
  delete visManager;
#endif

  delete runManager;
  return 0;
}
