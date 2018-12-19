#ifndef ISEventAction_h
#define ISEventAction_h 1

#include <G4UserEventAction.hh>

#include "ISHit.hpp"

class ISEventAction : public G4UserEventAction
{
public:
   ISEventAction();
   virtual ~ISEventAction();

   virtual void BeginOfEventAction(const G4Event *);
   virtual void EndOfEventAction(const G4Event *);

private:
   ISHitsCollection *GetHitsCollection(G4int hcID, const G4Event *event) const;
   
   G4int fHitsCollectionID;
};

#endif
