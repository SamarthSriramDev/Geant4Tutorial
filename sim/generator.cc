#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator() {
  
  fParticleGun = new G4ParticleGun(1); /*No. of particles per event, 1 in this case*/
  
}

MyPrimaryGenerator::~MyPrimaryGenerator() {
  
  delete fParticleGun;

}

void MyPrimaryGenerator::GeneratePrimaries(G4Event* anEvent) {
  
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable(); /*All particles are stored in this*/

  /*suppose we wanna shoot a proton*/

  G4String particleName = "proton";

  G4ParticleDefinition* particle = particleTable->FindParticle("proton");

  G4ThreeVector pos(0., 0., 0.);
  G4ThreeVector mom(0., 0., 1.);

  fParticleGun->SetParticlePosition(pos);
  fParticleGun->SetParticleMomentumDirection(mom);
  fParticleGun->SetParticleMomentum(100.*GeV);
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->GeneratePrimaryVertex(anEvent);

}
