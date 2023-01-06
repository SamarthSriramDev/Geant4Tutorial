#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "run.hh"

/*We need to define an action*/
class MyActionInitialization : public G4VUserActionInitialization {
  
  public:
    MyActionInitialization();
    ~MyActionInitialization();

    virtual void Build() const;

};

#endif
