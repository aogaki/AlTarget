#ifndef ISRunAction_h
#define ISRunAction_h 1

#include <G4UserRunAction.hh>
#include <G4Run.hh>


class ISRunAction: public G4UserRunAction
{
public:
   ISRunAction();
   virtual ~ISRunAction();

   virtual void BeginOfRunAction(const G4Run *);
   virtual void EndOfRunAction(const G4Run *);

private:

};

#endif
