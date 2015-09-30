import FWCore.ParameterSet.Config as cms
from PhysicsTools.SelectorUtils.pfJetIDSelector_cfi import pfJetIDSelector


niceJets = cms.EDFilter("PFJetIDSelectionFunctorFilter",
                         filterParams = pfJetIDSelector.clone(),
                         src = cms.InputTag("slimmedJetsAK8")
                         )

fatJetsNuSequence = cms.Sequence(niceJets)

