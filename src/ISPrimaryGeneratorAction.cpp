#include <TFile.h>

#include <G4AutoLock.hh>
#include <G4ChargedGeantino.hh>
#include <G4IonTable.hh>
#include <G4ParticleTable.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>
#include <g4root.hh>

#include "ISPrimaryGeneratorAction.hpp"

static G4int nEveInPGA = 0;
G4Mutex mutexInPGA = G4MUTEX_INITIALIZER;

ISPrimaryGeneratorAction::ISPrimaryGeneratorAction()
    : G4VUserPrimaryGeneratorAction(), fParticleGun(nullptr), fHis(nullptr)
{
  fParticleGun = new G4ParticleGun(1);

  auto parTable = G4ParticleTable::GetParticleTable();

  auto particle = parTable->FindParticle("e-");
  fParticleGun->SetParticleDefinition(particle);

  auto sourcePos = -10. * mm - ((50. / 2.) * mm);
  fParticleGun->SetParticlePosition(G4ThreeVector(0., 0., sourcePos));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));

  fEnergy = 1. * keV;
  fParticleGun->SetParticleEnergy(fEnergy);

  DefineCommands();

  G4AutoLock lock(&mutexInPGA);
  auto file = new TFile("Data/source.root", "READ");
  if (!file->IsOpen()) {
    G4cerr << "Source file is not open." << G4endl;
    exit(0);
  }
  fHis = (TH2D *)file->Get("His2D");
  fHis->SetDirectory(0);
  file->Close();
  delete file;
}

ISPrimaryGeneratorAction::~ISPrimaryGeneratorAction()
{
  delete fParticleGun;
  delete fHis;
}

void ISPrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
  G4double ene;
  G4double theta;
  fHis->GetRandom2(theta, ene);
  ene *= MeV;
  theta *= deg;
  G4double phi = G4UniformRand() * 2. * CLHEP::pi;

  G4double vx = sin(theta) * cos(phi);
  G4double vy = sin(theta) * sin(phi);
  G4double vz = cos(theta);
  auto parVec = G4ThreeVector(vx, vy, vz);

  fParticleGun->SetParticleEnergy(ene);
  fParticleGun->SetParticleMomentumDirection(parVec);
  fParticleGun->GeneratePrimaryVertex(event);

  G4AutoLock lock(&mutexInPGA);
  if (nEveInPGA++ % 10000 == 0)
    G4cout << nEveInPGA - 1 << " events done" << G4endl;
}

void ISPrimaryGeneratorAction::DefineCommands()
{
  fMessenger = new G4GenericMessenger(this, "/InSb/Primary/", "Beam control");

  // Kinetic energy
  G4GenericMessenger::Command &setEneCmd = fMessenger->DeclareMethodWithUnit(
      "K", "keV", &ISPrimaryGeneratorAction::SetEnergy,
      "Set the kinetic energy.");

  setEneCmd.SetParameterName("K", true);
  setEneCmd.SetRange("K>=1. && K<10000.");
  setEneCmd.SetDefaultValue("10");
}

void ISPrimaryGeneratorAction::SetEnergy(G4double ene)
{
  fEnergy = ene;
  fParticleGun->SetParticleEnergy(fEnergy);
}
