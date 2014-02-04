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

#include "simpleLooper.h"


char* version = (char*) "V00-00-01";
//char* version = (char*) "temp";

using namespace std;

//void doLoop(const char *inputFile, int nfiles=1);
void doLoop(const string inputFile, int nfiles=1, bool isSignal=false);

//--------------------------------------
// Function to run over various samples
//--------------------------------------

void simpleLooper(){
 
  gSystem->Load("libDelphes");

  bool runtt    = false;
  bool runWZ    = false;
  bool runW     = false;
  bool runWHsig = false;
  bool runWZsig = true;

  char* PU = (char*) "NoPileUp";
  //char* PU = (char*) "40PileUp";
  //char* PU = (char*) "140PileUp";

  int nfiles = 1;

  if (runtt){
    doLoop( Form("tt-4p-0-1000_100TEV_%s"      , PU ) , nfiles );
    doLoop( Form("tt-4p-1000-2000_100TEV_%s"   , PU ) , nfiles );
    doLoop( Form("tt-4p-2000-3500_100TEV_%s"   , PU ) , nfiles );
    doLoop( Form("tt-4p-3500-5500_100TEV_%s"   , PU ) , nfiles );
    doLoop( Form("tt-4p-5500-8500_100TEV_%s"   , PU ) , nfiles );
    doLoop( Form("tt-4p-8500-100000_100TEV_%s" , PU ) , nfiles );
  }

  if( runWZ ){
    doLoop( Form("BB-4p-0-500_100TEV_%s"       , PU ) , nfiles );
    doLoop( Form("BB-4p-500-1500_100TEV_%s"    , PU ) , nfiles );
    doLoop( Form("BB-4p-1500-3000_100TEV_%s"   , PU ) , nfiles );
    doLoop( Form("BB-4p-3000-5500_100TEV_%s"   , PU ) , nfiles );
    doLoop( Form("BB-4p-5500-9000_100TEV_%s"   , PU ) , nfiles );
    doLoop( Form("BB-4p-9000-100000_100TEV_%s" , PU ) , nfiles );
  }

  if( runW ){
    doLoop( Form("Bj-4p-0-500_100TEV_%s"       , PU ) , nfiles );
    doLoop( Form("Bj-4p-500-1500_100TEV_%s"    , PU ) , nfiles );
    doLoop( Form("Bj-4p-1500-3000_100TEV_%s"   , PU ) , nfiles );
    doLoop( Form("Bj-4p-3000-5500_100TEV_%s"   , PU ) , nfiles );
    doLoop( Form("Bj-4p-5500-9000_100TEV_%s"   , PU ) , nfiles );
    doLoop( Form("Bj-4p-9000-100000_100TEV_%s" , PU ) , nfiles );
  }

  if( runWHsig ){
    doLoop( "ewkino_WH_500_1000_extra" , 1 , true );
    doLoop( "ewkino_WH_500_2000_extra" , 1 , true );
    doLoop( "ewkino_WH_500_3000_extra" , 1 , true );
  }

  if( runWZsig ){
    doLoop( "ewkino_WZ_500_1000_extra" , 1 , true );
    doLoop( "ewkino_WZ_500_2000_extra" , 1 , true );
    doLoop( "ewkino_WZ_500_3000_extra" , 1 , true );
  }

}

//--------------------------------------
// Function to run over various samples
//--------------------------------------

void simpleLooper(char* sample, char* PU, int stbin , int nfiles = 1 ){
 
  gSystem->Load("libDelphes");

  if ( TString(sample).Contains("ttbar") ){
    if     ( stbin == 1 ) doLoop( Form("tt-4p-0-1000_100TEV_%s"      , PU ) , nfiles );
    else if( stbin == 2 ) doLoop( Form("tt-4p-1000-2000_100TEV_%s"   , PU ) , nfiles );
    else if( stbin == 3 ) doLoop( Form("tt-4p-2000-3500_100TEV_%s"   , PU ) , nfiles );
    else if( stbin == 4 ) doLoop( Form("tt-4p-3500-5500_100TEV_%s"   , PU ) , nfiles );
    else if( stbin == 5 ) doLoop( Form("tt-4p-5500-8500_100TEV_%s"   , PU ) , nfiles );
    else if( stbin == 6 ) doLoop( Form("tt-4p-8500-100000_100TEV_%s" , PU ) , nfiles );
    else{
      cout << "Error, unrecognized bin " << stbin << endl;
    }
  }

  else if ( TString(sample).Contains("diboson") ){

    if     ( stbin == 1 ) doLoop( Form("BB-4p-0-500_100TEV_%s"       , PU ) , nfiles );
    else if( stbin == 2 ) doLoop( Form("BB-4p-500-1500_100TEV_%s"    , PU ) , nfiles );
    else if( stbin == 3 ) doLoop( Form("BB-4p-1500-3000_100TEV_%s"   , PU ) , nfiles );
    else if( stbin == 4 ) doLoop( Form("BB-4p-3000-5500_100TEV_%s"   , PU ) , nfiles );
    else if( stbin == 5 ) doLoop( Form("BB-4p-5500-9000_100TEV_%s"   , PU ) , nfiles );
    else if( stbin == 6 ) doLoop( Form("BB-4p-9000-100000_100TEV_%s" , PU ) , nfiles );
    else{
      cout << "Error, unrecognized bin " << stbin << endl;
    }

  }

  else if ( TString(sample).Contains("boson") ){
    if     ( stbin == 1 ) doLoop( Form("Bj-4p-0-500_100TEV_%s"       , PU ) , nfiles );
    else if( stbin == 2 ) doLoop( Form("Bj-4p-500-1500_100TEV_%s"    , PU ) , nfiles );
    else if( stbin == 3 ) doLoop( Form("Bj-4p-1500-3000_100TEV_%s"   , PU ) , nfiles );
    else if( stbin == 4 ) doLoop( Form("Bj-4p-3000-5500_100TEV_%s"   , PU ) , nfiles );
    else if( stbin == 5 ) doLoop( Form("Bj-4p-5500-9000_100TEV_%s"   , PU ) , nfiles );
    else if( stbin == 6 ) doLoop( Form("Bj-4p-9000-100000_100TEV_%s" , PU ) , nfiles );
    else{
      cout << "Error, unrecognized bin " << stbin << endl;
    }

  }

}

//-------------------------------------------
// Function to add files to chain
//-------------------------------------------

TChain* addFile( const char* sample ){

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


vector<TChain*> addFiles( const char* sample , int nfiles = 1){

  cout << "Opening file list for sample " << sample << endl;

  ifstream ifile( Form("fileLists/%s.txt",sample) );
  
  string filepath;

  vector<TChain*> myChains;
  int n = 0;

  if( !ifile.is_open() ){
    cout << "Couldn't find file for sample " << sample << endl;
    exit(0);
  }

  TFile*  f     = new TFile();
  TTree*  tree  = new TTree();
  TChain* chain = new TChain();

  while( n < nfiles){
    ifile >> filepath;

    char* fullfilepath = Form("root://red-gridftp11.unl.edu/%s",filepath.c_str());

    cout << "File path " << fullfilepath << endl;

    // TFile*  f     = TFile::Open(fullfilepath);
    // TTree*  tree  = (TTree*) f->Get("Delphes");
    // TChain* chain = (TChain*) tree; 

    f     = TFile::Open(fullfilepath);
    tree  = (TTree*) f->Get("Delphes");
    chain = (TChain*) tree; 

    myChains.push_back(chain);
    n++;
  }

  // delete f;
  // delete tree;
  // delete chain;

  return myChains;
}

//vector<char*> fileNames( const char* sample , int nfiles = 1){
vector<string> fileNames( const string sample , int nfiles = 1){

  cout << "Opening file list for sample " << sample << endl;

  ifstream ifile( Form("fileLists/%s.txt",sample.c_str()) );
  
  string filepath;

  vector<string> names;

  int n = 0;

  if( !ifile.is_open() ){
    cout << "Couldn't find file for sample " << sample << endl;
    exit(0);
  }

  char* fullfilepath = (char*) "";
  string previousfilepath = "";

  // if nfiles > 0, run over nfiles in list
  if( nfiles > 0 ){
    while( n < nfiles){
      ifile >> filepath;
      
      fullfilepath = Form("root://red-gridftp11.unl.edu/%s",filepath.c_str());
      cout << fullfilepath << endl;
      names.push_back(fullfilepath);
      n++;
    }
  }

  // if nfiles = -1, run over all files in list
  else{
    while( !ifile.eof() ){

      previousfilepath = filepath;

      ifile >> filepath;

      // check for duplicate at end of file
      if( strcmp(previousfilepath.c_str(),filepath.c_str()) != 0 ){
      
	fullfilepath = Form("root://red-gridftp11.unl.edu/%s",filepath.c_str());
	cout << fullfilepath << endl;      
	names.push_back(fullfilepath);
      }

    }
  }

  return names;
}


//-------------------------------------------------------------------------------------
// cross sections from:
// http://www.snowmass2013.org/tiki-index.php?page=Energy_Frontier_FastSimulation
//-------------------------------------------------------------------------------------

//float getCrossSection( const char* sample ){
float getCrossSection( const string sample ){

  float xsec = -1;
  
  // dibosons
  if( TString(sample).Contains("BB-4p-0-500_100TEV"        ) )  xsec = 2867.87;
  else if( TString(sample).Contains("BB-4p-500-1500_100TEV"     ) )  xsec = 405.2;
  else if( TString(sample).Contains("BB-4p-1500-3000_100TEV"    ) )  xsec = 22.8439;
  else if( TString(sample).Contains("BB-4p-3000-5500_100TEV"    ) )  xsec = 2.221;
  else if( TString(sample).Contains("BB-4p-5500-9000_100TEV"    ) )  xsec = 0.20005;
  else if( TString(sample).Contains("BB-4p-9000-100000_100TEV"  ) )  xsec = 0.02441;

  // ttbar
  else if( TString(sample).Contains("tt-4p-0-1000_100TEV"       ) )  xsec = 29141.3;
  else if( TString(sample).Contains("tt-4p-1000-2000_100TEV"    ) )  xsec =  1777.3;
  else if( TString(sample).Contains("tt-4p-2000-3500_100TEV"    ) )  xsec =  185.22;
  else if( TString(sample).Contains("tt-4p-3500-5500_100TEV"    ) )  xsec =  18.919;
  else if( TString(sample).Contains("tt-4p-5500-8500_100TEV"    ) )  xsec = 2.38751;
  else if( TString(sample).Contains("tt-4p-8500-100000_100TEV"  ) )  xsec = 0.27715;

  // W+jets
  else if( TString(sample).Contains("Bj-4p-0-500_100TEV"        ) ) xsec =   485362;
  else if( TString(sample).Contains("Bj-4p-500-1500_100TEV"     ) ) xsec =  20395.9;
  else if( TString(sample).Contains("Bj-4p-1500-3000_100TEV"    ) ) xsec =    635.9;
  else if( TString(sample).Contains("Bj-4p-3000-5500_100TEV"    ) ) xsec =  47.6179;
  else if( TString(sample).Contains("Bj-4p-5500-9000_100TEV"    ) ) xsec =  3.48470;
  else if( TString(sample).Contains("Bj-4p-9000-100000_100TEV"  ) ) xsec =  0.35638;

  // WH
  else if( TString(sample).Contains("ewkino_WH_500_1000"  ) ) xsec =  0.0650 * 1.3 * 0.56;
  else if( TString(sample).Contains("ewkino_WH_500_2000"  ) ) xsec =  0.0051 * 1.3 * 0.56;
  else if( TString(sample).Contains("ewkino_WH_500_3000"  ) ) xsec =  0.0010 * 1.3 * 0.56;

  // WZ
  else if( TString(sample).Contains("ewkino_WZ_500_1000"  ) ) xsec =  0.0650 * 1.3 * 0.07 * 0.22;
  else if( TString(sample).Contains("ewkino_WZ_500_2000"  ) ) xsec =  0.0051 * 1.3 * 0.07 * 0.22;
  else if( TString(sample).Contains("ewkino_WZ_500_3000"  ) ) xsec =  0.0010 * 1.3 * 0.07 * 0.22;

  cout << "Sample cross section " << xsec << endl;

  if( xsec < 0 ){
    cout << "ERROR! couldn't find cross section for sample " << sample << endl;
    exit(0);
  }

  return 1000.0 * xsec;

}

void InitVars(){
  nb_       = 0  ;
  nbgen_    = 0  ;
  njets_    = 0  ;
  njets40_  = 0  ;
  njets50_  = 0  ;
  njets100_ = 0  ;
  ngenjets_ = 0  ;
  nels_     = 0  ;
  nmus_     = 0  ;
  nleps_    = 0  ; 
  ngenels_  = 0  ;
  ngenmus_  = 0  ;
  ngentaus_ = 0  ;
  ngenleps_ = 0  ;
  met_      = 0. ;
  metphi_   = 0. ;
  ht_       = 0. ;
  jet1pt_   = 0. ;
  jet1eta_  = 0. ;
  jet1phi_  = 0. ;
  jet2pt_   = 0. ;
  jet2eta_  = 0. ;
  jet2phi_  = 0. ;
  bjet1pt_  = 0. ;
  bjet1eta_ = 0. ;
  bjet1phi_ = 0. ;
  bjet2pt_  = 0. ;
  bjet2eta_ = 0. ;
  bjet2phi_ = 0. ;
  jet3pt_   = 0. ;
  jet3eta_  = 0. ;
  jet3phi_  = 0. ;
  jet4pt_   = 0. ;
  jet4eta_  = 0. ;
  jet4phi_  = 0. ;
  st_       = 0. ;
  stlep_    = 0. ;
  stweight_ = 0. ;
  // xsec_     = 0. ;
  // nevents_  = 0  ;
  // weight_   = 0. ;
  nw_       = 0  ;
  nh_       = 0  ;
  nz_       = 0  ;
  ntop_     = 0  ;
  mt_       = 0  ;
  mbb_      = 0  ;
  ptbb_     = 0  ;
  drbb_     = 0  ;
  drbbgen_  = 0  ;
  pthgen_   = 0  ;
  lep1pt_   = 0. ;
  lep1eta_  = 0. ;
  lep1phi_  = 0. ;
  lep2pt_   = 0. ;
  lep2eta_  = 0. ;
  lep2phi_  = 0. ;
  lep3pt_   = 0. ;
  lep3eta_  = 0. ;
  lep3phi_  = 0. ;
  leptype_  = -1;
}

//-------------------------------------------
// Function to loop over events in sample
//-------------------------------------------

//void doLoop(const char *prefix, int nfiles ){
void doLoop(const string prefix, int nfiles , bool isSignal){

  //static const char* sample = prefix;

  cout << endl << endl;
  cout << "Running on sample: " << prefix  << endl;
  cout << "Code version     : " << version << endl;

  //--------------------------------------------------------------
  // make an output ntuple
  //--------------------------------------------------------------

  TFile *fbaby = TFile::Open(  Form("output/%s/%s_baby.root",version,prefix.c_str()) ,"RECREATE" );
  fbaby->cd();

  TTree* tree = new TTree("t","Tree");

  //--------------------------------------------------------------
  // define variables for output ntuple
  //--------------------------------------------------------------

  tree->Branch("nb"         ,  &nb_         ,   "nb/I"		);
  tree->Branch("nbgen"      ,  &nbgen_      ,   "nbgen/I"	);
  tree->Branch("njets"      ,  &njets_      ,   "njets/I"	);
  tree->Branch("njets40"    ,  &njets40_    ,   "njets40/I"	);
  tree->Branch("njets50"    ,  &njets50_    ,   "njets50/I"	);
  tree->Branch("njets100"   ,  &njets100_   ,   "njets100/I"	);
  tree->Branch("ngenjets"   ,  &ngenjets_   ,   "ngenjets/I"	);
  tree->Branch("nels"       ,  &nels_       ,   "nels/I"	);
  tree->Branch("nmus"       ,  &nmus_       ,   "nmus/I"	);
  tree->Branch("nleps"      ,  &nleps_      ,   "nleps/I"	);
  tree->Branch("ngenels"    ,  &ngenels_    ,   "ngenels/I"	);
  tree->Branch("ngenmus"    ,  &ngenmus_    ,   "ngenmus/I"	);
  tree->Branch("ngentaus"   ,  &ngentaus_   ,   "ngentaus/I"	);
  tree->Branch("ngenleps"   ,  &ngenleps_   ,   "ngenleps/I"	);
  tree->Branch("met"        ,  &met_        ,   "met/F"		);
  tree->Branch("ht"         ,  &ht_         ,   "ht/F"		);
  tree->Branch("jet1pt"     ,  &jet1pt_     ,   "jet1pt/F"	);
  tree->Branch("jet2pt"     ,  &jet2pt_     ,   "jet2pt/F"	);
  tree->Branch("jet3pt"     ,  &jet3pt_     ,   "jet3pt/F"	);
  tree->Branch("jet4pt"     ,  &jet4pt_     ,   "jet4pt/F"	);
  tree->Branch("jet1eta"    ,  &jet1eta_    ,   "jet1eta/F"	);
  tree->Branch("jet2eta"    ,  &jet2eta_    ,   "jet2eta/F"	);
  tree->Branch("jet3eta"    ,  &jet3eta_    ,   "jet3eta/F"	);
  tree->Branch("jet4eta"    ,  &jet4eta_    ,   "jet4eta/F"	);
  tree->Branch("jet1phi"    ,  &jet1phi_    ,   "jet1phi/F"	);
  tree->Branch("jet2phi"    ,  &jet2phi_    ,   "jet2phi/F"	);
  tree->Branch("jet3phi"    ,  &jet3phi_    ,   "jet3phi/F"	);
  tree->Branch("jet4phi"    ,  &jet4phi_    ,   "jet4phi/F"	);
  tree->Branch("bjet1pt"    ,  &bjet1pt_    ,   "bjet1pt/F"	);
  tree->Branch("bjet2pt"    ,  &bjet2pt_    ,   "bjet2pt/F"	);
  tree->Branch("bjet1eta"   ,  &bjet1eta_   ,   "bjet1eta/F"	);
  tree->Branch("bjet2eta"   ,  &bjet2eta_   ,   "bjet2eta/F"	);
  tree->Branch("bjet1phi"   ,  &bjet1phi_   ,   "bjet1phi/F"	);
  tree->Branch("bjet2phi"   ,  &bjet2phi_   ,   "bjet2phi/F"	);
  tree->Branch("st"         ,  &st_         ,   "st/F"		);
  tree->Branch("stlep"      ,  &stlep_      ,   "stlep/F"	);
  tree->Branch("stweight"   ,  &stweight_   ,   "stweight/F"	);
  tree->Branch("xsec"       ,  &xsec_       ,   "xsec/F"	);
  tree->Branch("nevents"    ,  &nevents_    ,   "nevents/I"	);
  tree->Branch("weight"     ,  &weight_     ,   "weight/F"	);
  tree->Branch("nw"         ,  &nw_         ,   "nw/I"		);
  tree->Branch("nh"         ,  &nh_         ,   "nh/I"		);
  tree->Branch("nz"         ,  &nz_         ,   "nz/I"		);
  tree->Branch("ntop"       ,  &ntop_       ,   "ntop/I"	);
  tree->Branch("mt"         ,  &mt_         ,   "mt/F"		);
  tree->Branch("mbb"        ,  &mbb_        ,   "mbb/F"		);
  tree->Branch("ptbb"       ,  &ptbb_       ,   "ptbb/F"	);
  tree->Branch("drbb"       ,  &drbb_       ,   "drbb/F"	);
  tree->Branch("drbbgen"    ,  &drbbgen_    ,   "drbbgen/F"	);
  tree->Branch("pthgen"     ,  &pthgen_     ,   "pthgen/F"	);
  tree->Branch("lep1pt"     ,  &lep1pt_     ,   "lep1pt/F"	);
  tree->Branch("lep1phi"    ,  &lep1phi_    ,   "lep1phi/F"	);
  tree->Branch("lep1eta"    ,  &lep1eta_    ,   "lep1eta/F"	);
  tree->Branch("lep2pt"     ,  &lep2pt_     ,   "lep2pt/F"	);
  tree->Branch("lep2eta"    ,  &lep2eta_    ,   "lep2eta/F"	);
  tree->Branch("lep3pt"     ,  &lep3pt_     ,   "lep3pt/F"	);
  tree->Branch("lep3eta"    ,  &lep3eta_    ,   "lep3eta/F"	);

  //-----------------------------------------------------------------------
  // Create chain of root trees, add appropriate files
  //-----------------------------------------------------------------------

  xsec_    = getCrossSection( prefix );

  TChain chain("Delphes");

  // load signal samples
  if( isSignal ){
    char* sigfile = Form("signalSamples/%s.root",prefix.c_str());
    cout << "Loading signal sample " << sigfile << endl;
    chain.Add( sigfile );
  }

  // load list of background samples
  else{
    vector<string> filepaths = fileNames( prefix , nfiles );
    
    cout << "Loading " << filepaths.size() << " files" << endl;
    
    for( unsigned int i = 0 ; i < filepaths.size() ; i++ ){
      //cout << "Adding " << filepaths.at(i) << endl;
      chain.Add(filepaths.at(i).c_str());
    }
  }

  nevents_ = chain.GetEntries();

  weight_  = xsec_ / (float) nevents_;
  cout << "xsec nevents weight " << xsec_ << " " << nevents_ << " " << weight_ << endl;

  //--------------------------------------------------------------
  // Book histograms
  //--------------------------------------------------------------
  
  TDirectory *rootdir = gDirectory->GetDirectory("Rint:");
  rootdir->cd();

  TH1 *histJetPT  = new TH1F("jet_pt"  , "jet P_{T} [GeV]"              , 100  , 0.0  , 500.0);
  //TH1 *histMass   = new TH1F("mass"    , "M_{inv}(e_{1}, e_{2}) [GeV]"  , 100  , 40.0 , 140.0);
  TH1 *histMet    = new TH1F("met"     , "E_{T}^{miss} [GeV]"           , 100  , 0.0  , 2000.0);
  TH1 *histHT     = new TH1F("ht"      , "H_{T} [GeV]"                  , 100  , 0.0  , 20000.0);
  TH1 *histNjets  = new TH1F("njets"   , "N_{jets}"                     , 10   , 0    , 10);
  TH1 *histSt     = new TH1F("st"      , "S_{T} [GeV]"                  , 2000 , 0    , 20000);
  TH1 *histStLO   = new TH1F("stlo"    , "S_{T} [GeV]"                  , 2000 , 0    , 20000);
  TH1 *histWeight = new TH1F("weight"  , "event weight"                 , 100  , 0    , 100);

  //--------------------------------------------------------------
  // loop over chains
  //--------------------------------------------------------------

  ExRootTreeReader *treeReader = new ExRootTreeReader(&chain);
  Long64_t numberOfEntries = treeReader->GetEntries();
  int nEventsTotal = 0;

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
  TClonesArray *branchGenJet    = treeReader->UseBranch("GenJet");

  // Loop over all events
  for(Int_t entry = 0; entry < numberOfEntries; ++entry){
  //for(Int_t entry = 0; entry < 100; ++entry){

    InitVars();

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

    if( nEventsTotal % 10000 == 0 ){
      cout << "Processed " << nEventsTotal << " events" << endl;
    }

    //----------------------------------------
    // event weight
    //----------------------------------------

    LHEFEvent* myevent = (LHEFEvent*) branchEvent->At(0);
    if( isSignal ) stweight_ = 1.0;
    else           stweight_ = myevent->Weight;
    histWeight->Fill(stweight_);

    //----------------------------------------
    // get leading jet pt and njets
    //----------------------------------------

    if(branchJet->GetEntries() > 0){
      Jet *jet = (Jet*) branchJet->At(0);
      jet1pt_  = jet->PT;
      jet1eta_ = jet->Eta;
      jet1phi_ = jet->Phi;
      histJetPT->Fill(jet1pt_,weight_*stweight_);
    }

    if(branchJet->GetEntries() > 1){
      Jet *jet = (Jet*) branchJet->At(1);
      jet2pt_  = jet->PT;
      jet2eta_ = jet->Eta;
      jet2phi_ = jet->Phi;
    }

    if(branchJet->GetEntries() > 2){
      Jet *jet = (Jet*) branchJet->At(2);
      jet3pt_  = jet->PT;
      jet3eta_ = jet->Eta;
      jet3phi_ = jet->Phi;

    }

    if(branchJet->GetEntries() > 3){
      Jet *jet = (Jet*) branchJet->At(3);
      jet4pt_  = jet->PT;
      jet4eta_ = jet->Eta;
      jet4phi_ = jet->Phi;
    }

    //----------------------------------------
    // number of pt > 30 GeV jets
    //----------------------------------------

    for( int ijet = 0 ; ijet < branchJet->GetEntries() ; ijet++ ){
      Jet* jet = (Jet*) branchJet->At(ijet);
      //cout << i << " " << Form("%.1f",jet->PT) << " " << Form("%.2f",jet->Eta) << endl;
      if( jet->PT > 30  ) njets_++;
      if( jet->PT > 40  ) njets40_++;
      if( jet->PT > 50  ) njets50_++;
      if( jet->PT > 100 ) njets100_++;
    }

    histNjets->Fill(njets_,weight_*stweight_);

    //----------------------------------------
    // number of pt > 30 GeV gen jets
    //----------------------------------------

    for( int igjet = 0 ; igjet < branchGenJet->GetEntries() ; igjet++ ){
      Jet* genjet = (Jet*) branchGenJet->At(igjet);
      //cout << i << " " << Form("%.1f",jet->PT) << " " << Form("%.2f",jet->Eta) << endl;
      if( genjet->PT > 30 ) ngenjets_++;
    }
    
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

    for( int iel = 0 ; iel < branchElectron->GetEntries() ; iel++ ){
      Electron* el = (Electron*) branchElectron->At(iel);
      stlep_ += el->PT;
      //cout << "Electron " << i << el->PT << endl;
    }

    for( int imu = 0 ; imu < branchMuon->GetEntries() ; imu++ ){
      Muon* mu = (Muon*) branchMuon->At(imu);
      stlep_ += mu->PT;
      //cout << "Muon " << i << mu->PT << endl;
    }

    st_ = met_ + ht_ + stlep_;

    histSt->Fill(st_,weight_*stweight_);
    histStLO->Fill(st_,weight_);

    //----------------------------------------
    // Count various types of particles
    //----------------------------------------
    
    int ibgen1 = -1;
    int ibgen2 = -1;

    //cout << endl << endl;
    for( int ip = 0 ; ip < branchParticle->GetEntries() ; ip++ ){
      GenParticle* p = (GenParticle*) branchParticle->At(ip);

      if( isSignal && ( p->Status < 20 || p->Status > 30 ) ) continue;

      if( abs( p->PID ) == 25 ){
	nh_++;
	pthgen_ = p->PT;
      }
      if( abs( p->PID ) == 24 ) nw_++;
      if( abs( p->PID ) == 23 ) nz_++;
      if( abs( p->PID ) ==  6 ) ntop_++;
      if( abs( p->PID ) == 11 ) ngenels_++;
      if( abs( p->PID ) == 13 ) ngenmus_++;
      if( abs( p->PID ) == 15 ) ngentaus_++;

      if( abs( p->PID ) ==  5 ){
	nbgen_++;
	if     ( ibgen1 < 0 ) ibgen1 = ip;
	else if( ibgen2 < 0 ) ibgen2 = ip;
      }

      //cout << ip << " ID " << p->PID << " status " << p->Status << endl;
    }

    if( nbgen_ == 2 ){
      GenParticle* genb1 = (GenParticle*) branchParticle->At(ibgen1);      
      GenParticle* genb2 = (GenParticle*) branchParticle->At(ibgen2);      

      float deta = genb1->Eta - genb2->Eta;
      float dphi = acos( cos ( genb1->Phi - genb2->Phi ) );
      drbbgen_ = sqrt( deta*deta + dphi*dphi );
    }

    ngenleps_ = ngenels_ + ngenmus_ + ngentaus_;

    //----------------------------------------
    // look at events with 2 b-jets
    //----------------------------------------

    int ib1 = -1;
    int ib2 = -1;

    for( int ij = 0 ; ij < branchJet->GetEntries() ; ij++ ){

      Jet* jet = (Jet*) branchJet->At(ij);

      if( jet->PT < 30.0 ) continue;

      if( jet->BTag & (1 << 1) ){ 
	nb_++; 
	if     ( ib1 < 0 ) ib1 = ij;
	else if( ib2 < 0 ) ib2 = ij;
      }

    }

    if( nb_ >= 2 ){
      if( ib1 < 0 || ib2 < 0 ) cout << "Negative b-jet index" << endl;

      Jet* bjet1 = (Jet*) branchJet->At(ib1);      
      Jet* bjet2 = (Jet*) branchJet->At(ib2);      

      mbb_  = ( (bjet1->P4()) + (bjet2->P4()) ).M();
      ptbb_ = ( (bjet1->P4()) + (bjet2->P4()) ).Pt();

      float deta = bjet1->Eta - bjet2->Eta;
      float dphi = acos( cos ( bjet1->Phi - bjet2->Phi ) );
      drbb_ = sqrt( deta*deta + dphi*dphi );

      bjet1pt_  = bjet1->PT;
      bjet1eta_ = bjet1->Eta;
      bjet1phi_ = bjet1->Phi;

      bjet2pt_  = bjet2->PT;
      bjet2eta_ = bjet2->Eta;
      bjet2phi_ = bjet2->Phi;
    }

    nels_  = branchElectron->GetEntries();
    nmus_  = branchMuon->GetEntries();
    nleps_ = nels_ + nmus_;

    if( nleps_ == 1 ){

      if( nels_ == 1 ){
	Electron* el = (Electron *) branchElectron->At(0);
	leptype_ = 0;
	lep1pt_  = el->PT;
	lep1eta_ = el->Eta;
	lep1phi_ = el->Phi;
      }

      else if( nmus_ == 1 ){
	Muon* mu = (Muon *) branchMuon->At(0);
	leptype_ = 1;
	lep1pt_  = mu->PT;
	lep1eta_ = mu->Eta;
	lep1phi_ = mu->Phi;
      }
      
      else{ 
	cout << "Couldn't find lepton!" << endl;
	exit(0);
      }

      mt_ = sqrt( 2 * met_ * lep1pt_ * ( 1 - cos( metphi_ - lep1phi_) ) );
    }


    // leptype_ = -1;
    // float maxleppt = -1.0;

    // cout << "Electrons " << endl;
    // for( int iel = 0 ; iel < nels_ ; iel++ ){
    //   Electron* el = (Electron *) branchElectron->At(iel);
    //   cout << iel << " " << el->PT << endl;
    // }

    // cout << "Muons " << endl;
    // for( int imu = 0 ; imu < nmus_ ; imu++ ){
    //   Muon* mu = (Muon *) branchMuon->At(imu);
    //   cout << imu << " " << mu->PT << endl;
    // }


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

  } // end loop over events in chain
    //  } // end loop over chains

  fbaby->cd();
  tree->Write();
  fbaby->Close();

  char* histname = Form("output/%s/%s.root",version,prefix.c_str());

  cout << "histname " << histname << endl;

  TFile *fout = TFile::Open( histname ,"RECREATE" );

  fout->cd();

  histMet->Write();
  histHT->Write();
  histJetPT->Write();
  histNjets->Write();
  histSt->Write();
  histStLO->Write();

  fout->Close();

}
