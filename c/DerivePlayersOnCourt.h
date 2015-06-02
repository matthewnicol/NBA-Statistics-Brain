#ifndef DERIVEPLAYERSONCOURT_H
#define DERIVEPLAYERSONCOURT_H

#include <vector>
#include <string>
#include <algorithm>

#include "Play.h"
#include "GameHolder.h"

class DerivePlayersOnCourt
{
private:
  std::vector<Play> lastGamePlays;
  bool earlyExit(std::vector<std::string> &players, std::vector<std::string> &notPlayers);
public:
  DerivePlayersOnCourt() {};
  std::vector<std::string> getAtTime(GameHolder const &h, int date, std::string team, int quarter, int timeleft);
  std::vector<std::string> getStarters(GameHolder const &h, int date, std::string team);
};

#endif
