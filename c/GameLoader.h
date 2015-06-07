#ifndef GAMELOADER_H
#define GAMELOADER_H
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <iostream>

#include "Play.h"
#include "DumbTimer.h"

class GameLoader
{
private:
  int totalGames;
  int totalPlays; 
  int totalEmptyGames;
  float loadTime;
  std::vector<Play> allplays;
  void loadInAllGames();
public:
  GameLoader();
  std::vector<Play>& getPlays();
  void summary();
};

#endif
