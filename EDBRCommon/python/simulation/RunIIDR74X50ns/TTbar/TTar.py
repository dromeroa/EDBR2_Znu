import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/94BC39DE-7710-E511-823E-0025905B860C.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/9600449D-6E0F-E511-8CDB-20CF305616E2.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/9652EFEB-310F-E511-9554-3417EBE64BA3.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/9A0E62C2-780F-E511-BEED-002590AC4C48.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/9A44B3D5-5B0F-E511-8BFD-B8CA3A708F98.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/9A83FAB0-540F-E511-91A3-00074305CDD2.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/9C5ADA4A-890F-E511-8F25-20CF305B056C.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/9CE2C479-420F-E511-B089-00304865C254.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/9E2F7D61-530F-E511-BE56-0002C90F8054.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/9EDE1012-7810-E511-8ACC-0025905B860C.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/9EEF8676-0F10-E511-BD9D-00259073E4E4.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/9EF73AB6-4B0F-E511-8928-002590DB925E.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/A07CEACB-7110-E511-AAC9-0025905B85E8.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/A09808B9-780F-E511-8891-0002C94CDA06.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/A0A9361F-3710-E511-9A33-20CF3027A560.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/A0CD167E-E80F-E511-A416-3417EBE2F445.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/A2A85A90-420F-E511-B76D-0025B3E05BBE.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/A2CFF69C-680F-E511-81AE-20CF305B056C.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/A2F27C87-E80F-E511-9297-3417EBE644D1.root',
       '/store/mc/RunIISpring15DR74/TT_TuneCUETP8M1_13TeV-powheg-pythia8/MINIAODSIM/Asympt50ns_MCRUN2_74_V9A-v4/60000/A6083985-560F-E511-91BC-0CC47A4DEDF6.root' ] );
