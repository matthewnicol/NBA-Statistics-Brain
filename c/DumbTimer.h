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
  DumbTimer(std::string taskname, bool doIPrint) {
    task = taskname;
    if ((autoprint = doIPrint)) { std::cout << "Beginning timer >>>> " << taskname << std::endl; }
    start = clock();
  };
  float stop() {
    loadTime = ((float)clock()-(float)start) / CLOCKS_PER_SEC;
    if (autoprint) {
      std::cout << task << " executed in " << loadTime << " seconds." << std::endl << std::endl;
    }
    return loadTime;
  }; 
};

#endif
