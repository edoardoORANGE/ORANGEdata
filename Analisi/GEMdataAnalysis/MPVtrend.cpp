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

  std::vector<double> mpv2 , mu2 , empv2 , emu2 , mpv3 , mu3 , empv3 , emu3 , mpv1 , mu1 , empv1 , emu1;
  std::vector<double> voltage , voltage1;
  
  
  for(int nGem = 1 ; nGem <= 3 ; nGem++) {
    for(int number = 380 ; number <= 500 ; number+=20){
      int k = 0;

      if(number == 440 && nGem == 2) {
	number = 450;
      } else if(number == 490 && k == 0 && nGem == 2) {
	number = 480;
	k++;
      } else if(number > 490 && nGem == 2) {
	number = 490;

      } else if(number > 420 && nGem == 3) {
	break;

      } else if(number == 380 && nGem == 1) {
	number = 400;
      } else if (number == 440 && nGem == 1) {
	number = 450; 
      } 
      

      ifstream inputFile;
      ifstream inputFile2;

      // string numberGEM = "2";
      //int number = 380;
      string numberGEM = to_string(nGem);
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
	if(nGem == 3) {
	  gem.push_back(pmt);
	} else {
	  gem.push_back(pmt);
	}
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
	if(nGem == 3) {
	  signal.push_back(sig);    
	} else {
	  signal.push_back(sig);
	}    
      }


    

      vector<double>::const_iterator max = max_element(gem.begin() , gem.end());

      TString histoName = "Charge Histogram with "+numberGEM+" GEM at "+
	numberS + " V";
  
      int nBins; //1120
      int maxBin;
      if(nGem == 1) {
	maxBin = 50;
	nBins = 30;
      } else if(nGem == 2){
	nBins = 1120;
	maxBin = 3000;
      } else if(nGem == 3) {
	nBins = 3020;
	maxBin = 3000;
      }
     
      TH1F h1("Histogram & Fit" , histoName
	      , nBins , -20 , maxBin); //1220

      TH1F h1S("Signal Histogram" , ""
	       , nBins , -20 , maxBin); //1220

    

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
   

  
      Double_t altezza = h1.GetMaximum();
      Double_t altezzaL = h1S.GetMaximum();

      int nMax = 500;
      if(nGem == 1) {
	nMax = 50;
      }
	/* } else {
	nMax = 3000;
	}*/
      
      TF1 *land = new TF1("landau" , "landau" ,  -20  , nMax);
      //TF1 *total = new TF1("tot" , "gaus(0) + landau(3)" ,  -20  , 3000);
    
      land -> SetParNames("A_{L}", "MPV" , "#sigma_{L}");
      //cout << altezza << endl;


      //---------parametri della landau-----------

      land -> SetParameter(0 , altezzaL);
      land -> SetParLimits(0 , 0 , 1000);
      land -> SetParameter(1 , 10);
      //land -> SetParLimits(1 , 0. , 30.);
      land -> SetParameter(2 , 20.);
      //land -> SetParLimits(2 , 5. , 10.);
      land -> SetNpx(10000);

      TF1 *total = new TF1("tot" , "gaus(0) + landau(3)" ,  -20  , 3000);
      total -> SetNpx(10000);

      total -> SetParameter(0 , altezza);
      total -> SetParameter(1 , 2);
      total -> SetParameter(2 , 5);
  
      total -> SetParameter(3 , altezzaL);
      total -> SetParameter(4 , 15);
      //h1.Fit(total , "R" , "" , -20 , 100);
  

      

      //  h1S.Fit(land , "R"  , "" , 0 , 100); //100
      //h1.Fit(land , "R" , "" , 1 , 200);

      if(nGem == 2){
	h1S.Fit(land , "R"  , "" , 0 , 100); //100

	mpv2.push_back(Double_t(land -> GetParameter(1)));
	empv2.push_back(land -> GetParError(1));
      
	mu2.push_back(land -> GetParameter(1));
	//	emu.push_back(total ->GetParError(1));
      
	voltage.push_back(Int_t(number));
      }else if(nGem == 3) {  
	h1.Fit(total , "R" , "" , -20 , 100);
  
	mpv3.push_back(Double_t(total -> GetParameter(4)));
	empv3.push_back(total -> GetParError(4));
	
	mu3.push_back(land -> GetParameter(1));
	//	emu.push_back(total ->GetParError(1));	


      } else if(nGem == 1) {
	h1S.Fit(land , "R"  , "" , 0 , 100); //100

	mpv1.push_back(Double_t(land -> GetParameter(1)));
	empv1.push_back(land -> GetParError(1));
	
	mu1.push_back(land -> GetParameter(1));
	voltage1.push_back(Int_t(number));
	//	emu.push_back(total ->GetParError(1));
      }

    }
  }
  //fine ciclo

  /*
    
    gStyle -> SetOptFit(1111);
    gStyle -> SetOptStat(1);
     
   
    h1S.SetLineColor(3);
    h1.GetXaxis()->SetRangeUser(-20 , 200);
    h1S.GetXaxis()->SetRangeUser(-20 , 200);
    
    h1.SetXTitle("Charge [pC]");
    h1.SetYTitle("Counts");

    h1.Draw();
    h1S.Draw("SAME");

  
    */
 
  
  /*
    h2.SetYTitle("Charge GEM's PMT [pC]");
    h2.SetXTitle("Charge Trigger PMTs [pC]");
  
    h2.GetXaxis() -> SetRangeUser(40 , 120);
    h2.GetYaxis() -> SetRangeUser(-100 , 500);

    h2.Draw("colz");
  */
 
  TCanvas c1("c1" , "" , 1024 , 800);
  
  
  TGraphErrors gr2(mpv2.size() , &voltage[0] ,
		   &mpv2[0] , 0 , &empv2[0]);
    

  for(int i = 0 ; i < mpv3.size() ; i++) {
    mpv3[i] = mpv3[i];
    empv3[i] = empv3[i];
  }

  TGraphErrors gr3(mpv3.size() , &voltage[0] ,
		   &mpv3[0] , 0 , &empv3[0]);
  
  TGraphErrors gr1(mpv1.size() , &voltage1[0] ,
		   &mpv1[0] , 0 , &empv1[0]);
  

  TMultiGraph *mg = new TMultiGraph();

  gr2.SetMarkerStyle(kFullCircle);
  gr3.SetMarkerStyle(kOpenCircle);
  gr1.SetMarkerStyle(kFullSquare);

  gr2.SetMarkerColor(2);
  gr1.SetMarkerColor(1);
    
  c1.SetGrid();

  mg -> SetTitle("MPV Trend with 1/2 GEM");
  mg -> GetYaxis() -> SetTitle("MPV [pC]");
  mg -> GetXaxis() -> SetTitle("Voltage [V]") ;
  mg -> GetXaxis() -> SetLimits(370,500);
  mg -> GetYaxis() -> SetLimits(2,25);
  mg -> Add(&gr2 , "p");
  mg -> Add(&gr3 , "p");
  //mg -> Add(&gr1 , "p");
  mg -> Draw("aPC");
    

  TLegend* legend = new TLegend(1,.8,.3,.9);
  //legend->SetHeader("");
  legend -> AddEntry(&gr2 , "MPV for 2 GEM" , "p");
  legend -> AddEntry(&gr3 , "MPV for 3 GEM" , "p");
  legend -> AddEntry(&gr1 , "MPV for 1 GEM" , "p");
  //legend -> Draw();
    
  //Save the plot....
    
  TString outName = "MPVtrend1_2.png"; 
  //"histoCarica"+numberGEM+"G_" + numberS + "+Fit.png";
  
  c1.SaveAs(outName);
    
  system("gio open " + outName);
    
  return 0;
}
