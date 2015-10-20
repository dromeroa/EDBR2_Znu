
from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True

## General options

#config.General.requestName = 'EDBR_ZJetsToNuNu_HT-100To200_25ns'
#config.General.requestName = 'EDBR_ZJetsToNuNu_HT-200To400_25ns'
#config.General.requestName = 'EDBR_ZJetsToNuNu_HT-400To600_25ns'
#config.General.requestName = 'EDBR_ZJetsToNuNu_HT-600ToInf_25ns'
#config.General.requestName = 'EDBR_WJetsToLNu_HT-100To200_25ns'
#config.General.requestName = 'EDBR_WJetsToLNu_HT-200To400_25ns'
#config.General.requestName = 'EDBR_WJetsToLNu_HT-400To600_25ns'
#config.General.requestName = 'EDBR_WJetsToLNu_HT-600ToInf_25ns'
config.General.requestName = 'EDBR_TTJets_powheg_25ns'
#config.General.requestName = 'EDBR_ZZ_25ns'
#config.General.requestName = 'EDBR_WW_25ns'
#config.General.requestName = 'EDBR_WZ_25ns'

config.General.workArea = 'EDBR_crab_projects'

# Job Type options
# esta opcion es para que soporte EventBased
#config.JobType.pluginName = 'PrivateMC'
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'analysis2015D_25ns_TTJets.py'


## Data options


## Z +jets
#config.Data.inputDataset ='/ZJetsToNuNu_HT-100To200_13TeV-madgraph/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
#config.Data.inputDataset ='/ZJetsToNuNu_HT-200To400_13TeV-madgraph/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
#config.Data.inputDataset ='/ZJetsToNuNu_HT-400To600_13TeV-madgraph/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
#config.Data.inputDataset ='/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'

## W + jets
#config.Data.inputDataset ='/WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
#config.Data.inputDataset ='/WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
#config.Data.inputDataset ='/WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM'
#config.Data.inputDataset ='/WJetsToLNu_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM' 


## TTjets
config.Data.inputDataset ='/TT_TuneCUETP8M1_13TeV-powheg-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v2/MINIAODSIM'

## Dibosons
#config.Data.inputDataset ='/WW_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
#config.Data.inputDataset ='/ZZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v3/MINIAODSIM'
#config.Data.inputDataset ='/WZ_TuneCUETP8M1_13TeV-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'  
 

config.Data.inputDBS = 'global'

# esto es para cuando se tiene mas de un archivo
config.Data.splitting = 'FileBased'

# esto es para dividir por eventos
#config.Data.splitting = 'EventBased'
config.Data.unitsPerJob =1

config.Data.publication = False

## User options
config.section_("User")
#config.User.email = 'dromeroa@cern.ch'

## Site options
config.section_("Site")
config.Site.storageSite = 'T2_BR_SPRACE'
#config.Site.whitelist = ["T2_BR_SPRACE"]
