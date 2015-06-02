#include "GameHolder.h"

GameHolder::GameHolder() {
  GameLoader loader;
  loader.summary();

  playList = loader.getPlays();
}


void GameHolder::newSearch() {
  searching = true;
  search.empty();
}

void GameHolder::addTeamPlays(std::string team) {
  int count = 0;
  std::vector<Play>::iterator it = playList.begin();
  for(Play p : playList) {
    if (p.getTeam() == team) { search.push_back(p); count++; }
  }
}

void GameHolder::addTeamOrOpponentPlays(std::string team) {

}


//search particular game, get plays from specified team
std::vector<Play> GameHolder::getGameOneTeam(int date, std::string team, int quarter) const{

  std::vector<Play> relevantPlays;

  for (Play p : playList) {
    if (p.date == date && p.getTeam() == team) {
      if (quarter == 0 || (quarter != 0 && p.quarter == quarter)) {
        relevantPlays.push_back(p);
      }
    }
  }
  
  return relevantPlays;
}

//search particular game, get plays from both participating teams
std::vector<Play> GameHolder::getGameBothTeams(int date, std::string team, int quarter) const {

  std::vector<Play> relevantPlays;

  for (Play p : playList) {
    if (p.date == date && (p.getTeam() == team || p.getOtherTeam() == team)) {
      if (quarter == 0 || (quarter != 0 && p.quarter == quarter)) {
        relevantPlays.push_back(p);
      }
    }
  }
  
  return relevantPlays;
}

Play GameHolder::getPlayNumber(int number) const {
  return playList[number];
}
