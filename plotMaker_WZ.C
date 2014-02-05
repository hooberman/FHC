#include <iostream>
#include <utility>
#include <vector>

#include "TROOT.h"
#include "TCut.h"
#include "TStyle.h"
#include "TChain.h"
#include "TLatex.h"
#include "TSystem.h"
#include "TApplication.h"
#include "TString.h"
#include "TH2.h"
#include "THStack.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TPaveText.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"

using namespace std;


void makePlot( vector<TChain*> samples , vector<string> names , char* var , TCut sel , TCut weight , int nbin , float xmin , float xmax ){
  
  const unsigned int n = samples.size();

  TH1F* h[n];

  TCanvas* can = new TCanvas(Form("%s_can",var),Form("%s_can",var),800,600);
  can->cd();

  int colors[]     = {kBlue-10,kGreen+2,kRed+3};
  int linecolors[] = {1,2,4,kMagenta};

  THStack* t = new THStack(Form("%s_stack",var),Form("%s_stack",var));
  TH1F* bkgtot = new TH1F();

  int   nbkg = 0;
  float ymax = 0;

  TLegend* leg = new TLegend(0.6,0.6,0.8,0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);

  //TCut nj2("njets==2");
  //TCut nj2("");

  for( unsigned int i = 0 ; i < n ; i++ ){
    if( TString(names.at(i)).Contains("sig")  ) continue;
    h[i] = new TH1F(Form("hist_%s_%s",names.at(i).c_str(),var),"",nbin,xmin,xmax);
    //samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%s",var,xmax-0.0001,names.at(i).c_str(),var),(sel+nj2)*weight);
    samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%s",var,xmax-0.0001,names.at(i).c_str(),var),(sel)*weight);
    h[i]->SetFillColor(colors[i]);
    cout << "Intregal " << names.at(i) << " " << h[i]->Integral() << endl;
    t->Add(h[i]);
    nbkg++;
    ymax += h[i]->GetMaximum();
    leg->AddEntry(h[i],names.at(i).c_str(),"f");
    if( i==0 ) bkgtot = (TH1F*) h[i]->Clone("bkgtot");
    else bkgtot->Add(h[i]);
  }

  for( unsigned int i = 0 ; i < n ; i++ ){
    if( !TString(names.at(i)).Contains("sig") ) continue;
    h[i] = new TH1F(Form("hist_%s_%s",names.at(i).c_str(),var),"",nbin,xmin,xmax);
    samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%s",var,xmax-0.0001,names.at(i).c_str(),var),sel*weight);
    cout << "Intregal " << names.at(i) << " " << h[i]->Integral() << endl;
    leg->AddEntry(h[i],names.at(i).c_str(),"l");
    //h[i]->Add(bkgtot);
  }

  TH2F* hdummy = new TH2F("hdummy","",nbin,xmin,xmax,100,1,2*ymax);
  gPad->SetLogy();
  hdummy->Draw();

  t->Draw("same");
  for( unsigned int isig = nbkg ; isig < n ; isig++ ){
    //h[isig]->Scale(10);
    h[isig]->SetLineColor(linecolors[isig-nbkg]);
    h[isig]->SetLineWidth(2);
    h[isig]->Draw("samehist");
  }

  leg->Draw();
  hdummy->Draw("axissame");

}

void plotMaker_WZ(){

  char* version    = (char*) "V00-00-02";
  char* sigversion = (char*) "V00-00-03";
  //char* filter     = (char*) "";
  char* filter     = (char*) "_nleps3";

  //---------------------------------
  // load ttbar samples
  //---------------------------------

  // TChain* chtt = new TChain("t");
  // chtt->Add(Form("output/%s/tt-4p-0-1000_100TEV_NoPileUp_baby.root",version));
  // chtt->Add(Form("output/%s/tt-4p-1000-2000_100TEV_NoPileUp_baby.root",version));
  // chtt->Add(Form("output/%s/tt-4p-2000-3500_100TEV_NoPileUp_baby.root",version));
  // chtt->Add(Form("output/%s/tt-4p-3500-5500_100TEV_NoPileUp_baby.root",version));
  // chtt->Add(Form("output/%s/tt-4p-5500-8500_100TEV_NoPileUp_baby.root",version));
  // chtt->Add(Form("output/%s/tt-4p-8500-100000_100TEV_NoPileUp_baby.root",version));
  // cout << "tt entries " << chtt->GetEntries() << endl;

  //---------------------------------
  // load W samples
  //---------------------------------

  // TChain* chw = new TChain("t");
  // chw->Add(Form("output/%s/Bj-4p-0-500_100TEV_NoPileUp_baby.root",version));
  // chw->Add(Form("output/%s/Bj-4p-500-1500_100TEV_NoPileUp_baby.root",version));
  // chw->Add(Form("output/%s/Bj-4p-1500-3000_100TEV_NoPileUp_baby.root",version));
  // chw->Add(Form("output/%s/Bj-4p-3000-5500_100TEV_NoPileUp_baby.root",version));
  // chw->Add(Form("output/%s/Bj-4p-5500-9000_100TEV_NoPileUp_baby.root",version));
  // chw->Add(Form("output/%s/Bj-4p-9000-100000_100TEV_NoPileUp_baby.root",version));
  // cout << "W entries " << chw->GetEntries() << endl;


  //---------------------------------
  // load diboson samples
  //---------------------------------

  TChain* chvv = new TChain("t");
  chvv->Add(Form("output/%s/BB-4p-0-500_100TEV_NoPileUp_baby%s.root",version,filter));
  chvv->Add(Form("output/%s/BB-4p-500-1500_100TEV_NoPileUp_baby%s.root",version,filter));
  chvv->Add(Form("output/%s/BB-4p-1500-3000_100TEV_NoPileUp_baby%s.root",version,filter));
  chvv->Add(Form("output/%s/BB-4p-3000-5500_100TEV_NoPileUp_baby%s.root",version,filter));
  chvv->Add(Form("output/%s/BB-4p-5500-9000_100TEV_NoPileUp_baby%s.root",version,filter));
  chvv->Add(Form("output/%s/BB-4p-9000-100000_100TEV_NoPileUp_baby%s.root",version,filter));
  cout << "VV entries " << chvv->GetEntries() << endl;

  //---------------------------------
  // signal samples
  //---------------------------------

  TChain* WZ1 = new TChain("t");
  TChain* WZ2 = new TChain("t");
  //TChain* WZ3 = new TChain("t");
  //TChain* WZ4 = new TChain("t");

  WZ1->Add(Form("output/%s/ewkino_NoMPI_WZ_100_500_large_baby.root" ,sigversion));
  WZ2->Add(Form("output/%s/ewkino_NoMPI_WZ_100_1000_large_baby.root",sigversion));
  //WZ3->Add(Form("output/%s/ewkino_NoMPI_WZ_100_2000_large_baby.root",sigversion));
  //WZ4->Add(Form("output/%s/ewkino_NoMPI_WZ_100_3000_large_baby.root",sigversion));

  vector<TChain*> samples;
  vector<string>  names;

  samples.push_back(chvv); names.push_back("diboson");
  samples.push_back(WZ1);  names.push_back("WZ_500GeV_sig");
  samples.push_back(WZ2);  names.push_back("WZ_1TeV_sig");
  //samples.push_back(WZ3);  names.push_back("WZ_2TeV_sig");
  //samples.push_back(WZ4);  names.push_back("WZ_3TeV_sig");
  
  //---------------------------------
  // signal samples
  //---------------------------------

  TCut nlep1("nleps==1");
  TCut nlep3("nleps==3");
  TCut mz("dilmass>81.0 && dilmass<101.0");
  TCut ptlep30("lep1pt>30");
  TCut ptlep50("lep1pt>50");
  TCut ptlep100("lep1pt>100");
  TCut nb2("nb==2");
  TCut nj2("njets==2");
  TCut mbb("mbb>100.0 && mbb<150.0");
  TCut mt200("mt > 200.0");
  TCut mt300("mt > 300.0");
  TCut mt500("mt > 500.0");
  TCut met300("met > 300.0");
  TCut met500("met > 500.0");
  TCut met700("met > 700.0");
  TCut st1000("st > 1000.0");
  TCut jet1pt100("jet1pt > 100.0");
  TCut jet2pt50 ("jet2pt >  50.0");
  TCut jet3pt50 ("jet3pt <  50.0");
  TCut weight("1000 * weight * stweight");
  // TCut drlj1("sqrt( pow(lep1eta-jet1eta,2) + pow(acos(cos(lep1phi-jet1phi)) ,2) ) > 0.4");
  // TCut drlj2("sqrt( pow(lep1eta-jet2eta,2) + pow(acos(cos(lep1phi-jet2phi)) ,2) ) > 0.4");
  // TCut drlj3("sqrt( pow(lep1eta-jet3eta,2) + pow(acos(cos(lep1phi-jet3phi)) ,2) ) > 0.4");
  // TCut drlj4("sqrt( pow(lep1eta-jet4eta,2) + pow(acos(cos(lep1phi-jet4phi)) ,2) ) > 0.4");

  TCut sel;

  //---------------------
  // 3-lepton selection
  //---------------------

  // sel += nlep3;
  // sel += TCut("lep1pt > 100.0");
  // sel += TCut("lep2pt >  50.0");
  // sel += TCut("lep3pt >  50.0");
  // sel += TCut("dilmass>81 && dilmass<101.0");
  // sel += mt300;

  makePlot( samples , names , (char*)"dilmass"  , nlep3    , weight , 100 , 0 , 200 );
  makePlot( samples , names , (char*)"lep1pt"   , nlep3+mz , weight , 100 , 0 , 200 );

  // makePlot( samples , names , (char*)"mt"  , sel , weight , 50 , 0 , 1000 );
  // makePlot( samples , names , (char*)"met" , TCut(sel+mt200) , weight , 50 , 0 , 1000 );
  // makePlot( samples , names , (char*)"st"  , sel , weight , 50 , 0 , 5000 );
  // makePlot( samples , names , (char*)"njets"  , sel , weight , 10 , 0 , 10 );
  // makePlot( samples , names , (char*)"mbb" , TCut(nlep1+nb2+mt300+met500+st1000+jet1pt100+jet2pt50+jet3pt50) , weight , 16 , 0 , 400 );
  // makePlot( samples , names , (char*)"mbb" , sel , weight , 16 , 0 , 400 );

  // makePlot( samples , names , (char*)"met" , sel , weight , 20 , 0 , 600 );









}
