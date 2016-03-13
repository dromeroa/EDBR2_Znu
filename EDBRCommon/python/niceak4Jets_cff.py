import FWCore.ParameterSet.Config as cms


from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJets
from PhysicsTools.PatAlgos.cleaningLayer1.jetCleaner_cfi import cleanPatJets
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector

patak4JetCorrFactorsReapplyJEC = updatedPatJetCorrFactors.clone(
                                     src = cms.InputTag("slimmedJets"),
                                     levels = ['L1FastJet','L2Relative','L3Absolute'],
                                     payload = 'AK4PFchs')


patak4JetsReapplyJEC = updatedPatJets.clone(
                                      jetSource = cms.InputTag("slimmedJets"),
                                      jetCorrFactorsSource = cms.VInputTag(cms.InputTag("patak4JetCorrFactorsReapplyJEC") ))


###-------- JET ID LOOSE --------------------------------------
selectak4Jets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                         filterParams = pfJetIDSelector.clone(),
                         src = cms.InputTag("patak4JetsReapplyJEC"),
                         filter = cms.bool(True)
                         )



###---------JET KINEMATICS --------------------------------
ak4JETCUTS  =   "(pt > 30)  && (abs(eta) < 2.4) && (chargedHadronEnergyFraction() > 0.1) && (neutralHadronEnergyFraction() < 0.8)"

niceak4Jets = cms.EDFilter("PATJetSelector",
                                 src = cms.InputTag("selectak4Jets"),
                                 cut = cms.string(ak4JETCUTS),
                                 filter = cms.bool(True)
)

#cleanak4Jets = cleanPatJets.clone()

### CLEANING
#cleanak4Jets.src = "niceak4Jets"
#cleanak4Jets.checkOverlaps.muons.src = "slimmedMuons"
#cleanak4Jets.checkOverlaps.muons.deltaR = 0.4
#cleanak4Jets.checkOverlaps.muons.requireNoOverlaps = True
#cleanak4Jets.checkOverlaps.electrons.src = "slimmedElectrons"
#cleanak4Jets.checkOverlaps.electrons.deltaR = 0.4
#cleanak4Jets.checkOverlaps.electrons.requireNoOverlaps = True
#cleanak4Jets.checkOverlaps.photons = cms.PSet()
#cleanak4Jets.checkOverlaps.taus = cms.PSet()
#cleanak4Jets.checkOverlaps.tkIsoElectrons = cms.PSet()
#cleanak4Jets.finalCut = ""


ak4JetsNuSequence = cms.Sequence(
                                    patak4JetCorrFactorsReapplyJEC  *
                                    patak4JetsReapplyJEC            *
                                    selectak4Jets                   *
                                    niceak4Jets                   
#                                    cleanak4Jets          
                                                                    )
                                                          





