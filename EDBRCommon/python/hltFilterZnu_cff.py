import FWCore.ParameterSet.Config as cms

import HLTrigger.HLTfilters.triggerResultsFilter_cfi as hlt
### Note that we can use any version adding _v* in each path

hltFilterZnu = hlt.triggerResultsFilter.clone(

# Check if this work for MC and Data?

## FOR MET DATA AND MC
triggerConditions = ( 'HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*','HLT_PFMET170*'),
                       hltResults = cms.InputTag( "TriggerResults", "", "HLT"),
                       l1tResults = cms.InputTag( "gtDigis" ),
                       throw = False )


hltSequenceZnu = cms.Sequence(hltFilterZnu)

