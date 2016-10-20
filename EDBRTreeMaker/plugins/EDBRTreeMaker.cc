// system include files
#include <iostream>
#include <memory>
#include <map>
#include <string>

// user include files
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/EgammaCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

//// FOR MUONS ID
#include "DataFormats/MuonReco/interface/MuonSelectors.h"

//// FOR ELECTRONS ID
#include "DataFormats/Common/interface/ValueMap.h"

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "EDBRChannels.h"
#include "TAxis.h"
#include "TEfficiency.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"


#include "TString.h"
#include "TTree.h"
#include "TF1.h"

////---- JEC
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"

#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"
#include "PhysicsTools/PatAlgos/plugins/JetCorrFactorsProducer.h"


#include "DataFormats/Math/interface/LorentzVector.h"
#include "PhysicsTools/CandUtils/interface/AddFourMomenta.h"
#include "TLorentzVector.h"
#include "TMath.h"
#include "Math/LorentzVector.h"

////------TRIGGER
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"

#include <boost/foreach.hpp>
#include <utility>
#define DEBUG

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
//  BTagCalibrationReader reader;
//  BTagCalibration calib;


  template<typename T>
    struct RefGreaterByPt {
      typedef T first_argument_type;
      typedef T second_argument_type;
      bool operator()( const T* t1, const T* t2 ) const {
        return t1->pt() > t2->pt();
      }
    };

//******************************************************************
//************************* MEMBER DATA ****************************
//******************************************************************
  edm::Service<TFileService> fs;
  TTree* outTree_;

  //------------------------ GENERAL ----------------------------------------------
  int nVtx;
  int numCands;
  int nevent, run, lumisec;
  int channel, reg;
  double triggerWeight, lumiWeight, pileupWeight, genWeight, ewkWeight;
  double electronWeight, electronrecoWeight, photonWeight, muonWeight, muonisoWeight, vetobtaggWeight;
  double totalWeight;

  bool isGen_;
  bool isData_; 
  bool correctEW_;
  bool correctBtag_;

  int originalNEvents_;
  double crossSectionPb_;
  double targetLumiInvPb_;
  std::string EDBRChannel_;
  std::string gravitonSrc_, metSrc_;
  edm::FileInPath puWeights_;
  edm::FileInPath EWcorr_;
  edm::EDGetTokenT<reco::VertexCollection> vertexToken_;

  edm::FileInPath electronsSFs_;
  edm::FileInPath elrecoSFs_;
  edm::FileInPath photonsSFs_;
  edm::FileInPath muonSFs_;
  edm::FileInPath muIsoSFs_;


  edm::EDGetTokenT<double> rhoToken;
  edm::EDGetTokenT<reco::CompositeCandidateView> gravitonsToken;
  edm::EDGetTokenT<std::vector<PileupSummaryInfo> > puInfoToken;
  edm::EDGetTokenT<GenEventInfoProduct> genEvtInfoToken;


  //------------------------ V quantities ------------------------------------------
  double ptVhad, yVhad, phiVhad, massVhad;

  //-----------------------MET FROM GRAVITON ----------------------------------------
  double metpt, metphi, metpx, metpy, metnomu;
  double sumET, rawmetpt, rawmetphi, rawsumET, genmetpt, genmetphi, calometpt, calometphi, calometsumET;
  double metcorrptup, metcorrptdown;

  //---------------------- AK8 JETS --------------------------------------------------
  double tau1,     tau2,     tau3,     tau21;
  double etjet1,   ptjet1,   etajet1,  phijet1;
  double massjet1, softjet1, prunedjet1;
  double ptCorUp, ptCorDown;

  //------------------ AK8 JET ID VARIABLES------------------------------------
  double chf, nhf, cef, nef;
  int nch, nconstituents;

  //-----------------------  AK4 JETS  ----------------------------------------------
  int numjets;
  double ak4jetspt1;
  double ak4jetseta1, ak4jetsphi1;
  double ak4jetsphi2;
  double minabsdeltaphi;
  double ak4jetphi;
  double absdeltaphiak4jetmet;

  // b-tagging (pfCombinedInclusiveSecondaryVertexV2BJetTags)
  std:: vector<double> btagDisc;

  double HT, MHTx, MHTy, MHT;
  std::vector<double> ak4jetpt;
  std::vector<double> deltaRjetfatjet; 
  std::vector<double> deltaphiak4jetmetvec;
  edm::EDGetTokenT<pat::JetCollection> niceak4JetToken_;

  //------------------------  EXTRA JETS ---------------------------------------

  int extranumjets;
  double extrajetspt1;
  double extrajetphi1;
  double extraHT, extraMHTx, extraMHTy, extraMHT;
  std::vector<double> deltaPhiextrajetfatjet;
  std::vector<float> extrajetpt; 
  edm::EDGetTokenT<pat::JetCollection> niceextraJetToken_;

  //--------------------DELTAS ------------------------------------------------------- 
  double deltaphijetmet;
  //-------------------CANDIDATES MASS -----------------------------------------------
  double candTMass; // transverse mass

  double rho; // energy density

  // Leptons
  edm::EDGetTokenT<pat::MuonCollection> muonToken_;
  edm::EDGetTokenT<pat::ElectronCollection> electronToken_;
  edm::EDGetTokenT<pat::PhotonCollection> photonToken_;
 
  std::vector<double> muonsPT; 
  std::vector<double> muonsETA;
  std::vector<double> electronsPT;
  std::vector<double> electronsETA;
  std::vector<double> photonsPT;
  std::vector<double> photonsETA;
  std::vector<double> btaggjetsPT;
  std::vector<double> btaggjetsETA;

  int nmuons, nelectrons, nphotons, nbtaggjets;
  int nmuonsBefMatch, nelectronsBefMatch, nphotonsBefMatch;

  double mmDeltaR, MinmmDeltaR;
  std::vector<double> deltaRMu; 

  double eeDeltaR, MineeDeltaR;
  std::vector<double> deltaREle;

  double ppDeltaR, MinppDeltaR;
  std::vector<double> deltaRPho;


  // btagging info
  double bdisc;
  double taggWeight;
  double notaggWeight;
  double MCBtaggweight;
  double btaggWeight;
  edm::FileInPath btaggEff_;
  TFile *effBtagMap;
  TH2D *effBtagMaphisto;
  int partonFlavorValue;

  TF1 *CSVM_SFb_30to670pt;

  //------------------- GEN INFORMATION ------------------------
  edm::EDGetTokenT<reco::CandidateCollection> genleptonicZ_;
  edm::EDGetTokenT<reco::CandidateCollection> genleptonicW_;
  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  edm::EDGetTokenT<edm::View<pat::PackedGenParticle> > packedGenToken_;
  double genptZl, genptWl;
  int numgenZ, numgenW;


  edm::FileInPath triggerSFs_;


  void setDummyValues();
 
  TFile *f1, *f2, *f3, *f4, *f5, *f6, *f7, *file1;
  TH1D *h1;
  TF1 *fun1, *fun2;
  TH2F *h2, *h3, *h4, *h5, *h6; 
  TH1F *h7;

  double getEfficiency( const double& pt, const double& eta) {
     double eff = 1.;
     TH2D *thisHist = effBtagMaphisto;
     int binx = thisHist->GetXaxis()->FindBin(pt);
     int biny = thisHist->GetYaxis()->FindBin(eta);
     eff = thisHist->GetBinContent(binx, biny);
    return eff;
     }


 
};

//
// constructors and destructor
//
EDBRTreeMaker::EDBRTreeMaker(const edm::ParameterSet& iConfig):
  isGen_           (                                   iConfig.getParameter<bool>          ( "isGen"             ) ),
  correctEW_       (                                   iConfig.getParameter<bool>          ( "correctEW"         ) ),
  correctBtag_     (                                   iConfig.getParameter<bool>          ( "correctBtag"       ) ),
  originalNEvents_ (                                   iConfig.getParameter<int>           ( "originalNEvents"   ) ),
  crossSectionPb_  (                                   iConfig.getParameter<double>        ( "crossSectionPb"    ) ),
  targetLumiInvPb_ (                                   iConfig.getParameter<double>        ( "targetLumiInvPb"   ) ),
  EDBRChannel_     (                                   iConfig.getParameter<std::string>   ( "EDBRChannel"       ) ),
  vertexToken_     ( consumes<reco::VertexCollection>( iConfig.getParameter<edm::InputTag> ( "vertex"          ) ) ),
  niceak4JetToken_ ( consumes<pat::JetCollection>    ( iConfig.getParameter<edm::InputTag> ( "niceak4JetsSrc"   ) )),
  niceextraJetToken_ ( consumes<pat::JetCollection>    ( iConfig.getParameter<edm::InputTag> ( "niceextraJetsSrc" ) )),
  muonToken_       ( consumes<pat::MuonCollection>   ( iConfig.getParameter<edm::InputTag> (  "muons"             ) ) ),
  electronToken_(consumes<pat::ElectronCollection>(iConfig.getParameter<edm::InputTag>("electrons"))),
  photonToken_(consumes<pat::PhotonCollection>(iConfig.getParameter<edm::InputTag>("photons"))),
  prunedGenToken_(consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned"))),
  packedGenToken_(consumes<edm::View<pat::PackedGenParticle> >(iConfig.getParameter<edm::InputTag>("packed")))
{

   using namespace edm;

   if( iConfig.existsAs<bool>("isData") )
        isData_ = iConfig.getParameter<bool> ("isData");
   else isData_ = true;



   if( iConfig.existsAs<edm::FileInPath>("puWeights") )
        puWeights_ = iConfig.getParameter<edm::FileInPath>("puWeights") ;

  if( iConfig.existsAs<FileInPath>("EWcorr") )
     EWcorr_ = iConfig.getParameter<FileInPath>("EWcorr") ;

    if( iConfig.existsAs<FileInPath>("elrecoSFs") )
     elrecoSFs_ = iConfig.getParameter<FileInPath>("elrecoSFs") ;

  if( iConfig.existsAs<FileInPath>("electronsSFs") )
     electronsSFs_ = iConfig.getParameter<FileInPath>("electronsSFs") ;

  if( iConfig.existsAs<FileInPath>("muonSFs") )
     muonSFs_ = iConfig.getParameter<FileInPath>("muonSFs") ;

  if( iConfig.existsAs<FileInPath>("muIsoSFs") )
     muIsoSFs_ = iConfig.getParameter<FileInPath>("muIsoSFs") ;

  if( iConfig.existsAs<FileInPath>("photonsSFs") )
     photonsSFs_ = iConfig.getParameter<FileInPath>("photonsSFs") ;

  if( iConfig.existsAs<FileInPath>("btaggEff") )
     btaggEff_ = iConfig.getParameter<FileInPath>("btaggEff");


  if( iConfig.existsAs<FileInPath>("triggerSFs") )
     triggerSFs_ = iConfig.getParameter<FileInPath>("triggerSFs") ;



  rhoToken          = consumes<double>(          InputTag("fixedGridRhoFastjetAll"            ));
  gravitonsToken    = consumes<reco::CompositeCandidateView>(  InputTag("graviton","","TEST"  ));
  puInfoToken       = consumes<std::vector<PileupSummaryInfo>>(InputTag("slimmedAddPileupInfo"));
  genEvtInfoToken   = consumes<GenEventInfoProduct>(           InputTag("generator"           ));


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


   // function for b-tagging SF
   CSVM_SFb_30to670pt = new TF1("CSVM_SFb_30to670pt","0.934588*((1.+(0.00678184*x))/(1.+(0.00627144*x)))",30.,670.);


  
  //now do what ever initialization is needed
  outTree_ = fs->make<TTree>("EDBRCandidates","EDBR Candidates");

  /// Basic event quantities
  outTree_->Branch("event"           ,&nevent         ,"event/I"          );
  outTree_->Branch("run"             ,&run            ,"run/I"            );
  outTree_->Branch("lumisec"         ,&lumisec        ,"lumisec/I"        );
  outTree_->Branch("nVtx"            ,&nVtx           ,"nVtx/I"           );
  outTree_->Branch("numCands"        ,&numCands       ,"numCands/I"       );
  outTree_->Branch("ptVhad"          ,&ptVhad         ,"ptVhad/D"         );
  outTree_->Branch("yVhad"           ,&yVhad          ,"yVhad/D"          );
  outTree_->Branch("phiVhad"         ,&phiVhad        ,"phiVhad/D"        );
  outTree_->Branch("massVhad"        ,&massVhad       ,"massVhad/D"       );
  outTree_->Branch("tau1"            ,&tau1           ,"tau1/D"           );
  outTree_->Branch("tau2"            ,&tau2           ,"tau2/D"           );
  outTree_->Branch("tau3"            ,&tau3           ,"tau3/D"           );
  outTree_->Branch("tau21"           ,&tau21          ,"tau21/D"          );
  outTree_->Branch("region"          ,&reg            ,"region/I"         );
  outTree_->Branch("channel"         ,&channel        ,"channel/I"        );
  outTree_->Branch("candTMass"       ,&candTMass      ,"candTMass/D"      );

  
  /// Generic kinematic quantities
  outTree_->Branch("numjets"         ,&numjets        ,"numjets/I"        );
  outTree_->Branch("extranumjets"    ,&extranumjets   ,"extranumjets/I"   );
  outTree_->Branch("ptjet1"          ,&ptjet1         ,"ptjet1/D"         );
  outTree_->Branch("etjet1"          ,&etjet1         ,"etjet1/D"         );
  outTree_->Branch("etajet1"         ,&etajet1        ,"etajet1/D"        );
  outTree_->Branch("phijet1"         ,&phijet1        ,"phijet1/D"        );
  outTree_->Branch("massjet1"        ,&massjet1       ,"massjet1/D"       );
  outTree_->Branch("softjet1"        ,&softjet1       ,"softjet1/D"       );
  outTree_->Branch("prunedjet1"      ,&prunedjet1     ,"prunedjet1/D"     );
  outTree_->Branch("metpt"           ,&metpt          ,"metpt/D"          );
  outTree_->Branch("metphi"          ,&metphi         ,"metphi/D"         );
  outTree_->Branch("metpx"           ,&metpx          ,"metpx/D"          );
  outTree_->Branch("metpy"           ,&metpy          ,"metpy/D"          );
  outTree_->Branch("HT"              ,&HT             ,"HT/D"             );
  outTree_->Branch("MHT"             ,&MHT            ,"MHT/D"            );
  outTree_->Branch("MHTx"            ,&MHTx           ,"MHTx/D"           );
  outTree_->Branch("MHTy"            ,&MHTy           ,"MHTy/D"           );
  outTree_->Branch("extraHT"         ,&extraHT        ,"extraHT/D"        );
  outTree_->Branch("extraMHT"        ,&extraMHT       ,"extraMHT/D"       );
  outTree_->Branch("extraMHTx"       ,&extraMHTx      ,"extraMHTx/D"      );
  outTree_->Branch("extraMHTy"       ,&extraMHTy      ,"extraMHTy/D"      );
  outTree_->Branch("sumET"           ,&sumET          ,"sumET/D"          );
  outTree_->Branch("rawmetpt"        ,&rawmetpt       ,"rawmetpt/D"       );
  outTree_->Branch("rawmetphi"       ,&rawmetphi      ,"rawmetphi/D"      );
  outTree_->Branch("rawsumET"        ,&rawsumET       ,"rawsumET/D"       );
  outTree_->Branch("genmetpt"        ,&genmetpt       ,"genmetpt/D"       );
  outTree_->Branch("genmetphi"       ,&genmetphi      ,"genmetphi/D"      );
  outTree_->Branch("calometpt"       ,&calometpt      ,"calometpt/D"      );
  outTree_->Branch("calometphi"      ,&calometphi     ,"calometphi/D"     );
  outTree_->Branch("calometsumET"    ,&calometsumET   ,"calometsumET/D"   );
  outTree_->Branch("metcorrptup"     ,&metcorrptup    ,"metcorrptup/D"    );
  outTree_->Branch("metcorrptdown"   ,&metcorrptdown  ,"metcorrptdown/D"  );
  outTree_->Branch("minabsdeltaphi"  ,&minabsdeltaphi ,"minabsdeltaphi/D" );

  /// Other quantities
  outTree_->Branch("triggerWeight"   ,&triggerWeight  ,"triggerWeight/D"  );
  outTree_->Branch("lumiWeight"      ,&lumiWeight     ,"lumiWeight/D"     );
  outTree_->Branch("pileupWeight"    ,&pileupWeight   ,"pileupWeight/D"   );
  outTree_->Branch("genWeight"       ,&genWeight      ,"genWeight/D"      );
  outTree_->Branch("electronWeight"  ,&electronWeight ,"electronWeight/D"      );
  outTree_->Branch("electronrecoWeight"   ,&electronrecoWeight, "electronrecoWeight/D" );
  outTree_->Branch("photonWeight"    ,&photonWeight   ,"photonWeight/D"   );
  outTree_->Branch("muonWeight"      ,&muonWeight     ,"muonWeight/D"     );
  outTree_->Branch("muonisoWeight"      ,&muonisoWeight     ,"muonisoWeight/D"     );
  outTree_->Branch("vetobtaggWeight"    ,&vetobtaggWeight, "vetobtaggWeight/D"  );
  outTree_->Branch("totalWeight"     ,&totalWeight    ,"totalWeight/D"    );
  outTree_->Branch("deltaphijetmet"    ,&deltaphijetmet   ,"deltaphijetmet/D"   );
  outTree_->Branch("ak4jetpt"          ,&ak4jetpt     );
  outTree_->Branch("extrajetpt"       ,&extrajetpt  );
  outTree_->Branch("deltaRjetfatjet" ,&deltaRjetfatjet );
  outTree_->Branch("deltaPhiextrajetfatjet"  ,&deltaPhiextrajetfatjet);

  /// Jet ID variables
  outTree_->Branch("chf"   ,&chf  ,"chf/D"  );
  outTree_->Branch("nhf"   ,&nhf  ,"nhf/D"     );
  outTree_->Branch("cef"   ,&cef  ,"cef/D"   );
  outTree_->Branch("nef"   ,&nef  ,"nef/D"   );
  outTree_->Branch("nch"   ,&nch  ,"nch/I"   );
  outTree_->Branch("nconstituents"  ,&nconstituents  ,"nconstituents/I"   );

  /// Leptons
  outTree_->Branch("nelectrons"   ,&nelectrons  ,"nelectrons/I"  );
  outTree_->Branch("nelectronsBefMatch"    ,&nelectronsBefMatch    ,"nelectronsBefMatch/I"  );
  outTree_->Branch("nmuons"   ,&nmuons  ,"nmuons/I"  );
  outTree_->Branch("nmuonsBefMatch"    ,&nmuonsBefMatch    ,"nmuonsBefMatch/I"  );
  outTree_->Branch("nphotons"   ,&nphotons  ,"nphotons/I"  );
  outTree_->Branch("nphotonsBefMatch"    ,&nphotonsBefMatch    ,"nphotonsBefMatch/I"  );
  outTree_->Branch("nbtaggjets"   ,&nbtaggjets  ,"nbtaggjets/I"  );
  outTree_->Branch("muonsPT"      ,&muonsPT     );
  outTree_->Branch("muonsETA"      ,&muonsETA     );
  outTree_->Branch("electronsPT"      ,&electronsPT     );
  outTree_->Branch("electronsETA"      ,&electronsETA     );
  outTree_->Branch("photonsPT"      ,&photonsPT     );
  outTree_->Branch("photonsETA"      ,&photonsETA     );
  outTree_->Branch("btaggjetsPT"      ,&btaggjetsPT     );
  outTree_->Branch("btaggjetsETA"      ,&btaggjetsETA     );
  outTree_->Branch("MinmmDeltaR"       ,&MinmmDeltaR, "MinmmDeltaR/D"  );
  outTree_->Branch("MineeDeltaR"       ,&MineeDeltaR, "MineeDeltaR/D"  );
  outTree_->Branch("MinppDeltaR"       ,&MinppDeltaR, "MinppDeltaR/D"  );

  outTree_->Branch("ptCorUp" ,&ptCorUp ,"ptCorUp/D" );
  outTree_->Branch("ptCorDown" ,&ptCorDown ,"ptCorDown/D" );


}


EDBRTreeMaker::~EDBRTreeMaker() {}

// ------------ method called for each event  ------------
void
EDBRTreeMaker::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;
   using namespace reco;

   nevent  = iEvent.eventAuxiliary().event();
   run     = iEvent.eventAuxiliary().run();
   lumisec = iEvent.eventAuxiliary().luminosityBlock();

   setDummyValues(); //Initalize variables with dummy values

   Handle<reco::CompositeCandidateView > gravitons;
   iEvent.getByToken(gravitonsToken, gravitons);
   numCands = gravitons->size();


   if(numCands != 0 ) {

       const reco::Candidate& graviton = gravitons->at(0);


      if (correctEW_){

          Handle<edm::View<reco::GenParticle> > pruned;
          iEvent.getByToken(prunedGenToken_,pruned);

          // genZ
          int cont = 0;    
          for(size_t i=0; i<pruned->size();i++){
              if(abs((*pruned)[i].pdgId()) ==  23 ){
                  cont = cont+1; 
                  const Candidate *Zlep  = &(*pruned)[i];
                  genptZl = Zlep->pt();
                 if (cont>0) break;
             }
           }

           // genW
           int cont2 = 0;
           for(size_t j=0; j<pruned->size();j++){
              if(abs((*pruned)[j].pdgId()) ==  24 ){
                  cont2 = cont2+1; 
                  const Candidate *Wlep  = &(*pruned)[j];
                  genptWl = Wlep->pt();
                  if (cont2>0) break;
               }
            }
        }


        // All the quantities which depend on RECO could go here
        if(not isGen_) {
        
          // handle goodOfflinePrimaryVertex collection   
          Handle<reco::VertexCollection> vertices;
          iEvent.getByToken(vertexToken_, vertices);
          nVtx = vertices->size();
          

          // energy density
          Handle< double > rhoHandle;
          iEvent.getByToken(rhoToken, rhoHandle);
          rho = (float)(*rhoHandle);


          //we put the definitions inside the channel
          switch(channel){
              case VZ_CHANNEL:{                  
                   break;}
               case VW_CHANNEL:{
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
                   massVhad     = hadronicVnu.userFloat("ak8PFJetsCHSCorrPrunedMass");
                   ptCorUp      = hadronicVnu.userFloat("ptCorUp");
                   ptCorDown    = hadronicVnu.userFloat("ptCorDown");
//                   massVhad = prunedjet1 * prunedMassCorrection( rho, nVtx, hadronicVnu, JetCorParColl ); 
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
                   if ( !isData_ ){
                        genmetpt   =  goodMET.genMET()->pt();
                        genmetphi  =  goodMET.genMET()->phi();
                   }  
                   //// The Calo MET
                   calometpt     =   goodMET.caloMETPt();
                   calometphi    =   goodMET.caloMETPhi();
                   calometsumET  =   goodMET.caloMETSumEt();

                  /// MET UNCERTAINTIES                 
                   metcorrptup   = goodMET.shiftedPt(pat::MET::JetEnUp); 
                   metcorrptdown = goodMET.shiftedPt(pat::MET::JetEnDown);                  
                   ////-----------------------------------------------------------------------------------////
                   ////--------------------------------  AK4 JETS  ---------------------------------------////
                   ////-----------------------------------------------------------------------------------////
                   ak4jetpt.clear();
                   deltaRjetfatjet.clear();
                   deltaphiak4jetmetvec.clear();
                   Handle<pat::JetCollection> jatos;
                   iEvent.getByToken(niceak4JetToken_, jatos);
                   ////--- NUMBER OF JETS ----//// 
                   numjets = jatos->size(); 
                   //// Min deltaPhi(ak4jet, MET) 
                   for(unsigned int k = 0; k != jatos->size(); ++k) {
                       const pat::Jet& ak4jet = jatos->at(k);
                         ak4jetphi = ak4jet.phi();
                         absdeltaphiak4jetmet = abs(deltaPhi(ak4jetphi, metphi)); 
                         deltaphiak4jetmetvec.push_back(absdeltaphiak4jetmet);
                   //// B-Tagging
                   //      btagDisc.push_back(ak4jet.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags"));
                   }       
                   // sort
                   std::sort( deltaphiak4jetmetvec.begin(), deltaphiak4jetmetvec.end());
                   // mindeltaPhi
                   if (deltaphiak4jetmetvec.size()){
                       minabsdeltaphi = deltaphiak4jetmetvec[0];
                   }
                 
                   ////--------  HT AND MHT  -------------////
                   HT=0;
                   MHTx = 0, MHTy = 0; 
                   for(unsigned int i = 0; i != jatos->size(); ++i) {
                            const pat::Jet& jet1 = jatos->at(i);
                            ak4jetspt1    =  jet1.pt(); 
                            ak4jetseta1   =  jet1.eta();
                            ak4jetsphi1   =  jet1.phi();
                            HT += ak4jetspt1;
                            MHTx -= jet1.px();
                            MHTy -= jet1.py(); 
                            ak4jetpt.push_back(ak4jetspt1); 
                            deltaRjetfatjet.push_back(jet1.userFloat("deltaRjetfatjet"));               
                    }         
                    MHT = sqrt( MHTx*MHTx + MHTy*MHTy );
                   ////-----------------------------------------------------------------------------
                   //// --------------   EXTRA JETS -----------------------------------------------
                   ////--------------------------------------------------------------------------
                   extrajetpt.clear();                 
                   deltaPhiextrajetfatjet.clear();
                   Handle<pat::JetCollection> extrajatos;
                   iEvent.getByToken(niceextraJetToken_, extrajatos);
                   extranumjets = extrajatos->size(); 
                   extraHT=0;
                   extraMHTx = 0, extraMHTy = 0;
                   for(unsigned int j = 0; j != extrajatos->size(); ++j) {
                           const pat::Jet& jat1 = extrajatos->at(j);
                           extrajetspt1    =  jat1.pt();
                           extrajetphi1    =  jat1.phi();
                           extraHT += extrajetspt1;
                           extraMHTx -= jat1.px();
                           extraMHTy -= jat1.py();
                           extrajetpt.push_back(extrajetspt1);    
                           deltaPhiextrajetfatjet.push_back(abs(deltaPhi(extrajetphi1,phiVhad)));
                   }
                   extraMHT = sqrt( extraMHTx*extraMHTx + extraMHTy*extraMHTy );
                   ////---------------------------------------------------------------------------////
                    ////--------------------------  OTHER VARIABLES  ------------------------------////
                    ////---------------------------------------------------------------------------////
                    ////delta Phi between jet and met(from graviton) 
                    deltaphijetmet = deltaPhi(phijet1, metphi);
                    // transverse candidate mass for JET + MET
                    candTMass    = sqrt(abs(2*ptjet1*metpt*(1-cos(deltaphijetmet))));       

                    //---------- Leptons Information --------------------------------
                    std::vector<const pat::Muon*> muonsVec;
                    std::vector<const pat::Muon*> Matchmuons;
                    std::vector<const pat::Electron*> electronsVec;
                    std::vector<const pat::Electron*> Matchelectrons;
                    std::vector<const pat::Photon*> photonsVec;
                    std::vector<const pat::Photon*> Matchphotons;
                    std::vector<const pat::Jet*> btaggjetsVec;
                    electronsPT.clear();
                    electronsETA.clear();
                    muonsPT.clear();
                    muonsETA.clear();
                    photonsPT.clear();
                    photonsETA.clear();
                    btaggjetsPT.clear();
                    btaggjetsETA.clear();

                    // Packed gen collection
                   Handle<edm::View<pat::PackedGenParticle> > packed;
                   iEvent.getByToken(packedGenToken_,packed);
                    
//*****************************************************************
//                           MUONS
//****************************************************************
                   deltaRMu.clear();
                   edm::Handle<pat::MuonCollection> muons;
                   iEvent.getByToken(muonToken_, muons);
                   for (const pat::Muon &mu : *muons) {
                         if (mu.pt() < 10 ) continue;
                         if ( fabs(mu.eta()) > 2.4 ) continue;

                         // Veto Muons selection
                         if (!mu.isPFMuon()) continue;
                         if (mu.isLooseMuon() == false) continue;
                         if ((mu.pfIsolationR04().sumChargedHadronPt+max(0.,mu.pfIsolationR04().sumNeutralHadronEt+mu.pfIsolationR04().sumPhotonEt-0.5*mu.pfIsolationR04().sumPUPt))/mu.pt()> 0.25) continue;

                         // MC Match
                         for(const pat::PackedGenParticle& genmu : *packed){
                             if ( ! (fabs (genmu.pdgId()) == 13) ) continue;
                             if ( fabs(genmu.eta()) > 2.4 ) continue;
                             if ((mu.charge()*genmu.charge()) < 0 ) continue;
                             Candidate::LorentzVector Recmu = mu.p4();
                             Candidate::LorentzVector Genmu = genmu.p4();
                             mmDeltaR = deltaR(Recmu, Genmu);
                             deltaRMu.push_back(mmDeltaR);
                          }                         

                         muonsVec.push_back(&mu);
                  }

                  // sort the collections
                  std::sort(muonsVec.begin(),muonsVec.end(),RefGreaterByPt<pat::Muon>());
                  std::sort(deltaRMu.begin(),deltaRMu.end());

                  //save the min deltaR
                  if (deltaRMu.size()){
                   MinmmDeltaR = deltaRMu[0];
                  }
                  // number of muons before match
                  nmuonsBefMatch = muonsVec.size();
                      
                 // The matching and save the objects
                 BOOST_FOREACH(const pat::Muon* Mu, muonsVec) {
                     if ( MinmmDeltaR < 0.1){
                          Matchmuons.push_back(Mu);
                          double Mupt = Mu->pt();
                          double Mueta = fabs(Mu->eta());
                          muonsPT.push_back(Mupt);
                          muonsETA.push_back(Mueta);
                     }
                   }

                 // Number of match muons
                 std::sort(Matchmuons.begin(),Matchmuons.end(),RefGreaterByPt<pat::Muon>());
                 nmuons = Matchmuons.size();

//*****************************************************************
////                           ELECTRONS
////****************************************************************
                   deltaREle.clear();              
                   edm::Handle<pat::ElectronCollection> electrons;
                   iEvent.getByToken(electronToken_, electrons);
                   for (const pat::Electron &el : *electrons) {
                         if (el.pt()<10) continue;
                         if ( fabs(el.eta()) > 2.4 ) continue;

                         // veto electron selection
                         if(! el.electronID("cutBasedElectronID-Spring15-25ns-V1-standalone-veto")) continue;

                         //Delta R
                         for(const pat::PackedGenParticle& genele : *packed){
                             if ( ! (fabs (genele.pdgId()) == 11) ) continue;
                             if ( fabs(genele.eta()) > 2.4 ) continue;
                             if ((el.charge()*genele.charge()) < 0 ) continue;
                             Candidate::LorentzVector Recele = el.p4();
                             Candidate::LorentzVector Genele = genele.p4();
                             eeDeltaR = deltaR(Recele, Genele);
                             deltaREle.push_back(eeDeltaR);
                          }
    
                          electronsVec.push_back(&el);                        
                    }

                    // sort
                    std::sort(electronsVec.begin(),electronsVec.end(),RefGreaterByPt<pat::Electron>());
                    std::sort(deltaREle.begin(),deltaREle.end());
                       
                    // Save min deltaR
                   if (deltaREle.size()){
                   MineeDeltaR = deltaREle[0];
                   }

                  // number of electrons before match
                  nelectronsBefMatch = electronsVec.size();

                  // the matching
                  BOOST_FOREACH(const pat::Electron* El, electronsVec) {
                     if ( MineeDeltaR < 0.1){
                          Matchelectrons.push_back(El);
                          double Elept = El->pt();
                          double Eleeta = fabs(El->superCluster()->eta());
                          electronsPT.push_back(Elept);
                          electronsETA.push_back(Eleeta);
                     }
                   }


                 std::sort(Matchelectrons.begin(),Matchelectrons.end(),RefGreaterByPt<pat::Electron>());
                 nelectrons = Matchelectrons.size();



//*****************************************************************
//////                           PHOTONS
//////****************************************************************

                deltaRPho.clear(); 
                edm::Handle<pat::PhotonCollection> photons;
                iEvent.getByToken(photonToken_, photons);                 
                for (const pat::Photon &pho : *photons) {
                      if (pho.pt()<15) continue;
                      if ( fabs(pho.eta()) > 2.5 ) continue;

                      // ID
                      if( ! pho.photonID("cutBasedPhotonID-Spring15-50ns-V1-standalone-loose")) continue;

                      // Delta R
                      for(const pat::PackedGenParticle& genpho: *packed){
                             if ( ! (fabs (genpho.pdgId()) == 22) ) continue;
                             if ( fabs(genpho.eta()) > 2.5 ) continue;
                             Candidate::LorentzVector Recpho = pho.p4();
                             Candidate::LorentzVector Genpho = genpho.p4();
                             ppDeltaR = deltaR(Recpho, Genpho);
                             deltaRPho.push_back(ppDeltaR);
                       }

                       photonsVec.push_back(&pho);
                 }
             
                 // sort
                 std::sort(photonsVec.begin(),photonsVec.end(),RefGreaterByPt<pat::Photon>());
                 std::sort(deltaRPho.begin(),deltaRPho.end());

                 // min deltaR
                 if (deltaRPho.size()){
                   MinppDeltaR = deltaRPho[0];
                  }
  
                  // number of photons before match
                  nphotonsBefMatch = photonsVec.size();

                  // the matching
                  BOOST_FOREACH(const pat::Photon* Pho, photonsVec) {
                     if ( MinppDeltaR < 0.1){
                          Matchphotons.push_back(Pho);
                          double Phopt = Pho->pt();
                          double Phoeta = fabs(Pho->superCluster()->eta());
                          photonsPT.push_back(Phopt);
                          photonsETA.push_back(Phoeta);
                     }
                   }


                 std::sort(Matchphotons.begin(),Matchphotons.end(),RefGreaterByPt<pat::Photon>());
                 nphotons = Matchphotons.size();


//*****************************************************************
////////                          BTAG JETS
////////**************************************************************
  
                for (const pat::Jet &j : *extrajatos) {
                      bdisc = j.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
           
                       
                      if (bdisc < 0.8) continue;
                       
                          btaggjetsVec.push_back(&j);
                          btaggjetsPT.push_back(j.pt());
                          btaggjetsETA.push_back(j.eta());
                }


                            


              std::sort(btaggjetsVec.begin(),btaggjetsVec.end(),RefGreaterByPt<pat::Jet>());
              nbtaggjets = btaggjetsVec.size();


   
 
                    break;}
                case VH_CHANNEL: // This channel needs to be implemented 
                    break;

           }// close switch


       }// close not isGen
       
//------------------------------------------

        /// For data, all weights are equal to 1
        triggerWeight = 1.0;
        pileupWeight = 1.0;
        lumiWeight = 1.0;
        genWeight     = 1.0;
        ewkWeight  = 1.0;
        electronWeight = 1.0; 
        electronrecoWeight = 1.0;
        muonWeight = 1.0;
        muonisoWeight =1.0; 
        taggWeight = 1.0;
        notaggWeight = 1.0;
        btaggWeight = 1.0;
        vetobtaggWeight = 1.0;
        totalWeight = 1.0;

        if( !isData_ ) {
              // pileup reweight
              Handle<std::vector< PileupSummaryInfo > > puInfo;
              iEvent.getByToken(puInfoToken, puInfo);
                    std::vector<PileupSummaryInfo>::const_iterator PVI;
                    for(PVI = puInfo->begin(); PVI != puInfo->end(); ++PVI) {
                    int BX = PVI->getBunchCrossing();
                      if( BX == 0 ){
                            int bin = h1->FindBin(PVI->getTrueNumInteractions());
                            pileupWeight = h1->GetBinContent(bin);
                            continue;
                      }
                    }
               
              // generator weight
              edm::Handle<GenEventInfoProduct>   genEvtInfo; 
              iEvent.getByToken(genEvtInfoToken, genEvtInfo );
              genWeight = genEvtInfo->weight();
              // lumi weight
              double targetEvents = targetLumiInvPb_*crossSectionPb_;
              lumiWeight = targetEvents/originalNEvents_;
         


             // LEPTONS WEIGHTS

             if (nelectrons ==1){
                int bin1 = electronsPT[0]<200. ? h2->FindBin(electronsETA[0],electronsPT[0]) : h2->FindBin(electronsETA[0],199.);
                electronWeight = 1-(h2->GetBinContent(bin1));
                int bin2 = electronsPT[0]<200. ? h3->FindBin(electronsETA[0],electronsPT[0]) : h3->FindBin(electronsETA[0],199.);
                electronrecoWeight = 1-(h3->GetBinContent(bin2));

//                  cout << "the number os electrons is  " << nelectrons << endl;
//                 cout << "the electron weight is  " << electronWeight  << endl; 
//                  cout << "the electron reco weight is  " << electronrecoWeight  << endl;
             }


             if (nelectrons ==2){
                int bin1a = electronsPT[0]<200. ? h2->FindBin(electronsETA[0],electronsPT[0]) : h2->FindBin(electronsETA[0],199.);
                int bin1b = electronsPT[1]<200. ? h2->FindBin(electronsETA[1],electronsPT[1]) : h2->FindBin(electronsETA[1],199.);

                electronWeight = 1-( h2->GetBinContent(bin1a) * h2->GetBinContent(bin1b) );
 
                int bin2a = electronsPT[0]<200. ? h3->FindBin(electronsETA[0],electronsPT[0]) : h3->FindBin(electronsETA[0],199.);
                int bin2b = electronsPT[1]<200. ? h3->FindBin(electronsETA[1],electronsPT[1]) : h3->FindBin(electronsETA[1],199.);

                electronrecoWeight = 1-( h3->GetBinContent(bin2a) * h3->GetBinContent(bin2b) ); 

//                 cout << "the number os electrons is  " << nelectrons << endl;
//                 cout << "the electron weight is  " << electronWeight  << endl;
//                 cout << "the electron reco weight is  " << electronWeight  << endl;
             }
              
            
                if (nphotons ==1){
                int bin3 = photonsPT[0]<200. ? h4->FindBin(photonsETA[0],photonsPT[0]) : h4->FindBin(photonsETA[0],199.);
                photonWeight = 1-(h4->GetBinContent(bin3));

//                  cout << "the number of photons is  " << nphotons << endl;
//                  cout << "the photon weight is  " << photonWeight  << endl;
             }

                if (nphotons ==2){
                int bin4a = photonsPT[0]<200. ? h4->FindBin(photonsETA[0],photonsPT[0]) : h4->FindBin(photonsETA[0],199.);
                int bin4b = photonsPT[1]<200. ? h4->FindBin(photonsETA[1],photonsPT[1]) : h4->FindBin(photonsETA[1],199.);
                photonWeight = 1-( h4->GetBinContent(bin4a) * h4->GetBinContent(bin4b) );

//                  cout << "the number of photons is  " << nphotons << endl;
//                  cout << "the photon weight is  " << photonWeight  << endl;
             }


               if (nmuons ==1){
                int bin5 = muonsPT[0]<120. ? h5->FindBin(muonsETA[0],muonsPT[0]) : h5->FindBin(muonsETA[0],119.);
                muonWeight = 1-(h5->GetBinContent(bin5));
                int bin6 = muonsPT[0]<120. ? h6->FindBin(muonsETA[0],muonsPT[0]) : h6->FindBin(muonsETA[0],119.);
                muonisoWeight = 1-(h6->GetBinContent(bin6));

//                  cout << "the number os muons is  " << nmuons << endl;
//                  cout << "the muon weight is  " << muonWeight  << endl;
//                  cout << "the muon iso weight is  " << muonisoWeight  << endl;
             }


             if (nmuons ==2){
                int bin5a = muonsPT[0]<120. ? h5->FindBin(muonsETA[0],muonsPT[0]) : h5->FindBin(muonsETA[0],119.);
                int bin5b = muonsPT[1]<120. ? h5->FindBin(muonsETA[1],muonsPT[1]) : h5->FindBin(muonsETA[1],119.);

                muonWeight = 1-( h5->GetBinContent(bin5a) * h5->GetBinContent(bin5b) );

                int bin6a = muonsPT[0]<120. ? h6->FindBin(muonsETA[0],muonsPT[0]) : h6->FindBin(muonsETA[0],119.);
                int bin6b = muonsPT[1]<120. ? h6->FindBin(muonsETA[1],muonsPT[1]) : h6->FindBin(muonsETA[1],119.);

                muonisoWeight = 1-( h6->GetBinContent(bin6a) * h6->GetBinContent(bin6b) );

//                 cout << "the number of muons is  " << nmuons << endl;
//                 cout << "the muon weight is  " << muonWeight  << endl;
//                 cout << "the muon iso weight is  " << muonisoWeight  << endl;
             }



            
         if (correctBtag_){
             // b-tagg jets weight
             Handle<pat::JetCollection> extrajat;
             iEvent.getByToken(niceextraJetToken_, extrajat);
             for (const pat::Jet &jat : *extrajat) {
                    
                   double  jatpt   = jat.pt();
                   double  jateta  = jat.eta();
                   double  bDisc   = jat.bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
                   int PartonFlavorValue = jat.partonFlavour();

                   if (fabs(PartonFlavorValue) !=5) continue;
                   if (fabs(jateta) > 2.4 ) continue;
                   if ( jatpt > 650. ) continue;
                   if ( jatpt<20. ) continue;

                   double scalefactor = CSVM_SFb_30to670pt->Eval(jatpt);  
//                   cout << "the SF:  " << scalefactor << endl;      
                   double effMC = getEfficiency(jatpt, jateta);
//                   cout << "the eff  :  " << effMC << endl;
                   if ((scalefactor != 0) && (effMC!= 0)){      
                     if (bDisc >= 0.8){
                                         taggWeight *= scalefactor;
                     }
                     else{
                              notaggWeight *= ( 1-(scalefactor*effMC)) / (1-effMC);
                     }
                  }
         
             }
             

            if (nbtaggjets>0 ){    

             btaggWeight = taggWeight*notaggWeight;
             vetobtaggWeight = 1 - btaggWeight;
//             cout << "............... EVENT ................  " << endl;
//             cout << "the number of b-tagg jets is  " << nbtaggjets << endl;
//             cout << "the b-tagg weight is  " << btaggWeight  << endl;     
//             cout << "the veto b-tagg weight is  " << vetobtaggWeight  << endl;  
            } 

         }// end of correct Btag 


     if (correctEW_){

         // Electroweak corrections for Z+jets
         // before 123 GeV, the function gives Zero

         if ( genptZl > 123){
              ewkWeight = fun1->Eval(genptZl);
         }

               
         if ( genptWl > 123){
              ewkWeight = fun2->Eval(genptWl);
         }
          
     }



     // Trigger weight
     if( metpt>250){
                int bin7 =  h7->FindBin(metpt);
                triggerWeight = (h7->GetBinContent(bin7));

      }


} // end of is ! data

 // total weight         
 totalWeight = triggerWeight*pileupWeight*lumiWeight*(genWeight/abs(genWeight))*ewkWeight*electronWeight*electronrecoWeight*photonWeight*muonWeight*muonisoWeight*vetobtaggWeight;

//-----------------------------------------


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

  } // end of numcandidate != 0

   else {
       /// If we arrive here, that means we have NOT found a resonance candidate,
       /// i.e. numCands == 0.
       outTree_->Fill();
       //return; // skip event if there is no resonance candidate
   }

}




void EDBRTreeMaker::setDummyValues() {
     nVtx           = -1e4;
     triggerWeight  =  1;
     pileupWeight   = 1;
     lumiWeight     = 1;
     totalWeight    = 1;
     electronWeight = 1;
     electronrecoWeight = 1;
     photonWeight   = 1;
     muonWeight     = 1;
     muonisoWeight  = 1;
     vetobtaggWeight = 1;
     ptVhad         = -1e4;
     yVhad          = -1e4;
     phiVhad        = -1e4;
     massVhad       = -1e4;
     ptCorUp = -1e4;
     ptCorDown = -1e4;
     tau1           = -1e4;
     tau2           = -1e4;
     tau3           = -1e4;
     tau21          = -1e4;
     numjets        = -1e4;
     extranumjets   = -1e4; 
     etjet1         = -1e4;
     ptjet1         = -1e4;
     etajet1        = -1e4;
     phijet1        = -1e4;
     massjet1       = -1e4;
     softjet1       = -1e4;
     prunedjet1     = -1e4;
     metpt          = -1e4;
     metphi         = -1e4;
     metpx          = -1e4;
     metpy          = -1e4;
     deltaphijetmet = -1e4; 
     reg            = -1e4;
     rho            = -1e4;
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
     metcorrptup    = -1e4;
     metcorrptdown  = -1e4;
     minabsdeltaphi = -1e4;
     nelectrons = 0;
     nmuons = 0;
     nmuonsBefMatch = 0;
     nelectronsBefMatch = 0;
     nphotonsBefMatch = 0;
     nphotons = 0;
     nbtaggjets = 0;
     MinmmDeltaR = -1e4;
     MineeDeltaR = -1e4;
     MinppDeltaR = -1e4;
}

// ------------ method called once each job just before starting event loop  ------------
void EDBRTreeMaker::beginJob(){
    if ( !isData_ ){
                  f1 = new TFile( puWeights_.fullPath().c_str() );
         h1 = (TH1D*)f1->Get("pileupWeights");
         f2 = new TFile( electronsSFs_.fullPath().c_str() );
         f3 = new TFile( elrecoSFs_.fullPath().c_str() );
         f4 = new TFile( photonsSFs_.fullPath().c_str() );
         f5 = new TFile( muonSFs_.fullPath().c_str() );
         f6 = new TFile( muIsoSFs_.fullPath().c_str() );
         f7 = new TFile( triggerSFs_.fullPath().c_str());
         h2 = (TH2F*)f2->Get("EGamma_SF2D");
         h3 = (TH2F*)f3->Get("EGamma_SF2D");
         h4 = (TH2F*)f4->Get("EGamma_SF2D");
         h5 = (TH2F*)f5->Get("MC_NUM_LooseID_DEN_genTracks_PAR_pt_spliteta_bin1/abseta_pt_ratio");
         h6 = (TH2F*)f6->Get("MC_NUM_LooseRelIso_DEN_LooseID_PAR_pt_spliteta_bin1/abseta_pt_ratio");
         h7 = (TH1F*)f7->Get("TriggerSF");
         // access to b-tagg efficiency
         effBtagMap = new TFile( btaggEff_.fullPath().c_str() );
         effBtagMaphisto = (TH2D*)effBtagMap->Get("efficiency_b");

        if (correctEW_){
         // electroweak corrections
         file1 = new TFile( EWcorr_.fullPath().c_str() );
         fun1 = (TF1*)file1->Get("ewkZcorrection");
         fun2 = (TF1*)file1->Get("ewkWcorrection"); 
         }


    } 

}

// ------------ method called once each job just after ending the event loop  ------------
void EDBRTreeMaker::endJob() {
  std::cout << "EDBRTreeMaker endJob()..." << std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(EDBRTreeMaker);
