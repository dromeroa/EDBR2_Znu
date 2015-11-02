//// This script take boths histograms in pile MC and data and generate an histogram of weights

//// Usage : root -l Pileup_reweight_gen.C

#include <TF1.h>
#include <TFile.h>
#include <TH1F.h>
#include <TCanvas.h>


void Pileup_reweight_gen() {

   TFile *f1 = new TFile("MyDataPileupHistogram_true.root");
   TH1D *hPU_data = (TH1D*)f1->Get("pileup");  

   TFile *f2 = new TFile("PU_MC_histo.root");
   TH1D *hPU_MC = (TH1D*)f2->Get("PU_MC");

   hPU_data->Scale(1.0/hPU_data->Integral());
   hPU_MC->Scale(1.0/hPU_MC->Integral());

   TH1D *pileupWeights = new TH1D("pileupWeights", "Computed Weights", 52, 0., 52);


  std::vector<double> weights(hPU_data->GetNbinsX()+1, 1.0);

  for (int i = 1, n = weights.size(); i < n; ++i) {
        double nMC = hPU_MC->GetBinContent(i), nData = hPU_data->GetBinContent(i);
        weights[i-1] = (nMC > 0 ? nData/nMC : 1.0);
        pileupWeights->SetBinContent(i,weights[i-1]);
    }

  
     pileupWeights->Draw(); 

   TFile *outFile = new TFile("pileupWeights.root", "RECREATE");
   outFile->cd();
   pileupWeights->Write();
   outFile->Close();



}

