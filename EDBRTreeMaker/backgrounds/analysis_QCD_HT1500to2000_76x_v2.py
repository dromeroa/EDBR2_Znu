##+++++++++++++++++++++++++++++++++++++++++++++++++++#
## Configuration File for run with MC                #
## In the VZ(nunu) Channel                           #
##+++++++++++++++++++++++++++++++++++++++++++++++++++#


import FWCore.ParameterSet.Config as cms
process = cms.Process( "TEST" )


##****************************************************************************************#
##     1. Summary and Messages                                                            #
##****************************************************************************************#
process.options = cms.untracked.PSet(wantSummary = cms.untracked.bool(True))
process.load("FWCore.MessageLogger.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
process.MessageLogger.cerr.FwkReport.limit = 99999999


##***************************************************************************************#
##     2. Global Tag                                                                     #
##***************************************************************************************#
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff")
## FROM March 05 2016
process.GlobalTag.globaltag = '76X_mcRun2_asymptotic_RunIIFall15DR76_v1'


##***************************************************************************************#
##     3. Channel                                                                        #
##***************************************************************************************#
CHANNEL         = "VZnu_CHANNEL" 
VZ_JetMET       = True


##***************************************************************************************#
##     4. Samples                                                                        #
##***************************************************************************************#                
## Signal                                                         
#SAMPLE="RSGravZZToZZinv_1000_76xs_v2"

## Backgrounds
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
SAMPLE="QCD_HT1500to2000_76x_v2"
#SAMPLE="QCD_HT1000to1500_76x_v2"
#SAMPLE="QCD_HT700to1000_76x_v2"
#SAMPLE="QCD_HT500to700_76x_v2"
#SAMPLE="QCD_HT300to500_76x_v2"
#SAMPLE="QCD_HT200to300_76x_v2"
#SAMPLE="QCD_HT100to200_76x_v2"

### To use with CRAB
#import sys
#SAMPLE = str(sys.argv[2])


##***************************************************************************************#
##     5. Source and Number of events to run                                             #
##***************************************************************************************#
## Source
process.load("ExoDiBosonResonances.EDBRCommon.Simulation76X."+SAMPLE)
## Number of Events to run
process.maxEvents.input = -1
#process.maxEvents.input = 40000


##***************************************************************************************#
##     6. Cross Section and number of events of the samples                              #
##***************************************************************************************#
## Cross sections based on
## https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns (1 Billion campaign)

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
                "TTJets_amcatnloFXFX_76x_v2"             : 12771412, ## Effective (sumweight) -> generated : 38475776
                "TTJets_amcatnloFXFX_76x_v2_ext"         : 65363623, ## Effective (sumewight) -> generated : 196937036
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


##***************************************************************************************#
##     7. Configuration files to load                                                    #
##***************************************************************************************#
process.load("ExoDiBosonResonances.EDBRCommon.hltFilterZnu_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZnu_cff")
process.load("ExoDiBosonResonances.EDBRCommon.METFiltersMC_cff")
process.load("ExoDiBosonResonances.EDBRCommon.goodVertex_cff")
process.load("ExoDiBosonResonances.EDBRCommon.niceJets_cff")
process.load("ExoDiBosonResonances.EDBRCommon.niceak4Jets_cff")
process.load("ExoDiBosonResonances.EDBRCommon.extraJets_cff")
process.load("ExoDiBosonResonances.EDBRCommon.goodMET_cff")
#process.load("ExoDiBosonResonances.VetoesProducer.photon_Vetoes_cff")
#process.load("ExoDiBosonResonances.VetoesProducer.ele_Vetoes_cff")
#process.load("ExoDiBosonResonances.VetoesProducer.Muon_Vetoes_cff")
process.load("ExoDiBosonResonances.VetoesProducer.Taus_Vetoes_cff")
#process.load("ExoDiBosonResonances.VetoesProducer.btag_Veto_cff")
process.load("ExoDiBosonResonances.EDBRCommon.FilterdeltaPhi_cff")

##***************************************************************************************#
##     8. Modules                                                                        #
##***************************************************************************************#
TRANSVERSEMASSCUT = 'sqrt(2.0*daughter(0).pt()*daughter(1).pt()*(1.0-cos(daughter(0).phi()-daughter(1).phi()))) > 600'

process.bestHadronicVnu = cms.EDFilter(         "LargestPtCandSelector",
                                                src                 = cms.InputTag  (  "hadronicVnu"              ),
                                                maxNumber           = cms.uint32    (  1                          ) )


process.graviton = cms.EDProducer(              "CandViewCombiner",
                                                decay               = cms.string    (  "goodMET bestHadronicVnu"  ),
                                                checkCharge         = cms.bool      (  False                      ),
                                                cut                 = cms.string    (  TRANSVERSEMASSCUT          ),
                                                roles               = cms.vstring   (  'goodMET', 'hadronicVnu'   ) )


process.gravitonFilter = cms.EDFilter(          "CandViewCountFilter",
                                                src                 = cms.InputTag  (  "graviton"                 ),
                                                minNumber           = cms.uint32    (  1                          ),
                                                filter              = cms.bool      (  True                       ) )


process.treeDumper = cms.EDAnalyzer(            "EDBRTreeMaker",
                                                isGen               = cms.bool      (  False                      ),
                                                isData              = cms.bool      (  False                      ),
                                                correctEW           = cms.bool      (  False                      ),
                                                correctBtag         = cms.bool      (  False                      ),    
                                                originalNEvents     = cms.int32     (  usedNevents                ),
                                                crossSectionPb      = cms.double    (  usedXsec                   ),
                                                targetLumiInvPb     = cms.double    (  2307                       ),
                                                EDBRChannel         = cms.string    (  CHANNEL                    ),
                                                niceextraJetsSrc    = cms.InputTag  (  "niceextraJets"            ),
                                                niceak4JetsSrc      = cms.InputTag  (  "niceak4Jets"              ),
                                                muons               = cms.InputTag("slimmedMuons"),
                                                electrons           = cms.InputTag("slimmedElectrons"),
                                                photons             = cms.InputTag("slimmedPhotons"),
                                                puWeights           = cms.FileInPath(  "ExoDiBosonResonances/EDBRTreeMaker/data/inputfiles/pileupWeights69mb.root"),
                                                electronsSFs = cms.FileInPath("ExoDiBosonResonances/EDBRTreeMaker/data/inputfiles/CutBasedID_VetoWP_76X_18Feb.txt_SF2D.root"),
                                                elrecoSFs = cms.FileInPath("ExoDiBosonResonances/EDBRTreeMaker/data/inputfiles/eleRECO.txt_SF2D.root"),
                                                photonsSFs = cms.FileInPath("ExoDiBosonResonances/EDBRTreeMaker/data/inputfiles/Loosenumbers.txt.egamma_SF2D.root"),
                                                muonSFs = cms.FileInPath("ExoDiBosonResonances/EDBRTreeMaker/data/inputfiles/MuonID_Z_RunCD_Reco76X_Feb15.root"),
                                                muIsoSFs = cms.FileInPath("ExoDiBosonResonances/EDBRTreeMaker/data/inputfiles/MuonIso_Z_RunCD_Reco76X_Feb15.root"),
                                                btaggEff = cms.FileInPath("ExoDiBosonResonances/EDBRTreeMaker/data/inputfiles/btaggMaps/RSGravZZToZZinv_1000_MAP.root"),
                                                triggerSFs = cms.FileInPath("ExoDiBosonResonances/EDBRTreeMaker/data/inputfiles/mettrigSF.root"),
                                                vertex              = cms.InputTag  (  "goodOfflinePrimaryVertex" ),
                                                pruned              = cms.InputTag  (    "prunedGenParticles"     ))




                                                    

##***************************************************************************************#
##     9. Electron and Photon ID                                                         #
##***************************************************************************************# 
from PhysicsTools.SelectorUtils.tools.vid_id_tools import *

switchOnVIDElectronIdProducer(process, DataFormat.MiniAOD)
my_el_modules = ['RecoEgamma.ElectronIdentification.Identification.cutBasedElectronID_Spring15_25ns_V1_cff',
                 'RecoEgamma.ElectronIdentification.Identification.heepElectronID_HEEPV60_cff']
for idmod in my_el_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDElectronSelection)

switchOnVIDPhotonIdProducer(process, DataFormat.MiniAOD)
my_pho_modules = ['RecoEgamma.PhotonIdentification.Identification.cutBasedPhotonID_Spring15_25ns_V1_cff']
for idmod in my_pho_modules:
    setupAllVIDIdsInModule(process,idmod,setupVIDPhotonSelection)


##***************************************************************************************#
##     10. Sequences                                                                     #
##***************************************************************************************# 
process.jetSequence       = cms.Sequence  (
                                             process.fatJetsNuSequence          *
                                             process.hadronicVnuSequence        * 
                                             process.bestHadronicVnu            
                                                                                )

process.ak4jetSequence    = cms.Sequence  (  process.ak4JetsNuSequence          ) 


process.extrajetSequence  = cms.Sequence  (  process.extraJetsNuSequence        )


process.gravitonSequence  = cms.Sequence  (  process.graviton                   *
                                             process.gravitonFilter   
                                                                                )

process.analysis          = cms.Path(       
                                             process.hltSequenceZnu             *
                                             process.metfilterSequence          *
                                             process.VertexSequence             *
                                             process.metSequence                *
                                             process.jetSequence                *
                                             process.ak4jetSequence             *
                                             process.extrajetSequence           *
                                             process.mindeltaPhiSequence        *
#                                             process.egmGsfElectronIDs          *
#                                             process.VETOSelectEvents           *
#                                             process.egmPhotonIDs               *
#                                             process.photonvetoSequence         *
#                                             process.muonsVetoSequence          *
                                             process.tausVetoSequence           *
#                                             process.bJetsVetoSequence          *
                                             process.gravitonSequence           * 
                                             process.treeDumper       
                                                                                )
 
###################################################################################################

print "++++++++++ CUTS ++++++++++\n"
print "Graviton cut = "+str(process.graviton.cut)
print "Hadronic V cut = "+str(process.hadronicVnu.cut)
print "MET cut = "+str(process.goodMET.cut)
print "\n++++++++++++++++++++++++++"

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("treeEDBR_"+SAMPLE+".root")
                                  )
