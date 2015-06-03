//Play --
//    Object that represents each individual play. 
//
//    Keep information about the game:
//       -which teams were playing
//       -what date
//    keep information about the play itself:
//       -when? quarter/timeleft
//       -which of the teams caused this play?
//       -textual description of the play.
//
//    Facilitate easy and fast access to data with low memory overhead.
//
//  NOTE: These plays were copied from the ESPN website by hand. There are only a few games (6),
//        and they are all here just for testing purposes. I would never scrape from a website
//        and you shouldn't either. Once a prototype is complete here I will purchase the play
//        by play data somehow but I will not be able to share it here.

#include "Play.h"

void clean(std::string &var) {
  
  while (var.substr(0,1) == " ") {
    var = var.substr(1,var.size()-1); 
  }
  while (var.substr(var.size()-1,1) == " " || var.substr(var.size()-1,1) == "\n") {
    var = var.substr(0, var.size()-1); 
  }
}

Play::Play(std::string fname, std::string lineoftext)
//Constructor: Pass in filename (for deriving date and teams),
//             and line of text (containing other play information).
//             Parse this data in order to fill out all fields.
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

  //integer conversions
  scorea = atoi(sa.c_str());
  scoreb = atoi(sb.c_str());
  teamcol = col.at(0);
  quarter = atoi(q.c_str());
  timeleft = atoi(tl.c_str());
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

//search playtext 
int Play::search(std::string pattern) const {
  return playtext.find(pattern);
}

//convert both strings to lowercase in order to not get tripped up by capitals
int Play::searchLower(std::string pattern) const {
    std::string tolower = playtext;
    std::transform(tolower.begin(), tolower.end(), tolower.begin(), ::tolower);
    std::transform(pattern.begin(), pattern.end(), pattern.begin(), ::tolower);
    return tolower.find(pattern);
  
}

//returns a vector containing the player entering the game & the player exiting the game
std::vector<std::string> Play::getSubstitution() const { 
  int pos;
  std::vector<std::string> players; 

  if ((pos = search(" enters the game for ")) != std::string::npos) { 
    players.push_back(playtext.substr(0, pos));
    players.push_back(playtext.substr(players[0].size()+20, len()-(players[0].size()+20))); 
    clean(players[0]);
    clean(players[1]);
    //std::cout << "COMING IN:  " << players[0] << std::endl;
    //std::cout << "COMING OUT: " << players[1] << std::endl;
  }

  return players; 
}

int Play::len() const { return playtext.size(); }

//returns vector containing the shooter and the assister, or ""
std::vector<std::string> Play::getMakes() const { 
  int pos;
  std::vector<std::string> players;

  if ((pos = search(" makes ")) != std::string::npos) { 
    players.push_back(playtext.substr(0, pos));
  
    if ((pos = search(" assists ")) == std::string::npos) { 
      int pos2 = search("(");
      players.push_back(playtext.substr(pos2,len()-pos2));
    }
    else {
      players.push_back("");
    }
  } 
 
  return players;  
}


//returns a vector containing the shooter and the blocker, or ""
std::vector<std::string> Play::getMisses() const {
  int pos, pos2;
  std::vector<std::string> players;
  if ((pos = search(" makes ")) == std::string::npos) {  

    if ((pos2 = search(" blocks ")) == std::string::npos) {
      return players;
    }
    else {
      pos = search("'s ");
      players.push_back(playtext.substr(pos2+8,len()-(pos+8)));
      players.push_back(playtext.substr(0,pos2));
    } 
  }
  else {
    players.push_back(playtext.substr(0,pos));
    players.push_back("");  
  }

  return players;
}

//COMPARISON OF PLAYS:
//   I create a string of information and compare the two strings in order to
//   determine whether a play occurrs before another play:
//
//    Example of a string:
//      20150319CLECHA01309
//      2015 = year
//          03 = month
//            19 = date
//              CLE = (away?) team
//                 CHA = other team
//                    01 = quarter (overtimes are 5, 6, etc...)
//                      309 = time left in the quarter at that point

//Get string representation of the play for comparison
std::string Play::toString() const{
  std::string quart = std::to_string(quarter);
  std::string time = std::to_string(timeleft);
  while (quart.size() < 2) { quart = '0' + quart; }
  while (time.size() < 3) { time = '0' + time; }

  
  return std::to_string(date) + teama + teamb + quart + time;
}

//comparison operators

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
