import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1200_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/5094C753-D37C-E511-86DE-00261894391B.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1200_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/A8943F88-D37C-E511-88D4-00259059649C.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1200_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/BA867463-D37C-E511-84DC-00221982D6CC.root',
       '/store/mc/RunIISpring15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-1200_13TeV-madgraph/MINIAODSIM/74X_mcRun2_asymptotic_v2-v1/80000/F4B5565E-D37C-E511-80EE-002481ACDA98.root' ] );


secFiles.extend( [
               ] )

