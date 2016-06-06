

SignalShapes(std::string key){

  using namespace RooFit;

  std::map<std::string, std::string> selection;
  selection["HP"] = "tau21<0.45";
  selection["LP"] = "tau21>0.45 && tau21<0.75 ";

  TCut mycut = selection[key].c_str();

  std::vector<std::string> files;

  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-4500_el.root");
  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-4000_el.root");
  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-3500_el.root");
  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-3000_el.root");
  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-2500_el.root");
  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-2000_el.root");
  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1800_el.root");
  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1600_el.root");
  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1400_el.root");
  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1200_el.root");
  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-1000_el.root");
  files.push_back("trees/treeEDBR_BulkGravToZZToZlepZhad_M-800_el.root");



  RooRealVar candTMass("candTMass","VZ candidate mass", 600., 5000., "GeV");
  RooRealVar massVhad("massVhad","M_{j}" ,             65.,  105., "GeV");
  RooRealVar tau21("tau21","tau21",                     0.,  0.75       );
  RooRealVar totalWeight("totalWeight","totalWeight",      0.,    10.      );
  RooArgSet variables(candTMass,massVhad,tau21,totalWeight);


  // Total number of signal events
  std::map<std::string, Int_t> nEvents;
  nEvents["800"]  = 50000;
  nEvents["1000"] = 100000;
  nEvents["1200"] = 100000;
  nEvents["1400"] = 49200;
  nEvents["1600"] = 50000;
  nEvents["1800"] = 50000;
  nEvents["2000"] = 48400;
  nEvents["2500"] = 50000;
  nEvents["3000"] = 50000;
  nEvents["3500"] = 50000;
  nEvents["4000"] = 50000;

  
  std::vector<double> MEAN, SIGMA, ALPHA, EFF;

  // Single crystal ball
  RooRealVar mean("mean","mean of the Crystal Ball",800.,600.,5000.);
  RooRealVar sigma("sigma","Crystal Ball sigma",100.,1.,200.);
  RooRealVar alpha("alpha","alpha left",  1, 0., 3.);
  RooRealVar n("n","n", 2.,1., 2.); n.setConstant(true);

  RooCBShape ZZ_sig("ZZ_sig", "Crystall Ball Shape",candTMass,mean,sigma,alpha,n);


    while( !files.empty() ){
     std::string mass = files.back().substr(40,4);
     if(mass[3]=='_') mass.pop_back();
     mean.setVal(Mass[mass]);
     mean.setRange(low[mass],upp[mass]);

     RooDoubleCrystalBall ZZ_sig("ZZ_sig","Double Crystall Ball",candTMass,mean,sigma,alphaL,nL,alphaR,nR);
 
     TChain t("treeDumper/EDBRCandidates");
     t.Add(files.back().c_str());

     RooDataSet ds("ds","ds",variables,WeightVar(totalWeight),Cut(mycut),Import(t));
     // selection efficiency
     EFF.push_back( (double)ds.numEntries()/nEvents[mass] );
     ZZ_sig.fitTo(ds, Minimizer("Minuit"), Range(low[mass],upp[mass]), SumW2Error(kTRUE), PrintLevel(-1));
     MEAN.push_back(     mean.getVal() );
     SIGMA.push_back(   sigma.getVal() );
     ALPHAL.push_back( alphaL.getVal() );
     ALPHAR.push_back( alphaR.getVal() );
     files.pop_back();
    }





