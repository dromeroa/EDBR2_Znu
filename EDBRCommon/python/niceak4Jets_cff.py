import FWCore.ParameterSet.Config as cms


from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJetCorrFactors
from PhysicsTools.PatAlgos.producersLayer1.jetUpdater_cff import updatedPatJets
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
                         filter = cms.bool(False)
                         )



###---------JET KINEMATICS --------------------------------
ak4JETCUTS  =   "(pt > 30)  && (abs(eta) < 2.4) && (chargedHadronEnergyFraction() > 0.1) && (neutralHadronEnergyFraction() < 0.8)"

niceak4Jets = cms.EDFilter("PATJetSelector",
                                 src = cms.InputTag("selectak4Jets"),
                                 cut = cms.string(ak4JETCUTS),
                                 filter = cms.bool(False)
)

ak4JetsNuSequence = cms.Sequence(
                                    patak4JetCorrFactorsReapplyJEC  *
                                    patak4JetsReapplyJEC            *
                                    selectak4Jets                   *
                                    niceak4Jets                   
                                                                    )
                                                          





