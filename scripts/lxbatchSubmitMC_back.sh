#!/bin/bash 
#
# Submit jobs to lxbatch. More info at https://twiki.cern.ch/twiki/bin/view/Main/BatchJobs
#
# Usage: 
#
#         1) Request a valid proxy
#            voms-proxy-init --voms cms -valid 168:00
#         
#         2) Copy proxy to your home
#            cp /tmp/x509up_u47670 $HOME
#
#         3) Submission example to the 1 day queue with a 10MB memory limit 
#            bsub -q 2nd -M 100000 -J Zjets100 < lxbatchSubmitMC_back.sh 

export X509_USER_PROXY=/afs/cern.ch/user/d/dromeroa/x509up_u47670
cd /afs/cern.ch/work/d/dromeroa/private/EDBR2_PILEUP_Oct11/CMSSW_7_4_14/src/ExoDiBosonResonances/EDBRTreeMaker/backgrounds
eval `scramv1 runtime -sh`

#cmsRun analysis2015D_25ns_RSG_M2000.py
#cmsRun  analysis2015D_25ns_Zjets_HT100To200.py
#cmsRun analysis2015D_25ns_Zjets_HT200To400.py
#cmsRun analysis2015D_25ns_Zjets_HT400To600.py
#cmsRun analysis2015D_25ns_Zjets_HT600ToInf.py
#cmsRun  analysis2015D_25ns_Wjets_HT100To200.py
#cmsRun analysis2015D_25ns_Wjets_HT200To400.py
#cmsRun analysis2015D_25ns_Wjets_HT400To600.py
#cmsRun analysis2015D_25ns_Wjets_HT600ToInf.py
#cmsRun analysis2015D_25ns_TTjets_powheg.py
#cmsRun analysis2015D_25ns_WW.py
#cmsRun analysis2015D_25ns_ZZ.py
#cmsRun analysis2015D_25ns_WZ.py
#cmsRun analysis2015D_25ns_QCD_HT100to200.py
#cmsRun analysis2015D_25ns_QCD_HT200to300.py
cmsRun analysis2015D_25ns_QCD_HT300to500.py
#cmsRun analysis2015D_25ns_QCD_HT500to700.py
#cmsRun analysis2015D_25ns_QCD_HT700to1000.py
#cmsRun analysis2015D_25ns_QCD_HT1000to1500.py
#cmsRun analysis2015D_25ns_QCD_HT1500to2000.py
#cmsRun analysis2015D_25ns_QCD_HT2000toInf.py
