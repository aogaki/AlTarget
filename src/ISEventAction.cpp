#include <G4Event.hh>
#include <G4SDManager.hh>
#include <g4root.hh>

#include "ISEventAction.hpp"

ISEventAction::ISEventAction() : G4UserEventAction(), fHitsCollectionID(-1) {}

ISEventAction::~ISEventAction() {}

ISHitsCollection *ISEventAction::GetHitsCollection(G4int hcID,
                                                   const G4Event *event) const
{
  ISHitsCollection *hitsCollection =
      static_cast<ISHitsCollection *>(event->GetHCofThisEvent()->GetHC(hcID));

  if (!hitsCollection) {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID;
    // check how to use G4Exception
    G4Exception("ISEventAction::GetHitsCollection()", "ISCode0003",
                FatalException, msg);
  }

  return hitsCollection;
}

void ISEventAction::BeginOfEventAction(const G4Event *) {}

void ISEventAction::EndOfEventAction(const G4Event *event)
{
  if (fHitsCollectionID == -1)
    fHitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID("HC");

  G4int eventID = event->GetEventID();

  G4AnalysisManager *anaMan = G4AnalysisManager::Instance();

  ISHitsCollection *hc = GetHitsCollection(fHitsCollectionID, event);
  const G4int kHit = hc->entries();
  for (G4int iHit = 0; iHit < kHit; iHit++) {
    ISHit *newHit = (*hc)[iHit];

    anaMan->FillNtupleIColumn(0, eventID);

    G4ThreeVector position = newHit->GetPosition();
    anaMan->FillNtupleDColumn(1, position.x());
    anaMan->FillNtupleDColumn(2, position.y());
    anaMan->FillNtupleDColumn(3, position.z());

    G4ThreeVector momentum = newHit->GetMomentum();
    anaMan->FillNtupleDColumn(4, momentum.x());
    anaMan->FillNtupleDColumn(5, momentum.y());
    anaMan->FillNtupleDColumn(6, momentum.z());

    G4double ene = newHit->GetKineticEnergy();
    anaMan->FillNtupleDColumn(7, ene);

    G4int pdgCode = newHit->GetPDGCode();
    anaMan->FillNtupleIColumn(8, pdgCode);

    anaMan->AddNtupleRow();
  }
}
