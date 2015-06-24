#ifndef PLAYERDETAILS_H
#define PLAYERDETAILS_H

#include <vector>
#include <string>
#include <iostream>
#include "GameLoaderAVL.h"
#include "Play.h"
#include "PlayParser.h"

class PlayerDetails
{
private:
  GameLoaderAVL *games;
public:
  PlayerDetails(GameLoaderAVL *g) { games = g; };
  void getStarters(std::string (&players)[5], std::string game, std::string team, int quarter);
  void getAllPlayers(std::string (&starters)[5], std::vector<std::string> &bench, std::string game, std::string team);
  void getPlayerMinutes(int &minutes, std::string game, std::string player, int quarter);
  //made shots:
  void findMadeThrees(std::vector<int> &times, std::string game, std::string team, std::string player, int quarter);
  std::vector<int> findMadeTwos(std::string player, int quarter);
  std::vector<int> findMadeOnes(std::string player, int quarter);

  //missed shots:
  std::vector<int> findMissedThrees(std::string player, int quarter);
  std::vector<int> findMissedTwos(std::string player, int quarter);
  std::vector<int> findMissedOnes(std::string player, int quarter);
};

#endif
