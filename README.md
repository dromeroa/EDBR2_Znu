Instructions to setup the ExoDiBosonResonances code
========

```
cmsrel CMSSW_7_6_5
cd CMSSW_7_6_5/src
cmsenv
git cms-init # This will allow you to checkout packages in official CMSSW
git clone -b 76X git@github.com:dromeroa/EDBR2_Znu.git ExoDiBosonResonances
scram b -j 10
```

