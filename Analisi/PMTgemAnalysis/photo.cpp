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
#include "TLatex.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TLegend.h"


using namespace std;

int main () {
    ifstream inputFile;

    string filename = "histoCaricaSinglePhoto.dat";

    //open the file...
    inputFile.open(filename);
    if(!inputFile) {
      cerr << "Impossibile Leggere il file 1...."<< endl;
      exit(1);
    }


    std::vector<double> gem;
 
    //Read from file...
    while(!inputFile.eof()) {
      double pmt;

      inputFile >> pmt;
      gem.push_back(pmt);
  
    }

    

    vector<double>::const_iterator max = max_element(gem.begin() , gem.end());
    vector<double>::const_iterator min = min_element(gem.begin() , gem.end());

    TString histoName = "Charge Histogram of Single Photoelectron";
  
    int nBins = 50;

    TH1F h1("Histogram & Fit" , histoName
	    , nBins , *min , *max); //1220
    

    for(int i = 0 ; i < gem.size() ; i++) {
      h1.Fill(gem[i]);
     }
  

  
    Double_t altezza = h1.GetMaximum();
  
    TCanvas c1("c1" , "" , 1024 , 800);
 
    TF1 *gaus = new TF1("gaus" , "gaus" , *min , *max);
    
    
    //parametri del fit

    /*  land -> SetParameter(0 , altezzaL);
    land -> SetParameter(1 , 5.);
    land -> SetParLimits(1 , 5. , 30.);
    land -> SetParameter(2 , 20);
    land -> SetParLimits(2 , 5. , 10.);
    land -> SetNpx(10000);
    */
    h1.Fit(gaus , "R"  , "" , -1 , 2);
    
    gStyle -> SetOptFit(1111);
    gStyle -> SetOptStat(1);
    
    // h1.GetXaxis()->SetRangeUser(-20 , 200);
    h1.SetXTitle("Charge [pC]");
    h1.SetYTitle("Counts");
    h1.Draw();

    TLegend* legend = new TLegend(.6 , .6 , 1 , .4);
    //legend->SetHeader("");
    legend->AddEntry(&h1 , "Total Histogram" , "f");
    //legend->Draw();
    
  
  //Save the plot....
  
  TString outName = "histoCaricaSinglePhoto.png";
  c1.SaveAs(outName);

  system("xdg-open " + outName);

  return 0;
}
