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
#include "TMultiGraph.h"


using namespace std;

int main () {

  // std::vector<double> mpv2 , mu2 , empv2 , emu2 , mpv3 , mu3 , empv3 , emu3;
  // std::vector<double> voltage;
  
  
  //  for(int nGem = 2 ; nGem <= 3 ; nGem++) {
  //  for(int number = 380 ; number <= 420 ; number+=20){


  ifstream inputFile;
  ifstream inputFile2;

  //string numberGEM = to_string(nGem);

  string numberGEM = "1";
  int number = 420;
  string numberS = to_string(number);

  //./datasetFromAnalysis/
  string filename = "histoCarica"+ numberGEM + "G_"+ numberS +".dat";

  //open the file...
  inputFile.open(filename);
  if(!inputFile) {
    cerr << "Impossibile Leggere: " + filename +  " ...."<< endl;
    exit(1);
  }


  std::vector<double> gem;
  std::vector<double> trigger;
  std::vector<double> signal;
 
  //Read from file...
  while(!inputFile.eof()) {
    double pmt , pmtB , pmtV;
    inputFile >> pmt
	      >> pmtB >> pmtV;
    gem.push_back(pmt);
    trigger.push_back(pmtB+pmtV);    
  }

  string filenameS = "histoCarica" + numberGEM + "G_S" + numberS + ".dat";

  //open the file...
  inputFile2.open(filenameS);
  if(!inputFile2) {
    cerr << "Impossibile Leggere: " + filenameS + " ...."<< endl;
    exit(1);
  }

  while(!inputFile2.eof()) {
    double sig;
    inputFile2 >> sig;
    signal.push_back(sig);    
  }


  TCanvas c1("c1" , "" , 1024 , 800);

  vector<double>::const_iterator max = max_element(gem.begin() , gem.end());

  TString histoName = "Charge Histogram with "+numberGEM+" GEM at "+
    numberS + " V";
  
  int nBins = 1220; //1120
  int maxBin = 3000;
  int minBin = -20;
  TH1F h1("Histogram & Fit" , histoName
	  , nBins , minBin , maxBin); //1220

  TH1F h1S("Signal Histogram" , ""
	   , nBins , minBin , maxBin); //1220

    

  TString histoName2 = "Vertical Configuration - Charge in GEM's PMT vs Charge in Trigger's PMTs with 2 GEM at "+
    numberS + " V";

  TH2F h2("h2D" , histoName2 , 
	  3020 , -200 , 3000 , //x set
	  3020 , -200 , 3000); //y set
  
  for(int i = 0 ; i < gem.size() ; i++){
    h2.Fill(trigger[i] , gem[i]);
    h1.Fill(gem[i]);
  }

  for(int i = 0 ; i < signal.size() ; i++) {
    h1S.Fill(signal[i]);
  }
   

  
  //Double_t altezza = h1.GetMaximum();
  Double_t altezzaL = h1S.GetMaximum();

 
  TF1 *land = new TF1("landau" , "landau" ,  -20  , 3000);
  //TF1 *total = new TF1("tot" , "gaus(0) + landau(3)" ,  -20  , 3000);
    
  land -> SetParNames("A_{L}", "MPV" , "#sigma_{L}");
  //cout << altezza << endl;


  //---------parametri della landau-----------

  land -> SetParameter(0 , altezzaL);
  land -> SetParLimits(0 , 0 , 1000);
  land -> SetParameter(1 , 5);
  //land -> SetParLimits(1 , 0. , 30.);
  land -> SetParameter(2 , 20.);
  //land -> SetParLimits(2 , 5. , 10.);
  land -> SetNpx(10000);

  h1S.Fit(land , "R"  , "" , 0 , 30); //100
  //h1.Fit(land , "R" , "" , 1 , 200);

    
  gStyle -> SetOptFit(1111);
  gStyle -> SetOptStat(1);
     
   
  h1S.SetLineColor(3);
  h1.GetXaxis()->SetRangeUser(-20 , 500);
  h1S.GetXaxis()->SetRangeUser(-20 , 500);
    
  h1.SetXTitle("Charge [pC]");
  h1.SetYTitle("Counts");

  //h1.Draw();
  h1S.Draw();

   
  
  /*
    h2.SetYTitle("Charge GEM's PMT [pC]");
    h2.SetXTitle("Charge Trigger PMTs [pC]");
  
    h2.GetXaxis() -> SetRangeUser(40 , 120);
    h2.GetYaxis() -> SetRangeUser(-100 , 500);

    h2.Draw("colz");
  */
 
  
  /*
  TLegend* legend = new TLegend(.1,.7,.3,.9);
  //legend->SetHeader("");
  legend->AddEntry(&gr2 , "MPV for 2 GEM" , "p");
  legend->AddEntry(&gr3 , "MPV for 3 GEM" , "p");
  //legend->AddEntry(land , "Fit of Signal Hist" , "l");
  legend->Draw();
  */


  //Save the plot....
    
  TString outName = "histoCarica"+numberGEM+"G_" + numberS + "+Fit.png";
  c1.SaveAs(outName);
    
  system("gio open " + outName);
    
  return 0;
}
