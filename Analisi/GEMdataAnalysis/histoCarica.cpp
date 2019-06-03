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


using namespace std;

int main () {

  std::vector<double> mpv , mu , empv , emu;
  std::vector<double> voltage , evolt;
  
  
  //for(int number = 470 ; number <= 490 ; number+=10){

    ifstream inputFile;

    int number = 470;
    string numberS = to_string(number);

    //./datasetFromAnalysis/
    string filename = "./datasetFromAnalysis/histoCarica1G100_"+ numberS +".dat";

    //open the file...
    inputFile.open(filename);
    if(!inputFile) {
      cerr << "Impossibile Leggere il file...."<< endl;
      exit(1);
    }


    std::vector<double> gem;
    std::vector<double> trigger;
 
    //Read from file...
    while(!inputFile.eof()) {
      double pmt , pmtB , pmtV;
      inputFile >> pmt 
		>> pmtB >> pmtV;
      gem.push_back(pmt);
      trigger.push_back(pmtB+pmtV);    
    }


    vector<double>::const_iterator max = max_element(gem.begin() , gem.end());

    TString histoName = "Charge Histogram with GEM 1 at 0 V and the others at "+
      numberS + " V";
  
    TH1F h1("Histogram & Fit" , histoName
	    , 1240 , -20 , 3000); //1220


    TString histoName2 = "Vertical Configuration - Charge in Green PMT vs Charge in Blue PMT with 2 GEM at "+
      numberS + " V";

    TH2F h2("h2D" , histoName2 , 
	    2020 , -20 , 3000 , //x set
	    2020 , -20 , 3000); //y set
  
    for(int i = 0 ; i < gem.size() ; i++){

      h2.Fill(trigger[i] , gem[i]);
      h1.Fill(gem[i]);
    }
  
    Double_t altezza = h1.GetMaximum();
  
    TCanvas c1("c1" , "" , 1024 , 800);
 
    TF1 *total = new TF1("tot" , "gaus(0) + landau(3)" ,  -20  , 3000);
    total -> SetParameter(0 , altezza);
    total -> SetParameter(1 , 0.);
    total -> SetParameter(2 , 3.);

    total -> SetParameter(3 , altezza/2); 
    //total -> SetParLimits(3 , 15. , altezza/5.3);
    total -> SetParameter(4 , 15.);
    total -> SetParLimits(4 , 5. , 100.);
    total -> SetParameter(5 , 20.);

    total -> SetParNames("A_{G}", "#mu" , "#sigma_{G}" , "A_{L}" , "MPV" , "#sigma_{L}");

    total -> SetNpx(10000);
    h1.Fit(total , "R");

    mpv.push_back(Double_t(total -> GetParameter(4)));
    empv.push_back(total -> GetParError(4));

    mu.push_back(total -> GetParameter(1));
    emu.push_back(total ->GetParError(1));

    voltage.push_back(Int_t(number));
    evolt.push_back(0);


  gStyle -> SetOptFit(1111);
  //gStyle -> SetOptStat(1);

  
  h1.GetXaxis()->SetRangeUser(-20 , 200);
  h1.SetXTitle("Charge [pC]");
  h1.SetYTitle("Counts");
  h1.Draw();
  
  
  /*

    h2.SetXTitle("Charge PMT Blue [pC]");
    h2.SetYTitle("Charge PMT Green [pC]");
  
    h2.GetXaxis() -> SetRangeUser(0 , 120);
    h2.GetYaxis() -> SetRangeUser(-10 , 120);

    h2.Draw("colz");
  */

 

  /*
  TGraphErrors gr(mpv.size() , &voltage[0] ,
		  &mpv[0] , 0 , &empv[0]);
  
  gr.SetMarkerStyle(21);
  gr.Fit("pol1");
  gr.Draw("AP");
  */


  
  //Save the plot....
  
  TString outName = "histoCarica2GEM_" + numberS + "+Fit.pdf";
  c1.SaveAs(outName);

  system("xdg-open " + outName);

  return 0;
}
