import FWCore.ParameterSet.Config as cms

### This add the payload to the jets in order to use later the JEC  
### Then we apply a cut in the mass of the fatjets in order to select the graviton in the event with the right mass


corrJetsProducer = cms.EDProducer ( "CorrJetsProducer",
                                     jets     =    cms.InputTag( "niceJets" ),
                                     vertex   =    cms.InputTag( "goodOfflinePrimaryVertex" ),
                                     rho      =    cms.InputTag( "fixedGridRhoFastjetAll" ),
                                     payload  =    cms.string  ( "AK8PFchs" ),
                                     isData   =    cms.bool    ( False ))


### We are not cut in jet mass for now (check this)
hadronicVnu = cms.EDFilter(  "CandViewSelector",
                               src      =      cms.InputTag("corrJetsProducer:corrJets"),
                               cut      =      cms.string('pt > 200. &  abs(eta)<2.4'),
                               filter   =      cms.bool(True) )


hadronicVnuSequence = cms.Sequence( corrJetsProducer   *
                                    hadronicVnu        )

