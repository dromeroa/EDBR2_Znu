import FWCore.ParameterSet.Config as cms


from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector

### FOR NOW WE APPLY THE JET ID LOOSE, THEN WE EXPLORE THIS AS WE ARE DOING IN FAT JETS

###-------- JET ID LOOSE --------------------------------------
selectak4Jets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                         filterParams = pfJetIDSelector.clone(),
                         src = cms.InputTag("slimmedJets")
                         )



###---------JET KINEMATICS --------------------------------
ak4JETCUTS  =   "(pt > 30)  && (abs(eta) < 2.4) && (chargedHadronEnergyFraction() > 0.1) && (neutralHadronEnergyFraction() < 0.8)"

niceak4Jets = cms.EDFilter("PATJetSelector",
                                 src = cms.InputTag("selectak4Jets"),
                                 cut = cms.string(ak4JETCUTS),
                                 filter = cms.bool(True)
)


ak4JetsNuSequence = cms.Sequence(
                                    selectak4Jets         *
                                    niceak4Jets           )
                                                          





