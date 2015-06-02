#include "Play.h"
#include <iostream>
#include <assert.h>

//Constructor
Play::Play(std::string fname, std::string lineoftext)
{
  date = atoi(fname.substr(12, 8).c_str());
  teama = fname.substr(20, 3);
  teamb = fname.substr(23);  
  std::string q, tl, sa, sb, col;

  //iterate through string to get details within. 
  int fields = 0;
  for (int i = 0; i < lineoftext.length(); i++) {

    //next field
    if (lineoftext.at(i) == ',') { fields++; i++; }
    
    //done loading
    else if (lineoftext.at(i) == '\n') { break; }

    //load into fields
    else if (fields == 0) { q += lineoftext.at(i); }
    else if (fields == 1) { tl += lineoftext.at(i); }
    else if (fields == 2) { col += lineoftext.at(i); }
    else if (fields == 3) { playtext += lineoftext.at(i); }
    else if (fields == 4) { sa += lineoftext.at(i); }
    else if (fields == 5) { sb += lineoftext.at(i); }
  } 

  //any integer conversions
  scorea = atoi(sa.c_str());
  scoreb = atoi(sb.c_str());
  teamcol = col.at(0);
  quarter = atoi(q.c_str());
  timeleft = atoi(tl.c_str());
}


bool Play::occurs(int afterThisDate) {
  return date > afterThisDate;
}

bool Play::occurs(int afterThisDate, int beforeThisDate) {
  return date > afterThisDate && date < beforeThisDate;
}

bool Play::isShot() {
  return isMake() || isMiss();
}

bool Play::isMake() {
  return playtext.find(" makes ") != std::string::npos ||
         playtext.find(" made ") != std::string::npos;
}

bool Play::isMiss() {
  return playtext.find(" misses ") != std::string::npos ||
         playtext.find(" blocks ") != std::string::npos;
}

std::string Play::getTeam() {
  if (teamcol == '3') { return teama; }
  else if (teamcol == '1') { return teamb; }
  else { return "2"; }
}

std::string Play::getOtherTeam() {
  if (teamcol == '3') { return teamb; }
  else if (teamcol == '1') { return teama; }
  else { return "2"; }
}

bool Play::searchPlay(std::string pattern, bool isCaseSensitive) {
  if (isCaseSensitive) {
    return playtext.find(pattern) != std::string::npos;
  }
  else {
    std::string tolower = playtext;
    std::transform(tolower.begin(), tolower.end(), tolower.begin(), ::tolower);
    std::transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
    return tolower.find(pattern) != std::string::npos;
  }
}

//COMPARISON OF PLAYS:

std::string Play::toString() const{
  std::string quart = std::to_string(quarter);
  std::string time = std::to_string(timeleft);
  while (quart.size() < 2) { quart = '0' + quart; }
  while (time.size() < 3) { time = '0' + time; }

  
  return std::to_string(date) + teama + teamb + quart + time;
}

bool operator==(Play &p1, Play &p2){
  return p1.toString().compare(p2.toString()) == 0;
}

bool operator<(Play &p1, Play &p2){
  return p1.toString().compare(p2.toString()) < 0;
}

bool operator>(Play &p1, Play &p2){
  return p1.toString().compare(p2.toString()) > 0;
}

bool operator!=(Play &p1, Play &p2){
  return p1.toString().compare(p2.toString()) != 0;
}

bool operator>=(Play &p1, Play &p2){
  return p1.toString().compare(p2.toString()) >= 0;
}
bool operator<=(Play &p1, Play &p2){
  return p1.toString().compare(p2.toString()) <= 0;
}
