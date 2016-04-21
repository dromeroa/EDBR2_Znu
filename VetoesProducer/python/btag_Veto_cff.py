import FWCore.ParameterSet.Config as cms


## Medium working point

bJets = cms.EDFilter("PATJetSelector",
                      src = cms.InputTag("niceak4Jets"),
                      cut = cms.string('bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags") >= 0.800 && userFloat("deltaRjetfatjet")>0.8' ),
                      filter = cms.bool(False))


bJetsVeto = cms.EDFilter("PATCandViewCountFilter",
                          minNumber = cms.uint32(0),
                          maxNumber = cms.uint32(0),
                          src = cms.InputTag("bJets"))



bJetsVetoSequence = cms.Sequence(
                                    bJets                *
                                    bJetsVeto            
                                                         )

