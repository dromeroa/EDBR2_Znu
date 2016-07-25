import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/06F02B09-AD26-E611-9A26-02163E013901.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/16DEA4DF-B926-E611-A0FE-02163E0137E7.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/C22E3A47-A726-E611-8BF1-02163E01432E.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/C2C43A47-A726-E611-AEC5-02163E01432E.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/DE23C5EF-B726-E611-8BF8-00259074AE3E.root' ] );


secFiles.extend( [
               ] )

