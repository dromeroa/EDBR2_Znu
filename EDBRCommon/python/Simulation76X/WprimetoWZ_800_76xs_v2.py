import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/221F443D-38C3-E511-9988-FACADE0000F3.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/240A983D-38C3-E511-91BC-5065F3818261.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/3C91FDBA-38C3-E511-AA2C-002590D4FBA4.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/06FAF5AF-AEC3-E511-8942-44A842CFC9E6.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/18F35716-AEC3-E511-B835-00266CF9BEE4.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/32D207C2-AEC3-E511-BBE0-002590DB040C.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/3C2E8BB3-B0C3-E511-B47D-90B11C443C96.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/488EA7C8-AEC3-E511-9D8B-002590D9D9DA.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/4CDA57BC-B0C3-E511-80A3-F01FAFD8ED06.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/9E0D8ABB-AEC3-E511-8D02-001E681E0F9E.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/ACB4D5BA-AEC3-E511-9BD5-7845C4FC3C86.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/B2DFE0BA-AEC3-E511-8DFA-008CFA1111F4.root',
       '/store/mc/RunIIFall15MiniAODv2/WprimeToWZ_width0p1_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/BCC09CB7-B0C3-E511-A86F-00259073E512.root' ] );


secFiles.extend( [
               ] )

