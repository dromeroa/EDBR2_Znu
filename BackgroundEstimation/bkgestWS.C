
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

void bkgestWS(std::string key)
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
  int plevelshap =-1;
  int plevelshapDom = -1;
  // Silent RooFit
  RooMsgService::instance().setGlobalKillBelow(FATAL);
  ////**************************************************


  ////*********************************************************************
  //// 2. INTRODUCE THE VARIABLES
  ////*********************************************************************
  RooRealVar candTMass("candTMass","M_{VZ}",            600.,  3500., "GeV");
  RooRealVar massVhad("massVhad","M_{j}" ,               40.,   220., "GeV");
  RooRealVar tau21("tau21","tau21",                       0.,   1.0        );
  RooRealVar totalWeight("totalWeight", "total weight",   0.,  10.         );
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

      treeData.Add(     "../trees/newtrees/treeEDBR_MET_Run2015C_25ns_16Dec2015_v1.root"         );
      treeData.Add(     "../trees/newtrees/treeEDBR_MET_Run2015D_16Dec2015_v1.root"              );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_QCD_76x_v2.root"                             );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_QCD_HT1000to1500_76x_v2.root"                );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_QCD_HT1500to2000_76x_v2.root"                );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_QCD_HT700to1000_76x_v2.root"                  );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_TTbar_76x_v2.root"                            );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_TTJets_reg_76x_v2.root"                        );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_VV_76x_v2.root"                                );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_WW_76x_v2.root"                                );
      treeMC2.Add(      "../trees/newtrees/treeEDBR_WZ_76x_v2.root"                                );
      treeMC1.Add(      "../trees/newtrees/treeEDBR_Z+Jets_76x_v2.root"                            );
      treeMC1.Add(      "../trees/newtrees/treeEDBR_ZJetsToNuNu_HT-100To200_76x_v2.root"           );
      treeMC1.Add(      "../trees/newtrees/treeEDBR_ZJetsToNuNu_HT-200To400_76x_v2.root"           );
      treeMC1.Add(      "../trees/newtrees/treeEDBR_ZJetsToNuNu_HT-400To600_76x_v2.root"           );
      treeMC1.Add(      "../trees/newtrees/treeEDBR_W+Jets_76x_v2.root"                            );
      treeMC1.Add(      "../trees/newtrees/treeEDBR_WJetsToLNu_HT-100To200_76x_v2.root"            );
      treeMC1.Add(      "../trees/newtrees/treeEDBR_WJetsToLNu_HT-200To400_76x_v2.root"            );
      treeMC1.Add(      "../trees/newtrees/treeEDBR_WJetsToLNu_HT-400To600_76x_v2.root"            );


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

   RooDataSet Data_SB("Data_SB","Data_SB", variables, Cut(allSB), Import(treeData));
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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


RooRealVar c1("c1","slope of the exp",             -0.032,  -1.,    0.);
RooRealVar offset1("offset1","offset of the erf",    85.0,   1.,  150.);
RooRealVar width1("width1",  "width of the erf",     36.0,   1,   100.);
  
RooRealVar mu1("mu1", "average", 84, 0, 200);
RooRealVar sigma1("sigma1", "sigma", 8.7, 0, 100);
RooRealVar mu2("mu2", "average", 102, 0, 200);
RooRealVar sigma2("sigma2", "sigma", 28, 0, 100);
RooGaussian gauss1("gauss1","gaussian PDF1", massVhad, mu1, sigma1);
RooGaussian gauss2("gauss2","gaussian PDF2", massVhad, mu2, sigma2);
RooRealVar funfrac("funfrac","fraction of functions",0.6,0.,1.);
  
RooErfExpPdf model1("model1","dominant backgrounds",massVhad,c1,offset1,width1);
RooAddPdf model2("Gaus2", "gaussian plus gaussian", RooArgList(gauss1, gauss2), funfrac);
    
     
RooFitResult *rf1 = model1.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));      
RooFitResult *rf2 = model2.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,160));

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


RooExtendPdf emodel1("emodel1","extended dom backgrounds",model1,nbkg1);
RooExtendPdf emodel2("emodel2","extended sub backgrounds",model2,nbkg2);
RooAddPdf model_ext("model_ext","sum of extended models",RooArgList(emodel1,emodel2));


model_ext.fitTo(Data_SB,Extended(kTRUE),Range("lowerSB,upperSB"),PrintLevel(-1));
nbkg1.setConstant(true);


RooAbsReal* Dom_integral = model1.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
RooAbsReal* Sub_integral = model2.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
RooAbsReal* Dom_SB_integral = model1.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB,upperSB"));
RooAbsReal* Sub_SB_integral = model2.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB,upperSB"));
RooFormulaVar Dom_yield( "Dom_yield","@0*@1",RooArgList( *Dom_integral,nbkg1));
RooFormulaVar Sub_yield( "Sub_yield","@0*@1",RooArgList( *Sub_integral,nbkg2));
RooFormulaVar Dom_SB_yield( "Dom_SB_yield","@0*@1",RooArgList( *Dom_SB_integral,nbkg1));
RooFormulaVar Sub_SB_yield("Sub_SB_yield","@0*@1",RooArgList(*Sub_SB_integral,nbkg2));


RooFormulaVar coef( "coef","@0/@1", RooArgList(Sub_SB_yield,Dom_SB_yield));

RooRealVar Sub_pdf_norm("Sub_pdf_norm", "Sub yield in lowerSIG", Sub_yield.getVal(), 0.,1.e4);
RooRealVar Dom_pdf_norm( "Dom_pdf_norm", "Dom yield in lowerSIG", Dom_yield.getVal(), 0.,1.e4);
RooRealVar Dom_error( "Dom_error", "Dom yield error", 1 + Dom_yield.getPropagatedError(*rf1)/ Dom_yield.getVal(),1.,2.);
cout << "Dom estimation = " << Dom_yield.getVal() << " +/- " << Dom_yield.getPropagatedError(*rf1) << endl;
cout << "Sub estimation = " << Sub_yield.getVal() << " +/- " << Sub_yield.getPropagatedError(*rf2) << endl;
std::cout << "Events in signal region = " << sigObs.sumEntries() << std::endl;
Sub_pdf_norm.setConstant(true);

 
///////////////////////////////////////////////////////////////////////////////
////                           _____ _                                         //
////                          / ____| |                                        //
////                         | (___ | |__   __ _ _ __   ___                    //
////                          \___ \| '_ \ / _` | '_ \ / _ \                   // 
////                          ____) | | | | (_| | |_) |  __/                   //
////                         |_____/|_| |_|\__,_| .__/ \___|                   //
////                                            | |                            //
////                                            |_|                            // 
/////////////////////////////////////////////////////////////////////////////////

    //*****************************************************************
    //     DECLARE PDFs (5 LEVEL EXPONENTIALS)   
    //***************************************************************



RooRealVar s0("s0","slope of the exp0", 100., 0., 1000.);
RooRealVar s1("s1","slope of the exp1", 100., 0., 1000.);
RooRealVar s2("s2","slope of the exp2", 200., 0., 1000.);
RooRealVar s3("s3","slope of the exp3", 1., 0., 200.);
RooRealVar s4("s4","slope of the exp4", 200, 0., 1000.);
RooRealVar a0("a0","parameter of exp0", 0.1 , 0.001, 10.);
RooRealVar a1("a1","parameter of exp1", 0.1 , 0.001, 10.);
RooRealVar a2("a2","parameter of exp2", 0., -1, 1.);
RooRealVar a3("a3","parameter of exp3", 0.03 , 0., 60);
RooRealVar a4("a4","parameter of exp4", 0., -1, 1);
RooExpTailPdf Sub_pdf( "Sub_pdf", "Sub in nominal region", candTMass,s0,a0);
RooExpTailPdf Sub_SB_pdf("Sub_SB_pdf", "Sub in sideband region", candTMass,s1,a1);
RooExpTailPdf Dat_SB ("Dat_SB" , "Data sideband", candTMass,s2,a2);
RooExpTailPdf Dom_SR_pdf( "Dom_SR_pdf", "Dom in nominal region", candTMass,s3,a3);
RooExpTailPdf Dom_SB_pdf( "Dom_SB_pdf", "Dom in sideband region", candTMass,s4,a4);
a4.setConstant(true);
a2.setConstant(true);


RooAddPdf Data_SB_pdf("Data_SB_pdf", "Model data in sideband", Sub_SB_pdf, Dat_SB, coef);
RooAlpha4ExpTailPdf alpha_pdf("alpha", "alpha function for Dom", candTMass,s3,a3,s4,a4);
RooProdPdf Dom("Dom", "Dom in SIG", alpha_pdf, Dat_SB);

candTMass.setRange("range", 600., 3500);



RooDataSet Sub( "Sub", "Sub", variables, Cut(lowerSIG), WeightVar(totalWeight), Import(treeMC2));
RooDataSet Sub_SB("Sub_SB", "Sub_SB", variables, Cut(allSB), WeightVar(totalWeight), Import(treeMC2));
Sub_pdf.fitTo( Sub, Range("range"), SumW2Error(true), PrintLevel(-1));
Sub_SB_pdf.fitTo(Sub_SB, Range("range"), SumW2Error(true), PrintLevel(-1));
s0.setConstant(true); a0.setConstant(true);
s1.setConstant(true); a1.setConstant(true);




RooDataSet Dom_SR("Dom_SR", "Dom_SR", variables, Cut(lowerSIG), WeightVar(totalWeight), Import(treeMC1));
RooDataSet Dom_SB("Dom_SB", "Dom_SB", variables, Cut(allSB), WeightVar(totalWeight), Import(treeMC1));
RooCategory reg("reg","reg");
reg.defineType("1");
reg.defineType("2");
reg.defineType("3");
RooDataSet bigSample("bigSample","bigSample",variables,WeightVar(totalWeight),Index(reg),Import("1",Dom_SR),Import("2",Dom_SB),Import("3",Data_SB));
RooSimultaneous bigSample_pdf("bigSample_pdf", "simultaneous pdf", RooArgList(Dom_SR_pdf,Dom_SB_pdf,Data_SB_pdf), reg); 

RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), Range("range"), SumW2Error(kTRUE));

s2.setConstant(true); a2.setConstant(true);
s3.setConstant(true); a3.setConstant(true);
s4.setConstant(true); a4.setConstant(true);


RooWorkspace *w = new RooWorkspace("ZZnunu_13TeV","workspace");

w->import(Sub_pdf);
w->import(Sub_pdf_norm);
w->import(Dom_pdf_norm);
w->import(Dom_error);

PdfDiagonalizer diag("pdf", w, *fitres);
RooAbsPdf *Dom_pdf = diag.diagonalize( Dom );
w->import(*Dom_pdf , RecycleConflictNodes() );

RooDataSet data_obs("data_obs","data_obs",variables,Cut(lowerSIG),Import(treeData));
w->import(data_obs);

w->writeToFile(Form("workSpaces/Workspace2/MS_ZZnunu_%s_13TeV.root",key.c_str()));

}
