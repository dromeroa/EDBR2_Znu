
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

void test11mayoLP(std::string key)
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
//  RooRealVar c1("c1","slope of the exp",             -0.1,  -10.,    10.);
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
  RooRealVar mu1("mu1", "average", 150, 0, 300);
  RooRealVar sigma1("sigma1", "sigma", 16, 0, 100);
  RooRealVar mu2("mu2", "average", 75, 0, 200);
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
  std::cout << "Fitting models - normalisation" << std::endl;
  RooFitResult *rf1 = emodel1.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf1a = emodel1a.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf2 = emodel2.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,160));
  RooFitResult *rf2a = emodel2a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,160));

//  RooFitResult *rf2 = emodel2.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
//  RooFitResult *rf2a = emodel2a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));

  RooFitResult *rf3 = emodel3.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,160));
  RooFitResult *rf3a = emodel3a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,160));

//  RooFitResult *rf3 = emodel3.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
//  RooFitResult *rf3a = emodel3a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));


  RooFitResult *rf4 = emodel4.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,160));
  RooFitResult *rf4a = emodel4a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,160));
 

// RooFitResult *rf4 = emodel4.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
//  RooFitResult *rf4a = emodel4a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));

 
  //*****************************************************************
  //                     PLOTS FOR THE BACKGROUNDS AND FITS
  //****************************************************************

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /// 1. DOMINANT BACKGROUND
  RooPlot* frame1 = massVhad.frame();
  TCanvas cv("cv","cv",800,800);
  // Dominant backgrounds
  bkg1.plotOn(frame1,Name("mc1"), DrawOption("ep"),Binning(36));
  model1.plotOn(frame1,Name("fitmc1"),LineColor(kBlue));
  model1a.plotOn(frame1,Name("error"),VisualizeError(*rf1a,1),FillColor(kAzure-2), FillStyle(3002));  
  model1.paramOn(frame1,Layout(0.58,0.9,0.6));
  frame1->drawAfter("error","mc1");
  frame1->drawAfter("error","fitmc1");
  frame1->getAttText()->SetTextSize(0.03); 
  frame1->SetTitle("");

  TText* te1 = new TText(50,240,"CMS") ;
  te1->SetTextSize(0.04) ;
  te1->SetTextColor(kBlack) ;
  te1->SetTextFont(61);
  frame1->addObject(te1) ;

  TText* txt1a = new TText(50,225,"Simulation") ;
  txt1a->SetTextSize(0.04) ;
  txt1a->SetTextColor(kBlack) ;
  txt1a->SetTextFont(52);
  frame1->addObject(txt1a) ;


  TText* txt2a = new TText(160,270,"2.307 /fb (13TeV)") ;
  txt2a->SetTextSize(0.04) ;
  txt2a->SetTextColor(kBlack) ;
  frame1->addObject(txt2a) ;


  // The pulls
  RooHist* hpull = frame1->pullHist("mc1","fitmc1");
  RooPlot* frame1a = massVhad.frame() ;
  frame1a->addPlotable(hpull,"P") ;
  // Chi square
  Double_t chi2 = frame1->chiSquare("fitmc1", "mc1", 3); 
  // The pads
  TPad* fPads1 = NULL;
  TPad* fPads2 = NULL;
  fPads1 = new TPad("pad1", "", 0.00, 0.17, 0.99, 0.99);
  fPads2 = new TPad("pad2", "", 0.00, 0.04, 0.99, 0.25);
  fPads1->SetFillColor(0);
  fPads1->SetLineColor(0);
  fPads2->SetFillColor(0);
  fPads2->SetLineColor(0);
  fPads1->Draw();
  fPads2->Draw();
  // First pad (main plot)
  fPads1->cd();
  frame1->GetYaxis()->SetTitleOffset(1.30);
  frame1->GetXaxis()->SetLabelSize(0);
  frame1->Draw();
  // The legend
  TLegend *leg1 = new TLegend(0.58,0.6,0.9,0.9);
  leg1->SetHeader(legTitle[key].c_str());
  leg1->AddEntry("mc1",  "Dominant Background ",    "ep");
  leg1->AddEntry("fitmc1","ErfExp Fit Function", "l");
  leg1->SetTextSize(0.03);
  leg1->Draw();
  TLegendEntry *header1 = (TLegendEntry*)leg1->GetListOfPrimitives()->First();
  header1->SetTextAlign(22);
  header1->SetTextColor(1);
  header1->SetTextSize(.045); 
  // Second Pad
  fPads2->cd();
  fPads2->SetGridx();
  fPads2->SetGridy();
  fPads2->SetTopMargin(0);
  fPads2->SetBottomMargin(0.4);
  frame1a->GetYaxis()->SetLabelSize(0.08);
  frame1a->GetXaxis()->SetLabelSize(0.17);
  frame1a->GetYaxis()->SetTitle("Pulls");
  frame1a->GetYaxis()->SetTitleOffset(0.30);
  frame1a->GetYaxis()->SetTitleSize(0.15);
  frame1a->GetXaxis()->SetTitleSize(0.17);
  frame1a->GetYaxis()->SetRangeUser(-5,5);
  frame1a->SetTitle(""); 
  frame1a->Draw();
  TPaveLabel *t1 = new TPaveLabel(0.7,0.85,0.9,1, Form("#chi^{2}/dof = %f", chi2),"brNDC");
  t1->Draw();
  // SAVE THE FILE 
  cv.SaveAs(Form("otherPlots/domBkgMj%s.png",key.c_str()));
  cv.SaveAs(Form("otherPlots/domBkgMj%s.pdf",key.c_str()));
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



  //++++++++++++++++++++++i+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // bining for subdominant background
  // check the other for (36,40,220)
//   RooBinning xbins(36,40,220);
  RooBinning xbins(24,40,160);
  

  // 2. SUBDOMINANT BACKGROUND (erf*exp)
  RooPlot* frame2 = massVhad.frame();
  bkg2.plotOn(frame2,Name("mc2"),Binning(xbins),Range(40,160));
  model2.plotOn(frame2,Name("fitmc2"), LineColor(kRed),Range(40,160));
  model2a.plotOn(frame2,Name("error2"),VisualizeError(*rf2a,1),FillColor(kAzure-2), FillStyle(3002),Range(40,160));

//  bkg2.plotOn(frame2,Name("mc2"),Binning(xbins));
//  model2.plotOn(frame2,Name("fitmc2"), LineColor(kRed));
//  model2a.plotOn(frame2,Name("error2"),VisualizeError(*rf2a,1),FillColor(kAzure-2), FillStyle(3002));



  model2.paramOn(frame2,Layout(0.53,0.9,0.7));
  frame2->drawAfter("error2","mc2");
  frame2->drawAfter("error2","fitmc2");
  frame2->getAttText()->SetTextSize(0.03);
  frame2->SetTitle("");


  TText* tx1 = new TText(50,24,"CMS") ;
  tx1->SetTextSize(0.04) ;
  tx1->SetTextColor(kBlack) ;
  tx1->SetTextFont(61);
  frame2->addObject(tx1) ;

  TText* tx2 = new TText(50,22.7,"Simulation") ;
  tx2->SetTextSize(0.04) ;
  tx2->SetTextColor(kBlack) ;
  tx2->SetTextFont(52);
  frame2->addObject(tx2) ;


  TText* tx3 = new TText(161,28,"2.307 /fb (13TeV)") ;
  tx3->SetTextSize(0.04) ;
  tx3->SetTextColor(kBlack) ;
  frame2->addObject(tx3) ;



  // The canvas
  TCanvas cv2("cv2","cv2",800,800);
  // The pulls
  RooHist* hpull2 = frame2->pullHist();
  RooPlot* frame2a = massVhad.frame();
  frame2a->addPlotable(hpull2,"P");
  // Chi square
  Double_t chi2a = frame2->chiSquare("fitmc2", "mc2", 3);
  // The pads
  TPad* fPads1a = NULL;
  TPad* fPads2a = NULL;
  fPads1a = new TPad("pad1d", "", 0.00, 0.17, 0.99, 0.99);
  fPads2a = new TPad("pad2d", "", 0.00, 0.04, 0.99, 0.25);
  fPads1a->SetFillColor(0);
  fPads1a->SetLineColor(0);
  fPads2a->SetFillColor(0);
  fPads2a->SetLineColor(0);
  fPads1a->Draw();
  fPads2a->Draw(); 
  // First Pad
  fPads1a->cd();
  frame2->GetYaxis()->SetTitleOffset(1.30);
  frame2->GetXaxis()->SetLabelSize(0);
//  frame2->GetYaxis()->SetRangeUser(0,50);
  frame2->Draw();
  // The Legend
  TLegend *leg1a = new TLegend(0.53,0.7,0.9,0.9);
  leg1a->SetHeader(legTitle[key].c_str());
  leg1a->AddEntry("mc2",  "Subdominant Background ",    "ep");
  leg1a->AddEntry("fitmc2","ErfExp Fit Function", "l");
  leg1a->SetTextSize(0.03);
  leg1a->Draw();
  TLegendEntry *header1a = (TLegendEntry*)leg1a->GetListOfPrimitives()->First();
  header1a->SetTextAlign(22);
  header1a->SetTextColor(1);
  header1a->SetTextSize(.045);
  // Second Pad
  fPads2a->cd();
  fPads2a->SetGridx();
  fPads2a->SetGridy();
  fPads2a->SetTopMargin(0);
  fPads2a->SetBottomMargin(0.4);
  frame2a->GetYaxis()->SetLabelSize(0.08);
  frame2a->GetXaxis()->SetLabelSize(0.17);
  frame2a->GetYaxis()->SetTitle("Pulls");
  frame2a->GetYaxis()->SetTitleOffset(0.30);
  frame2a->GetYaxis()->SetTitleSize(0.15);
  frame2a->GetXaxis()->SetTitleSize(0.17);
  frame2a->GetYaxis()->SetRangeUser(-5,5);
  frame2a->SetTitle("");
  frame2a->Draw();
  TPaveLabel *t2 = new TPaveLabel(0.7,0.85,0.9,1, Form("#chi^{2}/dof = %f", chi2a),"brNDC");
  t2->Draw();
  // SAVE THE FILE
  cv2.SaveAs(Form("otherPlots/subBkgMj%s.png",key.c_str()));
  cv2.SaveAs(Form("otherPlots/subBkgMj%s.pdf",key.c_str()));
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // 3. SUBDOMINANT BACKGROUND (GAUS 2)
  RooPlot* frame3 = massVhad.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
  bkg2.plotOn(frame3,Name("mc3"),Binning(xbins),Range(40,160));
  model3.plotOn(frame3,Name("fitmc3"), LineColor(kRed),Range(40,160));
  model3a.plotOn(frame3,Name("error3"),VisualizeError(*rf3a,1),FillColor(kAzure-2), FillStyle(3002),Range(40,160));


//    bkg2.plotOn(frame3,Name("mc3"),Binning(xbins));
//  model3.plotOn(frame3,Name("fitmc3"), LineColor(kRed));
//  model3a.plotOn(frame3,Name("error3"),VisualizeError(*rf3a,1),FillColor(kAzure-2), FillStyle(3002));



  model3.paramOn(frame3,Layout(0.53,0.9,0.7));
  frame3->drawAfter("error3","mc3");
  frame3->drawAfter("error3","fitmc3");
  frame3->getAttText()->SetTextSize(0.025);

  frame3->SetTitle("");


  TText* tx4 = new TText(50,24,"CMS") ;
  tx4->SetTextSize(0.04) ;
  tx4->SetTextColor(kBlack) ;
  tx4->SetTextFont(61);
  frame3->addObject(tx4) ;

  TText* tx5 = new TText(50,22.7,"Simulation") ;
  tx5->SetTextSize(0.04) ;
  tx5->SetTextColor(kBlack) ;
  tx5->SetTextFont(52);
  frame3->addObject(tx5) ;


  TText* tx6 = new TText(159,28,"2.307 /fb (13TeV)") ;
  tx6->SetTextSize(0.04) ;
  tx6->SetTextColor(kBlack) ;
  frame3->addObject(tx6) ;

  // THE CANVAS
  TCanvas cv3("cv3","cv3",800,800);
  // The pulls
  RooHist* hpull3 = frame3->pullHist();
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
  leg1b->AddEntry("mc3",  "Subdominant Background ",    "ep");
  leg1b->AddEntry("fitmc3","Gaus2 Fit Function", "l");
  leg1b->SetTextSize(0.03);
  leg1b->Draw();
  TLegendEntry *header1b = (TLegendEntry*)leg1b->GetListOfPrimitives()->First();
  header1b->SetTextAlign(22);
  header1b->SetTextColor(1);
  header1b->SetTextSize(.045);
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
  cv3.SaveAs(Form("otherPlots/subBkgMj%s_gaus2.png",key.c_str()));
  cv3.SaveAs(Form("otherPlots/subBkgMj%s_gaus2.pdf",key.c_str()));
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

 
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // 4. SUBDOMINANT BACKGROUND (GAUSEXPO)
  RooPlot* frame4 = massVhad.frame();
  bkg2.plotOn(frame4,Name("mc4"),Binning(xbins),Range(40,160));
  model4.plotOn(frame4,Name("fitmc4"), LineColor(kRed),Range(40,160));
  model4a.plotOn(frame4,Name("error4"),VisualizeError(*rf4a,1),FillColor(kAzure-2), FillStyle(3002),Range(40,160));
  model4.paramOn(frame4,Layout(0.53,0.9,0.7));
  frame4->drawAfter("error4","mc4");
  frame4->drawAfter("error4","fitmc4");
  frame4->getAttText()->SetTextSize(0.03);
  frame4->SetTitle("");


  TText* tx7 = new TText(50,24,"CMS") ;
  tx7->SetTextSize(0.04) ;
  tx7->SetTextColor(kBlack) ;
  tx7->SetTextFont(61);
  frame4->addObject(tx7) ;

  TText* tx8 = new TText(50,22.7,"Simulation") ;
  tx8->SetTextSize(0.04) ;
  tx8->SetTextColor(kBlack) ;
  tx8->SetTextFont(52);
  frame4->addObject(tx8) ;


  TText* tx9 = new TText(159,28,"2.307 /fb (13TeV)") ;
  tx9->SetTextSize(0.04) ;
  tx9->SetTextColor(kBlack) ;
  frame4->addObject(tx9) ;

  // THE CANVAS
  TCanvas cv4("cv4","cv4",800,800);
  // The pulls
  RooHist* hpull4 = frame4->pullHist();
  RooPlot* frame4a = massVhad.frame();
  frame4a->addPlotable(hpull4,"P");
  // Chi square
  Double_t chi2c = frame4->chiSquare("fitmc4", "mc4", 4);
  // The Pads
  TPad* fPads1c = NULL;
  TPad* fPads2c = NULL;
  fPads1c = new TPad("pad1d", "", 0.00, 0.17, 0.99, 0.99);
  fPads2c = new TPad("pad2d", "", 0.00, 0.04, 0.99, 0.25);
  fPads1c->SetFillColor(0);
  fPads1c->SetLineColor(0);
  fPads2c->SetFillColor(0);
  fPads2c->SetLineColor(0);
  fPads1c->Draw();
  fPads2c->Draw();
  // First pad
  fPads1c->cd();
  frame4->GetYaxis()->SetTitleOffset(1.30);
  frame4->GetXaxis()->SetLabelSize(0);
  frame4->Draw();
  // The Legend
  TLegend *leg1c = new TLegend(0.53,0.7,0.9,0.9);
  leg1c->SetHeader(legTitle[key].c_str());
  leg1c->AddEntry("mc4",  "Subdominant Background ",    "ep");
  leg1c->AddEntry("fitmc4","GausExpo Fit Function", "l");
  leg1c->SetTextSize(0.03);
  leg1c->Draw();
  TLegendEntry *header1c = (TLegendEntry*)leg1c->GetListOfPrimitives()->First();
  header1c->SetTextAlign(22);
  header1c->SetTextColor(1);
  header1c->SetTextSize(.045);
  // Second Pad
  fPads2c->cd();
  fPads2c->SetGridx();
  fPads2c->SetGridy();
  fPads2c->SetTopMargin(0);
  fPads2c->SetBottomMargin(0.4);
  frame4a->GetYaxis()->SetLabelSize(0.08);
  frame4a->GetXaxis()->SetLabelSize(0.17);
  frame4a->GetYaxis()->SetTitle("Pulls");
  frame4a->GetYaxis()->SetTitleOffset(0.30);
  frame4a->GetYaxis()->SetTitleSize(0.15);
  frame4a->GetXaxis()->SetTitleSize(0.17);
  frame4a->GetYaxis()->SetRangeUser(-5,5);
  frame4a->SetTitle("");
  frame4a->Draw();
  TPaveLabel *t4 = new TPaveLabel(0.7,0.85,0.9,1, Form("#chi^{2}/dof = %f", chi2c),"brNDC");
  t4->Draw();
  // SAVE THE FILE
  cv4.SaveAs(Form("otherPlots/subBkgMj%s_gausexpo.png",key.c_str()));
  cv4.SaveAs(Form("otherPlots/subBkgMj%s_gausexpo.pdf",key.c_str()));
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 

 ////*******************************************************************************
 ////              FINAL BACKGROUND MODEL
 ////******************************************************************************* 

 RooAddPdf model_ext("model_ext","sum of extended models",RooArgList(emodel1,emodel3));
 c1.setConstant(true);
 offset1.setConstant(true);
 width1.setConstant(true);
 mu1.setConstant(true);
 sigma1.setConstant(true);
 mu2.setConstant(true);
 sigma2.setConstant(true);
 funfrac.setConstant(true);
 nbkg1.setConstant(false);
 nbkg2.setConstant(true);

 RooFitResult* erf = model_ext.fitTo(sbObs,Extended(kTRUE),Range("lowerSB,upperSB"),PrintLevel(plevelnorm),Save());
 RooPlot* frame5 = massVhad.frame();
 TCanvas cv5("cv5","cv5",800,800);
 sbObs.plotOn(frame5,Name("data"),Binning(36));
 model_ext.plotOn(frame5,Name("bothMC"),Range("fullRange"),LineColor(kWhite),FillColor(kAzure+6),VLines(),DrawOption("F"));
// model_ext.plotOn(frame5,Name("dominantMC"),Components("emodel1"),FillColor(kYellow+1),VLines(),DrawOption("F"),Range("fullRange"));
 model_ext.plotOn(frame5,Name("subdominantMC"),Components("emodel3"),FillColor(kYellow+1),VLines(),DrawOption("F"),Range("fullRange"),LineColor(kWhite));
// upsigObs.plotOn(frame5,Binning(36),Name("dataupsig"),MarkerColor(kRed));
 frame5->SetMinimum(0.00005 );
 frame5->drawAfter("bothMC","subdominantMC");
 frame5->drawAfter("subdominantMC","data");
 frame5->SetTitle("");


  TText* txt0 = new TText(50,280,"CMS") ;
  txt0->SetTextSize(0.04) ;
  txt0->SetTextColor(kBlack) ;
  txt0->SetTextFont(61);
  frame5->addObject(txt0) ;

  TText* txt1 = new TText(50,265,"Preliminary") ;
  txt1->SetTextSize(0.04) ;
  txt1->SetTextColor(kBlack) ;
  txt1->SetTextFont(52);
  frame5->addObject(txt1) ;


  TText* txt2 = new TText(159,308,"2.307 /fb (13TeV)") ;
  txt2->SetTextSize(0.04) ;
  txt2->SetTextColor(kBlack) ;
  frame5->addObject(txt2) ;


 // the pulls
 RooHist* hpull5 = frame5->pullHist("data","bothMC");
 RooPlot* frame5a = massVhad.frame();
 frame5a->addPlotable(hpull5,"P"); 
 // the pads
 TPad* fPads1d = NULL;
 TPad* fPads2d = NULL;
 fPads1d = new TPad("pad1d", "", 0.00, 0.17, 0.99, 0.99);
 fPads2d = new TPad("pad2d", "", 0.00, 0.04, 0.99, 0.25);
 fPads1d->SetFillColor(0);
 fPads1d->SetLineColor(0);
 fPads2d->SetFillColor(0);
 fPads2d->SetLineColor(0);
 fPads1d->Draw();
 fPads2d->Draw(); 
 // first pad
 fPads1d->cd();
 frame5->GetYaxis()->SetTitleOffset(1.30);
 frame5->GetXaxis()->SetLabelSize(0);
 frame5->GetYaxis()->SetRangeUser(0.00005,300);
 frame5->Draw();
 // The legend
 TLegend *leg1d = new TLegend(0.55,0.55,0.9,0.9);
// leg1d->SetBorderSize(0);
 leg1d->SetHeader(legTitle[key].c_str());
 leg1d->AddEntry("bothMC",  "Dominant MC fit",    "f");
 leg1d->AddEntry("subdominantMC","Subdominant MC fit", "f");
 leg1d->AddEntry("data","data in sidebands", "ep");
// leg1d->AddEntry("dataupsig","data in Higgs region", "ep");
 leg1d->SetTextSize(0.025);
 leg1d->Draw();
 TLegendEntry *header1d = (TLegendEntry*)leg1d->GetListOfPrimitives()->First();
 header1d->SetTextAlign(22);
 header1d->SetTextColor(1);
 header1d->SetTextSize(.05); 
 //Second Pad
 fPads2d->cd();
 fPads2d->SetGridx();
 fPads2d->SetGridy();
 fPads2d->SetTopMargin(0);
 fPads2d->SetBottomMargin(0.4);
 frame5a->GetYaxis()->SetLabelSize(0.08);
 frame5a->GetXaxis()->SetLabelSize(0.17);
 frame5a->GetYaxis()->SetTitle("Pulls");
 frame5a->GetYaxis()->SetTitleOffset(0.30);
 frame5a->GetYaxis()->SetTitleSize(0.15);
 frame5a->GetXaxis()->SetTitleSize(0.17);
 frame5a->GetYaxis()->SetRangeUser(-5,5);
 frame5a->SetTitle("");
 frame5a->Draw();  
 // SAVE THE FILE
 cv5.SaveAs(Form("otherPlots/dataMj%s.png",key.c_str())); 
 cv5.SaveAs(Form("otherPlots/dataMj%s.pdf",key.c_str()));

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
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

  std::cout << "Preparing shapes for mVV bkg distribution" << std::endl;
  RooRealVar s0("s0","slope of the exp0",70.,1.,150);
  RooRealVar s1("s1","slope of the exp1",500.,1.,1000);
  RooRealVar s2("s2","slope of the exp2",500.,1.,1000);
  RooRealVar s3("s3","slope of the exp3", 221.28,  1.,   1000);
  RooRealVar s4("s4","slope of the exp4",  112,  40.,  200);
  RooRealVar s5("s5","slope of the exp2", 100.,    0., 1000.);
  RooRealVar a0("a0","parameter of exp0",3.02632e-02 ,0,0.1);
  RooRealVar a1("a1","parameter of exp1",0.1 ,0.,1.);
  RooRealVar a2("a2","parameter of exp2",-0.00574976 ,-0.1,0.1);
  RooRealVar a3("a3","parameter of exp3", -0.0003,  -0.02,  0.02);
  RooRealVar a4("a4","parameter of exp4",  0.0263154,   0,   0.06);
  RooRealVar a5("a5","parameter of exp2",0.1,0.000001 ,   1.);
  a3.setConstant(true);

  RooExpTailPdf       nsBkg_pdf("nsBkg_pdf", "fit bkg  in nominal  reg",   candTMass,s0,a0);
  RooExpTailPdf       nsBkg_pdfa("nsBkg_pdfa", "fit bkg  in nominal  rega",   candTMass,s0,a0);
  RooExpTailPdf       sbBkg_pdf("sbBkg_pdf", "fit bkg  in sideband reg",   candTMass,s1,a1);
  RooExpTailPdf       sbDom_pdf("sbDom_pdf",   "fit Dom in sideband reg",     candTMass,s2,a2);
  RooExpTailPdf       sbDom_pdfa("sbDom_pdfa",   "fit Dom in sideband rega",     candTMass,s2,a2);
  RooExpTailPdf       sbSub_pdf("sbSub_pdf", "sub bkg in sideband reg",   candTMass,s3,a3);
  RooExpTailPdf       sbSub_pdfa("sbSub_pdfa", "sub bkg in sideband rega",   candTMass,s3,a3);
  RooExpTailPdf       nsSub_pdf("nsSub_pdf", "sub bkg in nominal  reg",   candTMass,s4,a4);
  RooExpTailPdf       nsSub_pdfa("nsSub_pdfa", "sub bkg in nominal  rega",   candTMass,s4,a4);
  RooExpTailPdf       sbObs_pdf("sbObs_pdf", "fit data in sideband region",   candTMass,s5,a5);
  RooExpTailPdf       sbObs_pdfa("sbObs_pdfa", "fit data in sideband region",   candTMass,s5,a5);
  RooAlpha4ExpTailPdf alpha_pdf("alpha_pdf", "alpha ratio",                   candTMass,s0,a0,s1,a1);

//--------------------------------------------------------------------------------------
//             NEW PDF ExpN
//--------------------------------------------------------------------------------------
  RooRealVar k0("k0","parameter of expN0",  0.03,   0.001,   0.1); 
  RooRealVar n0("n0","parameter of expN1",  0.03,   0.001,   0.1); 
  RooRealVar k1("k1","parameter of expN1",  0.03,   0.001,   0.1);
  RooRealVar n1("n1","parameter of expN1",  0.03,   0.001,   0.1);
  RooRealVar k2("k2","parameter of expN2",  0.03,   0.001,   0.1);
  RooRealVar n2("n2","parameter of expN2",  0.03,   0.001,   0.1);
  RooRealVar k3("k3","parameter of expN3",  0.03,   0.001,   0.1);
  RooRealVar n3("n3","parameter of expN3",  0.03,   0.001,   0.1);
  RooRealVar k4("k4","parameter of expN4",  4.49,     0,  100);
  RooRealVar n4("n4","parameter of expN4",  0.022,   0,   1);
  RooExpNPdf          nsBkg_pdf1("nsBkg_pdf1", "fit bkg  in nominal  reg",   candTMass,k0,n0);
  RooExpNPdf          sbBkg_pdf1("sbBkg_pdf1", "fit bkg  in sideband reg",   candTMass,k1,n1);
  RooExpNPdf          sbDom_pdf1("sbDom_pdf1", "dom bkg  in sideband reg",   candTMass,k2,n2);
  RooExpNPdf          sbSub_pdf1("sbSub_pdf1", "sub bkg in sideband reg",   candTMass,k3,n4);
  RooExpNPdf          nsSub_pdf1("nsSub_pdf1", "sub bkg in nominal  reg",   candTMass,k4,n4);
  RooAlpha4ExpNPdf alpha_pdf1("alpha_pdf1", "alpha ratio",                   candTMass,k0,n0,k1,n1);
//-------------------------------------------------------------------------------------------

/*


   //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
   // STEP 0: fit the subdominant backgrounds in signal region
   //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
   cout << "Fitting subdominant backgrounds in total signal region" << endl;
   // We define a dataset to use the subdominant backgrounds in total signal region (lower + upper) 
   RooDataSet NSsubBkg("NSsubBkg", "NSsubBkg", variables, Cut(lowerSIG or upperSIG),  WeightVar(totalWeight), Import(treeMC2));
   // we have to normalize? include the yields? before fit
   RooFitResult *rf1MT  = nsSub_pdf.fitTo(NSsubBkg,Save(),SumW2Error(kTRUE),PrintLevel(plevelshap));
   RooFitResult *rf1MTa = nsSub_pdfa.fitTo(NSsubBkg,Save(),SumW2Error(kTRUE),PrintLevel(plevelshap));
   s4.Print();
   a4.Print();
   RooPlot* MVZframe = candTMass.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
   NSsubBkg.plotOn(MVZframe,Name("Submc"),DrawOption("ep"),Binning(58),Range("fullRange"));
   nsSub_pdf.plotOn(MVZframe,Name("fitSubMVZ"),LineColor(kRed),Range("fullRange"));
   nsSub_pdfa.plotOn(MVZframe,Name("fitSubMVZerror"),VisualizeError(*rf1MTa,1),FillColor(kBlue), FillStyle(3002),Range("fullRange"));
   nsSub_pdf.paramOn(MVZframe,Layout(0.45,0.9,0.6));
   MVZframe->drawAfter("fitSubMVZerror","Submc");
   MVZframe->drawAfter("fitSubMVZerror","fitSubMVZ");
   MVZframe->getAttText()->SetTextSize(0.03);

   TCanvas* canvasMVZ1 = new TCanvas("MVZ1","MVZ1",800,800);
   // the pulls
   RooHist* hpullMT1 = MVZframe->pullHist();
   RooPlot* MVZframe1 = candTMass.frame(Range("fullRange"));
   MVZframe1->addPlotable(hpullMT1,"P");
   // chi square
   Double_t chi2MV1 = MVZframe->chiSquare("fitSubMVZ", "Submc", 2);
   // The pads
   TPad* fPadsMT1a = NULL;
   TPad* fPadsMT1b = NULL;
   fPadsMT1a = new TPad("padMT1a", "", 0.00, 0.15, 0.99, 0.99);
   fPadsMT1b = new TPad("padMT1b", "", 0.00, 0.05, 0.99, 0.225);
   fPadsMT1a->SetFillColor(0);
   fPadsMT1a->SetLineColor(0);
   fPadsMT1b->SetFillColor(0);
   fPadsMT1b->SetLineColor(0);
   fPadsMT1a->Draw();
   fPadsMT1b->Draw();
   // First pad
   fPadsMT1a->cd();
   fPadsMT1a->SetLogy();
   MVZframe->GetYaxis()->SetTitleOffset(1.30);
   MVZframe->GetXaxis()->SetLabelSize(0);
   MVZframe->SetMinimum(0.001);
   MVZframe->Draw();

   char result[100];
   strcpy(result,legTitle[key].c_str());
   strcat(result," - Signal Region");

   // The legend
   TLegend *legMT1 = new TLegend(0.45,0.6,0.9,0.9);
   legMT1->SetHeader(result);
   legMT1->AddEntry("Submc",  "Subdominant Background ",    "ep");
   legMT1->AddEntry("fitSubMVZ","ExpoTail Background Fit", "l");
   legMT1->SetTextSize(0.03);
   legMT1->Draw();
   TLegendEntry *headerMT1 = (TLegendEntry*)legMT1->GetListOfPrimitives()->First();
   headerMT1->SetTextAlign(22);
   headerMT1->SetTextColor(1);
   headerMT1->SetTextSize(.045);
  
   // second pad
   fPadsMT1b->cd();
   fPadsMT1b->SetGridx();
   fPadsMT1b->SetGridy();
   MVZframe1->GetYaxis()->SetLabelSize(0.08);
   MVZframe1->GetXaxis()->SetLabelSize(0.17);
   MVZframe1->GetYaxis()->SetTitle("Pulls");
   MVZframe1->GetYaxis()->SetTitleOffset(0.30);
   MVZframe1->GetYaxis()->SetTitleSize(0.15);
   MVZframe1->GetXaxis()->SetTitleSize(0.17);
   MVZframe1->GetXaxis()->SetTitle("M_{T} (GeV)");
   MVZframe1->GetYaxis()->SetRangeUser(-5,5);
   MVZframe1->SetTitle("");
   MVZframe1->Draw();
   TPaveLabel *MT1 = new TPaveLabel(0.7,0.7,0.9,0.9, Form("#chi^{2}/dof = %f", chi2MV1),"brNDC");
   MT1->Draw();

   // Save File
   canvasMVZ1->SaveAs(Form("otherPlots/nsSub_MVZ%s.png",key.c_str()));


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  // STEP 1: fit the subdominant backgrounds in sideband region
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


  cout << "Fitting subdominant backgrounds in total sideband region" << endl;
  RooDataSet SBsubBkg("SBsubBkg", "SBsubBkg", variables, Cut(allSB), WeightVar(totalWeight), Import(treeMC2));
  RooFitResult *rf2MT  = sbSub_pdf.fitTo(SBsubBkg,Save(),SumW2Error(kTRUE),PrintLevel(plevelshap));
  RooFitResult *rf2MTa = sbSub_pdfa.fitTo(SBsubBkg,Save(),SumW2Error(kTRUE),PrintLevel(plevelshap));
  s3.Print();
  a3.Print();


   RooPlot* Frame2 = candTMass.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
   SBsubBkg.plotOn(Frame2,Name("Submc2"),DrawOption("ep"),Binning(58),Range("fullRange"));
   sbSub_pdf.plotOn(Frame2,Name("fitSubMVZ2"),LineColor(kRed),Range("fullRange"));
   sbSub_pdfa.plotOn(Frame2,Name("fitSubMVZerror2"),VisualizeError(*rf2MTa,1),FillColor(kBlue), FillStyle(3002),Range("fullRange"));

   a3.setConstant(false);

   sbSub_pdf.paramOn(Frame2,Layout(0.40,0.9,0.6));
   Frame2->drawAfter("fitSubMVZerror2","Submc2");
   Frame2->drawAfter("fitSubMVZerror2","fitSubMVZ2");
   Frame2->getAttText()->SetTextSize(0.03);


   TCanvas* canvasMVZ2 = new TCanvas("MVZ2","MVZ2",800,800);

   RooHist* hpullMT2 = Frame2->pullHist();
   RooPlot* Frame2pull = candTMass.frame(Range("fullRange"));
   Frame2pull->addPlotable(hpullMT2,"P");

   Double_t chi2MV2 = Frame2->chiSquare("fitSubMVZ2", "Submc2", 2);

   TPad* fPadsMT2a = NULL;
   TPad* fPadsMT2b = NULL;
   fPadsMT2a = new TPad("padMT2a", "", 0.00, 0.15, 0.99, 0.99);
   fPadsMT2b = new TPad("padMT2b", "", 0.00, 0.05, 0.99, 0.225);
   fPadsMT2a->SetFillColor(0);
   fPadsMT2a->SetLineColor(0);
   fPadsMT2b->SetFillColor(0);
   fPadsMT2b->SetLineColor(0);
   fPadsMT2a->Draw();
   fPadsMT2b->Draw();

   fPadsMT2a->cd();
   fPadsMT2a->SetLogy();
   Frame2->GetYaxis()->SetTitleOffset(1.30);
   Frame2->GetXaxis()->SetLabelSize(0);
   Frame2->SetMinimum(0.001);
   Frame2->Draw();

   char result2[100];
   strcpy(result2,legTitle[key].c_str());
   strcat(result2," - Sideband Region");

   TLegend *legMT2 = new TLegend(0.40,0.6,0.9,0.9);
   legMT2->SetHeader(result2);
   legMT2->AddEntry("Submc2",  "Subdominant Background ",    "ep");
   legMT2->AddEntry("fitSubMVZ2","ExpoTail Background Fit", "l");
   legMT2->SetTextSize(0.03);
   legMT2->Draw();
   TLegendEntry *headerMT2 = (TLegendEntry*)legMT2->GetListOfPrimitives()->First();
   headerMT2->SetTextAlign(22);
   headerMT2->SetTextColor(1);
   headerMT2->SetTextSize(.045);

   fPadsMT2b->cd();
   fPadsMT2b->SetGridx();
   fPadsMT2b->SetGridy();
   Frame2pull->GetYaxis()->SetLabelSize(0.08);
   Frame2pull->GetXaxis()->SetLabelSize(0.17);
   Frame2pull->GetYaxis()->SetTitle("Pulls");
   Frame2pull->GetYaxis()->SetTitleOffset(0.30);
   Frame2pull->GetYaxis()->SetTitleSize(0.15);
   Frame2pull->GetXaxis()->SetTitleSize(0.17);
   Frame2pull->GetXaxis()->SetTitle("M_{T} (GeV)");
   Frame2pull->GetYaxis()->SetRangeUser(-5,5);
   Frame2pull->SetTitle("");
   Frame2pull->Draw();
   TPaveLabel *MT2 = new TPaveLabel(0.7,0.7,0.9,0.9, Form("#chi^{2}/dof = %f", chi2MV2),"brNDC");
   MT2->Draw();

   canvasMVZ2->SaveAs(Form("otherPlots/sbSub_MVZ%s.png",key.c_str()));


   //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
   // STEP 2: Fit the dominant background in sideband region
   //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



   cout << "Fitting dominant backgrounds in total sideband region" << endl;
   RooDataSet SBdomBkg("SBdomBkg", "SBdomBkg", variables, Cut(allSB), WeightVar(totalWeight), Import(treeMC1));
   RooFitResult *rf3MT  = sbDom_pdf.fitTo(SBdomBkg,Save(),SumW2Error(kTRUE),PrintLevel(plevelshapDom));
   RooFitResult *rf3MTa = sbDom_pdfa.fitTo(SBdomBkg,Save(),SumW2Error(kTRUE),PrintLevel(plevelshap));
   s2.Print();
   a2.Print();
   RooPlot* Frame3 = candTMass.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
   SBdomBkg.plotOn(Frame3,Name("DomMC1"),DrawOption("ep"),Binning(58),Range("fullRange"));
   sbDom_pdf.plotOn(Frame3,Name("fitDomMVZ1"),LineColor(kGreen+2),Range("fullRange"));
   sbDom_pdfa.plotOn(Frame3,Name("fitDomMVZerror1"),VisualizeError(*rf3MTa,1),FillColor(kBlue), FillStyle(3002),Range("fullRange"));
   sbDom_pdf.paramOn(Frame3,Layout(0.5,0.9,0.6));
   Frame3->drawAfter("fitDomMVZerror1","DomMC1");
   Frame3->drawAfter("fitDomMVZerror1","fitDomMVZ1");
   Frame3->getAttText()->SetTextSize(0.03);

 
   TCanvas* canvasMVZ3 = new TCanvas("MVZ3","MVZ3",800,800);
   
   RooHist* hpullMT3 = Frame3->pullHist();
   RooPlot* Frame3pull = candTMass.frame(Range("fullRange"));
   Frame3pull->addPlotable(hpullMT3,"P");

   Double_t chi2MV3 = Frame3->chiSquare("fitDomMVZ1", "DomMC1", 2);

   TPad* fPadsMT3a = NULL;
   TPad* fPadsMT3b = NULL;
   fPadsMT3a = new TPad("padMT3a", "", 0.00, 0.15, 0.99, 0.99);
   fPadsMT3b = new TPad("padMT3b", "", 0.00, 0.05, 0.99, 0.225);
   fPadsMT3a->SetFillColor(0);
   fPadsMT3a->SetLineColor(0);
   fPadsMT3b->SetFillColor(0);
   fPadsMT3b->SetLineColor(0);
   fPadsMT3a->Draw();
   fPadsMT3b->Draw();

   fPadsMT3a->cd();
   fPadsMT3a->SetLogy();
   Frame3->GetYaxis()->SetTitleOffset(1.30);
   Frame3->GetXaxis()->SetLabelSize(0);
   Frame3->SetMinimum(0.001);
   Frame3->Draw();

   char result3[100];
   strcpy(result3,legTitle[key].c_str());
   strcat(result3," - Sideband Region");

   TLegend *legMT3 = new TLegend(0.50,0.6,0.9,0.9);
   legMT3->SetHeader(result3);
   legMT3->AddEntry("DomMC1",  "Dominant Background ",    "ep");
   legMT3->AddEntry("fitDomMVZ1","ExpoTail Background Fit", "l");
   legMT3->SetTextSize(0.03);
   legMT3->Draw();
   TLegendEntry *headerMT3 = (TLegendEntry*)legMT3->GetListOfPrimitives()->First();
   headerMT3->SetTextAlign(22);
   headerMT3->SetTextColor(1);
   headerMT3->SetTextSize(.035);

   fPadsMT3b->cd();
   fPadsMT3b->SetGridx();
   fPadsMT3b->SetGridy();
   Frame3pull->GetYaxis()->SetLabelSize(0.08);
   Frame3pull->GetXaxis()->SetLabelSize(0.17);
   Frame3pull->GetYaxis()->SetTitle("Pulls");
   Frame3pull->GetYaxis()->SetTitleOffset(0.30);
   Frame3pull->GetYaxis()->SetTitleSize(0.15);
   Frame3pull->GetXaxis()->SetTitleSize(0.17);
   Frame3pull->GetXaxis()->SetTitle("M_{T} (GeV)");
   Frame3pull->GetYaxis()->SetRangeUser(-5,5);
   Frame3pull->SetTitle("");
   Frame3pull->Draw();
   TPaveLabel *MT3 = new TPaveLabel(0.7,0.7,0.9,0.9, Form("#chi^{2}/dof = %f", chi2MV3),"brNDC");
   MT3->Draw();

   canvasMVZ3->SaveAs(Form("otherPlots/sbDom_MVZ%s.png",key.c_str()));


     //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
     //   // STEP 3: Fit the dominant background in signal region
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


   cout << "Fitting dominant backgrounds in total signal region" << endl;
   RooDataSet SigdomBkg("SigdomBkg", "SigdomBkg", variables, Cut(lowerSIG), WeightVar(totalWeight), Import(treeMC1));
   RooFitResult *rf4MT  = nsBkg_pdf.fitTo(SigdomBkg,Save(),SumW2Error(kTRUE),PrintLevel(plevelshapDom));
   RooFitResult *rf4MTa = nsBkg_pdfa.fitTo(SigdomBkg,Save(),SumW2Error(kTRUE),PrintLevel(plevelshap));
   s0.Print();
   a0.Print();
   RooPlot* Frame4 = candTMass.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
   SigdomBkg.plotOn(Frame4,Name("DomMC1sig"),DrawOption("ep"),Binning(58),Range("fullRange"));
   nsBkg_pdf.plotOn(Frame4,Name("fitDomMC1MVZsig"),LineColor(kGreen+2),Range("fullRange"));
   nsBkg_pdfa.plotOn(Frame4,Name("fitDomMC1MVZerrorsig"),VisualizeError(*rf4MTa,1),FillColor(kBlue), FillStyle(3002),Range("fullRange"));
   nsBkg_pdf.paramOn(Frame4,Layout(0.50,0.9,0.6));
   Frame4->drawAfter("fitDomMC1MVZerrorsig","DomMC1sig");
   Frame4->drawAfter("fitDomMC1MVZerrorsig","fitDomMC1MVZsig");
   Frame4->getAttText()->SetTextSize(0.03);




   TCanvas* canvasMVZ4 = new TCanvas("MVZ4","MVZ4",800,800);

   RooHist* hpullMT4 = Frame4->pullHist();
   RooPlot* Frame4pull = candTMass.frame(Range("fullRange"));
   Frame4pull->addPlotable(hpullMT4,"P");

   Double_t chi2MV4 = Frame4->chiSquare("fitDomMC1MVZsig", "DomMC1sig", 2);

   TPad* fPadsMT4a = NULL;
   TPad* fPadsMT4b = NULL;
   fPadsMT4a = new TPad("padMT4a", "", 0.00, 0.15, 0.99, 0.99);
   fPadsMT4b = new TPad("padMT4b", "", 0.00, 0.05, 0.99, 0.225);
   fPadsMT4a->SetFillColor(0);
   fPadsMT4a->SetLineColor(0);
   fPadsMT4b->SetFillColor(0);
   fPadsMT4b->SetLineColor(0);
   fPadsMT4a->Draw();
   fPadsMT4b->Draw();

   fPadsMT4a->cd();
   fPadsMT4a->SetLogy();
   Frame4->GetYaxis()->SetTitleOffset(1.30);
   Frame4->GetXaxis()->SetLabelSize(0);
   Frame4->SetMinimum(0.001);
   Frame4->Draw();

   char result4[100];
   strcpy(result4,legTitle[key].c_str());
   strcat(result4," - Signal Region");

   TLegend *legMT4 = new TLegend(0.50,0.6,0.9,0.9);
   legMT4->SetHeader(result4);
   legMT4->AddEntry("DomMC1sig",  "Dominant Background ",    "ep");
   legMT4->AddEntry("fitDomMC1MVZsig","ExpoTail Background Fit", "l");
   legMT4->SetTextSize(0.03);
   legMT4->Draw();
   TLegendEntry *headerMT4 = (TLegendEntry*)legMT4->GetListOfPrimitives()->First();
   headerMT4->SetTextAlign(22);
   headerMT4->SetTextColor(1);
   headerMT4->SetTextSize(.035);

   fPadsMT4b->cd();
   fPadsMT4b->SetGridx();
   fPadsMT4b->SetGridy();
   Frame4pull->GetYaxis()->SetLabelSize(0.08);
   Frame4pull->GetXaxis()->SetLabelSize(0.17);
   Frame4pull->GetYaxis()->SetTitle("Pulls");
   Frame4pull->GetYaxis()->SetTitleOffset(0.30);
   Frame4pull->GetYaxis()->SetTitleSize(0.15);
   Frame4pull->GetXaxis()->SetTitleSize(0.17);
   Frame4pull->GetXaxis()->SetTitle("M_{T} (GeV)");
   Frame4pull->GetYaxis()->SetRangeUser(-5,5);
   Frame4pull->SetTitle("");
   Frame4pull->Draw();
   TPaveLabel *MT4 = new TPaveLabel(0.7,0.7,0.9,0.9, Form("#chi^{2}/dof = %f", chi2MV4),"brNDC");
   MT4->Draw();

   canvasMVZ4->SaveAs(Form("otherPlots/sigDom_MVZ%s.png",key.c_str()));


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  // STEP 4: Fit data in sideband region
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
*/
  
   cout << "Fitting signal in sideband region" << endl;
   RooDataSet DataSB("DataSB", "DataSB", variables, Cut(allSB), WeightVar(totalWeight), Import(treeData));
   RooFitResult *rf5MT  = sbObs_pdf.fitTo(DataSB,Save(),SumW2Error(kTRUE),PrintLevel(plevelshapDom));
   RooFitResult *rf5MTa = sbObs_pdfa.fitTo(DataSB,Save(),SumW2Error(kTRUE),PrintLevel(plevelshap));
   s5.Print();
   a5.Print();
   RooPlot* plot5 = candTMass.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
   DataSB.plotOn(plot5,Name("datasb"),DrawOption("ep"),Binning(58),Range("fullRange"));
   sbObs_pdf.plotOn(plot5,Name("fitdatsb"),LineColor(kGreen+2),Range("fullRange"));
   sbObs_pdfa.plotOn(plot5,Name("fitdatasberror"),VisualizeError(*rf5MTa,1),FillColor(kBlue), FillStyle(3002),Range("fullRange"));
   sbObs_pdf.paramOn(plot5,Layout(0.50,0.9,0.6));
   plot5->drawAfter("fitdatasberror","datasb");
   plot5->drawAfter("fitdatasberror","fitdatasb");
   plot5->getAttText()->SetTextSize(0.03);




   TCanvas* canvasMVZ5 = new TCanvas("MVZ5","MVZ5",800,800);

   RooHist* hpullMT5 = plot5->pullHist();
   RooPlot* Frame5pull = candTMass.frame(Range("fullRange"));
   Frame5pull->addPlotable(hpullMT5,"P");

   Double_t chi2MV5 =plot5->chiSquare("fitdatasb", "datasb", 2);

   TPad* fPadsMT5a = NULL;
   TPad* fPadsMT5b = NULL;
   fPadsMT5a = new TPad("padMT5a", "", 0.00, 0.15, 0.99, 0.99);
   fPadsMT5b = new TPad("padMT5b", "", 0.00, 0.05, 0.99, 0.225);
   fPadsMT5a->SetFillColor(0);
   fPadsMT5a->SetLineColor(0);
   fPadsMT5b->SetFillColor(0);
   fPadsMT5b->SetLineColor(0);
   fPadsMT5a->Draw();
   fPadsMT5b->Draw();

   fPadsMT5a->cd();
   fPadsMT5a->SetLogy();
   plot5->GetYaxis()->SetTitleOffset(1.30);
   plot5->GetXaxis()->SetLabelSize(0);
   plot5->SetMinimum(0.001);
   plot5->SetMaximum(1000); 
   plot5->Draw();

   char result5[100];
   strcpy(result5,legTitle[key].c_str());
   strcat(result5," - Data in SB");

   TLegend *legMT5 = new TLegend(0.50,0.6,0.9,0.9);
   legMT5->SetHeader(result5);
   legMT5->AddEntry("datasb",  "Data in SB ",    "ep");
   legMT5->AddEntry("fitdatasb","ExpoTail Background Fit", "l");
   legMT5->SetTextSize(0.03);
   legMT5->Draw();
   TLegendEntry *headerMT5 = (TLegendEntry*)legMT5->GetListOfPrimitives()->First();
   headerMT5->SetTextAlign(22);
   headerMT5->SetTextColor(1);
   headerMT5->SetTextSize(.035);

   fPadsMT5b->cd();
   fPadsMT5b->SetGridx();
   fPadsMT5b->SetGridy();
   Frame5pull->GetYaxis()->SetLabelSize(0.08);
   Frame5pull->GetXaxis()->SetLabelSize(0.17);
   Frame5pull->GetYaxis()->SetTitle("Pulls");
   Frame5pull->GetYaxis()->SetTitleOffset(0.30);
   Frame5pull->GetYaxis()->SetTitleSize(0.15);
   Frame5pull->GetXaxis()->SetTitleSize(0.17);
   Frame5pull->GetXaxis()->SetTitle("M_{T} (GeV)");
   Frame5pull->GetYaxis()->SetRangeUser(-5,5);
   Frame5pull->SetTitle("");
   Frame5pull->Draw();
   TPaveLabel *MT5 = new TPaveLabel(0.7,0.7,0.9,0.9, Form("#chi^{2}/dof = %f", chi2MV5),"brNDC");
   MT5->Draw();

   canvasMVZ5->SaveAs(Form("otherPlots/dataSB_MVZ%s.png",key.c_str()));


}
