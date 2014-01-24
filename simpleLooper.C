#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <fstream>

#include "TROOT.h"
#include "TSystem.h"
#include "TApplication.h"

#include "TString.h"

#include "TH2.h"
#include "THStack.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"

#include "classes/DelphesClasses.h"

#include "ExRootAnalysis/ExRootTreeReader.h"
#include "ExRootAnalysis/ExRootTreeWriter.h"
#include "ExRootAnalysis/ExRootTreeBranch.h"
#include "ExRootAnalysis/ExRootResult.h"
#include "ExRootAnalysis/ExRootUtilities.h"





using namespace std;

void doLoop(const char *inputFile);

//--------------------------------------
// Function to run over various samples
//--------------------------------------

void simpleLooper(){
 
  gSystem->Load("libDelphes");

  TChain chtt("Delphes");

  bool runtt = true;
  bool runWZ = true;
  bool runW  = true;

  char* PU = "NoPileUp";
  //char* PU = "40PileUp";
  //char* PU = "140PileUp";

  if( runWZ ){
    doLoop( Form("BB-4p-0-500_100TEV_%s"       , PU ));
    doLoop( Form("BB-4p-500-1500_100TEV_%s"    , PU ));
    doLoop( Form("BB-4p-1500-3000_100TEV_%s"   , PU ));
    doLoop( Form("BB-4p-3000-5500_100TEV_%s"   , PU ));
    doLoop( Form("BB-4p-5500-9000_100TEV_%s"   , PU ));
    doLoop( Form("BB-4p-9000-100000_100TEV_%s" , PU ));
  }

  if (runtt){
    // doLoop( "tt0"    );
    // doLoop( "tt1000" );
    // doLoop( "tt2000" );
    // doLoop( "tt3500" );
    // doLoop( "tt5500" );
    // doLoop( "tt8500" );

    doLoop( Form("tt-4p-0-1000_100TEV_%s"      , PU ));
    doLoop( Form("tt-4p-1000-2000_100TEV_%s"   , PU ));
    doLoop( Form("tt-4p-2000-3500_100TEV_%s"   , PU ));
    doLoop( Form("tt-4p-3500-5500_100TEV_%s"   , PU ));
    doLoop( Form("tt-4p-5500-8500_100TEV_%s"   , PU ));
    doLoop( Form("tt-4p-8500-100000_100TEV_%s" , PU ));
  }

  if( runW ){
    doLoop( Form("Bj-4p-0-500_100TEV_%s"       , PU ));
    doLoop( Form("Bj-4p-500-1500_100TEV_%s"    , PU ));
    doLoop( Form("Bj-4p-1500-3000_100TEV_%s"   , PU ));
    doLoop( Form("Bj-4p-3000-5500_100TEV_%s"   , PU ));
    doLoop( Form("Bj-4p-5500-9000_100TEV_%s"   , PU ));
    doLoop( Form("Bj-4p-9000-100000_100TEV_%s" , PU ));
  }

}

//-------------------------------------------
// Function to add files to chain
//-------------------------------------------

TChain* addFiles( const char* sample ){

  cout << "Opening file list for sample " << sample << endl;

  ifstream ifile( Form("fileLists/%s.txt",sample) );
  
  string filepath;

  if( ifile.is_open() ){
    ifile >> filepath;
    cout << "File path " << filepath << endl;
  }
  else{
    cout << "COULD NOT FIND LIST FOR " << sample << endl;
    exit(0);
  }

  TFile * f     = TFile::Open(Form("root://red-gridftp11.unl.edu/%s",filepath.c_str()));
  TTree*  tree  = (TTree*) f->Get("Delphes");
  TChain* chain = (TChain*) tree; 

  return chain;

}

float getCrossSection( const char* sample ){

  float xsec = -1;
  
  // dibosons
  if( TString(sample).Contains("BB-4p-0-500_100TEV"        ) )  xsec = 2867.87;
  if( TString(sample).Contains("BB-4p-500-1500_100TEV"     ) )  xsec = 405.2;
  if( TString(sample).Contains("BB-4p-1500-3000_100TEV"    ) )  xsec = 22.8439;
  if( TString(sample).Contains("BB-4p-3000-5500_100TEV"    ) )  xsec = 2.221;
  if( TString(sample).Contains("BB-4p-5500-9000_100TEV"    ) )  xsec = 0.20005;
  if( TString(sample).Contains("BB-4p-9000-100000_100TEV"  ) )  xsec = 0.02441;

  // ttbar
  if( TString(sample).Contains("tt-4p-0-1000_100TEV"       ) )  xsec = 29141.3;
  if( TString(sample).Contains("tt-4p-1000-2000_100TEV"    ) )  xsec =  1777.3;
  if( TString(sample).Contains("tt-4p-2000-3500_100TEV"    ) )  xsec =  185.22;
  if( TString(sample).Contains("tt-4p-3500-5500_100TEV"    ) )  xsec =  18.919;
  if( TString(sample).Contains("tt-4p-5500-8500_100TEV"    ) )  xsec = 2.38751;
  if( TString(sample).Contains("tt-4p-8500-100000_100TEV"  ) )  xsec = 0.27715;

  // W+jets
  if( TString(sample).Contains("Bj-4p-0-500_100TEV"        ) ) xsec =   485362;
  if( TString(sample).Contains("Bj-4p-500-1500_100TEV"     ) ) xsec =  20395.9;
  if( TString(sample).Contains("Bj-4p-1500-3000_100TEV"    ) ) xsec =    635.9;
  if( TString(sample).Contains("Bj-4p-3000-5500_100TEV"    ) ) xsec =  47.6179;
  if( TString(sample).Contains("Bj-4p-5500-9000_100TEV"    ) ) xsec =  3.48470;
  if( TString(sample).Contains("Bj-4p-9000-100000_100TEV"  ) ) xsec =  0.35638;

  cout << "Sample cross section " << xsec << endl;

  if( xsec < 0 ){
    cout << "ERROR! couldn't find cross section for sample " << sample << endl;
    exit(0);
  }

  return xsec;

}

//-------------------------------------------
// Function to loop over events in sample
//-------------------------------------------

void doLoop(const char *prefix){

  cout << "Running on sample: " << prefix << endl;

  TFile *fbaby = TFile::Open(  Form("output/%s_baby.root",prefix) ,"RECREATE" );
  fbaby->cd();

  TTree* tree = new TTree("t","Tree");

  //--------------------------------------------------------------
  // define variables for output ntuple
  //--------------------------------------------------------------

  Int_t   njets_    = 0;
  Int_t   nels_     = 0;
  Int_t   nmus_     = 0;
  Int_t   nleps_    = 0;
  Int_t   ngenels_  = 0;
  Int_t   ngenmus_  = 0;
  Int_t   ngentaus_ = 0;
  Int_t   ngenleps_ = 0;
  Float_t met_      = 0.0;
  Float_t ht_       = 0.0;
  Float_t jetpt_    = 0.0;
  Float_t st_       = 0.0;
  Float_t stlep_    = 0.0;
  Float_t stweight_ = 0.0;
  Float_t xsec_     = -1.0;
  Int_t   nevents_  = -1;
  Float_t weight_   = -1.0;
  Int_t   nw_       = 0;
  Int_t   nz_       = 0;

  tree->Branch("st",        &st_,         "st/F");
  tree->Branch("stweight",  &stweight_,   "stweight/F");
  tree->Branch("nw",        &nw_,         "nw/F");
  tree->Branch("nz",        &nz_,         "nz/F");

  //-----------------------------------------------------------------------
  // Create chain of root trees, add appropriate files
  //-----------------------------------------------------------------------

  TChain* chain = addFiles(prefix);

  ExRootTreeReader *treeReader = new ExRootTreeReader(chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  int nEventsTotal = 0;

  xsec_    = getCrossSection( prefix );
  nevents_ = numberOfEntries;
  weight_  = xsec_ / (float) numberOfEntries;

  cout << "xsec nevents weight " << xsec_ << " " << nevents_ << " " << weight_ << endl;
  asdfasdfasdf
  //--------------------------------------------------------------
  // Get pointers to branches used in this analysis
  //--------------------------------------------------------------

  TClonesArray *branchEvent     = treeReader->UseBranch("Event");
  TClonesArray *branchParticle  = treeReader->UseBranch("Particle");
  TClonesArray *branchJet       = treeReader->UseBranch("Jet");
  TClonesArray *branchElectron  = treeReader->UseBranch("Electron");
  TClonesArray *branchMuon      = treeReader->UseBranch("Muon");
  TClonesArray *branchMissingET = treeReader->UseBranch("MissingET");
  TClonesArray *branchScalarHT  = treeReader->UseBranch("ScalarHT");

  //--------------------------------------------------------------
  // Book histograms
  //--------------------------------------------------------------
  
  TH1 *histJetPT  = new TH1F("jet_pt"  , "jet P_{T} [GeV]"              , 100  , 0.0  , 500.0);
  TH1 *histMass   = new TH1F("mass"    , "M_{inv}(e_{1}, e_{2}) [GeV]"  , 100  , 40.0 , 140.0);
  TH1 *histMet    = new TH1F("met"     , "E_{T}^{miss} [GeV]"           , 100  , 0.0  , 2000.0);
  TH1 *histHT     = new TH1F("ht"      , "H_{T} [GeV]"                  , 100  , 0.0  , 20000.0);
  TH1 *histNjets  = new TH1F("njets"   , "N_{jets}"                     , 10   , 0    , 10);
  TH1 *histSt     = new TH1F("st"      , "S_{T} [GeV]"                  , 2000 , 0    , 20000);
  TH1 *histWeight = new TH1F("weight"  , "event weight"                 , 100  , 0    , 100);

  int nWZ = 0;

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry){

    njets_    = 0;
    met_      = 0.0;
    ht_       = 0.0;
    jetpt_    = 0.0;
    st_       = 0.0;
    stlep_    = 0.0;
    stweight_ = 0.0;
    nw_       = 0;
    nz_       = 0;
    ngenels_  = 0;
    ngenmus_  = 0;
    ngentaus_ = 0;
    ngenleps_ = 0;

    nEventsTotal++;

    // Load selected branches with data from specified event
    treeReader->ReadEntry(entry);

    // progress feedback to user
    if (nEventsTotal % 1000 == 0){
      
      // xterm magic from L. Vacavant and A. Cerri
      if (isatty(1)){
	
	printf("\015\033[32m ---> \033[1m\033[31m%4.1f%%"
	       "\033[0m\033[32m <---\033[0m\015", (float)nEventsTotal/(numberOfEntries*0.01));
	fflush(stdout);
      }
    }

    //----------------------------------------
    // event weight
    //----------------------------------------

    LHEFEvent* myevent = (LHEFEvent*) branchEvent->At(0);
    stweight_ = myevent->Weight;
    histWeight->Fill(stweight_);

    //----------------------------------------
    // get leading jet pt and njets
    //----------------------------------------

    if(branchJet->GetEntries() > 0){
      Jet *jet = (Jet*) branchJet->At(0);
      jetpt_ = jet->PT;
      histJetPT->Fill(jetpt_,weight_*stweight_);
    }

    //----------------------------------------
    // number of pt > 30 GeV jets
    //----------------------------------------

    for( int i = 0 ; i < branchJet->GetEntries() ; i++ ){
      Jet* jet = (Jet*) branchJet->At(i);
      cout << i << " " << jet->PT << endl;
      if( jet->PT > 30 ) njets_++;
    }

    //njets_ = branchJet->GetEntries();
    histNjets->Fill(njets_,weight_*stweight_);
    
    //----------------------------------------
    // missing et
    //----------------------------------------

    MissingET* met = (MissingET*) branchMissingET->At(0);
    met_ = met->MET;
    histMet->Fill(met_,weight_*stweight_);

    //----------------------------------------
    // HT
    //----------------------------------------

    ScalarHT* ht = (ScalarHT*) branchScalarHT->At(0);
    ht_ = ht->HT;
    histHT->Fill(ht_,weight_*stweight_);

    //----------------------------------------
    // loop over leptons to get STlep
    //----------------------------------------

    for( int i = 0 ; i < branchElectron->GetEntries() ; i++ ){
      Electron* el = (Electron*) branchElectron->At(i);
      stlep_ += el->PT;
      //cout << "Electron " << i << el->PT << endl;
    }

    for( int i = 0 ; i < branchMuon->GetEntries() ; i++ ){
      Muon* mu = (Muon*) branchMuon->At(i);
      stlep_ += mu->PT;
      //cout << "Muon " << i << mu->PT << endl;
    }

    st_ = met_ + ht_ + stlep_;

    histSt->Fill(st_,weight_*stweight_);

    //----------------------------------------
    // Count various types of particles
    //----------------------------------------

    for( int i = 0 ; i < branchParticle->GetEntries() ; i++ ){
      GenParticle* p = (GenParticle*) branchParticle->At(i);
      if( abs( p->PID ) == 24 ) nw_++;
      if( abs( p->PID ) == 23 ) nz_++;
      if( abs( p->PID ) == 11 ) ngenels_++;
      if( abs( p->PID ) == 13 ) ngenmus_++;
      if( abs( p->PID ) == 15 ) ngentaus_++;
    }



    /*
    nels_  = branchElectron->GetEntries();
    nmus_  = branchMuon->GetEntries();
    nleps_ = nels_ + nmus_;

    cout << endl << endl;
    cout << "nels nmus nleps " << nels_ << " " << nmus_ << " " << nleps_ << endl;

    //if( nleps_ == 3 ){

    cout << "Electrons " << endl;
    for( int iel = 0 ; iel < nels_ ; iel++ ){
      Electron* el = (Electron *) branchElectron->At(iel);
      cout << iel << " " << el->PT << endl;
    }

    cout << "Muons " << endl;
    for( int imu = 0 ; imu < nmus_ ; imu++ ){
      Muon* mu = (Muon *) branchMuon->At(imu);
      cout << imu << " " << mu->PT << endl;
    }
    */

    //}


    // Electron *elec1, *elec2;

    // // If event contains at least 2 electrons
    // if(branchElectron->GetEntries() > 1){
    //   // Take first two electrons
    //   elec1 = (Electron *) branchElectron->At(0);
    //   elec2 = (Electron *) branchElectron->At(1);
      
    //   // Plot their invariant mass
    //   histMass->Fill(((elec1->P4()) + (elec2->P4())).M());
    // }
    
    tree->Fill();
  }

  cout << "Found " << nWZ << " WZ events" << endl;

  fbaby->cd();
  tree->Write();
  fbaby->Close();

  TFile *fout = TFile::Open(  Form("output/%s.root",prefix) ,"RECREATE" );
  fout->cd();

  histMet->Write();
  histHT->Write();
  histJetPT->Write();
  histNjets->Write();
  histSt->Write();
  histStStar->Write();

  fout->Close();




}
