import FWCore.ParameterSet.Config as cms

goodMET = cms.EDFilter("PATMETSelector",
                             src = cms.InputTag("slimmedMETs"),
                             cut = cms.string("pt >40")
                             )

metSequence = cms.Sequence(goodMET)

