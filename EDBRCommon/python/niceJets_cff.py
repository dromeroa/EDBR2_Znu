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



slimmedJetsSmeared = cms.EDProducer('SmearedPATJetProducer',
           src = cms.InputTag('patJetsReapplyJEC'),
           enabled = cms.bool(True),
           rho = cms.InputTag("fixedGridRhoFastjetAll"),
           resolutionFile = cms.FileInPath('ExoDiBosonResonances/EDBRJets/data/Fall15_25nsV2_MC_PtResolution_AK8PFchs.txt'),
           scaleFactorFile = cms.FileInPath('ExoDiBosonResonances/EDBRJets/data/Fall15_25nsV2_MC_SF_AK8PFchs.txt'),
           genJets = cms.InputTag('slimmedGenJetsAK8'),
           dRMax = cms.double(0.2),
           dPtMaxFactor = cms.double(3),
           debug = cms.untracked.bool(False)
           )

###-------- JET ID LOOSE --------------------------------------
selectJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                           filterParams = pfJetIDSelector.clone(),
                           src = cms.InputTag("slimmedJetsSmeared"),
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
                                   slimmedJetsSmeared           *
                                   selectJets                   *
                                   niceJets                      
                                )





