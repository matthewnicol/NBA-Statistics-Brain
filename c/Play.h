#ifndef PLAY_H
#define PLAY_H

#include <algorithm>
#include <string>
#include <iostream>
class Play 
{
private:
  Play() {};
  int len() const;
public:
  int date, timeleft;
  char quarter, teamcol;
  int scorea, scoreb;
  std::string teama, teamb, playtext;

  Play(std::string fname, std::string lineoftext);
  bool isShot();
  bool isMake();
  bool isMiss();

  int search(std::string pattern) const;
  int searchLower(std::string pattern) const;

  std::vector<std::string> getSubstitution() const;
  std::vector<std::string> getMakes() const;
  std::vector<std::string> getMisses() const;

  std::string getTeam();
  std::string getOtherTeam();
  bool searchPlay(std::string pattern, bool isCaseSensitive);

  std::string toString() const;
  std::string gameTitle() const;
  friend bool operator==(Play &p1, Play &p2);
  friend bool operator<(Play &p1, Play &p2);
  friend bool operator>(Play &p1, Play &p2);
  friend bool operator!=(Play &p1, Play &p2);
  friend bool operator>=(Play &p1, Play &p2);
  friend bool operator<=(Play &p1, Play &p2);
};

#endif
