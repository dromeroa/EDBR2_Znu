
// FROM 24/07/2016
// FOR THE FINAL FIT OF THE TRASNVERSE MASS LOW PURITY
//
// FROM /afs/cern.ch/work/d/dromeroa/private/ALPHAMETHOD_Enero25/CMSSW_8_0_0_pre5/src/ALPHA_METHOD/TESTNEWCODE
// Do : >cmsenv (ROOT 6)
// FIRST WE NEED TO COMPILE THE LIBRARY HWWLVJRooPdfs_cxx.so
// root[] gSystem->Load("../PDFs/HWWLVJRooPdfs_cxx.so")
// root[] .x fitResultMTLP.C("LP")

#include "TMath.h"
#include "string.h"

void fitResultMTLP(std::string key)
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
  int plevelnorm1 = -1;
  int plevelnorm2 = 1;
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
  RooRealVar sigma1("sigma1", "sigma", 24, 0, 300);
  RooRealVar mu2("mu2", "average", 152, 0, 500);
  RooRealVar sigma2("sigma2", "sigma", 18, 0, 100);
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
  RooFitResult *rf1 = emodel1_pdf.fitTo(bkg1, Save(1), PrintLevel(plevelnorm1));
  RooFitResult *rf2 = emodel2_pdf.fitTo(bkg2, Save(1), PrintLevel(plevelnorm2));

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

  RooFormulaVar coef( "coef","@0/@1", RooArgList(Sub_SB_yield,Dom_SB_yield));

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
//                              III. PDFs (Transverse Mass)                       //
//                                                                                //     
//********************************************************************************//

 ////*********************************************************************************
 ////   10.  Expo tail PDF for Dominant Backround in SB
 ////********************************************************************************


  RooRealVar s0("s0","slope of the exp0", 1., 0., 200.);
  RooRealVar a0("a0","parameter of exp0", 1. , 0, 10);
  RooExpTailPdf Dom_SB_pdf("Dom_SB_pdf", "Dom in SB region", candTMass, s0,a0);
 ////******************************************************************************** 

 ////*********************************************************************************
 ////   11.  Expo tail PDF Dominant in SR
 ////********************************************************************************
 RooRealVar s1("s1","slope of the exp1", 1., 0., 200.);
 RooRealVar a1("a1","parameter of exp1", 0.03 , 0., 60);
 RooExpTailPdf Dom_SR_pdf("Dom_SR_pdf", "Dom in SR region", candTMass, s1,a1);
 ////********************************************************************************

 ////*********************************************************************************
 ////   12.  Expo Tail PDF for Data in SB
 ////********************************************************************************
 RooRealVar s2("s2","slope of the exp2", 1, 0.,200.);
 RooRealVar a2("a2","parameter of exp2", 0.03 , 0., 60);
 RooExpTailPdf Data_SB_pdf( "Data_SB_pdf", "Data in SB region", candTMass,s2,a2);
 ////*********************************************************************************


 RooRealVar s3("s3","slope of the exp3", 100., 0., 1000.);
 RooRealVar s4("s4","slope of the exp4", 100., 0., 1000.);

 RooRealVar a3("a3","parameter of exp3", 0.1 , 0.001, 10.);
 RooRealVar a4("a4","parameter of exp4", 0.1 , 0.001, 10.);

 RooExpTailPdf Sub_SR_pdf( "Sub_SR_pdf", "Sub in nominal region", candTMass,s3,a3);
 RooExpTailPdf Sub_SB_pdf("Sub_SB_pdf", "Sub in sideband region", candTMass,s4,a4);

  
  // The Products
  RooAddPdf Data_SB_pdf_2("Data_SB_pdf_2", "Model data in sideband", Sub_SB_pdf, Data_SB_pdf, coef);
  RooAlpha4ExpTailPdf alpha_pdf("alpha_pdf", "alpha function for Dom", candTMass,s1,a1,s0,a0);
  RooProdPdf MC_est_pdf("MC_est_pdf", "Data-driven bakground estimation", alpha_pdf, Data_SB_pdf);
//------------------------------------------------------------
  candTMass.setRange("range", 600., 2000);

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
  RooSimultaneous bigSample_pdf("bigSample_pdf", "simultaneous pdf", RooArgList(Dom_SR_pdf,Dom_SB_pdf,Data_SB_pdf_2), reg);

  // FINAL FIT  
  RooFitResult *fitres = bigSample_pdf.fitTo(bigSample, Save(1), Range("range"), SumW2Error(kTRUE), PrintLevel(-1));

  RooDataSet *alpha = alpha_pdf.generate(candTMass,1.e6);
  alpha->SetName("alpha");

//---------------------------------------------------------------------------------------------

  RooBinning xbins2(28,600,2000);
  RooPlot *plot3 = candTMass.frame();
  RooPlot *plot5 = candTMass.frame();
  plot3->SetAxisRange(600,2000,"X");
  plot5->SetAxisRange(600,2000,"X");


  // The alpha
  alpha->plotOn(plot3,RooFit::Invisible());
  alpha_pdf.plotOn(plot3,Name("1sigma"),VisualizeError(*fitres,1,kFALSE),FillStyle(1001),FillColor(kGreen),LineColor(kBlack));
  alpha_pdf.plotOn(plot3,Name("2sigma"),VisualizeError(*fitres,2,kFALSE),FillStyle(1001),FillColor(kYellow),LineColor(kBlack)); 
  alpha_pdf.plotOn(plot3,Name("mean"),DrawOption("L"),LineWidth(2),LineColor(kBlack));
  plot3->drawAfter("2sigma","1sigma");
  plot3->drawAfter("1sigma","mean");

  plot3->SetTitle("");

  TText* te1 = new TText(700,47000,"CMS") ;
  te1->SetTextSize(0.03) ;
  te1->SetTextColor(kBlack) ;
  te1->SetTextFont(61);
  plot3->addObject(te1) ;

  TText* txt1a = new TText(700,45000,"Simulation") ;
  txt1a->SetTextSize(0.03) ;
  txt1a->SetTextColor(kBlack) ;
  txt1a->SetTextFont(52);
  plot3->addObject(txt1a) ;


  TText* txt2a = new TText(1600,51000,"2.318 /fb (13TeV)") ;
  txt2a->SetTextSize(0.03) ;
  txt2a->SetTextColor(kBlack) ;
  plot3->addObject(txt2a) ;

  plot3->GetYaxis()->SetTitle("");
  plot3->GetYaxis()->SetTitleSize(0.05);
  plot3->GetYaxis()->SetTitleOffset(0.85);
  plot3->GetXaxis()->SetTitleSize(0.05);
  plot3->GetXaxis()->SetTitleOffset(0.85);
  plot3->GetXaxis()->SetTitle("M_{T} (GeV)");
  plot3->SetMinimum(0); 
  plot3->SetMaximum(50e3);


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
   canvasalpha->SaveAs(Form("otherPlots/alpha%s.pdf",key.c_str())); 


 // ---------------------------------------------------------------------------
 // -----------------  FINAL PLOT ---------------------------------
 // --------------------------------------------------------------------------
 
  MC_est_pdf.plotOn(plot5,RooFit::Invisible());
  MC_est_pdf.plotOn( plot5,Name("error5"),Normalization(N),VisualizeError(*fitres,1),LineColor(kBlack),FillColor(kRed),FillStyle(3002));
  MC_est_pdf.plotOn( plot5,Name("fit5"),Binning(xbins2),Normalization(N),VLines(),DrawOption("F"), FillColor(kAzure-9),LineColor(kWhite));
  Sub_SR_pdf.plotOn( plot5,Name("subfit5"),Binning(xbins2),Normalization(Nsub),VLines(),DrawOption("F"), FillColor(kOrange-4),LineColor(kWhite));

  plot5->GetXaxis()->SetTitle("M_{T} (GeV)");
  plot5->GetYaxis()->SetTitle("Events");
  plot5->GetYaxis()->SetTitleOffset(1.30);
  plot5->SetTitle("");

  plot5->drawAfter("fit5","error5");
  plot5->drawAfter("fit5","subfit5");
  plot5->SetMinimum(0.01);
  plot5->SetMaximum(1000);


   TText* tex1 = new TText(700,400,"CMS") ;
  tex1->SetTextSize(0.04) ;
  tex1->SetTextColor(kBlack) ;
  tex1->SetTextFont(61);
  plot5->addObject(tex1) ;

  TText* tex2 = new TText(700,200,"Preliminary") ;
  tex2->SetTextSize(0.04) ;
  tex2->SetTextColor(kBlack) ;
  tex2->SetTextFont(52);
  plot5->addObject(tex2) ;


  TText* tex3 = new TText(1600,1100,"2.318 /fb (13TeV)") ;
  tex3->SetTextSize(0.03) ;
  tex3->SetTextColor(kBlack) ;
  plot5->addObject(tex3) ;


  TCanvas* canvasMVZ5 = new TCanvas("canvasMVZ5","canvasMVZ5",800,800);
  canvasMVZ5->SetLogy();

  plot5->Draw();


   char result5[100];
   strcpy(result5,legTitle[key].c_str());
   strcat(result5," - Signal Region");

   TLegend *leg5 =new TLegend(0.40,0.7,0.9,0.9);
   leg5->SetHeader(result5);
   leg5->AddEntry("fit5",  "Dominant Background ",    "f");
   leg5->AddEntry("subfit5","Subdominant Background", "f");
   leg5->SetTextSize(0.03);
   leg5->Draw();
   TLegendEntry *header5 = (TLegendEntry*)leg5->GetListOfPrimitives()->First();
   header5->SetTextAlign(22);
   header5->SetTextColor(1);
   header5->SetTextSize(.035);

  canvasMVZ5->SaveAs(Form("otherPlots/finalresult%s.png",key.c_str()));
  canvasMVZ5->SaveAs(Form("otherPlots/finalresult%s.pdf",key.c_str()));

}
