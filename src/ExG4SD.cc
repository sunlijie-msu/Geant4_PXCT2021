#include "ExG4SD.hh"
#include "ExG4Hit.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

ExG4SD::ExG4SD(G4String name)
: G4VSensitiveDetector(name), fHitsCollection(0), fHCID(-1)
{
  G4String HCname = "SDCollect";
  collectionName.insert(HCname);
  G4cout<<"4(HC"<<fHCID<<")$ before run, by run and SD, ExG4SD::ExG4SD(G4String name)"<<G4endl;
}

ExG4SD::~ExG4SD()
{
	G4cout<<"9(HC"<<fHCID<<")$ after run, by run and SD ExG4SD::~ExG4SD()"<<G4endl;
}

void ExG4SD::Initialize(G4HCofThisEvent* hce)//每个事件开始时被调用
{
  fHitsCollection = new ExG4HitsCollection (SensitiveDetectorName,collectionName[0]);//新建保存Hit的容器，即HitsCollection，匹配一个SD，分配给该HC一个ID
  if(fHCID<0) fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);//取HitsCollection的ID赋给fHCID
  hce->AddHitsCollection(fHCID,fHitsCollection);//向一个事件的HCofThisEvent大容器hce添加一个ID为fHCID的HitsCollection
  //G4cout<<"(2)[HC"<<fHCID<<"]$ before event, by SD and event, void ExG4SD::Initialize(G4HCofThisEvent* hce)"<<G4endl;
}

G4bool ExG4SD::ProcessHits(G4Step* step, G4TouchableHistory*)//探测器区域内粒子的每一个Step完成时被调用，收集粒子信息
{
	//G4cout<<"(3)[1]$ first in hit, by SD and hit, G4bool ExG4SD::ProcessHits(G4Step* step, G4TouchableHistory*)"<<G4endl;
  G4double edep = step->GetTotalEnergyDeposit();
  if(edep==0.) return true;
  //G4StepPoint* preStepPoint = step->GetPreStepPoint();//modify
  G4StepPoint* preStepPoint = step->GetPostStepPoint();//modify

  //G4TouchableHistory* touchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  //G4int copyNo;
  //copyNo=touchable->GetVolume()->GetCopyNo();
  
  G4ThreeVector worldPos = preStepPoint->GetPosition();
  G4double hitTime = preStepPoint->GetGlobalTime();

  ExG4Hit* hit = new ExG4Hit(worldPos,edep,hitTime);//新建一个hit容器，存储位置能量时间信息

  fHitsCollection->insert(hit);//fHitsCollection收集hit信息

  return true;
}
