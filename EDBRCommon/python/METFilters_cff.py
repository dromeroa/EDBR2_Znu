import FWCore.ParameterSet.Config as cms


HBHENoiseFilter = cms.EDFilter("HLTHighLevel",
           TriggerResultsTag  = cms.InputTag("TriggerResults","","PAT"),
           HLTPaths           = cms.vstring("Flag_HBHENoiseFilter"),
           eventSetupPathsKey = cms.string(''),
           andOr              = cms.bool(True),
           throw              = cms.bool(True)
)



goodVertices = cms.EDFilter("HLTHighLevel",
        TriggerResultsTag  = cms.InputTag("TriggerResults","","PAT"),
        HLTPaths           = cms.vstring("Flag_goodVertices"),
        eventSetupPathsKey = cms.string(''),
        andOr              = cms.bool(True),
        throw              = cms.bool(True)
)


eeBadScFilter = cms.EDFilter("HLTHighLevel",
        TriggerResultsTag  = cms.InputTag("TriggerResults","","PAT"),
        HLTPaths           = cms.vstring("Flag_eeBadScFilter"),
        eventSetupPathsKey = cms.string(''),
        andOr              = cms.bool(True),
        throw              = cms.bool(True)
)

CSCTightHaloFilter = cms.EDFilter("HLTHighLevel",
        TriggerResultsTag  = cms.InputTag("TriggerResults","","PAT"),
        HLTPaths           = cms.vstring("Flag_CSCTightHaloFilter"),
        eventSetupPathsKey = cms.string(''),
        andOr              = cms.bool(True),
        throw              = cms.bool(True)
)



metfilterSequence = cms.Sequence( HBHENoiseFilter       +
                                  goodVertices          +
                                  eeBadScFilter         +
                                  CSCTightHaloFilter    )

