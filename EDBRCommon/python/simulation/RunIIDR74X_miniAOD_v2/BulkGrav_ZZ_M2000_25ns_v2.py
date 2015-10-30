import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/50840E74-3B7C-E511-9E96-008CFA1979B0.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/54A978FB-4679-E511-95A4-00505602077E.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/782951F3-4579-E511-8269-02163E016A8C.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-2000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/8E1B6715-4779-E511-BF5E-00259073E322.root' ] );


secFiles.extend( [
               ] )

