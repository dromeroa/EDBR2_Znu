import FWCore.ParameterSet.Config as cms



HBHENoiseFilter = cms.EDFilter("HLTHighLevel",
          TriggerResultsTag = cms.InputTag("TriggerResults","","RECO"),
          HLTPaths = cms.vstring("Flag_HBHENoiseFilter"),
          eventSetupPathsKey = cms.string(''),
          andOr = cms.bool(True),
          throw = cms.bool(True)
)


CSCTightHalo2015Filter = cms.EDFilter("HLTHighLevel",
          TriggerResultsTag = cms.InputTag("TriggerResults","","RECO"),
          HLTPaths = cms.vstring("Flag_CSCTightHalo2015Filter"),
          eventSetupPathsKey = cms.string(''),
          andOr = cms.bool(True),
          throw = cms.bool(True)
)




HBHENoiseIsoFilter = cms.EDFilter("HLTHighLevel",
          TriggerResultsTag = cms.InputTag("TriggerResults","","RECO"),
          HLTPaths = cms.vstring("Flag_HBHENoiseIsoFilter"),
          eventSetupPathsKey = cms.string(''),
          andOr = cms.bool(True),
          throw = cms.bool(True)
)


EcalDeadCellTriggerPrimitiveFilter  = cms.EDFilter("HLTHighLevel",
          TriggerResultsTag = cms.InputTag("TriggerResults","","RECO"),
          HLTPaths = cms.vstring("Flag_EcalDeadCellTriggerPrimitiveFilter"),
          eventSetupPathsKey = cms.string(''),
          andOr = cms.bool(True),
          throw = cms.bool(True)
)


muonBadTrackFilter  = cms.EDFilter("HLTHighLevel",
          TriggerResultsTag = cms.InputTag("TriggerResults","","RECO"),
          HLTPaths = cms.vstring("Flag_muonBadTrackFilter"),
          eventSetupPathsKey = cms.string(''),
          andOr = cms.bool(True),
          throw = cms.bool(True)
)



eeBadScFilter  = cms.EDFilter("HLTHighLevel",
          TriggerResultsTag = cms.InputTag("TriggerResults","","RECO"),
          HLTPaths = cms.vstring("Flag_eeBadScFilter"),
          eventSetupPathsKey = cms.string(''),
          andOr = cms.bool(True),
          throw = cms.bool(True)
)


chargedHadronTrackResolutionFilter  = cms.EDFilter("HLTHighLevel",
          TriggerResultsTag = cms.InputTag("TriggerResults","","RECO"),
          HLTPaths = cms.vstring("Flag_chargedHadronTrackResolutionFilter"),
          eventSetupPathsKey = cms.string(''),
          andOr = cms.bool(True),
          throw = cms.bool(True)
)


goodVertices  = cms.EDFilter("HLTHighLevel",
          TriggerResultsTag = cms.InputTag("TriggerResults","","RECO"),
          HLTPaths = cms.vstring("Flag_goodVertices"),
          eventSetupPathsKey = cms.string(''),
          andOr = cms.bool(True),
          throw = cms.bool(True)
)



metfilterSequence = cms.Sequence(
                                  HBHENoiseFilter                          *
                                  CSCTightHalo2015Filter                   *
                                  HBHENoiseIsoFilter                       *
                                  EcalDeadCellTriggerPrimitiveFilter       *
#                                  muonBadTrackFilter                       *    # still under study (not use)
                                  eeBadScFilter                            *
#                                  chargedHadronTrackResolutionFilter       *    # still under study (not use)
                                  goodVertices
                                  
                                 )



