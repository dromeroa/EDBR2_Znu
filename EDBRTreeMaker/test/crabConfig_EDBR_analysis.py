from CRABClient.UserUtilities import config
config = config()

config.General.transferOutputs = True

## General options

config.General.requestName = 'EDBR_ZJetsToNuNu_HT-100To200_25ns'
#config.General.requestName = 'EDBR_ZJetsToNuNu_HT-200To400_25ns'
#config.General.requestName = 'EDBR_ZJetsToNuNu_HT-400To600_25ns'
#config.General.requestName = 'EDBR_ZJetsToNuNu_HT-600ToInf_25ns'
#config.General.requestName = 'EDBR_WJetsToLNu_25ns'
#config.General.requestName = 'EDBR_WJetsToLNu_total'
#config.General.requestName = 'QCD_3200toInf_50ns'
#config.General.requestName = 'QCD_2400to3200_50ns'
#config.General.requestName = 'QCD_1800to2400_50ns'
#config.General.requestName = 'QCD_1400to1800_50ns'
#config.General.requestName = 'QCD_1000to1400_50ns'
#config.General.requestName = 'QCD_800to1000_50ns'
#config.General.requestName = 'QCD_600to8000_50ns'
#config.General.requestName = 'QCD_470to600_50ns'
#config.General.requestName = 'QCD_300to470_50ns'

config.General.workArea = 'EDBR_crab_projects'

# Job Type options
# esta opcion es para que soporte EventBased
#config.JobType.pluginName = 'PrivateMC'
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'analysis_25ns.py'
#config.JobType.inputFiles = ['Summer15_50nsV5_MC_L2Relative_AK8PFchs.txt', 'Summer15_50nsV5_MC_L3Absolute_AK8PFchs.txt']

## Data options
#config.Data.inputDataset ='/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM'
#config.Data.inputDataset ='/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM'
#config.Data.inputDataset ='/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM'
#config.Data.inputDataset ='/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM'
#config.Data.inputDataset ='/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM'
## QCD
#config.Data.inputDataset ='/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/MINIAODSIM'
#config.Data.inputDataset ='/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM'
#config.Data.inputDataset ='/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/MINIAODSIM'
#config.Data.inputDataset ='/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM'
#config.Data.inputDataset ='/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM'
#config.Data.inputDataset ='/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM'
#config.Data.inputDataset ='/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v2/MINIAODSIM'
#config.Data.inputDataset ='/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/MINIAODSIM'
#config.Data.inputDataset ='/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/MINIAODSIM'
#config.Data.inputDataset ='/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/MINIAODSIM'
#config.Data.inputDataset ='/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/MINIAODSIM'
## W + jets
#config.Data.inputDataset ='/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt50ns_MCRUN2_74_V9A-v1/MINIAODSIM'
## Z +jets
config.Data.inputDataset ='/ZJetsToNuNu_HT-100To200_13TeV-madgraph/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
#config.Data.inputDataset ='/ZJetsToNuNu_HT-200To400_13TeV-madgraph/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
#config.Data.inputDataset ='/ZJetsToNuNu_HT-400To600_13TeV-madgraph/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
#config.Data.inputDataset ='/ZJetsToNuNu_HT-600ToInf_13TeV-madgraph/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM'
#config.Data.inputDataset ='/WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8/RunIISpring15DR74-Asympt25ns_MCRUN2_74_V9-v1/MINIAODSIM' 

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

