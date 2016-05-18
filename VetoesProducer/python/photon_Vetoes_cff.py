import FWCore.ParameterSet.Config as cms

goodPhotons = cms.EDFilter("PATPhotonRefSelector",
                               src = cms.InputTag("slimmedPhotons"),
                               cut = cms.string("pt > 15 &  abs(eta) < 2.5"),
                               filter = cms.bool(False)
)



photonsVetoProd = cms.EDProducer("PatPhotonSelectorByValueMap",
                               input     = cms.InputTag("goodPhotons"),
                               cut       = cms.string(""),
                               selection = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-loose"),
                               id_cut    = cms.bool(True)
)



photonVeto = cms.EDFilter("PATCandViewCountFilter",
                 minNumber = cms.uint32(0),
                 maxNumber = cms.uint32(0),
                 src = cms.InputTag("photonsVetoProd"),
                 filter = cms.bool(True)
)



photonvetoSequence = cms.Sequence(    goodPhotons                      *
                                      photonsVetoProd                  *
                                      photonVeto                       )
