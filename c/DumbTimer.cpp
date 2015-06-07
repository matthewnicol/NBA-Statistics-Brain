//DumbTimer - this is just removed logic for timing functions for code reuse.
// just create it when you need to start timing and call .stop() to get the time (float).
#include "DumbTimer.h"


DumbTimer::DumbTimer(std::string taskname, bool doIPrint) {
  task = taskname;
  autoprint = doIPrint;
  start = clock();
}

float DumbTimer::stop() {
  loadTime = ((float)clock()-(float)start) / CLOCKS_PER_SEC;
  if (autoprint) {
    std::cout << task << " executed in " << loadTime << " seconds.";
  }
  return loadTime;
}


