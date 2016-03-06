import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

process.load('Configuration.StandardSequences.Services_cff')
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
## FROM March 05 2016
process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_RunIIFall15DR76_v1'


#*********************************** CHOOSE YOUR CHANNEL  *******************************************#
#                                                                                                    #
#CHANNEL         = "VZ_CHANNEL" 
CHANNEL         = "VZnu_CHANNEL" 
VZ_semileptonic = False
VZ_JetMET       = True
#                                                                                                    #
#****************************************************************************************************#
#************************************ CHOOSE YOUR HLT *******************************************#

#*********************************** THE SAMPLES ****************************************************#
### CHOOSE THE SAMPLE :                                                                   

###------   Z +JETS  -----------
#SAMPLE="ZJetsToNuNu_HT-100To200_76x_v2"
#SAMPLE="ZJetsToNuNu_HT-200To400_76x_v2"
#SAMPLE="ZJetsToNuNu_HT-400To600_76x_v2"
#SAMPLE="ZJetsToNuNu_HT-600ToInf_76x_v2"

###-----   W + jets-------------------
#SAMPLE="WJetsToLNu_HT-100To200_76x_v2"
#SAMPLE="WJetsToLNu_HT-200To400_76x_v2"
#SAMPLE="WJetsToLNu_HT-400To600_76x_v2"
#SAMPLE="WJetsToLNu_HT-600ToInf_76x_v2"

### ------- TTJets ------------------
#SAMPLE="TTJets_amcatnloFXFX_76x_v2"  
#SAMPLE="TTJets_amcatnloFXFX_76x_v2_ext"

### ------- Dibosons ---------------
#SAMPLE="WW_76x_v2"
#SAMPLE="WZ_76x_v2"
#SAMPLE="ZZ_76x_v2"

###-------- QCD ------------------
#SAMPLE="QCD_HT2000toInf_76x_v2"
#SAMPLE="QCD_HT1500to2000_76x_v2"
#SAMPLE="QCD_HT1000to1500_76x_v2"
#SAMPLE="QCD_HT700to1000_76x_v2"
#SAMPLE="QCD_HT500to700_76x_v2"
#SAMPLE="QCD_HT300to500_76x_v2"
#SAMPLE="QCD_HT200to300_76x_v2"
#SAMPLE="QCD_HT100to200_76x_v2"

### To use with CRAB
#import sys
#SAMPLE = str(sys.argv[2])



### Source
process.load("ExoDiBosonResonances.EDBRCommon.76X_simulation."+SAMPLE)
process.maxEvents.input = -1
### NUMBER OF EVENTS
#process.maxEvents.input = 10000


# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns (1 Billion campaign)

configXsecs = { 
                "ZJetsToNuNu_HT-100To200_76x_v2"         : 344.8305,  ##  280.35  x 1.23 (NLO)  
                "ZJetsToNuNu_HT-200To400_76x_v2"         : 95.571,    ##   77.67  x 1.23 (NLO)
                "ZJetsToNuNu_HT-400To600_76x_v2"         : 13.1979,   ##   10.73  x 1.23 (NLO)
                "ZJetsToNuNu_HT-600ToInf_76x_v2"         : 5.06268,   ##    4.116 x 1.23 (NLO)
                "WJetsToLNu_HT-100To200_76x_v2"          : 1627.45,   ## 1345     x 1.21 (NLO) 
                "WJetsToLNu_HT-200To400_76x_v2"          : 435.237,   ##  359.7   x 1.21 (NLO)
                "WJetsToLNu_HT-400To600_76x_v2"          : 59.1811,   ##   48.91  x 1.21 (NLO)
                "WJetsToLNu_HT-600ToInf_76x_v2"          : 22.7117,   ##   18.77  x 1.21 (NLO)
                "WW_76x_v2"                              : 118.7,
                "ZZ_76x_v2"                              : 16.523,
                "WZ_76x_v2"                              : 47.13, 
                "TTJets_amcatnloFXFX_76x_v2"             : 831.76,
                "TTJets_amcatnloFXFX_76x_v2_ext"         : 831.76,
                "QCD_HT200to300_76x_v2"                  : 1712000, ## LO 
                "QCD_HT300to500_76x_v2"                  : 347700,  ## LO
                "QCD_HT500to700_76x_v2"                  : 32100,   ## LO
                "QCD_HT700to1000_76x_v2"                 : 6831,    ## LO
                "QCD_HT1000to1500_76x_v2"                : 1207,    ## LO
                "QCD_HT1500to2000_76x_v2"                : 119.9,   ## LO   
                "QCD_HT2000toInf_76x_v2"                 : 25.24,   ## LO                    
              }

configNevents = {

                "ZJetsToNuNu_HT-100To200_76x_v2"         : 5240199, 
                "ZJetsToNuNu_HT-200To400_76x_v2"         : 5135542,
                "ZJetsToNuNu_HT-400To600_76x_v2"         : 954435,
                "ZJetsToNuNu_HT-600ToInf_76x_v2"         : 1033818,
                "WJetsToLNu_HT-100To200_76x_v2"          : 10205377, 
                "WJetsToLNu_HT-200To400_76x_v2"          : 4949568,
                "WJetsToLNu_HT-400To600_76x_v2"          : 1943664,
                "WJetsToLNu_HT-600ToInf_76x_v2"          : 1041358,
                "WW_76x_v2"                              : 988418,
                "ZZ_76x_v2"                              : 985600,
                "WZ_76x_v2"                              : 1000000,  
                "TTJets_amcatnloFXFX_76x_v2"             : 38475776,
                "TTJets_amcatnloFXFX_76x_v2_ext"         : 196937036,
                "QCD_HT200to300_76x_v2"                  : 18784379, 
                "QCD_HT300to500_76x_v2"                  : 16909004,
                "QCD_HT500to700_76x_v2"                  : 19665695,
                "QCD_HT700to1000_76x_v2"                 : 15547962,
                "QCD_HT1000to1500_76x_v2"                : 5049267,
                "QCD_HT1500to2000_76x_v2"                : 3939077,    
                "QCD_HT2000toInf_76x_v2"                 : 1981228,              
                }

usedXsec = configXsecs[SAMPLE]
usedNevents = configNevents[SAMPLE]

#*******************************************************************************************************#

### Hadronic and leptonic boson.
process.load("ExoDiBosonResonances.EDBRCommon.leptonicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZ_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZnu_cff")

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
                                          targetLumiInvPb = cms.double  (  2086.097                  ),
                                          EDBRChannel     = cms.string  (  CHANNEL                   ),
                                          gravitonSrc     = cms.string  ( "graviton"                 ),
                                          metSrc          = cms.string  ( "slimmedMETs"              ),
                                          niceak4JetsSrc  = cms.InputTag( "niceak4Jets"              ),
                                          vertex          = cms.InputTag( "goodOfflinePrimaryVertex" ),
                                          puWeights       = cms.FileInPath( "ExoDiBosonResonances/EDBRTreeMaker/data/inputfiles/pileupWeights69mb.root"),
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
    process.load("ExoDiBosonResonances.EDBRCommon.Numberjetsak4QCD_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.deltaPhiak4Jets_cff")
    process.hadronicV.cut = cms.string('pt > 200. '
                                       '& (userFloat("ak8PFJetsCHSSoftDropMass") > 50.) '
                                       '& (userFloat("ak8PFJetsCHSSoftDropMass") < 110.)')
    ##-----  FOR NOW JUST CUT IN MET -------------##
    ## NO CUT FOR NOW, WE IMPOSE THIS AFTER PRODUCE THE TREE
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

 
    process.hadronicVFilter.src = cms.InputTag("hadronicVnu")
    ## Why the best hadronicV candidate has the largest pt?
    process.bestHadronicV.src   = cms.InputTag("hadronicVnu")

    TRANSVERSEMASSCUT = 'sqrt(2.0*daughter(0).pt()*daughter(1).pt()*(1.0-cos(daughter(0).phi()-daughter(1).phi()))) > 600'


    process.graviton.decay  =  cms.string("goodMET hadronicVnu")
    process.graviton.cut    =  cms.string(TRANSVERSEMASSCUT)
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




    ###---------------- MET FILTERS for MINIAOD v2 -----------------------------------###
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




    process.HBHEmetfilterSequence = cms.Sequence( process.HBHENoiseFilterResultProducer *
                                                 process.ApplyBaselineHBHENoiseFilter *
                                                 process.ApplyBaselineHBHEIsoNoiseFilter
                              
   )
#++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++#



    process.analysis.replace(       process.jetSequence,
                                    process.hltSequenceZnu             *
                                    process.HBHEmetfilterSequence      *  
                                    process.metfilterSequence          *
                                    process.VertexSequence             *
                                    process.jetSequence                *
                                    process.ak4jetSequence             *
                                    process.Numberjetsak4QCDSequence   *
                                    process.deltaPhiak4JetsSequence    *   
                                    process.metSequence                *  
                                    process.egmGsfElectronIDs          *    
                                    process.VETOSelectEvents           *
                                    process.egmPhotonIDs               * 
                                    process.photonvetoSequence         *
                                    process.muonsVetoSequence          *
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
                                   fileName = cms.string("treeEDBR_"+SAMPLE+"_CUTS.root")
                                  )
