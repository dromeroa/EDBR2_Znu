import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/20000/380748D4-847E-E511-AD1E-20CF3027A561.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/20000/767BE8A9-847E-E511-998D-0025905A605E.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/20000/B0CD47AF-847E-E511-93FA-002590DB9214.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/20000/B61072C8-847E-E511-BA48-002590207C28.root' ] );


secFiles.extend( [
               ] )

