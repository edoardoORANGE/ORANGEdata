#ifndef Event_h
#define Event_h

#include <iostream>
#include <vector>
#include <stdlib>

#include "TH1F.h"
#include "TF1.h"

using namespace std;

class Event {

 public:
  Event(float *time , float *wave) {
    for(int i = 0 ; i<)
  };
  ~Event();

  std::vector<double> GetTimeArray();
  std::vector<double> GetWaveArray();


 private:
  std::vector<double> time, wave;
  

};
