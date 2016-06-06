
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

void fitSB_exptailLP(std::string key)
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
  const bool isBlind = false;
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
  RooRealVar genWeight("genWeight", "gen weight",  -100.,  100.         ); 
  RooArgSet variables(candTMass,massVhad,tau21,totalWeight,genWeight);
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
  RooDataSet bkg1("bkg1", "bkg1", variables, Cut(selectedCategory), WeightVar("totalWeight"), Import(treeMC1));
  RooDataSet bkg2("bkg2", "bkg2", variables, Cut(selectedCategory), WeightVar("totalWeight"), Import(treeMC2));
  RooRealVar nbkg1("nbkg1","nbkg1",bkg1.sumEntries(),bkg1.sumEntries()/10,bkg1.sumEntries()*10);
  RooRealVar nbkg2("nbkg2","nbkg2",bkg2.sumEntries(),bkg2.sumEntries()/10,bkg1.sumEntries()*10);
  RooCategory MC("MC","MC");
  MC.defineType( "dominant");
  MC.defineType("subdominant");
  RooDataSet allMC("allMC","allMC", variables, WeightVar(totalWeight), Index(MC), Import("dominant",bkg1), Import("subdominant",bkg2));



  // Exp tail (for dominant SB)
  RooRealVar s0("s0","slope of the exp0", 200., 0., 1000.);
  RooRealVar a0("a0","parameter of exp0", 1. , 0, 10);
  RooExpTailPdf Dom_SB_pdf("Dom_SB_pdf", "Dom in SB region", candTMass, s0,a0);
//  a0.setConstant(true);


//  RooRealVar k0("k0","parameter of expN0",  -0.1,  -1 ,   1);
//  RooRealVar n0("n0","parameter of expN1",  100,   0.,   3000);
//  RooExpNPdf Dom_SB_pdf("Dom_SB_pdf", "Dom in SB region",   candTMass,k0,n0);

/*
  RooRealVar lambda("lambda", "slope", -0.1, -5., 0.);
  RooExponential Dom_SB_pdf("expo", "exponential PDF", candTMass, lambda);
  candTMass.setRange("range", 600., 3500);
*/

  RooDataSet Dom_SB("Dom_SB", "Dom_SB", variables, Cut(allSB), WeightVar(totalWeight), Import(treeMC1));

  RooFitResult *testf1  = Dom_SB_pdf.fitTo(Dom_SB,Save(),SumW2Error(kTRUE));

//---------------------------------------------------------------------------------------------

  RooBinning xbins2(58,600,3500);
  RooPlot *plot1 = candTMass.frame(Title("#bf{MC SIG}"));
  RooPlot *plot2 = candTMass.frame();
  RooPlot *plot3 = candTMass.frame(Title("#bf{MC SIG / MC SB}"));
  RooPlot *plot4 = candTMass.frame(Title("#bf{Data SB}"));
  plot1->SetAxisRange(600,3500,"X");
  plot2->SetAxisRange(600,3500,"X");
  plot3->SetAxisRange(600,3500,"X");
  plot4->SetAxisRange(600,3500,"X");


 // ---------------------------------------------------------------------------
 // ------------------   MC IN SIDEBAND ---------------------------------------
 // --------------------------------------------------------------------------


  Dom_SB.plotOn(plot2,Binning(xbins2),RooFit::Invisible());
//  Dom_SB_pdf.plotOn( plot2,Name("error2"),VisualizeError(*fitres,2),LineColor(kBlack),FillColor(kYellow-7));
  Dom_SB_pdf.plotOn( plot2,Name("error2"),VisualizeError(*testf1,1),LineColor(kBlack),FillColor(kBlue),FillStyle(3002));
  Dom_SB.plotOn(plot2,Name("mc2"),Binning(xbins2),DrawOption("P"));
  Dom_SB_pdf.plotOn( plot2,Name("fit2"),Binning(xbins2),DrawOption("L"),LineWidth(3),LineColor(kGreen+2));
  Dom_SB_pdf.paramOn(plot2,Layout(0.53,0.9,0.7)) ;

/*

  Dom_SB.plotOn(plot2,Binning(xbins2),RooFit::Invisible());
  DomSB_pdf1.plotOn( plot2,Name("error2"),VisualizeError(*testf1,1),LineColor(kBlack),FillColor(kYellow-7));
  Dom_SB.plotOn(plot2,Name("mc2"),Binning(xbins2),DrawOption("ep"));
  DomSB_pdf1.plotOn( plot2,Name("fit2"),Binning(xbins2),DrawOption("L"),LineWidth(3),LineColor(kGreen+2));
  DomSB_pdf1.paramOn(plot2,Layout(0.50,0.9,0.6)) ;
*/
  plot2->drawAfter("error2","mc2");
  plot2->drawAfter("error2","fit2");
  plot2->drawAfter("fit2","mc2");
  plot2->getAttText()->SetTextSize(0.03);
  plot2->SetTitle("");

     TText* te1 = new TText(800,400,"CMS") ;
  te1->SetTextSize(0.04) ;
  te1->SetTextColor(kBlack) ;
  te1->SetTextFont(61);
  plot2->addObject(te1) ;

  TText* txt1a = new TText(800,200,"Simulation") ;
  txt1a->SetTextSize(0.04) ;
  txt1a->SetTextColor(kBlack) ;
  txt1a->SetTextFont(52);
  plot2->addObject(txt1a) ;


  TText* txt2a = new TText(2500,1100,"2.307 /fb (13TeV)") ;
  txt2a->SetTextSize(0.04) ;
  txt2a->SetTextColor(kBlack) ;
  plot2->addObject(txt2a) ;


   TCanvas* canvasMVZ2 = new TCanvas("MVZ2","MVZ2",800,800);

   RooHist* hpull2 = plot2->pullHist();
   RooPlot* Frame2pull = candTMass.frame(Range("fullRange"));
   Frame2pull->addPlotable(hpull2,"P");

   Double_t chi2plot2 = plot2->chiSquare("fit2", "mc2", 2);

   TPad* fPads2a = NULL;
   TPad* fPads2b = NULL;
   fPads2a = new TPad("pad2a", "", 0.00, 0.14, 0.99, 0.99);
   fPads2b = new TPad("pad2b", "", 0.00, 0.04, 0.99, 0.25);
 
//   fPads2a = new TPad("pad2a", "", 0.00, 0.15, 0.99, 0.99);
//   fPads2b = new TPad("pad2b", "", 0.00, 0.05, 0.99, 0.225);
   fPads2a->SetFillColor(0);
   fPads2a->SetLineColor(0);
   fPads2b->SetFillColor(0);
   fPads2b->SetLineColor(0);
   fPads2a->Draw();
   fPads2b->Draw();
   fPads2a->cd();
   fPads2a->SetLogy();
   plot2->GetYaxis()->SetTitleOffset(1.30);
   plot2->GetXaxis()->SetLabelSize(0);
   plot2->SetMinimum(0.001);
   plot2->SetMaximum(1000);
   plot2->Draw();

   char result2[100];
   strcpy(result2,legTitle[key].c_str());
   strcat(result2," - SB Region");

   TLegend *leg2 = new TLegend(0.53,0.7,0.9,0.9);
   leg2->SetHeader(result2);
   leg2->AddEntry("mc2",  "Dominant Background ",    "ep");
   leg2->AddEntry("fit2","Expo tail Fit Function", "l");
   leg2->SetTextSize(0.03);
   leg2->Draw();
   TLegendEntry *header2 = (TLegendEntry*)leg2->GetListOfPrimitives()->First();
   header2->SetTextAlign(22);
   header2->SetTextColor(1);
   header2->SetTextSize(.035);

   fPads2b->cd();
   fPads2b->SetGridx();
   fPads2b->SetGridy();
   fPads2b->SetTopMargin(0);
   fPads2b->SetBottomMargin(0.4);
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
   TPaveLabel *MT2 = new TPaveLabel(0.7,0.85,0.9,1, Form("#chi^{2}/dof = %f", chi2plot2),"brNDC");
   MT2->Draw();

   canvasMVZ2->SaveAs(Form("otherPlots/sbDom_MVZ%s.png",key.c_str()));
   canvasMVZ2->SaveAs(Form("otherPlots/sbDom_MVZ%s.pdf",key.c_str()));


}
