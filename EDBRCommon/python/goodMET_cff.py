import FWCore.ParameterSet.Config as cms

goodMET = cms.EDFilter("PATMETSelector",
                             src = cms.InputTag("slimmedMETs"),
                             cut = cms.string("pt >250"),
                             filter = cms.bool(True)
                             )

metSequence = cms.Sequence(goodMET)

