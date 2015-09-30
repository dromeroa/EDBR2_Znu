import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/00733350-F72A-E511-A7AC-0026189437FD.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/0285050B-2A2A-E511-A448-20CF3027A561.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/0A6243E7-012B-E511-843C-0025905A6136.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/0ECCB5A6-582F-E511-BD43-00259075D714.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/1436890B-0F2B-E511-BFDC-008CFA00F690.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/162B24BE-C82C-E511-B1B9-001E67504D15.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/180A6686-582F-E511-A9BC-0025907E35AA.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/18BE589D-182A-E511-B736-00259073E36C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/1AE57882-582F-E511-B1A0-00266CFFBCDC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/202BD3AE-582F-E511-9682-D8D385FF4ABA.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/246BE8B4-582F-E511-94A2-00259029ED64.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/2A3E7C0A-4828-E511-8B34-001517FB20EC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/2CF1EB42-BE2C-E511-8373-B083FED7477A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/30626892-3E2A-E511-B977-D4AE527F338C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/30C982D6-3C2A-E511-9A5B-00215AEDFD12.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/32D172BB-4A2E-E511-9D07-00266CF9BCAC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/32D658FF-DD2A-E511-9016-00259074AEAE.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/44BC969B-F72A-E511-87FD-0025905B85EE.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/48787170-292A-E511-8ECD-0025905C3E36.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/48ECEC00-602D-E511-9F83-00261894386B.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/4AA5D910-1E2B-E511-A9E3-00266CFCCB44.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/507D0280-582F-E511-9C94-0025907D250E.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/52993AF6-4728-E511-8065-0025905C975C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/5A4CFF90-582F-E511-A701-002590D9D8BE.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/608C11B3-DA2D-E511-B3F2-0025907B4F04.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/60DEB5A6-582F-E511-A200-00259075D714.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/648413AB-DA2D-E511-8DAA-D48564593FA8.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/6AAFAEC7-3B2A-E511-8D6C-008CFA1660F8.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/6C2C2142-F72A-E511-B0E8-0025905A606A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/6EF46C80-582F-E511-859A-0CC47A0AD4A4.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/72FD34F5-4728-E511-A2E1-0025905C2CD0.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/76100A19-362A-E511-905F-002481DE4AA6.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/76E52178-582F-E511-81D4-00304865C31C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/78572B78-582F-E511-AA09-90B11C26815F.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/7C08A3F8-322A-E511-8CF7-002481DE47D0.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/7CC6777C-582F-E511-BFE6-0025901AC0FC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/7E6C6E79-582F-E511-934A-0025901AC0FA.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/803DEA62-012B-E511-9D5B-0025905B8562.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/828FFB88-582F-E511-8A17-002590D9D968.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/8ABE5DDF-182A-E511-9311-002590D8C7FA.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/8E14C03D-DC2D-E511-B183-00259074AE5E.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/8E158DDC-3B2A-E511-B3B6-008CFA14FA8C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/92AF143C-F42D-E511-808C-001EC9ADC460.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/9433237F-0B2B-E511-A4B3-0023AEEEB799.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/946E8336-752D-E511-813E-002481E0DE08.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/948FA505-F72A-E511-AB94-0025905A48EC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/A0791F40-392A-E511-A3B1-E41D2D08E050.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/A65F73B2-182A-E511-8708-20CF3027A61A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/A8C14D97-182A-E511-B122-002590743042.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/AC8FF0ED-512F-E511-A458-20CF3027A561.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/B03D36C8-102B-E511-BC87-B083FED42A6E.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/B0D229CD-DA2D-E511-AC0F-002590D60036.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/B4BB1A8E-582F-E511-807A-002590D9D96E.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/BCDB9DEA-132B-E511-81B0-D4AE526A0B8F.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/BE63668E-3B2B-E511-A489-001517FAD934.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/C06EF291-592F-E511-96A0-008CFA166234.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/C0DD7EAD-DA2D-E511-948C-001E0BC18A56.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/C207598E-1E2B-E511-9367-0002C90F8088.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/C4C7EA8F-0A2B-E511-A716-0025905AA9CC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/C60427C9-F62A-E511-A365-002618943882.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/C655EC91-182A-E511-BC2C-20CF3027A62B.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/C8B87819-592F-E511-B976-001E67A40523.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/CC7CFDCB-182A-E511-B819-00259073E36C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/CCE1DE7C-582F-E511-B2DB-3417EBE885A6.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/CED06686-582F-E511-ABEB-0025907E35AA.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/D0A78AFE-F62A-E511-8BA1-0025905964CC.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/DAA1703D-562A-E511-BC83-6C3BE5B59218.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/DAF16C85-582F-E511-B0B1-0CC47A0AD742.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/DCA6619C-182A-E511-B7D2-002590D60042.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/DE4CEFF8-022B-E511-9907-0025B3E025B6.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/E0086CF4-4728-E511-B29A-0025905C2CB8.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/E0CFAB60-4D28-E511-A12A-0025904C4F9E.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/E24A0C80-582F-E511-BA90-0025907D2430.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/E26C8F1D-152B-E511-9CDD-842B2B76670F.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/E64F5889-2C2A-E511-9FB0-0025905A60D2.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/E6C8EC88-B82C-E511-9299-D4AE526A091F.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/E847EC52-F72A-E511-B961-0025905B85AE.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/E8608292-182A-E511-AE19-20CF3027A5A2.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/EAA0071D-022B-E511-8CB8-0025905B855C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/F0165882-582F-E511-9A45-003048322A7C.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/F41AC906-002B-E511-94F9-000F53273498.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/40000/FCC4A17E-582F-E511-B52F-002590FD5A48.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/0CB29898-F92A-E511-B964-001E4F1BC1D4.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/182D5744-1E2E-E511-8518-D4AE526A0419.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/1895D58E-9828-E511-BBB9-0025905A6082.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/26C68892-9828-E511-9C41-003048FFCB6A.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/C4287FA1-F92A-E511-81A7-001E4F1BC1D4.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/CCEB3022-6F30-E511-BFBA-002590A2CD06.root',
       '/store/mc/RunIISpring15DR74/DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v2/80000/EE6C5924-6F30-E511-A12F-002590AC4B5C.root' ] );


secFiles.extend( [
               ] )
