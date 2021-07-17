#include "ExG4RunAction.hh"
#include "ExG4Analysis.hh"
#include "G4Run.hh"
#include "G4UnitsTable.hh"
//#include "G4SystemOfUnits.hh"
#include <iostream>
#include <fstream>
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
using namespace std;
ExG4RunAction::ExG4RunAction()
: G4UserRunAction()
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  G4cout<<"2$ before run, by run, ExG4RunAction::ExG4RunAction() Using "<<analysisManager->GetType()<<G4endl;

  analysisManager->SetVerboseLevel(1);
  //analysisManager->SetFileName("ExG4");//root filename

  //Book histograms, ntuple
  //

  analysisManager->CreateH1("h1DSSD1n","h1DSSD1n",10,0.,10.); // h1 ID=0, the range may be not suitable, the results are subject to nt
  analysisManager->CreateH1("h1DSSD2n","h1DSSD2n",10,0.,10.); // h1 ID=1, the range may be not suitable, the results are subject to nt
  analysisManager->CreateH1("h1DSSD3n","h1DSSD3n",10,0.,10.); // h1 ID=2, the range may be not suitable, the results are subject to nt
  analysisManager->CreateH1("h1DSSD1e","h1DSSD1e",60000,0.,60000); // h1 ID=3//6000 is range, in what unit is defined in FillH1
  analysisManager->CreateH1("h1DSSD2e","h1DSSD2e",60000,0.,60000); // h1 ID=4//6000 is range, in what unit is defined in FillH1
  analysisManager->CreateH1("h1DSSD3e","h1DSSD3e",60000,0.,60000); // h1 ID=5//6000 is range, in what unit is defined in FillH1
  analysisManager->CreateH2("DSSD1XY","DSSD1XY",80,80.,120.,80,80.,120.); // h2 ID = 0
  analysisManager->CreateH2("DSSD2XY","DSSD2XY",80,80.,120.,80,80.,120.); // h2 ID = 1
  analysisManager->CreateH2("DSSD3XY","DSSD3XY",80,80.,120.,80,80.,120.); // h2 ID = 2
  //CreatH1(name,title,nbins,vmin,vmax)
  //analysisManager/h1set hID nxbin xmin xmax [xunit] [xfcn] [xfcn] [binscheme]
  //analysisManager/h2set hID nxbin xmin xmax xunit xfcn nybin ymin ymax yunit yfcn
  //histogram IDs are attributed automatically. 1D and 2D histograms IDs are defined independently

  analysisManager->CreateNtuple("tree","tree");
  analysisManager->CreateNtupleIColumn("DSSD1n"); //nt ID = 0
  analysisManager->CreateNtupleDColumn("DSSD1e"); //nt ID = 1
  analysisManager->CreateNtupleDColumn("DSSD1x");  //nt ID = 2
  analysisManager->CreateNtupleDColumn("DSSD1y");  //nt ID = 3
  analysisManager->CreateNtupleDColumn("DSSD1z");  //nt ID = 4
  analysisManager->CreateNtupleDColumn("DSSD1t");  //nt ID = 5

  analysisManager->CreateNtupleIColumn("DSSD2n"); //nt ID = 6
  analysisManager->CreateNtupleDColumn("DSSD2e"); //nt ID = 7
  analysisManager->CreateNtupleDColumn("DSSD2x");  //nt ID = 8
  analysisManager->CreateNtupleDColumn("DSSD2y");  //nt ID = 9
  analysisManager->CreateNtupleDColumn("DSSD2z");  //nt ID = 10
  analysisManager->CreateNtupleDColumn("DSSD2t");  //nt ID = 11

  analysisManager->CreateNtupleIColumn("DSSD3n"); //nt ID = 12
  analysisManager->CreateNtupleDColumn("DSSD3e"); //nt ID = 13
  analysisManager->CreateNtupleDColumn("DSSD3x");  //nt ID = 14
  analysisManager->CreateNtupleDColumn("DSSD3y");  //nt ID = 15
  analysisManager->CreateNtupleDColumn("DSSD3z");  //nt ID = 16
  analysisManager->CreateNtupleDColumn("DSSD3t");  //nt ID = 17
  
  analysisManager->CreateNtupleIColumn("QSD1n"); //nt ID = 18
  analysisManager->CreateNtupleDColumn("QSD1e"); //nt ID = 19
  analysisManager->CreateNtupleDColumn("QSD1x");  //nt ID = 20
  analysisManager->CreateNtupleDColumn("QSD1y");  //nt ID = 21
  analysisManager->CreateNtupleDColumn("QSD1z");  //nt ID = 22
  analysisManager->CreateNtupleDColumn("QSD1t");  //nt ID = 23

  analysisManager->CreateNtupleDColumn("DSSD2_Ring1e"); //nt ID = 24
  analysisManager->CreateNtupleDColumn("DSSD2_Ring1x");  //nt ID = 25
  analysisManager->CreateNtupleDColumn("DSSD2_Ring1y");  //nt ID = 26
  analysisManager->CreateNtupleDColumn("DSSD2_Ring2e"); //nt ID = 27
  analysisManager->CreateNtupleDColumn("DSSD2_Ring2x");  //nt ID = 28
  analysisManager->CreateNtupleDColumn("DSSD2_Ring2y");  //nt ID = 29
  analysisManager->CreateNtupleDColumn("DSSD2_Ring3e"); //nt ID = 30
  analysisManager->CreateNtupleDColumn("DSSD2_Ring3x");  //nt ID = 31
  analysisManager->CreateNtupleDColumn("DSSD2_Ring3y");  //nt ID = 32

}

ExG4RunAction::~ExG4RunAction()
{
	G4cout<<"7$ after run, by run,ExG4RunAction::~ExG4RunAction()"<<G4endl;
	delete G4AnalysisManager::Instance();
}

void ExG4RunAction::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile("ExG4");//output root file
  //ofstream outresultfile("out.txt",ios::out);//定义输出文件流对象outbeamfile，以输出方式打开磁盘文件，这里是by run的。
  G4cout<<"5$ first in run, by run, ExG4RunAction::BeginOfRunAction(const G4Run*)"<<G4endl;
}

void ExG4RunAction::EndOfRunAction(const G4Run*)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  //G4cout<<analysisManager->GetH1(2)->mean()<<G4endl;
  analysisManager->Write();
  analysisManager->CloseFile();
  G4cout<<"6$ last in run, by run, ExG4RunAction::EndOfRunAction(const G4Run*)"<<G4endl;
}
