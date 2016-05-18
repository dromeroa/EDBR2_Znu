import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1200_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/3A42283F-61D8-E511-9B19-02163E01167C.root',
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1200_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/704EF935-61D8-E511-9C64-002590D0AF66.root',
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1200_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/74A35F58-61D8-E511-95E9-0025905A60F8.root',
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1200_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/8E234920-61D8-E511-8636-001EC9AF1E89.root',
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1200_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/00000/B851DC2F-61D8-E511-A842-008CFA1982C0.root' ] );


secFiles.extend( [
               ] )

