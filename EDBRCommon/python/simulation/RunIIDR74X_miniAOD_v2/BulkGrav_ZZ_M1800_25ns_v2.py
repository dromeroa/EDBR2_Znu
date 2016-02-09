import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1800_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/06122346-827E-E511-B3E6-AC162DA8E1E8.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1800_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/0875A851-827E-E511-963C-001E675A6AB3.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1800_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/0CBD2F47-827E-E511-BC88-AC162DACC3F0.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1800_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/38747B4A-827E-E511-839F-008CFA111174.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1800_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/8C94D576-827E-E511-B53A-0026B94DBD88.root' ] );


secFiles.extend( [
               ] )


