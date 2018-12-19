#include <g4root.hh>

#include "ISRunAction.hpp"

ISRunAction::ISRunAction() : G4UserRunAction()
{
  auto anaMan = G4AnalysisManager::Instance();
  // anaMan->SetNtupleMerging(true);
  anaMan->SetVerboseLevel(1);
  G4String fileName = "result";
  anaMan->SetFileName(fileName);

  anaMan->CreateNtuple("AlTarget", "particle info");
  anaMan->CreateNtupleIColumn("eveID");

  anaMan->CreateNtupleDColumn("x");
  anaMan->CreateNtupleDColumn("y");
  anaMan->CreateNtupleDColumn("z");

  anaMan->CreateNtupleDColumn("Px");
  anaMan->CreateNtupleDColumn("Py");
  anaMan->CreateNtupleDColumn("Pz");

  anaMan->CreateNtupleDColumn("KineticEnergy");

  anaMan->CreateNtupleIColumn("PDGCode");

  anaMan->FinishNtuple();
}

ISRunAction::~ISRunAction() { delete G4AnalysisManager::Instance(); }

void ISRunAction::BeginOfRunAction(const G4Run *)
{
  G4AnalysisManager *anaMan = G4AnalysisManager::Instance();
  anaMan->OpenFile();
}

void ISRunAction::EndOfRunAction(const G4Run *)
{
  G4AnalysisManager *anaMan = G4AnalysisManager::Instance();
  anaMan->Write();
  anaMan->CloseFile();
}
