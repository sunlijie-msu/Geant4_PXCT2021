#include "ExG4EventAction.hh"
#include "ExG4PrimaryGeneratorAction.hh"
#include "ExG4Analysis.hh"
#include "ExG4Hit.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4UnitsTable.hh"
//#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4Types.hh"
#include "Randomize.hh"
using namespace std;
ExG4EventAction::ExG4EventAction()
: G4UserEventAction(),
  fDHC1ID(-1), fDHC2ID(-1), fDHC3ID(-1), fDHC4ID(-1)
{
    G4RunManager::GetRunManager()->SetPrintProgress(1);
	ofstream outresultfile("out.txt",ios::out);//定义输出文件流对象outbeamfile，以输出方式打开磁盘文件，这里是by run的，也可以在RunAction.cc里打开文件。
    //eFile=new TFile("/home/sun/app/geant/first/ExG4old.root","read"); 
    //histo = new TH1F("histo","histo",100,-100,100);
    G4cout<<"3$ before run, by run, ExG4EventAction::ExG4EventAction()"<<G4endl;
}

ExG4EventAction::~ExG4EventAction()
{
	 //eFile->Close();
	 G4cout<<"10$ after run, by run, ExG4EventAction::~ExG4EventAction()"<<G4endl;
}

void ExG4EventAction::BeginOfEventAction(const G4Event*)
{
	//G4cout<<"(3)$ first in event, by event, ExG4EventAction::BeginOfEventAction(const G4Event*)"<<G4endl;
	if(fDHC1ID==-1||fDHC2ID==-1||fDHC3ID==-1||fDHC4ID==-1)//the initial value of -1 for hits id allows you to be efficient in searching the hits by string: if id==-1 you need to search the collections, if not you already did this opeartion and you can skip it.
    {
      G4SDManager* sdManager = G4SDManager::GetSDMpointer();
      fDHC1ID = sdManager->GetCollectionID("DSSD1/SDCollect");//SensitiveDetectorName,collectionName[0]//按照SDName和HCName获取其HCID赋给fDHCID
      fDHC2ID = sdManager->GetCollectionID("DSSD2/SDCollect");//SensitiveDetectorName,collectionName[0]//按照SDName和HCName获取其HCID赋给fDHCID
	  fDHC3ID = sdManager->GetCollectionID("DSSD3/SDCollect");//SensitiveDetectorName,collectionName[0]//按照SDName和HCName获取其HCID赋给fDHCID
	  fDHC4ID = sdManager->GetCollectionID("QSD1/SDCollect");//SensitiveDetectorName,collectionName[0]//按照SDName和HCName获取其HCID赋给fDHCID
    }//按照SDName retrieve the IDs of the two collections
	//ofstream outresultfile("out.txt",ios::out);//定义输出文件流对象outbeamfile，以输出方式打开磁盘文件，这里是by event的，不建议在这里打开outfile。
}

void ExG4EventAction::EndOfEventAction(const G4Event* event)
{
	//histo = (TH1F*)eFile->Get("h1");
	//G4cout<<histo->GetMean()<<G4endl;
	//G4double dssd1Reso=0.1/2.35;
	//G4double dssd2Reso=0.1/2.35;

  G4HCofThisEvent* hce = event->GetHCofThisEvent();
  if(!hce)
  {
    G4ExceptionDescription msg;
    msg << "No hits collection of this event found. \n";
    G4Exception("ExG4EventAction::EndOfEventAction()","ExG4Cod001",JustWarning,msg);
    return;
  }

  //Get hits collections
  ExG4HitsCollection* dHC1 = static_cast<ExG4HitsCollection*>(hce->GetHC(fDHC1ID));//按照fDHC1ID从hce中取出一个HitsCollection，称为dHC1
  ExG4HitsCollection* dHC2 = static_cast<ExG4HitsCollection*>(hce->GetHC(fDHC2ID));//按照fDHC2ID从hce中取出一个HitsCollection，称为dHC2
  ExG4HitsCollection* dHC3 = static_cast<ExG4HitsCollection*>(hce->GetHC(fDHC3ID));//按照fDHC3ID从hce中取出一个HitsCollection，称为dHC3
  ExG4HitsCollection* dHC4 = static_cast<ExG4HitsCollection*>(hce->GetHC(fDHC4ID));//按照fDHC4ID从hce中取出一个HitsCollection，称为dHC4

//   if(!dHC1)
//   {
//     G4ExceptionDescription msg;
//     msg << " Some of hits collection of this event not found!. \n";
//     G4Exception("ExG4EventAction::EndOfEventAction()","ExG4Code001",JustWarning,msg);
//     return;
//   }
  ofstream outresultfile("out.txt",ios::app);//定义输出文件流对象outbeamfile，以追加方式打开磁盘文件. by event
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();


  if(dHC1)//For DSSD1
  {
	  G4int n_hits=dHC1->entries();//DSSD1SD hit 数
	  //G4cout<<"-----DSSD1---"<<"dHC1 n_hits="<<n_hits<<G4endl;
	  analysisManager->FillH1(0,n_hits);//h1 ID=0, distribution of the number of hits
	  totalEmHit=0;	totalEmE=0;	ih=-100;	jh=-100; tof=-999; length=0; velocity=0;
	  memset(px,0,sizeof(px));
	  memset(py,0,sizeof(py));
	  memset(pz,0,sizeof(pz));
	  memset(dx,0,sizeof(dx));//distance between two step points
	  memset(dt,0,sizeof(dt));//time difference between two step points
	  memset(t,0,sizeof(t));//time stamp of each step point
	  for(G4int i=0;i<n_hits;i++)//Within this loop, the histo are filled by hit, so the number can be much larger than the event number, the nt can only be filled by event (the last hit)
	  {
		  //if(i>0) break; //using this statement to extract the first hit for position check, the energy would be incomplete cuz only the first hit was recorded.
		  ExG4Hit* hit = (*dHC1)[i];//fHitsCollection中第i个hit的信息，有时一个event就产生1个hit，但打出次级粒子会有多个hit
		  //hit->Print();
		  tof = hit->GetTof();
		  G4ThreeVector globalPos=hit->GetPos();
		  ih = globalPos.x()+100;
		  jh = globalPos.y()+100;
		  analysisManager->FillNtupleDColumn(2,ih);//nt ID=2
		  analysisManager->FillNtupleDColumn(3,jh);//nt ID=3
		  analysisManager->FillNtupleDColumn(4,globalPos.z());//nt ID=4
		  analysisManager->FillH2(0,ih,jh);//h2 ID=0
		  eDep=hit->GetE();
		  totalEmHit++;
		  totalEmE += eDep;
		  px[i]=globalPos.x();
		  py[i]=globalPos.y();
		  pz[i]=globalPos.z();
		  t[i]=tof;
		  if(i==0)
		  {
			  dt[i]=t[i];
			  dx[i]=sqrt(px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);
		  }
		  if(i>0&&i<300)
		  {
			  dt[i]=t[i]-t[i-1];
			  dx[i]=sqrt((px[i]-px[i-1])*(px[i]-px[i-1]) + (py[i]-py[i-1])*(py[i]-py[i-1]) + (pz[i]-pz[i-1])*(pz[i]-pz[i-1]));
		  }
		  length+=dx[i];
		  velocity=dx[i]/dt[i];
		  //outresultfile<<"D1_totalEmHit=	"<<totalEmHit<<"	totalEmE=	"<<totalEmE/CLHEP::keV<<"	keV	Er=	"<<111.11-totalEmE/CLHEP::keV<<"	keV	eDep=	"<<eDep/CLHEP::keV<<"	keV	tof=	"<<tof/CLHEP::ns<<"	ns	Pos.x=	"<<globalPos.x()/CLHEP::um<<"	um	Pos.y=	"<<globalPos.y()/CLHEP::um<<"	um	Pos.z=	"<<globalPos.z()/CLHEP::um<<"	um	dx=	"<<dx[i]/CLHEP::um<<"	um	dt=	"<<dt[i]/CLHEP::ns<<"	ns	v=	"<<velocity/CLHEP::m/ns<<"	m/ns	length=	"<<length/CLHEP::um<<"	um"<<G4endl;
	  }
	  //Outside the loop, the nt are filled by event, so the number of "nt>0" is exactly the event number!, you cannot use if(n>0)Fillnt; here, it's useless.
	  analysisManager->FillNtupleIColumn(0,dHC1->entries());//nt ID=0 filled by event
	  //if(totalEmE>0)	
	  //{
		  //G4double Etemp=totalEmE;
		  //totalEmE=G4RandGauss::shoot(Etemp,dssd1Reso*Etemp);//G4RandGauss::shoot(μ,σ)
	  //}
	  //excitE width should be added in PrimaryGeneratorAction.cc, while detector resolution should be added in EventAction.cc
	  analysisManager->FillH1(3,totalEmE/CLHEP::keV);//h1 ID=3 filled by event. Fill histogram using the values in units of keV. Don't change. 
 	  analysisManager->FillNtupleDColumn(1,totalEmE/CLHEP::keV);//nt ID=1 filled by event
 	  analysisManager->FillNtupleDColumn(5,t[0]);//nt ID=5 filled by event
  }
  
  if(dHC2)//For DSSD2
  {
	  G4int n_hits=dHC2->entries();//DSSD2SD hit 数
	  //G4cout<<"-----DSSD2---"<<"dHC2 n_hits="<<n_hits<<G4endl;
	  analysisManager->FillH1(1,n_hits);//h1 ID=1, distribution of the number of hits
	  totalEmHit=0;	totalEmE=0;	ih=-100;	jh=-100; tof=-999; length=0; velocity=0; ring1_hit=0; ring2_hit=0; ring3_hit=0;
	  memset(px,0,sizeof(px));
	  memset(py,0,sizeof(py));
	  memset(pz,0,sizeof(pz));
	  memset(dx,0,sizeof(dx));//distance between two step points
	  memset(dt,0,sizeof(dt));//time difference between two step points
	  memset(t,0,sizeof(t));//time stamp of each step point
	  for(G4int i=0;i<n_hits;i++)//Within this loop, the histo are filled by hit, so the number can be much larger than the event number, the nt can only be filled by event (the last hit)
	  {
		  //if(i>0) break; //using this statement to extract the first hit for position check, the energy would be incomplete cuz only the first hit was recorded.
		  ExG4Hit* hit = (*dHC2)[i];//fHitsCollection中第i个hit的信息，有时一个event就产生1个hit，但打出次级粒子会有多个hit
		  // hit->Print();
		  tof = hit->GetTof();
		  G4ThreeVector globalPos=hit->GetPos();
		  ih = globalPos.x()+100;
		  jh = globalPos.y()+100;
		  analysisManager->FillNtupleDColumn(8,ih);//nt ID=8
		  analysisManager->FillNtupleDColumn(9,jh);;//nt ID=9
		  analysisManager->FillNtupleDColumn(10,globalPos.z());//nt ID=10
		  analysisManager->FillH2(1,ih,jh);//h2 ID=1
		  eDep=hit->GetE();
		  totalEmHit++;
		  totalEmE += eDep;
		  px[i]=globalPos.x();
		  py[i]=globalPos.y();
		  pz[i]=globalPos.z();
		  t[i]=tof;
		  if(i==0)
		  {
			  dt[i]=t[i];
			  dx[i]=sqrt(px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);
			  //G4cout<<"r=	"<<sqrt(px[i]*px[i] + py[i]*py[i])/CLHEP::mm<<G4endl;
			  if(sqrt(px[i]*px[i] + py[i]*py[i])<7*CLHEP::mm)  //segmented rings
			  {
				  ring1_hit=1;
				  analysisManager->FillNtupleDColumn(25,ih);//nt ID=25
				  analysisManager->FillNtupleDColumn(26,jh);;//nt ID=26
			  }
			  if(sqrt(px[i]*px[i] + py[i]*py[i])>=7*CLHEP::mm&&sqrt(px[i]*px[i] + py[i]*py[i])<10*CLHEP::mm)  //segmented rings
			  {
				  ring2_hit=1;
				  analysisManager->FillNtupleDColumn(28,ih);//nt ID=28
				  analysisManager->FillNtupleDColumn(29,jh);;//nt ID=29
			  }
			  if(sqrt(px[i]*px[i] + py[i]*py[i])>=10*CLHEP::mm&&sqrt(px[i]*px[i] + py[i]*py[i])<13*CLHEP::mm)  //segmented rings
			  {
				  ring3_hit=1;
				  analysisManager->FillNtupleDColumn(31,ih);//nt ID=31
				  analysisManager->FillNtupleDColumn(32,jh);;//nt ID=32
				  //G4cout<<"r=	"<<sqrt(px[i]*px[i] + py[i]*py[i])/CLHEP::mm<<G4endl;
			  }
		  }
		  if(i>0&&i<300)
		  {
			  dt[i]=t[i]-t[i-1];
			  dx[i]=sqrt((px[i]-px[i-1])*(px[i]-px[i-1]) + (py[i]-py[i-1])*(py[i]-py[i-1]) + (pz[i]-pz[i-1])*(pz[i]-pz[i-1]));
		  }
		  length+=dx[i];
		  velocity=dx[i]/dt[i];
		 //outresultfile<<"D2_totalEmHit=	"<<totalEmHit<<"	totalEmE=	"<<totalEmE/CLHEP::keV<<"	keV	Er=	"<<103.448275862-totalEmE/CLHEP::keV<<"	keV	eDep=	"<<eDep/CLHEP::keV<<"	keV	tof=	"<<tof/CLHEP::ns<<"	ns	Pos.x=	"<<globalPos.x()/CLHEP::um<<"	um	Pos.y=	"<<globalPos.y()/CLHEP::um<<"	um	Pos.z=	"<<globalPos.z()/CLHEP::um<<"	um	dx=	"<<dx[i]/CLHEP::um<<"	um	dt=	"<<dt[i]/CLHEP::ns<<"	ns	v=	"<<velocity/CLHEP::m/CLHEP::ns<<"	m/ns	length=	"<<length/CLHEP::um<<"	um"<<G4endl;
	  }
	  //Outside the loop, the nt are filled by event, so the number of "nt>0" is exactly the event number!
	  analysisManager->FillNtupleIColumn(6,dHC2->entries());//nt ID=6
	  //if(totalEmE>0)
	  //{
		  //G4double Etemp=totalEmE;
		  //totalEmE=G4RandGauss::shoot(Etemp,dssd2Reso*Etemp);//G4RandGauss::shoot(μ,σ)
	  //}
	  //excitE width should be added in PrimaryGeneratorAction.cc, while detector resolution should be added in EventAction.cc
	  analysisManager->FillH1(4,totalEmE/CLHEP::keV);//h1 ID=4. Fill histogram using the values in units of keV. Don't change. 
	  analysisManager->FillNtupleDColumn(7,totalEmE/CLHEP::keV);//nt ID=7
	  if(ring1_hit==1) analysisManager->FillNtupleDColumn(24,totalEmE/CLHEP::keV);//nt ID=24  //segmented rings
	  if(ring2_hit==1) analysisManager->FillNtupleDColumn(27,totalEmE/CLHEP::keV);//nt ID=27  //segmented rings
	  if(ring3_hit==1) analysisManager->FillNtupleDColumn(30,totalEmE/CLHEP::keV);//nt ID=30  //segmented rings
	  analysisManager->FillNtupleDColumn(11,tof);;//nt ID=11
  }
  if(dHC3)//For DSSD3 = X-ray detector
  {
	  G4int n_hits=dHC3->entries();//DSSD3SD hit 数
	  //G4cout<<"-----DSSD3---"<<"dHC3 n_hits="<<n_hits<<G4endl;
	  analysisManager->FillH1(2,n_hits);//h1 ID=2, distribution of the number of hits
	  totalEmHit=0;	totalEmE=0;	ih=-100;	jh=-100; tof=-999; length=0; velocity=0;
	  memset(px,0,sizeof(px));
	  memset(py,0,sizeof(py));
	  memset(pz,0,sizeof(pz));
	  memset(dx,0,sizeof(dx));//distance between two step points
	  memset(dt,0,sizeof(dt));//time difference between two step points
	  memset(t,0,sizeof(t));//time stamp of each step point
	  for(G4int i=0;i<n_hits;i++)//Within this loop, the histo are filled by hit, so the number can be much larger than the event number, the nt can only be filled by event (the last hit)
	  {
		  //if(i>0) break; //using this statement to extract the first hit for position check, the energy would be incomplete cuz only the first hit was recorded.
		  ExG4Hit* hit = (*dHC3)[i];//fHitsCollection中第i个hit的信息，有时一个event就产生1个hit，但打出次级粒子会有多个hit
		  // hit->Print();
		  tof = hit->GetTof();
		  G4ThreeVector globalPos=hit->GetPos();
		  ih = globalPos.x()+100;
		  jh = globalPos.y()+100;
		  analysisManager->FillNtupleDColumn(14,ih);//nt ID=14
		  analysisManager->FillNtupleDColumn(15,jh);//nt ID=15
		  analysisManager->FillNtupleDColumn(16,globalPos.z());//nt ID=16
		  analysisManager->FillH2(2,ih,jh);//h2 ID=2
		  eDep=hit->GetE();
		  totalEmHit++;
		  totalEmE += eDep;
		  px[i]=globalPos.x();
		  py[i]=globalPos.y();
		  pz[i]=globalPos.z();
		  t[i]=tof;
		  if(i==0)
		  {
			  dt[i]=t[i];
			  dx[i]=sqrt(px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);
		  }
		  if(i>0&&i<300)
		  {
			  dt[i]=t[i]-t[i-1];
			  dx[i]=sqrt((px[i]-px[i-1])*(px[i]-px[i-1]) + (py[i]-py[i-1])*(py[i]-py[i-1]) + (pz[i]-pz[i-1])*(pz[i]-pz[i-1]));
		  }
		  length+=dx[i];
		  velocity=dx[i]/dt[i];
		  //outresultfile<<"D3_totalEmHit=	"<<totalEmHit<<"	totalEmE=	"<<totalEmE/CLHEP::keV<<"	keV	Er=	"<<111.11-totalEmE/CLHEP::keV<<"	keV	eDep=	"<<eDep/CLHEP::keV<<"	keV	tof=	"<<tof/CLHEP::ns<<"	ns	Pos.x=	"<<globalPos.x()/CLHEP::um<<"	um	Pos.y=	"<<globalPos.y()/CLHEP::um<<"	um	Pos.z=	"<<globalPos.z()/CLHEP::um<<"	um	dx=	"<<dx[i]/CLHEP::um<<"	um	dt=	"<<dt[i]/CLHEP::ns<<"	ns	v=	"<<velocity/CLHEP::m/ns<<"	m/ns	length=	"<<length/CLHEP::um<<"	um"<<G4endl;
	  }
	  //Outside the loop, the nt are filled by event, so the number of "nt>0" is exactly the event number!
	  analysisManager->FillNtupleIColumn(12,dHC3->entries());//nt ID=12
	  if(totalEmE>0.001*CLHEP::MeV)
	  {
		  G4double Etemp=totalEmE;
		  //totalEmE=G4RandGauss::shoot(Etemp,250.0/2.355/1000000.0);//G4RandGauss::shoot(μ,σ)
		  //G4cout<<"Energy_DSSD3=	"<<totalEmE*1000.0<<" keV"<<G4endl;
		  totalEmE=G4RandGauss::shoot(Etemp,250.0/2.355*CLHEP::eV);//G4RandGauss::shoot(μ,σ)
		  //G4cout<<"Energy_DSSD3=	"<<totalEmE/CLHEP::keV<<" keV"<<G4endl;
	  }
	  //excitE width should be added in PrimaryGeneratorAction.cc, while detector resolution should be added in EventAction.cc
	  analysisManager->FillH1(5,totalEmE/CLHEP::keV);//h1 ID=5. Fill histogram using the values in units of keV. Don't change. 
 	  analysisManager->FillNtupleDColumn(13,totalEmE/CLHEP::keV);//nt ID=13
 	  analysisManager->FillNtupleDColumn(17,t[0]);//nt ID=17
  }

  if(dHC4)//For QSD1 = HPGe
  {
	  G4int n_hits=dHC4->entries();//QSD1SD hit 数
	  //G4cout<<"-----DSSD4---"<<"dHC4 n_hits="<<n_hits<<G4endl;
	  analysisManager->FillH1(2,n_hits);//h1 ID=2, distribution of the number of hits
	  totalEmHit=0;	totalEmE=0;	ih=-100;	jh=-100; tof=-999; length=0; velocity=0;
	  memset(px,0,sizeof(px));
	  memset(py,0,sizeof(py));
	  memset(pz,0,sizeof(pz));
	  memset(dx,0,sizeof(dx));//distance between two step points
	  memset(dt,0,sizeof(dt));//time difference between two step points
	  memset(t,0,sizeof(t));//time stamp of each step point
	  for(G4int i=0;i<n_hits;i++)//Within this loop, the histo are filled by hit, so the number can be much larger than the event number, the nt can only be filled by event (the last hit)
	  {
		  //if(i>0) break; //using this statement to extract the first hit for position check, the energy would be incomplete cuz only the first hit was recorded.
		  ExG4Hit* hit = (*dHC4)[i];//fHitsCollection中第i个hit的信息，有时一个event就产生1个hit，但打出次级粒子会有多个hit
		  // hit->Print();
		  tof = hit->GetTof();
		  G4ThreeVector globalPos=hit->GetPos();
		  ih = globalPos.x()+100;
		  jh = globalPos.y()+100;
		  analysisManager->FillNtupleDColumn(20,ih);//nt ID=20
		  analysisManager->FillNtupleDColumn(21,jh);//nt ID=21
		  analysisManager->FillNtupleDColumn(22,globalPos.z());//nt ID=22
		  //analysisManager->FillH2(2,ih,jh);//h2 ID=2
		  eDep=hit->GetE();
		  totalEmHit++;
		  totalEmE += eDep;
		  //G4cout<<"-----DSSD1---"<<"totalEmHit="<<totalEmHit<<" totalEmE="<<totalEmE<<" eDep="<<eDep<<G4endl;
	  }
	  //Outside the loop, the nt are filled by event, so the number of "nt>0" is exactly the event number!
	  analysisManager->FillNtupleIColumn(18,dHC4->entries());//nt ID=18
	  //if(totalEmE>0)
	  //{
		  //G4double Etemp=totalEmE;
		  //totalEmE=G4RandGauss::shoot(Etemp,dssd3Reso*Etemp);//G4RandGauss::shoot(μ,σ)
	  //}
	  //excitE width should be added in PrimaryGeneratorAction.cc, while detector resolution should be added in EventAction.cc
	  //analysisManager->FillH1(6,totalEmE);//h1 ID=6. Fill histogram using the values in units of keV. Don't change. 
	  analysisManager->FillNtupleDColumn(19,totalEmE/CLHEP::keV);//nt ID=19
	  analysisManager->FillNtupleDColumn(23,tof);//nt ID=23
  }
  //G4cout<<analysisManager->GetH1(1)->mean();
  analysisManager->AddNtupleRow();//For all of the above dHC1+2+3+4, this statement can be written only once. Without this statement, all the branches in the tree are empty
  //  tof=G4RandGauss::shoot(tof,0.5);
  //G4cout<<"(4)$ last in event, by event, ExG4EventAction::EndOfEventAction(const G4Event* event)"<<G4endl;
}
