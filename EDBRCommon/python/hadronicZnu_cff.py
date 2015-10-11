import FWCore.ParameterSet.Config as cms

###--------------------------------------------------------------------------------------------
### IF WE NEED TO LOAD SOME CONFIGURATION FILES, WE CAN DEFINE A PROCESS
###
###  def hadroniZnu(process):
###
###     ### Geometry and Detector Conditions (needed for a few patTuple production steps)
###     process.load('Configuration.Geometry.GeometryIdeal_cff')
###
###     etc,...
###
###     LOOK INTO https://github.com/cms-jet/JMEDAS/blob/master/python/run2muoniso_cff.py
###---------------------------------------------------------------------------------------------

### This add the payload to the jets in order to use later the JEC  
### Then we apply a cut in the mass of the fatjets in order to select the graviton in the event with the right mass


corrJetsProducer = cms.EDProducer ( "CorrJetsProducer",
                                     jets     =    cms.InputTag( "niceJets" ),
                                     vertex   =    cms.InputTag( "goodOfflinePrimaryVertex" ),
                                     rho      =    cms.InputTag( "fixedGridRhoFastjetAll" ),
                                     payload  =    cms.string  ( "AK8PFchs" ),
                                     isData   =    cms.bool    ( False ))


hadronicVnu = cms.EDFilter(  "CandViewSelector",
                               src      =      cms.InputTag("corrJetsProducer:corrJets"),
                               cut      =      cms.string('pt > 200. & '
                                                          'userFloat("ak8PFJetsCHSCorrPrunedMass") > 40. & '
                                                          'userFloat("ak8PFJetsCHSCorrPrunedMass") < 105.  '),
                               filter   =      cms.bool(True) )


hadronicVnuSequence = cms.Sequence( corrJetsProducer   *
                                    hadronicVnu        )

