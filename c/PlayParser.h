#ifndef PLAYPARSER_H
#define PLAYPARSER_H

#include <string>
#include "Play.h"

//I want to see if removing the facilities for searching the play reduces the overhead of storing every
//play in memory. This way we can just create one of these whenever we need to do the searching and the
//play doesn't need to know about any of this stuff.

class PlayParser
{
private:
  std::string playtext;

  //len - get the length of the play text, helper for calculating some substrings
  int  len()                           const { return playtext.size(); }

  //search - look for pattern appearing in playtext. update this to a more efficient search later
  int  search(std::string pattern)     const { return playtext.find(pattern); } 
  bool searchBool(std::string pattern) const { return search(pattern) != std::string::npos; }

  //clean - remove unwanted whitespace characters from before or after strings
  std::string& clean(std::string &var) const {
    if (var.size() != 0) {
      while (var.substr(0,1) == " ") {
        var = var.substr(1,var.size()-1); 
      }
      while (var.substr(var.size()-1,1) == " " || var.substr(var.size()-1,1) == "\n") {
        var = var.substr(0, var.size()-1); 
      }
    }
    return var;
  }

public:
  PlayParser() {};
  PlayParser(Play *p) { playtext = p->playtext; };
  PlayParser(Play p) { playtext = p.playtext; };
  void setPlay(Play *p) { playtext = p->playtext; };
  void setPlay(Play  p) { playtext = p.playtext; };

  bool isThreePointer() { return searchBool(" three "); }
  bool isFreeThrow() { return searchBool(" free throw "); }

  //getAnyName - look for a name in the play by testing it against known playtext formats. fill &name with the found
  //name and return success or fail.
  bool getAnyName(std::string &name) {
    return getSubstitutionOut(name) || getMake(name) || getMiss(name) || getAssist(name) || getOffensiveRebound(name) || getDefensiveRebound(name);
  } 

  //getSubstitutionIn - test the play against the substitution format. fill &name with the player who subs in and
  //return success or fail
  bool getSubstitutionIn(std::string &playerIn) const {
    int pos = search(" enters the game for ");
    return clean(playerIn = (pos != std::string::npos) ? playtext.substr(0, pos) : "") != "";
  }

  //getSubstitutionOut - test the play against the substitution format. fill & name with the player who subs out and
  //return success or fail.
  bool getSubstitutionOut(std::string &playerOut) const {
    int pos = search(" enters the game for ");
    return clean(playerOut = (pos != std::string::npos) ? playtext.substr(pos+21, len()-(pos+21)) : "") != ""; 
  }

  //getMake - test the play against the "made shot" format. fill &name with the player who made the shot and return
  //success or fail.
  bool getMake(std::string &maker) const { 
    int posMakes = search(" makes " );
    return clean(maker = (posMakes != std::string::npos) ? playtext.substr(0, posMakes) : "") != ""; 
  }

  //getAssist - test the play against the "made shot with assist" format. fill &name with the player who assisted the
  //shot and return success or fail.
  bool getAssist(std::string &assister) const {
    int posAssists = search(" assists"); int posBracket = search("(");
    return clean(assister = (posAssists != std::string::npos) ? playtext.substr(posBracket+1, posAssists-posBracket) : "") != ""; 
  }

  //getMiss - test the play against the "missed shot" format. fill &name with the player who missed the shot and return
  //success or fail.
  bool getMiss(std::string &misser) const {
    int posMisses = search(" misses ");
    return clean(misser = (posMisses != std::string::npos) ? playtext.substr(0, posMisses) : "") != "";
  }

  //getOffensiveRebound - test the play against the "offensive rebound" format. fill &name with the player who caught
  //the board and return success or fail.
  bool getOffensiveRebound(std::string &catcher) const {
    int pos = search(" offensive rebound");
    return clean(catcher = (pos != std::string::npos) ? playtext.substr(0, pos) : "") != "";
  }

  //getDefensiveRebound - test the play against the "defensive rebound" format. fill &name with the player who caught
  //the board and return success or fail.
  bool getDefensiveRebound(std::string &catcher) const {
    int pos = search(" defensive rebound");
    return clean(catcher = (pos != std::string::npos) ? playtext.substr(0, pos) : "") != "";
  }
};

#endif
