#include <iostream>
#include <utility>
#include <vector>

#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TApplication.h"
#include "TString.h"
#include "TH2.h"
#include "THStack.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TPaveText.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"

using namespace std;

void simplePlotter(){

  const unsigned int n = 6;

  TFile* ftt[n];

  // diboson
  char* names[n] = {"BB-4p-0-500_100TEV_40PileUp",
		    "BB-4p-500-1500_100TEV_40PileUp",
		    "BB-4p-1500-3000_100TEV_40PileUp",
		    "BB-4p-3000-5500_100TEV_40PileUp",
		    "BB-4p-5500-9000_100TEV_40PileUp",
		    "BB-4p-9000-100000_100TEV_40PileUp"};


  char* labels[n] = {"S*_{T} < 1 TeV","S*_{T} 1-2 TeV","S*_{T} 2-3.5 TeV","S*_{T} 3.5-5.5 TeV","S*_{T} 5.5-8.5 TeV","S*_{T} > 8.5 TeV"};

  int   colors[n] = { 2 , 3 , 4 , 5 , 6 , 7 };

  TH1F* hst[n];

  THStack* htstack = new THStack();

  TLegend *leg = new TLegend(0.5,0.5,0.8,0.8);

  for( int i = 0 ; i < n ; i++ ){

    ftt[i] = TFile::Open(Form("output/%s.root",names[i]));
    hst[i] = (TH1F*) ftt[i]->Get("st");
    hst[i]->SetFillColor(colors[i]);

    cout << "Integral " << i << " " << hst[i]->Integral() << endl;

    hst[i]->GetXaxis()->SetTitle("S_{T} [GeV]");
    hst[i]->GetYaxis()->SetTitle("events");

    leg->AddEntry( hst[i] , labels[i] , "lf" );

    htstack->Add(hst[i]);

  }

  TCanvas *c2 = new TCanvas("c2","c2",1200,600);
  c2->cd();
  gStyle->SetOptStat(0);

  gPad->SetLogy();
  htstack->Draw();
  htstack->GetXaxis()->SetTitle("S_{T} [GeV]");
  htstack->GetYaxis()->SetTitle("events");

  TLatex *t = new TLatex();
  t->SetNDC();
  t->DrawLatex(0.5,0.85,"t#bar{t} events, 100 TeV, L = 1 pb^{-1}");

  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->Draw();

}
