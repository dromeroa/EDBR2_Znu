import FWCore.ParameterSet.Config as cms


from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector

### NOW WE ARE TESTING THE JET ID, SO WE WILL REMOVE IT AND WE HAVE TO APPLY
### AS AN OFFLINE CUT

###-------- JET ID LOOSE --------------------------------------
#selectJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
#                         filterParams = pfJetIDSelector.clone(),
#                         src = cms.InputTag("slimmedJetsAK8")
#                         )



###---------JET KINEMATICS --------------------------------
niceJets = cms.EDFilter("PATJetSelector",
#                                 src = cms.InputTag("selectJets")
                                 src = cms.InputTag("slimmedJetsAK8"),
                                 cut = cms.string("pt > 20 & abs(eta) < 2.4"),
                                 filter = cms.bool(True)
)


fatJetsNuSequence = cms.Sequence(
#                                  selectJets         *
                                  niceJets           )





