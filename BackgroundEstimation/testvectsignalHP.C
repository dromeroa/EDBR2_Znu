
void testvectsignalHP(std::string key){

  using namespace RooFit;

  RooMsgService::instance().setGlobalKillBelow(FATAL);

  std::map<std::string, std::string> selection;

  selection["HP"] = "tau21<0.45";
  selection["LP"] = "tau21>0.45 && tau21<0.75 ";

  TCut mycut = selection[key].c_str();

  std::map<std::string, std::string> legTitle;
  legTitle["HP"]="High Purity";
  legTitle["LP"]="Low Purity";


  std::vector<std::string> files;

  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_4500_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_4000_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_3500_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_3000_76xs_v2.root");
/*
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_2500_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_2000_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_1800_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_1600_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_1400_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_1200_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_1000_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_800_76xs_v2.root");

*/


  RooRealVar candTMass("candTMass","VZ candidate mass", 600., 5000., "GeV");
  RooRealVar massVhad("massVhad","M_{j}" ,             65.,  105., "GeV");
  RooRealVar tau21("tau21","tau21",                     0.,  0.75       );
  RooRealVar totalWeight("totalWeight","totalWeight",      -10,    10.      );
  RooArgSet variables(candTMass,massVhad,tau21,totalWeight);



/*
 
  // VARIABLE SIGMA

  std::map<std::string, Double_t> low, Mass, upp;
  low["800"] = 600; Mass["800"] = 750; upp["800"] = 900;
  low["1000"] = 650; Mass["1000"] = 914; upp["1000"] = 1177;
  low["1200"] = 650; Mass["1200"] = 991.5; upp["1200"] = 1350;
  low["1400"] = 670; Mass["1400"] = 1120; upp["1400"] = 1570;
  low["1600"] = 1200; Mass["1600"] = 1554.1; upp["1600"] = 1800;
  low["1800"] = 1400; Mass["1800"] = 1754.1; upp["1800"] = 2100;
  low["2000"] = 1530.; Mass["2000"] = 1950.; upp["2000"] = 2370.;
  low["2500"] = 1900.; Mass["2500"] = 2450.; upp["2500"] = 3000.;
  low["3000"] = 2270.; Mass["3000"] = 2950.; upp["3000"] = 3630.;
  low["3500"] = 2640.; Mass["3500"] = 3450.; upp["3500"] = 4260.;
  low["4000"] = 3008.; Mass["4000"] = 3950.; upp["4000"] = 4892.;
  low["4500"] = 3400.; Mass["4500"] = 4450.; upp["4500"] = 5500.;
*/


  // 2 SIGMA
  std::map<std::string, Double_t> low, Mass, upp;

  low["800"] = 600; Mass["800"] = 760; upp["800"] = 900; // here 1 sigma to no be complete the interval
  low["1000"] = 633; Mass["1000"] = 957; upp["1000"] = 1281;
  low["1200"] = 743; Mass["1200"] = 1158; upp["1200"] = 1573;
  low["1400"] = 852; Mass["1400"] = 1370; upp["1400"] = 1888;
  low["1600"] = 935; Mass["1600"] = 1554; upp["1600"] = 2173;
  low["1800"] = 1031; Mass["1800"] = 1756; upp["1800"] = 2481;
  low["2000"] = 1119; Mass["2000"] = 1951.; upp["2000"] = 2783;
  low["2500"] = 1357; Mass["2500"] = 2452.; upp["2500"] = 3547;
  low["3000"] = 1547.; Mass["3000"] = 2936; upp["3000"] = 4298.;
  low["3500"] = 1812; Mass["3500"] = 3432; upp["3500"] = 5052;
  low["4000"] = 2013; Mass["4000"] = 3915; upp["4000"] = 5800;
  low["4500"] = 2263; Mass["4500"] = 4415.; upp["4500"] = 6557;


  std::map<std::string, Int_t> nEvents;
  nEvents["800"] = 100000;
  nEvents["1000"] = 100000;
  nEvents["1200"] = 99200;
  nEvents["1400"] = 100000;
  nEvents["1600"] = 100000;
  nEvents["1800"] = 100000;
  nEvents["2000"] = 100000;
  nEvents["2500"] = 100000;
  nEvents["3000"] = 99200;
  nEvents["3500"] = 100000;
  nEvents["4000"] = 100000;
  nEvents["4500"] = 99200;

  std::vector<double> MEAN, SIGMA, ALPHA, EFF;

  // single crystal ball
  RooRealVar mean("mean","mean of the Crystal Ball",800.,600.,5000.);
  RooRealVar sigma("sigma","Crystal Ball sigma",100.,1.,200.);
  RooRealVar alpha("alpha","alpha",  1.42273e-01, 0., 3.);
  RooRealVar n("n","n", 5.,0., 10.); 
  n.setConstant(true);  

  while( !files.empty() ){
    std::string mass = files.back().substr(43,4);
    if(mass[3]=='_') mass.pop_back();
    mean.setVal(Mass[mass]);
    mean.setRange(low[mass],upp[mass]);

    RooCBShape ZZ_sig("ZZ_sig", "Crystall Ball Shape",candTMass,mean,sigma,alpha,n);

    TChain t("treeDumper/EDBRCandidates");
    t.Add(files.back().c_str());

    RooDataSet ds("ds","ds",variables,WeightVar(totalWeight),Cut(mycut),Import(t));

    ZZ_sig.fitTo(ds, Minimizer("Minuit"), Range(low[mass],upp[mass]), SumW2Error(kTRUE), PrintLevel(-1));

//    ZZ_sig.fitTo(ds,SumW2Error(kTRUE), PrintLevel(-1));

//    ZZ_sig.fitTo(ds, Minimizer("Minuit"), Range(low[mass],upp[mass]), SumW2Error(kTRUE));

    RooPlot* frame1 = candTMass.frame();

    ds.plotOn(frame1,Name("mc1"));

    ZZ_sig.plotOn(frame1,Name("fitmc1"),LineColor(kBlue));


//    ZZ_sig.paramOn(frame1,Layout(0.53,0.9,0.7));
    ZZ_sig.paramOn(frame1,Layout(0.1,0.40,0.7));
    frame1->getAttText()->SetTextSize(0.03);

    frame1->SetTitle("");  

/*
  TText* tex1 = new TText(4000,19,"CMS") ;
  tex1->SetTextSize(0.04) ;
  tex1->SetTextColor(kBlack) ;
  tex1->SetTextFont(61);
  frame1->addObject(tex1) ;

  TText* tex2 = new TText(4000,18,"Preliminary") ;
  tex2->SetTextSize(0.04) ;
  tex2->SetTextColor(kBlack) ;
  tex2->SetTextFont(52);
  frame1->addObject(tex2) ;


  TText* tex3 = new TText(3500,22,"2.307 /fb (13TeV)") ;
  tex3->SetTextSize(0.04) ;
  tex3->SetTextColor(kBlack) ;
  frame1->addObject(tex3) ;
*/   

    TCanvas cv("cv","cv",800,800);
    // The pulls
    RooHist* hpull = frame1->pullHist();
    RooPlot* frame1a = candTMass.frame();
    frame1a->addPlotable(hpull,"P") ;
    // Chi square
    Double_t chi2 = frame1->chiSquare("fitmc1", "mc1", 3);
    // the pads
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
    // first pad
    fPads1->cd();
    frame1->GetYaxis()->SetTitleOffset(1.30);
    frame1->GetXaxis()->SetLabelSize(0);
    frame1->Draw();
    // The legend
    char result[100], result2[100];
    strcpy(result,legTitle[key].c_str());
    strcat(result," - Mass = ");
    strcpy(result2, mass.c_str());
    strcat(result,result2);
    strcat(result," GeV");

//    TLegend *leg1 = new TLegend(0.53,0.7,0.9,0.9);
    TLegend *leg1 = new TLegend(0.1,0.7,0.40,0.9);

    leg1->SetHeader(result);
    leg1->AddEntry("mc1",  "MC Signal ",    "ep");
    leg1->AddEntry("fitmc1"," Crystal ball Fit", "l");
    leg1->SetTextSize(0.03);
    leg1->Draw();
    TLegendEntry *header1 = (TLegendEntry*)leg1->GetListOfPrimitives()->First();
    header1->SetTextAlign(22);
    header1->SetTextColor(1);
//    header1->SetTextSize(.035);
     header1->SetTextSize(.025);

    // second pad
    fPads2->cd();
    fPads2->SetGridx();
    fPads2->SetGridy();
    fPads2->SetTopMargin(0);
    fPads2->SetBottomMargin(0.4);
    frame1a->GetYaxis()->SetLabelSize(0.08);
    frame1a->GetXaxis()->SetLabelSize(0.17);
    frame1a->GetYaxis()->SetTitle("Pulls");
    frame1a->GetXaxis()->SetTitle("VZ Candidate transverse mass (GeV)");
    frame1a->GetYaxis()->SetTitleOffset(0.30);
    frame1a->GetYaxis()->SetTitleSize(0.15);
    frame1a->GetXaxis()->SetTitleSize(0.17);
    frame1a->GetYaxis()->SetRangeUser(-5,5);
    frame1a->SetTitle("");
    frame1a->Draw();
    TPaveLabel *t1 = new TPaveLabel(0.7,0.85,0.9,1, Form("#chi^{2}/dof = %f", chi2),"brNDC");
    t1->Draw();

    cv.SaveAs(Form("othersignalPlots/testplots/signalSIG%s.pdf",(key+mass).c_str()));

    files.pop_back();

   }

}
