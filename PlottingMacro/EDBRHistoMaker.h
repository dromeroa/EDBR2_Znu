#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "TH1D.h"
#include "TH2D.h"
#include "TFile.h"
#include "TROOT.h"
#include "TTree.h"
#include "TChain.h"


/// The large arrays that were here are now GONE.
/// Instead, we have this helper that holds the
/// information of all our histograms.

class HistoFactory{
 public:
  std::vector<std::string> vars;
  std::vector<int> nBins;
  std::vector<double> minBin;
  std::vector<double> maxBin;
  void setHisto(std::string s, int n, double min, double max) {
    vars.push_back(s);
    nBins.push_back(n);
    minBin.push_back(min);
    maxBin.push_back(max);
  }
};

/// EDBRHistoMaker is the class that analyzes the flat
/// TTree that comes out from the NTuple dumper module.
/// It doesn't make analysis; it just makes plots.
/// There are a few switches to do different plots:
/// SIGNAL - BACKGROUND,
/// MUON - ELECTRON, etc...

class EDBRHistoMaker {
 public:
  EDBRHistoMaker(TTree *tree=0, 
		 bool wantElectrons=true,
		 bool wantMuons=true,
		 bool wantSideband=true, 
		 bool wantSignal=false,
		 bool wantFullRange=false,
		 int  wantNXJets=1,
		 bool isZZchannel=1);
  virtual ~EDBRHistoMaker();

  /// This is the tree structure. This comes directly from MakeClass
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   
   // Declaration of leaf types
   Int_t           event;
   Int_t           nVtx;
   Double_t        ptVlep;
   Double_t        ptVhad;
   Double_t        yVlep;
   Double_t        yVhad;
   Double_t        phiVlep;
   Double_t        phiVhad;
   Double_t        massVlep;
   Double_t        mtVlep;
   Double_t        massVhad;
   Double_t        tau1;
   Double_t        tau2;
   Double_t        tau3;
   Double_t        tau21;
   Double_t        ptlep1;
   Double_t        ptlep2;
   Double_t        ptjet1;
   Double_t        etalep1;
   Double_t        etalep2;
   Double_t        etajet1;
   Double_t        philep1;
   Double_t        philep2;
   Double_t        phijet1;
   Double_t        met;
   Double_t        metPhi;
   Int_t           lep;
   Int_t           region;
   Int_t           channel;
   Double_t        triggerWeight;
   Double_t        lumiWeight;
   Double_t        pileupWeight;
   Double_t        deltaRleplep;
   Double_t        delPhilepmet;
   Double_t        deltaRlepjet;
   Double_t        delPhijetmet;
   Double_t        candMass;
   Double_t        candTMass;
   Double_t        puweight;
   Int_t           numjets;
   Double_t        massjet1;
   Double_t        softjet1;
   Double_t        prunedjet;
   Double_t        metpt;
   Double_t        metpx;
   Double_t        metpy;
   Double_t        metphi;
   Double_t        HT;
   Double_t        MHT;
   Double_t        MHTx;
   Double_t        MHTy;
   Double_t        metnomu;
   Double_t        deltaPhijetjetabs;
   Double_t        chf;
   Double_t        nhf;
   Double_t        cef;
   Double_t        nef;
   Int_t           nch; 
   Int_t           nconstituents;
   Double_t        sumET;
   Double_t        rawmetpt;
   Double_t        rawmetphi;
   Double_t        rawsumET;  



   TBranch        *b_event;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_ptVlep;   //!
   TBranch        *b_ptVhad;   //!
   TBranch        *b_yVlep;   //!
   TBranch        *b_yVhad;   //!
   TBranch        *b_phiVlep;   //!
   TBranch        *b_phiVhad;   //!
   TBranch        *b_massVlep;   //!
   TBranch        *b_mtVlep;   //!
   TBranch        *b_massVhad;   //!
   TBranch        *b_tau1;   //!
   TBranch        *b_tau2;   //!
   TBranch        *b_tau3;   //!
   TBranch        *b_tau21;   //!
   TBranch        *b_ptlep1;   //!
   TBranch        *b_ptlep2;   //!
   TBranch        *b_ptjet1;   //!
   TBranch        *b_etalep1;   //!
   TBranch        *b_etalep2;   //!
   TBranch        *b_etajet1;   //!
   TBranch        *b_philep1;   //!
   TBranch        *b_philep2;   //!
   TBranch        *b_phijet1;   //!
   TBranch        *b_met;   //!
   TBranch        *b_metPhi;   //!
   TBranch        *b_lep;   //!
   TBranch        *b_region;   //!
   TBranch        *b_channel;   //!
   TBranch        *b_triggerWeight;   //!
   TBranch        *b_lumiWeight;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_deltaRleplep;   //!
   TBranch        *b_delPhilepmet;   //!
   TBranch        *b_deltaRlepjet;   //!
   TBranch        *b_delPhijetmet;   //!
   TBranch        *b_candMass;   //!
   TBranch        *b_candTMass;   //!
   TBranch        *b_numjets;   //!
   TBranch        *b_massjet1;   //!
   TBranch        *b_softjet1;   //!
   TBranch        *b_prunedjet;   //!
   TBranch        *b_metpt;   //!
   TBranch        *b_metpx;   //!
   TBranch        *b_metpy;   //!
   TBranch        *b_metphi;   //!
   TBranch        *b_HT;   //!
   TBranch        *b_MHT;   //!
   TBranch        *b_MHTx;   //!
   TBranch        *b_MHTy;   //!
   TBranch        *b_metnomu;   //!
   TBranch        *b_deltaPhijetjetabs;   //!
   TBranch        *b_chf;  //!
   TBranch        *b_nhf;  //!
   TBranch        *b_cef;  //!
   TBranch        *b_nef;  //!
   TBranch        *b_nch;  //!
   TBranch        *b_nconstituents;  //!
   TBranch        *b_puweight;  //!

   //new
   TBranch        *b_sumET;
   TBranch        *b_rawmetpt;
   TBranch        *b_rawmetphi;
   TBranch        *b_rawsumET;





 // Basic functions directly from MakeClass
  Int_t    GetEntry(Long64_t entry);
  Long64_t LoadTree(Long64_t entry);
  void     Init(TTree *tree);
  void     Loop(std::string outFileName);

  // Our added functions
  void createAllHistos();
  void printAllHistos();
  void saveAllHistos(std::string outFileName);

  void setWantElectrons(bool doele=false){wantElectrons_=doele;}
  void setWantMuons(bool domu=false){wantMuons_=domu;}
  void setWantSideband(bool dosb=false){wantSideband_=dosb;}
  void setWantSignal(bool dosig=false){wantSignal_=dosig;}
  void setWantNXJets(int nxj=1){wantNXJets_=nxj;}
  void setUnitaryWeights(bool setuniw=false){setUnitaryWeights_=setuniw;}
  void setPileupReweight(bool purewei=false){pileupReweight_=purewei;}

  bool eventPassesFlavorCut();
  bool eventPassesLeptonicZPtCut(double ptZll_threshold);
  bool eventPassesHadronicZPtCut(double ptZjj_threshold);
  bool eventPassesLep1PtCut(double ptlep1_threshold);
  bool eventInSidebandRegion();
  bool eventInSignalRegion();
  bool eventPassesRegionCut();
  bool eventPassesCut(double ptZ_threshold, double ptlep1_threshold );
  bool eventPassesVBFCut();

  ////***********************************************************************
  ////                    HERE DEFINE THE Znunu CUTS
  ////***********************************************************************
  bool eventPassesnumJetsCut(int numjets_threshold);
  bool eventPassesdeltaPhiJetCut(double deltaPhiJet_threshold);
  bool eventPassestau21Cut(double tau21_threshold);
  bool eventPassescandTMassCut(double candTMass_threshold);
  bool eventPassesJetMassCut(double jetMass_threshold1, double jetMass_threshold2, double jetMass_threshold3);
  bool eventPasseschfCut(double chf_threshold); // charged hadron fraction
  bool eventPassesnhfCut(double nhf_threshold); // neutral hadron fraction
  bool eventPassesnefCut(double nef_threshold); // neutral electromagnetic fraction
  bool eventPassesnchCut(int nch_threshold); // charged multiplicity 
  bool eventPassescefCut(double cef_threshold); // charged electromagnetic fraction
  bool eventPassesnconstituentsCut(int nconstituents_threshold);  // number of contituents

  //// COMBINATIONS
  bool eventPassesCutZnu1(int numjets_threshold, double deltaPhiJet_threshold, double tau21_threshold, double candTMass_threshold);
  bool eventPassesCutZnu2(double chf_threshold, int nch_threshold, double cef_threshold, int nconstituents_threshold );
  bool eventPassesCutZnu3(double chf_threshold, double nhf_threshold, double nef_threshold, int nch_threshold, double cef_threshold, int nconstituents_threshold );
  bool eventPassesCutZnu4(double massVhad_threshold1, double massVhad_threshold2);




  double deltaPhi(const double& phi1, const double& phi2)
  { 
    double deltaphi = fabs(phi1 - phi2);
    if (deltaphi > 3.141592654) deltaphi = 6.283185308 - deltaphi;
    return deltaphi;
  }

  //  ------------------------------------------------------------

  double deltaEta(const double& eta1, const double& eta2)
  { 
    double deltaeta = fabs(eta1 - eta2);
    return deltaeta;
  }

  //  ------------------------------------------------------------

  double deltaR(const double& eta1, const double& phi1,
		const double& eta2, const double& phi2)
  { 
    double deltaphi = deltaPhi(phi1, phi2);
    double deltaeta = deltaEta(eta1, eta2);
    double deltar = sqrt(deltaphi*deltaphi + deltaeta*deltaeta);
    return deltar;
  }

  int check ( double pt, vector<double> * ptZ  )
  {
    int goodw=1;
    for(unsigned int i =0; i< ptZ->size(); i++)
      {   
	//printf("Comparing %g and %g\n",pt,ptZ->at(i));
	if(pt==ptZ->at(i)) { goodw=0; break;}
	//else {printf("I think they're different\n");}
      }   

    return goodw;
  }

  // Our added variables
  int nVars;
  bool wantElectrons_;
  bool wantMuons_;
  bool wantSideband_;
  bool wantSignal_;
  bool wantFullRange_;
  bool setUnitaryWeights_;
  bool debug_;
  int wantNXJets_;

  double sidebandVHMassLow_;
  double sidebandVHMassHigh_;
  double signalVHMassLow_;
  double signalVHMassHigh_;
  bool isZZchannel_;
  bool pileupReweight_;

  // The histograms
  HistoFactory hs;
  std::map<std::string,TH1D*> theHistograms;
  TH2D *hmjmzz; 
  TH1D *hmzzNEW;
};

void EDBRHistoMaker::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("nVtx",  &nVtx,  &b_nVtx);
   fChain->SetBranchAddress("ptVlep", &ptVlep, &b_ptVlep);
   fChain->SetBranchAddress("ptVhad", &ptVhad, &b_ptVhad);
   fChain->SetBranchAddress("yVlep", &yVlep, &b_yVlep);
   fChain->SetBranchAddress("yVhad", &yVhad, &b_yVhad);
   fChain->SetBranchAddress("phiVlep", &phiVlep, &b_phiVlep);
   fChain->SetBranchAddress("phiVhad", &phiVhad, &b_phiVhad);
   fChain->SetBranchAddress("massVlep", &massVlep, &b_massVlep);
   fChain->SetBranchAddress("mtVlep", &mtVlep, &b_mtVlep);
   fChain->SetBranchAddress("massVhad", &massVhad, &b_massVhad);
   fChain->SetBranchAddress("tau1", &tau1, &b_tau1);
   fChain->SetBranchAddress("tau2", &tau2, &b_tau2);
   fChain->SetBranchAddress("tau3", &tau3, &b_tau3);
   fChain->SetBranchAddress("tau21", &tau21, &b_tau21);
   fChain->SetBranchAddress("ptlep1", &ptlep1, &b_ptlep1);
   fChain->SetBranchAddress("ptlep2", &ptlep2, &b_ptlep2);
   fChain->SetBranchAddress("ptjet1", &ptjet1, &b_ptjet1);
   fChain->SetBranchAddress("etalep1", &etalep1, &b_etalep1);
   fChain->SetBranchAddress("etalep2", &etalep2, &b_etalep2);
   fChain->SetBranchAddress("etajet1", &etajet1, &b_etajet1);
   fChain->SetBranchAddress("philep1", &philep1, &b_philep1);
   fChain->SetBranchAddress("philep2", &philep2, &b_philep2);
   fChain->SetBranchAddress("phijet1", &phijet1, &b_phijet1);
   fChain->SetBranchAddress("met", &met, &b_met);
   fChain->SetBranchAddress("metPhi", &metPhi, &b_metPhi);
   fChain->SetBranchAddress("lep", &lep, &b_lep);
   fChain->SetBranchAddress("region", &region, &b_region);
   fChain->SetBranchAddress("channel", &channel, &b_channel);
   fChain->SetBranchAddress("triggerWeight", &triggerWeight, &b_triggerWeight);
   fChain->SetBranchAddress("lumiWeight", &lumiWeight, &b_lumiWeight);
   fChain->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   fChain->SetBranchAddress("deltaRleplep", &deltaRleplep, &b_deltaRleplep);
   fChain->SetBranchAddress("delPhilepmet", &delPhilepmet, &b_delPhilepmet);
   fChain->SetBranchAddress("deltaRlepjet", &deltaRlepjet, &b_deltaRlepjet);
   fChain->SetBranchAddress("delPhijetmet", &delPhijetmet, &b_delPhijetmet);
   fChain->SetBranchAddress("candMass", &candMass, &b_candMass);
   fChain->SetBranchAddress("candTMass", &candTMass, &b_candTMass);
   fChain->SetBranchAddress("numjets", &numjets, &b_numjets);
   fChain->SetBranchAddress("massjet1", &massjet1, &b_massjet1);
   fChain->SetBranchAddress("softjet1", &softjet1, &b_softjet1);
   fChain->SetBranchAddress("prunedjet", &prunedjet, &b_prunedjet);
   fChain->SetBranchAddress("metpt", &metpt, &b_metpt);
   fChain->SetBranchAddress("metpx", &metpx, &b_metpx);
   fChain->SetBranchAddress("metpy", &metpy, &b_metpy);
   fChain->SetBranchAddress("metphi", &metphi, &b_metphi);
   fChain->SetBranchAddress("HT", &HT, &b_HT);
   fChain->SetBranchAddress("MHT", &MHT, &b_MHT);
   fChain->SetBranchAddress("MHTx", &MHTx, &b_MHTx);
   fChain->SetBranchAddress("MHTy", &MHTy, &b_MHTy);
   fChain->SetBranchAddress("metnomu", &metnomu, &b_metnomu); 
   fChain->SetBranchAddress("deltaPhijetjetabs", &deltaPhijetjetabs, &b_deltaPhijetjetabs);
   fChain->SetBranchAddress("chf", &chf, &b_chf);
   fChain->SetBranchAddress("nhf", &nhf, &b_nhf);
   fChain->SetBranchAddress("cef", &cef, &b_cef);
   fChain->SetBranchAddress("nef", &nef, &b_nef);
   fChain->SetBranchAddress("nch", &nch, &b_nch);
   fChain->SetBranchAddress("nconstituents", &nconstituents, &b_nconstituents);
   //// News
  fChain->SetBranchAddress("sumET", &sumET, &b_sumET);
   fChain->SetBranchAddress("rawmetpt", &rawmetpt, &b_rawmetpt);
   fChain->SetBranchAddress("rawmetphi", &rawmetphi, &b_rawmetphi);
   fChain->SetBranchAddress("rawsumET", &rawsumET, &b_rawsumET);



   

}

EDBRHistoMaker::EDBRHistoMaker(TTree* tree, 
			       bool wantElectrons,
			       bool wantMuons,
			       bool wantSideband,
			       bool wantSignal,
			       bool wantFullRange,
			       int  wantNXJets,
			       bool isZZchannel){
  fChain = 0;

  // Which category do we want to analyze?
  wantElectrons_ = wantElectrons;
  wantMuons_ = wantMuons;
  wantSideband_ = wantSideband;
  wantSignal_ = wantSignal;
  wantFullRange_ = wantFullRange;
  wantNXJets_ = wantNXJets;
  isZZchannel_ = isZZchannel;

  debug_ = true;
  Init(tree);
  createAllHistos();
  printAllHistos();
}

EDBRHistoMaker::~EDBRHistoMaker() {
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}                  

Int_t EDBRHistoMaker::GetEntry(Long64_t entry) {
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}

Long64_t EDBRHistoMaker::LoadTree(Long64_t entry) {
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
  }
  return centry;
}

//-------------------------
// Infrastructure functions
//-------------------------

void EDBRHistoMaker::createAllHistos() {

  /// This part substitutes the big arrays that used to be 
  /// in the beginning of this file.
  /// Much simpler to create histos now: just add them to
  /// hs with hs.setHisto(name,nbins,min,max);
  hs.setHisto("nVtx", 40,0,40);
  hs.setHisto("ptZjj",20,0,2000); // 20 GeV bins
//  hs.setHisto("ptZjj",50,0,2000); // 20 GeV bins
//  hs.setHisto("yZll",56,-2.8,2.8);
  hs.setHisto("yZjj",28,-2.8,2.8);
//  hs.setHisto("phiZll",74,-3.7,3.7);
  hs.setHisto("phiZjj",28,-3.7,3.7);
//  hs.setHisto("massZll",50,50,150); // 2 GeV bins 
  hs.setHisto("massZjj",32,0,600); // 2 GeV bins  
  hs.setHisto("tau21",30,0,1);
  hs.setHisto("numjets", 15, -0.5, 14.5);
//  hs.setHisto("ptlep1",40,0,800); 
//  hs.setHisto("ptlep2",50,0,500);
//  hs.setHisto("ptjet1",50,0,1000);
//  hs.setHisto("etalep1",50,-2.5,2.5);
//  hs.setHisto("etalep2",50,-2.5,2.5);
//  hs.setHisto("etajet1",50,-2.5,2.5);
//  hs.setHisto("philep1",74,-3.7,3.7);
//  hs.setHisto("philep2",74,-3.7,3.7);
//  hs.setHisto("phijet1",74,-3.7,3.7);
//  hs.setHisto("lep",30,-0.5,29.5);
  hs.setHisto("region",5,-1.5,3.5); 
//  hs.setHisto("triggerWeight",50,0,5); 
//  hs.setHisto("lumiWeight",70,0,7);
//  hs.setHisto("pileupWeight",70,0,7);
//  hs.setHisto("deltaRleplep",70,0,3.5); 
//  hs.setHisto("deltaRlepjet",70,0,7); 
//  hs.setHisto("candMass", 40,100,2100); // 50 GeV bins...
  //but to have the signal spread around 4 bins maybe we want 25 GeV bins?
//  hs.setHisto("candTMass", 30,100,2800);
  hs.setHisto("candTMass", 20,500,2500);
//  hs.setHisto("metpt", 30, 0, 1800);
  hs.setHisto("metpt", 20, 0, 2000);
  hs.setHisto("metphi", 30, -3.7, 3.7);
  hs.setHisto("HT", 30, 0, 1600);
  hs.setHisto("MHT", 30, 0, 1600);
  hs.setHisto("deltaPhijetjetabs", 30, 0, 3.7);
  hs.setHisto("chf", 30, 0 ,1.2);
  hs.setHisto("nhf", 30, 0, 1.2);
  hs.setHisto("cef", 30, 0, 1.2);
  hs.setHisto("nef", 30, 0, 1.2);
  hs.setHisto("nch", 30, 0, 100);
  hs.setHisto("nconstituents", 30, 0, 100);

  
  char buffer[256];
  char buffer2[256];

  nVars = hs.vars.size();

  for(int i = 0; i!= nVars; ++i) {
    sprintf(buffer,"h_%s",hs.vars[i].c_str());
    sprintf(buffer2,"%s;%s;Number of events;",hs.vars[i].c_str(),hs.vars[i].c_str());
    TH1D* histogram = new TH1D(buffer,
			       buffer2,
			       hs.nBins[i],
			       hs.minBin[i],
			       hs.maxBin[i]);
    histogram->SetDirectory(0);
    histogram->Sumw2();
    theHistograms[hs.vars[i]] = histogram;
  }

}

void EDBRHistoMaker::printAllHistos() {
  printf("We have %i histograms \n",int(theHistograms.size()));
  typedef std::map<std::string, TH1D*>::iterator it_type;
  for(it_type iterator = theHistograms.begin(); iterator != theHistograms.end(); iterator++) {
    //iterator->second->Print();
    // Repeat if you also want to iterate through the second map.
  }
}

void EDBRHistoMaker::saveAllHistos(std::string outFileName) {

  TFile* outFile = TFile::Open(outFileName.c_str(),"RECREATE");

  for(int i = 0; i!=nVars; ++i) {
    std::string name = hs.vars[i];
    const TH1D* thisHisto = this->theHistograms[name];
    thisHisto->Write();
  }
  outFile->Close();
}

//------------------
// Physics functions
//------------------

bool EDBRHistoMaker::eventPassesFlavorCut(){
  bool passesFlavour = ((lep == 11 and wantElectrons_) or
			(lep == 13 and wantMuons_));

  return passesFlavour;
}


bool EDBRHistoMaker::eventPassesLep1PtCut(double ptlep1_threshold) {
  
  bool pass = false;

  pass = (ptlep1  > ptlep1_threshold);

  return pass;
}

bool EDBRHistoMaker::eventPassesLeptonicZPtCut(double ptZll_threshold){

  bool passesLeptonicZPt = false;

  passesLeptonicZPt = (ptVlep > ptZll_threshold);

  return passesLeptonicZPt;
}

bool EDBRHistoMaker::eventPassesHadronicZPtCut(double ptZjj_threshold){

  bool passesHadronicZPt = false;

  passesHadronicZPt = (ptVlep > ptZjj_threshold);

  return passesHadronicZPt;
}

bool EDBRHistoMaker::eventInSidebandRegion(){

  bool isInSideband = false;

  isInSideband = (region == 0);

  return isInSideband;
}

bool EDBRHistoMaker::eventInSignalRegion(){

  bool isInSignal = false;

  isInSignal = (region == 1);

  return isInSignal;
}

bool EDBRHistoMaker::eventPassesRegionCut(){
  bool isInSideband = eventInSidebandRegion();
  bool isInSignal   = eventInSignalRegion();
  bool passesRegion = ( isInSideband and wantSideband_) or 
                      ( isInSignal   and wantSignal_  )  ;
  if(wantFullRange_) passesRegion = true;
  if(!wantSideband_ and isInSideband) passesRegion = false;
  if(!wantSignal_   and isInSignal)   passesRegion = false;
  return passesRegion;
}

/// An all around cutting function
bool EDBRHistoMaker::eventPassesCut(double ptZ_threshold, double ptlep1_threshold ) {

  bool passesFlavour = eventPassesFlavorCut();
  bool passesRegion  = eventPassesRegionCut();
  bool passesNXJet   = true;
  bool passesLeptonicZPt = eventPassesLeptonicZPtCut(ptZ_threshold);
  bool passesHadronicZPt = eventPassesHadronicZPtCut(ptZ_threshold);
  bool passesLep1Pt  = eventPassesLep1PtCut(ptlep1_threshold);
  //bool passesVBF     = eventPassesVBFCut();
  //bool passesVTag = vTagPurity==0;
  //bool passesMZZ = mZZ>=500.0&&mZZ<1400.0;

  if(false) {
    printf("passesFlavour: %i\n",passesFlavour); 
    printf("passesRegion: %i\n",passesRegion); 
    printf("passesNXJet: %i\n",passesNXJet); 
    printf("passesLeptonicZPt: %i\n",passesLeptonicZPt); 
    printf("passesLep1Pt: %i\n",passesLep1Pt); 
  }

  bool result = 
    passesFlavour &&
    passesRegion &&
    passesNXJet && 
    passesLep1Pt &&
    passesLeptonicZPt &&
    passesHadronicZPt;
  
  return result;
}

////*******************************************************************************
////                               Znunu CUTS
////******************************************************************************


////-------- CUT IN THE JET MASS (BLIND) --------------------------------------
bool EDBRHistoMaker::eventPassesJetMassCut(double jetMass_threshold1, double jetMass_threshold2, double jetMass_threshold3){
     bool pass = false;
     pass = ( (massVhad > jetMass_threshold1) & (massVhad < jetMass_threshold2) || (massVhad > jetMass_threshold3));
     return pass;
} 

////----------- CUT IN THE NUMBER OF ak4Jets------------------------------------
bool EDBRHistoMaker::eventPassesnumJetsCut(int numjets_threshold) {
     bool pass = false;
     pass = (numjets <=  numjets_threshold);
     return pass;
}

////---------- CUT IN DELTA PHI BETWEEN TWO ak4 JETS (for only 2 jets)--------------------
bool EDBRHistoMaker::eventPassesdeltaPhiJetCut(double deltaPhiJet_threshold) {
     bool pass = false;
     pass = (deltaPhijetjetabs <=  deltaPhiJet_threshold || numjets == 1 || numjets == 0);
     return pass;
}

////---------------- CUT IN TAU21 ---------------------------------------------------------
bool EDBRHistoMaker::eventPassestau21Cut(double tau21_threshold) {
     bool pass = false;
     pass = (tau21 <  tau21_threshold );
     return pass;
}

////------------- CUT IN THE TRANSVERSE MASS ----------------------------------------------
bool EDBRHistoMaker::eventPassescandTMassCut(double candTMass_threshold) {
     bool pass = false;
     pass = (candTMass >  candTMass_threshold );
     return pass;
}


////------------- CUT IN THE CHARGED HADRON FRACTION ----------------------------------------------
bool EDBRHistoMaker::eventPasseschfCut(double chf_threshold) {
     bool pass = false;
          pass = (chf >  chf_threshold );
               return pass;
}

////------------- CUT IN THE NEUTRAL HADRON FRACTION ----------------------------------------------
bool EDBRHistoMaker::eventPassesnhfCut(double nhf_threshold) {
     bool pass = false;
          pass = (nhf <  nhf_threshold );
                 return pass;
}

////------------- CUT IN THE NEUTRAL ELECTROMAGNETIC FRACTION ----------------------------------------------
bool EDBRHistoMaker::eventPassesnefCut(double nef_threshold) {
     bool pass = false;
          pass = (nef <  nef_threshold );
                 return pass;
}

////------------- CUT IN CHARGED MULTIPLICITY ----------------------------------------------
bool EDBRHistoMaker::eventPassesnchCut(int nch_threshold) {
     bool pass = false;
          pass = (nch >  nch_threshold );
                 return pass;
}

////------------- CUT IN CHARGED ELECTROMAGNETIC FRACTION -------------------------------------------
bool EDBRHistoMaker::eventPassescefCut(double cef_threshold) {
     bool pass = false;
          pass = (cef <  cef_threshold );
                 return pass;
}

////------------- CUT IN THE NUMBER OF CONSTITUENTS  ------------------------------------------
bool EDBRHistoMaker::eventPassesnconstituentsCut(int nconstituents_threshold) {
     bool pass = false;
          pass = (nconstituents > nconstituents_threshold );
                 return pass;
}



////---------- NEW CUT COMBINING THE OTHERS ------------------------------------------------
bool EDBRHistoMaker::eventPassesCutZnu1(int numjets_threshold, double deltaPhiJet_threshold, double tau21_threshold, double candTMass_threshold ) {
          bool passesdeltaPhiJet  = eventPassesdeltaPhiJetCut(deltaPhiJet_threshold) ;
          bool passesNumJets  = eventPassesnumJetsCut(numjets_threshold);
          bool passestau21 = eventPassestau21Cut(tau21_threshold);
          bool passesTmass = eventPassescandTMassCut(candTMass_threshold);
          if(false) {
                       printf("passesdeltaPhiJet: %i\n",passesdeltaPhiJet);
                       printf("passesNumJets: %i\n",passesNumJets);
                       printf("passesTmass: %i\n",passesTmass);
                       printf("passestau21: %i\n",passestau21);
          }

          bool result =
               passesdeltaPhiJet &&
               passesNumJets &&
               passesTmass &&
               passestau21;

  return result;
}

//// chf, nch, cef, nconstituents
bool EDBRHistoMaker::eventPassesCutZnu2(double chf_threshold, int nch_threshold, double cef_threshold, int nconstituents_threshold ) {
     bool passeschf  = eventPasseschfCut(chf_threshold);
     bool passesnch  = eventPassesnchCut(nch_threshold);
     bool passescef  = eventPassescefCut(cef_threshold);
     bool passesnconstituents  = eventPassesnconstituentsCut(nconstituents_threshold);

     if(false) {
                       printf("passeschf: %i\n",passeschf);
                       printf("passesnch: %i\n",passesnch);
                       printf("passescef: %i\n",passescef);
                       printf("passesnconstituents: %i\n",passesnconstituents);
     }

    bool result =
         passeschf &&
         passesnch &&
         passescef &&
         passesnconstituents;

  return result;
}

//// chf, nhf, nef, nch, cef, nconstituents
bool EDBRHistoMaker::eventPassesCutZnu3(double chf_threshold, double nhf_threshold, double nef_threshold, int nch_threshold, double cef_threshold, int nconstituents_threshold ) {
     bool passeschf  = eventPasseschfCut(chf_threshold);
     bool passesnhf  = eventPassesnhfCut(nhf_threshold);
     bool passesnef  = eventPassesnefCut(nef_threshold);
     bool passesnch  = eventPassesnchCut(nch_threshold);
     bool passescef  = eventPassescefCut(cef_threshold);
     bool passesnconstituents  = eventPassesnconstituentsCut(nconstituents_threshold);
     if(false) {
                       printf("passeschf: %i\n",passeschf);
                       printf("passesnhf: %i\n",passesnhf);
                       printf("passesnef: %i\n",passesnef);
                       printf("passesnch: %i\n",passesnch);
                       printf("passescef: %i\n",passescef);
                       printf("passesnconstituents: %i\n",passesnconstituents);
     }

    bool result =
         passeschf &&
         passesnhf &&
         passesnef &&
         passesnch &&
         passescef &&
         passesnconstituents;

  return result;
}

///----------------------------------------------------------------
/// This is the important function, the loop over all events.
/// Here we fill the histograms according to cuts, weights,
/// and can also filter out events on an individual basis.
///----------------------------------------------------------------
void EDBRHistoMaker::Loop(std::string outFileName){

  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  Long64_t nbytes = 0, nb = 0;

  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    if(jentry%10000==0) std::cout << "Entry num " << jentry << std::endl;

    if(jentry==0){
      //      printf("Entry number %i...\n",(int)jentry);
      float genLumi=1.0/lumiWeight;
      if(genLumi==1.0)genLumi=-1.0;
      if(genLumi!=-1.0) std::cout<<"Lumi of this sample: "<<genLumi <<" /pb"<<std::endl;
      else std::cout<<"Lumi of this sample: xxx /pb (dummy for data)"<<std::endl;
    }

    // We calculate a weight here.
    // THE ACTUAL WEIGHT
    // --------------------------------------------------------------
    double actualWeight = triggerWeight*lumiWeight*pileupWeight;
  //--------------------------------------------------------------- 


    if(setUnitaryWeights_) {
      if(jentry==0)printf("Unitary weights set!\n");
      actualWeight=1.0;
    }
    // We get the histogram from the map by string and fill it.
    // We could wrap all the fills in the this->eventPassesCut()
    // to fill histograms only for the events which pass a given
    // cut (Sideband / SignalRegion, Muon / Electron, 
    // Single / Double jet ...) 

    // Remember: bool eventPassesCut(double ptZ_threshold, double ptlep1_threshold );

    if(eventPassescandTMassCut(500)){

//    if(eventPassesnumJetsCut(2)){

//    if(eventPassesdeltaPhiJetCut(2.8)){ 

    if (eventPassesJetMassCut(20,65,130)){

    //// THE QCD CUTS
//    if(eventPassesCutZnu1(2, 2.7, 0.5, 600)){

    //// THE JET ID CUTS
//    if(eventPassesCutZnu2(0.1, 0, 0.99, 1)){
      
      // In case we need particular events
      //if(candMass>2400.0)
      //cout<<"Found one event with MZZ="<<candMass<<endl;
      
      /*
      double deltaR_LJ = deltaR(etalep1,philep1,etajet1,phijet1);
      double deltaPhi_LJ   = deltaPhi(phijet1,philep1);
      double deltaPhi_JMET = deltaPhi(phijet1,philep2);
      double deltaPhi_JWL  = deltaPhi(phijet1,phiZll); 
      double deltaPhi_LMET = deltaPhi(philep1,philep2);
      double ptLoverJ      = ptlep1/ptjet1;
      */
      
      (theHistograms["nVtx"])->Fill(nVtx,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["ptlep1"])->Fill(ptlep1,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["ptlep2"])->Fill(ptlep2,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["ptjet1"])->Fill(ptjet1,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["etalep1"])->Fill(etalep1,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["etalep2"])->Fill(etalep2,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["etajet1"])->Fill(etajet1,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["philep1"])->Fill(philep1,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["philep2"])->Fill(philep2,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["phijet1"])->Fill(phijet1,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["ptZll"])->Fill(ptVlep,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["ptZjj"])->Fill(ptVhad,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["phiZll"])->Fill(phiVlep,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["phiZjj"])->Fill(phiVhad,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["yZll"])->Fill(yVlep,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["yZjj"])->Fill(yVhad,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["deltaRleplep"])->Fill(deltaRleplep,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["deltaRlepjet"])->Fill(deltaRlepjet,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["massZll"])->Fill(massVlep,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["massZjj"])->Fill(massVhad,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["tau21"])->Fill(tau21,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["candTMass"])->Fill(candTMass,actualWeight);//printf("line number %i\n",__LINE__);
//      (theHistograms["lep"])->Fill(lep,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["region"])->Fill(region,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["numjets"])->Fill(numjets,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["metpt"])->Fill(metpt,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["metphi"])->Fill(metphi,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["HT"])->Fill(HT,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["MHT"])->Fill(MHT,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["deltaPhijetjetabs"])->Fill(deltaPhijetjetabs,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["chf"])->Fill(chf,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["nhf"])->Fill(nhf,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["cef"])->Fill(cef,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["nef"])->Fill(nef,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["nch"])->Fill(nch,actualWeight);//printf("line number %i\n",__LINE__);
      (theHistograms["nconstituents"])->Fill(nconstituents,actualWeight);//printf("line number %i\n",__LINE__);

      }
      
//      }//end if eventPassesCutZnu1

//   }//end if eventPassesCutZnu2

  }
    
  }//end loop over entries
  
  //std::cout<<"From makeHisto: the histo with #vtx has "<<(theHistograms["nVtx"])->GetEntries()<<" entries"<<std::endl;
  this->saveAllHistos(outFileName);
}
