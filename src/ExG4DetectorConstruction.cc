#include "ExG4DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"

#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4IntersectionSolid.hh"

#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "G4ios.hh"

ExG4DetectorConstruction::ExG4DetectorConstruction():G4VUserDetectorConstruction(),physiDSSD1(0),physiDSSD2(0),physiLEGe(0),physiSEGe1(0),physiTarget(0),physiChamber(0),silicon(0),germanium(0),gold(0),iron(0),carbon(0),csi(0),vacuum(0)
{}

ExG4DetectorConstruction::~ExG4DetectorConstruction()
{}

G4VPhysicalVolume* ExG4DetectorConstruction::Construct()
{
	ConstructMaterials();
	G4bool checkOverlaps = true;

// 	G4Tubs(const G4String &pname, // name 
// 		G4double pRmin, // inner radius 
// 		G4double pRmax, // outer radius 
// 		G4double pDz, // Z half length 
// 		G4double pSphi, // starting Phi 
// 		G4double pDphi); // segment angl
	
	//Coordinates:
	//upstream -z, downstream +z
	//toward the beam:
	//left -x, right +x
	//up -y, down +y

	//World
	G4VSolid* solidWorld
		= new G4Box("worldBox",2*m,2*m,2*m);
	G4LogicalVolume* logicWorld
		= new G4LogicalVolume(solidWorld,vacuum,"logicWorld");
	G4VPhysicalVolume* physiWorld
		= new G4PVPlacement(0,G4ThreeVector(),logicWorld,"physiWorld",0,false,0,checkOverlaps);

	//DSSD1
	G4VSolid* solidDSSD1
		= new G4Tubs("solidDSSD1",0*mm, 6*mm, 0.010/2.*mm,	0.*deg, 	360.*deg);//DE active area
	logicDSSD1
		= new G4LogicalVolume(solidDSSD1,silicon,"logicDSSD1");
	physiDSSD1
		= new G4PVPlacement(0,G4ThreeVector(0,0,10*mm),logicDSSD1,"physiDSSD1",logicWorld,false,0,checkOverlaps);

	//DSSD1_Chip
	G4VSolid* solidDSSD1_Chip
		= new G4Tubs("solidDSSD1_Chip",6*mm, 8*mm, 0.140/2.*mm,	0.*deg, 	360.*deg);//DE Chip inactive area
	logicDSSD1_Chip
		= new G4LogicalVolume(solidDSSD1_Chip,silicon,"logicDSSD1_Chip");
	physiDSSD1_Chip
		= new G4PVPlacement(0,G4ThreeVector(0,0,10*mm),logicDSSD1_Chip,"physiDSSD1_Chip",logicWorld,false,0,checkOverlaps);

	//DSSD1_Frame
	G4VSolid* solidDSSD1_Frame
		= new G4Tubs("solidDSSD1_Frame",8*mm, 15*mm, 3.47/2.*mm,	0.*deg, 	360.*deg);//DE package
	logicDSSD1_Frame
		= new G4LogicalVolume(solidDSSD1_Frame,FR4,"logicDSSD1_Frame");
	physiDSSD1_Frame
		= new G4PVPlacement(0,G4ThreeVector(0,0,10*mm),logicDSSD1_Frame,"physiDSSD1_Frame",logicWorld,false,0,checkOverlaps);

	//DSSD1_Window_Front
	G4VSolid* solidDSSD1_Window_Front
		= new G4Tubs("solidDSSD1_Window_Front",0*mm, 6*mm, 0.0005/2.*mm,	0.*deg, 	360.*deg);//DE dead layer front
	logicDSSD1_Window_Front
		= new G4LogicalVolume(solidDSSD1_Window_Front,aluminum,"logicDSSD1_Window_Front");
	physiDSSD1_Window_Front
		= new G4PVPlacement(0,G4ThreeVector(0,0,9.99475*mm),logicDSSD1_Window_Front,"physiDSSD1_Window_Front",logicWorld,false,0,checkOverlaps);//10-0.010/2-0.0005/2=9.99475

	//DSSD1_Window_Back
	G4VSolid* solidDSSD1_Window_Back
		= new G4Tubs("solidDSSD1_Window_Back",0*mm, 6*mm, 0.0005/2.*mm,	0.*deg, 	360.*deg);//DE dead layer back
	logicDSSD1_Window_Back
		= new G4LogicalVolume(solidDSSD1_Window_Back,aluminum,"logicDSSD1_Window_Back");
	physiDSSD1_Window_Back
		= new G4PVPlacement(0,G4ThreeVector(0,0,10.00525*mm),logicDSSD1_Window_Back,"physiDSSD1_Window_Back",logicWorld,false,0,checkOverlaps);//10+0.010/2+0.0005/2=10.00525


	//DSSD2
	G4VSolid* solidDSSD2
		= new G4Tubs("solidDSSD2",0*mm, 13*mm, 1.0/2.*mm,	0.*deg, 	360.*deg);//ER active area
	logicDSSD2
		= new G4LogicalVolume(solidDSSD2,silicon,"logicDSSD2");
	physiDSSD2
		= new G4PVPlacement(0,G4ThreeVector(0,0,20*mm),logicDSSD2,"physiDSSD2",logicWorld,false,0,checkOverlaps);

	//DSSD2_Chip
	G4VSolid* solidDSSD2_Chip
		= new G4Tubs("solidDSSD2_Chip",13*mm, 15*mm, 1.0/2.*mm,	0.*deg, 	360.*deg);//ER Chip inactive area
	logicDSSD2_Chip
		= new G4LogicalVolume(solidDSSD2_Chip,silicon,"logicDSSD2_Chip");
	physiDSSD2_Chip
		= new G4PVPlacement(0,G4ThreeVector(0,0,20*mm),logicDSSD2_Chip,"physiDSSD2_Chip",logicWorld,false,0,checkOverlaps);

	//DSSD2_Frame
	G4VSolid* solidDSSD2_Frame
		= new G4Tubs("solidDSSD2_Frame",15*mm, 21.6*mm, 3.2/2.*mm,	0.*deg, 	360.*deg);//ER package
	logicDSSD2_Frame
		= new G4LogicalVolume(solidDSSD2_Frame,FR4,"logicDSSD2_Frame");
	physiDSSD2_Frame
		= new G4PVPlacement(0,G4ThreeVector(0,0,20*mm),logicDSSD2_Frame,"physiDSSD2_Frame",logicWorld,false,0,checkOverlaps);

	//DSSD2_Window_Front
	G4VSolid* solidDSSD2_Window_Front
		= new G4Tubs("solidDSSD2_Window_Front",0*mm, 13*mm, 0.0005/2.*mm,	0.*deg, 	360.*deg);//ER dead layer front
	logicDSSD2_Window_Front
		= new G4LogicalVolume(solidDSSD2_Window_Front,aluminum,"logicDSSD2_Window_Front");
	physiDSSD2_Window_Front
		= new G4PVPlacement(0,G4ThreeVector(0,0,19.49975*mm),logicDSSD2_Window_Front,"physiDSSD2_Window_Front",logicWorld,false,0,checkOverlaps);//20-1.0/2-0.0005/2=19.49975

	//DSSD2_Window_Back
	G4VSolid* solidDSSD2_Window_Back
		= new G4Tubs("solidDSSD2_Window_Back",0*mm, 13*mm, 0.0005/2.*mm,	0.*deg, 	360.*deg);//ER dead layer back
	logicDSSD2_Window_Back
		= new G4LogicalVolume(solidDSSD2_Window_Back,aluminum,"logicDSSD2_Window_Back");
	physiDSSD2_Window_Back
		= new G4PVPlacement(0,G4ThreeVector(0,0,20.50025*mm),logicDSSD2_Window_Back,"physiDSSD2_Window_Back",logicWorld,false,0,checkOverlaps);//20+1.0/2+0.0005/2=20.50025



	//LEGe
	G4VSolid* solidLEGe
		= new G4Tubs("solidLEGe",0.0*mm, 12.6*mm, 10.0/2.*mm,	0.*deg, 	360.*deg); //X-ray detector
	logicLEGe
		= new G4LogicalVolume(solidLEGe,germanium,"logicLEGe");
	physiLEGe
		= new G4PVPlacement(0,G4ThreeVector(0,0,-20.*mm),logicLEGe,"physiLEGe",logicWorld,false,0,checkOverlaps);

	//SEGe1
	G4VSolid* solidSEGe1
		= new G4Tubs("solidSEGe1",0.0*mm, 40.0*mm, 80.0/2.*mm,	0.*deg, 	360.*deg); //HPGe
	logicSEGe1
		= new G4LogicalVolume(solidSEGe1,germanium,"logicSEGe1");
	physiSEGe1 //(78.26+148.9/2)=152.71
		= new G4PVPlacement(0,G4ThreeVector(0,0,92*mm),logicSEGe1,"physiSEGe1",logicWorld,false,0,checkOverlaps);

	//SEGe2
	G4RotationMatrix* RotSEGe2 = new G4RotationMatrix; // Rotates X and Z axes only
	RotSEGe2 -> rotateY(M_PI/2.*rad); // Rotates 90 degrees
	G4VSolid* solidSEGe2
		= new G4Tubs("solidSEGe2",0.0*mm, 40.0*mm, 80.0/2.*mm,	0.*deg, 	360.*deg); //HPGe
	logicSEGe2
		= new G4LogicalVolume(solidSEGe2,germanium,"logicSEGe2");
	physiSEGe2 //(78.26+148.9/2)=152.71
		= new G4PVPlacement(RotSEGe2,G4ThreeVector(92,0,0*mm),logicSEGe2,"physiSEGe2",logicWorld,false,0,checkOverlaps);

	//Target
	G4VSolid* solidTarget
		= new G4Tubs("solidTarget",0.0*mm, 8.0*mm, 1.0/2.*mm,	0.*deg, 	360.*deg); //target
	logicTarget
		= new G4LogicalVolume(solidTarget,mylar,"logicTarget");
	physiTarget
		= new G4PVPlacement(0,G4ThreeVector(0,0,0*mm),logicTarget,"physiTarget",logicWorld,false,0,checkOverlaps);

	//Chamber
// 	G4RotationMatrix* Rot = new G4RotationMatrix; // Rotates X and Z axes only
// 	Rot -> rotateX(M_PI/2.*rad); // Rotates 90 degrees
	G4VSolid* solidChamberBox
		= new G4Box("solidChamberBox",68./2.*mm,68./2.*mm,68./2.*mm); //Chamber
	G4VSolid* solidChamberHollow
		= new G4Box("solidChamberHollow",64./2.*mm,70./2.*mm,64/2.*mm);
	G4SubtractionSolid* solidChamber
		= new G4SubtractionSolid("solidChamber",solidChamberBox, solidChamberHollow, 0, G4ThreeVector(0.,0.,0.));
	logicChamber
		= new G4LogicalVolume(solidChamber,aluminum,"logicChamber");
	physiChamber
		= new G4PVPlacement(0,G4ThreeVector(0,0,0*mm),logicChamber,"physiTarget",logicWorld,false,0,checkOverlaps);


	// visualization attributes ------------------------------------------------
	DetectorVisAtt = new G4VisAttributes(G4Colour::Red());
	logicDSSD1_Frame->SetVisAttributes(DetectorVisAtt);
	DetectorVisAtt = new G4VisAttributes(G4Colour::Blue());
	logicDSSD2_Frame->SetVisAttributes(DetectorVisAtt);
	DetectorVisAtt = new G4VisAttributes(G4Colour::Green());
	logicDSSD1_Chip->SetVisAttributes(DetectorVisAtt);
	DetectorVisAtt = new G4VisAttributes(G4Colour::Green());
	logicDSSD2_Chip->SetVisAttributes(DetectorVisAtt);
	DetectorVisAtt = new G4VisAttributes(G4Colour::Gray());
	logicDSSD1_Window_Front->SetVisAttributes(DetectorVisAtt);
	logicDSSD2_Window_Front->SetVisAttributes(DetectorVisAtt);

	DetectorVisAtt = new G4VisAttributes(G4Colour::Green());
	logicLEGe->SetVisAttributes(DetectorVisAtt);
	DetectorVisAtt = new G4VisAttributes(G4Colour::Cyan());
	logicSEGe1->SetVisAttributes(DetectorVisAtt);
	logicSEGe2->SetVisAttributes(DetectorVisAtt);
	DetectorVisAtt = new G4VisAttributes(G4Colour::Yellow());
	logicTarget->SetVisAttributes(DetectorVisAtt);


	return physiWorld;
	//   	G4Box* solidWorld= new G4Box("solidWorld",0.5*fSizeWorld[0],0.5*fSizeWorld[1],0.5*fSizeWorld[2]);
	//   	G4LogicalVolume* logicWorld= new G4LogicalVolume(solidWorld,vacuum, "logicWorld",0,0,0);
	//   	G4VPhysicalVolume* physiWorld= new G4PVPlacement(0,G4ThreeVector(0,0,0),logicWorld,"physiWorld",0,false,0);
	// 	//NaI
	// 	G4Tubs* solidDSSD1 = new G4Box("solidDSSD1",0.*cm, 5.*cm, 10.*cm, 0.*deg, 360.*deg);
	//     G4LogicalVolume* logicDSSD1= new G4LogicalVolume(solidDSSD1,germanium,"logicDSSD1",0,0,0);
	//     G4VPhysicalVolume* physiDSSD1 = new G4PVPlacement(0,G4ThreeVector(0,0,0),logicDSSD1,"physiDSSD1",logicWorld,false,0);             

	//Sensitive Detector 	
	// 	ybSD *DSSD1SD= new ybSD("DSSD1SD");	
	// 	logicDSSD1->SetSensitiveDetector( DSSD1SD );
	// 	G4SDManager* SDman = G4SDManager::GetSDMpointer();
	// 	SDman->AddNewDetector( DSSD1SD );

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
	
	// vacuum
//	nistManager->FindOrBuildMaterial("G4_Galatic");

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
  SDman->AddNewDetector(DSSD1SD);//向探测器的管理器注册
  logicDSSD1->SetSensitiveDetector(DSSD1SD);//attach SD to a logical volume

  G4VSensitiveDetector* DSSD2SD = new ExG4SD(SDname="/DSSD2");//SensitiveDetectorName
  SDman->AddNewDetector(DSSD2SD);
  logicDSSD2->SetSensitiveDetector(DSSD2SD);

  G4VSensitiveDetector* DSSD3SD = new ExG4SD(SDname="/DSSD3");//SensitiveDetectorName
  SDman->AddNewDetector(DSSD3SD);
  logicLEGe->SetSensitiveDetector(DSSD3SD);

  G4VSensitiveDetector* QSD1SD = new ExG4SD(SDname="/QSD1");//SensitiveDetectorName
  SDman->AddNewDetector(QSD1SD);
  logicSEGe1->SetSensitiveDetector(QSD1SD);//attach SD to a logical volume
}
