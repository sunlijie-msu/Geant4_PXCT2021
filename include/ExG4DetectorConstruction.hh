#ifndef ExG4DetectorConstruction_h
#define ExG4DetectorConstruction_h

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4NistManager.hh"
#include "G4FieldManager.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh" 
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "G4VSensitiveDetector.hh"
#include "globals.hh"
#include "G4ios.hh"
#include "ExG4SD.hh"
#include <vector>

class G4VPhysicalVolume;
class G4Material;
class G4VSensitiveDetector;
class G4VisAttributes;
class G4GenericMessenger;

//Detector construction
class ExG4DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    ExG4DetectorConstruction();
    virtual ~ExG4DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();
    
    void ConstructMaterials();

private:
	G4VPhysicalVolume* physiDSSD1;
	G4VPhysicalVolume* physiDSSD2;
	G4VPhysicalVolume* physiDSSD3;
	G4VPhysicalVolume* physiQSD1;
	G4VPhysicalVolume* physiQSD2;
	//G4VPhysicalVolume* fCSIArray;

	G4LogicalVolume* logicDSSD1;
	G4LogicalVolume* logicDSSD2;
	G4LogicalVolume* logicDSSD3;
	G4LogicalVolume* logicQSD1;
	G4LogicalVolume* logicQSD2;

	//Materials
	G4Material* silicon;
	G4Material* germanium;
	G4Material* gold;
	G4Material* iron;
	G4Material* carbon;
	G4Material* csi;
	G4Material* vacuum;
	G4Material* plastic;
	G4Material *P10_780torr;
	G4Material *air;
	G4Material *Ar;
};

#endif
