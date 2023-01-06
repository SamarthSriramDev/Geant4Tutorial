#include "action.hh"
#include "run.hh"

MyActionInitialization::MyActionInitialization() {}

 MyActionInitialization::~MyActionInitialization() {}

 void MyActionInitialization::Build() const {

   MyPrimaryGenerator* generator = new MyPrimaryGenerator();
   SetUserAction(generator);

   MyRunAction *runAction = new MyRunAction();
   SetUserAction(runAction);

 }
