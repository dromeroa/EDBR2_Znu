from CRABClient.UserUtilities import config
config = config()
config.General.transferOutputs = True
config.General.transferLogs = True

config.General.requestName = 'EDBR_MET_2015D_25ns_prmpt_v4'

config.General.workArea = 'EDBR_crab_projects'

config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'analysis-MET_Run2015D_25ns_13Ene_v4_BASELINE.py'



config.section_('Data')
config.Data.inputDataset= '/MET/Run2015D-PromptReco-v4/MINIAOD'
config.Data.unitsPerJob = 200
config.Data.splitting = 'LumiBased'
config.Data.lumiMask = "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions15/13TeV/Cert_246908-260627_13TeV_PromptReco_Collisions15_25ns_JSON.txt"
config.Data.publication = False
config.Data.useParent = False


config.Data.publication = False
## User options
config.section_("User")
#config.User.email = 'dromeroa@cern.ch'
## Site options
config.section_("Site")
config.Site.storageSite = 'T2_BR_SPRACE'
