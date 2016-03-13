import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/data/Run2015C_25ns/MET/MINIAOD/16Dec2015-v1/70000/321E212A-E3AD-E511-9A30-002590D0AFFC.root',
       '/store/data/Run2015C_25ns/MET/MINIAOD/16Dec2015-v1/70000/701429F7-E3AD-E511-A858-0CC47A4D75EC.root',
       '/store/data/Run2015C_25ns/MET/MINIAOD/16Dec2015-v1/70000/AEDB4CF6-E3AD-E511-A9E6-008CFA002FF4.root',
       '/store/data/Run2015C_25ns/MET/MINIAOD/16Dec2015-v1/70000/DC970305-E4AD-E511-A98D-0CC47A4D7616.root',
       '/store/data/Run2015C_25ns/MET/MINIAOD/16Dec2015-v1/70000/EE6878F3-E3AD-E511-841F-0025904C66A4.root' ] );


secFiles.extend( [
               ] )



