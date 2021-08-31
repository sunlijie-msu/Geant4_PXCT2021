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

void ExG4SD::Initialize(G4HCofThisEvent* hce)//ÿ���¼���ʼʱ������
{
  fHitsCollection = new ExG4HitsCollection (SensitiveDetectorName,collectionName[0]);//�½�����Hit����������HitsCollection��ƥ��һ��SD���������HCһ��ID
  if(fHCID<0) fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);//ȡHitsCollection��ID����fHCID
  hce->AddHitsCollection(fHCID,fHitsCollection);//��һ���¼���HCofThisEvent������hce���һ��IDΪfHCID��HitsCollection
  //G4cout<<"(2)[HC"<<fHCID<<"]$ before event, by SD and event, void ExG4SD::Initialize(G4HCofThisEvent* hce)"<<G4endl;
}

G4bool ExG4SD::ProcessHits(G4Step* step, G4TouchableHistory*)//̽�������������ӵ�ÿһ��Step���ʱ�����ã��ռ�������Ϣ
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

  ExG4Hit* hit = new ExG4Hit(worldPos,edep,hitTime);//�½�һ��hit�������洢λ������ʱ����Ϣ

  fHitsCollection->insert(hit);//fHitsCollection�ռ�hit��Ϣ

  return true;
}
