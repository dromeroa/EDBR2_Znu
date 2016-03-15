###**********************************
###***********  FOR 25 NS  *********
###*********************************


import FWCore.ParameterSet.Config as cms

goodElectrons = cms.EDFilter("PATElectronRefSelector",
                               src = cms.InputTag("slimmedElectrons"),
                               cut = cms.string("pt > 20 & abs(eta) < 2.5"),
                               filter = cms.bool(False)
)
### The pt and eta cuts are based on https://indico.cern.ch/event/370507/contribution/1/attachments/1140657/1633761/Rami_eleCB_ID_25ns.pdf

### Based on HEEPID, for now we can use this for 25ns, be alert for new HEEPID 6.1 
electronsVetoProdHEEP = cms.EDProducer("PatElectronSelectorByValueMap",
                               input     = cms.InputTag("goodElectrons"),
                               cut       = cms.string(""),
                               selection = cms.InputTag("egmGsfElectronIDs:heepElectronID-HEEPV60"),
                               id_cut    = cms.bool(True)
)

electronsVetoProdCUTBASED = cms.EDProducer("PatElectronSelectorByValueMap",
                               input     = cms.InputTag("goodElectrons"),
                               cut       = cms.string(""),
                               selection = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-veto"),
                               id_cut    = cms.bool(True)
)

### For HEEP, if we found and electron, we veto the event
electronVetoHEEP = cms.EDFilter("PATCandViewCountFilter",
                             minNumber = cms.uint32(0),
                             maxNumber = cms.uint32(0),
                             src = cms.InputTag("electronsVetoProdHEEP")
)

### For CUTBASED we have the veto
electronVetoCUTBASED = cms.EDFilter("PATCandViewCountFilter",
                             minNumber = cms.uint32(0),
                             maxNumber = cms.uint32(0),
                             src = cms.InputTag("electronsVetoProdCUTBASED")
)


### We will try to combine boths ID with an "OR"


elevetoHEEPSequence = cms.Sequence(       goodElectrons                          *
                                          electronsVetoProdHEEP                  *
                                          electronVetoHEEP                       )

elevetoCUTBASEDSequence = cms.Sequence(   goodElectrons                          *
                                          electronsVetoProdCUTBASED              *
                                          electronVetoCUTBASED                   )




#VETOSelectEvents = cms.Sequence(elevetoHEEPSequence   elevetoCUTBASEDSequence) 

VETOSelectEvents = cms.Sequence(elevetoCUTBASEDSequence)
