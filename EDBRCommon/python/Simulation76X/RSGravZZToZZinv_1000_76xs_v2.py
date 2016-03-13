import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/80000/C46D8DE5-6DD8-E511-AEF5-0CC47A4C8E3C.root',
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/80000/D053A8E2-6DD8-E511-BC5D-00261894385A.root',
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/80000/F203B4DC-6DD8-E511-8E60-002618943821.root',
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/80000/F4CBDBE0-6DD8-E511-9569-FA163E821B72.root' ] );


secFiles.extend( [
               ] )


