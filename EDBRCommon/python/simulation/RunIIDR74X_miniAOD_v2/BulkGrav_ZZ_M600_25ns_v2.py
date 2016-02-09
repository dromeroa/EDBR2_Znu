import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-600_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/A67ACEAB-CE7C-E511-8E03-20CF307C98DC.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-600_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/D62507B1-CE7C-E511-B58A-B083FED13803.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-600_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/F21734A8-CE7C-E511-9CED-0025902D06D4.root' ] );


secFiles.extend( [
               ] )
