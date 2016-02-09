import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-3000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/18C2DF61-A17E-E511-82E6-0026189438B9.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-3000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/50CA7766-A17E-E511-8C29-0025905A6056.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-3000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/EAF24760-A17E-E511-9CE4-001EC9AE1AE3.root' ] );


secFiles.extend( [
               ] )

