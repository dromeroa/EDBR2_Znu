### FOR 25 ns --------------------------###

import FWCore.ParameterSet.Config as cms

process = cms.Process( "TEST" )
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))

#process.load("Configuration.StandardSequences.Geometry_cff")
#process.load("Configuration.Geometry.GeometryIdeal_cff")
process.load('Configuration.StandardSequences.Services_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
# This is for MC
#### find the global tag in the DAS under the Configs for given dataset
#### for 50 ns
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

#*********************************** THE SAMPLES ****************************************************#
# choose the sample                                                                     

#SAMPLE="RSGravToZZ_kMpl01_M-2000_25ns"
#SAMPLE="RSGravToZZ_kMpl01_50ns_M_1000"
#SAMPLE="RSGravToZZ_kMpl01_50ns_M_2000"
#SAMPLE="BulkGravToZZToZlepZhad_M-600" 
#SAMPLE="BulkGravToZZToZlepZhad_M-800" 
#SAMPLE="BulkGravToZZToZlepZhad_M-1000" 
#SAMPLE="BulkGravToZZToZlepZhad_M-1200" 
#SAMPLE="BulkGravToZZToZlepZhad_M-1400" 
#SAMPLE="BulkGravToZZToZlepZhad_M-1600" 
#SAMPLE="BulkGravToZZToZlepZhad_M-1800" 
#SAMPLE="BulkGravToZZToZlepZhad_M-2000" 
#SAMPLE="BulkGravToZZToZlepZhad_M-2500" 
#SAMPLE="BulkGravToZZToZlepZhad_M-3000" 
#SAMPLE="BulkGravToZZToZlepZhad_M-3500" 
#SAMPLE="BulkGravToZZToZlepZhad_M-4000" 
#SAMPLE="BulkGravToZZToZlepZhad_M-4500" 

###------   Z +JETS  -----------
SAMPLE="ZJetsToNuNu_HT-100To200_25ns"
#SAMPLE="ZJetsToNuNu_HT-200To400_25ns"
#SAMPLE="ZJetsToNuNu_HT-400To600_25ns"
#SAMPLE="ZJetsToNuNu_HT-600ToInf_25ns"
###--- W + jets---------------------

#SAMPLE="WJetsToLNu_25ns"

###-------  QCD   -----------------

#SAMPLE="QCD_Pt_120to170_13TeV_50ns"
#SAMPLE="QCD_Pt_170to300_13TeV_50ns"
#SAMPLE="QCD_Pt_300to470_13TeV_50ns"
#SAMPLE="QCD_Pt_470to600_13TeV_50ns"
#SAMPLE="QCD_Pt_600to800_13TeV_50ns"        
#SAMPLE="QCD_Pt_800to1000_13TeV_50ns"        
#SAMPLE="QCD_Pt_1000to1400_13TeV_50ns"       
#SAMPLE="QCD_Pt_1400to1800_13TeV_50ns"      
#SAMPLE="QCD_Pt_1800to2400_13TeV_50ns"     
#SAMPLE="QCD_Pt_2400to3200_13TeV_50ns"       
#SAMPLE="QCD_Pt_3200toInf_13TeV_50ns" 


### Source
process.load("ExoDiBosonResonances.EDBRCommon.simulation.RunIIDR74X."+SAMPLE)
process.maxEvents.input = -1
#process.maxEvents.input = 1000

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

configXsecs = {  "BulkGravToZZToZlepZhad_M-600"         : 4.0151E-04,
                 "BulkGravToZZToZlepZhad_M-800"         : 7.3592E-05,
                 "BulkGravToZZToZlepZhad_M-1000"        : 1.9648E-05,
                 "BulkGravToZZToZlepZhad_M-1200"        : 6.5205E-06,
                 "BulkGravToZZToZlepZhad_M-1400"        : 2.4833E-06,
                 "BulkGravToZZToZlepZhad_M-1600"        : 8.1645E-07,
                 "BulkGravToZZToZlepZhad_M-1800"        : 3.7583E-07,
                 "BulkGravToZZToZlepZhad_M-2000"        : 2.2636E-07,
                 "BulkGravToZZToZlepZhad_M-2500"        : 4.2349E-08,
                 "BulkGravToZZToZlepZhad_M-3000"        : 9.2671E-09,
                 "BulkGravToZZToZlepZhad_M-3500"        : 4.7064E-09,
                 "BulkGravToZZToZlepZhad_M-4000"        : 1.9530E-09,
                 "BulkGravToZZToZlepZhad_M-4500"        : 8.9900E-10,
                 "RSGravToZZ_kMpl01_50ns_M_1000"        : 1,
                 "RSGravToZZ_kMpl01_50ns_M_2000"        : 1,
                 "WJetsToLNu"                           : 61526.7,
                 "QCD_Pt_120to170_13TeV_50ns"           : 471100,
                 "QCD_Pt_170to300_13TeV_50ns"           : 117276,
                 "QCD_Pt_300to470_13TeV_50ns"           : 7823.0,
                 "QCD_Pt_470to600_13TeV_50ns"           : 648.2,
                 "QCD_Pt_600to800_13TeV_50ns"           : 186.9,
                 "QCD_Pt_800to1000_13TeV_50ns"          : 32.293,
                 "QCD_Pt_1000to1400_13TeV_50ns"         : 9.83,
                 "QCD_Pt_1400to1800_13TeV_50ns"         : 0.842650,
                 "QCD_Pt_1800to2400_13TeV_50ns"         : 0.114943,
                 "QCD_Pt_2400to3200_13TeV_50ns"         : 0.006830,
                 "QCD_Pt_3200toInf_13TeV_50ns"          : 0.000165,
                 "RSGravToZZ_kMpl01_M-2000_25ns"        : 1,
                 "ZJetsToNuNu_HT-100To200_25ns"         : 280.47,
                 "ZJetsToNuNu_HT-200To400_25ns"         : 78.36,  
                 "ZJetsToNuNu_HT-400To600_25ns"         : 10.944,        
                 "ZJetsToNuNu_HT-600ToInf_25ns"         : 4.203,
                 "WJetsToLNu_25ns"                      : 61526.7,       
              }

configNevents = {"BulkGravToZZToZlepZhad_M-600"         : 50000,
                 "BulkGravToZZToZlepZhad_M-800"         : 50000,
                 "BulkGravToZZToZlepZhad_M-1000"        : 48400,
                 "BulkGravToZZToZlepZhad_M-1200"        : 49200,
                 "BulkGravToZZToZlepZhad_M-1400"        : 50000,
                 "BulkGravToZZToZlepZhad_M-1600"        : 50000,
                 "BulkGravToZZToZlepZhad_M-1800"        : 50000,
                 "BulkGravToZZToZlepZhad_M-2000"        : 50000,
                 "BulkGravToZZToZlepZhad_M-2500"        : 50000,
                 "BulkGravToZZToZlepZhad_M-3000"        : 49200,
                 "BulkGravToZZToZlepZhad_M-3500"        : 50000,
                 "BulkGravToZZToZlepZhad_M-4000"        : 50000,
                 "BulkGravToZZToZlepZhad_M-4500"        : 50000,
                 "RSGravToZZ_kMpl01_50ns_M_1000"        : 29586,
                 "RSGravToZZ_kMpl01_50ns_M_2000"        : 29751,
                 "WJetsToLNu"                           : 24089991,
                 "QCD_Pt_120to170_13TeV_50ns"           : 3446207,
                 "QCD_Pt_170to300_13TeV_50ns"           : 3438066,
                 "QCD_Pt_300to470_13TeV_50ns"           : 2930578,
                 "QCD_Pt_470to600_13TeV_50ns"           : 1939229,
                 "QCD_Pt_600to800_13TeV_50ns"           : 1890256,
                 "QCD_Pt_800to1000_13TeV_50ns"          : 1911296,
                 "QCD_Pt_1000to1400_13TeV_50ns"         : 1461216,
                 "QCD_Pt_1400to1800_13TeV_50ns"         : 197959,
                 "QCD_Pt_1800to2400_13TeV_50ns"         : 194924,
                 "QCD_Pt_2400to3200_13TeV_50ns"         : 198383,
                 "QCD_Pt_3200toInf_13TeV_50ns"          : 188696,
                 "RSGravToZZ_kMpl01_M-2000_25ns"        : 29751,
                 "ZJetsToNuNu_HT-100To200_25ns"         : 5148193,
                 "ZJetsToNuNu_HT-200To400_25ns"         : 5032927,
                 "ZJetsToNuNu_HT-400To600_25ns"         : 1014139,
                 "ZJetsToNuNu_HT-600ToInf_25ns"         : 1015904,
                 "WJetsToLNu_25ns"                      : 24151270,   
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

process.graviton = cms.EDProducer(        "CandViewCombiner",
                                          decay = cms.string("bestLeptonicV bestHadronicV"),
                                          checkCharge = cms.bool(False),
                                          cut = cms.string("mass > 400"),
                                          roles = cms.vstring('leptonicV', 'hadronicV') )

process.gravitonFilter =  cms.EDFilter(   "CandViewCountFilter",
                                          src = cms.InputTag("graviton"),
                                          minNumber = cms.uint32(1),
                                          filter = cms.bool(True) )

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

if option == 'RECO':
    process.load("ExoDiBosonResonances.EDBRCommon.hltFilterZnu_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.METFilters_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodVertex_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodJets_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.niceJets_cff")
    process.load("ExoDiBosonResonances.EDBRCommon.goodMET_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.photon_Vetoes_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.ele_Vetoes_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.Muon_Vetoes_cff")
    process.load("ExoDiBosonResonances.VetoesProducer.Taus_Vetoes_cff")
    process.hadronicV.cut = cms.string('pt > 200. '
                                       '& (userFloat("ak8PFJetsCHSSoftDropMass") > 50.) '
                                       '& (userFloat("ak8PFJetsCHSSoftDropMass") < 110.)')
    ##-----  FOR NOW NO CUT IN JET MASS  --------------##
    process.hadronicVnu.cut = cms.string('pt > 200. ')
    process.goodMET.cut = "pt > 250"




process.treeDumper = cms.EDAnalyzer(      "EDBRTreeMaker",
                                          isGen           = cms.bool    (  False                     ),
                                          isData          = cms.bool    (  False                      ),
                                          originalNEvents = cms.int32   (  usedNevents               ),
                                          crossSectionPb  = cms.double  (  usedXsec                  ),
                                          targetLumiInvPb = cms.double  (   15.48                    ),
                                          EDBRChannel     = cms.string  (  CHANNEL                   ),
                                          gravitonSrc     = cms.string  ( "graviton"                 ),
                                          metSrc          = cms.string  ( "slimmedMETs"              ),
                                          vertex          = cms.InputTag( "goodOfflinePrimaryVertex" ),
                                          metnohf         = cms.InputTag( "slimmedMETsNoHF"          ),
                                          ak4jetscorr     = cms.InputTag( "slimmedJetsRecorrected"   ),
                                          payload         = cms.string  ( "AK8PFchs"                 ))

#***************************************** SEQUENCES **********************************************# 

process.leptonSequence = cms.Sequence(    process.leptonicVSequence +
                                          process.leptonicVFilter   +
                                          process.leptonicVSelector + 
                                          process.bestLeptonicV     )

process.jetSequence = cms.Sequence(       process.fatJetsSequence   +
                                          process.hadronicV         +
                                          process.hadronicVFilter   +
                                          process.bestHadronicV     )

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

### WE NEED TO USE THE NEW MET TO FORM THE GRAVITON


if VZ_JetMET == True :
 
    process.hadronicVFilter.src = cms.InputTag("hadronicVnu")
    ## Why the best hadronicV candidate has the largest pt?
    process.bestHadronicV.src   = cms.InputTag("hadronicVnu")

    process.graviton.decay  =  cms.string("goodMET hadronicVnu")
    process.graviton.cut    =  cms.string("")
    process.graviton.roles  =  cms.vstring('goodMET', 'hadronicVnu')




    process.jetSequence.replace(    process.fatJetsSequence, 
                                    process.fatJetsNuSequence  *
                                    process.hadronicVnu        )

    process.jetSequence.remove(process.hadronicV) 

    from PhysicsTools.SelectorUtils.tools.vid_id_tools import *
    switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
#    my_el_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_PHYS14_PU20bx25_V2_cff']
#    my_el_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_50ns_V1_cff']
    my_el_modules = ['RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff']
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
                                    process.metSequence              *  
                                    process.egmGsfElectronIDs        *    
                                    process.elevetoSequence          *
                                    process.egmPhotonIDs             *
                                    process.photonvetoSequence       *
                                    process.muonsVetoSequence        *
                                    process.tausVetoSequence
#                                    process.ak4jecSequence       
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


#process.out = cms.OutputModule("PoolOutputModule",
#          fileName = cms.untracked.string('patTuple.root'),
#          outputCommands = cms.untracked.vstring('keep *')
#)
#process.outpath = cms.EndPath(process.out)
