import FWCore.ParameterSet.Config as cms

import HLTrigger.HLTfilters.triggerResultsFilter_cfi as hlt

hltFilterZnu = hlt.triggerResultsFilter.clone(


## DATA AND MC
triggerConditions = (  'HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*',),
                       hltResults = cms.InputTag( "TriggerResults", "", "HLT"),
                       l1tResults = cms.InputTag( "gtDigis" ),
                       throw = False )


hltSequenceZnu = cms.Sequence(hltFilterZnu)

