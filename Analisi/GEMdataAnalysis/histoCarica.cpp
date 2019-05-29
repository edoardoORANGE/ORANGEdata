#include <iostream>
#include <vector>
#include <string>

#include <fstream>


#include "TCanvas.h"
#include "TH1F.h"
#include "TF1.h"
#include "TStyle.h"


using namespace std;

int main () {

  ifstream inputFile;
  string filename = "histoCarica470.dat";//"CosmiciPMTgemNew_390";
  inputFile.open(filename);

  if(!inputFile) {
    cerr << "Impossibile Leggere il file....";
    exit(1);
  }

  double x;
  std::vector<double> dataset;
  
  while(inputFile >> x) {
    dataset.push_back(x);
  }

  /*
  for(int i = 0 ; i < dataset.size() ; i++){
    cout << dataset[i] << endl;
  }
  */

  vector<double>::const_iterator max = max_element(dataset.begin() , dataset.end()); 
  TH1F h1("h1" , "Charge Histogram" , 100 , -20 , 500);

  for(int i = 0 ; i < dataset.size() ; i++){
    //cout << dataset[i] << endl;
    h1.Fill(dataset[i]);
  }
  

  TCanvas c1("c1" , "" , 1024 , 800);

  // c1.Grid();


  Double_t par[9];
  TF1 *g = new TF1("g" , "gaus" , -20 , 30 );
  TF1 *land = new TF1("land" , "landau" , 31 , *max );
  TF1 *total = new TF1("tot" , "gaus(0) + landau(3)" ,  -20  , *max);
  //g -> SetParameter("Mean" , 0.);
  //land -> SetParameter("MPV" , 15.);
  h1.Fit(g , "R");
  h1.Fit(land , "R");
  g -> GetParameters(&par[0]);
  land -> GetParameters(&par[3]);
  
  total -> SetParameters(par);
  h1.Fit(total , "R");
  

  gStyle -> SetOptFit(1111);
  
  h1.Draw();
  string outName = "histoCarica"+filename+".pdf";
  c1.SaveAs("prova.pdf");

  return 0;
}
