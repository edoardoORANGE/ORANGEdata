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
#include "TPad.h"


using namespace std;

int main () {


  ifstream inputFileOld;
  ifstream inputFileNew;
  //ifstream inputFile2;

  //string numberGEM = to_string(nGem);


  //-----------OPZIONI OBBLIGATORIE----------
  string numberGEM = "3";
  int number = 420;
  string numberS = to_string(number);
  TString out = ".root"; //.png o .root

  //./datasetFromAnalysis/
  //string cc = ""; //"Old" o ""

  string filenameNew = "histoCarica" + numberGEM + "G_"+ numberS +".dat";
  
  string filenameOld = "histoCaricaOld" + numberGEM + "G_"+ numberS +".dat";
 
  //-----------INIZIO PROGRAMMA-------------

  //open the file...
  inputFileOld.open(filenameOld);
  if(!inputFileOld) {
    cerr << "Impossibile Leggere: " + filenameOld +  " ...."<< endl;
    exit(1);
  }

  inputFileNew.open(filenameNew);
  if(!inputFileNew) {
    cerr << "Impossibile Leggere: " + filenameNew +  " ...."<< endl;
    exit(1);
  }


  std::vector<double> gemNew , gemOld;
  std::vector<double> triggerNew , triggerOld;
  std::vector<double> signalNew , signalOld;
 
  //Read from file...
  while(!inputFileOld.eof()) {
    double pmt , pmtB , pmtV;
    inputFileOld >> pmt
		 >> pmtB >> pmtV;

    gemOld.push_back(pmt);
    triggerOld.push_back(pmtB+pmtV);    
  }

  while(!inputFileNew.eof()) {
    double pmt , pmtB , pmtV;
    inputFileNew >> pmt
		 >> pmtB >> pmtV;

    gemNew.push_back(pmt);
    triggerNew.push_back(pmtB+pmtV);    
  }




  /*
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

  */



  TString histoName = "Charge Histogram with "+numberGEM+" GEM at "+
    numberS + " V";
  
  int nBins = 3020; //3020 , 1220 ,
  int maxBin = 3000;
  int minBin = -20;

  TH1F hOld("Charge Hist at 3 mm Drift" , histoName
	  , nBins , minBin , maxBin); //1220

  TH1F hNew("Charge Hist at 1 cm Drift" , histoName
	  , nBins , minBin , maxBin); //1220



  TH1F h1S("Signal Histogram" , ""
	   , nBins , minBin , maxBin); //1220

  TCanvas c1("c1" , "" , 1024 , 800);

  TString histoName2 = "Vertical Configuration - Charge in GEM's PMT vs Charge in Trigger's PMTs with"+ numberGEM + " GEM at "+
    numberS + " V";

  TH2F h2("h2D" , histoName2 , 
	  3020 , -200 , 3000 , //x set
	  3020 , -200 , 3000); //y set

  
  /* TH1F hBlu1("hBlu" , "Histogramma di Carica PMT Blu1" , 
	    3200 , -200 , 3000);
  TH1F hVerde1("hVerde" , "Histogramma di Carica PMT Verde1" , 
	      3200 , -200 , 3000);
  TH1F hBlu2("hBlu" , "Histogramma di Carica PMT Blu2" , 
	    3200 , -200 , 3000);
  TH1F hVerde2("hVerde" , "Histogramma di Carica PMT Verde2" , 
	      3200 , -200 , 3000);


  for(int i = 0 ; i < caricaBlu1.size() ; i++) {
      hBlu1.Fill(caricaBlu1[i]);
  }
  for(int i = 0 ; i < caricaVerde1.size() ; i++) {
      hVerde1.Fill(caricaVerde1[i]);
  }
  for(int i = 0 ; i < caricaBlu2.size() ; i++) {

      hBlu2.Fill(caricaBlu2[i]);
  }
  for(int i = 0 ; i < caricaVerde2.size() ; i++) {

    hVerde2.Fill(caricaVerde2[i]);
  }

  */
  
  
  for(int i = 0 ; i < gemOld.size() ; i++){
    hOld.Fill(gemOld[i]);
  }
  
  for(int i = 0 ; i < gemNew.size() ; i++) {
    hNew.Fill(gemNew[i]);
  }
 
  
  //gPad -> SetLogy();
   
  hOld.SetLineColor(2);

  hOld.GetXaxis()->SetRangeUser(-20 , 100);
  hNew.GetXaxis()->SetRangeUser(-20 , 100);
    
  hNew.SetXTitle("Charge [pC]");
  hNew.SetYTitle("Counts");


  hNew.Draw();
  hOld.Draw("SAMES");  
  

   
  /*
    
    h2.SetYTitle("Charge GEM's PMT [pC]");
    h2.SetXTitle("Charge Trigger PMTs [pC]");
  
    h2.GetXaxis() -> SetRangeUser(0 , 200);
    h2.GetYaxis() -> SetRangeUser(0 , 200);

    h2.Draw("colz");
  */
 

  /*
  hVerde2.SetLineColor(2);
  hVerde1.GetXaxis() -> SetRangeUser(0 , 200);
  hVerde2.GetXaxis() -> SetRangeUser(0 , 200);
  hVerde1.GetYaxis() -> SetRangeUser(0 , 100);
  hVerde1.Draw();
  hVerde2.Draw("same");
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
    
  TString outName = "DoppioProva" + out;
  c1.SaveAs(outName);
 
  system("gio open " + outName);
  
  return 0;
}
