#include "physics.hh"

MyPhysicsList::MyPhysicsList() {

  RegisterPhysics ( new G4EmStandardPhysics() ); /*We are looking only at EM interactions in this case*/

  RegisterPhysics ( new G4OpticalPhysics() );  /*For cerenkov interactions*/


}

MyPhysicsList::~MyPhysicsList() {}
