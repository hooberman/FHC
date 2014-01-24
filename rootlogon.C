{
  gROOT->ProcessLine(".L tdrstyle.C");
  setTDRStyle();

  gSystem->Load("Delphes/libDelphes.so");
}
