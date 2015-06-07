#ifndef DUMBTIMER_H
#define DUMBTIMER_H

#include <time.h>
#include <string>
#include <iostream>
class DumbTimer
{
private:
  std::string task;
  clock_t start;
  float loadTime;
  bool autoprint;
public:
  DumbTimer(std::string taskname, bool doIPrint);
  float stop(); 
};

#endif
