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


#*********************************** THE SAMPLES ****************************************************#
### CHOOSE THE SAMPLE :                                                                   

###-------- RSGRrav------------------
#SAMPLE="RSGravToZZ_kMpl01_M-2000_25ns"

###------   Z +JETS  -----------
#SAMPLE="ZJetsToNuNu_HT-100To200_25ns"
#SAMPLE="ZJetsToNuNu_HT-200To400_25ns"
#SAMPLE="ZJetsToNuNu_HT-400To600_25ns"
#SAMPLE="ZJetsToNuNu_HT-600ToInf_25ns"

###-----   W + jets-------------------
#SAMPLE="WJetsToLNu_25ns_inclusive"
#SAMPLE="WJetsToLNu_HT-100To200_25ns"
#SAMPLE="WJetsToLNu_HT-200To400_25ns"
#SAMPLE="WJetsToLNu_HT-400To600_25ns"
SAMPLE="WJetsToLNu_HT-600ToInf_25ns"

### ------- TTJets ------------------
#SAMPLE="TTJets_25ns_madgraph"
#SAMPLE="TTjets_25ns_powheg" 

### ------- Dibosons ---------------
#SAMPLE="WW_25ns"
#SAMPLE="WZ_25ns"
#SAMPLE="ZZ_25ns"


### Source
process.load("ExoDiBosonResonances.EDBRCommon.simulation.RunIIDR74X."+SAMPLE)
process.maxEvents.input = -1
#process.maxEvents.input = 10000

process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999

configXsecs = { "WJetsToLNu_25ns_inclusive"            : 61526.7,
                "RSGravToZZ_kMpl01_M-2000_25ns"        : 1,
                "ZJetsToNuNu_HT-100To200_25ns"         : 280.47,
                "ZJetsToNuNu_HT-200To400_25ns"         : 78.36,
                "ZJetsToNuNu_HT-400To600_25ns"         : 10.944,
                "ZJetsToNuNu_HT-600ToInf_25ns"         : 4.203,
                "WJetsToLNu_HT-100To200_25ns"          : 1292,
                "WJetsToLNu_HT-200To400_25ns"          : 385.9,
                "WJetsToLNu_HT-400To600_25ns"          : 47.9,
                "WJetsToLNu_HT-600ToInf_25ns"          : 19.9,

              }

configNevents = {"WJetsToLNu_25ns_inclusive"            : 24089991,
                 "RSGravToZZ_kMpl01_M-2000_25ns"        : 29751,
                 "ZJetsToNuNu_HT-100To200_25ns"         : 5148193,
                 "ZJetsToNuNu_HT-200To400_25ns"         : 5032927,
                 "ZJetsToNuNu_HT-400To600_25ns"         : 1014139,
                 "ZJetsToNuNu_HT-600ToInf_25ns"         : 1015904,
                 "WJetsToLNu_HT-100To200_25ns"          : 10142187,
                 "WJetsToLNu_HT-200To400_25ns"          : 5231856,
                 "WJetsToLNu_HT-400To600_25ns"          : 1901705,
                 "WJetsToLNu_HT-600ToInf_25ns"          : 1036108,

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

process.treeDumper = cms.EDAnalyzer(      "EDBRTreeMaker",
                                          isGen           = cms.bool    (  False                     ),
                                          isData          = cms.bool    (  False                     ),
                                          originalNEvents = cms.int32   (  usedNevents               ),
                                          crossSectionPb  = cms.double  (  usedXsec                  ),
                                          targetLumiInvPb = cms.double  (  594.65                    ),
                                          EDBRChannel     = cms.string  (  CHANNEL                   ),
                                          gravitonSrc     = cms.string  ( "graviton"                 ),
                                          metSrc          = cms.string  ( "slimmedMETs"              ),
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



