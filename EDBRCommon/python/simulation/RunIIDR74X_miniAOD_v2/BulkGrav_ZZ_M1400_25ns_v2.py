import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1400_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/22886FEF-BF7C-E511-8053-FA163EE1E66B.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1400_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/98C81614-C07C-E511-9999-FA163E2945A2.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1400_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/B61FC0AF-CE7C-E511-AFC4-00259074AE52.root' ] );


secFiles.extend( [
               ] )


