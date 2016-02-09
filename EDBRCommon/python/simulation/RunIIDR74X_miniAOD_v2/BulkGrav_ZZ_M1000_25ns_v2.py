import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/62954132-557B-E511-89AF-38EAA7A3049A.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/86D4975C-307B-E511-ABEB-000AE488BDEA.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/A4B57052-307B-E511-8F08-00A0D1EE928C.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/FAA29BE2-447C-E511-AB20-001E6758651B.root' ] );


secFiles.extend( [
               ] )

