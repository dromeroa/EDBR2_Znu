import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1600_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/40000/36C5385C-16D6-E511-95C3-008CFA000898.root',
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1600_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/40000/549B355C-16D6-E511-96A2-008CFA002028.root',
       '/store/mc/RunIIFall15MiniAODv2/RSGravToZZToZZinv_narrow_M-1600_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/40000/D2FE7458-1CD6-E511-AE01-02163E0168CF.root' ] );


secFiles.extend( [
               ] )

