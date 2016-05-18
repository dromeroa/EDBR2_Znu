// system include files
#include <iostream>
#include <memory>

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
  double totalWeight;

  bool isGen_;
  bool isData_; 
  int originalNEvents_;
  double crossSectionPb_;
  double targetLumiInvPb_;
  std::string EDBRChannel_;
  std::string gravitonSrc_, metSrc_;
  edm::FileInPath puWeights_;
  edm::FileInPath EWcorr_;
  edm::EDGetTokenT<reco::VertexCollection> vertexToken_;


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

  //------------------- GEN INFORMATION ------------------------
  edm::EDGetTokenT<reco::CandidateCollection> genleptonicZ_;
  edm::EDGetTokenT<reco::CandidateCollection> genleptonicW_;
  edm::EDGetTokenT<edm::View<reco::GenParticle> > prunedGenToken_;
  double genptZl, genptWl;
  int numgenZ, numgenW;


  void setDummyValues();
 
 
  TFile *f1, *f2;
  TH1D *h1;
  TF1 *fun1, *fun2; 
 
};

//
// constructors and destructor
//
EDBRTreeMaker::EDBRTreeMaker(const edm::ParameterSet& iConfig):
  isGen_           (                                   iConfig.getParameter<bool>          ( "isGen"             ) ),
  originalNEvents_ (                                   iConfig.getParameter<int>           ( "originalNEvents"   ) ),
  crossSectionPb_  (                                   iConfig.getParameter<double>        ( "crossSectionPb"    ) ),
  targetLumiInvPb_ (                                   iConfig.getParameter<double>        ( "targetLumiInvPb"   ) ),
  EDBRChannel_     (                                   iConfig.getParameter<std::string>   ( "EDBRChannel"       ) ),
  vertexToken_     ( consumes<reco::VertexCollection>( iConfig.getParameter<edm::InputTag> ( "vertex"          ) ) ),
  niceak4JetToken_ ( consumes<pat::JetCollection>    ( iConfig.getParameter<edm::InputTag> ( "niceak4JetsSrc"   ) )),
  niceextraJetToken_ ( consumes<pat::JetCollection>    ( iConfig.getParameter<edm::InputTag> ( "niceextraJetsSrc" ) ))
//  prunedGenToken_(consumes<edm::View<reco::GenParticle> >(iConfig.getParameter<edm::InputTag>("pruned")))
{

   using namespace edm;

   if( iConfig.existsAs<bool>("isData") )
        isData_ = iConfig.getParameter<bool> ("isData");
   else isData_ = true;

   if( iConfig.existsAs<edm::FileInPath>("puWeights") )
        puWeights_ = iConfig.getParameter<edm::FileInPath>("puWeights") ;

  if( iConfig.existsAs<FileInPath>("EWcorr") )
     EWcorr_ = iConfig.getParameter<FileInPath>("EWcorr") ;


  rhoToken          = consumes<double>(          InputTag("fixedGridRhoFastjetAll"            ));
  gravitonsToken    = consumes<reco::CompositeCandidateView>(  InputTag("graviton","","TEST"  ));
  puInfoToken       = consumes<std::vector<PileupSummaryInfo>>(InputTag("slimmedAddPileupInfo"));
  genEvtInfoToken   = consumes<GenEventInfoProduct>(           InputTag("generator"           ));

  genleptonicZ_     =consumes<reco::CandidateCollection>( InputTag("genZboson::TEST" ));
  genleptonicW_     =consumes<reco::CandidateCollection>( InputTag("genWboson::TEST" )); 


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
//  outTree_->Branch("btagDisc"        ,&btagDisc        );
//  outTree_->Branch("genptZl"         ,&genptZl         ,"genptZl/D"       );
//  outTree_->Branch("genptWl"         ,&genptWl         ,"genptWl/D"       );

  /// Other quantities
  outTree_->Branch("triggerWeight"   ,&triggerWeight  ,"triggerWeight/D"  );
  outTree_->Branch("lumiWeight"      ,&lumiWeight     ,"lumiWeight/D"     );
  outTree_->Branch("pileupWeight"    ,&pileupWeight   ,"pileupWeight/D"   );
  outTree_->Branch("genWeight"       ,&genWeight      ,"genWeight/D"      );
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

/* 
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

*/

/*
       // genZ
       Handle< reco::CandidateCollection > genZlep;
       iEvent.getByToken(genleptonicZ_ , genZlep);
       const reco::Candidate& Zlep = (*genZlep)[0];
       genptZl = Zlep.pt();
       numgenZ = genZlep->size();

       // genW
       Handle< reco::CandidateCollection > genWlep;
       iEvent.getByToken(genleptonicW_ , genWlep);
       const reco::Candidate& Wlep = (*genWlep)[0];
       genptWl = Wlep.pt();
       numgenW = genWlep->size();
*/

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

                    // Gen Information

  
                            
                  
 
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
         }

      
  

         // Electroweak corrections for Z+jets
         // before 123 GeV, the function gives Zero
/*
         if ( genptZl > 123){
              ewkWeight = fun1->Eval(genptZl);
         }

               
         if ( genptWl > 123){
              ewkWeight = fun2->Eval(genptWl);
         }
          
*/
         // total weight         
         totalWeight = triggerWeight*pileupWeight*lumiWeight*(genWeight/abs(genWeight))*ewkWeight;

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
     triggerWeight  = -1e4;
     pileupWeight   = -1e4;
     lumiWeight     = -1e4;
     totalWeight    = -1e4;
     ptVhad         = -1e4;
     yVhad          = -1e4;
     phiVhad        = -1e4;
     massVhad       = -1e4;
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
//     genptZl        = -1e4;
//     genptWl        = -1e4; 

}

// ------------ method called once each job just before starting event loop  ------------
void EDBRTreeMaker::beginJob(){
    if ( !isData_ ){
         f1 = new TFile( puWeights_.fullPath().c_str() );
         h1 = (TH1D*)f1->Get("pileupWeights");  
         // Electroweak corrections
//         f2 = new TFile( EWcorr_.fullPath().c_str() );
//         fun1 = (TF1*)f2->Get("ewkZcorrection");
//         fun2 = (TF1*)f2->Get("ewkWcorrection");      
    } 

}

// ------------ method called once each job just after ending the event loop  ------------
void EDBRTreeMaker::endJob() {
  std::cout << "EDBRTreeMaker endJob()..." << std::endl;
}

//define this as a plug-in
DEFINE_FWK_MODULE(EDBRTreeMaker);
