import FWCore.ParameterSet.Config as cms

from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJets
from PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi import cleanPatJets
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector


patJetCorrFactorsReapplyJEC = updatedPatJetCorrFactors.clone(
                                     src = cms.InputTag("slimmedJetsAK8"),
                                     levels = ['L1FastJet','L2Relative','L3Absolute'],
                                     payload = 'AK8PFchs')



patJetsReapplyJEC = updatedPatJets.clone(
                                     jetSource = cms.InputTag("slimmedJetsAK8"),
                                     jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patJetCorrFactorsReapplyJEC") ))



###-------- JET ID LOOSE --------------------------------------
selectJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                           filterParams = pfJetIDSelector.clone(),
                           src = cms.InputTag("patJetsReapplyJEC"),
                           filter = cms.bool(True) )
                         


###---------JET KINEMATICS --------------------------------
### MONJET CUTS ##
FATJETCUTS  =   "(pt > 200) && (abs(eta) < 2.4) && (chargedHadronEnergyFraction() > 0.1) && (neutralHadronEnergyFraction() < 0.8)"  

niceJets = cms.EDFilter("PATJetSelector",
                                 src = cms.InputTag("selectJets"),
                                 cut = cms.string(FATJETCUTS),
                                 filter = cms.bool(True)
)


fatJetsNuSequence = cms.Sequence( 
                                   patJetCorrFactorsReapplyJEC  *
                                   patJetsReapplyJEC            *
                                   selectJets                   *
                                   niceJets                      
                                )





