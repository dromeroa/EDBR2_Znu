import FWCore.ParameterSet.Config as cms

### Muon Isolation (https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Muon_Isolation)
baseandisolationCutString2 = "pt > 20 && abs(eta) < 2.5 &&  ((pfIsolationR04().sumChargedHadronPt+max(0.,pfIsolationR04().sumNeutralHadronEt+pfIsolationR04().sumPhotonEt-0.5*pfIsolationR04().sumPUPt))/pt< 0.25)"
	

niceMuons = cms.EDFilter("PATMuonSelector",
                                       src = cms.InputTag("slimmedMuons"),
                                       cut = cms.string(baseandisolationCutString2)


### A loose muon ID 
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *
selectMuons =  selectedPatMuons.clone(
               src = 'niceMuons',
               cut = 'isLooseMuon'
)


selectmuonsSequence = cms.Sequence(        niceMuons     * 
                                           selectMuons   
                                                         ) 

