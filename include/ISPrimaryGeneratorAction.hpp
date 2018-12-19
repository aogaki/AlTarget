#ifndef ISPrimaryGeneratorAction_h
#define ISPrimaryGeneratorAction_h 1

#include <TH2.h>

#include <G4Event.hh>
#include <G4GenericMessenger.hh>
#include <G4ParticleGun.hh>
#include <G4Threading.hh>
#include <G4ThreeVector.hh>
#include <G4VUserPrimaryGeneratorAction.hh>

class ISPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
 public:
  ISPrimaryGeneratorAction();
  virtual ~ISPrimaryGeneratorAction();

  void GeneratePrimaries(G4Event *);

  void SetEnergy(G4double ene);

 private:
  G4ParticleGun *fParticleGun;

  TH2D *fHis;

  void DefineCommands();
  G4GenericMessenger *fMessenger;
  G4double fEnergy;
};

#endif
