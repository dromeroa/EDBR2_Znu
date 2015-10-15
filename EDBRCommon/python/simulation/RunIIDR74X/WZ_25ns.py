import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/0CB35A03-1E06-E511-A0D0-0CC47A13D2BE.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/16C10C6A-6907-E511-9957-0025901AEBD8.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/3008527F-8606-E511-99EA-0002C94D575E.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/4616C3E3-1906-E511-A643-002590E2F9D4.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/4AC7049E-1707-E511-84D5-0025905A48F2.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/4E55877A-5406-E511-A328-002590D9D8A4.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/6A838C08-F406-E511-A5A6-0025901D08EA.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/B273A3F7-8306-E511-8BF3-0002C94D5612.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/BACDDDF7-1906-E511-8E8C-0CC47A13D2BE.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/00000/DA2F33AF-4708-E511-9984-A0040420FE80.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/0EA5CF2F-1A06-E511-82CF-002590D9D9F6.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/18CBBAB3-AD05-E511-9171-0CC47A13CB36.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/28327590-8006-E511-B844-00238BAA1C4A.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/2AAACAEC-8606-E511-8F15-00259073E3FC.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/2C2687D0-AA05-E511-B941-A0040420FE80.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/2E4D3E63-1906-E511-A8C4-0CC47A0AD6F8.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/3EB756A4-AA05-E511-A06A-0025900E3508.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/44CC27C7-AA05-E511-BEE4-A0040420FE80.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/4A356134-CC05-E511-AD9C-008CFA064858.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/4C103433-4E07-E511-A2A0-B083FED73FEC.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/501D689D-AA05-E511-A54A-0CC47A13CEAC.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/52BC606A-6606-E511-8509-6CC2173D57C0.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/58F8AABD-AA05-E511-A012-0025904A8ED2.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/5E7E951F-7C06-E511-9768-002590D8C71A.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/60A678D4-AB05-E511-AA44-00259077501E.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/6E7618ED-E705-E511-9DAC-842B2B76653D.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/709A26D5-1B06-E511-816A-0CC47A0AD668.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/76AB2A80-D706-E511-AA56-002590AC4B5A.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/7CD3F556-BB07-E511-85AB-002590A370DC.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/8A6E0BF5-AB05-E511-ABD1-0CC47A13CB36.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/963E8A98-AD05-E511-ADA7-00304865C244.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/A0A3EEAA-1607-E511-A4D9-1CC1DE19285A.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/A2015043-B405-E511-AC68-00304865C2D0.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/A487E395-8B06-E511-8E37-F45214C7B6BA.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/A4FE1036-B506-E511-A809-AC853D9DAC41.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/AA6933F3-AB05-E511-A25E-002590EFF972.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/B0D8955F-7B06-E511-A3AD-0022195E1F5E.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/B2852018-B606-E511-A3D8-AC853D9DACE1.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/C2C72800-AC05-E511-88E6-0025902D944E.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/CC2E2F4C-1A06-E511-8FB7-002590D9D98E.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/D2999A21-0406-E511-8536-FA163EC78E1E.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/E4FAFEE2-9706-E511-818B-6C3BE5B59058.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/EE7A8ED9-AB05-E511-98BA-F45214C7B6BA.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/FAE8A475-7D07-E511-9A84-0025901D5CDA.root',
       '/store/mc/RunIISpring15DR74/WZ_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/60000/FC8A9C58-6406-E511-B28D-001EC9EAF8B2.root' ] );


secFiles.extend( [
               ] )


