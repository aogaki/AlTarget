#include <random>

#include <Randomize.hh>

#ifdef G4MULTITHREADED
#include <G4MTRunManager.hh>
#include <G4Threading.hh>
#else
#include <G4RunManager.hh>
#endif

#include <G4UImanager.hh>
#ifdef G4VIS_USE
#include <G4TrajectoryParticleFilter.hh>
#include <G4VisExecutive.hh>
#endif
#ifdef G4UI_USE
#include <G4UIExecutive.hh>
#endif

// Reference physics lists
#include <QGSP_BERT_HP.hh>

// User defined classes
#include "ISActionInitialization.hpp"
#include "ISDetectorConstruction.hpp"
#include "ISPhysicsList.hpp"

int main(int argc, char **argv)
{
  // Choose the Random engine
  // Need both?
  std::random_device rndSeed;  // Use C++11!
  CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine(rndSeed()));
  G4Random::setTheEngine(new CLHEP::MTwistEngine(rndSeed()));

  // Construct the default run manager
#ifdef G4MULTITHREADED
  auto runManager = new G4MTRunManager();
  runManager->SetNumberOfThreads(G4Threading::G4GetNumberOfCores());
#else
  auto runManager = new G4RunManager();
#endif

  // Detector construction
  runManager->SetUserInitialization(new ISDetectorConstruction());

  // Physics list
  auto physicsList = new ISPhysicsList();
  // auto physicsList = new QGSP_BERT_HP();
  runManager->SetUserInitialization(physicsList);

  // Primary generator action and User action intialization
  runManager->SetUserInitialization(new ISActionInitialization());

  // Initialize G4 kernel
  //
  runManager->Initialize();

#ifdef G4VIS_USE
  // Initialize visualization
  auto visManager = new G4VisExecutive();
  visManager->Initialize();
#endif

  // Get the pointer to the User Interface manager
  auto UImanager = G4UImanager::GetUIpointer();
  if (argc != 1) {
    // execute an argument macro file if exist
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command + fileName);
  } else {
    // interactive mode : define UI session
#ifdef G4UI_USE
    auto ui = new G4UIExecutive(argc, argv);
#ifdef G4VIS_USE
    UImanager->ApplyCommand("/control/execute init_vis.mac");
#else
    UImanager->ApplyCommand("/control/execute init.mac");
#endif
    ui->SessionStart();
    delete ui;
#endif
  }

#ifdef G4VIS_USE
  delete visManager;
#endif

  delete runManager;

  return 0;
}
