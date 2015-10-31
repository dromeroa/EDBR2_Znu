
import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

#process.load("Configuration.StandardSequences.Geometry_cff")
process.load("Configuration.Geometry.GeometryIdeal_cff")
# This is for MC
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
# find the global tag in the DAS under the Configs for given dataset
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
process.GlobalTag.globaltag = '74X_mcRun2_asymptotic_v2'
#*********************************** CHOOSE YOUR CHANNEL  *******************************************#
#                                                                                                    #
#CHANNEL         = "VZ_CHANNEL" 
CHANNEL         = "VZnu_CHANNEL" 
VZ_semileptonic = False
VZ_JetMET       = True
#                                                                                                    #
#****************************************************************************************************#
#*************************************** BLIND ANALYSIS *********************************************#
isBlinded = True
if isBlinded == True :
   JETMASSCUT = 'pt>200. & userFloat("ak8PFJetsCHSCorrPrunedMass") > 40. & userFloat("ak8PFJetsCHSCorrPrunedMass") < 65.'
else :
   JETMASSCUT = 'pt>200. & userFloat("ak8PFJetsCHSCorrPrunedMass") > 40.'
#************************************ CHOOSE YOUR HLT *******************************************#



#*********************************** THE SAMPLES ****************************************************#
### CHOOSE THE SAMPLE :                                                                   

###-------- RSGRrav------------------
SAMPLE="BulkGrav_ZZ_M2000_25ns_v2"

###------   Z +JETS  -----------
#SAMPLE="ZJetsToNuNu_HT-100To200_25ns_v2"
#SAMPLE="ZJetsToNuNu_HT-200To400_25ns_v2"
#SAMPLE="ZJetsToNuNu_HT-400To600_25ns_v2"
#SAMPLE="ZJetsToNuNu_HT-600ToInf_25ns_v2"

###-----   W + jets-------------------
#SAMPLE="WJetsToLNu_HT-100To200_25ns_v2"
#SAMPLE="WJetsToLNu_HT-200To400_25ns_v2"
#SAMPLE="WJetsToLNu_HT-400To600_25ns_v2"
#SAMPLE="WJetsToLNu_HT-600ToInf_25ns_v2"

### ------- TTJets ------------------
#SAMPLE="TTjets_25ns_powheg_v2" 

### ------- Dibosons ---------------
#SAMPLE="WW_25ns_v2"
#SAMPLE="WZ_25ns_v2"
#SAMPLE="ZZ_25ns_v2"

###-------- QCD ------------------
#SAMPLE="QCD_HT2000toInf_25ns_v2"
#SAMPLE="QCD_HT1500to2000_25ns_v2"
#SAMPLE="QCD_HT1000to1500_25ns_v2"
#SAMPLE="QCD_HT700to1000_25ns_v2"
#SAMPLE="QCD_HT500to700_25ns_v2"
#SAMPLE="QCD_HT300to500_25ns_v2"
#SAMPLE="QCD_HT200to300_25ns_v2"
#SAMPLE="QCD_HT100to200_25ns_v2"

### Source
process.load("ExoDiBosonResonances.EDBRCommon.simulation.RunIIDR74X_miniAOD_v2."+SAMPLE)
#process.maxEvents.input = -1
process.maxEvents.input = 100000

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

configXsecs = { 
                "BulkGrav_ZZ_M2000_25ns_v2"               : 1,
                "ZJetsToNuNu_HT-100To200_25ns_v2"         : 280.47,
                "ZJetsToNuNu_HT-200To400_25ns_v2"         : 78.36,
                "ZJetsToNuNu_HT-400To600_25ns_v2"         : 10.944,
                "ZJetsToNuNu_HT-600ToInf_25ns_v2"         : 4.203,
                "WJetsToLNu_HT-100To200_25ns_v2"          : 1345,
                "WJetsToLNu_HT-200To400_25ns_v2"          : 359.7,
                "WJetsToLNu_HT-400To600_25ns_v2"          : 48.91,
                "WJetsToLNu_HT-600ToInf_25ns_v2"          : 18.77,
                "WW_25ns_v2"                              : 118.7,
                "ZZ_25ns_v2"                              : 16.523,
                "WZ_25ns_v2"                              : 47.13, 
                "TTbar_25ns_powheg_v2"                    : 831.76,
                "QCD_HT100to200_25ns_v2"                  : 27540000.0	,
                "QCD_HT200to300_25ns_v2"                  : 1735000.0, 
                "QCD_HT300to500_25ns_v2"                  : 366800.0,
                "QCD_HT500to700_25ns_v2"                  : 29370.0,
                "QCD_HT700to1000_25ns_v2"                 : 6524.0,
                "QCD_HT1000to1500_25ns_v2"                : 1064.0,
                "QCD_HT1500to2000_25ns_v2"                : 121.5,   
                "QCD_HT2000toInf_25ns_v2"                 : 25.42,    

              }

configNevents = {
                 "BulkGrav_ZZ_M2000_25ns_v2"               : 99400,
                 "ZJetsToNuNu_HT-100To200_25ns_v2"         : 5148193,
                 "ZJetsToNuNu_HT-200To400_25ns_v2"         : 5032927,
                 "ZJetsToNuNu_HT-400To600_25ns_v2"         : 1014139,
                 "ZJetsToNuNu_HT-600ToInf_25ns_v2"         : 1015904,
                 "WJetsToLNu_HT-100To200_25ns_v2"          : 10142187,
                 "WJetsToLNu_HT-200To400_25ns_v2"          : 5231856,
                 "WJetsToLNu_HT-400To600_25ns_v2"          : 1901705,
                 "WJetsToLNu_HT-600ToInf_25ns_v2"          : 1036108,
                 "WW_25ns_v2"                              : 993640,
                 "ZZ_25ns_v2"                              : 996944,
                 "WZ_25ns_v2"                              : 978512, 
                 "TTbar_25ns_powheg_v2"                    : 19757190,
                 "QCD_HT100to200_25ns_v2"                  : 81637494,
                 "QCD_HT200to300_25ns_v2"                  : 18718905,
                 "QCD_HT300to500_25ns_v2"                  : 19826197,
                 "QCD_HT500to700_25ns_v2"                  : 19664159,
                 "QCD_HT700to1000_25ns_v2"                 : 15356448,
                 "QCD_HT1000to1500_25ns_v2"                : 4963895, 
                 "QCD_HT1500to2000_25ns_v2"                : 3868886,  
                 "QCD_HT2000toInf_25ns_v2"                 : 1912529,

                }

usedXsec = configXsecs[SAMPLE]
usedNevents = configNevents[SAMPLE]

#*******************************************************************************************************#

### Hadronic and leptonic boson.
process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZnu_cff")
#process.load("ExoDiBosonResonances.EDBRCommon.leptonicW_cff")
#process.load("ExoDiBosonResonances.EDBRCommon.hadronicW_cff")

WBOSONCUT = "pt > 200. & sqrt(2.0*daughter(0).pt()*daughter(1).pt()*(1.0-cos(daughter(0).phi()-daughter(1).phi()))) > 50."
ZBOSONCUT = "pt > 200. & 70. < mass < 110."

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

process.hadronicVFilter = cms.EDFilter(   "CandViewCountFilter",
                                          src = cms.InputTag("hadronicV"),
                                          minNumber = cms.uint32(1),
                                          filter = cms.bool(True) )

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
                                          cut = cms.string("mass > 400"),
                                          roles = cms.vstring('leptonicV', 'hadronicV') )

process.gravitonFilter =  cms.EDFilter(   "CandViewCountFilter",
                                          src = cms.InputTag("graviton"),
                                          minNumber = cms.uint32(1),
                                          filter = cms.bool(True) )

process.treeDumper = cms.EDAnalyzer(      "EDBRTreeMaker",
                                          isGen           = cms.bool    (  False                     ),
                                          isData          = cms.bool    (  False                     ),
                                          originalNEvents = cms.int32   (  usedNevents               ),
                                          crossSectionPb  = cms.double  (  usedXsec                  ),
                                          targetLumiInvPb = cms.double  (  1560.0                    ),
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
    process.load("ExoDiBosonResonances.EDBRCommon.hltFilterZnu_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.METFilters_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodVertex_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.niceJets_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.niceak4Jets_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodMET_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.photon_Vetoes_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.ele_Vetoes_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.Muon_Vetoes_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.Taus_Vetoes_cff")
    process.hadronicV.cut = cms.string('pt > 200. '
                                       '& (userFloat("ak8PFJetsCHSSoftDropMass") > 50.) '
                                       '& (userFloat("ak8PFJetsCHSSoftDropMass") < 110.)')
    ##-----  FOR NOW NO CUT IN MET -------------##
    process.goodMET.cut = "pt > 250"

#***************************************** SEQUENCES **********************************************# 

process.leptonSequence = cms.Sequence(    process.leptonicVSequence +
                                          process.leptonicVFilter   +
                                          process.leptonicVSelector + 
                                          process.bestLeptonicV     )

process.jetSequence = cms.Sequence(       process.fatJetsSequence   +
                                          process.hadronicV         +
                                          process.hadronicVFilter   +
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
    process.goodElectrons.cut = ""
    process.goodMuons.cut = ""
    process.leptonicVSelector.cut = '70. < mass < 110.'
    process.graviton.cut = ''
#                                                                                                    #
#****************************************************************************************************#

####################################################################################################
###################################  JET-MET CHANNEL  ##############################################
####################################################################################################

if VZ_JetMET == True :

    process.hadronicV.cut = cms.string( JETMASSCUT )
 
    process.hadronicVFilter.src = cms.InputTag("hadronicVnu")
    ## Why the best hadronicV candidate has the largest pt?
    process.bestHadronicV.src   = cms.InputTag("hadronicVnu")

    process.graviton.decay  =  cms.string("goodMET hadronicVnu")
    process.graviton.cut    =  cms.string("")
    process.graviton.roles  =  cms.vstring('goodMET', 'hadronicVnu')


    process.jetSequence.replace(    process.fatJetsSequence, 
                                    process.fatJetsNuSequence          *
                                    process.hadronicVnuSequence        )

    process.jetSequence.remove(process.hadronicV) 

    from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
    switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
    my_el_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff',
                     'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff']
    for idmod in my_el_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

    switchOnVIDPhotonIdProducer(process, DataFormat.MiniAOD)
#    my_pho_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_PHYS14_PU20bx25_V2_cff']
    my_pho_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring15_50ns_V1_cff']
    for idmod in my_pho_modules:
        setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)


#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#



    process.analysis.replace(       process.jetSequence,
                                    process.hltSequenceZnu           *
                                    process.metfilterSequence        *
                                    process.VertexSequence           *
                                    process.jetSequence              *
                                    process.ak4jetSequence           *
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
print "Graviton cut = "+str(process.graviton.cut)
if VZ_semileptonic == True :
   print "Leptonic V cut = "+str(process.leptonicVSelector.cut) 
   print "Hadronic V cut = "+str(process.hadronicV.cut)
if VZ_JetMET == True :
   print "Hadronic V cut = "+str(process.hadronicVnu.cut)
   print "MET cut = "+str(process.goodMET.cut)
print "\n++++++++++++++++++++++++++"

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("treeEDBR_"+SAMPLE+".root")
                                  )
