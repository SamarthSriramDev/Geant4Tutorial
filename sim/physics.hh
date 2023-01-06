#ifndef PHYSICS_HH
#define PHYSICS_HH

#include "G4VModularPhysicsList.hh"
#include "G4EmStandardPhysics.hh"
#include "G4OpticalPhysics.hh"
/* we need to define how the particles interact, hence we define a physics list */

class MyPhysicsList : public G4VModularPhysicsList {
  public:  
    MyPhysicsList();
    ~MyPhysicsList();

};


#endif
