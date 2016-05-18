import FWCore.ParameterSet.Config as cms

goodTaus = cms.EDFilter("PATTauSelector",
                                src = cms.InputTag("slimmedTaus"),
                                cut = cms.string("pt >20 & abs(eta)<2.3"),
                                filter = cms.bool(False)
)


from PhysicsTools.PatAlgos.selectionLayer1.tauSelector_cfi import *

vetoTausel = selectedPatTaus.clone(
                               src = 'goodTaus',
                               cut =
                               'tauID("decayModeFinding")&'
                               'tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits")')


niceLeptonsTau = cms.EDProducer("deltaRleptonsProducer",
                                electrons = cms.InputTag("slimmedElectrons"),
                                muons = cms.InputTag("slimmedMuons"),
                                taus = cms.InputTag("vetoTausel"),
                                fatjets = cms.InputTag("bestHadronicVnu"))


bestTaus = cms.EDFilter("PATTauSelector",
                                src = cms.InputTag("niceLeptonsTau:Taus"),
                                cut = cms.string('userFloat("deltaRJetTau")>0.8'),
                                filter = cms.bool(False))


tausVeto = cms.EDFilter("PATCandViewCountFilter",
                 minNumber = cms.uint32(0),
                 maxNumber = cms.uint32(0),
                 src = cms.InputTag("bestTaus"))


tausVetoSequence = cms.Sequence(          
                                              goodTaus        *
                                              vetoTausel      *
                                              niceLeptonsTau  *
                                              bestTaus        *
                                              tausVeto
                                                              )
