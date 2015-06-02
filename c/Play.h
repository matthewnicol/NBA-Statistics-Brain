#ifndef PLAY_H
#define PLAY_H

#include <algorithm>
#include <string>
class Play 
{
private:
  Play() {};
public:
  int date, timeleft;
  char quarter, teamcol;
  int scorea, scoreb;
  std::string teama, teamb, playtext;

  Play(std::string fname, std::string lineoftext);
  bool isShot();
  bool isMake();
  bool isMiss();

  std::string getTeam();
  std::string getOtherTeam();
  bool searchPlay(std::string pattern, bool isCaseSensitive);

  std::string toString() const;

  friend bool operator==(Play &p1, Play &p2);
  friend bool operator<(Play &p1, Play &p2);
  friend bool operator>(Play &p1, Play &p2);
  friend bool operator!=(Play &p1, Play &p2);
  friend bool operator>=(Play &p1, Play &p2);
  friend bool operator<=(Play &p1, Play &p2);
};

#endif
