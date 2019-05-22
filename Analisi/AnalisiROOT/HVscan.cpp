#include <iostream>
#include <stdlib>
#include <vector>


#include "TH1F.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TTree.h"
#include "TFile.h"


#define NMAX 1024
#define N_MAX_EVENTS 100000

int main () {

  filename = "";
  TFile* file = new TFile(filename);

  int nEvts = t1 -> GetEntries();
  float time[NMAX] , wave[NMAX];
  double timeA[N_MAX_EVENTS][NMAX],waveA[N_MAX_EVENTS][NMAX],dwaveA[N_MAX_EVENTS][NMAX],dtimeA[N_MAX_EVENTS][NMAX];


  R = 50 //ohm
  
  t1 -> SetBranchAddress("time_array" , time);
  t1 -> SetBranchAddress("wave_array", wave);

  TH1F* Qhist = new TH1F("Qhist" , "Charge Histogram" , 200 , 0 , 10);
  TCanvas *c = new TCanvas("graph" , "" , 200 , 10 , 600 , 400);


  for (int i = 0 ; i < nEvts ; i++) {
    t1 -> GetEvent(j);
    for(int entry = 0 ; entry < NMAX ; entry++) {
      t1 -> GetEntry(entry+1024*j);
      timeA[j][entry] = time[entry];
      waveA[j][entry] = wave[entry]/R;
    }

    if (i == 2) {
      event_i -> Draw("AL");
    }
    q_signal = event_i -> Integral();
  
  }
  


  return 0;
}
