// -*- C++ -*-
//
// Package:    filterQCD/QCDfilter
// Class:      QCDfilter
// 
/**\class QCDfilter QCDfilter.cc filterQCD/QCDfilter/plugins/QCDfilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Romero Abad
//         Created:  Thu, 10 Dec 2015 10:48:37 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "TMath.h"

//
// class declaration
//

class QCDfilter : public edm::EDFilter {
   public:
      explicit QCDfilter(const edm::ParameterSet&);
      ~QCDfilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() override;
      virtual bool filter(edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      
      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      edm::EDGetTokenT<pat::JetCollection> jetToken_;
      double deltaphi_threshold_;      
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
QCDfilter::QCDfilter(const edm::ParameterSet& iConfig):
jetToken_(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets")))
{
   //now do what ever initialization is needed
   deltaphi_threshold_               = iConfig.getParameter<double>("deltaphi_threshold");
}


QCDfilter::~QCDfilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
QCDfilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   using namespace edm;
   using namespace std;

   edm::Handle<pat::JetCollection> jets;
   iEvent.getByToken(jetToken_, jets);

   int multi = jets->size();

   bool result = true;

   if (multi == 2){

               const pat::Jet &jet1 = jets->at(0);
               const pat::Jet &jet2 = jets->at(1);
               double phi1 = jet1.phi();
               double phi2 = jet2.phi();
               double deltaPhijetjetabs = TMath::Abs(deltaPhi(phi1,phi2));

               if (deltaPhijetjetabs > deltaphi_threshold_){
                   result = false;
               }       

    }


   return result;
}

// ------------ method called once each job just before starting event loop  ------------
void 
QCDfilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
QCDfilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
QCDfilter::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
QCDfilter::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
QCDfilter::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
QCDfilter::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
QCDfilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(QCDfilter);
