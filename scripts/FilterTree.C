

// Usage: root -b -q FilterTree.C+


#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
#include <iostream>
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"



void FilterTree2() {

   typedef std::vector< std::string >::iterator strVecI;
   std::vector< std::string > EventList_;


//  TFile *oldfile = new TFile("treeEDBR_MET_Run2015D_05Oct2015.root");
  TFile *oldfile = new TFile("treeEDBR_MET_Run2015D_v4.root");
  TTree *oldtree = (TTree*)oldfile->Get("treeDumper/EDBRCandidates");
  Long64_t nentries = oldtree->GetEntries();
  Int_t run, lumisec, event;

  oldtree->SetBranchAddress("run", &run );
  oldtree->SetBranchAddress("lumisec", &lumisec);
  oldtree->SetBranchAddress("event", &event);


  //Create a new file + a clone of old tree in new file
//  TFile *newfile = new TFile("treeEDBR_MET_Run2015D_05Oct2015_Filter.root","recreate");
  TFile *newfile = new TFile("treeEDBR_MET_Run2015D_v4_Filter.root","recreate");
  newfile->mkdir("treeDumper");
  newfile->cd("treeDumper");
  TTree *newtree = oldtree->CloneTree(0);

  // Read from a file

  std::ifstream infile("allfilers.txt"); 

  std::string line;
  while (getline(infile, line)) {
                if (line.empty()) continue;
                EventList_.push_back(line );
    }

   for (Long64_t i=0;i<nentries; i++) {
         oldtree->GetEntry(i);

         std::stringstream thisevent;
         thisevent<<(unsigned int)run<<":"<<(unsigned int)lumisec<<":"<<(unsigned int)event;
         strVecI it = std::lower_bound(EventList_.begin(), EventList_.end(), thisevent.str());
         if (it == EventList_.end() || thisevent.str() < *it) newtree->Fill();
                      
   }           
                            
           

  newtree->Print();
  newtree->AutoSave();
  delete oldfile;
  delete newfile;

}
