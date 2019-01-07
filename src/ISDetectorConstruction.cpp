#include <G4Box.hh>
#include <G4LogicalVolume.hh>
#include <G4LogicalVolumeStore.hh>
#include <G4NistManager.hh>
#include <G4PVPlacement.hh>
#include <G4PVReplica.hh>
#include <G4RunManager.hh>
#include <G4SDManager.hh>
#include <G4SystemOfUnits.hh>
#include <G4Tubs.hh>

#include "ISDetectorConstruction.hpp"
#include "ISSD.hpp"

ISDetectorConstruction::ISDetectorConstruction() : fVacuumMat(nullptr)
{
  fCheckOverlap = true;

  // fTargetT = 7. * cm;
  fTargetT = 3.5 * mm;
  fTargetSize = 1. * mm;

  DefineMaterials();
  DefineCommands();
}

ISDetectorConstruction::~ISDetectorConstruction() {}

void ISDetectorConstruction::DefineMaterials()
{
  G4NistManager *manager = G4NistManager::Instance();

  // NIST database materials
  fVacuumMat = manager->FindOrBuildMaterial("G4_Galactic");
  // fTargetMat = manager->FindOrBuildMaterial("G4_Al");
  fTargetMat = manager->FindOrBuildMaterial("G4_W");
}

G4VPhysicalVolume *ISDetectorConstruction::Construct()
{
  // world volume
  G4double worldX = 10. * cm;
  G4double worldY = 10. * cm;
  G4double worldZ = 10. * cm;

  G4Box *worldS = new G4Box("World", worldX / 2., worldY / 2., worldZ / 2.);
  G4LogicalVolume *worldLV = new G4LogicalVolume(worldS, fVacuumMat, "World");

  G4VisAttributes *visAttributes = new G4VisAttributes(G4Colour::White());
  visAttributes->SetVisibility(false);
  worldLV->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

  // Al target
  auto targetS =
      new G4Box("Target", fTargetSize / 2., fTargetSize / 2., fTargetT / 2.);
  auto targetLV = new G4LogicalVolume(targetS, fTargetMat, "Target");
  visAttributes = new G4VisAttributes(G4Colour::Cyan());
  targetLV->SetVisAttributes(visAttributes);
  fVisAttributes.push_back(visAttributes);

  // auto pos = G4ThreeVector(0., 0., -fTargetT / 2.);
  auto pos = G4ThreeVector(0., 0., 0.);
  fTargetPV = new G4PVPlacement(nullptr, pos, targetLV, "Target", worldLV,
                                false, 0, fCheckOverlap);

  G4VPhysicalVolume *worldPV = new G4PVPlacement(
      nullptr, G4ThreeVector(), worldLV, "World", 0, false, 0, fCheckOverlap);

  return worldPV;
}

void ISDetectorConstruction::ConstructSDandField()
{
  // Sensitive Detectors
  G4VSensitiveDetector *SD = new ISSD("SD", "HC");
  G4SDManager::GetSDMpointer()->AddNewDetector(SD);
  SetSensitiveDetector("Target", SD);
}

void ISDetectorConstruction::DefineCommands()
{
  fMessenger = new G4GenericMessenger(this, "/InSb/Geo/", "Target control");

  // Thickness
  G4GenericMessenger::Command &scintiTCmd = fMessenger->DeclareMethodWithUnit(
      "T", "mm", &ISDetectorConstruction::SetTargetT,
      "Set the thickness of target.");
  scintiTCmd.SetParameterName("t", true);
  scintiTCmd.SetRange("t>=0. && t<10000.");
  scintiTCmd.SetDefaultValue("0.5");
}

void ISDetectorConstruction::SetTargetT(G4double t)
{
  fTargetT = t;
  G4Box *plate = (G4Box *)(fTargetPV->GetLogicalVolume()->GetSolid());
  plate->SetZHalfLength(fTargetT / 2.);

  G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
