#include <iomanip>

#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "ISHit.hpp"


G4ThreadLocal G4Allocator<ISHit> *ISHitAllocator = 0;


ISHit::ISHit()
   : G4VHit()
{}

ISHit::~ISHit()
{}

ISHit::ISHit(const ISHit & /*right*/)
   : G4VHit()
{}

const ISHit &
ISHit::operator=(const ISHit & /*right*/)
{
   return *this;
}

int ISHit::operator==(const ISHit & /*right*/) const
{
   return 0;
}
