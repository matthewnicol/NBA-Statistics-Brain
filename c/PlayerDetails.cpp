#include "PlayerDetails.h"

bool valueIn(std::string &value, std::vector<std::string> &vect) {
  for (int i = 0; i < vect.size(); i++) {
    if (vect.at(i) == value) { return true; }
  }
  return false;
}

bool valueIn(std::string &value, std::string vect[5]) {
  for (int i = 0; i < 5; i++) {
    if (value == vect[i]) { return true; }
  }
  return false;
}

void PlayerDetails::getStarters(std::string (&players)[5], std::string game, std::string team, int quarter) {
  for (int i = 0; i < 5; i++) { players[i] = ""; }

  std::vector<std::string> subbedinlater;
  std::string p1;
  int insert = 0;

  for (auto play : (*games)(game, team, quarter)) {
    PlayParser p(play);

    if (p.getAnyName(p1) && !valueIn(p1, subbedinlater) && !valueIn(p1, players)) {
      players[insert++] = p1;
      if (insert != 5 && p.getAssist(p1) && !valueIn(p1, subbedinlater) && !valueIn(p1, players)) {
        players[insert++] = p1;
      } 
    }

    if (p.getSubstitutionIn(p1) && !valueIn(p1, players)) { 
      subbedinlater.push_back(p1); 
    }

    if (insert == 5) { return; }
  }
}

void PlayerDetails::getAllPlayers(std::string (&starters)[5], std::vector<std::string> &bench, std::string game, std::string team) {
  getStarters(starters, game, team, 1);
  std::string name;
  for (auto play: (*games)(game, team)) {
    PlayParser p(play);
    if (p.getAnyName(name) && !valueIn(name, starters) && !valueIn(name, bench)) { bench.push_back(name); }
    if (p.getAssist(name) && !valueIn(name, starters) && !valueIn(name, bench)) { bench.push_back(name); }
    if (p.getSubstitutionIn(name) && !valueIn(name, starters) && !valueIn(name, bench)) { bench.push_back(name); }
  }
}

void PlayerDetails::getPlayerMinutes(int &minutes, std::string game, std::string player, int quarter) {
  std::cout << "Get Player Minutes..." << std::endl;
}

//made shots:
void PlayerDetails::findMadeThrees(std::vector<int> &times, std::string game, std::string team, std::string player, int quarter){
  for (auto play : (*games)(game, team, quarter)) {
    PlayParser p(play);
    std::string name;
    if (p.getMake(name) && p.isThreePointer() && name == player) { times.push_back(play->getTime()); }
  }
}

std::vector<int> PlayerDetails::findMadeTwos(std::string player, int quarter){
std::vector<int> a;
return a;

}

std::vector<int> PlayerDetails::findMadeOnes(std::string player, int quarter){
std::vector<int> a;
return a;

}

//missed shots:
std::vector<int> PlayerDetails::findMissedThrees(std::string player, int quarter){
std::vector<int> a;
return a;

}

std::vector<int> PlayerDetails::findMissedTwos(std::string player, int quarter){
std::vector<int> a;
return a;

}

std::vector<int> PlayerDetails::findMissedOnes(std::string player, int quarter){
std::vector<int> a;
return a;
}
