import FWCore.ParameterSet.Config as cms

import HLTrigger.HLTfilters.triggerResultsFilter_cfi as hlt
### Note that we can use any version adding _v* in each path

hltFilterZnu = hlt.triggerResultsFilter.clone(

### In 25 ns we have to change the NOISE cleaned in the path
#triggerConditions = (  'HLT_PFMETNoMu90_NoiseCleaned_PFMHTNoMu90_IDTight_v*', 'HLT_MonoCentralPFJet80_PFMETNoMu120_NoiseCleaned_PFMHTNoMu120_IDTight_v*' ),
#triggerConditions = (  'HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*', 'HLT_MonoCentralPFJet80_PFMETNoMu120_JetIdCleaned_PFMHTNoMu120_IDTight_v*' ),
## FOR MET DATA
triggerConditions = (  'HLT_PFMETNoMu90_JetIdCleaned_PFMHTNoMu90_IDTight_v*',),
## FOR SINGLE ELECTRON DATA
#triggerConditions = (  'HLT_Ele23 WPLoose Gsf_v*',),
                       hltResults = cms.InputTag( "TriggerResults", "", "HLT"),
                       l1tResults = cms.InputTag( "gtDigis" ),
                       throw = False )


hltSequenceZnu = cms.Sequence(hltFilterZnu)

