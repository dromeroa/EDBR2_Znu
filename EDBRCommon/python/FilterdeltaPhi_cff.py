import FWCore.ParameterSet.Config as cms


filterDeltaphi = cms.EDFilter("Deltaphi",
                            jets = cms.InputTag("niceak4Jets"),
                            mets = cms.InputTag("goodMET"),   
                            minDeltaphi_threshold  = cms.double(0.5),
                            filter = cms.bool(True)
)

mindeltaPhiSequence = cms.Sequence( filterDeltaphi )



