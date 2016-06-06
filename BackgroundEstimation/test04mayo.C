
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

void test04mayo(std::string key)
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
  RooRealVar candTMass("candTMass","M_{VZ}",            600.,  3000., "GeV");
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
  treeMC2.Add(      "../trees/newtrees/treeEDBR_TTbar_76x_v2.root"                           ); 
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

  RooCategory MC("MC","MC");
  MC.defineType( "dominant");
  MC.defineType("subdominant");
  RooDataSet allMC("allMC","allMC", variables, WeightVar(totalWeight), Index(MC), Import("dominant",bkg1), Import("subdominant",bkg2));


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

RooFormulaVar lowerSIGyield("lowerSIGyield","extrapolation to lowerSIG","@0+@1", RooArgList(Dom_yield,Sub_yield));
Double_t bkgYield = lowerSIGyield.getVal();
RooRealVar ZZ_bkg_norm("#color[2]{bkg norm}","expected yield in lowerSIG",bkgYield,0.,1.e4);

RooFormulaVar coef( "coef","@0/@1", RooArgList(Sub_SB_yield,Dom_SB_yield));

RooRealVar Sub_pdf_norm("Sub_pdf_norm", "Sub yield in lowerSIG", Sub_yield.getVal(), 0.,1.e4);
RooRealVar Dom_pdf_norm( "Dom_pdf_norm", "Dom yield in lowerSIG", Dom_yield.getVal(), 0.,1.e4);
RooRealVar Dom_error( "Dom_error", "Dom yield error", 1 + Dom_yield.getPropagatedError(*rf1)/ Dom_yield.getVal(),1.,2.);
cout << "Dom estimation = " << Dom_yield.getVal() << " +/- " << Dom_yield.getPropagatedError(*rf1) << endl;
cout << "Sub estimation = " << Sub_yield.getVal() << " +/- " << Sub_yield.getPropagatedError(*rf2) << endl;
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
RooRealVar s1("s1","slope of the exp1", 221., 0., 10000.);
RooRealVar s2("s2","slope of the exp2", 100., 0., 1000.);
RooRealVar s3("s3","slope of the exp3", 70., 0., 1000.);
RooRealVar s4("s4","slope of the exp4", 235, 0., 700.);
RooRealVar a0("a0","parameter of exp0", 0.001 , 0.00001, 10.);
RooRealVar a1("a1","parameter of exp1", 0.001 , 0.00001, 10.);
//RooRealVar a2("a2","parameter of exp2", -0.001 , -1, 10.);
RooRealVar a2("a2","parameter of exp2", 0., -1, 1);
RooRealVar a3("a3","parameter of exp3", 0.03 , 0.001, 10.);
//RooRealVar a4("a4","parameter of exp4", 0.00001 , 0, 1);
RooRealVar a4("a4","parameter of exp4", 0., -1	, 1);
RooExpTailPdf Sub_pdf( "Sub_pdf", "Sub in nominal region", candTMass,s0,a0);
RooExpTailPdf Sub_SB_pdf("Sub_SB_pdf", "Sub in sideband region", candTMass,s1,a1);
RooExpTailPdf Dat_SB ("Dat_SB" , "Data sideband", candTMass,s2,a2);
RooExpTailPdf Dom_SR_pdf( "Dom_SR_pdf", "Dom in nominal region", candTMass,s3,a3);
RooExpTailPdf Dom_SB_pdf( "Dom_SB_pdf", "Dom in sideband region", candTMass,s4,a4);
a2.setConstant(true);
a4.setConstant(true);

RooAddPdf Data_SB_pdf("Data_SB_pdf", "Model data in sideband", Sub_SB_pdf, Dat_SB, coef);
RooAlpha4ExpTailPdf alpha_pdf("alpha", "alpha function for Dom", candTMass,s3,a3,s4,a4);
//RooProdPdf Dom("Dom", "Dom in SIG", alpha_pdf, Dat_SB);
RooProdPdf ZZ_bkg("ZZ_bkg", "Data-driven bakground estimation", alpha_pdf, Dat_SB);

candTMass.setRange("range", 600., 3000);



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

//RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), Range("range"), SumW2Error(kTRUE), PrintLevel(-1));
RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), Range("range"), SumW2Error(kTRUE));

//RooFitResult *testf1  = Dom_SR_pdf.fitTo(Dom_SR,Save(),SumW2Error(kTRUE),PrintLevel(-1));
//RooFitResult *testf2  = Dom_SB_pdf.fitTo(Dom_SB,Save(),SumW2Error(kTRUE));
//RooFitResult *testf4  = Data_SB_pdf.fitTo(Data_SB,Save(),SumW2Error(kTRUE),PrintLevel(-1));

/*
s2.setConstant(true); a2.setConstant(true);
s3.setConstant(true); a3.setConstant(true);
s4.setConstant(true); a4.setConstant(true);
*/

//--------------------------------------------------------------------------------------
//             NEW PDF ExpN
//--------------------------------------------------------------------------------------
  RooRealVar k0("k0","parameter of expN0",  0.03,   0.001,   0.1); 
  RooRealVar n0("n0","parameter of expN1",  0.03,   0.001,   0.1); 
  RooRealVar k1("k1","parameter of expN1",  0.1,   0,   10);
  RooRealVar n1("n1","parameter of expN1",  0.1,   0,   10000);
  RooRealVar k2("k2","parameter of expN2",  0.03,   0.001,   0.1);
  RooRealVar n2("n2","parameter of expN2",  0.03,   0.001,   0.1);
  RooRealVar k3("k3","parameter of expN3",  0.03,   0.001,   0.1);
  RooRealVar n3("n3","parameter of expN3",  0.03,   0.001,   0.1);
  RooRealVar k4("k4","parameter of expN4",  4.49,     0,  100);
  RooRealVar n4("n4","parameter of expN4",  0.022,   0,   1);
  RooExpNPdf          DomSR_pdf1("DomSR_pdf1", "fit bkg  in nominal  reg",   candTMass,k0,n0);
  RooExpNPdf          DomSB_pdf1("DomSB_pdf1", "fit bkg  in sideband reg",   candTMass,k1,n1);
  RooExpNPdf          SubSB_pdf1("SubSB_pdf1", "dom bkg  in sideband reg",   candTMass,k2,n2);
  RooExpNPdf          SubSR_pdf1("SubSR_pdf1", "sub bkg in sideband reg",   candTMass,k3,n3);
  RooExpNPdf          nsSub_pdf1("nsSub_pdf1", "sub bkg in nominal  reg",   candTMass,k4,n4);
  RooAlpha4ExpNPdf alpha_pdf1("alpha_pdf1", "alpha ratio",                   candTMass,k0,n0,k1,n1);
//-------------------------------------------------------------------------------------------

//RooFitResult *testf1  = DomSB_pdf1.fitTo(Dom_SB,Save(),SumW2Error(kTRUE));


//---------------------------------------------------------------------------------------------

  RooDataSet *alpha = alpha_pdf.generate(candTMass,1.e6); 
  alpha->SetName("alpha");

  RooBinning xbins2(48,600,3000);
  RooPlot *plot1 = candTMass.frame(Title("#bf{MC SIG}"));
  RooPlot *plot2 = candTMass.frame(Title("#bf{MC SB}"));
  RooPlot *plot3 = candTMass.frame(Title("#bf{MC SIG / MC SB}"));
  RooPlot *plot4 = candTMass.frame(Title("#bf{Data SB}"));
  plot1->SetAxisRange(600,3000,"X");
  plot2->SetAxisRange(600,3000,"X");
  plot3->SetAxisRange(600,3000,"X");
  plot4->SetAxisRange(600,3000,"X");


  //------------------------------------------------------------------------------------
  //------------------------  MC SIGNAL -----------------------------------------------
  //-----------------------------------------------------------------------------------


  Dom_SR.plotOn(plot1,Binning(xbins2),RooFit::Invisible());
  Dom_SR_pdf.plotOn( plot1,Name("error1"),VisualizeError(*fitres,1),LineColor(kBlack),FillColor(kYellow-7));
// to test only the fit with this function
//  Dom_SR_pdf.plotOn( plot1,Name("error1"),VisualizeError(*testf1,1),LineColor(kBlack),FillColor(kYellow-7));
  Dom_SR.plotOn(plot1,Name("mc1"),DrawOption("ep"),Binning(xbins2));
  Dom_SR_pdf.plotOn( plot1,Name("fit1"),Binning(xbins2),DrawOption("L"),LineWidth(3),LineColor(kGreen+2));
  Dom_SR_pdf.paramOn(plot1,Layout(0.50,0.9,0.6));


  plot1->drawAfter("error1","mc1");
  plot1->drawAfter("error1","fit1");
  plot1->drawAfter("fit1","mc1");
  plot1->getAttText()->SetTextSize(0.03);

   TCanvas* canvasMVZ1 = new TCanvas("MVZ1","MVZ1",800,800);

   RooHist* hpull1 = plot1->pullHist();
   RooPlot* Frame1pull = candTMass.frame(Range("fullRange"));
   Frame1pull->addPlotable(hpull1,"P");

   Double_t chi2plot1 = plot1->chiSquare("fit1", "mc1", 2);

   TPad* fPads1a = NULL;
   TPad* fPads1b = NULL;
   fPads1a = new TPad("pad1a", "", 0.00, 0.15, 0.99, 0.99);
   fPads1b = new TPad("pad1b", "", 0.00, 0.05, 0.99, 0.225);
   fPads1a->SetFillColor(0);
   fPads1a->SetLineColor(0);
   fPads1b->SetFillColor(0);
   fPads1b->SetLineColor(0);
   fPads1a->Draw();
   fPads1b->Draw();

   fPads1a->cd();
   fPads1a->SetLogy();
   plot1->GetYaxis()->SetTitleOffset(1.30);
   plot1->GetXaxis()->SetLabelSize(0);
   plot1->SetMinimum(0.001);
   plot1->SetMaximum(1000);
   plot1->Draw();

   char result1[100];
   strcpy(result1,legTitle[key].c_str());
   strcat(result1," - Signal Region");

   TLegend *leg1 = new TLegend(0.50,0.6,0.9,0.9);
   leg1->SetHeader(result1);
   leg1->AddEntry("mc1",  "Dominant Background ",    "ep");
   leg1->AddEntry("fit1","ExpoTail Background Fit", "l");
   leg1->SetTextSize(0.03);
   leg1->Draw();
   TLegendEntry *header1 = (TLegendEntry*)leg1->GetListOfPrimitives()->First();
   header1->SetTextAlign(22);
   header1->SetTextColor(1);
   header1->SetTextSize(.035);

   fPads1b->cd();
   fPads1b->SetGridx();
   fPads1b->SetGridy();
   Frame1pull->GetYaxis()->SetLabelSize(0.08);
   Frame1pull->GetXaxis()->SetLabelSize(0.17);
   Frame1pull->GetYaxis()->SetTitle("Pulls");
   Frame1pull->GetYaxis()->SetTitleOffset(0.30);
   Frame1pull->GetYaxis()->SetTitleSize(0.15);
   Frame1pull->GetXaxis()->SetTitleSize(0.17);
   Frame1pull->GetXaxis()->SetTitle("M_{T} (GeV)");
   Frame1pull->GetYaxis()->SetRangeUser(-5,5);
   Frame1pull->SetTitle("");
   Frame1pull->Draw();
   TPaveLabel *MT1 = new TPaveLabel(0.7,0.7,0.9,0.9, Form("#chi^{2}/dof = %f", chi2plot1),"brNDC");
   MT1->Draw();

   canvasMVZ1->SaveAs(Form("otherPlots/sigDom_MVZ%s.png",key.c_str()));




  // ---------------------------------------------------------------------------
  // ------------------   MC IN SIDEBAND ---------------------------------------
  // --------------------------------------------------------------------------


  Dom_SB.plotOn(plot2,Binning(xbins2),RooFit::Invisible());
  Dom_SB_pdf.plotOn( plot2,Name("error2"),VisualizeError(*fitres,2),LineColor(kBlack),FillColor(kYellow-7));
//  Dom_SB_pdf.plotOn( plot2,Name("error2"),VisualizeError(*testf2,1),LineColor(kBlack),FillColor(kYellow-7));
  Dom_SB.plotOn(plot2,Name("mc2"),Binning(xbins2),DrawOption("ep"));
  Dom_SB_pdf.plotOn( plot2,Name("fit2"),Binning(xbins2),DrawOption("L"),LineWidth(3),LineColor(kGreen+2));
  Dom_SB_pdf.paramOn(plot2,Layout(0.50,0.9,0.6)) ;


/*
  DomSB_pdf1.plotOn( plot2,Name("error2"),VisualizeError(*testf1,1),LineColor(kBlack),FillColor(kYellow-7));
  Dom_SB.plotOn(plot2,Name("mc2"),Binning(xbins2),DrawOption("ep"));
  DomSB_pdf1.plotOn( plot2,Name("fit2"),Binning(xbins2),DrawOption("L"),LineWidth(3),LineColor(kGreen+2));
  DomSB_pdf1.paramOn(plot2,Layout(0.50,0.9,0.6)) ;
*/

  plot2->drawAfter("error2","mc2");
  plot2->drawAfter("error2","fit2");
  plot2->drawAfter("fit2","mc2");
  plot2->getAttText()->SetTextSize(0.03);



   TCanvas* canvasMVZ2 = new TCanvas("MVZ2","MVZ2",800,800);

   RooHist* hpull2 = plot2->pullHist();
   RooPlot* Frame2pull = candTMass.frame(Range("fullRange"));
   Frame2pull->addPlotable(hpull2,"P");

   Double_t chi2plot2 = plot2->chiSquare("fit2", "mc2", 2);

   TPad* fPads2a = NULL;
   TPad* fPads2b = NULL;
   fPads2a = new TPad("pad2a", "", 0.00, 0.15, 0.99, 0.99);
   fPads2b = new TPad("pad2b", "", 0.00, 0.05, 0.99, 0.225);
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

   TLegend *leg2 = new TLegend(0.50,0.6,0.9,0.9);
   leg2->SetHeader(result2);
   leg2->AddEntry("mc2",  "Dominant Background ",    "ep");
   leg2->AddEntry("fit2","ExpoTail Background Fit", "l");
   leg2->SetTextSize(0.03);
   leg2->Draw();
   TLegendEntry *header2 = (TLegendEntry*)leg2->GetListOfPrimitives()->First();
   header2->SetTextAlign(22);
   header2->SetTextColor(1);
   header2->SetTextSize(.035);

   fPads2b->cd();
   fPads2b->SetGridx();
   fPads2b->SetGridy();
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
   TPaveLabel *MT2 = new TPaveLabel(0.7,0.7,0.9,0.9, Form("#chi^{2}/dof = %f", chi2plot2),"brNDC");
   MT2->Draw();

   canvasMVZ2->SaveAs(Form("otherPlots/sbDom_MVZ%s.png",key.c_str()));




  // ---------------------------------------------------------------------------
  // ------------------   DATA IN SIDEBAND ---------------------------------------
  // --------------------------------------------------------------------------


  Data_SB.plotOn(plot4,Binning(xbins2),RooFit::Invisible());
  Data_SB_pdf.plotOn( plot4,Name("error4"),VisualizeError(*fitres,1),LineColor(kBlack),FillColor(kYellow-7));
//  Data_SB_pdf.plotOn( plot4,Name("error4"),VisualizeError(*testf4,1),LineColor(kBlack),FillColor(kYellow-7));
  Data_SB.plotOn(plot4,Name("mc4"),Binning(xbins2),DrawOption("ep"));
  Data_SB_pdf.plotOn( plot4,Name("fit4"),Binning(xbins2),DrawOption("L"),LineWidth(3),LineColor(kGreen+2));
  Data_SB_pdf.paramOn(plot4,Layout(0.50,0.9,0.6)) ;


  plot4->drawAfter("error4","mc4");
  plot4->drawAfter("error4","fit4");
  plot4->drawAfter("fit4","mc4");
  plot4->getAttText()->SetTextSize(0.03);

   TCanvas* canvasMVZ4 = new TCanvas("MVZ4","MVZ4",800,800);

   RooHist* hpull4 = plot4->pullHist();
   RooPlot* Frame4pull = candTMass.frame(Range("fullRange"));
   Frame4pull->addPlotable(hpull4,"P");

   Double_t chi2plot4 = plot4->chiSquare("fit4", "mc4", 2);

   TPad* fPads4a = NULL;
   TPad* fPads4b = NULL;
   fPads4a = new TPad("pad4a", "", 0.00, 0.15, 0.99, 0.99);
   fPads4b = new TPad("pad4b", "", 0.00, 0.05, 0.99, 0.225);
   fPads4a->SetFillColor(0);
   fPads4a->SetLineColor(0);
   fPads4b->SetFillColor(0);
   fPads4b->SetLineColor(0);
   fPads4a->Draw();
   fPads4b->Draw();

   fPads4a->cd();
   fPads4a->SetLogy();
   plot4->GetYaxis()->SetTitleOffset(1.30);
   plot4->GetXaxis()->SetLabelSize(0);
   plot4->SetMinimum(0.001);
   plot4->SetMaximum(1000);
   plot4->Draw();


   char result4[100];
   strcpy(result4,legTitle[key].c_str());
   strcat(result4," - SB Region");

   TLegend *leg4 = new TLegend(0.50,0.6,0.9,0.9);
   leg4->SetHeader(result4);
   leg4->AddEntry("mc4",  "Data",    "ep");
   leg4->AddEntry("fit4","ExpoTail Fit", "l");
   leg4->SetTextSize(0.03);
   leg4->Draw();
   TLegendEntry *header4 = (TLegendEntry*)leg4->GetListOfPrimitives()->First();
   header4->SetTextAlign(22);
   header4->SetTextColor(1);
   header4->SetTextSize(.035);

   fPads4b->cd();
   fPads4b->SetGridx();
   fPads4b->SetGridy();
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
   TPaveLabel *MT4 = new TPaveLabel(0.7,0.7,0.9,0.9, Form("#chi^{2}/dof = %f", chi2plot4),"brNDC");
   MT4->Draw();

   canvasMVZ4->SaveAs(Form("otherPlots/sbData_MVZ%s.png",key.c_str()));








//---------------------------------------------------------------




  // ALPHA
  alpha->plotOn(plot3,RooFit::Invisible());
  alpha_pdf.plotOn(plot3,Name("1sigma"),VisualizeError(*fitres,1,kFALSE),FillStyle(1001),FillColor(kGreen),LineColor(kBlack));
  alpha_pdf.plotOn(plot3,Name("2sigma"),VisualizeError(*fitres,2,kFALSE),FillStyle(1001),FillColor(kYellow),LineColor(kBlack)); 
  alpha_pdf.plotOn(plot3,Name("mean"),DrawOption("L"),LineWidth(2),LineColor(kBlack));
  alpha_pdf.paramOn(plot3,Layout(0.50,0.99,0.9)) ;
  plot3->drawAfter("2sigma","1sigma");
  plot3->drawAfter("1sigma","mean");

  plot3->GetYaxis()->SetTitle("Arbitrary units");
//  plot3->GetYaxis()->SetNdivisions(2);
  plot3->GetYaxis()->SetTitleSize(0.05);
  plot3->GetYaxis()->SetTitleOffset(0.85);
  plot3->GetXaxis()->SetTitleSize(0.05);
  plot3->GetXaxis()->SetTitleOffset(0.85);
  plot3->GetXaxis()->SetTitle("M_{T} (GeV)");
  plot3->SetMinimum(-5e3); 
  plot3->SetMaximum(150e3);


  TCanvas* canvasalpha = new TCanvas("alpha","alpha",800,800);
  plot3->Draw();

   TLegend *leg3 = new TLegend(0.50,0.6,0.9,0.9);
   leg3->SetHeader("Alpha transfer function");
   leg3->AddEntry("mean","alpha function",    "l");
   leg3->AddEntry("1sigma",  "#alpha #pm 1 #sigma ",    "f");
   leg3->AddEntry("2sigma","#alpha #pm 2 #sigma", "f");
   leg3->SetTextSize(0.03);
   leg3->Draw();
   TLegendEntry *header3 = (TLegendEntry*)leg3->GetListOfPrimitives()->First();
   header3->SetTextAlign(22);
   header3->SetTextColor(1);
   header3->SetTextSize(.035);



  canvasalpha->SaveAs(Form("otherPlots/alpha%s.png",key.c_str()));



  RooExtendPdf ZZ_bkg_ext( "ZZ_bkg_ext", "extended p.d.f",  ZZ_bkg, ZZ_bkg_norm);
  RooDataSet allMCns("allMCns","allMCns", variables, Cut(lowerSIG), WeightVar(totalWeight), Index(MC), Import("dominant",bkg1), Import("subdominant",bkg2));

  RooPlot *plot5 = candTMass.frame(Title("#bf{CMS} Preliminary #sqrt{s} = 13 TeV"));
  plot5->SetAxisRange(600,3000,"X");
//   const RooCmdArg goodNorm = Normalization(1.0,RooAbsReal::RelativeExpected);
  ZZ_bkg_ext.plotOn(plot5,Binning(xbins2),RooFit::Invisible());
//  ZZ_bkg_ext.plotOn( plot5, Name("1sigma"), goodNorm, VisualizeError(*fitres,1,kFALSE),LineColor(kBlack),FillColor(kGray),FillStyle(3002));
  ZZ_bkg_ext.plotOn( plot5, Name("1sigma"),VisualizeError(*fitres,1,kFALSE),LineColor(kBlack),FillColor(kGray),FillStyle(3002));
//  ZZ_bkg_ext.plotOn( plot5, Name("Bkg"),    goodNorm, VLines(),DrawOption("F"), FillColor(kAzure+6) );
  ZZ_bkg_ext.plotOn( plot5, Name("Bkg"), VLines(),DrawOption("F"), FillColor(kAzure+6) );
  sigObs.plotOn(plot5, Name("Data"), Binning(xbins2),DrawOption("ep") );
  plot5->drawAfter("Bkg","1sigma");
  plot5->drawAfter("Bkg","Data");
  plot5->drawAfter("1sigma","Data");
//  plot5->drawAfter("subBkg","Bkg");
//  plot2->drawAfter("error2","fit2");
//  plot2->drawAfter("fit2","mc2");
//  plot5->getAttText()->SetTextSize(0.03);


  TCanvas* canvasfinal = new TCanvas("canvasfinal","alpha",800,800);


  plot5->SetMinimum(0.01);
  plot5->SetMaximum(550);
  plot5->GetYaxis()->SetTitleSize(0.05); plot5->GetYaxis()->SetTitleOffset(0.85);
  plot5->GetXaxis()->SetTitleSize(0.05); plot5->GetXaxis()->SetTitleOffset(0.85);
  gPad->SetLogy();
  plot5->Draw();

  TLegend *leg5 = new TLegend(0.5,0.6,0.9,0.9);
  leg5->SetHeader(legTitle[key].c_str());
  leg5->AddEntry("Bkg",   "Estimated background","l");
  leg5->AddEntry("1sigma","Estimation #pm 1#sigma", "f");

  leg5->Draw();
  TLegendEntry *header5 = (TLegendEntry*)leg5->GetListOfPrimitives()->First();
  header5->SetTextAlign(22);
  header5->SetTextColor(1);
  header5->SetTextSize(.04);
  
  canvasfinal->SaveAs(Form("otherPlots/bkgFinalPrediction%s.png",key.c_str()));

  cout << "Estimated background = " << bkgYield << " +/- " << lowerSIGyield.getPropagatedError(*rf1) << endl;
  cout << "Simulated background = " << allMCns.sumEntries() << endl;
  cout << "True value = " << sigObs.numEntries() << endl;


}
