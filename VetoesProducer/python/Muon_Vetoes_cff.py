import FWCore.ParameterSet.Config as cms

# Muon Isolation (https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideMuonIdRun2#Muon_Isolation)
baseandisolationCutString = 'pt > 20 && abs(eta) < 2.5 &&  ((pfIsolationR04().sumChargedHadronPt+max(0.,pfIsolationR04().sumNeutralHadronEt+pfIsolationR04().sumPhotonEt-0.5*pfIsolationR04().sumPUPt))/pt< 0.25)'

# Loose muon Id
from PhysicsTools.PatAlgos.selectionLayer1.muonSelector_cfi import *

Muonsel= selectedPatMuons.clone(
                          src = 'slimmedMuons',
                          cut = 'isLooseMuon && ' + baseandisolationCutString)


niceLeptonsMu = cms.EDProducer("deltaRleptonsProducer",
                                electrons = cms.InputTag("slimmedElectrons"),
                                muons = cms.InputTag("Muonsel"),
                                taus = cms.InputTag("slimmedTaus"),
                                fatjets = cms.InputTag("bestHadronicVnu"))


goodMuons = cms.EDFilter("PATMuonSelector",
                                src = cms.InputTag("niceLeptonsMu:Muons"),
                                cut = cms.string('userFloat("deltaRJetMu")>0.8'),
                                filter = cms.bool(False))


muonsVeto = cms.EDFilter("PATCandViewCountFilter",
                 minNumber = cms.uint32(0),
                 maxNumber = cms.uint32(0),
                 src = cms.InputTag("goodMuons")
)


muonsVetoSequence = cms.Sequence(    
                                        Muonsel         *
                                        niceLeptonsMu   * 
                                        goodMuons       * 
                                        muonsVeto    
                                                      )    
                                


