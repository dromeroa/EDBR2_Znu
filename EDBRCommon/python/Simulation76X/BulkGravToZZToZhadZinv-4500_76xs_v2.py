import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/00BAEB5E-CF2A-E611-8AB7-AC853D9DACD3.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/363E03F4-0D2B-E611-8C48-0025905B855E.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/60356C6A-0D2B-E611-84FF-90B11C27E5BE.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/64C0D98E-4C2A-E611-BE1F-0CC47A4D7670.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/8466766F-0D2B-E611-BDE3-B499BAAC02CA.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/8A471ABA-4C2A-E611-B736-001CC4A61C52.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/CC3C806F-0D2B-E611-AA4A-008CFA05E874.root',
       '/store/mc/RunIIFall15MiniAODv2/BulkGravToZZToZhadZinv_narrow_M-4500_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/CED1D4FC-C62A-E611-9FA9-001EC94BF999.root' ] );


secFiles.extend( [
               ] )
