
void sig_eff(){

   gROOT->SetStyle("Plain");

   TCanvas *c1 = new TCanvas("c1","cv1",800,800);
   c1->SetGridx();
   c1->SetGridy();

//  TH1F *hotro = new TH1F("hotro","Signal Efficiency",10,0,10);



Double_t eff1x[10] = {
800,
1000,
1200,
1400,
1600,
1800,
2000,
2500,
3000,
3500
};


/*
Double_t eff1y[10] = {
0.2207,
0.30972,
0.35365,
0.37991,
0.39947,
0.40915,
0.41467,
0.42248,
0.42125,
0.42628
};

TGraph *graph = new TGraph(10,eff1x,eff1y);
graph->SetName("bulkToZZ");
graph->SetFillColor(1);
graph->SetLineColor(kBlack);
graph->SetLineWidth(2);
graph->SetMarkerStyle(20);
graph->SetMarkerSize(2);
graph->SetMarkerColor(kBlue);
graph->GetYaxis()->SetRangeUser(0.,0.5);
graph->GetYaxis()->SetTitle("Efficiency");
graph->GetXaxis()->SetTitle("Graviton Mass (GeV)");
graph->SetTitle("");
graph->GetYaxis()->SetTitleOffset(1.20);
graph->GetYaxis()->SetLabelSize(0.04);
graph->Draw();

*/




Double_t eff2x[10] = {
800,
1000,
1200,
1400,
1600,
1800,
2000,
2500,
3000,
3500
};


Double_t eff2y[10] = {
0.1207,
0.16772,
0.189052,
0.19746,
0.20149,
0.2055,
0.20505,
0.19915,
0.187157,
0.18326
};

TGraph *graph = new TGraph(10,eff2x,eff2y);
graph->SetName("bulkToZZ");
graph->SetFillColor(1);
graph->SetLineColor(kBlack);
graph->SetLineWidth(2);
graph->SetMarkerStyle(20);
graph->SetMarkerSize(2);
graph->SetMarkerColor(kBlue);
graph->GetYaxis()->SetRangeUser(0.,0.4);
graph->GetYaxis()->SetTitle("Efficiency");
graph->GetXaxis()->SetTitle("Graviton Mass (GeV)");
graph->SetTitle("");
graph->GetYaxis()->SetTitleOffset(1.30);
graph->GetYaxis()->SetLabelSize(0.03);
graph->Draw();


//------------------



/*

TGraph *graph2 = new TGraph(10,eff2x,eff2y);
graph2->SetName("HP");
graph2->SetFillColor(1);
graph2->SetLineColor(kBlack);
graph2->SetLineWidth(2);
graph2->SetMarkerStyle(21);
graph2->SetMarkerSize(2);
graph2->SetMarkerColor(kRed);
graph2->GetYaxis()->SetRangeUser(0.,0.7);
graph2->Draw("sameCP");

*/

Double_t eff3x[10] = {
800,
1000,
1200,
1400,
1600,
1800,
2000,
2500,
3000,
3500
};


Double_t eff3y[10] = {
0.04899,
0.0766,
0.0930242,
0.10311,
0.11656,
0.12192,
0.128,
0.14142,
0.147671,
0.15261
};

TGraph *graph3 = new TGraph(10,eff3x,eff3y);
graph3->SetName("LP");
graph3->SetFillColor(1);
graph3->SetLineColor(kBlack);
graph3->SetLineWidth(2);
graph3->SetMarkerStyle(21);
graph3->SetMarkerSize(2);
graph3->SetMarkerColor(kRed);
graph3->GetYaxis()->SetRangeUser(0.,0.7);
graph3->Draw("sameCP");


 graph->SetName("g2");
// graph2->SetName("g2");
 graph3->SetName("g3");

  TLegend *leg1c = new TLegend(0.53,0.62,0.9,0.9);
  leg1c->SetHeader("G_{RS} -> ZZ");
//  leg1c->AddEntry("g1",  "No Purity ",    "p");
  leg1c->AddEntry("g2","High Purity", "p");
 leg1c->AddEntry("g3","Low Purity", "p");
  leg1c->SetTextSize(0.03);
  leg1c->Draw();
  TLegendEntry *header1c = (TLegendEntry*)leg1c->GetListOfPrimitives()->First();
  header1c->SetTextAlign(22);
  header1c->SetTextColor(1);
  header1c->SetTextSize(.045);


  TText* tx7 = new TText(700,0.35,"CMS") ;
  tx7->SetTextSize(0.04) ;
  tx7->SetTextColor(kBlack) ;
  tx7->SetTextFont(61);
  tx7->Draw() ;

  TText* tx8 = new TText(700,0.32,"Simulation") ;
  tx8->SetTextSize(0.04) ;
  tx8->SetTextColor(kBlack) ;
  tx8->SetTextFont(52);
  tx8->Draw();


  TText* tx9 = new TText(2600,0.72,"2.307 /fb (13TeV)") ;
  tx9->SetTextSize(0.04) ;
  tx9->SetTextColor(kBlack) ;
  tx9->Draw();


c1->SaveAs("efficiency2.png");
c1->SaveAs("efficiency2.pdf");

}
