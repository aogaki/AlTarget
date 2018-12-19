#include <G4EmPenelopePhysics.hh>
#include <G4EmExtraPhysics.hh>
#include <G4DecayPhysics.hh>
#include <G4RadioactiveDecayPhysics.hh>
#include <G4HadronElasticPhysicsHP.hh>
#include <G4HadronPhysicsShielding.hh>
#include <G4StoppingPhysics.hh>
#include <G4IonQMDPhysics.hh>
#include <G4IonElasticPhysics.hh>
#include <G4IonBinaryCascadePhysics.hh>

#include "ISPhysicsList.hpp"


ISPhysicsList::ISPhysicsList()
   :  G4VModularPhysicsList()
{
   G4int verbose = 1;

   // EM physics
   RegisterPhysics(new G4EmPenelopePhysics(verbose));

   // Synchroton Radiation & GN Physics
   RegisterPhysics(new G4EmExtraPhysics(verbose));

   // Decays
   RegisterPhysics(new G4DecayPhysics(verbose));
   RegisterPhysics(new G4RadioactiveDecayPhysics(verbose));

   // Hadron Elastic scattering
   RegisterPhysics(new G4HadronElasticPhysicsHP(verbose));
   
   // Hadron Physics
   RegisterPhysics(new G4HadronPhysicsShielding(verbose));

   // Stopping Physics
   RegisterPhysics(new G4StoppingPhysics(verbose));

   // Ion Physics
   RegisterPhysics(new G4IonQMDPhysics(verbose));
   RegisterPhysics(new G4IonElasticPhysics(verbose));
}

ISPhysicsList::~ISPhysicsList()
{}
