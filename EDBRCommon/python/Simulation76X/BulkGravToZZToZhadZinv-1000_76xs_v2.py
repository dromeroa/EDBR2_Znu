import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/164A299C-4E26-E611-AEBD-0CC47A4D764A.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/6AA4079C-4E26-E611-ABA7-0CC47A4D761A.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/BEBC9FBA-4E26-E611-B09A-44A84225CDA4.root' ] );


secFiles.extend( [
               ] )
