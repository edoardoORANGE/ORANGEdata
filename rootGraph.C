#include <iostream>
#include <fstream>


#include "TCanvas.h"
#include "TFile.h"
#include "TGraphErrors.h"
#include "TGraph.h"
#include "TMath.h"

using namespace std;

int main () {
  
  std::string filename = "./Trigger/trashcontappi.txt";
  //std::string filename = "CoincidenzeVERDE.txt";
  //std::string filename = "CoincidenzeBLU1.txt";

  //ifstream myfile("vsetBLU.txt");
  ifstream myfile(filename);

  std::vector<Double_t> rateBLU , rateVERDE , rateCO , volt;

  //extract data from the dataset file and save in arrays

  double dat1 , dat2 , dat3 , dat4;
  while(1) {
    myfile >> dat1 >> dat2 >> dat3 >> dat4;
    if(!myfile.good()) break;

    volt.push_back(dat1);
    rateBLU.push_back(dat2/200);
    rateVERDE.push_back(dat3/200);
    rateCO.push_back(dat4/200);
  }

  myfile.close();
  
  cout << "tensione\trateBLU\trateVERDE\trateCOSMICI"<<endl;
  for(int i = 1 ; i < volt.size()+1 ; i++) {
    cout << volt[i-1] << "\t"
	 << rateBLU[i-1] << "\t"
	 << rateVERDE[i-1] << "\t"
	 << rateCO[i-1] << endl;
  }

  vector<Double_t> rerr;

  for(int i = 0 ; i < volt.size() ; i++) {
    rerr.push_back(TMath::Sqrt(rateCO[i]*200)/200);
  }
  
  //print the graph
  
  TCanvas* c1 = new TCanvas("c1","A Simple Graph with error bars",200,10,700,500);
  c1->SetGrid();// create the arrays for the points

  Int_t n = volt.size();

  TGraphErrors* gr = new TGraphErrors(n , &volt[0], &rateCO[0] , 0 , &rerr[0]);

  //ATTENZIONE: TGraph(n , y , x) e non il contrario
  // TGraph* gr = new TGraph(n , &volt[0], &rate[0] ); 
  
  gr->SetTitle("Rate Coincidenze al variare del Th; |Tensione| [mV] ; Rate [Hz]");
  gr->SetLineColor(1);
  gr->SetMarkerColor(1);
  gr->SetMarkerStyle(9);
  gr->SetMarkerSize(.5);
  gr->Draw( "ap");
  c1->SaveAs("graficoCoincidenzeTh.pdf");



  std::vector<double> rateProva;
  for(int i = 0 ; i < volt.size() ; i++) {
    rateProva.push_back( ((rateBLU[i]*rateVERDE[i])*(1E-9)*200) );
  }

//grafico2
  /*
  TCanvas* c2 = new TCanvas("c2","A Simple Graph with error bars",200,10,700,500);
  c2->SetGrid();// create the arrays for the points

TGraphErrors* gr1 = new TGraphErrors(n , &volt[0], &rateProva[0] , 0 , 0);

  //ATTENZIONE: TGraph(n , y , x) e non il contrario
  // TGraph* gr = new TGraph(n , &volt[0], &rate[0] ); 
  
  gr1->SetTitle("Coincidenze Random in funzione della tensione di soglia; |Tensione| [mV] ; Rate [Hz]");
  gr1->SetLineColor(1);
  gr1->SetMarkerColor(1);
  gr1->SetMarkerStyle(9);
  gr1->SetMarkerSize(.5);
  gr1->Draw( "ap");
  c2->SaveAs("graficoCOrandom.pdf");
  */
}

