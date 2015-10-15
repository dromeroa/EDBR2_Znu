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
#            bsub -q 1nd -M 10000 -J job1 < lxbatchSubmit.sh
#
#         4) For a la large sample 
#            bsub -q 2nd -M 50000 -J job2 < lxbatchSubmit.sh

export X509_USER_PROXY=/afs/cern.ch/user/d/dromeroa/x509up_u47670
cd /afs/cern.ch/work/d/dromeroa/private/EDBR2_PILEUP_Oct11/CMSSW_7_4_14/src/ExoDiBosonResonances/EDBRTreeMaker/data

eval `scramv1 runtime -sh`

cmsRun analysis-MET_Run2015D_25ns_v4.py
