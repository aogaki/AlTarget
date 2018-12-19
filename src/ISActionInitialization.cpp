#include "ISActionInitialization.hpp"
#include "ISPrimaryGeneratorAction.hpp"
#include "ISRunAction.hpp"
#include "ISEventAction.hpp"


ISActionInitialization::ISActionInitialization()
   : G4VUserActionInitialization()
{}

ISActionInitialization::~ISActionInitialization()
{}

void ISActionInitialization::BuildForMaster() const
{
   SetUserAction(new ISRunAction());
}

void ISActionInitialization::Build() const
{
   SetUserAction(new ISPrimaryGeneratorAction());
   SetUserAction(new ISRunAction());
   SetUserAction(new ISEventAction());
}
