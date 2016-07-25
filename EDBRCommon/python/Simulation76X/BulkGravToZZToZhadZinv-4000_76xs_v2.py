import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/10416D9A-8D27-E611-A76A-44A842CFD5CB.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/2EEBE2C2-D226-E611-9336-003048322CAB.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/8C1BE63A-D925-E611-BE65-14187733AD81.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/A40363B1-E025-E611-B719-6C3BE5B50180.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/C42A5174-B526-E611-9D61-1418774108DF.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/C4C6AF4B-9727-E611-A2C4-0CC47A57CBBC.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4000_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/F612FF32-9727-E611-91FB-44A842CF060D.root' ] );


secFiles.extend( [
               ] )
