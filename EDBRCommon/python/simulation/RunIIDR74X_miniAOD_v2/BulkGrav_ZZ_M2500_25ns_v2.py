import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/0ED5E0B9-0685-E511-8179-901B0E5427A6.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/90D28414-0685-E511-B72D-002590596486.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/30000/AC404B0F-0685-E511-8147-0025905A60E4.root' ] );


secFiles.extend( [
               ] )


