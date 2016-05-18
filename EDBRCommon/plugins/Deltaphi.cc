// -*- C++ -*-
//
// Package:    filterQCD/Deltaphi
// Class:      Deltaphi
// 
/**\class Deltaphi Deltaphi.cc filterQCD/Deltaphi/plugins/Deltaphi.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  David Romero Abad
//         Created:  Thu, 12 Abril 2016 10:48:37 GMT
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
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/Math/interface/deltaPhi.h"
#include "TMath.h"

//
// class declaration
//

class Deltaphi : public edm::EDFilter {
   public:
      explicit Deltaphi(const edm::ParameterSet&);
      ~Deltaphi();

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
      edm::EDGetTokenT<pat::METCollection> metToken_;
      double minDeltaphi_threshold_;      
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
Deltaphi::Deltaphi(const edm::ParameterSet& iConfig):
jetToken_(consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("jets"))),
metToken_(consumes<pat::METCollection>(iConfig.getParameter<edm::InputTag>("mets")))
{
   //now do what ever initialization is needed
   minDeltaphi_threshold_               = iConfig.getParameter<double>("minDeltaphi_threshold");
}


Deltaphi::~Deltaphi()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
Deltaphi::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   using namespace edm;
   using namespace std;

   // Handle the collections
   edm::Handle<pat::JetCollection> jets;
   iEvent.getByToken(jetToken_, jets);

   edm::Handle<pat::METCollection> mets;
   iEvent.getByToken(metToken_, mets);
   const pat::MET &met = mets->front();
   double metphi = met.phi();

   bool result = false;

   vector <double> allabsdeltaphiak4jetmet;
   double minabsDeltaphi;

   // Initialize the vector
   allabsdeltaphiak4jetmet.clear();
   minabsDeltaphi = 0;

   // Loop for the jets
   for(unsigned int k = 0; k != jets->size(); ++k) {
       const pat::Jet& ak4jet = jets->at(k); 
       double ak4jetphi = ak4jet.phi();
       double absdeltaphiak4jetmet = abs(deltaPhi(ak4jetphi, metphi));
       allabsdeltaphiak4jetmet.push_back(absdeltaphiak4jetmet); 
   }

   // sort
   std::sort( allabsdeltaphiak4jetmet.begin(), allabsdeltaphiak4jetmet.end()); 

   // minabsDeltaphi
   if (allabsdeltaphiak4jetmet.size()){
       minabsDeltaphi = allabsdeltaphiak4jetmet[0];
   } 
   
   // THE FILTER   
   if (minabsDeltaphi > minDeltaphi_threshold_ ){
        result = true;
   }


   return result;
}

// ------------ method called once each job just before starting event loop  ------------
void 
Deltaphi::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
Deltaphi::endJob() {
}

// ------------ method called when starting to processes a run  ------------
/*
void
Deltaphi::beginRun(edm::Run const&, edm::EventSetup const&)
{ 
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
Deltaphi::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
Deltaphi::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
Deltaphi::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
Deltaphi::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(Deltaphi);
