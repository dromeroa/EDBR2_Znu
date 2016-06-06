import FWCore.ParameterSet.Config as cms

goodPhotons = cms.EDFilter("PATPhotonRefSelector",
                               src = cms.InputTag("slimmedPhotons"),
                               cut = cms.string("pt > 20 &  abs(eta) < 2.5"),
                               filter = cms.bool(False)
)



nicePhotons = cms.EDProducer("PatPhotonSelectorByValueMap",
                               input     = cms.InputTag("goodPhotons"),
                               cut       = cms.string(""),
                               selection = cms.InputTag("egmPhotonIDs:cutBasedPhotonID-Spring15-25ns-V1-standalone-loose"),
                               id_cut    = cms.bool(True)
)

photonSequence = cms.Sequence(
                                      goodPhotons                      *
                                      nicePhotons
       
                                                                        )
