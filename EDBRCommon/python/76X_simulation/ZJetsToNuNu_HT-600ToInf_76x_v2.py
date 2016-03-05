import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/06CB5FB9-87BF-E511-8B74-78E7D12226B8.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/0A23F9B9-87BF-E511-8ADD-78E7D1239AB8.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/0E767B28-95BF-E511-9B5C-0CC47A78A426.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/204F2066-86BF-E511-B303-78E7D12395E8.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/20C17EEE-87BF-E511-938F-78E7D12395E8.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/28C7AE2A-95BF-E511-B466-0CC47A78A32E.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/3679209C-97BF-E511-AB92-0CC47A78A4A0.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/3AAC3519-97BF-E511-84A6-0CC47A4D7640.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/3EE864B9-87BF-E511-A920-78E7D12226B8.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/4E228942-86BF-E511-8860-78E7D123A0E0.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/4E4A6B29-95BF-E511-B5EF-0CC47A78A426.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/4EDDE7B8-87BF-E511-B34F-78E7D1238168.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/60428EB9-87BF-E511-82C0-78E7D123C768.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/7A474AA3-86BF-E511-9957-78E7D12226B8.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/82FEEB9A-97BF-E511-A6BC-0CC47A4D769C.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/94A35A11-97BF-E511-9490-002590593902.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/AE6CE47C-87BF-E511-AC91-78E7D12501E8.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/BEFE7B1A-97BF-E511-8F5F-0025905964C2.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/CE02CE7E-86BF-E511-8531-441EA1390CE0.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/D2442099-97BF-E511-A3FC-0CC47A4C8F26.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/DCAB400E-87BF-E511-8A70-78E7D122B9C8.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/F0725FB9-87BF-E511-858F-78E7D12226B8.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/FCCFC626-95BF-E511-AEEF-002618943947.root',
       '/store/mc/RunIIFall15MiniAODv2/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/20000/FCDE8526-95BF-E511-8A1B-002618943875.root' ] );


secFiles.extend( [
               ] )



