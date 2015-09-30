import FWCore.ParameterSet.Config as cms

### FOR NOW : no cut in jet mass (In the plotter we will define the cuts (blinded))

hadronicVnu = cms.EDFilter( "CandViewSelector",
                              src = cms.InputTag("niceJets"),
                              cut = cms.string('pt > 200. '), ## Consider a Boosted Z
                              filter = cms.bool(True) )

hadronicVnuSequence = cms.Sequence(hadronicVnu)

