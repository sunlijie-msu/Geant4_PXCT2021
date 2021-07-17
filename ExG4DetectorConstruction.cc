#include "ExG4DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4ios.hh"

ExG4DetectorConstruction::ExG4DetectorConstruction():G4VUserDetectorConstruction()
{}

ExG4DetectorConstruction::~ExG4DetectorConstruction()
{}

G4LogicalVolume* ExG4DetectorConstruction::addCylinder(G4String name, G4double r_in, G4double r_out, G4double hz,
					   G4Material *material, G4ThreeVector pos, G4RotationMatrix *rot,
					   G4Color color)
{
  G4VSolid *solid = new G4Tubs(name, r_in, r_out, hz, 0*deg, 360*deg);
  G4LogicalVolume *volume = new G4LogicalVolume(solid, material, name);
  new G4PVPlacement(rot, pos, volume, name, logicWorld, false, 0, checkOverlaps);
  volume->SetVisAttributes(G4VisAttributes(color));
  return volume;
}

G4VPhysicalVolume* ExG4DetectorConstruction::Construct()
{
  //set up materials and highest level volumes
  ConstructMaterials(); 

  solidWorld = new G4Box("worldBox",2*m,2*m,2*m);
  logicWorld = new G4LogicalVolume(solidWorld,vacuum,"logicWorld");
  physiWorld = new G4PVPlacement(0,G4ThreeVector(),logicWorld,"physiWorld",0,false,0,checkOverlaps);

  //  set up physical objects and detectors and things
  //DSSD1 (delta E)
  G4ThreeVector dssd1_pos(0,0,10*mm);
  G4double dssd1_thickness = 0.01*mm;
  G4double dssd1_wt = 0.0005*mm;//window thickness
  logicDSSD1 = addCylinder("DSSD1", 0*mm, 6*mm, dssd1_thickness/2,silicon, dssd1_pos, 0, G4Color::Grey()); //DE active area
  addCylinder("DSSD1_Chip", 6*mm, 8*mm, 0.140*mm/2, silicon, dssd1_pos, 0, G4Color::Green());
  addCylinder("DSSD1_Frame", 8*mm, 15*mm, 3.472*mm/2, FR4, dssd1_pos, 0, G4Color::Red());
  addCylinder("DSSD1_Window_Front", 0*mm, 6*mm, dssd1_wt/2, aluminum,
	      dssd1_pos - G4ThreeVector(0,0, dssd1_thickness + dssd1_wt/2),
	      0, G4Color::Grey());
  addCylinder("DSSD1_Window_Front", 0*mm, 6*mm, dssd1_wt/2, aluminum,
	      dssd1_pos + G4ThreeVector(0,0, dssd1_thickness + dssd1_wt/2),
	      0, G4Color::Grey());
  
  //DSSD2 (E)
  G4double dssd2_thickness = 1.0*mm;
  G4ThreeVector dssd2_pos(0,0,20*mm);
  G4double dssd2_wt = 0.0005*mm; //window thickness
  logicDSSD2 = addCylinder("DSSD2", 0*mm, 13*mm, dssd2_thickness/2, silicon, dssd2_pos, 0, G4Color::Grey());
  addCylinder("DSSD2_Chip", 13*mm, 15*mm, dssd2_thickness/2, silicon, dssd2_pos, 0, G4Color::Green());
  addCylinder("DSSD2_Frame", 15*mm, 21.6*mm, 3.2/2*mm, FR4, dssd2_pos, 0, G4Color::Red());
  addCylinder("DSSD2_Window_Front", 0*mm, 13*mm, dssd2_wt/2, aluminum,
	      dssd2_pos - G4ThreeVector(0,0,dssd2_thickness/2 + dssd2_wt/2), 0, G4Color::Grey());
  addCylinder("DSSD2_Window_Back", 0*mm, 13*mm, dssd2_wt/2, aluminum,
	      dssd2_pos - G4ThreeVector(0,0,dssd2_thickness/2 + dssd2_wt/2), 0, G4Color::Grey());

  //DSSD3 (X-ray detector)
  /*  G4VSolid* solidDSSD3
    = new G4Box("solidDSSD3",10./2.*mm,10./2.*mm,5/2.*mm); //X-ray detector
  logicDSSD3
    = new G4LogicalVolume(solidDSSD3,silicon,"logicDSSD3");
  physiDSSD3
    = new G4PVPlacement(0,G4ThreeVector(0,0,-20.*mm),logicDSSD3,"physiDSSD3",logicWorld,false,0,checkOverlaps);
    logicDSSD3->SetVisAttributes(G4VisAttributes(G4Color::Yellow()));*/
  G4double xrayDetectorToSourceDistance = 5*mm;
  G4double xrayDetectorThickness = 10*mm;
  G4double xrayDetectorRadius = sqrt(100/CLHEP::pi)*mm;
  logicDSSD3 = addCylinder("DSSD3", 0*mm, xrayDetectorRadius, xrayDetectorThickness/2, germanium,
			   G4ThreeVector(0,0,-(xrayDetectorToSourceDistance + xrayDetectorThickness/2)),
			   0, G4Color::Yellow());

  /*  addCylinder("xray window", 0*mm, xrayDetectorRadius, 0.0254*mm/2, beryllium,
	      G4ThreeVector(0,0,-xrayDetectorToSourceDistance/2),
	      0, G4Color(255, 100, 100, 0.5));*/
			   

  //QSD1 (gamma-ray detector)
  G4VSolid* solidQSD1
    = new G4Box("solidQSD1",80./2.*mm,80./2.*mm,100./2.*mm); //HPGe
  logicQSD1
    = new G4LogicalVolume(solidQSD1,germanium,"logicQSD1");
  physiQSD1 //(78.26+148.9/2)=152.71
    = new G4PVPlacement(0,G4ThreeVector(0,0,100*mm),logicQSD1,"physiQSD1",logicWorld,false,0,checkOverlaps);
  logicQSD1->SetVisAttributes(G4VisAttributes(G4Color::Cyan()));

  //  target (formerly known as QSD2)
  G4double target_thickness = 0.000001*mm;
  addCylinder("target", 0*mm,8*mm, target_thickness/2, mylar, G4ThreeVector(0,0,0), 0, G4Color::Grey());

  //Chamber
  G4RotationMatrix* Rot = new G4RotationMatrix; // Rotates X and Z axes only
  Rot -> rotateX(M_PI/2.*rad); // Rotates 90 degrees
  addCylinder("chamber", 75/2*mm, 79/2*mm, 500/2*mm, iron, G4ThreeVector(0,0,0), Rot, G4Color(0.5,0.5,0.5,0.25));



  // visualization attributes ------------------------------------------------
  /*DetectorVisAtt = new G4VisAttributes(G4Colour::Red());
  logicDSSD1_Frame->SetVisAttributes(DetectorVisAtt);
  DetectorVisAtt = new G4VisAttributes(G4Colour::Blue());
  logicDSSD2_Frame->SetVisAttributes(DetectorVisAtt);
  DetectorVisAtt = new G4VisAttributes(G4Colour::Green());
  logicDSSD1_Chip->SetVisAttributes(DetectorVisAtt);
  DetectorVisAtt = new G4VisAttributes(G4Colour::Green());
  logicDSSD2_Chip->SetVisAttributes(DetectorVisAtt);
  DetectorVisAtt = new G4VisAttributes(G4Colour::Yellow());
  logicDSSD3->SetVisAttributes(DetectorVisAtt);
  DetectorVisAtt = new G4VisAttributes(G4Colour::Cyan());
  logicQSD1->SetVisAttributes(DetectorVisAtt);
  DetectorVisAtt = new G4VisAttributes(G4Colour::Gray());
  logicQSD2->SetVisAttributes(DetectorVisAtt);
  */

  return physiWorld;
}

void ExG4DetectorConstruction::ConstructMaterials()
{
  G4NistManager* nistManager = G4NistManager::Instance();
  
  G4bool isotopes = false;
  O = nistManager->FindOrBuildElement("O" , isotopes);
  Si = nistManager->FindOrBuildElement("Si", isotopes);
  H = nistManager->FindOrBuildElement("H", isotopes);
  C = nistManager->FindOrBuildElement("C", isotopes);
  Fe = nistManager->FindOrBuildElement("Fe", isotopes);
  Cr = nistManager->FindOrBuildElement("Cr", isotopes);
  Ni = nistManager->FindOrBuildElement("Ni", isotopes);

  germanium=nistManager->FindOrBuildMaterial("G4_Ge");
  gold=nistManager->FindOrBuildMaterial("G4_Au");
  iron=nistManager->FindOrBuildMaterial("G4_Fe");
  carbon=nistManager->FindOrBuildMaterial("G4_C");
  hydrogen=nistManager->FindOrBuildMaterial("G4_H");
  aluminum=nistManager->FindOrBuildMaterial("G4_Al");
  silicon=nistManager->FindOrBuildMaterial("G4_Si");
  csi=nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
  plastic=nistManager->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");	// Scintillator	// (PolyVinylToluene, C_9H_10)
  mylar = nistManager->FindOrBuildMaterial("G4_MYLAR");
  stainless_steel=nistManager->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  beryllium = nistManager->FindOrBuildMaterial("G4_Be");
	
  // vacuum
  // nistManager->FindOrBuildMaterial("G4_Galatic");

  // vacuum : air with low density
  air = nistManager->FindOrBuildMaterial("G4_AIR");
  density = 1.0e-6*air->GetDensity();
  vacuum = nistManager->BuildMaterialWithNewDensity("VACUUM","G4_AIR",density);

  //P10 Gas 780 torr
  argon = nistManager->FindOrBuildMaterial("G4_Ar");
  methane = nistManager->FindOrBuildMaterial("G4_METHANE");
  PressureFactor = 1.0263;  // 780 torr/760 torr=1.0263
  density = PressureFactor*0.001564*g/cm3; // 1564*1.0263=1605
  pressure = PressureFactor*atmosphere;
  P10_780torr = new G4Material("P10_780torr", density, nel=2, kStateGas,temperature= 293.15*kelvin, pressure);
  P10_780torr->AddMaterial(argon, 0.90);
  P10_780torr->AddMaterial(methane, 0.10);
  
  //Epoxy (for FR4)
  epoxy = new G4Material("epoxy", 1.2*g/cm3, 2);
  epoxy->AddElement(H, 2);
  epoxy->AddElement(C, 2);

  //Glass (for FR4)
  SiO2 = new G4Material("SiO2", 2.2*g/cm3, 2);
  SiO2->AddElement(Si, 1);
  SiO2->AddElement(O, 2);
  
  //FR4 (Glass + Epoxy)
  density = 1.85*g/cm3;
  FR4 = new G4Material("FR4", density, 2);
  FR4->AddMaterial(SiO2, 0.528);
  FR4->AddMaterial(epoxy, 0.472);

  stainless_steel = new G4Material("stainless_steel", 8*g/cm3, 3);
  stainless_steel->AddElement(Fe, 0.74);
  stainless_steel->AddElement(Cr, 0.18);
  stainless_steel->AddElement(Ni, 0.08);

  PEEK = new G4Material("PEEK", 1.320*g/cm3, 3);
  PEEK -> AddElement(C, 21);
  PEEK -> AddElement(H, 18);
  PEEK -> AddElement(O, 3);

  G10 = new G4Material("G10", 1.700*g/cm3, 4);
  G10->AddElement(Si, 1);
  G10->AddElement(O, 2);
  G10->AddElement(C, 3);
  G10->AddElement(H, 3);

}

void ExG4DetectorConstruction::ConstructSDandField()
{
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4String SDname;
  G4VSensitiveDetector* DSSD1SD = new ExG4SD(SDname="/DSSD1");//SensitiveDetectorName
  SDman->AddNewDetector(DSSD1SD);
  logicDSSD1->SetSensitiveDetector(DSSD1SD);//attach SD to a logical volume

  G4VSensitiveDetector* DSSD2SD = new ExG4SD(SDname="/DSSD2");//SensitiveDetectorName
  SDman->AddNewDetector(DSSD2SD);
  logicDSSD2->SetSensitiveDetector(DSSD2SD);

  G4VSensitiveDetector* DSSD3SD = new ExG4SD(SDname="/DSSD3");//SensitiveDetectorName
  SDman->AddNewDetector(DSSD3SD);
  logicDSSD3->SetSensitiveDetector(DSSD3SD);

  G4VSensitiveDetector* QSD1SD = new ExG4SD(SDname="/QSD1");//SensitiveDetectorName
  SDman->AddNewDetector(QSD1SD);
  logicQSD1->SetSensitiveDetector(QSD1SD);//attach SD to a logical volume
}
