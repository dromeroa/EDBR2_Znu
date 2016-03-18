import FWCore.ParameterSet.Config as cms




filterQCD = cms.EDFilter("QCDfilter",
                            jets = cms.InputTag("niceak4Jets"),
                            deltaphi_threshold   = cms.double(2.8),
                            filter = cms.bool(True)
)

deltaPhiak4JetsSequence = cms.Sequence( filterQCD )





