import FWCore.ParameterSet.Config as cms

goodOfflinePrimaryVertex = cms.EDFilter("VertexSelector",
                                          src = cms.InputTag("offlineSlimmedPrimaryVertices"),
                                          cut = cms.string(  "chi2 != 0 "
                                                             "& ndof >= 4.0 "
                                                             "& abs(z) <= 24.0 "
                                                             "& abs(position.Rho) <= 2.0 "),
                                          filter = cms.bool(True))



VertexSequence = cms.Sequence(goodOfflinePrimaryVertex)

