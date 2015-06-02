//DerivePlayersOnCourt -- 
//  Used to find out which players were on the court at a specific time during a specific game.
//
//  Call getAtTime and pass:
//     -h: reference to GameHolder database object
//     -date:     when did this game take place
//     -team:     which team to find players on court for
//     -quarter:  quarter that you want to inspect
//     -timeleft: how much time left in the game
//
//  or call getStarters and pass:
//     -h: reference to GameHolder database object
//     -date:     when did this game take place
//     -team:     which team to find players on court for
//
//  and then it will tell you who was on court at that time.
//
//  I hate this module. With its code duplication and poor whitespace usage it is much like the 2015 Oklahoma City
//  Thunder with Durant, Westbrook and Ibaka injured. To do: fix this crap up.

#include "DerivePlayersOnCourt.h"
#include <iostream>

bool DerivePlayersOnCourt::earlyExit(std::vector<std::string> &players, std::vector<std::string> &notPlayers) {
//earlyExit --
//  called as a helper function each time a player is identified in the plays. It will:
//    remove whitespace from player names
//    remove duplicated players
//    remove players that have been substituted in
//    replace the players list with tidy list
//    check to see if 5 players have been identified & if so return true

  int count = 0;
  std::vector <std::string> starters;

  if (players.size() < 5) { return false; }
  
  for (int i = 0; i < players.size(); i++) {

    //no whitespace @ end of names
    while (players[i].substr(players[i].size()-1,1) == " ") { players[i] = players[i].substr(0, players[i].size()-1); }

    //no players who have newly been substituted in
    for (std::string notplayer : notPlayers) {
      if (players[i] == notplayer) { players[i] = "sub"; break; }
    }

    //no players who have appeared earlier in this list  
    for (int j = i-1; j >= 0; j--) {
      if (players[i] == players[j]) { players[i] = "repeat"; break; }
    }

    //remove bad entries
    if (players[i] != "sub" && players[i] != "repeat") { starters.push_back(players[i]); }

    //report home if we have derived all 5 players.
    if (starters.size() == 5) {
      players = starters;
      return true;
    }
  }

  players = starters;
  return false;
}
 
std::vector<std::string> DerivePlayersOnCourt::getAtTime(GameHolder const &h, int date, std::string team, int quarter, int timeleft) {
//getAtTime --
//   With a specified game, team, quarter and time,
//   identify which players were on the court at that time,
//   by parsing the plays that happen after that time.
//      refer to end for issues with this function & todo

  std::vector<std::string> players;
  std::vector<std::string> notPlayers;
  std::vector<Play> relevantPlays = h.getGameOneTeam(date, team, quarter);
  int findpos;

  for (Play p : relevantPlays) {
    if (p.timeleft < timeleft) {

      if ((findpos = p.playtext.find(" enters the game for ")) != std::string::npos) {
        notPlayers.push_back(p.playtext.substr(0,findpos));
        players.push_back( p.playtext.substr( findpos+21, p.playtext.size()-(findpos+21) ) );
        if (earlyExit(players, notPlayers)) { return players; }
      }

      if ((findpos = p.playtext.find(" makes ")) != std::string::npos) {
        players.push_back(p.playtext.substr(3,findpos-3));
        if (earlyExit(players, notPlayers)) { return players; }
      }

      if ((findpos = p.playtext.find(" assists ")) != std::string::npos) {
        players.push_back(p.playtext.substr(p.playtext.find("("),findpos));
        if (earlyExit(players, notPlayers)) { return players; }
      }

      if ((findpos = p.playtext.find(" misses ")) != std::string::npos) {
        players.push_back(p.playtext.substr(0,findpos));
        if (earlyExit(players, notPlayers)) { return players; }
      }

      if ((findpos = p.playtext.find(" defensive rebound ")) != std::string::npos) {
        players.push_back(p.playtext.substr(0,findpos));
        if (earlyExit(players, notPlayers)) { return players; }
      }

      if ((findpos = p.playtext.find(" offensive foul ")) != std::string::npos) {
        players.push_back(p.playtext.substr(0,findpos));
        if (earlyExit(players, notPlayers)) { return players; }
      }

      if ((findpos = p.playtext.find(" lost ball ")) != std::string::npos) {
        players.push_back(p.playtext.substr(0,findpos));
        if (earlyExit(players, notPlayers)) { return players; }
      }

      if ((findpos = p.playtext.find(" bad pass ")) != std::string::npos) {
        players.push_back(p.playtext.substr(0,findpos));
        if (earlyExit(players, notPlayers)) { return players; }
      }

      if ((findpos = p.playtext.find(" offensive rebound ")) != std::string::npos) {
        players.push_back(p.playtext.substr(0,findpos));
        if (earlyExit(players, notPlayers)) { return players; }
      }
    }
  }

  //if we start our search too late in the quarter there won't be enough plays to
  //derive the players. I need to implement a reverse search but I don't know if I'm
  //ready for that kind of code duplication in my life.
  //also, it probably wouldn't pick up joel anthony since he does nothing, lazy bastard.
  std::cout << "WARNING: COULD NOT FIND 5 UNIQUE PLAYERS ON THE COURT AT THIS TIME." << std::endl;    
  return players;  
}

std::vector<std::string> DerivePlayersOnCourt::getStarters(GameHolder const &h, int date, std::string team) {
//getStarters -
// just call that other function but automatically add obvious paramaters about time.
  return getAtTime(h, date, team, 1, 700);
}

