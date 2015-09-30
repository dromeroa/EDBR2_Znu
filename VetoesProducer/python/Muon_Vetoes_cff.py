import FWCore.ParameterSet.Config as cms


goodMuons = cms.EDFilter("PATMuonSelector",
                                       src = cms.InputTag("slimmedMuons"),
                                       cut = cms.string("pt > 20 && abs(eta) < 2.5"))


### A loose muon ID 
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
vetoMuonsel= selectedPatMuons.clone(
    src = 'goodMuons',
    cut = 'isLooseMuon'
)


muonsVeto = cms.EDFilter("PATCandViewCountFilter",
                 minNumber = cms.uint32(0),
                 maxNumber = cms.uint32(0),
                 src = cms.InputTag("vetoMuonsel")
)


muonsVetoSequence = cms.Sequence(       goodMuons     * 
                                        vetoMuonsel   *
                                        muonsVeto     )    
                                


