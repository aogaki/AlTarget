#include <G4HCofThisEvent.hh>
#include <G4Material.hh>
#include <G4SDManager.hh>
#include <G4Step.hh>
#include <G4SystemOfUnits.hh>
#include <G4TouchableHistory.hh>
#include <G4VProcess.hh>
#include <G4ios.hh>
#include <g4root.hh>

#include "ISHit.hpp"
#include "ISSD.hpp"

ISSD::ISSD(const G4String &name, const G4String &hitsCollectionName)
    : G4VSensitiveDetector(name)
{
  collectionName.insert(hitsCollectionName);
}

ISSD::~ISSD() {}

void ISSD::Initialize(G4HCofThisEvent *hce)
{
  fHitsCollection =
      new ISHitsCollection(SensitiveDetectorName, collectionName[0]);

  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection(hcID, fHitsCollection);
}

G4bool ISSD::ProcessHits(G4Step *step, G4TouchableHistory * /*history*/)
{
  // Only recording at boundary
  G4StepPoint *postStepPoint = step->GetPostStepPoint();
  if (postStepPoint->GetStepStatus() != fGeomBoundary) return false;
  G4ThreeVector position = postStepPoint->GetPosition();
  if (position[2] != 2.5 * cm) return false;

  auto newHit = new ISHit();

  newHit->SetPosition(position);

  G4ThreeVector momentum = postStepPoint->GetMomentum();
  newHit->SetMomentum(momentum);

  G4double kineticEnergy = postStepPoint->GetKineticEnergy();
  newHit->SetKineticEnergy(kineticEnergy);

  auto track = step->GetTrack();
  G4ParticleDefinition *particle = track->GetDefinition();
  G4int pdgCode = particle->GetPDGEncoding();
  newHit->SetPDGCode(pdgCode);

  fHitsCollection->insert(newHit);

  return true;
}
