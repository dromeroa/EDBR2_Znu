import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/54C5ABB2-207B-E511-A405-B083FED3EE25.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/78DF90BC-207B-E511-9F14-B083FED14CE1.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4000_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/DC1CBE16-617B-E511-8F8B-18A90570ABE0.root' ] );


secFiles.extend( [
               ] )


