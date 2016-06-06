
// CHECKING THE CODE
// FIRST TRY FROM 03/04/2016
// FOR ERFEXP IN THE SUBDOMINANT
//
// FROM /afs/cern.ch/work/d/dromeroa/private/ALPHAMETHOD_Enero25/CMSSW_8_0_0_pre5/src/ALPHA_METHOD/TESTNEWCODE
// Do : >cmsenv
// root[] gSystem->Load("../PDFs/HWWLVJRooPdfs_cxx.so")
// root[] .x test01abril.C("HP")

#include "TMath.h"
#include "string.h"

void testyields(std::string key)
{
 
  using namespace RooFit;

//********************************************************************************//
//                                                                                //     
//                                 I. DEFINITIONS                                 //
//                                                                                //     
//********************************************************************************//


  ////*************************************************
  //// 1.  DEFINE THE CONDITIONS
  ////*************************************************
  const bool isBlind = true;
  int plevelnorm = -1;
  int plevelshap = -1;
  int plevelshapDom = -1;
  int plevelshapSubDom = 1;
  // Silent RooFit
  RooMsgService::instance().setGlobalKillBelow(FATAL);
  ////**************************************************


  ////*********************************************************************
  //// 2. INTRODUCE THE VARIABLES
  ////*********************************************************************
  RooRealVar candTMass("candTMass","M_{VZ}",            600.,  3500., "GeV");
  RooRealVar massVhad("massVhad","M_{j}" ,               40.,   220., "GeV");
  RooRealVar tau21("tau21","tau21",                       0.,   1.0        );
  RooRealVar totalWeight("totalWeight", "total weight",  -100.,  100.         );
  RooArgSet variables(candTMass,massVhad,tau21,totalWeight);
  ////**********************************************************************

 
  ////*******************************************
  //// 3. DEFINE THE REGIONS OF THE PRUNED MASS
  ////******************************************* 
  massVhad.setRange("lowerSB",      40.,   65.);
  massVhad.setRange("lowerSIG",     65.,  105.);
  massVhad.setRange("upperSIG",    105.,  135.);
  massVhad.setRange("upperSB",     135.,  220.);
  massVhad.setRange("fullRange",    40.,  220.);
  ////*******************************************

  
  ////*********************************************
  //// 4. DEFINE THE CATEGORIES (tau21)
  ////*********************************************
  std::map<std::string, std::string> selection;
  selection["HP"] = "tau21 < 0.45";
  selection["LP"] = "tau21 > 0.45 && tau21 < 0.75";
  selection["AP"] = "tau21 > 0.75";
  selection["NP"] = "tau21 > 0";
  ////*********************************************

  
  ////****************************************************************
  //// 5. DEFINE THE CUTS OF THE PRUNED MASS AND tau21 TOGETHER (TCut)
  ////****************************************************************
  TCut selectedCategory = selection[key].c_str();
  TCut lowerSIG = "massVhad>65.  && massVhad<105" + selectedCategory;
  TCut upperSIG = "massVhad>105. && massVhad<135" + selectedCategory;
  TCut lowerSB  = "massVhad<65."  + selectedCategory;
  TCut upperSB  = "massVhad>135." + selectedCategory;
  TCut allSB    = lowerSB or upperSB;
  ////***************************************************************


  ////*********************************************
  //// 6. SET THE TITLES FOR DIFFERENT CATEGORIES
  ////*********************************************
  std::map<std::string, std::string> legTitle;
  legTitle["NP"]="NO Purity";
  legTitle["LP"]="Low Purity";
  legTitle["HP"]="High Purity";
  legTitle["AP"]="Anti Purity";
  ////*********************************************


//********************************************************************************//
//                                                                                //     
//                                II. INPUT FILES                                 //
//                                                                                //     
//********************************************************************************//


  ////*********************************************************************************
  ////  7. THE TREES
  ////********************************************************************************* 
  TChain treeData("treeDumper/EDBRCandidates");
  TChain treeMC1( "treeDumper/EDBRCandidates");
  TChain treeMC2( "treeDumper/EDBRCandidates");
  std::map<Int_t, std::string> inputFile;

// check if we need include the QCD samples

      treeData.Add(     "../trees/newtrees/treeEDBR_MET_Run2015C_25ns_16Dec2015_v1.root"         );
      treeData.Add(     "../trees/newtrees/treeEDBR_MET_Run2015D_16Dec2015_v1.root"              );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_QCD_76x_v2.root"                             );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_TTbar_76x_v2.root"                           ); 
//      treeMC2.Add(      "../trees/newtrees/treeEDBR_TTbar_TOTAL_76x_v2.root"                     );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_VV_76x_v2.root"                              );
      treeMC1.Add(      "../trees/newtrees/treeEDBR_W+Jets_76x_v2.root"                          );
      treeMC1.Add(      "../trees/newtrees/treeEDBR_Z+Jets_76x_v2.root"                          );
      ////*******************************************************************************


//********************************************************************************//
//                                                                                //     
//                              III. DATASETS                                     //
//                                                                                //     
//********************************************************************************//


  ////***********************************************************************************
  ////        8. DATASETS TO HOST DATA
  ////***********************************************************************************                       
  std::cout << "Dataset to host sideband data" << std::endl;
  // data in both SB (lower+upper)
  RooDataSet sbObs("sbObs","sbObs", variables, Cut(allSB), Import(treeData)); 
  // data in lower SB
  RooDataSet lsbObs("lsbObs","lsbObs", variables, Cut(lowerSB), Import(treeData));
  // data in upper SB
  RooDataSet usbObs("usbObs","usbObs", variables, Cut(upperSB), Import(treeData)); 
  // data in signal region
  RooDataSet sigObs("sigObs","sigObs", variables, Cut(lowerSIG), Import(treeData));
  // data in upper signal region
  RooDataSet upsigObs("upsigObs","upsigObs", variables, Cut(upperSIG), Import(treeData));
  ////************************************************************************************


  ////********************************************************************************************************
  ////   9.  DATASETS TO HOST MC
  ////********************************************************************************************************                 
  std::cout << "Simulated datasets" << std::endl;
  // Dominant background
  RooDataSet bkg1("bkg1", "bkg1", variables, Cut(selectedCategory), WeightVar("totalWeight"), Import(treeMC1));
  // Subdominant background
  RooDataSet bkg2("bkg2", "bkg2", variables, Cut(selectedCategory), WeightVar("totalWeight"), Import(treeMC2));
  // a variable to store the number of events en each background, with a minimum and maximum value  
  RooRealVar nbkg1("nbkg1","nbkg1",bkg1.sumEntries(),bkg1.sumEntries()/10,bkg1.sumEntries()*10);
  RooRealVar nbkg2("nbkg2","nbkg2",bkg2.sumEntries(),bkg2.sumEntries()/10,bkg1.sumEntries()*10);
  ////***********************************************************************************************************
  
  
  
/////////////////////////////////////////////////////////////////////////////////////
//        _   _                                                                    //
//       | \ | |                          | (_)         | | (_)                    //
//       |  \| | ___  _ __ _ __ ___   __ _| |_ ___  __ _| |_ _  ___  _ __          //
//       | . ` |/ _ \| '__| '_ ` _ \ / _` | | / __|/ _` | __| |/ _ \| '_ \         //
//       | |\  | (_) | |  | | | | | | (_| | | \__ \ (_| | |_| | (_) | | | |        //
//       |_| \_|\___/|_|  |_| |_| |_|\__,_|_|_|___/\__,_|\__|_|\___/|_| |_|        //
//                                                                                 //
/////////////////////////////////////////////////////////////////////////////////////


  ////************************************************************************
  ////  10. THE PDFs 
  ////************************************************************************

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Dominant Background (Error Function * Exponential = ErfExp)
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooRealVar c1("c1","slope of the exp",             -0.032,  -1.,    0.);
  RooRealVar offset1("offset1","offset of the erf",    85.0,   1.,  150.);
  RooRealVar width1("width1",  "width of the erf",     36.0,   1,   100.);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Subdominant Background
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Gaus 2 (gauss1 +gauss2)
  RooRealVar mu1("mu1", "average", 84 , 0., 200);
  RooRealVar sigma1("sigma1", "sigma", 8.7, 0, 100);
  RooRealVar mu2("mu2", "average", 102, 0., 200);
  RooRealVar sigma2("sigma2", "sigma",28 , 0., 100); 
  RooGaussian gauss1("gauss1","gaussian PDF1", massVhad, mu1, sigma1);
  RooGaussian gauss2("gauss2","gaussian PDF2", massVhad, mu2, sigma2);
  RooRealVar funfrac("funfrac","fraction of functions",0.6,0.,1.);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //  THE MODELS
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooErfExpPdf model1("model1","dominant backgrounds",massVhad,c1,offset1,width1);


  RooAddPdf model2("Gaus2", "gaussian plus gaussian", RooArgList(gauss1, gauss2), funfrac);
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


  // A command to add a normalization to the PDF
  RooExtendPdf emodel1("emodel1","extended dom backgrounds",model1,nbkg1);
  RooExtendPdf emodel2("emodel2","extended sub backgrounds",model2,nbkg2);


  // The fit of each background in all range separatly
  std::cout << "Fitting models - normalisation" << std::endl;
//  RooFitResult *rf1 = emodel1.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));
//  RooFitResult *rf2 = emodel2.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,160));
//  RooFitResult *rf2 = emodel2.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));

  RooFitResult *rf1 = model1.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));
//  RooFitResult *rf2 = model2.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,160));
  RooFitResult *rf2 = model2.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
  c1.setConstant(true);
  offset1.setConstant(true);
  width1.setConstant(true);
  mu1.setConstant(true);
  mu2.setConstant(true);
  sigma1.setConstant(true);
  sigma2.setConstant(true);
  funfrac.setConstant(true);
  nbkg1.setConstant(false);
  nbkg2.setConstant(true);



  RooAddPdf model_ext("model_ext","sum of extended models",RooArgList(emodel1,emodel2));
  RooFitResult* erf = model_ext.fitTo(sbObs,Extended(kTRUE),Range("lowerSB,upperSB"),PrintLevel(plevelnorm),Save());
  nbkg1.setConstant(true);


  RooAbsReal* nSIG = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooAbsReal* nSB  = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB"));
  RooAbsReal* nSB2  = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("upperSB"));
  RooAbsReal* nFULL  = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("fullRange"));
  RooAbsReal* nUSIG = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("upperSIG"));
  RooAbsReal* domBkgIntegralLSB = model1.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB"));
  RooAbsReal* subBkgIntegralLSB = model2.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB"));
  RooAbsReal* domBkgIntegralUSB = model1.createIntegral(massVhad,NormSet(massVhad),Range("upperSB"));
  RooAbsReal* subBkgIntegralUSB = model2.createIntegral(massVhad,NormSet(massVhad),Range("upperSB"));
  RooAbsReal* domBkgIntegralSR = model1.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooAbsReal* subBkgIntegralSR = model2.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
  RooAbsReal* domBkgIntegralUSR = model1.createIntegral(massVhad,NormSet(massVhad),Range("upperSIG"));
  RooAbsReal* subBkgIntegralUSR = model2.createIntegral(massVhad,NormSet(massVhad),Range("upperSIG"));
  RooAbsReal* domBkgIntegralTOTAL = model1.createIntegral(massVhad,NormSet(massVhad),Range("fullRange"));
  RooAbsReal* subBkgIntegralTOTAL = model2.createIntegral(massVhad,NormSet(massVhad),Range("fullRange"));
  RooFormulaVar TotalBkgLSByield("TotalBkgLSByield","@0*(@1+@2)",RooArgList(*nSB,nbkg1,nbkg2));
  RooFormulaVar TotalBkgUSByield("TotalBkgUSByield","@0*(@1+@2)",RooArgList(*nSB2,nbkg1,nbkg2));
  RooFormulaVar TotalBkgUSRyield("TotalBkgUSRyield","@0*(@1+@2)",RooArgList(*nUSIG,nbkg1,nbkg2));
  RooFormulaVar domBkgLSByield("domBkgLSByield","@0*@1",RooArgList(*domBkgIntegralLSB,nbkg1));
  RooFormulaVar subBkgLSByield("subBkgLSByield","@0*@1",RooArgList(*subBkgIntegralLSB,nbkg2));
  RooFormulaVar domBkgUSByield("domBkgUSByield","@0*@1",RooArgList(*domBkgIntegralUSB,nbkg1));
  RooFormulaVar subBkgUSByield("subBkgUSByield","@0*@1",RooArgList(*subBkgIntegralUSB,nbkg2));
  RooFormulaVar domBkgSRyield("domBkgSRyield","@0*@1",RooArgList(*domBkgIntegralSR,nbkg1));
  RooFormulaVar subBkgSRyield("subBkgSRyield","@0*@1",RooArgList(*subBkgIntegralSR,nbkg2));
  RooFormulaVar domBkgUSRyield("domBkgUSRyield","@0*@1",RooArgList(*domBkgIntegralUSR,nbkg1));
  RooFormulaVar subBkgUSRyield("subBkgUSRyield","@0*@1",RooArgList(*subBkgIntegralUSR,nbkg2));
  RooFormulaVar domBkgTOTALyield("domBkgFULLyield","@0*@1",RooArgList(*domBkgIntegralTOTAL,nbkg1));
  RooFormulaVar subBkgTOTALyield("subBkgFULLyield","@0*@1",RooArgList(*subBkgIntegralTOTAL,nbkg2));
  RooFormulaVar lowerSIGyield("lowerSIGyield","extrapolation to lowerSIG","@0+@1", RooArgList(domBkgSRyield,subBkgSRyield));

  RooRealVar yieldDY_NS("yieldDY_NS","yieldDY_NS", domBkgSRyield.getVal());
  yieldDY_NS.setError(domBkgSRyield.getPropagatedError(*rf1));
  RooRealVar yieldDY_SB("yieldDY_SB","yieldDY_SB", domBkgLSByield.getVal() + domBkgUSByield.getVal());
  RooRealVar yieldSUB_NS("yieldSUB_NS","yieldSUB_NS", subBkgSRyield.getVal());
  yieldSUB_NS.setError(subBkgSRyield.getPropagatedError(*rf2));
  RooRealVar yieldSUB_SB("yieldSUB_SB","yieldSUB_SB", subBkgLSByield.getVal() + subBkgUSByield.getVal());
  
   Double_t bkgYield       =     yieldDY_NS.getVal();
  Double_t bkgYield_error = 1 + yieldDY_NS.getPropagatedError(*rf1)/bkgYield;
  RooRealVar DY_bkg_eig_norm("DY_bkg_eig_norm","expected yield in lowerSIG",bkgYield,0.,1.e4);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  std::cout << ""<<std::endl;
  std::cout << ""<<std::endl;
  std::cout << "******************************************************************" << std::endl;
  std::cout << "                   RESULTS                                        " << std::endl;
  std::cout << "******************************************************************" << std::endl;
  std::cout << ""<<std::endl;
  std::cout << ""<<std::endl;
  std::cout << "NORMALIZATION "<<legTitle[key].c_str()<<std::endl;
  std::cout << ""<<std::endl;
  std::cout << " LOWER SB "<<std::endl;
  std::cout << ""<<std::endl;
  std::cout << "       Expected  (Data)                       : " <<lsbObs.sumEntries() << std::endl;
  std::cout << "       Predicted (Dom Bkg)                    : " <<domBkgLSByield.getVal() << " +- " << domBkgLSByield.getPropagatedError(*rf1) << std::endl;
  std::cout << "       Predicted (Subdom Bkg)                 : "<<subBkgLSByield.getVal() << " +- " << subBkgLSByield.getPropagatedError(*rf2) << std::endl;
  std::cout << "       Predicted (Total Bkg)                  : "<<TotalBkgLSByield.getVal()<< " +- " << TotalBkgLSByield.getPropagatedError(*erf) << std::endl;
  std::cout << ""<<std::endl;
  std::cout << " LOWER SR "<<std::endl;
  std::cout << ""<<std::endl;
  std::cout << "       Data                                   : " <<sigObs.sumEntries() << std::endl;
  std::cout << "       Predicted (Dom Bkg)                    : " <<domBkgSRyield.getVal() << " +- " << domBkgSRyield.getPropagatedError(*rf1) << std::endl;
  std::cout << "       Predicted (Subdom Bkg)                 : "<<subBkgSRyield.getVal() << " +- " << subBkgSRyield.getPropagatedError(*rf2) << std::endl;
  std::cout << "       Predicted (Total Bkg)                  : "<<lowerSIGyield.getVal() << " +- " <<  lowerSIGyield.getPropagatedError(*erf) << std::endl;
  std::cout << ""<<std::endl;
  std::cout << " UPPER SR (Higgs) "<<std::endl;
  std::cout << ""<<std::endl;
  std::cout << "       Expected (Data)                        : " <<upsigObs.sumEntries() << std::endl;
  std::cout << "       Predicted (Dom Bkg)                    : " <<domBkgUSRyield.getVal() << " +- " << domBkgUSRyield.getPropagatedError(*rf1) << std::endl;
  std::cout << "       Predicted (Subdom Bkg)                 : "<<subBkgUSRyield.getVal() << " +- " << subBkgUSRyield.getPropagatedError(*rf2) << std::endl;
  std::cout << "       Predicted (Total Bkg)                  : "<<TotalBkgUSRyield.getVal() << " +- " <<  TotalBkgUSRyield.getPropagatedError(*erf) << std::endl;
  std::cout << ""<<std::endl;
  std::cout << " UPPERS SB "<<std::endl;
  std::cout << ""<<std::endl;
  std::cout << "       Expected (Data)                        : " <<usbObs.sumEntries() << std::endl;
  std::cout << "       Predicted (Dom Bkg)                    : " <<domBkgUSByield.getVal() << " +- " << domBkgUSByield.getPropagatedError(*rf1) << std::endl;
  std::cout << "       Predicted (Subdom Bkg)                 : "<<subBkgUSByield.getVal() << " +- " << subBkgUSByield.getPropagatedError(*rf2) << std::endl;
  std::cout << "       Predicted (Total Bkg)                  : "<<TotalBkgUSByield.getVal()<< " +- " << TotalBkgUSByield.getPropagatedError(*erf) << std::endl;



}
