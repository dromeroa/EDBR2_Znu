
// FROM 25/07/2016
// FIT FOR DOMINANT AND SUBDOMINANT OF THE PRUNED MASS FOR LP 
//
// FROM /afs/cern.ch/work/d/dromeroa/private/ALPHAMETHOD_Enero25/CMSSW_8_0_0_pre5/src/ALPHA_METHOD/TESTNEWCODE
// Do : >cmsenv
// root[] gSystem->Load("../PDFs/HWWLVJRooPdfs_cxx.so")
// root[] .x fitPrunedLP.C("LP")

#include "TMath.h"
#include "string.h"

void fitPrunedLP(std::string key)
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
  RooRealVar candTMass("candTMass","M_{VZ}",            600.,  2000., "GeV");
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


      treeData.Add(     "../trees/newtreesPAS/treeEDBR_MET_Run2015C_25ns_16Dec2015_v1.root"         );
      treeData.Add(     "../trees/newtreesPAS/treeEDBR_MET_Run2015D_16Dec2015_v1.root"              );
      treeMC2.Add(      "../trees/newtreesPAS/treeEDBR_QCD_76x_v2.root"                             );
      treeMC2.Add(      "../trees/newtreesPAS/treeEDBR_QCD_HT1000to1500_76x_v2.root"                );
      treeMC2.Add(      "../trees/newtreesPAS/treeEDBR_QCD_HT1500to2000_76x_v2.root"                );
      treeMC2.Add(      "../trees/newtreesPAS/treeEDBR_QCD_HT700to1000_76x_v2.root"                  );
      treeMC2.Add(      "../trees/newtreesPAS/treeEDBR_TTbar_76x_v2.root"                            );
      treeMC2.Add(      "../trees/newtreesPAS/treeEDBR_TTJets_reg_76x_v2.root"                        );
      treeMC2.Add(      "../trees/newtreesPAS/treeEDBR_VV_76x_v2.root"                                );
      treeMC2.Add(      "../trees/newtreesPAS/treeEDBR_WW_76x_v2.root"                                );
      treeMC2.Add(      "../trees/newtreesPAS/treeEDBR_WZ_76x_v2.root"                                );
      treeMC1.Add(      "../trees/newtreesPAS/treeEDBR_Z+Jets_76x_v2.root"                            );
      treeMC1.Add(      "../trees/newtreesPAS/treeEDBR_ZJetsToNuNu_HT-100To200_76x_v2.root"           );
      treeMC1.Add(      "../trees/newtreesPAS/treeEDBR_ZJetsToNuNu_HT-200To400_76x_v2.root"           );
      treeMC1.Add(      "../trees/newtreesPAS/treeEDBR_ZJetsToNuNu_HT-400To600_76x_v2.root"           );
      treeMC1.Add(      "../trees/newtreesPAS/treeEDBR_W+Jets_76x_v2.root"                            );
      treeMC1.Add(      "../trees/newtreesPAS/treeEDBR_WJetsToLNu_HT-100To200_76x_v2.root"            );
      treeMC1.Add(      "../trees/newtreesPAS/treeEDBR_WJetsToLNu_HT-200To400_76x_v2.root"            );
      treeMC1.Add(      "../trees/newtreesPAS/treeEDBR_WJetsToLNu_HT-400To600_76x_v2.root"            );



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

  RooFitResult *rf2 = emodel2.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf2a = emodel2a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));

  RooFitResult *rf3 = emodel3.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf3a = emodel3a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));

  RooFitResult *rf4 = emodel4.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf4a = emodel4a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));

 
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


  TText* txt2a = new TText(160,269,"2.318 /fb (13TeV)") ;
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
   RooBinning xbins(36,40,220);
  

  // 2. SUBDOMINANT BACKGROUND (erf*exp)
  RooPlot* frame2 = massVhad.frame();
  bkg2.plotOn(frame2,Name("mc2"),Binning(xbins));
  model2.plotOn(frame2,Name("fitmc2"), LineColor(kRed));
  model2a.plotOn(frame2,Name("error2"),VisualizeError(*rf2a,1),FillColor(kAzure-2), FillStyle(3002));

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


  TText* tx3 = new TText(161,27,"2.318 /fb (13TeV)") ;
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
  bkg2.plotOn(frame3,Name("mc3"),Binning(xbins));
  model3.plotOn(frame3,Name("fitmc3"), LineColor(kRed));
  model3a.plotOn(frame3,Name("error3"),VisualizeError(*rf3a,1),FillColor(kAzure-2), FillStyle(3002));

  model3.paramOn(frame3,Layout(0.55,0.9,0.75));
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


  TText* tx6 = new TText(159,27,"2.318 /fb (13TeV)") ;
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
  TLegend *leg1b = new TLegend(0.55,0.75,0.9,0.9);
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
 model_ext.plotOn(frame5,Name("subdominantMC"),Components("emodel3"),FillColor(kYellow+1),VLines(),DrawOption("F"),Range("fullRange"),LineColor(kWhite));
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


  TText* txt2 = new TText(159,307,"2.318 /fb (13TeV)") ;
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

}
