
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

void fitResultMT(std::string key)
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
  int plevelshape =1;
  int plevelshapDom = -1;
  // Silent RooFit
  RooMsgService::instance().setGlobalKillBelow(FATAL);

  // Which plots do you want?

  // Transverse mass
  const bool plotDomSB = true;
  const bool plotalpha = true;
  ////**************************************************


  ////*********************************************************************
  //// 2. INTRODUCE THE VARIABLES
  ////*********************************************************************
  RooRealVar candTMass("candTMass","M_{VZ}",            600.,  3500., "GeV");
  RooRealVar massVhad("massVhad","M_{j}" ,               40.,   220., "GeV");
  RooRealVar tau21("tau21","tau21",                       0.,   1.0        );
  RooRealVar totalWeight("totalWeight", "total weight",   -100., 100.         );
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
  std::cout << "Dataset to host data" << std::endl;
  // data in both SB (lower+upper)
  RooDataSet Data_SB("Data_SB","Data_SB", variables, Cut(allSB), Import(treeData)); 
  // data in lower SB
  RooDataSet Data_lSB("Data_lSB","Data_lSB", variables, Cut(lowerSB), Import(treeData));
  // data in upper SB
  RooDataSet Data_uSB("Data_uSB","Data_uSB", variables, Cut(upperSB), Import(treeData)); 
  // data in signal region
  RooDataSet Data_lSIG("Data_lSIG","Data_lSIG", variables, Cut(lowerSIG), Import(treeData));
  // data in upper signal region
  RooDataSet Data_uSIG("Data_uSIG","Data_uSIG", variables, Cut(upperSIG), Import(treeData));
  ////************************************************************************************


  ////********************************************************************************************************
  ////   9.  DATASETS TO HOST MC
  ////********************************************************************************************************                 
  std::cout << "Dataset to host MC" << std::endl;
  // Dominant MC in SB
  RooDataSet Dom_SB("Dom_SB", "Dom_SB", variables, Cut(allSB), WeightVar(totalWeight), Import(treeMC1));
  // Dominant MC in SR
  RooDataSet Dom_SR("Dom_SR", "Dom_SR", variables, Cut(lowerSIG), WeightVar(totalWeight), Import(treeMC1));
  // Dominant background in all regions
  RooDataSet bkg1("bkg1", "bkg1", variables, Cut(selectedCategory), WeightVar("totalWeight"), Import(treeMC1));
  // Subdominant backgrounds in all regions
  RooDataSet bkg2("bkg2", "bkg2", variables, Cut(selectedCategory), WeightVar("totalWeight"), Import(treeMC2));
  ////*********************************************************************************************************

  // a variable to store the number of events en each background, with a minimum and maximum value
  RooRealVar nbkg1("nbkg1","nbkg1",bkg1.sumEntries(),bkg1.sumEntries()/10,bkg1.sumEntries()*10);
  RooRealVar nbkg2("nbkg2","nbkg2",bkg2.sumEntries(),bkg2.sumEntries()/10,bkg1.sumEntries()*10);
/*
  RooCategory MC("MC","MC");
  //------------------------------------------------------------------------------------------------------------
  MC.defineType( "dominant");
  MC.defineType("subdominant");
  RooDataSet allMC("allMC","allMC", variables, WeightVar(totalWeight), Index(MC), Import("dominant",bkg1), Import("subdominant",bkg2));
*/

/////////////////////////////////////////////////////////////////////////////////////
////        _   _                                                                    //
////       | \ | |                          | (_)         | | (_)                    //
////       |  \| | ___  _ __ _ __ ___   __ _| |_ ___  __ _| |_ _  ___  _ __          //
////       | . ` |/ _ \| '__| '_ ` _ \ / _` | | / __|/ _` | __| |/ _ \| '_ \         //
////       | |\  | (_) | |  | | | | | | (_| | | \__ \ (_| | |_| | (_) | | | |        //
////       |_| \_|\___/|_|  |_| |_| |_|\__,_|_|_|___/\__,_|\__|_|\___/|_| |_|        //
////                                                                                 //
///////////////////////////////////////////////////////////////////////////////////////


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
  RooRealVar mu1("mu1", "average", 84, 0, 300);
  RooRealVar sigma1("sigma1", "sigma", 8.7, 0, 100);
  RooRealVar mu2("mu2", "average", 102, 0, 200);
  RooRealVar sigma2("sigma2", "sigma", 28, 0, 100);
  RooGaussian gauss1("gauss1","gaussian PDF1", massVhad, mu1, sigma1);
  RooGaussian gauss2("gauss2","gaussian PDF2", massVhad, mu2, sigma2);
  RooRealVar funfrac("funfrac","fraction of functions",0.6,0.,1.);

  // The models (pdfs)
  RooErfExpPdf model1_pdf("model1_pdf","dominant backgrounds",massVhad,c1,offset1,width1);
  RooAddPdf model2_pdf("Gaus2", "gaussian plus gaussian", RooArgList(gauss1, gauss2), funfrac);

  // A command to add a normalization to the PDF
  RooExtendPdf emodel1_pdf("emodel1_pdf","extended dom backgrounds",model1_pdf,nbkg1);
  RooExtendPdf emodel2_pdf("emodel2_pdf","extended sub backgrounds",model2_pdf,nbkg2);

  // Do the fits to fix the shapes of the MC
  RooFitResult *rf1 = model1_pdf.fitTo(bkg1, Save(1), PrintLevel(plevelnorm));
  RooFitResult *rf2 = model2_pdf.fitTo(bkg2, Save(1), PrintLevel(plevelnorm),Range(40,160));

  // Fix the parameters (shape), let variable the normalization of the dominant
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

 // Calculate integrals of the model
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

 cout << "Dom estimation = " << Dom_SIG_yield.getVal() << " +/- " << Dom_SIG_yield.getPropagatedError(*rf1) << endl;
 cout << "Sub estimation = " << Sub_SIG_yield.getVal() << " +/- " << Sub_SIG_yield.getPropagatedError(*rf2) << endl;
 std::cout << "Events in signal region = " << Data_lSIG.sumEntries() << std::endl;
 cout << "Total estimation = " << Total_SIG_yield.getVal() << endl; 
 cout << "error " << 1 + Dom_SIG_yield.getPropagatedError(*rf1)/ Dom_SIG_yield.getVal() <<endl;

 RooRealVar Sub_pdf_norm("Sub_pdf_norm", "Sub yield in lowerSIG", Sub_SIG_yield.getVal(), 0.,1.e4);
 RooRealVar Dom_pdf_norm( "Dom_pdf_norm", "DY yield in lowerSIG", Dom_SIG_yield.getVal(), 0.,1.e4);
 RooRealVar Dom_norm_error( "Dom_error", "Dom yield error", 1 + Dom_SIG_yield.getPropagatedError(*rf1)/ Dom_SIG_yield.getVal(),1.,2.);

 Double_t N = Total_SIG_yield.getVal();
 Double_t Nsub = Sub_SIG_yield.getVal();
 cout << "valor de la normalizacion  " << N << endl;

 Sub_pdf_norm.setConstant(true);	

//********************************************************************************//
//                                                                                //     
//                              III. PDFs                                     //
//                                                                                //     
//********************************************************************************//

  std::cout << "LLegue a los pdfs   "  << std::endl;

 ////*********************************************************************************
 ////   10.  Expo tail PDF for Dominant Backround in SB
 ////********************************************************************************
 RooRealVar s0("s0","slope of the exp0", 230., 0., 1000.);
 RooRealVar a0("a0","parameter of exp0", 0. , -1, 1);
 RooExpTailPdf Dom_SB_pdf("Dom_SB_pdf", "Dom in SB region", candTMass, s0,a0);
 // to treat as an exponential
 a0.setConstant(true);
 ////******************************************************************************** 

 ////*********************************************************************************
 ////   11.  Expo tail PDF Dominant in SR
 ////********************************************************************************
 RooRealVar s1("s1","slope of the exp1", 2., 0., 100.);
 RooRealVar a1("a1","parameter of exp1", 0.03 , 0, 1);
 RooExpTailPdf Dom_SR_pdf("Dom_SR_pdf", "Dom in SR region", candTMass, s1,a1);
 ////********************************************************************************

 ////*********************************************************************************
 ////   12.  Expo Tail PDF for Dominant Backround in SR
 ////********************************************************************************
 RooRealVar s2("s2","slope of the exp2", 200., 0., 1000.);
 RooRealVar a2("a2","parameter of exp2", 0. , -1, 1);
 RooExpTailPdf Data_SB_pdf( "Data_SB_pdf", "Data in SB region", candTMass,s2,a2);
 a2.setConstant(true);
 ////*********************************************************************************


 RooRealVar s3("s3","slope of the exp3", 100., 0., 1000.);
 RooRealVar s4("s4","slope of the exp4", 100., 0., 1000.);
 RooRealVar a3("a3","parameter of exp3", 0.1 , 0.001, 10.);
 RooRealVar a4("a4","parameter of exp4", 0.1 , 0.001, 10.);
 RooExpTailPdf Sub_SR_pdf( "Sub_SR_pdf", "Sub in nominal region", candTMass,s3,a3);
 RooExpTailPdf Sub_SB_pdf("Sub_SB_pdf", "Sub in sideband region", candTMass,s4,a4);

  
  // The Products
//  RooAddPdf Add_Data_SB_pdf("Add_Data_SB_pdf", "Model data in sideband", Sub_SB_pdf, Dat_SB, coef);
  RooAlpha4ExpTailPdf alpha_pdf("alpha_pdf", "alpha function for Dom", candTMass,s1,a1,s0,a0);
  RooProdPdf MC_est_pdf("MC_est_pdf", "Data-driven bakground estimation", alpha_pdf, Data_SB_pdf);


//------------------------------------------------------------
  candTMass.setRange("range", 600., 3500);

  RooDataSet Sub_SR( "Sub_SR", "Sub_SR", variables, Cut(lowerSIG), WeightVar(totalWeight), Import(treeMC2));
  RooDataSet Sub_SB("Sub_SB", "Sub_SB", variables, Cut(allSB), WeightVar(totalWeight), Import(treeMC2));
  Sub_SR_pdf.fitTo(Sub_SR, Range("range"), SumW2Error(true), PrintLevel(-1));
  Sub_SB_pdf.fitTo(Sub_SB, Range("range"), SumW2Error(true), PrintLevel(-1));
  s3.setConstant(true); a3.setConstant(true);
  s4.setConstant(true); a4.setConstant(true);




  RooCategory reg("reg","reg");
  reg.defineType("1");
  reg.defineType("2");
  reg.defineType("3");

  RooDataSet bigSample("bigSample","bigSample",variables,WeightVar(totalWeight),Index(reg),Import("1",Dom_SR),Import("2",Dom_SB),Import("3",Data_SB));
  RooSimultaneous bigSample_pdf("bigSample_pdf", "simultaneous pdf", RooArgList(Dom_SR_pdf,Dom_SB_pdf,Data_SB_pdf), reg);

  // FINAL FIT  
  RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), Range("range"), SumW2Error(kTRUE), PrintLevel(plevelshape));


  RooDataSet *alpha = alpha_pdf.generate(candTMass,1.e6);
  alpha->SetName("alpha");



//---------------------------------------------------------------------------------------------

  RooBinning xbins2(58,600,3500);
  RooPlot *plot1 = candTMass.frame(Title("#bf{MC SIG}"));
  RooPlot *plot2 = candTMass.frame(Title("#bf{MC SB}"));
  RooPlot *plot3 = candTMass.frame();
  RooPlot *plot4 = candTMass.frame(Title("#bf{Data SB}"));
  RooPlot *plot5 = candTMass.frame();
  plot1->SetAxisRange(600,3500,"X");
  plot2->SetAxisRange(600,3500,"X");
  plot3->SetAxisRange(600,3500,"X");
  plot4->SetAxisRange(600,3500,"X");
  plot5->SetAxisRange(600,3500,"X");

 // ---------------------------------------------------------------------------
 // -----------------  Dom SB region-- ---------------------------------
 // --------------------------------------------------------------------------


  Dom_SB.plotOn(plot2,Binning(xbins2),RooFit::Invisible());
  Dom_SB_pdf.plotOn( plot2,Name("error2"),VisualizeError(*fitres,1),LineColor(kBlack),FillColor(kGray),FillStyle(3002));
  Dom_SB.plotOn(plot2,Name("mc2"),Binning(xbins2),DrawOption("P"));
  Dom_SB_pdf.plotOn( plot2,Name("fit2"),Binning(xbins2),DrawOption("L"),LineWidth(3),LineColor(kGreen+2));
  Dom_SB_pdf.paramOn(plot2,Layout(0.50,0.9,0.6)) ;


  plot2->drawAfter("fit2","error2");
  plot2->drawAfter("error2","line");
  plot2->getAttText()->SetTextSize(0.03);
  plot2->SetMinimum(0.001);
  plot2->SetMaximum(1000);

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

if (plotDomSB) { plot2->Draw();}

  char result2[100];
  strcpy(result2,legTitle[key].c_str());
  strcat(result2," - SB Region");

  TLegend *leg2 = new TLegend(0.50,0.6,0.9,0.9);
  leg2->SetHeader(result2);
  leg2->AddEntry("mc2",  "Dominant Background ",    "ep");
  leg2->AddEntry("fit2","Exponential Fit", "l");
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


if (plotDomSB){  canvasMVZ2->SaveAs(Form("otherPlots/DomSB_MVZ%s.png",key.c_str()));}



  alpha->plotOn(plot3,RooFit::Invisible());
  alpha_pdf.plotOn(plot3,Name("1sigma"),VisualizeError(*fitres,1,kFALSE),FillStyle(1001),FillColor(kGreen),LineColor(kBlack));
  alpha_pdf.plotOn(plot3,Name("2sigma"),VisualizeError(*fitres,2,kFALSE),FillStyle(1001),FillColor(kYellow),LineColor(kBlack)); 
  alpha_pdf.plotOn(plot3,Name("mean"),DrawOption("L"),LineWidth(2),LineColor(kBlack));
//  alpha_pdf.paramOn(plot3,Layout(0.50,0.99,0.9)) ;
  plot3->drawAfter("2sigma","1sigma");
  plot3->drawAfter("1sigma","mean");
  plot3->SetTitle("");

  TText* te1 = new TText(800,140000,"CMS") ;
  te1->SetTextSize(0.03) ;
  te1->SetTextColor(kBlack) ;
  te1->SetTextFont(61);
  plot3->addObject(te1) ;

  TText* txt1a = new TText(800,135000,"Simulation") ;
  txt1a->SetTextSize(0.03) ;
  txt1a->SetTextColor(kBlack) ;
  txt1a->SetTextFont(52);
  plot3->addObject(txt1a) ;


  TText* txt2a = new TText(2500,155000,"2.307 /fb (13TeV)") ;
  txt2a->SetTextSize(0.03) ;
  txt2a->SetTextColor(kBlack) ;
  plot3->addObject(txt2a) ;


  plot3->GetYaxis()->SetTitle("");
  plot3->GetYaxis()->SetTitleSize(0.05);
  plot3->GetYaxis()->SetTitleOffset(0.85);
  plot3->GetXaxis()->SetTitleSize(0.05);
  plot3->GetXaxis()->SetTitleOffset(0.85);
  plot3->GetXaxis()->SetTitle("M_{T} (GeV)");
  plot3->SetMinimum(-5e3); 
  plot3->SetMaximum(150e3);


  TCanvas* canvasalpha = new TCanvas("alpha","alpha",800,800);
  if (plotalpha){  plot3->Draw();}

   TLegend *leg3 = new TLegend(0.30,0.6,0.8,0.9);
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



  if (plotalpha) {

       canvasalpha->SaveAs(Form("otherPlots/alpha2%s.png",key.c_str()));
       canvasalpha->SaveAs(Form("otherPlots/alpha2%s.pdf",key.c_str()));

}



 // ---------------------------------------------------------------------------
 // -----------------  FINAL PLOT ---------------------------------
 // --------------------------------------------------------------------------
 
  MC_est_pdf.plotOn(plot5,RooFit::Invisible());
  MC_est_pdf.plotOn( plot5,Name("error5"),Normalization(N),VisualizeError(*fitres,1),LineColor(kBlack),FillColor(kRed),FillStyle(3002));
//  MC_est_pdf.plotOn( plot5,Name("line5"),Binning(xbins2),Normalization(N), DrawOption("L"),LineWidth(2),LineColor(kBlack));
  MC_est_pdf.plotOn( plot5,Name("fit5"),Binning(xbins2),Normalization(N),VLines(),DrawOption("F"), FillColor(kAzure-9),LineColor(kWhite));
  Sub_SR_pdf.plotOn( plot5,Name("subfit5"),Binning(xbins2),Normalization(Nsub),VLines(),DrawOption("F"), FillColor(kOrange-4),LineColor(kWhite));
//  MC_est_pdf.paramOn(plot5,Layout(0.50,0.9,0.6)) ;
  Data_lSIG.plotOn( plot5,Name("Data"),Binning(xbins2));

  plot5->SetMinimum(0.001);
  plot5->SetMaximum(1000);


  plot5->drawAfter("fit5","error5");
  plot5->drawAfter("subfit5","error5");
/*
  plot5->drawAfter("fit5","subfit5");
//  plot5->drawAfter("error5","line5");
//  plot5->drawAfter("error5","Data");
  plot5->getAttText()->SetTextSize(0.03);
*/
  plot5->SetTitle("");
  plot5->GetXaxis()->SetTitle("M_{T} (GeV)");
  plot5->GetYaxis()->SetTitle("Events"); 
  plot5->GetYaxis()->SetTitleOffset(1.30);

   TText* tex1 = new TText(800,400,"CMS") ;
  tex1->SetTextSize(0.04) ;
  tex1->SetTextColor(kBlack) ;
  tex1->SetTextFont(61);
  plot5->addObject(tex1) ;

  TText* tex2 = new TText(800,200,"Preliminary") ;
  tex2->SetTextSize(0.04) ;
  tex2->SetTextColor(kBlack) ;
  tex2->SetTextFont(52);
  plot5->addObject(tex2) ;


  TText* tex3 = new TText(2500,1150,"2.307 /fb (13TeV)") ;
  tex3->SetTextSize(0.04) ;
  tex3->SetTextColor(kBlack) ;
  plot5->addObject(tex3) ;



  TCanvas* canvasMVZ5 = new TCanvas("canvasMVZ5","canvasMVZ5",800,800);
  canvasMVZ5->SetLogy();

  RooHist* hpull5 = plot5->pullHist("Data","fit5");
  RooPlot* Frame5pull = candTMass.frame(Range("fullRange"));
  Frame5pull->addPlotable(hpull5,"P");

  TPad* fPads5a = NULL;
  TPad* fPads5b = NULL;
  fPads5a = new TPad("pad5a", "", 0.00, 0.15, 0.99, 0.99);
  fPads5b = new TPad("pad5b", "", 0.00, 0.05, 0.99, 0.225);
  fPads5a->SetFillColor(0);
  fPads5a->SetLineColor(0);
  fPads5b->SetFillColor(0);
  fPads5b->SetLineColor(0);
  fPads5a->Draw();
  fPads5b->Draw();


  fPads5a->cd();
  fPads5a->SetLogy();
  plot5->GetYaxis()->SetTitleOffset(1.30);
  plot5->GetXaxis()->SetLabelSize(0);
  plot5->Draw();

   char result5[100];
   strcpy(result5,legTitle[key].c_str());
   strcat(result5," - Signal Region");

   TLegend *leg5 =new TLegend(0.40,0.7,0.9,0.9);
   leg5->SetHeader(result5);
   leg5->AddEntry("fit5",  "Dominant Background ",    "f");
   leg5->AddEntry("subfit5","Subdominant Background", "f");
   leg5->AddEntry("Data","data signal region", "P");
   leg5->SetTextSize(0.03);
   leg5->Draw();
   TLegendEntry *header5 = (TLegendEntry*)leg5->GetListOfPrimitives()->First();
   header5->SetTextAlign(22);
   header5->SetTextColor(1);
   header5->SetTextSize(.035);


  
  fPads5b->cd();
  fPads5b->SetGridx();
  fPads5b->SetGridy();
  fPads5b->SetTopMargin(0);
  fPads5b->SetBottomMargin(0.4);


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







  canvasMVZ5->SaveAs(Form("otherPlots/finalresultUB%s.png",key.c_str()));
  canvasMVZ5->SaveAs(Form("otherPlots/finalresultUB%s.pdf",key.c_str()));

}
