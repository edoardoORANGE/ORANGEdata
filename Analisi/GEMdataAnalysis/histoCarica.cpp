#include <iostream>
#include <vector>
#include <string>

#include <fstream>


#include "TCanvas.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include "TStyle.h"
#include "TString.h"


using namespace std;

int main () {

  ifstream inputFile;
  string number = "490";
  string filename = "histoCarica"+number+".dat";//"CosmiciPMTgemNew_390";
  inputFile.open(filename);

  if(!inputFile) {
    cerr << "Impossibile Leggere il file....";
    exit(1);
  }


  std::vector<double> gem;
  std::vector<double> trigger;
 
  
  while(!inputFile.eof()) {
    double pmt , pmtB , pmtV;
    inputFile >> pmt 
	      >> pmtB >> pmtV;
    gem.push_back(pmt);
    trigger.push_back(pmtB+pmtV);    
  }


  vector<double>::const_iterator max = max_element(gem.begin() , gem.end());

  TString histoName = "Charge Histogram with 2 GEM at "+
    number + " V";
  
  TH1F h1("Histogram & Fit" , histoName
	  , 3020 , -20 , 3000);

   TH2F h2("h2" , "" , 
	  1208 , -20 , 3000 , //x set
	  1208 , -20 , 3000); //y set
  
  for(int i = 0 ; i < gem.size() ; i++){

    h2.Fill(trigger[i] , gem[i]);
    //cout << gem[i] << endl;
    h1.Fill(gem[i]);
  }
  
  Double_t altezza = h1.GetMaximum();
  TCanvas c1("c1" , "" , 1024 , 800);

 
  TF1 *total = new TF1("tot" , "gaus(0) + landau(3)" ,  -20  , *max);
  total -> SetParameter(0 , altezza);
  total -> SetParameter(1 , 0.);
  total -> SetParameter(2 , 3.);

  total -> SetParameter(3 , altezza/2);  
  total -> SetParameter(4 , 15.);
  total -> SetParLimits(4 , 5. , 100.);
  total -> SetParameter(5 , 20.);

  total -> SetNpx(10000);
  h1.Fit(total , "R");

  

  gStyle -> SetOptFit(1111);
  //gStyle -> SetOptStat(1);


  h1.GetXaxis()->SetRangeUser(-20 , 200);
  h1.SetXTitle("Charge [pC]");
  h1.SetYTitle("Counts");
  h1.Draw();
  
  //h2.SetXTitle("verde+blu");
  //h2.GetXaxis() -> SetRangeUser(-10 , 500);
  //h2.GetYaxis() -> SetRangeUser(-10 , 500);
  //h2.Draw("colz");

  TString outName = "histoCarica_" + number + "+Fit.pdf";
  c1.SaveAs(outName);

  system("xdg-open " + outName);

  return 0;
}
