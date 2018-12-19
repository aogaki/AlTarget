#ifndef ISHit_h
#define ISHit_h 1

#include "G4Allocator.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4Types.hh"
#include "G4VHit.hh"

class ISHit : public G4VHit
{
 public:
  ISHit();
  virtual ~ISHit();
  ISHit(const ISHit &right);
  const ISHit &operator=(const ISHit &right);
  int operator==(const ISHit &right) const;

  inline void *operator new(size_t);
  inline void operator delete(void *);

  // add setter/getter methods
  void SetPosition(G4ThreeVector position) { fPosition = position; };
  G4ThreeVector GetPosition() { return fPosition; };

  void SetMomentum(G4ThreeVector momentum) { fMomentum = momentum; };
  G4ThreeVector GetMomentum() { return fMomentum; };

  void SetKineticEnergy(G4double kineticEnergy)
  {
    fKineticEnergy = kineticEnergy;
  };
  G4double GetKineticEnergy() { return fKineticEnergy; };

  void SetPDGCode(G4int code) { fPDGCode = code; };
  G4int GetPDGCode() { return fPDGCode; };

 private:
  G4ThreeVector fPosition;
  G4ThreeVector fMomentum;
  G4double fKineticEnergy;
  G4int fPDGCode;
};

typedef G4THitsCollection<ISHit> ISHitsCollection;

extern G4ThreadLocal G4Allocator<ISHit> *ISHitAllocator;

inline void *ISHit::operator new(size_t)
{
  if (!ISHitAllocator) ISHitAllocator = new G4Allocator<ISHit>;
  return (void *)ISHitAllocator->MallocSingle();
}

inline void ISHit::operator delete(void *hit)
{
  ISHitAllocator->FreeSingle((ISHit *)hit);
}

#endif
