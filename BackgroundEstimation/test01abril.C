
// CHECKING THE CODE
// FIRST TRY FROM 03/04/2016
// FOR ERFEXP IN THE SUBDOMINANT
//
// FROM /afs/cern.ch/work/d/dromeroa/private/ALPHAMETHOD_Enero25/CMSSW_8_0_0_pre5/src/ALPHA_METHOD/TESTNEWCODE
// Do : >cmsenv
// root[] gSystem->Load("../PDFs/HWWLVJRooPdfs_cxx.so")
// root[] .x test01abril.C("HP")



void test01abril(std::string key)
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
  int plevelnorm = 1;
  int plevelshap = 1;
  // Silent RooFit
  RooMsgService::instance().setGlobalKillBelow(FATAL);
  ////**************************************************


  ////*********************************************************************
  //// 2. INTRODUCE THE VARIABLES
  ////*********************************************************************
  RooRealVar candTMass("candTMass","M_{VZ}",            600.,  3000., "GeV");
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

      treeData.Add(     "../trees/treeEDBR_MET_Run2015D_05Oct2015.root"                  );
      treeData.Add(     "../trees/treeEDBR_MET_Run2015D_v4.root"                         );
      treeMC2.Add(      "../trees/treeEDBR_QCD_25ns_v2.root"                             );
      treeMC2.Add(      "../trees/treeEDBR_QCD_HT1000to1500_25ns_v2.root"                );
      treeMC2.Add(      "../trees/treeEDBR_QCD_HT1500to2000_25ns_v2.root"                );
      treeMC2.Add(      "../trees/treeEDBR_QCD_HT300to500_25ns_v2.root"                  );
      treeMC2.Add(      "../trees/treeEDBR_QCD_HT500to700_25ns_v2.root"                  );
      treeMC2.Add(      "../trees/treeEDBR_QCD_HT700to1000_25ns_v2.root"                 );
      treeMC2.Add(      "../trees/treeEDBR_TTbar_25ns_v2.root"                           );
      treeMC2.Add(      "../trees/treeEDBR_VV_25ns_v2.root"                              );
      treeMC2.Add(      "../trees/treeEDBR_WW_25ns_v2.root"                              );
      treeMC2.Add(      "../trees/treeEDBR_ZZ_25ns_v2.root"                              );
      treeMC1.Add(      "../trees/treeEDBR_W+Jets_25ns_v2.root"                          );
      treeMC1.Add(      "../trees/treeEDBR_WJetsToLNu_HT-100To200_25ns_v2.root"          );
      treeMC1.Add(      "../trees/treeEDBR_WJetsToLNu_HT-200To400_25ns_v2.root"          );
      treeMC1.Add(      "../trees/treeEDBR_WJetsToLNu_HT-400To600_25ns_v2.root"          );
      treeMC1.Add(      "../trees/treeEDBR_Z+Jets_25ns_v2.root"                          );
      treeMC1.Add(      "../trees/treeEDBR_ZJetsToNuNu_HT-100To200_25ns_v2.root"         );
      treeMC1.Add(      "../trees/treeEDBR_ZJetsToNuNu_HT-200To400_25ns_v2.root"         );
      treeMC1.Add(      "../trees/treeEDBR_ZJetsToNuNu_HT-400To600_25ns_v2.root"         );
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
  RooDataSet bkg1("bkg1", "bkg1", variables, Cut(selectedCategory), WeightVar(totalWeight), Import(treeMC1));
  // Subdominant background
  RooDataSet bkg2("bkg2", "bkg2", variables, Cut(selectedCategory), WeightVar(totalWeight), Import(treeMC2));
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

  // Dominant Background (Error Function * Exponential = ErfExp)
  RooRealVar c1("c1","slope of the exp",             -0.032,  -1.,    0.);
  RooRealVar offset1("offset1","offset of the erf",    85.0,   1.,  150.);
  RooRealVar width1("width1",  "width of the erf",     36.0,   1,   100.);
  
  // Subdominant Background
  // ErfExp 
  RooRealVar c2("c2","slope of the exp",             -0.040,  -1.,    0.);
  RooRealVar offset2("offset2","offset of the erf",    79.0,   1.,  150.);
  RooRealVar width2("width2",  "width of the erf",     17.0,   1,   100.);
  // Gaus 2
  RooRealVar mu1("mu1", "average", 90, 0, 200);
  RooRealVar sigma1("sigma1", "sigma", 20, 0, 100);
  RooRealVar mu2("mu2", "average", 90, 0, 200);
  RooRealVar sigma2("sigma2", "sigma", 20, 0, 100); 
  RooGaussian gauss1("gauss1","gaussian PDF1", massVhad, mu1, sigma1);
  RooGaussian gauss2("gauss2","gaussian PDF2", massVhad, mu2, sigma2);
  RooRealVar funfrac("funfrac","fraction of functions",0.6,0.,1.);



  RooErfExpPdf model1("model1","dominant backgrounds",massVhad,c1,offset1,width1);
  // to plot the error
  RooErfExpPdf model1a("model1a","dominant backgroundsa",massVhad,c1,offset1,width1);
  RooErfExpPdf model2("model2","subdom backgrounds",massVhad,c2,offset2,width2);
  // to plot the error
  RooErfExpPdf model2a("model2a","subdom backgroundsa",massVhad,c2,offset2,width2);
  RooAddPdf model3("Gaus2", "gaussian plus gaussian", RooArgList(gauss1, gauss2), funfrac);
  RooAddPdf model3a("Gaus2a", "gaussian plus gaussiana", RooArgList(gauss1, gauss2), funfrac);


  // A command to add a normalization to the PDF
  RooExtendPdf emodel1("emodel1","extended dom backgrounds",model1,nbkg1);
  RooExtendPdf emodel1a("emodel1a","extended dom backgroundsa",model1a,nbkg1);
  RooExtendPdf emodel2("emodel2","extended sub backgrounds",model2,nbkg2);
  RooExtendPdf emodel2a("emodel2a","extended sub backgrounds",model2a,nbkg2);
  RooExtendPdf emodel3("emodel3","extended sub backgrounds",model3,nbkg2);
  RooExtendPdf emodel3a("emodel3a","extended sub backgrounds",model3a,nbkg2);

  // The fit of each background in all range separatly
  std::cout << "Fitting models - normalisation" << std::endl;
  RooFitResult *rf1 = emodel1.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf1a = emodel1a.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf2 = emodel2.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf2a = emodel2a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf3 = emodel3.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf3a = emodel3a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));

  
  //*****************************************************************
  //                     PLOTS FOR THE BACKGROUNDS AND FITS
  //****************************************************************

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /// 1. DOMINANT BACKGROUND
  RooPlot* frame1 = massVhad.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
  // Dominant backgrounds
  bkg1.plotOn(frame1,Name("mc1"), DrawOption("ep"),Binning(36));
  model1.plotOn(frame1,Name("fitmc1"),LineColor(kBlue));
  model1a.plotOn(frame1,Name("error"),VisualizeError(*rf1a,1),FillColor(kAzure-2), FillStyle(3002));  
  model1.paramOn(frame1,Layout(0.55,0.9,0.6));
  frame1->drawAfter("error","mc1");
  frame1->drawAfter("error","fitmc1");
  frame1->getAttText()->SetTextSize(0.03); 
  // The canvas   
  TCanvas cv("cv","cv",800,800);
  // The pulls
  RooHist* hpull = frame1->pullHist();
  RooPlot* frame1a = massVhad.frame() ;
  frame1a->addPlotable(hpull,"P") ;
  // The pads
  TPad* fPads1 = NULL;
  TPad* fPads2 = NULL;
  fPads1 = new TPad("pad1", "", 0.00, 0.15, 0.99, 0.99);
  fPads2 = new TPad("pad2", "", 0.00, 0.05, 0.99, 0.225);
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
  TLegend *leg1 = new TLegend(0.55,0.6,0.9,0.9);
  leg1->SetHeader(legTitle[key].c_str());
  leg1->AddEntry("mc1",  "Dominant Background ",    "ep");
  leg1->AddEntry("fitmc1","ErfExp Background Fit", "l");
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
  frame1a->GetYaxis()->SetLabelSize(0.08);
  frame1a->GetXaxis()->SetLabelSize(0.17);
  frame1a->GetYaxis()->SetTitle("Pulls");
  frame1a->GetYaxis()->SetTitleOffset(0.30);
  frame1a->GetYaxis()->SetTitleSize(0.15);
  frame1a->GetXaxis()->SetTitleSize(0.17);
  frame1a->GetYaxis()->SetRangeUser(-5,5);
  frame1a->SetTitle(""); 
  frame1a->Draw();
  // SAVE THE FILE 
  cv.SaveAs(Form("otherPlots/domBkgMj%s.png",key.c_str()));
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // 2. SUBDOMINANT BACKGROUND (erf*exp)
  RooPlot* frame2 = massVhad.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
  bkg2.plotOn(frame2,Name("mc2"),Binning(36));
  model2.plotOn(frame2,Name("fitmc2"), LineColor(kRed));
  model2a.plotOn(frame2,Name("error2"),VisualizeError(*rf2a,1),FillColor(kAzure-2), FillStyle(3002));
  model2.paramOn(frame2,Layout(0.55,0.9,0.6));
  frame2->drawAfter("error2","mc2");
  frame2->drawAfter("error2","fitmc2");
  frame2->getAttText()->SetTextSize(0.03);
  // The canvas
  TCanvas cv2("cv2","cv2",800,800);
  // The pulls
  RooHist* hpull2 = frame2->pullHist();
  RooPlot* frame2a = massVhad.frame();
  frame2a->addPlotable(hpull2,"P");
  // The pads
  TPad* fPads1a = NULL;
  TPad* fPads2a = NULL;
  fPads1a = new TPad("pad1a", "", 0.00, 0.15, 0.99, 0.99);
  fPads2a = new TPad("pad2a", "", 0.00, 0.05, 0.99, 0.225);
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
  TLegend *leg1a = new TLegend(0.55,0.6,0.9,0.9);
  leg1a->SetHeader(legTitle[key].c_str());
  leg1a->AddEntry("mc2",  "Subdominant Background ",    "ep");
  leg1a->AddEntry("fitmc2","ErfExp Background Fit", "l");
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
  frame2a->GetYaxis()->SetLabelSize(0.08);
  frame2a->GetXaxis()->SetLabelSize(0.17);
  frame2a->GetYaxis()->SetTitle("Pulls");
  frame2a->GetYaxis()->SetTitleOffset(0.30);
  frame2a->GetYaxis()->SetTitleSize(0.15);
  frame2a->GetXaxis()->SetTitleSize(0.17);
  frame2a->GetYaxis()->SetRangeUser(-5,5);
  frame2a->SetTitle("");
  frame2a->Draw();
  // SAVE THE FILE
  cv2.SaveAs(Form("otherPlots/subBkgMj%s.png",key.c_str()));
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // 3. SUBDOMINANT BACKGROUND (GAUS 2)
  RooPlot* frame3 = massVhad.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
  bkg2.plotOn(frame3,Name("mc3"),Binning(36));
  model3.plotOn(frame3,Name("fitmc3"), LineColor(kRed));
  model3a.plotOn(frame3,Name("error3"),VisualizeError(*rf3a,1),FillColor(kAzure-2), FillStyle(3002));
  model3.paramOn(frame3,Layout(0.55,0.9,0.6));
  frame3->drawAfter("error3","mc3");
  frame3->drawAfter("error3","fitmc3");
  frame3->getAttText()->SetTextSize(0.03);
  // THE CANVAS
  TCanvas cv3("cv3","cv3",800,800);
  // The pulls
  RooHist* hpull3 = frame3->pullHist();
  RooPlot* frame3a = massVhad.frame();
  frame3a->addPlotable(hpull3,"P"); 
  // The Pads
  TPad* fPads1b = NULL;
  TPad* fPads2b = NULL;
  fPads1b = new TPad("pad1b", "", 0.00, 0.15, 0.99, 0.99);
  fPads2b = new TPad("pad2b", "", 0.00, 0.05, 0.99, 0.225);
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
  TLegend *leg1b = new TLegend(0.55,0.6,0.9,0.9);
  leg1b->SetHeader(legTitle[key].c_str());
  leg1b->AddEntry("mc3",  "Subdominant Background ",    "ep");
  leg1b->AddEntry("fitmc3","Gaus2 Background Fit", "l");
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
  frame3a->GetYaxis()->SetLabelSize(0.08);
  frame3a->GetXaxis()->SetLabelSize(0.17);
  frame3a->GetYaxis()->SetTitle("Pulls");
  frame3a->GetYaxis()->SetTitleOffset(0.30);
  frame3a->GetYaxis()->SetTitleSize(0.15);
  frame3a->GetXaxis()->SetTitleSize(0.17);
  frame3a->GetYaxis()->SetRangeUser(-5,5);
  frame3a->SetTitle("");
  frame3a->Draw();
  // SAVE THE FILE
  cv3.SaveAs(Form("otherPlots/subBkgMj%s_gaus2.png",key.c_str()));

 
}
