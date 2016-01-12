

import FWCore.ParameterSet.Config as cms

# module to filter on the number of Jets
## put here the collection of ak4 jets (cleaning?)

countak4PatJets = cms.EDFilter("PATCandViewCountFilter",
                                minNumber = cms.uint32(0),
                                maxNumber = cms.uint32(2),
                                src       = cms.InputTag("niceak4Jets")
)



Numberjetsak4QCDSequence = cms.Sequence( countak4PatJets )
