#include <vector>
#include <iostream>

#include "TTree.h"
#include "TFile.h"
#include "TString.h"


using namespace std;

int main () {

  //Apre il rootfile
  
  TString filename("dataset.root");
  TFile* rootfile = new TFile( filename );

  if( !rootfile->IsOpen() ) {
    std::cout << "problems opening root file. exiting... " << std::endl;
    exit(-1);
  }

  std::cout << "Reading data from root file " << filename << std::endl;

  TTree* tree = (TTree*)rootfile -> Get("t1");
  if(!tree) {
    cout << "null pointer for TTree! exiting..." << endl;
    exit(-1);
  }

  //Legge i dati dal rootfile

  tree -> SetBranchAddress("value" , &y);

  int nentries = tree -> GetEntries();

  

  return 0;
}
