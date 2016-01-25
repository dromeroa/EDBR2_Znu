import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

#process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.Geometry.GeometryIdeal_cff")
#This is for DATA :GlobalTag_condDBv2
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
### find the global tag in the DAS under the Configs for given dataset
###
### new global tag with new JEC
###  Taken from the MINIAOD https://twiki.cern.ch/twiki/bin/view/CMSPublic/WorkBookMiniAOD#Run2015D_PromptReco_v4_Data_2015 and
### https://twiki.cern.ch/twiki/bin/view/CMS/JECDataMC#Recommended_for_MC
## NEW FROM NOV 19 2015
process.GlobalTag.globaltag = '74X_dataRun2_v5'
#*********************************** CHOOSE YOUR CHANNEL  *******************************************#
#                                                                                                    #
#CHANNEL         = "VZ_CHANNEL" 
CHANNEL         = "VZnu_CHANNEL"
VZ_semileptonic = False
VZ_JetMET       = True
TYPE            = "CUTS"
#                                                                                                    #
#****************************************************************************************************#
isBlinded = False
if isBlinded == True :
   JETMASSCUT = 'pt>200. & userFloat("ak8PFJetsCHSCorrPrunedMass") > 20. & userFloat("ak8PFJetsCHSCorrPrunedMass") < 65. || userFloat("ak8PFJetsCHSCorrPrunedMass") > 135. '
else :
   JETMASSCUT = 'pt>200. & userFloat("ak8PFJetsCHSCorrPrunedMass") > 20.'
#*********************************** THE SAMPLES ****************************************************#
# choose the sample                                                                     

SAMPLE="MET_Run2015D_05Oct2015"

### Source
process.load("ExoDiBosonResonances.EDBRCommon.PromptReco."+SAMPLE)
#process.maxEvents.input =100000 
process.maxEvents.input = -1

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

configXsecs = {   "MET_Run2015D_05Oct2015"      : 1.0,
              }

configNevents = { "MET_Run2015D_05Oct2015"       :1,
                }

usedXsec = configXsecs[SAMPLE]
usedNevents = configNevents[SAMPLE]

#*********************************** JSON file ****************************************************#
# https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/
# last modified 18-Dec-2015 
import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_v2.txt').getVLuminosityBlockRange()
JSON_NAME='Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON_v2.txt'
#***********************************  EVENTS TO SKIP ******************************************************************#
listEventsToSkip = []
## REMEMBER TO CHANGE THE PATH TO YOUR ACTUAL LOCATION
fileEventsToSkip = open("/afs/cern.ch/work/d/dromeroa/private/CRAB_13enero/CMSSW_7_4_16_patch2/src/ExoDiBosonResonances/EDBRTreeMaker/data/inputfiles/eventstoskip.txt","r")

for line in fileEventsToSkip:
    cleanLine = line.rstrip()
    listEventsToSkip.append(cleanLine+"-"+cleanLine)

rangeEventsToSkip = cms.untracked.VEventRange(listEventsToSkip)
process.source.eventsToSkip = rangeEventsToSkip
#************************************************************************************************************************#


### Hadronic and leptonic boson.
process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZnu_cff")
#process.load("ExoDiBosonResonances.EDBRCommon.leptonicW_cff")
#process.load("ExoDiBosonResonances.EDBRCommon.hadronicW_cff")

WBOSONCUT = "pt > 200. & sqrt(2.0*daughter(0).pt()*daughter(1).pt()*(1.0-cos(daughter(0).phi()-daughter(1).phi()))) > 50."
ZBOSONCUT = "pt > 20. & 70. < mass < 110."

process.leptonicVFilter = cms.EDFilter(   "CandViewCountFilter",
                                          src = cms.InputTag("leptonicV"),
                                          minNumber = cms.uint32(1),
                                          filter = cms.bool(True) )

process.leptonicVSelector = cms.EDFilter( "CandViewSelector",
                                          src = cms.InputTag("leptonicV"),
                                          cut = cms.string( ZBOSONCUT ), #Change in case of WChannel
                                          filter = cms.bool(True) )

process.bestLeptonicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src = cms.InputTag("leptonicVSelector"),
                                          maxNumber = cms.uint32(1) )


process.corrJetsProducer.isData = True


process.bestHadronicV = cms.EDFilter(    "LargestPtCandSelector",
                                          src = cms.InputTag("hadronicV"),
                                          maxNumber = cms.uint32(1) )

if VZ_JetMET == True :
   process.niceak4JetsSelector = cms.EDFilter(  "CandViewSelector",
                                                src = cms.InputTag("niceak4Jets"),
                                                cut = cms.string( "" ),
                                                filter = cms.bool(True)
                                       )


process.graviton = cms.EDProducer(        "CandViewCombiner",
                                          decay = cms.string("bestLeptonicV bestHadronicV"),
                                          checkCharge = cms.bool(False),
                                          cut = cms.string(" "),
                                          roles = cms.vstring('leptonicV', 'hadronicV') )

process.gravitonFilter =  cms.EDFilter(   "CandViewCountFilter",
                                          src = cms.InputTag("graviton"),
                                          minNumber = cms.uint32(1),
                                          filter = cms.bool(True) )

#### The luminosity is calculated with brilcalc
process.treeDumper = cms.EDAnalyzer(      "EDBRTreeMaker",
                                          isGen           = cms.bool    (  False                     ),
                                          isData          = cms.bool    (  True                       ),
                                          originalNEvents = cms.int32   (  usedNevents               ),
                                          crossSectionPb  = cms.double  (  usedXsec                  ),
                                          targetLumiInvPb = cms.double  (  1.                        ),
                                          EDBRChannel     = cms.string  (  CHANNEL                   ),
                                          gravitonSrc     = cms.string  ( "graviton"                 ),
                                          metSrc          = cms.string  ( "slimmedMETs"              ),
                                          niceak4JetsSrc  = cms.InputTag( "niceak4Jets"              ),
                                          vertex          = cms.InputTag( "goodOfflinePrimaryVertex" ),
                                          payload         = cms.string  ( "AK8PFchs"                 ))

#************************************** SELECT GEN OR RECO ******************************************# 

option = 'RECO' # 'GEN' 

### GEN level studies
if option == 'GEN':
    process.load("ExoDiBosonResonances.EDBRGenStudies.genMuons_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genElectrons_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genFatJets_cff")
    process.load("ExoDiBosonResonances.EDBRGenStudies.genMET_cff")
    process.treeDumper.metSrc = 'genMetTrue'
    process.treeDumper.isGen  = True
    process.hadronicV.cut = cms.string('pt > 200. '
                                       '& (userFloat("ak8GenJetsSoftDropMass") > 50.) '
                                       '& (userFloat("ak8GenJetsSoftDropMass") < 110.)')

### RECO level studies
if option == 'RECO':
    process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.niceJets_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.niceak4Jets_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodMET_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodVertex_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.hltFilterZnu_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.photon_Vetoes_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.ele_Vetoes_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.Muon_Vetoes_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.Taus_Vetoes_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.Numberjetsak4QCD_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.deltaPhiak4Jets_cff")
#    process.load("ExoDiBosonResonances.EDBRCommon.METFilters_cff")
    process.hadronicV.cut = cms.string('pt > 200. '
                                       '& (userFloat("ak8PFJetsCHSSoftDropMass") > 50.) '
                                       '& (userFloat("ak8PFJetsCHSSoftDropMass") < 110.)')

    ##-----  FOR NOW CUT IN MET --------------##
    ## NO CUT FOR NOW, WE IMPOSE THIS AFTER PRODUCE THE TREE
    process.goodMET.cut = "pt > 250"

#***************************************** SEQUENCES **********************************************# 

process.leptonSequence = cms.Sequence(    process.leptonicVSequence + 
                                          process.leptonicVFilter   +
                                          process.leptonicVSelector + 
                                          process.bestLeptonicV     )

process.jetSequence = cms.Sequence(       process.fatJetsSequence   +
                                          process.hadronicV         +
                                          process.bestHadronicV     )

if VZ_JetMET == True :
   process.ak4jetSequence = cms.Sequence(        process.ak4JetsNuSequence     +
                                                 process.niceak4JetsSelector   )


process.gravitonSequence = cms.Sequence(  process.graviton          +
                                          process.gravitonFilter    )

process.analysis = cms.Path(              process.leptonSequence    +
                                          process.jetSequence       +
                                          process.gravitonSequence  +
                                          process.treeDumper        )


if option=='RECO':
   if VZ_semileptonic == True :
      process.load("ExoDiBosonResonances.EDBRCommon.hltFilter_cff")
      process.load("ExoDiBosonResonances.EDBRLeptons.goodLeptonsProducer_cff")
      from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
      switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
      my_id_modules = ['RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff']
      for idmod in my_id_modules:
          setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)
      process.analysis.replace(process.leptonSequence,
                               process.hltSequence              +
                               process.egmGsfElectronIDSequence +
                               process.goodLeptonsProducer      +
                               process.leptonSequence           )

#************************************ TRIGGER REPORT ANALYZER ***************************************#
#                                                                                                    #
# Only supported for VZ channel   
if VZ_semileptonic == True :
   process.load("ExoDiBosonResonances.EDBRGenStudies.selectLeptonicDecay")
   process.load("ExoDiBosonResonances.EDBRGenStudies.selectHadronicDecay")
   process.load("ExoDiBosonResonances.EDBRGenStudies.trigReportAnalyzer_cff")
   process.analysis.replace(process.hltSequence,
                         process.leptonicDecay +
                         process.hadronicDecay +
                         process.hltSequence   )

   process.endpath = cms.EndPath( process.trigReportAnalyzer )
#                                                                                                    #
#****************************************************************************************************#


#***************************************** FILTER MODE **********************************************#
#                                                                                                    #
# True : Events are filtered before the analyzer. TTree is filled with good valudes only             #
# False: Events are filtered inside the analyzed. TTree is filled with dummy values when numCands==0 #
#                                                                                                    #
filterMode = True       
### If you're running in signal, you may want to not filter at this level
### but only later at the tree analysis.
if filterMode == False:
    process.hltFilter.triggerConditions = ('*',)
    process.goodLeptons.filter = False
    process.leptonicVSelector.cut = '70. < mass < 110.'
    process.graviton.cut = ''
#                                                                                                    #
#****************************************************************************************************#

#****************************************************************************************************#

####################################################################################################
###################################  JET-MET CHANNEL  ##############################################
####################################################################################################

if VZ_JetMET == True :

    process.hadronicVnu.cut = cms.string( JETMASSCUT )

    ## Why the best hadronicV candidate has the largest pt?
    process.bestHadronicV.src   = cms.InputTag("hadronicVnu")

    process.graviton.decay  =  cms.string("goodMET bestHadronicV")
    process.graviton.cut    =  cms.string("")
    process.graviton.roles  =  cms.vstring('goodMET', 'hadronicVnu')


    process.jetSequence.replace(    process.fatJetsSequence,
                                    process.fatJetsNuSequence       *
                                    process.hadronicVnuSequence     )

    process.jetSequence.remove(process.hadronicV)

    from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
    switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
    my_el_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff',
                     'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff']
    for idmod in my_el_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

###   THERE IS NO PHOTON ID FOR 25 ns (solo MVA) we are using still for 50 ns 

    switchOnVIDPhotonIdProducer(process, DataFormat.MiniAOD)
    my_pho_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring15_50ns_V1_cff']
    for idmod in my_pho_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)



    ###---------------- MET FILTERS DATA ---------------------------------------------###
    ###-------------------------------------------------------------------------------###
    process.load('CommonTools.RecoAlgos.HBHENoiseFilterResultProducer_cfi')
    process.HBHENoiseFilterResultProducer.minZeros = cms.int32(99999)
    process.HBHENoiseFilterResultProducer.IgnoreTS4TS5ifJetInLowBVRegion=cms.bool(False) 
    process.HBHENoiseFilterResultProducer.defaultDecision = cms.string("HBHENoiseFilterResultRun2Loose")

    process.ApplyBaselineHBHENoiseFilter = cms.EDFilter('BooleanFlagFilter',
       inputLabel = cms.InputTag('HBHENoiseFilterResultProducer','HBHENoiseFilterResult'),
       reverseDecision = cms.bool(False)
    )

    process.ApplyBaselineHBHEIsoNoiseFilter = cms.EDFilter('BooleanFlagFilter',
       inputLabel = cms.InputTag('HBHENoiseFilterResultProducer','HBHEIsoNoiseFilterResult'),
       reverseDecision = cms.bool(False)
    )

    process.eeBadScFilter = cms.EDFilter("HLTHighLevel",
        TriggerResultsTag  = cms.InputTag("TriggerResults","","RECO"),
        HLTPaths           = cms.vstring("Flag_eeBadScFilter"),
        eventSetupPathsKey = cms.string(''),
        andOr              = cms.bool(True),
        throw              = cms.bool(True)
    )


    process.goodVertices = cms.EDFilter("HLTHighLevel",
        TriggerResultsTag  = cms.InputTag("TriggerResults","","RECO"),
        HLTPaths           = cms.vstring("Flag_goodVertices"),
        eventSetupPathsKey = cms.string(''),
        andOr              = cms.bool(True),
        throw              = cms.bool(True)
)



    ## WE ARE USING THE TXT FILES POR NOW
#    process.CSCTightHaloFilter = cms.EDFilter("HLTHighLevel",
#        TriggerResultsTag  = cms.InputTag("TriggerResults","","RECO"),
#        HLTPaths           = cms.vstring("Flag_CSCTightHaloFilter"),
#        eventSetupPathsKey = cms.string(''),
#        andOr              = cms.bool(True),
#        throw              = cms.bool(True)
#    )



    ## goodVertex is run after this sequence


    process.metfilterSequence = cms.Sequence(   process.goodVertices                      *
                                                process.HBHENoiseFilterResultProducer     *
                                                process.ApplyBaselineHBHENoiseFilter      *
                                                process.ApplyBaselineHBHEIsoNoiseFilter   *
                                                process.eeBadScFilter                     
#                                                process.CSCTightHaloFilter
                                             )


###--------------------------------------------------------------------------------------###
    
    process.analysis.replace(       process.jetSequence,
                                    process.hltSequenceZnu           *
                                    process.metfilterSequence        *
                                    process.VertexSequence           *
                                    process.jetSequence              *
                                    process.ak4jetSequence           *
                                    process.Numberjetsak4QCDSequence *  ## INCLUDE THE QCD CUTS
                                    process.deltaPhiak4JetsSequence  *
                                    process.metSequence              *
                                    process.egmGsfElectronIDs        *
                                    process.VETOSelectEvents         *
                                    process.egmPhotonIDs             * 
                                    process.photonvetoSequence       *
                                    process.muonsVetoSequence        *
                                    process.tausVetoSequence
                            )

    process.analysis.remove(process.leptonSequence)

###################################################################################################


print "++++++++++ CUTS ++++++++++\n"
if VZ_semileptonic == True :
   print "Graviton cut = "+str(process.graviton.cut)
   print "Leptonic V cut = "+str(process.leptonicVSelector.cut)
   print "Hadronic V cut = "+str(process.hadronicV.cut)
if VZ_JetMET == True :
   print "CHANNEL = " +str(CHANNEL)
   print "SAMPLE = " +str(SAMPLE)
   print "IS BLINDED ?  = " +str(isBlinded)
   print "Global Tag = " +str(process.GlobalTag.globaltag)
   print "JSON file = " +str(JSON_NAME)
   print "Hadronic V cut = "+str(process.hadronicVnu.cut)
   print "MET cut = "+str(process.goodMET.cut)
   print "Type of Analysis = " +str(TYPE)
print "\n++++++++++++++++++++++++++"

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("treeEDBR_"+SAMPLE+"_CUTS.root")
                                  )
