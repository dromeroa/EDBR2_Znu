R__LOAD_LIBRARY(../PDFs/HWWLVJRooPdfs_cxx.so)

void makeDataCardsWprime(std::string key, Int_t mass){


  using namespace RooFit;
  double VtagSF;
  double VtagUnSF;



  TFile *f = TFile::Open( Form("workSpaces/Workspace2/CMS_ZZnunu_%s_13TeV.root", key.c_str()));

  RooWorkspace* ZZnunu_13TeV = (RooWorkspace*) f->Get("ZZnunu_13TeV");


  TFile *sig  = TFile::Open(Form("workSpaces/Workspace2/Wprime/CMS_ZZnunu_Wprime_%s_%d_13TeV.root",  key.c_str(), mass));
  RooWorkspace* RSG = (RooWorkspace*) sig->Get("RSG");
  RooAbsPdf  *ZZ_sig = RSG->pdf(Form("RSG_%d",mass));

  // selection efficiency
  Double_t sel_eff =RSG ->var(Form("eff_%d",mass))->getVal();
  Double_t sig_xs_fb = 1.;           // signal cross section in fb
  Double_t target_lumi_fbInv = 2.307; // target luminosity in fb^-1

  // SF for the categorie in signal Yield
  if (key=="HP"){
                    VtagSF = 0.942;
                    VtagUnSF = 1.067/0.933;
  }
  else{
                    VtagSF = 1.268;
                    VtagUnSF = 0.74/1.26; 
  }
    
  // Signal yield   
  Double_t sigYield = target_lumi_fbInv * sel_eff * sig_xs_fb*VtagSF;

  ZZnunu_13TeV->import(*ZZ_sig);
  ZZnunu_13TeV->writeToFile(Form("workSpaces/Workspace2/Wprime/CMS_ZZnunu_bkgsig_%d_%s_13TeV.root",mass,key.c_str()));

  // create datacard
  const char *outFile = Form("dataCards/datacards2/Wprime/CMS_ZZnunu_%d_%s_13TeVTEST.txt",mass,key.c_str());
  std::ofstream ofs;
  ofs.open(outFile, std::ofstream::out);


  ofs << Form("imax 1\n");
  ofs << Form("jmax *\n");
  ofs << Form("kmax *\n");
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("shapes            %-10s         %-5s    workSpaces/CMS_ZZnunu_bkgsig_%d_%s_13TeV.root    %s\n", "*",        key.c_str(), mass, key.c_str(), "ZZnunu_13TeV:$PROCESS");
  ofs << Form("shapes            %-10s         %-5s    workSpaces/CMS_ZZnunu_bkgsig_%d_%s_13TeV.root    %s\n", "data_obs", key.c_str(), mass, key.c_str(), "ZZnunu_13TeV:data_obs");
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("bin               %s\n", key.c_str());
  ofs << Form("observation       %s\n",      "-1.0");
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("bin               %-10s         %-10s         %s\n",       key.c_str(),     key.c_str(),      key.c_str() );
  ofs << Form("process           %-10s         %-10s         %s\n", ZZ_sig->GetName(),        "Dom_pdf",        "Sub_pdf" );
  ofs << Form("process           %-10s         %-10s         %s\n",               "0",             "1",              "2" );
  ofs << Form("rate              %-10f         %-10s         %s\n",          sigYield,             "1",              "1" );
  ofs << Form("-----------------------------------------------------------------------------------\n");
  ofs << Form("Dom_pdf_norm                   lnU         %-10s    %.2f       %-5s\n", "1.",        ZZnunu_13TeV->var( "Dom_error")->getVal(), "1." );
//  ofs << Form("Dom_pdf_norm                   lnU         %-10s    %-5s      %s\n", "1.",     "1.06", "1." );
  ofs << Form("lumi_13TeV                     lnN         %-10s    %-5s      %s\n", "1.027",  "1.", "1." );
//ofs << Form("CMS_eff_vtag_tau21_sf_13TeV lnN %-10s %-5s %s\n", "1.1" , "1.", "1." );
  ofs << Form("CMS_eff_vtag_tau21_sf_13TeV    lnN         %.2f     %-5s      %-5s\n",  VtagUnSF,  "1.", "1." );
  ofs << Form("CMS_scale_j_13TeV              lnN         %-10s    %-5s      %s\n", "1.01" ,  "1.", "1." );
  ofs << Form("pdf_eig0                       param       %-10s    %s\n",    "0.",    "1." );
  ofs << Form("pdf_eig1                       param       %-10s    %s\n",    "0.",    "1." );
  ofs << Form("pdf_eig2                       param       %-10s    %s\n",    "0.",    "1." );
  ofs << Form("pdf_eig3                       param       %-10s    %s\n",    "0.",    "1." );
  ofs << Form("pdf_eig4                       param       %-10s    %s\n",    "0.",    "1." );
  ofs << Form("pdf_eig5                       param       %-10s    %s\n",    "0.",    "1." );

  ofs.close();
  
}


