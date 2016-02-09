import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1600_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/6A28CB6C-C67D-E511-A5EB-0025905B861C.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1600_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/7CC3175A-C67D-E511-B809-003048FFD71E.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1600_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/DA442BE6-C47D-E511-A02C-00A0D1EE8AF0.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1600_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/DA55356F-C67D-E511-ACE2-0025905A6080.root' ] );


secFiles.extend( [
               ] )


