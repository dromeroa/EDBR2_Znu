import FWCore.ParameterSet.Config as cms


from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector

### NOW WE ARE TESTING THE JET ID, SO WE WILL REMOVE IT AND WE HAVE TO APPLY
### AS AN OFFLINE CUT


### FOR NOW WE ONLY FOCUS IN JET ID THEN WE WILL USE PU JET ID


###-------- JET ID LOOSE --------------------------------------
selectJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                           filterParams = pfJetIDSelector.clone(),
                           src = cms.InputTag("slimmedJetsAK8")
                         )


###---------JET KINEMATICS --------------------------------
### MONJET CUTS ##
FATJETCUTS  =   "(pt > 20)  && (abs(eta) < 2.4) && (chargedHadronEnergyFraction() > 0.1) && (neutralHadronEnergyFraction() < 0.8)"  



niceJets = cms.EDFilter("PATJetSelector",
                                 src = cms.InputTag("selectJets"),
                                 cut = cms.string(FATJETCUTS),
                                 filter = cms.bool(True)
)


fatJetsNuSequence = cms.Sequence(
                                    selectJets         *
                                    niceJets           )





