// -*- C++ -*-
//
// Package:    ExoDiBosonResonances/VetoesProducer
// Class:      deltaRleptonsProducer
// 
/**\class deltaRleptonsProducer deltaRleptonsProducer.cc ExoDiBosonResonances/VetoesProducer/plugins/deltaRleptonsProducer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Romero Abad
//         Created:  Wed, 13 Apr 2016 01:51:55 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/Math/interface/deltaR.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/Candidate/interface/CandidateFwd.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/PatCandidates/interface/VIDCutFlowResult.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"


//
// class declaration
//

class deltaRleptonsProducer : public edm::stream::EDProducer<> {
   public:
      explicit deltaRleptonsProducer(const edm::ParameterSet&);
      ~deltaRleptonsProducer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<pat::ElectronCollection>            electronToken;
      edm::EDGetTokenT<pat::MuonCollection>                    muonToken;
      edm::EDGetTokenT<pat::TauCollection>                      tauToken;
      edm::EDGetTokenT<edm::View<reco::Candidate> >          fatjetToken;
//      edm::EDGetTokenT<edm::ValueMap<vid::CutFlowResult> >     vetoToken;
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
deltaRleptonsProducer::deltaRleptonsProducer(const edm::ParameterSet& iConfig):
electronToken( consumes<pat::ElectronCollection>(            iConfig.getParameter<edm::InputTag>("electrons"     ) ) ),
muonToken(     consumes<pat::MuonCollection>(                iConfig.getParameter<edm::InputTag>("muons"         ) ) ),
tauToken(     consumes<pat::TauCollection>(                  iConfig.getParameter<edm::InputTag>("taus"          ) ) ),
fatjetToken(   consumes<edm::View<reco::Candidate> >(        iConfig.getParameter<edm::InputTag>("fatjets"       ) ) )
//vetoToken( consumes<edm::ValueMap<vid::CutFlowResult> >(     iConfig.getParameter<edm::InputTag>("veto"          ) ) )
{
   //register your products
   produces<std::vector<pat::Electron> >("Electrons");
   produces<std::vector<pat::Muon> >(    "Muons"    );
   produces<std::vector<pat::Tau> >(     "Taus"     ); 
}


deltaRleptonsProducer::~deltaRleptonsProducer()
{
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
deltaRleptonsProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   using namespace std;

   // handle leptons and jets
   Handle<pat::ElectronCollection>    electrons;
   Handle<pat::MuonCollection>            muons;
   Handle<pat::TauCollection>              taus;
   Handle<View<reco::Candidate> >       fatjets;
   iEvent.getByToken(electronToken,  electrons);
   iEvent.getByToken(muonToken,          muons);
   iEvent.getByToken(tauToken,            taus);
   iEvent.getByToken(fatjetToken,      fatjets);
   size_t elMult=electrons->size();
   size_t muMult=muons->size();
   size_t tauMult=taus->size();

//   Handle<ValueMap<vid::CutFlowResult> > vetoHandle;
//   iEvent.getByToken(vetoToken, vetoHandle);

   // we consider only the leading fat jet
   const reco::Candidate &fatjet1 = (*fatjets)[0];

   // output collections   
   auto_ptr< vector<pat::Electron> > niceElectrons( new vector<pat::Electron> );
   auto_ptr< vector<pat::Muon> >     niceMuons(     new vector<pat::Muon>     );
   auto_ptr< vector<pat::Tau> >      niceTaus(      new vector<pat::Tau>      );

   for ( size_t i=0; i<elMult; ++i ) {
        const Ptr<pat::Electron> elPtr(electrons, i);
        const pat::Electron& el = (*electrons)[i];
//        bool  VETO              = (*vetoHandle)[elPtr].cutFlowPassed();
        float deltaRJetEle      = deltaR(fatjet1,el);
        pat::Electron* cloneEl  = el.clone();
//        cloneEl->addUserInt("VETO",                           VETO );
        cloneEl->addUserFloat("deltaRJetEle",     deltaRJetEle     );
        niceElectrons->push_back(                      *cloneEl    );
   }
   
   for ( size_t i=0; i<muMult; ++i ) {
        const pat::Muon& mu    = (*muons)[i];
        float deltaRJetMu      = deltaR(fatjet1,mu); 
        pat::Muon* cloneMu = mu.clone();
        cloneMu->addUserFloat("deltaRJetMu",       deltaRJetMu     );
        niceMuons->push_back(                           *cloneMu   );
   }

   for ( size_t i=0; i<tauMult; ++i ) {
        const pat::Tau& ta    = (*taus)[i];
        float deltaRJetTau    = deltaR(fatjet1,ta); 
        pat::Tau* cloneTau = ta.clone();
        cloneTau->addUserFloat("deltaRJetTau",      deltaRJetTau    );
        niceTaus->push_back(                              *cloneTau );
   }



    iEvent.put(niceElectrons, "Electrons");
    iEvent.put(niceMuons,     "Muons"    );
    iEvent.put(niceTaus,      "Taus"    );
 
}


// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
deltaRleptonsProducer::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
deltaRleptonsProducer::endStream() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
deltaRleptonsProducer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
deltaRleptonsProducer::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
deltaRleptonsProducer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
deltaRleptonsProducer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
deltaRleptonsProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(deltaRleptonsProducer);
