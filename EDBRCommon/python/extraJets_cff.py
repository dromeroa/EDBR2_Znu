import FWCore.ParameterSet.Config as cms


extrajets = cms.EDProducer("extraJetsProducer",
                            jets = cms.InputTag("selectak4Jets"),
                            fatjets = cms.InputTag("bestHadronicVnu"))


###---------JET KINEMATICS --------------------------------
extraJETCUTS  =   '(pt > 30)  && (abs(eta) < 2.4) && (chargedHadronEnergyFraction() > 0.1) && (neutralHadronEnergyFraction() < 0.8) && userFloat("deltaRjetfatjet")>0.8'

niceextraJets = cms.EDFilter("PATJetSelector",
                                 src = cms.InputTag("extrajets:Jets"),
                                 cut = cms.string(extraJETCUTS),
                                 filter = cms.bool(False)

)



extraJetsNuSequence = cms.Sequence(
                                    extrajets                       * 
                                    niceextraJets 
                                                                    )




