import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-2000_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/2A2868B6-3608-E511-8652-A0040420FE80.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-2000_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/3443F39C-4508-E511-B6DB-0025905A60EE.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-2000_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/42514BAF-4608-E511-B581-002590775158.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-2000_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/488816B7-4508-E511-9CAD-A0040420FE80.root',
       '/store/mc/RunIISpring15DR74/RSGravToZZ_kMpl01_M-2000_TuneCUETP8M1_13TeV-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/A02BD19C-4508-E511-AB49-0025905AA9CC.root' ] );


secFiles.extend( [
               ] )

