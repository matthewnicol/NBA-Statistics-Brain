#ifndef GAMEHOLDER_H
#define GAMEHOLDER_H

#include <vector>
#include <string>

#include "GameLoader.h"
#include "Play.h"

class GameHolder
{
private:
  std::vector<Play> playList;
  std::vector<Play> search;
  bool searching;
public:
  GameHolder();
  void newSearch();
  void addTeamPlays(std::string team);
  void addTeamOrOpponentPlays(std::string team);

  Play getPlayNumber(int number) const;

  std::vector<Play> getGameOneTeam(int date, std::string team, int quarter) const;
  std::vector<Play> getGameBothTeams(int date, std::string team, int quarter) const;
};

#endif
