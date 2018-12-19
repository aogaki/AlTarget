#ifndef ISSD_h
#define ISSD_h 1

#include <G4VSensitiveDetector.hh>
#include <G4ThreeVector.hh>
#include <G4LogicalVolume.hh>

#include "ISHit.hpp"


class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class ISSD: public G4VSensitiveDetector
{
public:
   ISSD(const G4String &name,
            const G4String &hitsCollectionName);
   virtual ~ISSD();

   virtual void Initialize(G4HCofThisEvent *hce);
   virtual G4bool ProcessHits(G4Step *step, G4TouchableHistory *history);

private:
   ISHitsCollection *fHitsCollection;
};

#endif
