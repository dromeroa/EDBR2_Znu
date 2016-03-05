import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/04A66FE4-47B9-E511-85C6-002590DB9216.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/06301EE1-47B9-E511-8188-E41D2D08DE60.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/14F2624B-46B9-E511-8A9D-A4BADB45B97D.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/1CB099E3-47B9-E511-9671-002590DB91BE.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/1E62868A-46B9-E511-BE86-0025907DCA72.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/2237C9BD-47B9-E511-866F-0025904B232E.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/2808C686-46B9-E511-A3BA-0025907FD2DC.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/38A9AAE0-47B9-E511-8A37-F45214939090.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/3C740B2B-46B9-E511-B88D-047D7B881D90.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/4287BC8D-46B9-E511-A392-0025904A862C.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/44CCFC42-46B9-E511-8286-D8D385FF3201.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/48B4B6E1-47B9-E511-A124-E41D2D08DEE0.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/4E150B91-46B9-E511-B690-0025904B8934.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/4E95DB8B-46B9-E511-82C5-001E67398CA0.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/4EFCABE4-47B9-E511-A94F-002590A2CCE6.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/62DBE0B8-46B9-E511-90B1-0025904C66EC.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/6656C2E3-47B9-E511-9EF2-002590AC4C6C.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/6CCE1B90-46B9-E511-AB70-003048C5745C.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/6E1E5E97-46B9-E511-B959-00266CFFA418.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/88AEEB83-45B9-E511-A3F5-6CC2173D44D0.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/8A10258B-46B9-E511-827F-002590AC501A.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/8E50229A-46B9-E511-ABF9-00259081ED06.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/96E85887-46B9-E511-89CB-002590AC501A.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/980F45E4-47B9-E511-A073-047D7B881D90.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/9A7ECF85-46B9-E511-9F05-FACADE0000B5.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/9C60DF82-46B9-E511-978A-002590AC4C56.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/A4B936E2-47B9-E511-8684-002590AC539E.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/A8BCDB7D-46B9-E511-8B13-002618943860.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/AABEE385-46B9-E511-8B71-FACADE0000B5.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/AE0EB6E5-47B9-E511-8011-FACADE00016A.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/B666E9ED-47B9-E511-997D-E41D2D08E0A0.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/B69D5FE6-47B9-E511-89CD-E41D2D08DF50.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/B82223E2-47B9-E511-81E8-002590AC4C72.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/B855F88A-46B9-E511-AD22-0025907DCA72.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/B8625788-46B9-E511-B001-FACADE0000D3.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/B8D73F94-46B9-E511-9933-0025904B23B8.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/BADC530B-46B9-E511-84AB-7845C4FC362F.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/C060E887-46B9-E511-82B3-00266CFE7ADC.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/C6CD95B8-45B9-E511-A12B-141877411FED.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/CC6B8D94-46B9-E511-9B66-002590821170.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/CEC798B3-45B9-E511-BE0F-842B2B765E01.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/D2047086-46B9-E511-89CB-FACADE0000B5.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/D2558796-46B9-E511-B8B4-001DD8B71DB6.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/D8AE9A92-46B9-E511-9434-001DD8B71DB6.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/DA808588-46B9-E511-B9C3-FACADE0000D3.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/DCA92C94-45B9-E511-805C-0CC47A4D9A4A.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/DE7DE1E3-47B9-E511-B3D7-002590AC4C6E.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/E0A52D83-46B9-E511-8D83-002590AC4C56.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/E8354A88-46B9-E511-88B1-0025907DC9BE.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/E888088B-46B9-E511-B1BF-002590A2CD44.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/EA1FF6E4-47B9-E511-B35F-0025907FD24A.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/F0B26DA4-45B9-E511-852F-24BE05C3FBB1.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/10000/FA03AFE2-47B9-E511-A9FD-047D7B881D6A.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/0C17B49C-40B9-E511-999D-0025905C6448.root',
       '/store/mc/RunIIFall15MiniAODv2/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/PU25nsData2015v1_76X_mcRun2_asymptotic_v12-v1/70000/7440FFD1-38B9-E511-A330-FACADE0000C2.root' ] );


secFiles.extend( [
               ] )



