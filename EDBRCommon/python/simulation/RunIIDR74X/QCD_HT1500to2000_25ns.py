import FWCore.ParameterSet.Config as cms

maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/00E595C3-3324-E511-917A-20CF3027A5EC.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/0690329C-8722-E511-B7C5-20CF305B0581.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/10B96A58-BF22-E511-88B4-001E67A3EC00.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/180040AC-8723-E511-8F31-001517FB0F60.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/189B966E-5123-E511-B963-D485645943AC.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/20267B3B-2524-E511-BB04-002590207C28.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/7AF99AF0-8D22-E511-87FA-00259073E4DA.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/84D12272-9822-E511-ABE4-00259073E324.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/A6653BE8-5C23-E511-A727-00259073E464.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/B6A371BD-9022-E511-8C67-00259073E32A.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/CEC6A6FF-9222-E511-9E60-0CC47A4DEE04.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/20000/F06A4ED4-7624-E511-B29A-90B11C08AD92.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/0288B7C7-2724-E511-B5BB-00259073E34A.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/0438504F-FA24-E511-BB29-001E67A3ED40.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/0E8DB8AD-9022-E511-A348-00259074AE98.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/1286C111-FC24-E511-B6B0-D4AE529D9537.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/161103B3-C525-E511-A169-001E675A67BB.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/26F1A917-CD22-E511-A431-02163E00EB04.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/2CAB9977-8B22-E511-B6AC-00259073E36E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/30C840C4-0223-E511-8E04-02163E0145B2.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/3290404E-8A24-E511-8DBE-003048D15E0E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/36858B67-8922-E511-8176-00259074AEA6.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/464CA887-BF23-E511-B5BD-00259073E52A.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/4A258348-FA24-E511-944E-D4AE529D9537.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/66A60655-DD23-E511-BFD2-02163E00E867.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/68CEA074-8222-E511-AAD4-00259073E4B8.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/6C82E1DB-CF24-E511-8505-001E67A404B0.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/7269A519-7F22-E511-9533-00259073E34C.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/7EBBF5D5-F522-E511-91E2-00259057492E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/80F26C4D-8B24-E511-B74F-00261894388F.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/8C7F458D-CF24-E511-BA90-001E675A67BB.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/8CB26FC6-E423-E511-BA99-0025904C51FC.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/A0457371-5323-E511-ACD6-00259073E442.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/A8BA284C-8B24-E511-93CA-0025905A607E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/AE770E31-8722-E511-8CFD-0CC47A4128F8.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/BEE08650-8022-E511-885E-0CC47A4DEE68.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/DA3D4D50-8A24-E511-A15D-0025905AA9CC.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/DA582931-E924-E511-B55C-02163E00E724.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/DC5A7549-5325-E511-8D54-0025905A6132.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/F61C2D6F-8D22-E511-A6AB-0CC47A4DEE00.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/30000/FEB544C6-7822-E511-91E5-002590747D90.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/042583E1-7222-E511-BAB9-0CC47A4DEE50.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/0A29FD11-1C24-E511-BF3B-0026B94DBDBC.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/0A339675-AD22-E511-9FE0-00259073E522.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/10C074D0-7123-E511-9551-02163E016B55.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/14F0B34B-7522-E511-9FB3-0CC47A4D9A1E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/16B68F5A-BB24-E511-A308-003048FF86CA.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/16C1D8AB-CC22-E511-B5B8-02163E00E9D4.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/1AE894B3-0E24-E511-BB3C-549F35AD8B6E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/1C933C05-A622-E511-A661-02163E00C572.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/1CD49D0C-6A23-E511-AE93-0025904B7C26.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/2098CB6E-7024-E511-BBD9-20CF3027A5FB.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/244BE434-6E22-E511-8410-00259073E37C.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/30B4230C-7E22-E511-8E8E-20CF3027A57B.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/30BEF3A3-AC22-E511-B23F-002590747E14.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/327A1217-7B22-E511-B02E-0CC47A4DEF68.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/3623B4D1-1A24-E511-BF47-C4346BC8E730.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/42D4CFED-8122-E511-8C8A-002590747D92.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/445D2ABB-6725-E511-BC0A-90B11C05054D.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/4A2BA000-DB22-E511-954A-00266CF9AD60.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/541E7238-8625-E511-B57B-00261894388B.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/5AD468ED-A322-E511-8A71-0025905C2CE6.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/5ECAE568-6825-E511-9FEA-001E675A69DC.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/6072935D-C323-E511-9019-E41D2D08DFF0.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/6468C968-8922-E511-B035-00259073E500.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/68C81BDA-7F22-E511-A1D6-0CC47A4DEE5A.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/6A073A61-9422-E511-B5E7-00259073E41E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/6ACC12C0-6725-E511-80A8-001E67A3EA11.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/6AF4B5F4-9B23-E511-AD72-00259073E4F4.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/6E9F4744-4D23-E511-92AC-001EC9ED88D0.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/7A9C19FE-7722-E511-938D-00259073E32A.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/7C8EC67A-BE22-E511-82B9-02163E010D70.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/808ED594-2E26-E511-B029-001E675A6D10.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/82E25D7C-A822-E511-B798-0025907276DA.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/84DE62A1-2A23-E511-A301-00266CFF0840.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/866AECD2-DC22-E511-94FE-3417EBE6449E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/8A13E3D6-7622-E511-A169-0CC47A4DEE50.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/8EB6D41B-8522-E511-8850-00259073E47E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/90449C48-D822-E511-AAF8-3417EBE64C09.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/9470FAC3-A122-E511-881E-0025905C42B6.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/9A013624-8322-E511-98FC-00259074AED2.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/9E8FB758-BB24-E511-99CE-002618943975.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/9EA5ACB9-A622-E511-846B-B083FECFC6ED.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/A0EBB945-3C24-E511-9327-02163E015154.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/A6D51667-8922-E511-9215-00259073E390.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/B4AC7B32-8D22-E511-B04E-00259073E45E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/B6ACEAA3-B422-E511-9776-002590D600B6.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/C01E409E-E322-E511-97B2-002590D6012E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/C42DD074-8322-E511-990F-0CC47A4DED22.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/C64B302B-DE22-E511-BA7F-00A0D1EEF5B4.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/D464C13E-A922-E511-B7DD-D48564593FAC.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/D627D1A8-8D22-E511-91D4-00259074AE80.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/DC8AC0EE-8225-E511-9FE7-0026189438C0.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/E0815200-7922-E511-ADCB-0CC47A4DEE50.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/E2C215A5-FF22-E511-8271-02163E0133CA.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/E2DAD1A3-9F23-E511-99D3-3417EBE65E39.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/E6783E8C-D622-E511-A40B-00A0D1EE89E0.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/E814D861-C323-E511-BC5E-002590AC4C3E.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/EEA94A00-4924-E511-A3DE-00259073E4CE.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/F400460C-7C23-E511-89A5-0CC47A4D99EE.root',
       '/store/mc/RunIISpring15DR74/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/MINIAODSIM/Asympt25ns_MCRUN2_74_V9-v1/50000/F868E968-8922-E511-B29D-00259073E37C.root' ] );


secFiles.extend( [
               ] )


