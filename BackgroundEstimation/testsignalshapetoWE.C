
void signalshapetoWE(std::string key){

  using namespace RooFit;

  RooMsgService::instance().setGlobalKillBelow(FATAL);

  std::map<std::string, std::string> selection;

  selection["HP"] = "tau21<0.45";
  selection["LP"] = "tau21>0.45 && tau21<0.75 ";

  TCut mycut = selection[key].c_str();



  std::vector<std::string> files;


//  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_800_76xs_v2.root"); 
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_1000_76xs_v2.root");
/*
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_1200_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_1400_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_1600_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_1800_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_2000_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_2500_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_3000_76xs_v2.root");
  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_3500_76xs_v2.root");
//  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_4000_76xs_v2.root");
//  files.push_back("../trees/newtrees/treeEDBR_RSGravZZToZZinv_4500_76xs_v2.root");

*/

  RooRealVar candTMass("candTMass","VZ candidate mass", 600., 3500., "GeV");
  RooRealVar massVhad("massVhad","M_{j}" ,             65.,  105., "GeV");
  RooRealVar tau21("tau21","tau21",                     0.,  1.       );
  RooRealVar totalWeight("totalWeight","totalWeight",      0.,    10.      );
  RooArgSet variables(candTMass,massVhad,tau21,totalWeight);

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

  nEvents["800"]  =  100000;
  nEvents["1000"] =  100000;
  nEvents["1200"] =   99200;
  nEvents["1400"] =  100000;
  nEvents["1600"] =  100000;
  nEvents["1800"] =  100000;
  nEvents["2000"] =  100000;
  nEvents["2500"] =  100000;
  nEvents["3000"] =   99200;
  nEvents["3500"] =  100000;
//  nEvents["4000"] = 100000;
//  nEvents["4500"] = 99200;




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
    EFF.push_back( (double)ds.numEntries()/nEvents[mass] );


    ZZ_sig.fitTo(ds, Minimizer("Minuit"), Range(low[mass],upp[mass]), SumW2Error(kTRUE), PrintLevel(-1));
    
    MEAN.push_back( mean.getVal() );
    SIGMA.push_back( sigma.getVal() );
    ALPHA.push_back( alpha.getVal() );

    files.pop_back();
  }


   Double_t x[12]={800.,1000.,1200.,1400.,1600.,1800.,2000.,2500.,3000.,3500.,4000.,4500};
   TGraph *gmean = new TGraph(12, x, &(MEAN[0]) );
   TGraph *gsigma = new TGraph(12, x, &(SIGMA[0]) );
   TGraph *galpha = new TGraph(12, x, &(ALPHA[0]) );
   TGraph *geff = new TGraph(12, x, &(EFF[0]) );

//   RooWorkspace *w = new RooWorkspace("RSG","workspace");

  for(Double_t i=800.; i<=4500.; i+=100.){

     RooWorkspace *w = new RooWorkspace("RSG","workspace");

     RooRealVar _mean(  Form("mean_%.0f",  i), "mean of the Crystal Ball",800.,600.,5000.);
     RooRealVar _sigma( Form("sigma_%.0f", i), "Crystal Ball sigma",50.,1.,100.);
     RooRealVar _alpha(Form("alpha_%.0f",i), "alpha",  1.5, 1., 3.);
     _mean.setVal(   gmean->Eval(   i ) );
     _sigma.setVal(  gsigma->Eval(  i ) );
     _alpha.setVal( galpha->Eval( i ) );

     RooCBShape ZZ_sig(Form("RSG_%.0f",i),"Single Crystall Ball",candTMass,_mean,_sigma,_alpha, n);
     _mean.setConstant(   true );
     _sigma.setConstant(  true );
     _alpha.setConstant( true );
     w->import(ZZ_sig);

     RooRealVar eff(Form("eff_%.0f",i),"signal efficiency", 0.1, 0., 1.);
     eff.setVal( geff->Eval(i) );
     w->import(eff);

     w->writeToFile(Form("workSpaces/CMS_ZZnunu_RSG_%s_%.0f_13TeV.root", key.c_str(),i));

  }






}
