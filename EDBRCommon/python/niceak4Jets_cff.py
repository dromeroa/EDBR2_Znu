import FWCore.ParameterSet.Config as cms


from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector

### FOR NOW WE APPLY THE JET ID, THEN WE EXPLORE THIS AS WE ARE DOING IN FAT JETS

###-------- JET ID LOOSE --------------------------------------
selectak4Jets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                         filterParams = pfJetIDSelector.clone(),
                         src = cms.InputTag("slimmedJets")
                         )



###---------JET KINEMATICS --------------------------------
niceak4Jets = cms.EDFilter("PATJetSelector",
                                 src = cms.InputTag("selectak4Jets"),
#                                 src = cms.InputTag("slimmedJets"),
                                 cut = cms.string("pt > 30 & abs(eta) < 2.4"),
                                 filter = cms.bool(True)
)


ak4JetsNuSequence = cms.Sequence(
                                    selectak4Jets         *
                                    niceak4Jets           )





