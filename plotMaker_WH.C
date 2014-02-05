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


void makePlot( vector<TChain*> samples , vector<string> names , char* var , char* xtitle , TCut sel , TCut weight , int nbin , float xmin , float xmax , bool printplot = false , bool logplot = true , bool stacksig = false) {
  
  const unsigned int n = samples.size();

  TH1F* h[n];

  TCanvas* can = new TCanvas(Form("%s_can",var),Form("%s_can",var),800,600);
  can->cd();

  int colors[]     = {kBlue-10,kGreen+2,kRed+3};
  int linecolors[] = {1,2,4};

  THStack* t = new THStack(Form("%s_stack",var),Form("%s_stack",var));
  TH1F* bkgtot = new TH1F();

  int   nbkg = 0;
  float ymax = 0;

  //TLegend* leg = new TLegend(0.5,0.75,0.85,0.9);
  TLegend* leg = new TLegend(0.5,0.45,0.85,0.6);

  leg->SetFillColor(0);
  leg->SetBorderSize(0);

  //TCut nj2("njets==2");
  //TCut nj2("");

  char* legentry = "";

  for( unsigned int i = 0 ; i < n ; i++ ){
    if( TString(names.at(i)).Contains("sig")  ) continue;
    h[i] = new TH1F(Form("hist_%s_%s",names.at(i).c_str(),var),"",nbin,xmin,xmax);
    //h[i]->Sumw2();
    //samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%s",var,xmax-0.0001,names.at(i).c_str(),var),(sel+nj2)*weight);
    samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%s",var,xmax-0.0001,names.at(i).c_str(),var),(sel)*weight);
    h[i]->SetFillColor(colors[i]);
    cout << "Intregal " << names.at(i) << " " << h[i]->Integral() << endl;
    //cout << "Bin3     " << names.at(i) << " " << h[i]->GetBinContent(3) << " +/- " << h[i]->GetBinError(3) << endl;
    t->Add(h[i]);
    nbkg++;
    ymax += h[i]->GetMaximum();
    if( TString(names.at(i)).Contains("ttbar") ) legentry = "t#bar{t}";
    if( TString(names.at(i)).Contains("Vjets") ) legentry = "V+jets";

    leg->AddEntry(h[i],legentry,"f");
    if( i==0 ) bkgtot = (TH1F*) h[i]->Clone("bkgtot");
    else bkgtot->Add(h[i]);
  }

  for( unsigned int i = 0 ; i < n ; i++ ){
    if( !TString(names.at(i)).Contains("sig") ) continue;
    h[i] = new TH1F(Form("hist_%s_%s",names.at(i).c_str(),var),"",nbin,xmin,xmax);
    //h[i]->Sumw2();
    samples.at(i)->Draw(Form("min(%s,%f)>>hist_%s_%s",var,xmax-0.0001,names.at(i).c_str(),var),sel*weight);
    cout << "Intregal " << names.at(i) << " " << h[i]->Integral() << endl;
    //cout << "Bin3     " << names.at(i) << " " << h[i]->GetBinContent(3) << " +/- " << h[i]->GetBinError(3) << endl;
    if( TString(names.at(i)).Contains("WH500GeV_sig") ) legentry = "WH signal (500,100)";
    if( TString(names.at(i)).Contains("WH1TeV_sig") )   legentry = "WH signal (1000,100)";
    if( TString(names.at(i)).Contains("WH2TeV_sig") )   legentry = "WH signal (2000,100)";
    if( TString(names.at(i)).Contains("WH3TeV_sig") )   legentry = "WH signal (3000,100)";
    leg->AddEntry(h[i],legentry,"l");
    if( stacksig ) h[i]->Add(bkgtot);
  }

  if( logplot ) ymax*=10;
  else          ymax*=1.1;

  TH2F* hdummy = new TH2F("hdummy","",nbin,xmin,xmax,100,1,ymax);
  if( logplot ) gPad->SetLogy();
  hdummy->GetXaxis()->SetTitle(xtitle);
  hdummy->Draw();

  t->Draw("same");
  for( unsigned int isig = nbkg ; isig < n ; isig++ ){
    //h[isig]->Scale(10);
    h[isig]->SetLineColor(linecolors[isig-nbkg]);
    h[isig]->SetLineWidth(2);
    h[isig]->Draw("samehist");
  }

  //leg->Draw();
  hdummy->Draw("axissame");

  if( printplot ) can->Print(Form("plots/%s.pdf",var));
}

void plotMaker_WH(){

  char* version = (char*) "V00-00-00";
  //char* version = (char*) "V00-00-02";

  char* filter = "_nlep1pt30_nb2";
  //char* filter = "";

  //---------------------------------
  // load ttbar samples
  //---------------------------------

  TChain* chtt = new TChain("t");
  chtt->Add(Form("output/%s/tt-4p-0-1000_100TEV_NoPileUp_baby%s.root",version,filter));
  chtt->Add(Form("output/%s/tt-4p-1000-2000_100TEV_NoPileUp_baby%s.root",version,filter));
  chtt->Add(Form("output/%s/tt-4p-2000-3500_100TEV_NoPileUp_baby%s.root",version,filter));
  chtt->Add(Form("output/%s/tt-4p-3500-5500_100TEV_NoPileUp_baby%s.root",version,filter));
  chtt->Add(Form("output/%s/tt-4p-5500-8500_100TEV_NoPileUp_baby%s.root",version,filter));
  chtt->Add(Form("output/%s/tt-4p-8500-100000_100TEV_NoPileUp_baby%s.root",version,filter));
  cout << "tt entries " << chtt->GetEntries() << endl;

  //---------------------------------
  // load W samples
  //---------------------------------

  TChain* chw = new TChain("t");
  chw->Add(Form("output/%s/Bj-4p-0-500_100TEV_NoPileUp_baby%s.root",version,filter));
  chw->Add(Form("output/%s/Bj-4p-500-1500_100TEV_NoPileUp_baby%s.root",version,filter));
  chw->Add(Form("output/%s/Bj-4p-1500-3000_100TEV_NoPileUp_baby%s.root",version,filter));
  chw->Add(Form("output/%s/Bj-4p-3000-5500_100TEV_NoPileUp_baby%s.root",version,filter));
  chw->Add(Form("output/%s/Bj-4p-5500-9000_100TEV_NoPileUp_baby%s.root",version,filter));
  chw->Add(Form("output/%s/Bj-4p-9000-100000_100TEV_NoPileUp_baby%s.root",version,filter));
  cout << "W entries " << chw->GetEntries() << endl;


  //---------------------------------
  // load W samples
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

  TChain* WH1 = new TChain("t");
  TChain* WH2 = new TChain("t");
  TChain* WH3 = new TChain("t");

  // WH1->Add(Form("output/%s/ewkino_WH_500_1000_extra_baby.root",version));
  // WH2->Add(Form("output/%s/ewkino_WH_500_2000_extra_baby.root",version));
  // WH3->Add(Form("output/%s/ewkino_WH_500_3000_extra_baby.root",version));

  // WH1->Add("output/V00-00-02/ewkino_NoMPI_WH_100_500_baby.root");
  // WH2->Add("output/V00-00-02/ewkino_NoMPI_WH_100_1000_baby.root");
  // WH3->Add("output/V00-00-02/ewkino_NoMPI_WH_100_2000_baby.root");

  WH1->Add("output/V00-00-03/ewkino_NoMPI_WH_100_500_large_baby.root");
  WH2->Add("output/V00-00-03/ewkino_NoMPI_WH_100_1000_large_baby.root");
  WH3->Add("output/V00-00-03/ewkino_NoMPI_WH_100_2000_large_baby.root");

  vector<TChain*> samples;
  vector<string>  names;

  samples.push_back(chtt); names.push_back("ttbar");
  samples.push_back(chw);  names.push_back("Vjets");
  samples.push_back(WH1);  names.push_back("WH500GeV_sig");
  samples.push_back(WH2);  names.push_back("WH1TeV_sig");
  samples.push_back(WH3);  names.push_back("WH2TeV_sig");
  
  //---------------------------------
  // signal samples
  //---------------------------------

  TCut nlep1("nleps==1");
  TCut nlep3("nleps==3");
  TCut ptlep30("lep1pt>30");
  TCut ptlep50("lep1pt>50");
  TCut ptlep100("lep1pt>100");
  TCut nb2("nb==2");
  TCut nj2("njets==2");
  TCut nj23("njets==2 || njets==3");
  TCut mt200("mt > 200.0");
  TCut mt300("mt > 300.0");
  TCut mt500("mt > 500.0");
  TCut mt600("mt > 600.0");
  TCut met300("met > 300.0");
  TCut met500("met > 500.0");
  TCut met600("met > 600.0");
  TCut met700("met > 700.0");
  TCut st1000("st > 1000.0");
  TCut mbb("mbb > 100.0 && mbb < 150.0");
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
  // 1-lepton selection
  //---------------------

  sel += nj23;
  sel += nlep1;
  sel += ptlep100;
  sel += nb2;
  sel += mt300;
  // sel += mt500;
  sel += met500;
  //sel += met700;
  sel += st1000;
  // sel += drlj1;
  // sel += drlj2;
  // sel += drlj3;
  // sel += drlj4;

  //sel += mbb;  
  //sel += nj2;


  //---------------------
  // 3-lepton selection
  //---------------------
  /*
  sel += nlep3;
  sel += TCut("lep1pt > 100.0");
  sel += TCut("lep2pt >  50.0");
  sel += TCut("lep3pt >  50.0");
  sel += TCut("dilmass>81 && dilmass<101.0");
  sel += mt300;
  */
  // makePlot( samples , names , (char*)"mt"  , sel , weight , 50 , 0 , 1000 );
  // makePlot( samples , names , (char*)"met" , TCut(sel+mt200) , weight , 50 , 0 , 1000 );
  // makePlot( samples , names , (char*)"st"  , sel , weight , 50 , 0 , 5000 );
  // makePlot( samples , names , (char*)"njets"  , sel , weight , 10 , 0 , 10 );
  // makePlot( samples , names , (char*)"mbb" , TCut(nlep1+nb2+mt300+met500+st1000+jet1pt100+jet2pt50+jet3pt50) , weight , 16 , 0 , 400 );
  //

  //makePlot( samples , names , (char*)"met" , sel , weight , 20 , 0 , 600 );

  TCut presel = nlep1 + ptlep30 + nb2 + mbb;
  //TCut presel = nlep1 + ptlep30 + nb2;

  // makePlot( samples , names , (char*)"st"     , (char*) "S_{T} [GeV]" , presel              , weight , 60 , 0 , 3000 , true );
  // makePlot( samples , names , (char*)"njets"  , (char*) "N_{jets}"    , TCut(presel+st1000) , weight , 10 , 0 , 10 , true );
  // makePlot( samples , names , (char*)"lep1pt"  , (char*) "lepton p_{T} [GeV]"    , TCut(presel+st1000+nj23) , weight , 10 , 0 , 500 , true );
  // makePlot( samples , names , (char*)"mt"  , (char*) "M_{T} [GeV]"    , TCut(presel+st1000+nj23+ptlep100) , weight , 10 , 0 , 1000 , true );
  // makePlot( samples , names , (char*)"met"  , (char*) "E_{T}^{miss} [GeV]"    , TCut(presel+st1000+nj23+ptlep100+mt600) , weight , 10 , 0 , 1000 , true );

  makePlot( samples , names , (char*)"mbb"  , (char*) "M_{bb} [GeV]"    , TCut(mbb+nlep1+ptlep30+nb2+st1000+nj23+ptlep100+mt600+met600) , weight , 10 , 0 , 500 , true , false );

  //makePlot( samples , names , (char*)"mbb"  , (char*) "M_{bb} [GeV]"    , TCut(nlep1+ptlep30+nb2+st1000+nj23+ptlep100+mt600+met700) , weight , 10 , 0 , 500 , true , false );


  //makePlot( samples , names , (char*)"mbb" , sel , weight , 16 , 0 , 400 );








}
