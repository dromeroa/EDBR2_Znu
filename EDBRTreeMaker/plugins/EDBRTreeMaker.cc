// system include files
#include <iostream>
#include <memory>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "RecoEgamma/EgammaTools/interface/EffectiveAreas.h"

#include "EDBRChannels.h"
#include "TAxis.h"
#include "TEfficiency.h"
#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TTree.h"

////---- JEC
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "PhysicsTools/PatAlgos/plugins/JetCorrFactorsProducer.h"

#include "TLorentzVector.h"
#include "TMath.h"

////------TRIGGER
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

//
// class declaration
//

class EDBRTreeMaker : public edm::EDAnalyzer {
public:
  explicit EDBRTreeMaker(const edm::ParameterSet&);
  ~EDBRTreeMaker();
  
private:
  virtual void beginJob() override;
  virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
  virtual void endJob() override;

//******************************************************************
//************************* MEMBER DATA ****************************
//******************************************************************
  edm::Service<TFileService> fs;
  TTree* outTree_;

  //------------------------ GENERAL ----------------------------------------------
  int nVtx;
  int numCands;
  int nevent, run, lumisec;
  int channel, lep, reg;
  double triggerWeight, lumiWeight, pileupWeight;

  bool isGen_;
  bool isData_; 
  int originalNEvents_;
  double crossSectionPb_;
  double targetLumiInvPb_;
  std::string EDBRChannel_;
  std::string gravitonSrc_, metSrc_;
  edm::EDGetTokenT<reco::VertexCollection> vertexToken_;
  edm::EDGetTokenT<edm::View<pat::MET> > metnohfToken_;
  edm::EDGetTokenT<pat::JetCollection> jetToken_;

  //------------------------ V quantities ------------------------------------------
  double ptVlep, ptVhad, yVlep, yVhad, phiVlep, phiVhad, massVlep, massVhad, mtVlep;

  //------------------------- MET ---------------------------------------------------
  double met, metPhi;

  //-----------------------MET FROM GRAVITON ----------------------------------------
  double metpt, metphi, metpx, metpy, metnomu;
  double sumET, rawmetpt, rawmetphi, rawsumET, genmetpt, genmetphi, calometpt, calometphi, calometsumET;
  //---------------------- AK8 JETS --------------------------------------------------
  int    numfatjets;
  double tau1,     tau2,     tau3,     tau21;
  double etjet1,   ptjet1,   etajet1,  phijet1;
  double massjet1, softjet1, prunedjet1;

 //Recipe to apply JEC to the pruned jet mass:
 ////https://twiki.cern.ch/twiki/bin/view/CMS/JetWtagging#Recipes_to_apply_JEC_on_the_prun
 std::string payload_;
 double prunedMassCorrection( double, double, const pat::Jet&, edm::ESHandle<JetCorrectorParametersCollection> ); 

       //------------------ AK8 JET ID VARIABLES------------------------------------
  double chf, nhf, cef, nef;
  int nch, nconstituents;

  //-----------------------  AK4 JETS  ----------------------------------------------
  int numjets;
  double ak4jetspt , ak4jetseta, ak4jetsphi,  ak4jetsmass;
  double HT, MHTx, MHTy, MHT;
  std::vector<double> ak4jets_pt;
  std::vector<double> ak4jets_eta;
  std::vector<double> ak4jets_phi;
  std::vector<double> ak4jets_mass;

  edm::InputTag niceak4JetTags_;
  //------------ THE MET FILTER FUNCTION --------------------------------------------
  bool Pass_Filter(edm::Handle<edm::TriggerResults> triggerResults, const edm::TriggerNames & triggerNames, std::string triggPath);
  bool is_HBHENoiseFilter_Fired;
  //-------------------- LEPTONS -----------------------------------------------------
  double ptlep1,   ptlep2;
  double etalep1,  etalep2;
  double philep1,  philep2;
  double miniIso1, miniIso2;

  //--------------------DELTAS ------------------------------------------------------- 
  double deltaRleplep, deltaRlepjet, delPhilepmet, delPhijetmet, deltaphijetmet, deltaPhijetjetabs;

  //-------------------CANDIDATES MASS -----------------------------------------------
  double candMass;
  double candTMass; // transverse mass

  //-------------------- HIGH LEVEL TRIGGER ------------------------------------------
  int    elhltbit;
  int    muhltbit;
  int    matchHlt1;
  int    matchHlt2;
  double deltaRlep1Obj;
  double deltaRlep2Obj;
  double deltaPtlep1Obj;
  double deltaPtlep2Obj;


  // Electron ID 
  double d01,            d02;
  double dz1,            dz2;
  double etel1,          etel2;
  double ptel1,          ptel2;
  double etaSC1,         etaSC2;
  double dEtaIn1,        dEtaIn2;
  double dPhiIn1,        dPhiIn2;
  double hOverE1,        hOverE2;
  double relIso1,        relIso2;
  double caloIso1,       caloIso2;
  double ooEmooP1,       ooEmooP2;
  double trackIso1,      trackIso2;
  double dEtaSeed1,      dEtaSeed2; 
  double sigmaIEtaIEta1, sigmaIEtaIEta2;
  double e1x5overE5x5_1, e1x5overE5x5_2;
  double e2x5overE5x5_1, e2x5overE5x5_2;
  double rho; // energy density
  double eeDeltaR;
  int    barrel1,        barrel2;
  int    endcap1,        endcap2;
  int    heepV601,       heepV602;
  int    modheep1,       modheep2;
  int    ecalDriven1,    ecalDriven2;
  int    missingHits1,   missingHits2;
  int    passConVeto1,   passConVeto2;

  // Muon ID 
  int    highPtMu1,      highPtMu2;
  int    trackerMu1,     trackerMu2;

  boost::shared_ptr<FactorizedJetCorrector> jecAK8_;

  void setDummyValues();

};

//
// constructors and destructor
//
EDBRTreeMaker::EDBRTreeMaker(const edm::ParameterSet& iConfig):
  isGen_            (                                   iConfig.getParameter<bool>          ( "isGen"           ) ),
  isData_           (                                   iConfig.getParameter<bool>          ( "isData"          ) ),
  originalNEvents_  (                                   iConfig.getParameter<int>           ( "originalNEvents" ) ),
  crossSectionPb_   (                                   iConfig.getParameter<double>        ( "crossSectionPb"  ) ),
  targetLumiInvPb_  (                                   iConfig.getParameter<double>        ( "targetLumiInvPb" ) ),
  EDBRChannel_      (                                   iConfig.getParameter<std::string>   ( "EDBRChannel"     ) ),
  gravitonSrc_      (                                   iConfig.getParameter<std::string>   ( "gravitonSrc"     ) ),
  metSrc_           (                                   iConfig.getParameter<std::string>   ( "metSrc"          ) ),
  vertexToken_      ( consumes<reco::VertexCollection>( iConfig.getParameter<edm::InputTag> ( "vertex"        ) ) ),
//  metnohfToken_     (                                   iConfig.getParameter<edm::InputTag> ( "metnohf"         ) ),
//  ak4jetscorrToken_ (                                   iConfig.getParameter<edm::InputTag> ( "ak4jetscorr"     ) ),
  payload_          (                                   iConfig.getParameter<std::string>   ( "payload"          ) ),
  niceak4JetTags_   (                                   iConfig.getParameter<edm::InputTag> ( "niceak4JetsSrc"   ) )
{

   if( iConfig.existsAs<bool>("isData") )
        isData_ = iConfig.getParameter<bool> ("isData");
   else isData_ = true;



  if(EDBRChannel_ == "VZ_CHANNEL")
    channel=VZ_CHANNEL;
  else if(EDBRChannel_ == "VW_CHANNEL")
    channel=VW_CHANNEL;
  else if(EDBRChannel_ == "VH_CHANNEL")
    channel=VH_CHANNEL;
  else if(EDBRChannel_ == "VZnu_CHANNEL")
    channel=VZnu_CHANNEL;
  else {
    cms::Exception ex("InvalidConfiguration");
    ex << "Unknown channel " << EDBRChannel_  
       << ". Please check EDBRTreeMaker.cc for allowed values.";
    throw ex;
  }


  
  //now do what ever initialization is needed
  outTree_ = fs->make<TTree>("EDBRCandidates","EDBR Candidates");

  /// Basic event quantities
  outTree_->Branch("event"           ,&nevent         ,"event/I"          );
  outTree_->Branch("run"             ,&run            ,"run/I"            );
  outTree_->Branch("lumisec"         ,&lumisec        ,"lumisec/I"        );
  outTree_->Branch("nVtx"            ,&nVtx           ,"nVtx/I"           );
  outTree_->Branch("numCands"        ,&numCands       ,"numCands/I"       );
  outTree_->Branch("ptVlep"          ,&ptVlep         ,"ptVlep/D"         );
  outTree_->Branch("ptVhad"          ,&ptVhad         ,"ptVhad/D"         );
  outTree_->Branch("yVlep"           ,&yVlep          ,"yVlep/D"          );
  outTree_->Branch("yVhad"           ,&yVhad          ,"yVhad/D"          );
  outTree_->Branch("phiVlep"         ,&phiVlep        ,"phiVlep/D"        );
  outTree_->Branch("phiVhad"         ,&phiVhad        ,"phiVhad/D"        );
  outTree_->Branch("massVlep"        ,&massVlep       ,"massVlep/D"       );
  outTree_->Branch("mtVlep"          ,&mtVlep         ,"mtVlep/D"         );
  outTree_->Branch("massVhad"        ,&massVhad       ,"massVhad/D"       );
  outTree_->Branch("tau1"            ,&tau1           ,"tau1/D"           );
  outTree_->Branch("tau2"            ,&tau2           ,"tau2/D"           );
  outTree_->Branch("tau3"            ,&tau3           ,"tau3/D"           );
  outTree_->Branch("tau21"           ,&tau21          ,"tau21/D"          );
  outTree_->Branch("lep"             ,&lep            ,"lep/I"            );
  outTree_->Branch("region"          ,&reg            ,"region/I"         );
  outTree_->Branch("channel"         ,&channel        ,"channel/I"        );
  outTree_->Branch("candMass"        ,&candMass       ,"candMass/D"       );
  outTree_->Branch("candTMass"       ,&candTMass      ,"candTMass/D"      );

  /// HLT info 
  outTree_->Branch("elhltbit"        ,&elhltbit       ,"elhltbit/I"       );
  outTree_->Branch("muhltbit"        ,&muhltbit       ,"muhltbit/I"       );
  outTree_->Branch("matchHlt1"       ,&matchHlt1      ,"matchHlt1/I"      );
  outTree_->Branch("matchHlt2"       ,&matchHlt2      ,"matchHlt2/I"      );
  outTree_->Branch("deltaRlep1Obj"   ,&deltaRlep1Obj  ,"deltaRlep1Obj/D"  );
  outTree_->Branch("deltaRlep2Obj"   ,&deltaRlep2Obj  ,"deltaRlep2Obj/D"  );
  outTree_->Branch("deltaPtlep1Obj"  ,&deltaPtlep1Obj ,"deltaPtlep1Obj/D" );
  outTree_->Branch("deltaPtlep2Obj"  ,&deltaPtlep2Obj ,"deltaPtlep2Obj/D" );
 
  /// Muon ID quantities ID quantities
  outTree_->Branch("trackerMu1"      ,&trackerMu1     ,"trackerMu1/I"     );
  outTree_->Branch("trackerMu2"      ,&trackerMu2     ,"trackerMu2/I"     );
  outTree_->Branch("highPtMu1"       ,&highPtMu1      ,"highPtMu1/I"      );
  outTree_->Branch("highPtMu2"       ,&highPtMu2      ,"highPtMu2/I"      );

  /// Electron ID quantities
  outTree_->Branch("barrel1"         ,&barrel1        ,"barrel1/I"        );
  outTree_->Branch("barrel2"         ,&barrel2        ,"barrel2/I"        );
  outTree_->Branch("endcap1"         ,&endcap1        ,"endcap1/I"        );
  outTree_->Branch("endcap2"         ,&endcap2        ,"endcap2/I"        );
  outTree_->Branch("eeDeltaR"        ,&eeDeltaR       ,"eeDeltaR/D"       );
  outTree_->Branch("etel1"           ,&etel1          ,"etel1/D"          );
  outTree_->Branch("etel2"           ,&etel2          ,"etel2/D"          );
  outTree_->Branch("ptel1"           ,&ptel1          ,"ptel1/D"          );
  outTree_->Branch("ptel2"           ,&ptel2          ,"ptel2/D"          );
  outTree_->Branch("etaSC1"          ,&etaSC1         ,"etaSC1/D"         );
  outTree_->Branch("etaSC2"          ,&etaSC2         ,"etaSC2/D"         );
  outTree_->Branch("dEtaIn1"         ,&dEtaIn1        ,"dEtaIn1/D"        );
  outTree_->Branch("dEtaIn2"         ,&dEtaIn2        ,"dEtaIn2/D"        );
  outTree_->Branch("dEtaSeed1"       ,&dEtaSeed1      ,"dEtaSeed1/D"      );
  outTree_->Branch("dEtaSeed2"       ,&dEtaSeed2      ,"dEtaSeed2/D"      );
  outTree_->Branch("dPhiIn1"         ,&dPhiIn1        ,"dPhiIn1/D"        );
  outTree_->Branch("dPhiIn2"         ,&dPhiIn2        ,"dPhiIn2/D"        );
  outTree_->Branch("hOverE1"         ,&hOverE1        ,"hOverE1/D"        );
  outTree_->Branch("hOverE2"         ,&hOverE2        ,"hOverE2/D"        );
  outTree_->Branch("sigmaIEtaIEta1"  ,&sigmaIEtaIEta1 ,"sigmaIEtaIEta1/D" );
  outTree_->Branch("sigmaIEtaIEta2"  ,&sigmaIEtaIEta2 ,"sigmaIEtaIEta2/D" );
  outTree_->Branch("e1x5overE5x5_1"  ,&e1x5overE5x5_1 ,"e1x5overE5x5_1/D" );
  outTree_->Branch("e1x5overE5x5_2"  ,&e1x5overE5x5_2 ,"e1x5overE5x5_2/D" );
  outTree_->Branch("e2x5overE5x5_1"  ,&e2x5overE5x5_1 ,"e2x5overE5x5_1/D" );
  outTree_->Branch("e2x5overE5x5_2"  ,&e2x5overE5x5_2 ,"e2x5overE5x5_2/D" );
  outTree_->Branch("ooEmooP1"        ,&ooEmooP1       ,"ooEmooP1/D"       );
  outTree_->Branch("ooEmooP2"        ,&ooEmooP2       ,"ooEmooP2/D"       );
  outTree_->Branch("d01"             ,&d01            ,"d01/D"            );
  outTree_->Branch("d02"             ,&d02            ,"d02/D"            );
  outTree_->Branch("dz1"             ,&dz1            ,"dz1/D"            );
  outTree_->Branch("dz2"             ,&dz2            ,"dz2/D"            );
  outTree_->Branch("relIso1"         ,&relIso1        ,"relIso1/D"        );
  outTree_->Branch("relIso2"         ,&relIso2        ,"relIso2/D"        );
  outTree_->Branch("caloIso1"        ,&caloIso1       ,"caloIso1/D"       );
  outTree_->Branch("caloIso2"        ,&caloIso2       ,"caloIso2/D"       );
  outTree_->Branch("trackIso1"       ,&trackIso1      ,"trackIso1/D"      );
  outTree_->Branch("trackIso2"       ,&trackIso2      ,"trackIso2/D"      );
  outTree_->Branch("rho"             ,&rho            ,"rho/D"            );
  outTree_->Branch("ecalDriven1"     ,&ecalDriven1    ,"ecalDriven1/I"    );
  outTree_->Branch("ecalDriven2"     ,&ecalDriven2    ,"ecalDriven2/I"    );
  outTree_->Branch("missingHits1"    ,&missingHits1   ,"missingHits1/I"   );
  outTree_->Branch("missingHits2"    ,&missingHits2   ,"missingHits2/I"   );
  outTree_->Branch("passConVeto1"    ,&passConVeto1   ,"passConVeto1/I"   );
  outTree_->Branch("passConVeto2"    ,&passConVeto2   ,"passConVeto2/I"   );
  outTree_->Branch("heepV601"        ,&heepV601       ,"heepV601/I"       );
  outTree_->Branch("heepV602"        ,&heepV602       ,"heepV602/I"       );
  outTree_->Branch("modheep1"        ,&modheep1       ,"modheep1/I"       );
  outTree_->Branch("modheep2"        ,&modheep2       ,"modheep2/I"       );

  // mini isolation for leptons
  outTree_->Branch("miniIso1"        ,&miniIso1       ,"miniIso1/D"       );
  outTree_->Branch("miniIso2"        ,&miniIso2       ,"miniIso2/D"       );
  
  /// Generic kinematic quantities
  outTree_->Branch("numfatjets"      ,&numfatjets     ,"numfatjets/I"     );
  outTree_->Branch("numjets"         ,&numjets        ,"numjets/I"        );
  outTree_->Branch("ptlep1"          ,&ptlep1         ,"ptlep1/D"         );
  outTree_->Branch("ptlep2"          ,&ptlep2         ,"ptlep2/D"         );
  outTree_->Branch("ptjet1"          ,&ptjet1         ,"ptjet1/D"         );
  outTree_->Branch("etjet1"          ,&etjet1         ,"etjet1/D"         );
  outTree_->Branch("etalep1"         ,&etalep1        ,"etalep1/D"        );
  outTree_->Branch("etalep2"         ,&etalep2        ,"etalep2/D"        );
  outTree_->Branch("etajet1"         ,&etajet1        ,"etajet1/D"        );
  outTree_->Branch("philep1"         ,&philep1        ,"philep1/D"        );
  outTree_->Branch("philep2"         ,&philep2        ,"philep2/D"        );
  outTree_->Branch("phijet1"         ,&phijet1        ,"phijet1/D"        );
  outTree_->Branch("massjet1"        ,&massjet1       ,"massjet1/D"       );
  outTree_->Branch("softjet1"        ,&softjet1       ,"softjet1/D"       );
  outTree_->Branch("prunedjet1"      ,&prunedjet1     ,"prunedjet1/D"     );
  outTree_->Branch("met"             ,&met            ,"met/D"            );
  outTree_->Branch("metPhi"          ,&metPhi         ,"metPhi/D"         );
  outTree_->Branch("metpt"           ,&metpt          ,"metpt/D"          );
  outTree_->Branch("metphi"          ,&metphi         ,"metphi/D"         );
  outTree_->Branch("metpx"           ,&metpx          ,"metpx/D"          );
  outTree_->Branch("metpy"           ,&metpy          ,"metpy/D"          );
  outTree_->Branch("HT"              ,&HT             ,"HT/D"             );
  outTree_->Branch("MHT"             ,&MHT            ,"MHT/D"            );
  outTree_->Branch("MHTx"            ,&MHTx           ,"MHTx/D"           );
  outTree_->Branch("MHTy"            ,&MHTy           ,"MHTy/D"           );
  outTree_->Branch("metnomu"         ,&metnomu        ,"metnomu/D"        );
  outTree_->Branch("sumET"           ,&sumET          ,"sumET/D"          );
  outTree_->Branch("rawmetpt"        ,&rawmetpt       ,"rawmetpt/D"       );
  outTree_->Branch("rawmetphi"       ,&rawmetphi      ,"rawmetphi/D"      );
  outTree_->Branch("rawsumET"        ,&rawsumET       ,"rawsumET/D"       );
  outTree_->Branch("genmetpt"        ,&genmetpt       ,"genmetpt/D"       );
  outTree_->Branch("genmetphi"       ,&genmetphi      ,"genmetphi/D"      );
  outTree_->Branch("calometpt"       ,&calometpt      ,"calometpt/D"      );
  outTree_->Branch("calometphi"      ,&calometphi     ,"calometphi/D"     );
  outTree_->Branch("calometsumET"    ,&calometsumET   ,"calometsumET/D"   );
  // ak4 jets
  outTree_->Branch("ak4jets_pt"      ,&ak4jets_pt                         );
  outTree_->Branch("ak4jets_eta"     ,&ak4jets_eta                        );
  outTree_->Branch("ak4jets_phi"     ,&ak4jets_phi                        );
  outTree_->Branch("ak4jets_mass"    ,&ak4jets_mass                       );

  /// Other quantities
  outTree_->Branch("triggerWeight"   ,&triggerWeight  ,"triggerWeight/D"  );
  outTree_->Branch("lumiWeight"      ,&lumiWeight     ,"lumiWeight/D"     );
  outTree_->Branch("pileupWeight"    ,&pileupWeight   ,"pileupWeight/D"   );
  outTree_->Branch("deltaRleplep"    ,&deltaRleplep   ,"deltaRleplep/D"   );
  outTree_->Branch("delPhilepmet"    ,&delPhilepmet   ,"delPhilepmet/D"   );
  outTree_->Branch("deltaRlepjet"    ,&deltaRlepjet   ,"deltaRlepjet/D"   );
  outTree_->Branch("delPhijetmet"    ,&delPhijetmet   ,"delPhijetmet/D"   );
  outTree_->Branch("deltaPhijetjetabs"   ,&deltaPhijetjetabs   ,"deltaPhijetjetabs/D");

  outTree_->Branch("is_HBHENoiseFilter_Fired"    ,&is_HBHENoiseFilter_Fired   ,"is_HBHENoiseFilter_Fired/O"   ); 

  /// Jet ID variables
  outTree_->Branch("chf"   ,&chf  ,"chf/D"  );
  outTree_->Branch("nhf"   ,&nhf  ,"nhf/D"     );
  outTree_->Branch("cef"   ,&cef  ,"cef/D"   );
  outTree_->Branch("nef"   ,&nef  ,"nef/D"   );
  outTree_->Branch("nch"   ,&nch  ,"nch/I"   );
  outTree_->Branch("nconstituents"  ,&nconstituents  ,"nconstituents/I"   );


}


EDBRTreeMaker::~EDBRTreeMaker() {}

// ------------ method called for each event  ------------
void
EDBRTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   nevent  = iEvent.eventAuxiliary().event();
   run     = iEvent.eventAuxiliary().run();
   lumisec = iEvent.eventAuxiliary().luminosityBlock();

   setDummyValues(); //Initalize variables with dummy values


   Handle<View<reco::Candidate> > gravitons;
   iEvent.getByLabel(gravitonSrc_.c_str(), gravitons);
   numCands = gravitons->size();
   if(numCands != 0 ) {
       const reco::Candidate& graviton  = gravitons->at(0);

       // met
       Handle<View<reco::Candidate> > metHandle;
       iEvent.getByLabel(metSrc_.c_str(), metHandle);
       const reco::Candidate& metCand = metHandle->at(0);
       
       /// All the quantities which depend on RECO could go here
       if(not isGen_) {
           // electrons and muons
           Handle<View<pat::Electron> > electrons;
           Handle<View<pat::Muon> >     muons;
           iEvent.getByLabel("slimmedElectrons", electrons);
           iEvent.getByLabel("slimmedMuons",     muons);

           // number of jets
           Handle<std::vector<pat::Jet>> jets;
           iEvent.getByLabel("slimmedJetsAK8", jets);
           numfatjets = jets->size();
           met     = metCand.pt();
           metPhi  = metCand.phi();

           // handle goodOfflinePrimaryVertex collection
           Handle<reco::VertexCollection> vertices;
           iEvent.getByToken(vertexToken_, vertices);
           nVtx = vertices->size();
           const reco::Vertex& vertex = (*vertices)[0];
  
           // Effective area constants
           EffectiveAreas _effectiveAreas( FileInPath("RecoEgamma/ElectronIdentification/data/PHYS14/effAreaElectrons_cone03_pfNeuHadronsAndPhotons.txt").fullPath() );
           // The rho
           Handle< double > rhoHandle;
           iEvent.getByLabel("fixedGridRhoFastjetAll", rhoHandle);
           rho = (float)(*rhoHandle);
 
            // Jet Energy Corrections
            edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl;
            iSetup.get<JetCorrectionsRecord>().get(payload_, JetCorParColl); 


           //we put the definitions inside the channel
           switch(channel){
               case VZ_CHANNEL:{
                   const reco::Candidate& leptonicV = (*graviton.daughter("leptonicV"));
                   const pat::Jet& hadronicV = dynamic_cast<const pat::Jet&>(*graviton.daughter("hadronicV"));
                   // ------ analize trigger results ----------//  
                   Handle<bool> elHlt_handle;
                   Handle<bool> muHlt_handle;
                   Handle<ValueMap<bool> > matchHlt_handle;
                   Handle<ValueMap<float> > deltaPt_handle;
                   Handle<ValueMap<float> >  deltaR_handle;
                   iEvent.getByLabel(InputTag("hltMatchingElectrons","trigBit"), elHlt_handle);
                   iEvent.getByLabel(InputTag("hltMatchingMuons",    "trigBit"), muHlt_handle);
                   elhltbit = (int)(*elHlt_handle);
                   muhltbit = (int)(*muHlt_handle);


                   //**************DEFINITIONS *********************************** 
                   // candidate
                   candMass     = graviton.mass();
                   // leptons
                   ptVlep       = leptonicV.pt();
                   yVlep        = leptonicV.eta();
                   phiVlep      = leptonicV.phi();
                   massVlep     = leptonicV.mass();
                   mtVlep       = leptonicV.mt();
                   ptlep1       = leptonicV.daughter(0)->pt();
                   ptlep2       = leptonicV.daughter(1)->pt();
                   etalep1      = leptonicV.daughter(0)->eta();
                   etalep2      = leptonicV.daughter(1)->eta();
                   philep1      = leptonicV.daughter(0)->phi();
                   philep2      = leptonicV.daughter(1)->phi();
                   lep      = abs(leptonicV.daughter(0)->pdgId());
                   // hadrons
                   ptVhad       = hadronicV.pt();
                   yVhad        = hadronicV.eta();
                   phiVhad      = hadronicV.phi();
                   tau1         = hadronicV.userFloat("NjettinessAK8:tau1");
                   tau2         = hadronicV.userFloat("NjettinessAK8:tau2");
                   tau3         = hadronicV.userFloat("NjettinessAK8:tau3");
                   tau21        = tau2/tau1;
                   etjet1       = hadronicV.et();
                   ptjet1       = hadronicV.pt();
                   etajet1      = hadronicV.eta();
                   phijet1      = hadronicV.phi();
                   massjet1     = hadronicV.mass();
                   softjet1     = hadronicV.userFloat("ak8PFJetsCHSSoftDropMass");
                   prunedjet1   = hadronicV.userFloat("ak8PFJetsCHSPrunedMass");
                   massVhad     = hadronicV.userFloat("ak8PFJetsCHSSoftDropMass");
                   // deltas
                   deltaRleplep = deltaR(etalep1,philep1,etalep2,philep2);
                   double drl1j = deltaR(etalep1,philep1,etajet1,phijet1);
                   double drl2j = deltaR(etalep2,philep2,etajet1,phijet1);
                   deltaRlepjet = std::min(drl1j,drl2j);
                   delPhilepmet = deltaPhi(philep1, metPhi);
                   delPhijetmet = deltaPhi(phijet1, metPhi);
                   //*****************************************************************//
                   //************************* ID for muons **************************//
                   //*****************************************************************//
                   if ( leptonicV.daughter(0)->isMuon() && 
                        leptonicV.daughter(1)->isMuon()    ) {
                        const pat::Muon *mu1 = (pat::Muon*)leptonicV.daughter(0);
                        const pat::Muon *mu2 = (pat::Muon*)leptonicV.daughter(1);
                        const Ptr<pat::Muon> mu1Ptr(muons, mu1->userInt("slimmedIndex") );
                        const Ptr<pat::Muon> mu2Ptr(muons, mu2->userInt("slimmedIndex") );
                        iEvent.getByLabel(InputTag("hltMatchingMuons","deltaR"),   deltaR_handle);
                        iEvent.getByLabel(InputTag("hltMatchingMuons","deltaPt"),  deltaPt_handle);
                        iEvent.getByLabel(InputTag("hltMatchingMuons","matchHlt"), matchHlt_handle);
                        deltaRlep1Obj  =      (*deltaR_handle)[mu1Ptr];
                        deltaRlep2Obj  =      (*deltaR_handle)[mu2Ptr];
                        deltaPtlep1Obj =      (*deltaPt_handle)[mu1Ptr];
                        deltaPtlep2Obj =      (*deltaPt_handle)[mu2Ptr];
                        matchHlt1      = (int)(*matchHlt_handle)[mu1Ptr]; 
                        matchHlt2      = (int)(*matchHlt_handle)[mu2Ptr]; 
                        reco::MuonPFIsolation pfIso1  = mu1->pfIsolationR03();
                        reco::MuonPFIsolation pfIso2  = mu2->pfIsolationR03();
                        // isolation with delta beta correction
                        double absiso1 =  pfIso1.sumChargedHadronPt + std::max(0.0,  pfIso1.sumNeutralHadronEt +  pfIso1.sumPhotonEt -  0.5*pfIso1.sumPUPt );
                        double absiso2 =  pfIso2.sumChargedHadronPt + std::max(0.0,  pfIso2.sumNeutralHadronEt +  pfIso2.sumPhotonEt -  0.5*pfIso2.sumPUPt );
                        relIso1        = absiso1/mu1->pt();
                        relIso2        = absiso2/mu2->pt();
                        trackerMu1     = mu1->userInt("isTracker");
                        trackerMu2     = mu2->userInt("isTracker");
                        highPtMu1      = mu1->userInt("isHighPt");
                        highPtMu2      = mu2->userInt("isHighPt");
                        // retrieve mini isolation
                        miniIso1       = mu1->userFloat("miniIso");
                        miniIso2       = mu2->userFloat("miniIso");
                   }
                   //*****************************************************************//
                   //************************* ID for electrons **********************//
                   //*****************************************************************//
                   else if ( leptonicV.daughter(0)->isElectron() && 
                             leptonicV.daughter(1)->isElectron()    ) {
                        const pat::Electron *el1 = (pat::Electron*)leptonicV.daughter(0);
                        const pat::Electron *el2 = (pat::Electron*)leptonicV.daughter(1);
                        const Ptr<pat::Electron> el1Ptr(electrons, el1->userInt("slimmedIndex") );
                        const Ptr<pat::Electron> el2Ptr(electrons, el2->userInt("slimmedIndex") );
                        iEvent.getByLabel(InputTag("hltMatchingElectrons","deltaR"),   deltaR_handle);
                        iEvent.getByLabel(InputTag("hltMatchingElectrons","deltaPt"),  deltaPt_handle);
                        iEvent.getByLabel(InputTag("hltMatchingElectrons","matchHlt"), matchHlt_handle);
                        deltaRlep1Obj  =      (*deltaR_handle)[el1Ptr];
                        deltaRlep2Obj  =      (*deltaR_handle)[el2Ptr];
                        deltaPtlep1Obj =      (*deltaPt_handle)[el1Ptr];
                        deltaPtlep2Obj =      (*deltaPt_handle)[el2Ptr];
                        matchHlt1      = (int)(*matchHlt_handle)[el1Ptr]; 
                        matchHlt2      = (int)(*matchHlt_handle)[el2Ptr]; 
                        eeDeltaR       = reco::deltaR(el1->p4(),el2->p4());
                        ptel1          = el1->pt();
                        ptel2          = el2->pt();
                        etel1          = el1->superCluster()->energy();
                        etel2          = el2->superCluster()->energy();
                        etaSC1         = el1->superCluster()->eta();
                        etaSC2         = el2->superCluster()->eta();
                        barrel1        = fabs(etaSC1)<1.4442 ? 1:0;
                        barrel2        = fabs(etaSC2)<1.4442 ? 1:0;
                        endcap1        = fabs(etaSC1)>1.566 && fabs(etaSC1)<2.5 ? 1:0;
                        endcap2        = fabs(etaSC2)>1.566 && fabs(etaSC2)<2.5 ? 1:0;
                        // isolation with effective area correction
                        reco::GsfElectron::PflowIsolationVariables pfIso1 = el1->pfIsolationVariables();
                        reco::GsfElectron::PflowIsolationVariables pfIso2 = el2->pfIsolationVariables();
                        double     eA1 = _effectiveAreas.getEffectiveArea( etaSC1 );
                        double     eA2 = _effectiveAreas.getEffectiveArea( etaSC2 );
                        double absiso1 = pfIso1.sumChargedHadronPt + std::max(0.0, pfIso1.sumNeutralHadronEt + pfIso1.sumPhotonEt - rho*eA1 );
                        double absiso2 = pfIso2.sumChargedHadronPt + std::max(0.0, pfIso2.sumNeutralHadronEt + pfIso2.sumPhotonEt - rho*eA2 );
                        relIso1        = absiso1/el1->pt();
                        relIso2        = absiso2/el2->pt();
                        caloIso1       = el1->dr03EcalRecHitSumEt() + el1->dr03HcalDepth1TowerSumEt();
                        caloIso2       = el2->dr03EcalRecHitSumEt() + el2->dr03HcalDepth1TowerSumEt();
                        trackIso1      = el1->dr03TkSumPt();
                        trackIso2      = el2->dr03TkSumPt();
                        // retrieve mini isolation
                        miniIso1       = el1->userFloat("miniIso");
                        miniIso2       = el2->userFloat("miniIso");
                        // heepV60
                        heepV601       = el1->userInt("heepV60"); 
                        heepV602       = el1->userInt("heepV60"); 
                        modheep1       = el1->userInt("heepV60_noiso"); 
                        modheep2       = el1->userInt("heepV60_noiso"); 
                        // shower shapes
                        sigmaIEtaIEta1 = el1->full5x5_sigmaIetaIeta();
                        sigmaIEtaIEta2 = el2->full5x5_sigmaIetaIeta();
                        double e5x5_1  = el1->full5x5_e5x5(); 
                        double e5x5_2  = el2->full5x5_e5x5(); 
                        e1x5overE5x5_1 = e5x5_1!=0 ? el1->full5x5_e1x5()/e5x5_1    : 0; 
                        e1x5overE5x5_2 = e5x5_2!=0 ? el2->full5x5_e1x5()/e5x5_2    : 0; 
                        e2x5overE5x5_1 = e5x5_1!=0 ? el1->full5x5_e2x5Max()/e5x5_1 : 0; 
                        e2x5overE5x5_2 = e5x5_2!=0 ? el2->full5x5_e2x5Max()/e5x5_2 : 0; 
                        // more electron ID variables
                        dEtaIn1        = el1->deltaEtaSuperClusterTrackAtVtx();
                        dEtaIn2        = el2->deltaEtaSuperClusterTrackAtVtx();
                        dPhiIn1        = el1->deltaPhiSuperClusterTrackAtVtx();
                        dPhiIn2        = el2->deltaPhiSuperClusterTrackAtVtx();
                        dEtaSeed1      = el1->deltaEtaSeedClusterTrackAtVtx();
                        dEtaSeed2      = el2->deltaEtaSeedClusterTrackAtVtx();
                        hOverE1        = el1->hadronicOverEm();
                        hOverE2        = el2->hadronicOverEm();
                        ooEmooP1       = el1->ecalEnergy() && std::isfinite(el1->ecalEnergy()) ? 
                                         fabs(1.0/el1->ecalEnergy() - el1->eSuperClusterOverP()/el1->ecalEnergy() ) : 1e9;
                        ooEmooP2       = el2->ecalEnergy() && std::isfinite(el2->ecalEnergy()) ? 
                                         fabs(1.0/el2->ecalEnergy() - el2->eSuperClusterOverP()/el2->ecalEnergy() ) : 1e9;
                        ecalDriven1    = el1->ecalDriven();
                        ecalDriven2    = el2->ecalDriven();
                        passConVeto1   = el1->passConversionVeto();
                        passConVeto2   = el2->passConversionVeto();
                        if (el1->gsfTrack().isNonnull() && 
                            el2->gsfTrack().isNonnull()    ){
                            d01          = (-1)*el1->gsfTrack()->dxy(vertex.position());   
                            d02          = (-1)*el2->gsfTrack()->dxy(vertex.position());  
                            dz1          = el1->gsfTrack()->dz(vertex.position());
                            dz2          = el2->gsfTrack()->dz(vertex.position());
                            missingHits1 = el1->gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
                            missingHits2 = el2->gsfTrack()->hitPattern().numberOfHits(reco::HitPattern::MISSING_INNER_HITS);
                        }
                   }
                   break;}
               case VW_CHANNEL:{
                   const reco::Candidate& leptonicV = (*graviton.daughter("leptonicV"));
                   const pat::Jet& hadronicV = dynamic_cast<const pat::Jet&>(*graviton.daughter("hadronicV"));
                   //*****************DEFINITIONS *************************************
                   //candidate
                   candMass  = graviton.mass();
                   //leptons
                   ptVlep = leptonicV.pt();
                   yVlep  = leptonicV.eta();
                   phiVlep = leptonicV.phi();
                   massVlep = leptonicV.mass();
                   mtVlep  = leptonicV.mt();
                   ptlep1 = leptonicV.daughter(0)->pt();
                   etalep1 = leptonicV.daughter(0)->eta();
                   philep1 = leptonicV.daughter(0)->phi();
                   lep = abs(leptonicV.daughter(0)->pdgId());
                   //met
                   met = metCand.pt();
                   metPhi = metCand.phi();  
                   //hadrons
                   ptVhad = hadronicV.pt();
                   yVhad  = hadronicV.eta();
                   phiVhad = hadronicV.phi();
                   tau1 = hadronicV.userFloat("NjettinessAK8:tau1");
                   tau2 = hadronicV.userFloat("NjettinessAK8:tau2");
                   tau3 = hadronicV.userFloat("NjettinessAK8:tau3");
                   tau21 = tau2/tau1;
                   etjet1 = hadronicV.et();
                   ptjet1 = hadronicV.pt();
                   etajet1 = hadronicV.eta();
                   phijet1 = hadronicV.phi();
                   massjet1 = hadronicV.mass();
                   massVhad     = hadronicV.userFloat("ak8PFJetsCHSSoftDropMass");
                   //deltas
                   deltaRleplep = deltaR(etalep1,philep1,etalep2,philep2);
                   double drl1j = deltaR(etalep1,philep1,etajet1,phijet1);
                   double drl2j = deltaR(etalep2,philep2,etajet1,phijet1);
                   deltaRlepjet = std::min(drl1j,drl2j);
                   delPhilepmet = deltaPhi(philep1, metPhi);
                   delPhijetmet = deltaPhi(phijet1, metPhi);
                   break;}
               case VZnu_CHANNEL:{
                   ////************************************************************************************
                   ////***********************     VZNu CHANNEL      **************************************
                   ////************************************************************************************
                   const pat::Jet& hadronicVnu = dynamic_cast<const pat::Jet&>(*graviton.daughter("hadronicVnu"));
                   const pat::MET& goodMET =dynamic_cast<const pat::MET&> (*graviton.daughter("goodMET"));                 
                   ////--------------------------------------------------------------------------------////   
                   ////-------------------  HADRONS ---------------------------------------------------////
                   ////--------------------------------------------------------------------------------////
                   ////------- FLAG FOR MET FILTER -----////
                   edm::Handle<edm::TriggerResults> trigResults2;
                   //// This configuration is for data, in case of MC, check if RECO have to change
                   //// For Data
                   //edm::InputTag trigResultsTag2("TriggerResults","","RECO");
                   //// For MC
                   edm::InputTag trigResultsTag2("TriggerResults","","PAT");
                   iEvent.getByLabel(trigResultsTag2,trigResults2);
                   const edm::TriggerNames& trigNames2 = iEvent.triggerNames(*trigResults2); 
                   is_HBHENoiseFilter_Fired = Pass_Filter(trigResults2, trigNames2, "Flag_HBHENoiseFilter");
                   ////----------- FOR JET ID  --------////
                   chf = 0.0;
                   nhf = 0.0;
                   cef = 0.0;
                   nef = 0.0;
                   nch = 0;
                   nconstituents = 0;
                   //// ----   JET ID VARIABLES ------ ////
                   if ( hadronicVnu.isPFJet() ) {
                    chf = hadronicVnu.chargedHadronEnergyFraction();
                    nhf = hadronicVnu.neutralHadronEnergyFraction();
                    cef = hadronicVnu.chargedEmEnergyFraction();
                    nef = hadronicVnu.neutralEmEnergyFraction();
                    nch = hadronicVnu.chargedMultiplicity();
                    nconstituents = hadronicVnu.numberOfDaughters();
                   }
                   ////----- OTHER VARIABLES --------//// 
                   ptVhad    = hadronicVnu.pt();
                   yVhad     = hadronicVnu.eta();
                   phiVhad   = hadronicVnu.phi();
                   tau1      = hadronicVnu.userFloat("NjettinessAK8:tau1");
                   tau2      = hadronicVnu.userFloat("NjettinessAK8:tau2");
                   tau3      = hadronicVnu.userFloat("NjettinessAK8:tau3");
                   tau21     = tau2/tau1;
                   ptjet1    = hadronicVnu.pt();
                   etajet1   = hadronicVnu.eta();
                   phijet1   = hadronicVnu.phi();
                   ////------------ JET MASS WITHOUT CORRECTIONS  ----------////
                   //Already with JEC via the global tag
                   massjet1 = hadronicVnu.mass();
                   ///------------  JET MASS WITH CORRECTIONS  -------------////                        
                   softjet1     = hadronicVnu.userFloat("ak8PFJetsCHSSoftDropMass");
                   prunedjet1   = hadronicVnu.userFloat("ak8PFJetsCHSPrunedMass");
                   massVhad = prunedjet1 * prunedMassCorrection( rho, nVtx, hadronicVnu, JetCorParColl ); 
                   ////---------------------------------------------------------------------------------////
                   ////------------------------------  MET ---------------------------------------------////
                   ////---------------------------------------------------------------------------------////
                   //// THE TypeI PF MET
                   metpt   = goodMET.pt();
                   metphi  = goodMET.phi();
                   metpx   = goodMET.px();
                   metpy   = goodMET.py();
                   sumET   = goodMET.sumEt(); 
                   //// The Uncorrected MET (how access change with the release)
                   rawmetpt  =  goodMET.uncorPt();
                   rawmetphi =  goodMET.uncorPhi();
                   rawsumET  =  goodMET.uncorSumEt();
                   //// The Gen MET
                   genmetpt   =  goodMET.genMET()->pt();
                   genmetphi  =  goodMET.genMET()->phi();
                   //// The Calo MET
                   calometpt     =   goodMET.caloMETPt();
                   calometphi    =   goodMET.caloMETPhi();
                   calometsumET  =   goodMET.caloMETSumEt();
                      

                   ////--------------------  MET NO MU (TO FIX)--------------------////
                   double metnomu_x = metpx;
                   double metnomu_y = metpy;
                   edm::Handle<pat::MuonCollection> muons;
                   iEvent.getByLabel("slimmedMuons", muons);
                   for (const pat::Muon &mu : *muons) {
                        double muonpx = mu.px();
                        double muonpy = mu.py();
                        metnomu_x += muonpx;
                        metnomu_y += muonpy;
                    }
                   metnomu = sqrt(metnomu_x*metnomu_x + metnomu_y*metnomu_y);

                   ////-----------------------------------------------------------------------------------////
                   ////--------------------------------  AK4 JETS  ---------------------------------------////
                   ////-----------------------------------------------------------------------------------////
                   edm::Handle<std::vector<pat::Jet>> jets;
                   iEvent.getByLabel(niceak4JetTags_, jets); 
                   ////jets( vector of kinematic variables)
                   ak4jets_pt.clear();
                   ak4jets_eta.clear();
                   ak4jets_phi.clear();
                   ak4jets_mass.clear(); 
                   ////--- NUMBER OF JETS ----//// 
                   numjets = jets->size();
                   ////--------  HT AND MHT  -------------////
                   HT=0;
                   MHTx = 0, MHTy = 0;
                   for (const pat::Jet &j : *jets) {
                         ak4jetspt  =  j.pt();
                         ak4jetseta =  j.eta();
                         ak4jetsphi =  j.phi();
                         ak4jetsmass = j.mass();
                         ak4jets_pt.push_back(ak4jetspt);
                         ak4jets_eta.push_back(ak4jetseta);
                         ak4jets_phi.push_back(ak4jetsphi);
                         ak4jets_mass.push_back(ak4jetsmass);
                         HT += ak4jetspt;
                         MHTx -= j.px();
                         MHTy -= j.py();
                    }         
                    MHT = sqrt( MHTx*MHTx + MHTy*MHTy );
                    ////---DELTAPHI BETWEEN LEADING AND SUBLEADING JET----////
                    if(numjets==2){
                           const pat::Jet &jet1 = jets->at(0);
                           const pat::Jet &jet2 = jets->at(1);
                           double phi1 = jet1.phi();
                           double phi2 = jet2.phi();
                           deltaPhijetjetabs  = fabs(deltaPhi(phi1,phi2));
                    }

                    ////---------------------------------------------------------------------------////
                    ////--------------------------  OTHER VARIABLES  ------------------------------////
                    ////---------------------------------------------------------------------------////
                    ////delta Phi between jet and met(from graviton) 
                    deltaphijetmet = deltaPhi(phijet1, metphi);
                    // transverse candidate mass for JET + MET
                    candTMass    = sqrt(abs(2*ptjet1*metpt*(1-cos(deltaphijetmet))));                     
                    break;}
                case VH_CHANNEL: // This channel needs to be implemented 
                    break;

           }// close switch


       }// close not isGen
       
//       if(isGen_) {
//	   massVhad = hadronicV.userFloat("ak8GenJetsSoftDropMass");
//	   nVtx = 0;
//       }

       /// For the time being, set these to 1
       triggerWeight=1.0;
       pileupWeight=1.0;

       double targetEvents = targetLumiInvPb_*crossSectionPb_;
       lumiWeight = targetEvents/originalNEvents_;


       enum {
              excluded = -1,
              lowerSB,
              lowerSIG,
              upperSIG,
              upperSB,
       };

      
       if( massVhad < 40. )
           reg = excluded;
       if( massVhad > 40. and massVhad < 65. )
           reg = lowerSB;
       if( massVhad > 65. and massVhad < 105. )
           reg = lowerSIG;
       if( massVhad > 105. and massVhad < 135. )
           reg = upperSIG;
       if( massVhad > 135. )
           reg = upperSB;  

   
       outTree_->Fill();
   }
   else {
       /// If we arrive here, that means we have NOT found a resonance candidate,
       /// i.e. numCands == 0.
       outTree_->Fill();
       //return; // skip event if there is no resonance candidate
   }

}
double EDBRTreeMaker::prunedMassCorrection( double rho,
                                            double nVtx,
                                            const pat::Jet& jet,
                                            edm::ESHandle<JetCorrectorParametersCollection> JetCorParColl ) {
      std::vector<std::string> jecAK8PayloadNames;
      jecAK8PayloadNames.push_back("L2Relative");
      jecAK8PayloadNames.push_back("L3Absolute");
      if(isData_)
      jecAK8PayloadNames.push_back("L2L3Residual");
      std::vector<JetCorrectorParameters> vPar;
      for ( std::vector<std::string>::const_iterator payloadBegin = jecAK8PayloadNames.begin(),
                                                     payloadEnd = jecAK8PayloadNames.end() ,
                                                     ipayload = payloadBegin;
                                                     ipayload != payloadEnd;
                                                   ++ipayload ) vPar.push_back( (*JetCorParColl)[*ipayload] );
      // Make the FactorizedJetCorrector
      std::shared_ptr<FactorizedJetCorrector> jecAK8 = std::shared_ptr<FactorizedJetCorrector> ( new FactorizedJetCorrector(vPar) );
      jecAK8->setRho ( rho );
      jecAK8->setNPV ( nVtx );
      jecAK8->setJetA ( jet.jetArea() );
      jecAK8->setJetPt ( jet.correctedP4(0).pt() );
      jecAK8->setJetEta( jet.correctedP4(0).eta() );
      jecAK8->setJetE ( jet.correctedP4(0).energy() );
      return jecAK8->getCorrection();
}

bool EDBRTreeMaker::Pass_Filter( edm::Handle<edm::TriggerResults> trigResults, 
                                 const edm::TriggerNames & trigNames,
                                 std::string triggPath){
   bool isFired_Filter = false;
   unsigned int TrggIndex( trigNames.triggerIndex(triggPath) );
   if(TrggIndex < trigResults->size())isFired_Filter = trigResults->accept(TrggIndex);

   return isFired_Filter;

}

void EDBRTreeMaker::setDummyValues() {
     nVtx           = -1e4;
     triggerWeight  = -1e4;
     pileupWeight   = -1e4;
     lumiWeight     = -1e4;
     candMass       = -1e4;
     ptVlep         = -1e4;
     ptVhad         = -1e4;
     yVlep          = -1e4;
     yVhad          = -1e4;
     phiVlep        = -1e4;
     phiVhad        = -1e4;
     massVlep       = -1e4;
     massVhad       = -1e4;
     mtVlep         = -1e4;
     tau1           = -1e4;
     tau2           = -1e4;
     tau3           = -1e4;
     tau21          = -1e4;
     ptlep1         = -1e4;
     ptlep2         = -1e4;
     etalep1        = -1e4;
     etalep2        = -1e4;
     philep1        = -1e4;
     philep2        = -1e4;
     miniIso1       = -1e4;
     miniIso2       = -1e4;
     numjets        = -1e4; 
     numfatjets     = -1e4;
     etjet1         = -1e4;
     ptjet1         = -1e4;
     etajet1        = -1e4;
     phijet1        = -1e4;
     massjet1       = -1e4;
     softjet1       = -1e4;
     prunedjet1     = -1e4;
     met            = -1e4;
     metPhi         = -1e4;
     metpt          = -1e4;
     metphi         = -1e4;
     metpx          = -1e4;
     metpy          = -1e4;
     metnomu        = -1e4;
     matchHlt1      = -1e4;
     matchHlt2      = -1e4;
     deltaRlep1Obj  = -1e4;
     deltaRlep2Obj  = -1e4;
     deltaPtlep1Obj = -1e4;
     deltaPtlep2Obj = -1e4;
     deltaRleplep   = -1e4;
     deltaRlepjet   = -1e4;
     delPhilepmet   = -1e4;
     delPhijetmet   = -1e4;
     deltaphijetmet = -1e4; 
     deltaPhijetjetabs = -1e4;
     lep            = -1e4;
     reg            = -1e4;
     rho            = -1e4;
     barrel1        = -1e4;
     barrel2        = -1e4;
     endcap1        = -1e4;
     endcap2        = -1e4;
     eeDeltaR       = -1e4;
     etel1          = -1e4;
     ptel1          = -1e4;
     etaSC1         = -1e4;
     dEtaIn1        = -1e4;
     dPhiIn1        = -1e4;
     hOverE1        = -1e4;
     sigmaIEtaIEta1 = -1e4;
     e1x5overE5x5_1 = -1e4;
     e2x5overE5x5_1 = -1e4;
     ooEmooP1       = -1e4;
     d01            = -1e4;
     dz1            = -1e4;
     relIso1        = -1e4;
     caloIso1       = -1e4;
     trackIso1      = -1e4;
     ecalDriven1    = -1e4;
     missingHits1   = -1e4; 
     passConVeto1   = -1e4;
     heepV601       = -1e4;
     modheep1       = -1e4;
     etel2          = -1e4;
     ptel2          = -1e4;
     etaSC2         = -1e4;
     dEtaIn2        = -1e4;
     dPhiIn2        = -1e4;
     hOverE2        = -1e4;
     sigmaIEtaIEta2 = -1e4;
     e1x5overE5x5_2 = -1e4;
     e2x5overE5x5_2 = -1e4;
     ooEmooP2       = -1e4;
     d02            = -1e4;
     dz2            = -1e4;
     relIso2        = -1e4;
     caloIso2       = -1e4;
     trackIso2      = -1e4;
     ecalDriven2    = -1e4;
     missingHits2   = -1e4; 
     passConVeto2   = -1e4;
     heepV602       = -1e4; 
     modheep2       = -1e4; 
     trackerMu1     = -1e4;
     trackerMu2     = -1e4;
     highPtMu1      = -1e4;
     highPtMu2      = -1e4;
     sumET          = -1e4;
     rawmetpt       = -1e4;
     rawmetphi      = -1e4;
     rawsumET       = -1e4;
     genmetpt       = -1e4;
     genmetphi      = -1e4;
     calometpt      = -1e4;
     calometphi     = -1e4;
     calometsumET   = -1e4;
     HT             = -1e4;
     MHT            = -1e4;
     MHTx           = -1e4;
     MHTy           = -1e4;
     chf            = -1e4;
     nhf            = -1e4;
     cef            = -1e4;
     nef            = -1e4;
     nch            = -1e4; 
     nconstituents  = -1e4;

}

// ------------ method called once each job just before starting event loop  ------------
void EDBRTreeMaker::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void EDBRTreeMaker::endJob() {
  std::cout << "EDBRTreeMaker endJob()..." << std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(EDBRTreeMaker);
