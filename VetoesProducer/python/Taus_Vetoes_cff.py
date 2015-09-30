import FWCore.ParameterSet.Config as cms

goodTaus = cms.EDFilter("PATTauSelector",
                                src = cms.InputTag("slimmedTaus"),
                                cut = cms.string("pt >20 & abs(eta)<2.3"))


from PhysicsTools.PatAlgos.selectionLayer1.tauSelector_cfi import *
vetoTausel = selectedPatTaus.clone(
    src = 'goodTaus',
    cut =
    'tauID("decayModeFinding")&'
    'tauID("byMediumCombinedIsolationDeltaBetaCorr3Hits") '
)

tausVeto = cms.EDFilter("PATCandViewCountFilter",
                 minNumber = cms.uint32(0),
                 maxNumber = cms.uint32(0),
                 src = cms.InputTag("vetoTausel")
)


tausVetoSequence = cms.Sequence(              goodTaus    *
                                              vetoTausel  *
                                              tausVeto
                                 )
