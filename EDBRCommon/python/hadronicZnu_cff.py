import FWCore.ParameterSet.Config as cms

### This add the payload to the jets in order to use later the JEC  

corrJetsProducer = cms.EDProducer ( "CorrJetsProducer",
                                     jets     =    cms.InputTag( "niceJets" ),
                                     vertex   =    cms.InputTag( "goodOfflinePrimaryVertex" ),
                                     rho      =    cms.InputTag( "fixedGridRhoFastjetAll" ),
                                     payload  =    cms.string  ( "AK8PFchs" ),
                                     isData   =    cms.bool    ( False ))


hadronicVnu = cms.EDFilter(  "CandViewSelector",
                               src      =      cms.InputTag("corrJetsProducer:corrJets"),
                               cut      =      cms.string('pt>200. & abs(eta)<2.4\
                                               userFloat("ak8PFJetsCHSCorrPrunedMass")>40. & \
                                               userFloat("ak8PFJetsCHSCorrPrunedMass")<220.'),
                               filter   =      cms.bool(True) )


hadronicVnuSequence = cms.Sequence( corrJetsProducer   *
                                    hadronicVnu        )

