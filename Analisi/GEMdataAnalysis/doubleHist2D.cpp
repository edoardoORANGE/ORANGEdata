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
  string numberGEM = "2";
  int number = 470;
  string numberS = to_string(number);
  TString out = ".root"; //.png o .root

  //./datasetFromAnalysis/
  //string cc = ""; //"Old" o ""

  string filenameNew = "histoCarica" + numberGEM + "G_"+ numberS +".dat";
  
  string filenameOld = "histoCaricaOld" + numberGEM + "G_"+ numberS +".dat";
 
  //-----------INIZIO PROGRAMMA-------------

  //open the file...
  /*   inputFileOld.open(filenameOld);
  if(!inputFileOld) {
    cerr << "Impossibile Leggere: " + filenameOld +  " ...."<< endl;
    exit(1);
    }
  */
  inputFileNew.open(filenameNew);
  if(!inputFileNew) {
    cerr << "Impossibile Leggere: " + filenameNew +  " ...."<< endl;
    exit(1);
  }


  std::vector<double> gemNew , gemOld;
  std::vector<double> triggerNew , triggerOld;
  std::vector<double> signalNew , signalOld;
 
  //Read from file...
  /* while(!inputFileOld.eof()) {
    double pmt , pmtB , pmtV;
    inputFileOld >> pmt
		 >> pmtB >> pmtV;

    gemOld.push_back(pmtB);
    triggerOld.push_back(pmtV);    
    }
  */
  while(!inputFileNew.eof()) {
    double pmt , pmtB , pmtV;
    inputFileNew >> pmt
		 >> pmtB >> pmtV;

    gemNew.push_back(pmt);
    triggerNew.push_back(pmtB + pmtV);    
  }



  TString histoName = "Charge Histogram with "+numberGEM+" GEM at "+
    numberS + " V";
  
  TCanvas c1("c1" , "" , 1024 , 800);

  TString histoName2 = "Charge in GEM's PMT vs Charge in Trigger's PMTs with"+ numberGEM + " GEM at "+
    numberS + " V";

  TH2F h2("h2D" , histoName2 , 
	  2020 , -200 , 3000 , //x set
	  2020 , -200 , 3000); //y set

  for(int i = 0 ; i < gemNew.size() ; i++){
    h2.Fill(triggerNew[i] , gemNew[i]);
  }
 
  
  //gPad -> SetLogy();
  

  /* 
  hOld.SetLineColor(2);

  hOld.GetXaxis()->SetRangeUser(-20 , 100);
  hNew.GetXaxis()->SetRangeUser(-20 , 100);
    
  hNew.SetXTitle("Charge [pC]");
  hNew.SetYTitle("Counts");


  hNew.Draw();
  hOld.Draw("SAMES");  
  */

   
  h2.SetYTitle("Charge Blue PMT [pC]");
  h2.SetXTitle("Charge Green PMT [pC]");
  
  h2.GetXaxis() -> SetRangeUser(0 , 200);
  h2.GetYaxis() -> SetRangeUser(0 , 200);

  h2.Draw("colz");
  

  //Save the plot....
    
  TString outName = "DoppioProva2D" + out;
  c1.SaveAs(outName);
 
  system("gio open " + outName);
  
  return 0;
}
