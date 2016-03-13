##+++++++++++++++++++++++++++++++++++++++++++++++++++#
## Configuration File for run with DATA              #
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
process.GlobalTag.globaltag = '76X_dataRun2_16Dec2015_v0'

##***************************************************************************************#
##     3. Channel                                                                        #
##***************************************************************************************#
CHANNEL         = "VZnu_CHANNEL" 
VZ_JetMET       = True


##***************************************************************************************#
##     4. Samples                                                                        #
##***************************************************************************************#                
#SAMPLE="MET_Run2015D_16Dec2015_v1"
SAMPLE="MET_Run2015C_25ns_16Dec2015_v1"

### To use with CRAB
#import sys
#SAMPLE = str(sys.argv[2])


##***************************************************************************************#
##     5. Source and Number of events to run                                             #
##***************************************************************************************#
## Source
process.load("ExoDiBosonResonances.EDBRCommon.DATA76XRERECO."+SAMPLE)
## Number of Events to run
process.maxEvents.input = -1
#process.maxEvents.input = 40000


##***************************************************************************************#
##     6. JSON File                                                                      #
##***************************************************************************************#
# https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/
# last modified 02-Mar-2016 
import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'Cert_13TeV_16Dec2015ReReco_Collisions15_25ns_JSON_v2.txt').getVLuminosityBlockRange()


##***************************************************************************************#
##     7. Cross Section and number of events of the samples                              #
##***************************************************************************************#

configXsecs = { 
                "MET_Run2015D_16Dec2015_v1"           : 1,
                "MET_Run2015C_25ns_16Dec2015_v1"      : 1,                
              }

configNevents = {

                "MET_Run2015D_16Dec2015_v1"           : 1,
                "MET_Run2015C_25ns_16Dec2015_v1"      : 1,       
                }

usedXsec = configXsecs[SAMPLE]
usedNevents = configNevents[SAMPLE]


##***************************************************************************************#
##     8. Configuration files to load                                                    #
##***************************************************************************************#
process.load("ExoDiBosonResonances.EDBRCommon.hltFilterZnu_cff")
process.load("ExoDiBosonResonances.EDBRCommon.hadronicZnu_cff")
process.load("ExoDiBosonResonances.EDBRCommon.METFiltersDATA_cff")
process.load("ExoDiBosonResonances.EDBRCommon.goodVertex_cff")
process.load("ExoDiBosonResonances.EDBRCommon.niceJets_cff")
process.load("ExoDiBosonResonances.EDBRCommon.niceak4Jets_cff")
process.load("ExoDiBosonResonances.EDBRCommon.goodMET_cff")
process.load("ExoDiBosonResonances.VetoesProducer.photon_Vetoes_cff")
process.load("ExoDiBosonResonances.VetoesProducer.ele_Vetoes_cff")
process.load("ExoDiBosonResonances.VetoesProducer.Muon_Vetoes_cff")
process.load("ExoDiBosonResonances.VetoesProducer.Taus_Vetoes_cff")
process.load("ExoDiBosonResonances.EDBRCommon.Numberjetsak4QCD_cff")
process.load("ExoDiBosonResonances.EDBRCommon.deltaPhiak4Jets_cff")


##***************************************************************************************#
##     9. Modules                                                                        #
##***************************************************************************************#
TRANSVERSEMASSCUT = 'sqrt(2.0*daughter(0).pt()*daughter(1).pt()*(1.0-cos(daughter(0).phi()-daughter(1).phi()))) > 600'


process.corrJetsProducer.isData = True

process.niceak4JetsSelector = cms.EDFilter(     "CandViewSelector",
                                                src                 = cms.InputTag  (  "niceak4Jets"              ),
                                                cut                 = cms.string    (   ""                        ),
                                                filter              = cms.bool      (   True                      ) )


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
                                                isData              = cms.bool      (  True                       ),
                                                originalNEvents     = cms.int32     (  usedNevents                ),
                                                crossSectionPb      = cms.double    (  usedXsec                   ),
                                                targetLumiInvPb     = cms.double    (  1                          ),
                                                EDBRChannel         = cms.string    (  CHANNEL                    ),
                                                niceak4JetsSrc      = cms.InputTag  (  "niceak4Jets"              ),
                                                vertex              = cms.InputTag  (  "goodOfflinePrimaryVertex" ))
                                                     

##***************************************************************************************#
##     10. Electron and Photon ID                                                         #
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
##     11. Sequences                                                                     #
##***************************************************************************************# 
process.jetSequence       = cms.Sequence  (
                                             process.fatJetsNuSequence          *
                                             process.hadronicVnuSequence        * 
                                             process.bestHadronicVnu            
                                                                                )

process.ak4jetSequence    = cms.Sequence  (  process.ak4JetsNuSequence          *
                                             process.niceak4JetsSelector  
                                                                                )

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
                                             process.Numberjetsak4QCDSequence   *
                                             process.deltaPhiak4JetsSequence    *
                                             process.egmGsfElectronIDs          *
                                             process.VETOSelectEvents           *
                                             process.egmPhotonIDs               *
                                             process.photonvetoSequence         *
                                             process.muonsVetoSequence          *
                                             process.tausVetoSequence           *
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
