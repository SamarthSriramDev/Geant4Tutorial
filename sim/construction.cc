#include "construction.hh"
#include "detector.hh"

MyDetectorConstruction::MyDetectorConstruction() {}

MyDetectorConstruction::~MyDetectorConstruction() {}

G4VPhysicalVolume  *MyDetectorConstruction::Construct() {
  
  G4NistManager *nist = G4NistManager::Instance();

  G4Material *SiO2 = new G4Material("SiO2", 2.021*g/cm3, 2); /*Material, density, components*/
  SiO2->AddElement(nist->FindOrBuildElement("Si"), 1); /*Adding Silicon and only once, cuz Si*/
  SiO2->AddElement(nist->FindOrBuildElement("O"), 2); /*Adding O2*/

  G4Material *H2O = new G4Material("H2O", 1.000*g/cm3, 2); /*Material, density, components*/
  H2O->AddElement(nist->FindOrBuildElement("H"), 2); /*Adding H2*/
  H2O->AddElement(nist->FindOrBuildElement("O"), 1); /*Adding O*/  

  G4Element *C = nist->FindOrBuildElement("C");

  G4Material* Aerogel = new G4Material("Aerogel", 0.200*g/cm3, 3);
  Aerogel->AddMaterial(SiO2, 62.5*perCent); /*Material, percentage from units header*/
  Aerogel->AddMaterial(H2O, 37.4*perCent);
  Aerogel->AddElement(C, 0.1*perCent);

  G4double energy[2] ={1.239*eV/0.9, 1.239*eV/0.2}; /*Make sure energies are in increasing order*/
  G4double rindexAerogel[2] = {1.1, 1.1};
  G4double rindexWorld[2] = {1.0, 1.0};
  
  G4MaterialPropertiesTable* mptAerogel = new G4MaterialPropertiesTable();
  mptAerogel->AddProperty("RINDEX", energy, rindexAerogel, 2); /*Property name, energy/mom, rindex array, number of elements in array*/
  
  G4MaterialPropertiesTable* mptWorld = new G4MaterialPropertiesTable();

  mptWorld->AddProperty("RINDEX", energy, rindexWorld, 2);
  

  Aerogel->SetMaterialPropertiesTable(mptAerogel);

  G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
  worldMat->SetMaterialPropertiesTable(mptWorld);
  
  /* whenever we creat a detector we need to create 3 volumes and they are: 
   * Solid that defines the size, a logical volume that defines the material and
   * physical volume that places the detector in the geant4, this interacts with the particles*/ 

  /* the standard length in geant4 is mm */

  G4Box* solidWorld = new G4Box("solidWorld", 0.5*m, 0.5*m, 0.5*m); /*(name, half x, half y, half z)*/
  
  G4LogicalVolume* logicalWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
  /*(solid volume we define, material, name)*/

  G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicalWorld, "physWorld", 0, false, 0, true);
  /*(Rotation, location of the detector, logicalWorld, name, mothervolume, boolean operation, copy number, 
   * check for overlaps)*/

  G4Box* solidRadiator = new G4Box("SolidRadiator", 0.4*m, 0.4*m, 0.01*m);

  G4LogicalVolume* logicRadiator = new G4LogicalVolume(solidRadiator, Aerogel, "logicalRadiator");

  G4VPhysicalVolume* physRadiator = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.25*m), logicRadiator, "PhysRadiator", logicalWorld, false, 0, true);
  
  G4Box* solidDetector = new G4Box("solidDetector", 0.005*m, 0.005*m, 0.01*m); /*Name, half x, half y, half z*/

  logicDetector = new G4LogicalVolume(solidDetector, worldMat, "logicalDetector"); 

  for (G4int i = 0; i < 100; i++ ) {
    for ( G4int j = 0; j < 100; j++ ) {

      G4VPhysicalVolume* physDetector = new G4PVPlacement(0, G4ThreeVector(-0.5*m + (i+0.5)*m/100, -0.5*m + (j+0.5)*m/100, 0.49*m), logicDetector, "physDetector", logicalWorld, false, j + i*100, true);

    }
  
  }

  return physWorld; /*return the highest mothervolume*/ 

}

void MyDetectorConstruction::ConstructSDandField() {
  MySensitiveDetector* sensDet = new MySensitiveDetector("SensitiveDetector");

  logicDetector->SetSensitiveDetector(sensDet);
}


