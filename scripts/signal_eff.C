

//// THIS SCRIPT MAKE A PLOT FOR THE SIGNAL EFFICIENCY
//// FOR THREE CATEGORIES NP, HP AND LP

#include "TH1D.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"
#include "TLine.h"
#include "TString.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include <iostream>
#include <TCut.h>
#include <map>
#include "TMap.h"
#include "TGraph.h"
#include <vector>
#include "TPaveText.h"
#include "TLegend.h"


void signal_eff(){

  gROOT->SetStyle("Plain");

  // map to identify the number of events of the sample
  map<int,double > Nevents;

  // map to identify the efficiency mass point
  map<int,double > effNP;
  map<int,double > effHP;
  map<int,double > effLP;

  // map to identify the mass point
  map<int,string > Mass; 

  // map to identify the number of trees   
  map<int, TTree*> trees;

  vector<int> NPevents;

  // a vector to stoted the number of events in HP category (cut tau21<0.45)
  vector<int> HPevents;

  vector<int> LPevents;

  // number of signal samples
  int Nsamples;

  Nsamples = 13; 


  TFile *File0 = TFile::Open("treeEDBR_BulkGrav_ZZ_M600_25ns_v2_CUTS.root");
  TFile *File1 = TFile::Open("treeEDBR_BulkGrav_ZZ_M800_25ns_v2_CUTS.root");
  TFile *File2 = TFile::Open("treeEDBR_BulkGrav_ZZ_M1000_25ns_v2_CUTS.root");
  TFile *File3 = TFile::Open("treeEDBR_BulkGrav_ZZ_M1200_25ns_v2_CUTS.root");
  TFile *File4 = TFile::Open("treeEDBR_BulkGrav_ZZ_M1400_25ns_v2_CUTS.root");
  TFile *File5 = TFile::Open("treeEDBR_BulkGrav_ZZ_M1600_25ns_v2_CUTS.root");
  TFile *File6 = TFile::Open("treeEDBR_BulkGrav_ZZ_M1800_25ns_v2_CUTS.root");
  TFile *File7 = TFile::Open("treeEDBR_BulkGrav_ZZ_M2000_25ns_v2_CUTS.root");
  TFile *File8 = TFile::Open("treeEDBR_BulkGrav_ZZ_M2500_25ns_v2_CUTS.root");
  TFile *File9 = TFile::Open("treeEDBR_BulkGrav_ZZ_M3000_25ns_v2_CUTS.root"); 
  TFile *File10 = TFile::Open("treeEDBR_BulkGrav_ZZ_M3500_25ns_v2_CUTS.root");
  TFile *File11 = TFile::Open("treeEDBR_BulkGrav_ZZ_M4000_25ns_v2_CUTS.root");
  TFile *File12 = TFile::Open("treeEDBR_BulkGrav_ZZ_M4500_25ns_v2_CUTS.root");


  TTree* Tree0 = (TTree*) File0->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree1 = (TTree*) File1->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree2 = (TTree*) File2->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree3 = (TTree*) File3->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree4 = (TTree*) File4->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree5 = (TTree*) File5->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree6 = (TTree*) File6->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree7 = (TTree*) File7->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree8 = (TTree*) File8->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree9 = (TTree*) File9->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree10 = (TTree*) File10->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree11 = (TTree*) File11->Get("treeDumper/EDBRCandidates;1");
  TTree* Tree12 = (TTree*) File12->Get("treeDumper/EDBRCandidates;1");

  trees[0] = Tree0;
  trees[1] = Tree1;
  trees[2] = Tree2;
  trees[3] = Tree3;
  trees[4] = Tree4;
  trees[5] = Tree5;
  trees[6] = Tree6;
  trees[7] = Tree7;
  trees[8] = Tree8;
  trees[9] = Tree9;
  trees[10] = Tree10;
  trees[11] = Tree11;
  trees[12] = Tree12;


  Nevents[0] = 100000;  // for M = 600 GeV
  Nevents[1] = 100000;  // for M = 800 Gev
  Nevents[2] =  96800;  // for M = 1000 GeV
  Nevents[3] = 100000;  // for M = 1200 GeV
  Nevents[4] =  98400;  // for M = 1400 GeV
  Nevents[5] = 100000;  // for M = 1600 Gev
  Nevents[6] =  99800;  // for M = 1800 GeV
  Nevents[7] =  99400;  // for M = 2000 GeV
  Nevents[8] =  94800;  // for M = 2500 GeV
  Nevents[9] =  98600;  // for M = 3000 GeV
  Nevents[10] = 100000; // for M = 3500 GeV
  Nevents[11] = 100000; // for M = 4000 GeV
  Nevents[12] =  99800; // for M = 4500 GeV

  const char *Masa[13] ={"600", "800", "1000", "1200", "1400", "1600", "1800", "2000", "2500", "3000", "3500", "4000", "4500"}; 

/*
  Mass[0] = 600;
  Mass[1] = 800;
  Mass[2] = 1000;
  Mass[3] = 1200;
  Mass[4] = 1400;
  Mass[5] = 1600;
  Mass[6] = 1800;
  Mass[7] = 2000;
  Mass[8] = 2500;
  Mass[9] = 3000;
  Mass[10] = 3500;
  Mass[11] = 4000;
  Mass[12] = 4500;
*/

  TCut base = "candTMass>=600";
  TCut HP = "tau21<0.45 && candTMass>=600";
  TCut LP = "tau21>0.45 && tau21<0.75 && candTMass>=600";

  for (int j=0; j<Nsamples; j++){
           NPevents.push_back(trees[j]->GetEntries(base));
   }

  // the number of events for HP category
  for (int j=0; j<Nsamples; j++){
           HPevents.push_back(trees[j]->GetEntries(HP));
   }


  for (int k=0; k<Nsamples; k++){
           LPevents.push_back(trees[k]->GetEntries(LP));
   }

  // TO MAKE THE PLOT OF THE EFFICIENCY


  TCanvas *c1 = new TCanvas("c1");
  c1->SetGridx();
  c1->SetGridy();

  TH1F *h1 = new TH1F("h1","Signal Efficiency  NP ",13,0,13); 
  h1->SetStats(0);
   
  TH1F *h2 = new TH1F("h2","Signal Efficiency  HP ",13,0,13);
  h2->SetStats(0);
  
  TH1F *h3 = new TH1F("h3","Signal Efficiency  LP ",13,0,13);
  h3->SetStats(0); 


 for (int i=0; i<Nsamples; i++){
//          double Tentries = trees[i]->GetEntries();  
//          std::cout << "the number of entries  "<< Tentries<<std::endl;
//          std::cout << "events in the sample  "<< Nevents[i]<<std::endl;
          effNP[i] = NPevents[i]  / Nevents[i]; 
          effHP[i] = HPevents[i] / Nevents[i];
          effLP[i] = LPevents[i] / Nevents[i];
//          std::cout << "the efficiency  "<< eff[i]<<std::endl; 


          h1->GetXaxis()->SetBinLabel(i+1,Masa[i]);
          h1->SetBinContent(i+1,effNP[i]);
          h2->SetBinContent(i+1,effHP[i]);
          h3->SetBinContent(i+1,effLP[i]);



//          h1->Fill(Mass[i], effNP[i]);
//          h2->Fill(Mass[i], effHP[i]);
//          h3->Fill(Mass[i], effLP[i]);

//          h1->Fill(effNP[i]);
//          h2->Fill(effHP[i]);
//          h3->Fill(effLP[i]);
    }


    h1->GetXaxis()->SetTitle("Graviton Mass (GeV)");
    h1->GetYaxis()->SetTitle("Efficiency");
    h1->GetXaxis()->SetTitleOffset(1.25);
    h1->GetYaxis()->SetTitleOffset(1.25);
    h1->GetXaxis()->SetLabelSize(0.04);
    h1->GetXaxis()->SetRangeUser(0,13);

    h1->GetYaxis()->SetRangeUser(0,0.8);
  
    h1->SetMarkerColor(kRed);
    h1->SetMarkerStyle(20);
    h1->SetMarkerSize(1.0); 
    h1->Draw("P");



    h2->SetMarkerColor(kBlue);
    h2->SetMarkerStyle(20);
    h2->SetMarkerSize(1.0); 
    h2->Draw("PSAME");

    h3->SetMarkerColor(kGreen);
    h3->SetMarkerStyle(20);
    h3->SetMarkerSize(1.0);
    h3->Draw("PSAME");

    TLegend *leg1 = new TLegend(0.2,0.6,0.85,0.9);
    leg1->SetHeader("Signal Efficiency : BulkG #rightarrow ZZ #rightarrow ZhadZinv");
    leg1->SetTextFont(42);
    leg1->SetTextSize(0.045);
    leg1->AddEntry("h1", "No Purity", "p");
    leg1->AddEntry("h2", "High Purity", "p");
    leg1->AddEntry("h3", "Low Purity", "p");
    leg1->Draw();




}

