import FWCore.ParameterSet.Config as cms

### Muon Isolation (https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Muon_Isolation)
baseandisolationCutString = "pt > 20 && abs(eta) < 2.5 &&  ((pfIsolationR04().sumChargedHadronPt+max(0.,pfIsolationR04().sumNeutralHadronEt+pfIsolationR04().sumPhotonEt-0.5*pfIsolationR04().sumPUPt))/pt< 0.25)"
	

goodMuons = cms.EDFilter("PATMuonSelector",
                                       src = cms.InputTag("slimmedMuons"),
                                       cut = cms.string(baseandisolationCutString),
                                       filter = cms.bool(False)
)

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
                                


