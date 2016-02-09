import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-800_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/20000/7858D300-257C-E511-9054-000F530E4BD4.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-800_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/20000/AE5CCC42-E77B-E511-A81A-20CF300E9ECF.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-800_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/20000/E6CD943A-E77B-E511-A249-20CF3056170A.root' ] );


secFiles.extend( [
               ] )

