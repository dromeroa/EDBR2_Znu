
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

void testVVfit(std::string key)
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
  RooRealVar totalWeight("totalWeight", "total weight",   -100.,  100.         );
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
//      treeMC2.Add(      "../trees/newtrees/treeEDBR_QCD_76x_v2.root"                             );
//      treeMC2.Add(      "../trees/newtrees/treeEDBR_QCD_HT1000to1500_76x_v2.root"                );
//      treeMC2.Add(      "../trees/newtrees/treeEDBR_QCD_HT1500to2000_76x_v2.root"                );
//      treeMC2.Add(      "../trees/newtrees/treeEDBR_QCD_HT700to1000_76x_v2.root"                  );
//      treeMC2.Add(      "../trees/newtrees/treeEDBR_TTbar_76x_v2.root"                            );
//      treeMC2.Add(      "../trees/newtrees/treeEDBR_TTJets_reg_76x_v2.root"                        );
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
  // ErfExp 
  RooRealVar c2("c2","slope of the exp",             -0.040,  -1.,    0.);
  RooRealVar offset2("offset2","offset of the erf",    79.0,   1.,  150.);
  RooRealVar width2("width2",  "width of the erf",     17.0,   1,   100.);
  // Gaus 2 (gauss1 +gauss2)
  RooRealVar mu1("mu1", "average", 84, 0, 200);
  RooRealVar sigma1("sigma1", "sigma", 8.7, 0, 100);
  RooRealVar mu2("mu2", "average", 102, 0, 200);
  RooRealVar sigma2("sigma2", "sigma", 28, 0, 100); 
  RooGaussian gauss1("gauss1","gaussian PDF1", massVhad, mu1, sigma1);
  RooGaussian gauss2("gauss2","gaussian PDF2", massVhad, mu2, sigma2);
  RooRealVar funfrac("funfrac","fraction of functions",0.6,0.,1.);
  // ExpGaus (exp + gauss)
  RooRealVar mu3("mu3", "average", 90, 0, 200);
  RooRealVar sigma3("sigma3", "sigma", 20, 0, 100);
  RooRealVar lambda("lambda", "exponential slope", -0.1, -1.0, 1.0);
  RooGaussian gauss3("gauss3","gaussian PDF", massVhad, mu3, sigma3);
  RooExponential expo("expo", "exponential PDF", massVhad, lambda);
  RooRealVar funfrac2("funfrac2","fraction of functions",0.6,0.,1.);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //  THE MODELS
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooErfExpPdf model1("model1","dominant backgrounds",massVhad,c1,offset1,width1);
  RooErfExpPdf model1a("model1a","dominant backgroundsa",massVhad,c1,offset1,width1);

  RooErfExpPdf model2("model2","subdom backgrounds",massVhad,c2,offset2,width2);
  RooErfExpPdf model2a("model2a","subdom backgroundsa",massVhad,c2,offset2,width2);

  RooAddPdf model3("Gaus2", "gaussian plus gaussian", RooArgList(gauss1, gauss2), funfrac);
  RooAddPdf model3a("Gaus2a", "gaussian plus gaussiana", RooArgList(gauss1, gauss2), funfrac);

  RooAddPdf model4("Gausexpo", "gaussian plus expo", RooArgList(gauss3, expo), funfrac2);
  RooAddPdf model4a("Gausexpoa", "gaussian plus expo", RooArgList(gauss3, expo), funfrac2);
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


  // A command to add a normalization to the PDF
  RooExtendPdf emodel1("emodel1","extended dom backgrounds",model1,nbkg1);
  RooExtendPdf emodel1a("emodel1a","extended dom backgroundsa",model1a,nbkg1);
  RooExtendPdf emodel2("emodel2","extended sub backgrounds",model2,nbkg2);
  RooExtendPdf emodel2a("emodel2a","extended sub backgrounds",model2a,nbkg2);
  RooExtendPdf emodel3("emodel3","extended sub backgrounds",model3,nbkg2);
  RooExtendPdf emodel3a("emodel3a","extended sub backgrounds",model3a,nbkg2);
  RooExtendPdf emodel4("emodel4","extended sub backgrounds",model4,nbkg2);
  RooExtendPdf emodel4a("emodel4a","extended sub backgrounds",model4a,nbkg2);


  // The fit of each background in all range separatly
//  std::cout << "Fitting models - normalisation" << std::endl;
//  RooFitResult *rf1 = emodel1.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));
//  RooFitResult *rf1a = emodel1a.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));
//  RooFitResult *rf2 = emodel2.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,220));
//  RooFitResult *rf2a = emodel2a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,220));

//  RooFitResult *rf2 = emodel2.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
//  RooFitResult *rf2a = emodel2a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));

  RooFitResult *rf3 = emodel3.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,220));
  RooFitResult *rf3a = emodel3a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,220));

  RooBinning xbins(36,40,220);
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  // 3. SUBDOMINANT BACKGROUND (GAUS 2)
  RooPlot* frame3 = massVhad.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
  bkg2.plotOn(frame3,Name("mc3"),Binning(xbins),Range(40,220));
  model3.plotOn(frame3,Name("fitmc3"), LineColor(kRed),Range(40,220));
  model3a.plotOn(frame3,Name("error3"),VisualizeError(*rf3a,1),FillColor(kAzure-2), FillStyle(3002),Range(40,220));


//    bkg2.plotOn(frame3,Name("mc3"),Binning(xbins));
//  model3.plotOn(frame3,Name("fitmc3"), LineColor(kRed));
//  model3a.plotOn(frame3,Name("error3"),VisualizeError(*rf3a,1),FillColor(kAzure-2), FillStyle(3002));



//  model3.paramOn(frame3,Layout(0.53,0.9,0.8));
//  frame3->drawAfter("error3","mc3");
//  frame3->drawAfter("error3","fitmc3");
//  frame3->getAttText()->SetTextSize(0.020);

  frame3->SetTitle("");


  TText* tx4 = new TText(50,36,"CMS") ;
  tx4->SetTextSize(0.04) ;
  tx4->SetTextColor(kBlack) ;
  tx4->SetTextFont(61);
  frame3->addObject(tx4) ;

  TText* tx5 = new TText(50,34,"Simulation") ;
  tx5->SetTextSize(0.04) ;
  tx5->SetTextColor(kBlack) ;
  tx5->SetTextFont(52);
  frame3->addObject(tx5) ;


  TText* tx6 = new TText(159,41,"2.307 /fb (13TeV)") ;
  tx6->SetTextSize(0.04) ;
  tx6->SetTextColor(kBlack) ;
  frame3->addObject(tx6) ;

  // THE CANVAS
  TCanvas cv3("cv3","cv3",800,800);
  // The pulls
  RooHist* hpull3 = frame3->pullHist("mc3","fitmc3");
  RooPlot* frame3a = massVhad.frame();
  frame3a->addPlotable(hpull3,"P"); 
  // Chi square
  Double_t chi2b = frame3->chiSquare("fitmc3", "mc3", 5);
  // The Pads
  TPad* fPads1b = NULL;
  TPad* fPads2b = NULL;
  fPads1b = new TPad("pad1b", "", 0.00, 0.17, 0.99, 0.99);
  fPads2b = new TPad("pad2b", "", 0.00, 0.04, 0.99, 0.25);
  fPads1b->SetFillColor(0);
  fPads1b->SetLineColor(0);
  fPads2b->SetFillColor(0);
  fPads2b->SetLineColor(0);
  fPads1b->Draw();
  fPads2b->Draw();
  // First pad
  fPads1b->cd();
  frame3->GetYaxis()->SetTitleOffset(1.30);
  frame3->GetXaxis()->SetLabelSize(0);
  frame3->Draw();
  // The Legend
  TLegend *leg1b = new TLegend(0.53,0.7,0.9,0.9);
  leg1b->SetHeader(legTitle[key].c_str());
  leg1b->AddEntry("mc3",  "VV Background ",    "ep");
  leg1b->AddEntry("fitmc3","Gaus2 Fit Function", "l");
  leg1b->SetTextSize(0.04);
  leg1b->Draw();
  TLegendEntry *header1b = (TLegendEntry*)leg1b->GetListOfPrimitives()->First();
  header1b->SetTextAlign(22);
  header1b->SetTextColor(1);
  header1b->SetTextSize(.04);
  // Second Pad
  fPads2b->cd();
  fPads2b->SetGridx();
  fPads2b->SetGridy();
  fPads2b->SetTopMargin(0);
  fPads2b->SetBottomMargin(0.4);
  frame3a->GetYaxis()->SetLabelSize(0.08);
  frame3a->GetXaxis()->SetLabelSize(0.17);
  frame3a->GetYaxis()->SetTitle("Pulls");
  frame3a->GetYaxis()->SetTitleOffset(0.30);
  frame3a->GetYaxis()->SetTitleSize(0.15);
  frame3a->GetXaxis()->SetTitleSize(0.17);
  frame3a->GetYaxis()->SetRangeUser(-5,5);
  frame3a->SetTitle("");
  frame3a->Draw();
  TPaveLabel *t3 = new TPaveLabel(0.7,0.85,0.9,1, Form("#chi^{2}/dof = %f", chi2b),"brNDC");
  t3->Draw();
  // SAVE THE FILE
  cv3.SaveAs(Form("otherPlots/VVMj%s_gaus2.png",key.c_str()));
  cv3.SaveAs(Form("otherPlots/VVMj%s_gaus2.pdf",key.c_str()));
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

}
