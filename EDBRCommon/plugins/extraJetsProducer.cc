// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/PatCandidates/interface/Jet.h"


#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/JetReco/interface/PFJet.h"

//
// class declaration
//

class extraJetsProducer : public edm::EDProducer {
   public:
      explicit extraJetsProducer(const edm::ParameterSet&);
      ~extraJetsProducer();

   private:
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      
      // ----------member data ---------------------------    
      edm::EDGetTokenT<pat::JetCollection>                      jetToken;
      edm::EDGetTokenT<edm::View<reco::Candidate> >            fatjetToken;
};

extraJetsProducer::extraJetsProducer(const edm::ParameterSet& iConfig):
jetToken(      consumes<pat::JetCollection>(                 iConfig.getParameter<edm::InputTag>("jets"          ) ) ),
fatjetToken(   consumes<edm::View<reco::Candidate> >(        iConfig.getParameter<edm::InputTag>("fatjets"       ) ) )
{
    produces<std::vector<pat::Jet> >("Jets");

}

extraJetsProducer::~extraJetsProducer() {}

// ------------ method called to produce the data  ------------
void
extraJetsProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
    using namespace edm;
    using namespace std;


    // handle jets
    Handle<pat::JetCollection>             jets;
    Handle<View<reco::Candidate> >         fatjets; 
    iEvent.getByToken(jetToken,            jets);
    iEvent.getByToken(fatjetToken,      fatjets);
    int jetMult=jets->size();

    
    // We consider only the leading jet for deltaR
      const reco::Candidate &fatjet1 = (*fatjets)[0];

    // output collections
    auto_ptr< vector<pat::Jet> > extraJets( new vector<pat::Jet> );
     
    for ( int i=0; i<jetMult; ++i ) {
          const pat::Jet& jet          = (*jets)[i];
          float deltaRjetfatjet       = deltaR(fatjet1,jet);
          pat::Jet* cloneJET  = jet.clone();
          cloneJET -> addUserFloat("deltaRjetfatjet", deltaRjetfatjet); 
//          if (deltaRjetfatjet > 0.8){
          extraJets->push_back(                          *cloneJET    );
//         }    
    }
    

    iEvent.put(extraJets, "Jets");

}

//define this as a plug-in
DEFINE_FWK_MODULE(extraJetsProducer);

