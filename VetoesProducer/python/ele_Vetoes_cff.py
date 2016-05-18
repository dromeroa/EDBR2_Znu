

import FWCore.ParameterSet.Config as cms

### The pt and eta cuts are based on https://indico.cern.ch/event/370507/contribution/1/attachments/1140657/1633761/Rami_eleCB_ID_25ns.pdf

goodElectrons = cms.EDFilter("PATElectronRefSelector",
                               src = cms.InputTag("slimmedElectrons"),
                               cut = cms.string("pt > 20 & abs(eta) < 2.5"),
                               filter = cms.bool(False))



electronsVetoProdCUTBASED = cms.EDProducer("PatElectronSelectorByValueMap",
                               input     = cms.InputTag("goodElectrons"),
                               cut       = cms.string(""),
                               selection = cms.InputTag("egmGsfElectronIDs:cutBasedElectronID-Spring15-25ns-V1-standalone-veto"),
                               id_cut    = cms.bool(True))


### For CUTBASED we have the veto
electronVetoCUTBASED = cms.EDFilter("PATCandViewCountFilter",
                             minNumber = cms.uint32(0),
                             maxNumber = cms.uint32(0),
                             src = cms.InputTag("electronsVetoProdCUTBASED"))


elevetoCUTBASEDSequence = cms.Sequence(   goodElectrons                          *
                                          electronsVetoProdCUTBASED              *
                                          electronVetoCUTBASED                   )


VETOSelectEvents = cms.Sequence(elevetoCUTBASEDSequence)
