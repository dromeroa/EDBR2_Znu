
/* THIS SCRIPT LET US WORK WITH TTREES IN ROOT
   WE WILL TRY TO IMPLEMENT THE COMPLETE ANALYSIS HERE
   THIS FILE WORKS WITH THE RESULTS TREES OF THE EDBR2
   IN CASE YOU HAVE OTHER TREES HAVE TO CHANGES THE NAMES 
   OF THE DIRECTORIES

   AUTHOR : DAVID ROMERO

README
********************************************************************************************************************
 the way to call the file is:

 root -l(-b) Opticuts_base.C+

*******************************************************************************************************************
*/

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


void Opticuts_base(){

   // the number of cuts
   unsigned int  Ncuts;
   // the number of trees
   unsigned int Ntrees;  
   // map to identify the tree
   map<int, TTree*> trees; 
   // map to identify the cuts
   map<int, TCut> cuts;
   // map to identify the weights
   map<int,double > weight;
   // the vector to stored the number of events after the respective cut
   vector<int> eventscuts;
   // the vector to stored the number of events after some cuts 
   vector<int> events0;
   vector<int> events1;
   vector<int> events2;
   vector<int> events3;
   vector<int> events4;
   vector<int> events5;
   vector<int> events6;
   // the vector to store the number of Backgrounds   
   vector<double> numB;
   // the vector to store the number of sqrt(Backgrounds)   
   vector<double> sqrtB; 

   // better histogram  
   gROOT->SetStyle("Plain");
   // the files
   TFile *File1 = TFile::Open("../treeEDBR_QCD_HT-250to500_PHYS14.root");
   TFile *File2 = TFile::Open("../treeEDBR_QCD_HT-250to500ext_PHYS14.root");
   TFile *File3 = TFile::Open("../treeEDBR_QCD_HT-500to1000_PHYS14.root");
   TFile *File4 = TFile::Open("../treeEDBR_QCD_HT-500to1000ext_PHYS14.root");
   TFile *File5 = TFile::Open("../treeEDBR_QCD_HT-1000toInf_PHYS14.root");
   TFile *File6 = TFile::Open("../treeEDBR_QCD_HT-1000toInfext_PHYS14.root");
   TFile *File7 = TFile::Open("../treeEDBR_TTJets_PHYS14.root");
   TFile *File8 = TFile::Open("../treeEDBR_WJetsToLNu_HT-100to200_PHYS14.root");
   TFile *File9 = TFile::Open("../treeEDBR_WJetsToLNu_HT-200to400_PHYS14.root");
   TFile *File10 = TFile::Open("../treeEDBR_WJetsToLNu_HT-400to600_PHYS14.root");
   TFile *File11 = TFile::Open("../treeEDBR_WJetsToLNu_HT-600toInf_PHYS14.root");
   TFile *File12 = TFile::Open("../treeEDBR_ZJetsToNuNu_HT-100to200_PHYS14.root");
   TFile *File13 = TFile::Open("../treeEDBR_ZJetsToNuNu_HT-200to400_PHYS14.root");
   TFile *File14 = TFile::Open("../treeEDBR_ZJetsToNuNu_HT-400to600_PHYS14.root");
   TFile *File15 = TFile::Open("../treeEDBR_ZJetsToNuNu_HT-600toInf_PHYS14.root");
   TFile *File16 = TFile::Open("../treeEDBR_RSGravToZZ_kMpl01_M-1000_PHYS14.root");
   TFile *File17 = TFile::Open("../treeEDBR_RSGravToZZ_kMpl01_M-2000_PHYS14.root");
   // Creates pointers to the Trees
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
   TTree* Tree13 = (TTree*) File13->Get("treeDumper/EDBRCandidates;1");
   TTree* Tree14 = (TTree*) File14->Get("treeDumper/EDBRCandidates;1");
   TTree* Tree15 = (TTree*) File15->Get("treeDumper/EDBRCandidates;1");
   TTree* Tree16 = (TTree*) File16->Get("treeDumper/EDBRCandidates;1");
   TTree* Tree17 = (TTree*) File17->Get("treeDumper/EDBRCandidates;1");
   // Identify the tree 
   trees[0] = Tree1;
   trees[1] = Tree2;
   trees[2] = Tree3;
   trees[3] = Tree4;
   trees[4] = Tree5;
   trees[5] = Tree6;
   trees[6] = Tree7;
   trees[7] = Tree8;
   trees[8] = Tree9;
   trees[9] = Tree10;
   trees[10] = Tree11;
   trees[11] = Tree12;
   trees[12] = Tree13;
   trees[13] = Tree14;
   trees[14] = Tree15;
   trees[15] = Tree16;
   trees[16] = Tree17;  
   // Identify the cuts
   
   TCut basecut1 = "numjets<=2"; 
   TCut basecut2 = "numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0)";
   // esta solo la usamos para llenar la tabla
//   TCut basecut3 = "numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=1.2";
   TCut basecut4 = "numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) &&  tau21<0.5";
   TCut basecut5 = "numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) &&  tau21<0.5 && candTMass>600";
  
   TCut basecut6 = "numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) &&  tau21<0.5 && candTMass>600 && ( (abs(ptVhad - metpt)) / (ptVhad + metpt) ) < 0.15";

   cuts[0] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=2.8");
   cuts[1] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=2.6 ");
   cuts[2] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=2.4");
   cuts[3] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=2.2");
   cuts[4] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=2.0");
   cuts[5] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=1.8");
   cuts[6] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=1.6");
   cuts[7] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=1.4");
   cuts[8] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=1.2");
   cuts[9] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=1.0");
   cuts[10] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=0.8");
   cuts[11] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=0.6");
   cuts[12] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=0.4");
   cuts[13] = TCut("numjets<=2 && ((deltaPhijetjetabs<=2.8 && deltaPhijetjetabs>0) || numjets == 1 || numjets == 0) && deltaphijetmet >=0.2");


   //************************************************************************************************************** 
   //*************     SELECT THE NUMBER OF TREES AND CUTS     *****************************************************
   //***************************************************************************************************************
   Ncuts = 14;
   Ntrees = 17;
  
   //***************************************************************************************************************
   //************* THE NUMBER OF EVENTS BEFORE THE CUT WE WANT TO APPLY ********************************************
   //***************************************************************************************************************
   // the number of events before any cuts
   for (unsigned int j=0; j<Ntrees; j++){
           events0.push_back(trees[j]->GetEntries());
   }
   // the number of events after cut (numjets)
   for (unsigned int j=0; j<Ntrees; j++){
           events1.push_back(trees[j]->GetEntries(basecut1));
   }
   // loop to store the number of events before the cut in deltaPhi, but we
   // have to consider the cut in numjets <= 2 (basecut)
   for (unsigned int j=0; j<Ntrees; j++){
           events2.push_back(trees[j]->GetEntries(basecut2));
   }
  // the number of events after the first cut (numjets + deltaPhijets + deltaPhiJetMet)
//  for (unsigned int j=0; j<Ntrees; j++){
//           events3.push_back(trees[j]->GetEntries(basecut3));
//  }
  // the number of events after the  cut (numjets + deltaPhijets + deltaPhiJetMet + tau21)
  for (unsigned int j=0; j<Ntrees; j++){
           events4.push_back(trees[j]->GetEntries(basecut4));
  } 
  // the number of events after the  cut (numjets + deltaPhijets + deltaPhiJetMet + tau21 + candTMass)
  for (unsigned int j=0; j<Ntrees; j++){
           events5.push_back(trees[j]->GetEntries(basecut5));
  }

// all cuts + jet imbalance - jetmet
  for (unsigned int j=0; j<Ntrees; j++){
           events6.push_back(trees[j]->GetEntries(basecut6));
  }



   // we will verify these numbers:
   cout << "************** NUMBER OF EVENTS BEFORE THE CUT **************************************************"<<endl;
   cout << "************** FROM THE TREE  **************************************************"<<endl;
   cout << " For the tree QCD_HT-250to500 (Tree1), we have        :  " << trees[0]->GetEntries()<<endl;
   cout << " For the tree QCD_HT-250to500ext (Tree2), we have     :  " << trees[1]->GetEntries()<<endl;
   cout << " For the tree QCD_HT-500to1000 (Tree3), we have       :  " << trees[2]->GetEntries()<<endl;
   cout << " For the tree QCD_HT-500to1000ext (Tree4), we have    :  " << trees[3]->GetEntries()<<endl;
   cout << " For the tree QCD_HT-1000toInf (Tree5), we have       :  " << trees[4]->GetEntries()<<endl;
   cout << " For the tree QCD_HT-1000toInfext (Tree6), we have    :  " << trees[5]->GetEntries()<<endl;
cout << "********************************************************************************"<<endl;



   for (unsigned int k=0; k<events0.size(); k++){
          cout << "   the number of events of the Tree " << k+1 << " is   : "  << events0[k] << endl;
   }

   //***************************************************************************************************************
   //************* THE NUMBER OF EVENTS AFTER THE CUT (numjets + deltaPhi) ********************************************
   //***************************************************************************************************************
   // the loop to stored the events of all the trees after we apply the cut
   // here we have a vector with NcutsxNtrees element
   // each tree goes from 0->13,etc ... in the vector
   // REVISAR SI EL ORDEN EN QUE GUARDA LOS ELEMENTOS ES EL CORRECTO
   for (unsigned int j=0; j<Ntrees; j++){
        for (unsigned int i=0; i< Ncuts ; i++){
           // here we stored the number of events which pass the cut : cut[i]  
           eventscuts.push_back(trees[j]->GetEntries(cuts[i]));
        } 
   }  
   cout << "************** NUMBER OF EVENTS AFTER THE CUT **************************************************"<<endl; 
   // the loop to show the the cuts and the number of events
   // we have 238 elements in the vector
   for (unsigned int k=0; k<eventscuts.size(); k++){
        cuts[k+Ncuts] = cuts[k];
        if ( k % Ncuts == 0 || k == 0 ){
            cout << "**********************************************************************************************"<<endl;
            cout << endl;
            cout << "TREE NUMBER "<< (k/Ncuts)+1 << endl;
            cout << endl;
            cout << "the number of events before the cut  :  is " << events2[k/Ncuts]  << endl;
            cout << endl;
            cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
        }
        cout << "After the cut :  " << cuts[k] << "   the number of events is :  " << eventscuts[k] << endl;          
   }                  
 

cout << "************************************************************************************"<<endl;
cout << "*******************     THE WEIGHTS        ********************************************"<<endl;
cout << "************************************************************************************"<<endl;

  //**********************************************************************************
  //**********  HERE WE WILL CALCULATE THE NUMBER OF BACKGROUNDS WITH EACH WIGHT******* 
  //**********************************************************************************
 
   weight[0] = 3029.58191317759;      //QCD_HT_250to500_PHYS14 
   weight[1] = 1003.63283653134;      //QCD_HT_250to500_PHYS14_ext
   weight[2] = 94.483959987421;       //QCD_HT_500to1000_PHYS14
   weight[3] = 24.9571292394764;      //QCD_HT_500to1000_PHYS14_ext
   weight[4] = 6.91900411406723;      //QCD_HT_1000toInf_PHYS14
   weight[5] = 2.04215013442762;      //QCD_HT_1000toInf_PHYS14_ext 
   weight[6] = 0.098057951287211;     //TTJets_20bx25_PHYS14 
   weight[7] = 1.03586573462188;      //WjetsToLNu_HT-100to200_PHYS14 
   weight[8] = 0.286624378023276;     //WjetsToLNu_HT-200to400_PHYS14
   weight[9] = 0.0359501391416702;    //WjetsToLNu_HT-400to600_PHYS14
   weight[10] = 0.0123160100928862;   //WjetsToLNu_HT-600toInf_PHYS14 
   weight[11] = 0.224168662753107;    //ZjetsToNuNu_HT-100to200_PHYS14
   weight[12] = 0.0665131409643086;   //ZjetsToNuNu_HT-200to400_PHYS14
   weight[13] = 0.00811270914415317;  //ZjetsToNuNu_HT-400to600_PHYS14
   weight[14] = 0.00276423303342484;  //ZjetsToNuNu_HT-600toInf_PHYS14
   weight[15] = 0.1202;               //RSM1000 
   weight[16] = 0.0023036579;         //RSM2000 

   for (unsigned int k=0; k<Ncuts; k++){
        double B=0;
        for (unsigned int j=0; j<Ntrees-2; j++){ 
              B += eventscuts[((Ncuts*j)+k)]*weight[j];
        }                
        numB.push_back(B);
        sqrtB.push_back(sqrt(B));
        cout << "the number of background is "  << B  << "  for the cut  " << cuts[k] << endl;
        cout << "the root square of the background is "  << sqrt(B)  << "  for the cut  " << cuts[k] << endl;
   } 


cout << "************************************************************************************"<<endl;
cout << "*******************  THE SIGNAL EFFICIENCY  ********************************************"<<endl;
cout << "************************************************************************************"<<endl;

   //******************************************************************************************************
   //***************  	THE SIGNAL ***********************************************************************
   //******************************************************************************************************

   // this is for MG = 1 TeV
   // the number of events after the basline selections + cut numjets + cut deltaphi(jet,jet)
   vector<double> S_eff1;
   double S1_events =1949 ;
   for (unsigned int j=(Ntrees-2)*Ncuts; j<(Ntrees-1)*Ncuts; j++){ 
       S_eff1.push_back(eventscuts[j]/S1_events);
      cout << "the signal efficiency for MG = 1 TeV is    "  << eventscuts[j]/S1_events   <<  "  "  <<  cuts[j-(Ntrees-2)*Ncuts] <<endl;  
   } 
   // this is for MG = 2 TeV
   // the number of events after the basline selections + cut numjets + cut deltaphi(jet,jet)
   vector<double> S_eff2;
   double S2_events =3455;
   for (unsigned int j=(Ntrees-1)*Ncuts; j<(Ntrees)*Ncuts; j++){
         S_eff2.push_back(eventscuts[j]/S2_events);
         cout << "the signal efficiency  for MG = 2 TeV is    "  << eventscuts[j]/S2_events   <<  "  "  <<  cuts[j-(Ntrees-1)*Ncuts] <<endl;
   }


cout << "************************************************************************************"<<endl;
cout << "*******************  THE PUNZI SIGNIFICANCE   ********************************************"<<endl;
cout << "************************************************************************************"<<endl;

     //******************************************************************************************************
     //***************    THE PUNZI SIGNIFICANCE    ***********************************************************************
     //******************************************************************************************************
           
     vector<double> punzi1;
     vector<double> punzi2; 
     for (unsigned int i=0; i<Ncuts; i++){
           punzi1.push_back( S_eff1[i] / (1 + sqrtB[i]));
           cout << "the punzi significance 1  is    "  << S_eff1[i] / (1 + sqrtB[i])   <<  "  "  <<  cuts[i] <<endl;
     } 
     for (unsigned int i=0; i<Ncuts; i++){
           punzi2.push_back( S_eff2[i] / (1 + sqrtB[i]));
           cout << "the punzi significance 2  is    "  << S_eff2[i] / (1 + sqrtB[i])   <<  "  "  <<  cuts[i] <<endl;
     }

cout << "************************************************************************************"<<endl;
cout << "*******************  ROC CURVE SIGNIFICANCE   ********************************************"<<endl;
cout << "************************************************************************************"<<endl;


     //******************************************************************************************************
     //***************   ROC CURVE SENSITIVITY     ***********************************************************************
     //******************************************************************************************************

     double deno = 0;
     // is Ntrees-2 to consider only background, the last 2 are signals
     for (unsigned int j=0; j<Ntrees-2; j++){
          deno += events2[j]*weight[j];
          cout << "events   : "  << events2[j] <<"  the  weight  " << weight[j] <<endl;
     }
     cout << "the denomintor  is   : "  << deno  << endl; 

    // The efficiency
    vector<double> unmenoseffB;
    
    for (unsigned int j=0; j<Ncuts; j++){
         unmenoseffB.push_back(1-(numB[j]/deno));
         cout << " the efficiency of the background is :  " << numB[j]/deno << " for the cut " << cuts[j] << endl;
         cout << " the efficiency of the signal 1 is :  " << S_eff1[j] << " for the cut " << cuts[j] << endl;  
         cout << " the efficiency of the signal 2 is :  " << S_eff2[j] << " for the cut " << cuts[j] << endl;
         cout << " the product (signal eff)x(1- back eff) for signal 1 for the cut  " << cuts[j] << " es :  " << S_eff1[j]*(1-numB[j]/deno ) << endl; 
         cout << " the product (signal eff)x(1- back eff) for signal 2 for the cut  " << cuts[j] << " es :  " << S_eff2[j]*(1-numB[j]/deno ) << endl;     
    }  

    //*********************************************************************************************************
    //******************************  THE PLOTS  *************************************************************
    //********************************************************************************************************
/*

    // The Punzi Plot---------------------------------------------------------------------------------------
    
   TCanvas *c1 = new TCanvas("c1");
   c1->SetGridx();
   c1->SetGridy();
 
   //The histogram for M = 2 TeV
   TH1F *hotro = new TH1F("hotro","Punzi significance",14,0,14);
   hotro->SetStats(0);
                           
   //The histogram for M = 1 TeV 
   TH1F *h = new TH1F("h","Punzi significance ",14,0,14); 
   h->SetStats(0);
   
   for (unsigned int i=0; i<Ncuts; i++){
          h->Fill(cuts[i], punzi1[i]);
          hotro->Fill(cuts[i], punzi2[i]);
    }  

    h->GetXaxis()->SetTitle("cuts");
    h->GetXaxis()->SetTitleOffset(1.25);
    h->GetXaxis()->SetBinLabel(1,"#Delta #phi #geq 2.8");
    h->GetXaxis()->SetBinLabel(2,"#Delta #phi #geq 2.6");
    h->GetXaxis()->SetBinLabel(3,"#Delta #phi #geq 2.4");
    h->GetXaxis()->SetBinLabel(4,"#Delta #phi #geq 2.2");
    h->GetXaxis()->SetBinLabel(5,"#Delta #phi #geq 2.0");
    h->GetXaxis()->SetBinLabel(6,"#Delta #phi #geq 1.8");
    h->GetXaxis()->SetBinLabel(7,"#Delta #phi #geq 1.6");
    h->GetXaxis()->SetBinLabel(8,"#Delta #phi #geq 1.4");
    h->GetXaxis()->SetBinLabel(9,"#Delta #phi #geq 1.2");
    h->GetXaxis()->SetBinLabel(10,"#Delta #phi #geq 1.0");
    h->GetXaxis()->SetBinLabel(11,"#Delta #phi #geq 0.8");
    h->GetXaxis()->SetBinLabel(12,"#Delta #phi #geq 0.6");
    h->GetXaxis()->SetBinLabel(13,"#Delta #phi #geq 0.4");
    h->GetXaxis()->SetBinLabel(14,"#Delta #phi #geq 0.2");
    h->GetXaxis()->SetLabelSize(0.04);


    // axis Y
    h->GetYaxis()->SetLabelSize(0.03);
    h->GetYaxis()->SetTitleSize(0.03);
    h->GetYaxis()->SetTitleOffset(1.7);
    h->GetYaxis()->SetTitle("P = #frac{ #varepsilon_{S}}{1 + #sqrt{B}}");
                         
    // the market 
    hotro->SetMarkerColor(kBlue);
    hotro->SetMarkerStyle(22);
    hotro->SetMarkerSize(3);
    // for the other plot
    h->SetMarkerColor(kRed);
    h->SetMarkerStyle(8);
    h->SetMarkerSize(2.5); 
    // the draw
    h->GetXaxis()->SetRangeUser(0,14);
    h->GetYaxis()->SetRangeUser(0.018,0.019); 
    h->Draw("P");
    hotro->Draw("PSAME");

      // draw the line in the maximum
      TLine *line1 = new TLine(0,0.0189011,14,0.0189011);
      line1->SetLineColor(kRed);
      line1->SetLineStyle(2);
      line1->SetLineWidth(2);
      line1->Draw();
      double ymax2 = hotro->GetMaximum();
      TLine *line2 = new TLine(0,ymax2,14,ymax2);
      line2->SetLineColor(kBlue);
      line2->SetLineStyle(2);
      line2->SetLineWidth(2);
      line2->Draw();

    // make the texts : title
    TPaveText *pt = new TPaveText(0.5645531,0.2270195,0.8372804,0.281337,"blNDC");
    pt->SetName("title");
    pt->SetBorderSize(0);
    pt->SetFillColor(0);
    pt->SetTextSize(0.05027933);
    TText *text = pt->AddText("Punzi significance");
    pt->Draw();

    pt = new TPaveText(0.09700176,0.9152299,0.3694885,0.9698276,"blNDC");
    pt->SetName("otro");
    pt->SetBorderSize(0);
    pt->SetFillColor(0);
    pt->SetTextSize(0.05027933);
    text = pt->AddText("Work in progress");
    pt->Draw();

    pt = new TPaveText(0.6684303,0.9152299,0.9409171,0.9698276,"blNDC");
    pt->SetName("oreo2");
    pt->SetBorderSize(0);
    pt->SetFillColor(0);
    pt->SetTextSize(0.05027933);
    text = pt->AddText("#sqrt{s} = 13 TeV");
    pt->Draw();

    pt = new TPaveText(0.5584416,0.3224234,0.8304049,0.3767409,"blNDC");
    pt->SetName("cuts");
    pt->SetBorderSize(0);
    pt->SetFillColor(0);
    pt->SetTextSize(0.05027933);
    text = pt->AddText("Cut in #left| #Delta #phi(jet,MET) #right|");
    pt->Draw();

    pt = new TPaveText(0.1558442,0.1371866,0.4461421,0.1915042,"blNDC");
    pt->SetName("oroe2");
    pt->SetBorderSize(0);
    pt->SetFillColor(0);
    pt->SetTextSize(0.05027933);
    text = pt->AddText("CMS simulation");
    pt->Draw(); 

    // The Legend
    TLegend *leg_hist = new TLegend(0.1878307,0.2701149,0.3880071,0.4698276,NULL,"brNDC");
    leg_hist -> SetBorderSize(1);
    leg_hist->SetFillColor(0);
    leg_hist->AddEntry(h,"M_{G} = 1 TeV","P");
    leg_hist->AddEntry(hotro,"M_{G} = 2 TeV","P");
    leg_hist->Draw();


*/

//--------------------------- ROC PLOT-------------------------------------

/*

//
//           // The ROC Plot
//

   TCanvas *c1 = new TCanvas("c1");
   c1->SetGridx();
   c1->SetGridy();

   TGraph *g1 = new TGraph(Ncuts, &S_eff1[0], &unmenoseffB[0]);
   g1->SetFillColor(1);
   g1->SetLineColor(2);
   g1->SetMarkerColor(2);
   g1->SetMarkerStyle(20);
   g1->SetMarkerSize(1.2);

   TGraph *g2 = new TGraph(Ncuts, &S_eff2[0], &unmenoseffB[0]);
   g2->SetFillColor(1);
   g2->SetLineColor(4);
   g2->SetMarkerColor(4);
   g2->SetMarkerStyle(20);
   g2->SetMarkerSize(1.2);
   g2->Draw("acp");
   g1->Draw("PC");


   g2->GetXaxis()->SetTitle("#varepsilon_{S}");
   g2->GetXaxis()->SetTitleSize(0.05);
   g2->GetYaxis()->SetTitle("1 - #varepsilon_{B}");
   g2->GetYaxis()->SetTitleSize(0.05);

   g2->GetXaxis()->SetLimits(0.93,1);
   g2->GetYaxis()->SetRangeUser(0,0.14);

   TPaveText *pt = new TPaveText(0.6615737,0.7869081,0.8319328,0.8426184,"blNDC");
   pt->SetName("otro");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.05232558);
   TText *text = pt->AddText("ROC Curve");
   pt->Draw();

   pt = new TPaveText(0.4705882,0.5630372,0.6103896,0.6189112,"blNDC");
   pt->SetName("otro2");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.04);
   text = pt->AddText("#leftarrow #left| #Delta #phi #right| #geq 2.8");
   pt->Draw();

   pt = new TPaveText(0.4125286,0.6561605,0.4828113,0.7120344,"blNDC");
   pt->SetName("otro3");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.04);
   text = pt->AddText("#leftarrow #left| #Delta #phi #right| #geq 2.8");
   pt->Draw();

   pt = new TPaveText(0.6745607,0.6922006,0.8449198,0.7479109,"blNDC");
   pt->SetName("a1");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextSize(0.05232558);
   text = pt->AddText("Cut in #left| #Delta #phi (Jet,MET)#right|");
   pt->Draw();

    TLegend *leg_hist = new TLegend(0.1512605,0.3280802,0.3514133,0.5286533,NULL,"brNDC");
    leg_hist -> SetBorderSize(1);
    leg_hist->SetFillColor(0);
    leg_hist->AddEntry(g1,"M_{G} = 1 TeV","P");
    leg_hist->AddEntry(g2,"M_{G} = 2 TeV","P");
    leg_hist->Draw();

    pt = new TPaveText(0.09700176,0.9152299,0.3694885,0.9698276,"blNDC");
    pt->SetName("otro");
    pt->SetBorderSize(0);
    pt->SetFillColor(0);
    pt->SetTextSize(0.05027933);
    text = pt->AddText("Work in progress");
    pt->Draw();

    pt = new TPaveText(0.6684303,0.9152299,0.9409171,0.9698276,"blNDC");
    pt->SetName("oreo2");
    pt->SetBorderSize(0);
    pt->SetFillColor(0);
    pt->SetTextSize(0.05027933);
    text = pt->AddText("#sqrt{s} = 13 TeV");
    pt->Draw();


    pt = new TPaveText(0.1558442,0.1371866,0.4461421,0.1915042,"blNDC");
    pt->SetName("oroe2");
    pt->SetBorderSize(0);
    pt->SetFillColor(0);
    pt->SetTextSize(0.05027933);
    text = pt->AddText("CMS simulation");
    pt->Draw();
*/

//***************************************************************************************
   // To Print in the screen a code table in latex  with the relevant information
//***************************************************************************************
cout<<"*********************************************************************************"<< endl;
cout<<" LATEX TABLE ***"<<endl;
cout<<endl;
cout<<endl;
cout<<"\\documentclass{article}"<<endl;
cout<<"\\usepackage{amsmath}"<<endl;
cout<<"\\usepackage{amsfonts}"<<endl;
cout<<"\\usepackage{amssymb}"<<endl;
cout<<"\\usepackage{booktabs}"<<endl;
cout<<"\\begin{document}"<<endl;
cout<<"\\begin{table}[h]"<<endl;
cout<<"\\centering"<<endl;
cout<<"\\renewcommand{\\arraystretch}{2.5}"<<endl;
cout<<"\\begin{tabular}{|c|c|c|c|c|c|c|}"<<endl;
cout<<"\\hline"<<endl;
cout<<"\\textbf{Selection}  &\\multicolumn{2}{|c|}{\\textbf{Signal}} & \\multicolumn{4}{|c|}{\\textbf{Background}} \\\\ "<<endl;
cout<<"\\hline"<<endl;
cout<<" & $M_{G}$ =1 TeV & $M_{G}$= 2 TeV & Z + jets & W + jets & QCD & $t\\bar{t}$ + jets \\\\ "<<endl;
cout<<"\\hline"<<endl; 
cout<<"Baseline Selection  & "<<events0[15]*weight[15] <<" & "<<events0[16]*weight[16] <<"  & "<<events0[11]*weight[11]+events0[12]*weight[12]+events0[13]*weight[13]+events0[14]*weight[14] <<"  & "<<events0[7]*weight[7]+events0[8]*weight[8]+events0[9]*weight[9]+events0[10]*weight[10] <<"  & "<<events0[0]*weight[0]+events0[1]*weight[1]+events0[2]*weight[2]+events0[3]*weight[3]+ events0[4]*weight[4]+ events0[5]*weight[5] <<"  & "<<events0[6]*weight[6] <<" \\\\ "<<endl;
cout<<"\\hline"<<endl;
cout<<"$N_{j} \\leq 2$  & "<<events1[15]*weight[15] <<"  & "<<events1[16]*weight[16]  <<"  & "<<events1[11]*weight[11]+events1[12]*weight[12]+events1[13]*weight[13]+events1[14]*weight[14] <<"  & "<<events1[7]*weight[7]+events1[8]*weight[8]+events1[9]*weight[9]+events1[10]*weight[10] <<"  & "<<events1[0]*weight[0]+events1[1]*weight[1]+events1[2]*weight[2]+events1[3]*weight[3]+ events1[4]*weight[4]+ events1[5]*weight[5] <<"  & "<<events1[6]*weight[6] <<"  \\\\ "<<endl;
cout<<"\\hline "<<endl;
cout<<"$\\left| \\Delta \\Phi( \\text{jet1}, \\text{jet2})\\right| \\leq 2.8 $  & "<<events2[15]*weight[15] <<"  & "<<events2[16]*weight[16]  <<"  & "<<events2[11]*weight[11]+events2[12]*weight[12]+events2[13]*weight[13]+events2[14]*weight[14] <<"  & "<<events2[7]*weight[7]+events2[8]*weight[8]+events2[9]*weight[9]+events2[10]*weight[10] <<"  & "<<events2[0]*weight[0]+events2[1]*weight[1]+events2[2]*weight[2]+events2[3]*weight[3]+ events2[4]*weight[4]+ events2[5]*weight[5] <<"  & "<<events2[6]*weight[6] <<"  \\\\ "<<endl;
cout<<"\\hline "<<endl; 
cout<<"$ \\tau_{21} < 0.5 $  & "<<events4[15]*weight[15] <<"  & "<<events4[16]*weight[16]  <<"  & "<<events4[11]*weight[11]+events4[12]*weight[12]+events4[13]*weight[13]+events4[14]*weight[14] <<"  & "<<events4[7]*weight[7]+events4[8]*weight[8]+events4[9]*weight[9]+events4[10]*weight[10] <<"  &  "<<events4[0]*weight[0]+events4[1]*weight[1]+events4[2]*weight[2]+events4[3]*weight[3]+ events4[4]*weight[4]+ events4[5]*weight[5] <<"  & "<<events4[6]*weight[6] <<"  \\\\ "<<endl;
cout<<"\\hline "<<endl;
cout<<"$ M_{T} > 600 $  & "<<events5[15]*weight[15] <<"  & "<<events5[16]*weight[16]  <<"  & "<<events5[11]*weight[11]+events5[12]*weight[12]+events5[13]*weight[13]+events5[14]*weight[14] <<"  & "<<events5[7]*weight[7]+events5[8]*weight[8]+events5[9]*weight[9]+events5[10]*weight[10] <<"  &  "<<events5[0]*weight[0]+events5[1]*weight[1]+events5[2]*weight[2]+events5[3]*weight[3]+ events5[4]*weight[4]+ events5[5]*weight[5] <<"  & "<<events5[6]*weight[6] <<"  \\\\ "<<endl;
cout<<"\\hline "<<endl;
cout<<"\\hline "<<endl;
cout<<"\\end{tabular} "<<endl;
cout<<"\\end{table}"<<endl;
cout<<"\\end{document}"<<endl;
cout<<endl;
cout<<endl;
cout<<"*********************************************************************************"<< endl;
cout<<" LATEX TABLE ***"<<endl;
cout<<endl;
cout<<endl;


cout<<"*********************************************************************************"<< endl;
cout<<" Print some values to verify our results"<<endl;
cout<<"*********************************************************************************"<< endl;
cout<<" QCD_HT-250to500 eventes after baseline selection        :  "<< events0[0]<<endl;
cout<<" the weight of QCD_HT-250to500                           :  "<< weight[0]<<endl;
cout<<" QCD_HT-250to500ext eventes after baseline selection     :  "<< events0[1]<<endl;
cout<<" the weight of QCD_HT-250to500ext                        :  "<< weight[1]<<endl;
cout<<" QCD_HT-500to1000 eventes after baseline selection       :  "<< events0[2]<<endl;
cout<<" the weight of QCD_HT-500to1000                          :  "<< weight[2]<<endl;
cout<<" QCD_HT-500to1000ext eventes after baseline selection    :  "<< events0[3]<<endl;
cout<<" the weight of QCD_HT-500to1000ext                       :  "<< weight[3]<<endl;
cout<<" QCD_HT-1000toInf eventes after baseline selection       :  "<< events0[4]<<endl;
cout<<" the weight of QCD_HT-1000toInf                          :  "<< weight[4]<<endl;
cout<<" QCD_HT-1000toInfext eventes after baseline selection    :  "<< events0[5]<<endl;
cout<<" the weight of QCD_HT-1000toInfext                       :  "<< weight[5]<<endl;
cout<<"*********************************************************************************"<< endl;
cout<<" the sum of events in  QCD(total)                        :  "<< events0[0] + events0[1] + events0[2] + events0[3] + events0[4] + events0[5]<<endl;
cout<<" the sum of weight events in  QCD(total)                 :  "<< events0[0]*weight[0]+events0[1]*weight[1]+events0[2]*weight[2]+events0[3]*weight[3]+ events0[4]*weight[4]+ events0[5]*weight[5]<<endl;
cout<<"*********************************************************************************"<< endl;
cout<<" QCD_HT-250to500 eventes after baseline+numjets selection         :  "<< events1[0]<<endl;
cout<<" the weight of QCD_HT-250to500                                    :  "<< weight[0]<<endl;
cout<<" QCD_HT-250to500ext eventes after baseline+numjets selection      :  "<< events1[1]<<endl;
cout<<" the weight of QCD_HT-250to500ext                                 :  "<< weight[1]<<endl;
cout<<" QCD_HT-500to1000 eventes after baseline+numjets selection        :  "<< events1[2]<<endl;
cout<<" the weight of QCD_HT-500to1000                                   :  "<< weight[2]<<endl;
cout<<" QCD_HT-500to1000ext eventes after baseline+numjets selection     :  "<< events1[3]<<endl;
cout<<" the weight of QCD_HT-500to1000ext                                :  "<< weight[3]<<endl;
cout<<" QCD_HT-1000toInf eventes after baseline+numjets selection        :  "<< events1[4]<<endl;
cout<<" the weight of QCD_HT-1000toInf                                   :  "<< weight[4]<<endl;
cout<<" QCD_HT-1000toInfext eventes after baseline+numjets selection     :  "<< events1[5]<<endl;
cout<<" the weight of QCD_HT-1000toInfext                                :  "<< weight[5]<<endl;
cout<<"*********************************************************************************"<< endl;
cout<<" the sum of events in  QCD(total)                        :  "<< events1[0] + events1[1] + events1[2] + events1[3] + events1[4] + events1[5]<<endl;
cout<<" the sum of weight events in  QCD(total)                 :  "<< events1[0]*weight[0]+events1[1]*weight[1]+events1[2]*weight[2]+events1[3]*weight[3]+ events1[4]*weight[4]+ events1[5]*weight[5]<<endl;
cout<<"*********************************************************************************"<< endl;
cout<<" QCD_HT-250to500 eventes after baseline+numjets+deltaphijets selection         :  "<< events2[0]<<endl;
cout<<" the weight of QCD_HT-250to500                                                 :  "<< weight[0]<<endl;
cout<<" QCD_HT-250to500ext eventes after baseline+numjets+deltaphijets selection      :  "<< events2[1]<<endl;
cout<<" the weight of QCD_HT-250to500ext                                              :  "<< weight[1]<<endl;
cout<<" QCD_HT-500to1000 eventes after baseline+numjets+deltaphijets selection        :  "<< events2[2]<<endl;
cout<<" the weight of QCD_HT-500to1000                                                :  "<< weight[2]<<endl;
cout<<" QCD_HT-500to1000ext eventes after baseline+numjets+deltaphijets selection     :  "<< events2[3]<<endl;
cout<<" the weight of QCD_HT-500to1000ext                                             :  "<< weight[3]<<endl;
cout<<" QCD_HT-1000toInf eventes after baseline+numjets+deltaphijets selection        :  "<< events2[4]<<endl;
cout<<" the weight of QCD_HT-1000toInf                                                :  "<< weight[4]<<endl;
cout<<" QCD_HT-1000toInfext eventes after baseline+numjets+deltaphijets selection     :  "<< events2[5]<<endl;
cout<<" the weight of QCD_HT-1000toInfext                                             :  "<< weight[5]<<endl;
cout<<"*********************************************************************************"<< endl;
cout<<" the sum of events in  QCD(total)                        :  "<< events2[0] + events2[1] + events2[2] + events2[3] + events2[4] + events2[5]<<endl;
cout<<" the sum of weight events in  QCD(total)                 :  "<< events2[0]*weight[0]+events2[1]*weight[1]+events2[2]*weight[2]+events2[3]*weight[3]+ events2[4]*weight[4]+ events2[5]*weight[5]<<endl;
cout<<"*********************************************************************************"<< endl;



// TURN OFF THIS IF YOU WANT TO MAKE THE OTHER PLOTS (IN THE FUTURE USE A FLAG)
//****************************************************************************************************************************
//--------------  TO MAKE THE HISTOGRAM WITH THE CUTFLOW ---------------------------------------------------------------------
//****************************************************************************************************************************

/*

   TCanvas *c1 = new TCanvas("c1");
   c1->SetLogy();
   c1->SetGridx();



   //QCD
   TH1F *histo3 = new TH1F("QCD","Cut Flow",6,1,7);
   histo3->SetStats(0);
   histo3->Fill(1,(events0[0]*weight[0])+(events0[1]*weight[1])+(events0[2]*weight[2])+(events0[3]*weight[3])+ (events0[4]*weight[4])+ (events0[5]*weight[5]));
   histo3->Fill(2,(events1[0]*weight[0])+(events1[1]*weight[1])+(events1[2]*weight[2])+(events1[3]*weight[3])+ (events1[4]*weight[4])+ (events1[5]*weight[5]));
   histo3->Fill(3,(events2[0]*weight[0])+(events2[1]*weight[1])+(events2[2]*weight[2])+(events2[3]*weight[3])+ (events2[4]*weight[4])+ (events2[5]*weight[5]));
   histo3->Fill(4,(events3[0]*weight[0])+(events3[1]*weight[1])+(events3[2]*weight[2])+(events3[3]*weight[3])+ (events3[4]*weight[4])+ (events3[5]*weight[5]));
   histo3->Fill(5,(events4[0]*weight[0])+(events4[1]*weight[1])+(events4[2]*weight[2])+(events4[3]*weight[3])+ (events4[4]*weight[4])+ (events4[5]*weight[5]));
   histo3->Fill(6,(events5[0]*weight[0])+(events5[1]*weight[1])+(events5[2]*weight[2])+(events5[3]*weight[3])+ (events5[4]*weight[4])+ (events5[5]*weight[5]));
   histo3->GetYaxis()->SetRangeUser(10,12000);
   histo3->GetXaxis()->SetBinLabel(1,"Baseline");
   histo3->GetXaxis()->SetBinLabel(2,"N_{j} #leq 2");
   histo3->GetXaxis()->SetBinLabel(3,"#Delta #Phi_{jj} #leq 2.8");
   histo3->GetXaxis()->SetBinLabel(4,"#Delta #Phi_{jm} #geq 1.2");
   histo3->GetXaxis()->SetBinLabel(5,"#tau_{21} < 0.5");
   histo3->GetXaxis()->SetBinLabel(6,"M_{T} > 600");
   histo3->GetYaxis()->SetTitle("Events");
   histo3->SetLineWidth(2);
   histo3->SetLineColor(kBlue+2);
   histo3->Draw();
   TLegend *leg_hist = new TLegend(0.7513228,0.7960894,0.9514991,0.9972067,NULL,"brNDC");
   leg_hist -> SetBorderSize(1);
   leg_hist->SetFillColor(0);
   leg_hist->AddEntry(histo3,"QCD","l");
 
   

   // Z + jets
   TH1F *histo4 = new TH1F("Z + jets","Cut Flow",6,1,7);
   histo4->SetStats(0);
   histo4->Fill(1,(events0[11]*weight[11])+(events0[12]*weight[12])+(events0[13]*weight[13])+(events0[14]*weight[14]));
   histo4->Fill(2,(events1[11]*weight[11])+(events1[12]*weight[12])+(events1[13]*weight[13])+(events1[14]*weight[14]));
   histo4->Fill(3,(events2[11]*weight[11])+(events2[12]*weight[12])+(events2[13]*weight[13])+(events2[14]*weight[14]));
   histo4->Fill(4,(events3[11]*weight[11])+(events3[12]*weight[12])+(events3[13]*weight[13])+(events3[14]*weight[14]));
   histo4->Fill(5,(events4[11]*weight[11])+(events4[12]*weight[12])+(events4[13]*weight[13])+(events4[14]*weight[14]));
   histo4->Fill(6,(events5[11]*weight[11])+(events5[12]*weight[12])+(events5[13]*weight[13])+(events5[14]*weight[14]));
   histo4->SetLineColor(kGreen+2);
   histo4->SetLineWidth(2);
   histo4->Draw("same");
   leg_hist->AddEntry(histo4,"Z + jets","l");



   // W + jets
   TH1F *histo5 = new TH1F("W + jets","Cut Flow",6,1,7);
   histo5->SetStats(0);
   histo5->Fill(1,events0[7]*weight[7]+events0[8]*weight[8]+events0[9]*weight[9]+events0[10]*weight[10]);
   histo5->Fill(2,events1[7]*weight[7]+events1[8]*weight[8]+events1[9]*weight[9]+events1[10]*weight[10]);
   histo5->Fill(3,events2[7]*weight[7]+events2[8]*weight[8]+events2[9]*weight[9]+events2[10]*weight[10]);
   histo5->Fill(4,events3[7]*weight[7]+events3[8]*weight[8]+events3[9]*weight[9]+events3[10]*weight[10]);
   histo5->Fill(5,events4[7]*weight[7]+events4[8]*weight[8]+events4[9]*weight[9]+events4[10]*weight[10]);
   histo5->Fill(6,events5[7]*weight[7]+events5[8]*weight[8]+events5[9]*weight[9]+events5[10]*weight[10]);
   histo5->SetLineColor(kRed);
   histo5->SetLineWidth(2);
   histo5->Draw("same");
   leg_hist->AddEntry(histo5,"W + jets","l");


   // ttbar
   TH1F *histo6 = new TH1F("ttbar","Cut Flow",6,1,7);
   histo6->SetStats(0);
   histo6->Fill(1,events0[6]*weight[6]);
   histo6->Fill(2,events1[6]*weight[6]);
   histo6->Fill(3,events2[6]*weight[6]);
   histo6->Fill(4,events3[6]*weight[6]);
   histo6->Fill(5,events4[6]*weight[6]);
   histo6->Fill(6,events5[6]*weight[6]);
   histo6->SetLineWidth(2);
   histo6->SetLineColor(kBlack);
   histo6->Draw("same");
   leg_hist->AddEntry(histo6,"ttbar","l");
   leg_hist->Draw();




*/


/*
   TCanvas *c1 = new TCanvas("c1");
//   c1->SetLogy();
   c1->SetGridx();

// signal 2 TeV
   TH1F *histo1 = new TH1F("signal 2TeV","Cut Flow",6,1,7); 
   histo1->SetStats(0);
   histo1->Fill(1,events0[16]*weight[16] );
   histo1->Fill(2,events1[16]*weight[16] );
   histo1->Fill(3,events2[16]*weight[16] );
   histo1->Fill(4,events3[16]*weight[16] );
   histo1->Fill(5,events4[16]*weight[16] );
   histo1->Fill(6,events5[16]*weight[16] );
   histo1->GetXaxis()->SetBinLabel(1,"Baseline");
   histo1->GetXaxis()->SetBinLabel(2,"N_{j} #leq 2");
   histo1->GetXaxis()->SetBinLabel(3,"#Delta #Phi_{jj} #leq 2.8");
   histo1->GetXaxis()->SetBinLabel(4,"#Delta #phi_{jm} #geq 1.2");
   histo1->GetXaxis()->SetBinLabel(5,"#tau_{21} < 0.5");
   histo1->GetXaxis()->SetBinLabel(6,"M_{T} > 600");
   histo1->GetYaxis()->SetRangeUser(0,10000);
   histo1->GetYaxis()->SetTitle("Events");
   histo1->GetXaxis()->SetTitle("cuts");
   histo1->SetLineColor(kBlue);
   histo1->SetLineWidth(2);
   histo1->Draw();
// signal 1 TeV
   TH1F *histo2 = new TH1F("signal 1TeV","Cut Flow",6,1,7);
   histo2->SetStats(0);
   histo2->Fill(1,events0[15]*weight[15] );
   histo2->Fill(2,events1[15]*weight[15]);
   histo2->Fill(3,events2[15]*weight[15]);
   histo2->Fill(4,events3[15]*weight[15]);
   histo2->Fill(5,events4[15]*weight[15]);
   histo2->Fill(6,events5[15]*weight[15]);
   histo2->SetLineColor(kRed);
   histo2->SetLineWidth(2);
   histo2->Draw("same");

   TLegend *leg_hist = new TLegend(0.7513228,0.7960894,0.9514991,0.9972067,NULL,"brNDC");
   leg_hist -> SetBorderSize(1);
   leg_hist->SetFillColor(0);
   leg_hist->AddEntry(histo1,"Signal 2TeV","l");
   leg_hist->AddEntry(histo2,"Signal 1TeV","l");
   leg_hist->Draw();


   


*/

}// end of script

