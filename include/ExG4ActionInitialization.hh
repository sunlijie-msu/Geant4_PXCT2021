#ifndef ExG4ActionInitialization_h
#define ExG4ActionInitialization_h

#include "G4VUserActionInitialization.hh"

class ExG4ActionInitialization : public G4VUserActionInitialization
{
public:
   ExG4ActionInitialization();
   virtual ~ExG4ActionInitialization();

   virtual void BuildForMaster() const;
   virtual void Build() const;

};

#endif
