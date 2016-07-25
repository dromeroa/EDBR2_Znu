
// FROM 24/07/2016
// FINAL FIR FOR THE PRUNED MASS UNBLIDED HP
//
// FROM /afs/cern.ch/work/d/dromeroa/private/ALPHAMETHOD_Enero25/CMSSW_8_0_0_pre5/src/ALPHA_METHOD/TESTNEWCODE
// Do : >cmsenv
// root[] gSystem->Load("../PDFs/HWWLVJRooPdfs_cxx.so")
// root[] .x fitPrunedUBHP.C("HP")

#include "TMath.h"
#include "string.h"

void fitPrunedUBHP(std::string key)
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
  TCut all    = lowerSB or upperSB or lowerSIG or upperSIG;
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
  //alldata
  RooDataSet alldata("alldata","alldata", variables, Cut(all), Import(treeData));
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
  RooRealVar mu1("mu1", "average", 84, 0, 200);
  RooRealVar sigma1("sigma1", "sigma", 8.7, 0, 100);
  RooRealVar mu2("mu2", "average", 102, 0, 200);
  RooRealVar sigma2("sigma2", "sigma", 28, 0, 100); 
  RooGaussian gauss1("gauss1","gaussian PDF1", massVhad, mu1, sigma1);
  RooGaussian gauss2("gauss2","gaussian PDF2", massVhad, mu2, sigma2);
  RooRealVar funfrac("funfrac","fraction of functions",0.6,0.,1.);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //  THE MODELS
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooErfExpPdf model1("model1","dominant backgrounds",massVhad,c1,offset1,width1);
  RooErfExpPdf model1a("model1a","dominant backgroundsa",massVhad,c1,offset1,width1);

  RooAddPdf model3("Gaus2", "gaussian plus gaussian", RooArgList(gauss1, gauss2), funfrac);
  RooAddPdf model3a("Gaus2a", "gaussian plus gaussiana", RooArgList(gauss1, gauss2), funfrac);
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


  // A command to add a normalization to the PDF
  RooExtendPdf emodel1("emodel1","extended dom backgrounds",model1,nbkg1);
  RooExtendPdf emodel1a("emodel1a","extended dom backgroundsa",model1a,nbkg1);
  RooExtendPdf emodel3("emodel3","extended sub backgrounds",model3,nbkg2);
  RooExtendPdf emodel3a("emodel3a","extended sub backgrounds",model3a,nbkg2);


  // The fit of each background in all range separatly
  std::cout << "Fitting models - normalisation" << std::endl;
  RooFitResult *rf1 = emodel1.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf1a = emodel1a.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));

  RooFitResult *rf3 = emodel3.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf3a = emodel3a.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));


  //*****************************************************************
  //                     PLOTS FOR THE BACKGROUNDS AND FITS
  //****************************************************************


  //++++++++++++++++++++++i+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // bining for subdominant background
   RooBinning xbins(36,40,220);
  

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
 alldata.plotOn(frame5,Name("data"),Binning(36));
 model_ext.plotOn(frame5,Name("bothMC"),Range("fullRange"),LineColor(kWhite),FillColor(kAzure+6),VLines(),DrawOption("F"));
 model_ext.plotOn(frame5,Name("subdominantMC"),Components("emodel3"),FillColor(kYellow+1),VLines(),DrawOption("F"),Range("fullRange"),LineColor(kWhite));
 frame5->SetMinimum(0.00005 );
 frame5->drawAfter("bothMC","subdominantMC");
 frame5->drawAfter("subdominantMC","data");
 frame5->SetTitle("");


  TText* txt0 = new TText(50,98,"CMS") ;
  txt0->SetTextSize(0.04) ;
  txt0->SetTextColor(kBlack) ;
  txt0->SetTextFont(61);
  frame5->addObject(txt0) ;

  TText* txt1 = new TText(50,93,"Preliminary") ;
  txt1->SetTextSize(0.04) ;
  txt1->SetTextColor(kBlack) ;
  txt1->SetTextFont(52);
  frame5->addObject(txt1) ;


  TText* txt2 = new TText(159,112,"2.318 /fb (13TeV)") ;
  txt2->SetTextSize(0.04) ;
  txt2->SetTextColor(kBlack) ;
  frame5->addObject(txt2) ;


 RooHist* hpull5 = frame5->pullHist("data","bothMC");
 RooPlot* frame5a = massVhad.frame();
 frame5a->addPlotable(hpull5,"P"); 


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

 fPads1d->cd();
 frame5->GetYaxis()->SetTitleOffset(1.30);
 frame5->GetXaxis()->SetLabelSize(0);
 frame5->GetYaxis()->SetRangeUser(0.00005,110);
 frame5->Draw();

 TLegend *leg1d = new TLegend(0.55,0.55,0.9,0.9);
 leg1d->SetHeader(legTitle[key].c_str());
 leg1d->AddEntry("bothMC",  "Dominant MC fit",    "f");
 leg1d->AddEntry("subdominantMC","Subdominant MC fit", "f");
 leg1d->AddEntry("data","data in sidebands", "ep");
 leg1d->SetTextSize(0.025);
 leg1d->Draw();
 TLegendEntry *header1d = (TLegendEntry*)leg1d->GetListOfPrimitives()->First();
 header1d->SetTextAlign(22);
 header1d->SetTextColor(1);
 header1d->SetTextSize(.05); 

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

 cv5.SaveAs(Form("otherPlots/dataMjUB%s.png",key.c_str())); 
 cv5.SaveAs(Form("otherPlots/dataMjUB%s.pdf",key.c_str()));


}
