#include <iostream>
//#include <stdlib>
#include <vector>


#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"
#include "TString.h"

#define NMAX 1024
#define N_MAX_EVENTS 100000

using namespace std;

int main () {

  TString filename = "../../../Data/PMTgem/selfPMTgem2_360.root";
  TFile* file = new TFile(filename);
  TTree* t1 = (TTree*)file -> Get("t1");
  int nEvts = t1 -> GetEntries();
  //float time[NMAX] , wave[NMAX];
  //double timeA[N_MAX_EVENTS][NMAX],waveA[N_MAX_EVENTS][NMAX],dwaveA[N_MAX_EVENTS][NMAX],dtimeA[N_MAX_EVENTS][NMAX];


  int R = 50; //ohm
  float time, wave;
  
  t1 -> SetBranchAddress("time_array" , &time);
  t1 -> SetBranchAddress("wave_array", &wave);

  /*TH1F* Qhist = new TH1F("Qhist" , "Charge Histogram" , 200 , 0 , 10);
  TCanvas *c = new TCanvas("graph" , "" , 200 , 10 , 600 , 400);

  */

  std::vector<float> timeV , waveV;
  cout << "ok";
  
  for (int i = 0 ; i < nEvts ; i++) {
    //t1 -> GetEvent(i);
    //for(int entry = 0 ; entry < NMAX ; entry++) {
    t1 -> GetEntry(1024*i);
    timeV.push_back(time);
    cout << i << endl;
      //waveA[i][entry] = wave[entry]/R;
  }
    /*
    if (i == 2) {
      event_i -> Draw("AL");
    }
    q_signal = event_i -> Integral();
    */
  
  
  // cout << timeA << endl;

  return 0;
}
