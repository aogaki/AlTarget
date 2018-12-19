#ifndef ISActionInitialization_h
#define ISActionInitialization_h 1

#include <G4VUserActionInitialization.hh>
#include <globals.hh>


class ISActionInitialization : public G4VUserActionInitialization
{
public:
   ISActionInitialization();
   virtual ~ISActionInitialization();

   virtual void BuildForMaster() const;
   virtual void Build() const;

private:
      
};

#endif
