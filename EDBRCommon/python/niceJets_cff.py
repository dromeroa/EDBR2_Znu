import FWCore.ParameterSet.Config as cms


from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector

###-------- JET ID LOOSE --------------------------------------
selectJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                         filterParams = pfJetIDSelector.clone(),
                         src = cms.InputTag("slimmedJetsAK8")
                         )


###---------JET KINEMATICS --------------------------------
niceJets = cms.EDFilter("PATJetSelector",
                                 src = cms.InputTag("selectJets"),
                                 cut = cms.string("pt > 20 & abs(eta) < 2.4"),
                                 filter = cms.bool(True)
)

fatJetsNuSequence = cms.Sequence( selectJets         *
                                  niceJets           )





