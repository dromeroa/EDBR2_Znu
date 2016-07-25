
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

void fitdataSB_exptailLP(std::string key)
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


  RooRealVar c1("c1","slope of the exp",             -0.032,  -1.,    0.);
  RooRealVar offset1("offset1","offset of the erf",    85.0,   1.,  150.);
  RooRealVar width1("width1",  "width of the erf",     36.0,   1,   100.);

  RooRealVar mu1("mu1", "average", 84, 0, 300);
  RooRealVar sigma1("sigma1", "sigma", 8.7, 0, 100);
  RooRealVar mu2("mu2", "average", 102, 0, 200);
  RooRealVar sigma2("sigma2", "sigma", 28, 0, 100);
  RooGaussian gauss1("gauss1","gaussian PDF1", massVhad, mu1, sigma1);
  RooGaussian gauss2("gauss2","gaussian PDF2", massVhad, mu2, sigma2);
  RooRealVar funfrac("funfrac","fraction of functions",0.6,0.,1.);

  RooErfExpPdf model1_pdf("model1_pdf","dominant backgrounds",massVhad,c1,offset1,width1);
  RooAddPdf model2_pdf("Gaus2", "gaussian plus gaussian", RooArgList(gauss1, gauss2), funfrac);

  RooExtendPdf emodel1_pdf("emodel1_pdf","extended dom backgrounds",model1_pdf,nbkg1);
  RooExtendPdf emodel2_pdf("emodel2_pdf","extended sub backgrounds",model2_pdf,nbkg2);

  RooFitResult *rf1 = model1_pdf.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf2 = model2_pdf.fitTo(bkg2, Save(1), PrintLevel(plevelnorm));

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


  RooAddPdf model_ext("model_ext","sum of extended models",RooArgList(emodel1_pdf,emodel2_pdf));

  RooFitResult * Nfit =  model_ext.fitTo(Data_SB,Extended(kTRUE),Range("lowerSB,upperSB"),PrintLevel(-1));
  nbkg1.setConstant(true);

 RooAbsReal* Dom_SIG_integral = model1_pdf.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
 RooAbsReal* Sub_SIG_integral = model2_pdf.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
 RooAbsReal* Dom_SB_integral = model1_pdf.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB,upperSB"));
 RooAbsReal* Sub_SB_integral = model2_pdf.createIntegral(massVhad,NormSet(massVhad),Range("lowerSB,upperSB"));
 RooAbsReal* Total_SIG_integral = model_ext.createIntegral(massVhad,NormSet(massVhad),Range("lowerSIG"));
 RooFormulaVar Dom_SIG_yield( "Dom_SIG_yield","@0*@1",RooArgList( *Dom_SIG_integral,nbkg1));
 RooFormulaVar Sub_SIG_yield( "Sub_SIG_yield","@0*@1",RooArgList( *Sub_SIG_integral,nbkg2));
 RooFormulaVar Dom_SB_yield( "Dom_SB_yield","@0*@1",RooArgList( *Dom_SB_integral,nbkg1));
 RooFormulaVar Sub_SB_yield("Sub_SB_yield","@0*@1",RooArgList(*Sub_SB_integral,nbkg2));
 RooFormulaVar Total_SIG_yield( "Total_SIG_yield","@0*(@1+@2)",RooArgList( *Total_SIG_integral,nbkg1,nbkg2));
 RooFormulaVar Norma( "Norma","@0 +@1",RooArgList( nbkg1,nbkg2));


 RooFormulaVar coef( "coef","@0/@1", RooArgList(Sub_SB_yield,Dom_SB_yield));









  // Exponential (for data in SB)
  RooRealVar s1("s1","slope of the exp1", 1., 0., 200.);
  RooRealVar a1("a1","parameter of exp1", 0.03 , 0, 60);
  RooExpTailPdf Data_SB_pdf("Data_SB_pdf", "Data in SB region", candTMass, s1,a1);
//  a1.setConstant(true);



 RooRealVar s4("s4","slope of the exp4", 100., 0., 1000.);
 RooRealVar a4("a4","parameter of exp4", 0.1 , 0.001, 10.);
 RooExpTailPdf Sub_SB_pdf("Sub_SB_pdf", "Sub in sideband region", candTMass,s4,a4);


  RooAddPdf Data_SB_pdf_2("Data_SB_pdf_2", "Model data in sideband", Sub_SB_pdf, Data_SB_pdf, coef);

  RooDataSet Sub_SB("Sub_SB", "Sub_SB", variables, Cut(allSB), WeightVar(totalWeight), Import(treeMC2));
  Sub_SB_pdf.fitTo(Sub_SB, Range("range"), SumW2Error(true), PrintLevel(-1));
  s4.setConstant(true); a4.setConstant(true);



  candTMass.setRange("range", 600., 2000);


  RooFitResult *testf1  = Data_SB_pdf_2.fitTo(Data_SB,Save(),SumW2Error(kTRUE));

//---------------------------------------------------------------------------------------------

  RooBinning xbins2(28,600,2000);
  RooPlot *plot1 = candTMass.frame(Title("#bf{MC SIG}"));
  RooPlot *plot2 = candTMass.frame(Title("#bf{Data SB}"));
  RooPlot *plot3 = candTMass.frame(Title("#bf{MC SIG / MC SB}"));
  RooPlot *plot4 = candTMass.frame(Title("#bf{Data SB}"));
  plot1->SetAxisRange(600,2000,"X");
  plot2->SetAxisRange(600,2000,"X");
  plot3->SetAxisRange(600,2000,"X");
  plot4->SetAxisRange(600,2000,"X");


 // ---------------------------------------------------------------------------
 // ------------------   MC IN SIDEBAND ---------------------------------------
 // --------------------------------------------------------------------------


  Data_SB.plotOn(plot2,Binning(xbins2),RooFit::Invisible());
  Data_SB_pdf.plotOn( plot2,Name("error2"),VisualizeError(*testf1,1),LineColor(kBlack),FillColor(kGray),FillStyle(3002));
  Data_SB.plotOn(plot2,Name("mc2"),Binning(xbins2),DrawOption("P"));
  Data_SB_pdf.plotOn( plot2,Name("fit2"),Binning(xbins2),DrawOption("L"),LineWidth(3),LineColor(kGreen+2));
  Data_SB_pdf.paramOn(plot2,Layout(0.53,0.9,0.7)) ;

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

  TText* txt1a = new TText(800,200,"Preliminary") ;
  txt1a->SetTextSize(0.04) ;
  txt1a->SetTextColor(kBlack) ;
  txt1a->SetTextFont(52);
  plot2->addObject(txt1a) ;


  TText* txt2a = new TText(2500,1100,"2.318 /fb (13TeV)") ;
  txt2a->SetTextSize(0.038) ;
  txt2a->SetTextColor(kBlack) ;
  plot2->addObject(txt2a) ;


   TCanvas* canvasMVZ2 = new TCanvas("MVZ2","MVZ2",800,800);

   RooHist* hpull2 = plot2->pullHist();
   RooPlot* Frame2pull = candTMass.frame(Range("fullRange"));
   Frame2pull->addPlotable(hpull2,"P");

   Double_t chi2plot2 = plot2->chiSquare("fit2", "mc2", 2);

   TPad* fPads2a = NULL;
   TPad* fPads2b = NULL;
   fPads2a = new TPad("pad1", "", 0.00, 0.17, 0.99, 0.99);
   fPads2b = new TPad("pad2", "", 0.00, 0.04, 0.99, 0.22);
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
   plot2->SetMinimum(0.1);
   plot2->SetMaximum(1000);
   plot2->Draw();

   char result2[100];
   strcpy(result2,legTitle[key].c_str());
   strcat(result2," - SB Region");

   TLegend *leg2 = new TLegend(0.53,0.7,0.9,0.9);
   leg2->SetHeader(result2);
   leg2->AddEntry("mc2",  " Data",    "ep");
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

   canvasMVZ2->SaveAs(Form("otherPlots/sbData_MVZ%s.png",key.c_str()));
   canvasMVZ2->SaveAs(Form("otherPlots/sbData_MVZ%s.pdf",key.c_str()));


}
