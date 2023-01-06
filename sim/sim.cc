#include <iostream>
#include "G4RunManager.hh"  
#include "G4UIExecutive.hh"
#include "G4VisManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "construction.hh"
#include "action.hh"
#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main ( int argc, char** argv ) { /*This is a simple outer shell that we can use for any project*/
  
  G4RunManager* runManager = new G4RunManager(); /*used for running the Simulation*/
  runManager->SetUserInitialization(new MyDetectorConstruction());
  runManager->SetUserInitialization(new MyPhysicsList() );
  runManager->SetUserInitialization(new MyActionInitialization() );
  runManager->Initialize();

  G4UIExecutive* ui = new G4UIExecutive(argc, argv);

  G4VisManager* visManager = new G4VisExecutive(); /*Visualization manager*/
  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  
  UImanager->ApplyCommand("/vis/open OGL"); /*To use openGL*/
  UImanager->ApplyCommand("/vis/drawVolume"); /*To draw the detector volume*/
  UImanager->ApplyCommand("/vis/scene/add/trajectories smooth"); /*To show the trajectory of the particle*/
  UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
  UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate");

  ui->SessionStart();

  return 0;

}
