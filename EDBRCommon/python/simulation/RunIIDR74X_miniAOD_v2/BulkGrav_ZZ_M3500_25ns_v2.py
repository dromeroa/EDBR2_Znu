import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-3500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/242DD900-A17E-E511-8863-B083FED76508.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-3500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/946AAD24-A17E-E511-B35B-008CFAF06A80.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-3500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/A4F5C962-A17E-E511-91DB-F45214C748C8.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-3500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/50000/C8E5900A-A17E-E511-8E3B-B083FED7685B.root' ] );


secFiles.extend( [
               ] )


