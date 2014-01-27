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

//---------------------------------------------------------------------
// This is a simple macro that chains together the ST*-binned
// Delphes samples, checks the normalization of each one, and plots
// the ST distribution, which should be smooth if the correct weights
// have been used.
//---------------------------------------------------------------------

void sanityChecker(){

  //-------------------------------
  // choose PU scenario
  //-------------------------------

  char* PU = "NoPileUp";
  // char* PU = "40PileUp";
  // char* PU = "140PileUp";

  //-------------------------------
  // diboson filenames and labels
  //-------------------------------

  const unsigned int n = 6;

  char* names[n] = {Form("BB-4p-0-500_100TEV_%s",PU),
		    Form("BB-4p-500-1500_100TEV_%s",PU),
		    Form("BB-4p-1500-3000_100TEV_%s",PU),
		    Form("BB-4p-3000-5500_100TEV_%s",PU),
		    Form("BB-4p-5500-9000_100TEV_%s",PU),
		    Form("BB-4p-9000-100000_100TEV_%s",PU)};

  char* labels[n] = {"S*_{T} < 0.5 TeV",
		     "S*_{T} 0.5-1.5 TeV",
		     "S*_{T} 1.5-3.0 TeV",
		     "S*_{T} 3.0-5.5 TeV",
		     "S*_{T} 5.5-9.0 TeV",
		     "S*_{T} > 9.0 TeV"};

  //-------------------------------
  // ttbar filenames and labels
  //-------------------------------

  const unsigned int n = 6;

  chat* names[n] = {Form("tt-4p-0-1000_100TEV_%s",PU),
		    Form("tt-4p-1000-2000_100TEV_%s",PU),
		    Form("tt-4p-2000-3500_100TEV_%s",PU),
		    Form("tt-4p-3500-5500_100TEV_%s",PU),
		    Form("tt-4p-5500-8500_100TEV_%s",PU),
		    Form("tt-4p-8500-100000_100TEV_%s",PU)};

  char* labels[n] = {"S*_{T} < 1 TeV",
		     "S*_{T} 1-2 TeV",
		     "S*_{T} 2-3.5 TeV",
		     "S*_{T} 3.5-5.5 TeV",
		     "S*_{T} 5.5-8.5 TeV",
		     "S*_{T} > 8.5 TeV"};

  //--------------------------------------------
  // NO NEED TO MODIFY ANYTHING BELOW HERE
  //--------------------------------------------

  TFile* files[n];

  int   colors[n] = { 2 , 3 , 4 , 5 , 6 , 7 };

  TH1F* hst[n];
  TH1F* hstlo[n];

  THStack* htstack = new THStack();

  TLegend *leg = new TLegend(0.5,0.5,0.8,0.8);

  for( int i = 0 ; i < n ; i++ ){

    files[i] = TFile::Open(Form("output/%s.root",names[i]));
    hst[i] = (TH1F*) files[i]->Get("st");
    hstlo[i] = (TH1F*) files[i]->Get("stlo");
    hst[i]->SetFillColor(colors[i]);

    cout << endl;
    cout << "1 pb yields for sample " << names[i] << endl;
    cout << "LO yield  " << hstlo[i]->Integral() << endl;
    cout << "NLO yield " << hstlo[i]->Integral() << endl;

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
  t->DrawLatex(0.5,0.85,"100 TeV, L = 1 pb^{-1}");

  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->Draw();

}
