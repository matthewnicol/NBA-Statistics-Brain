
#ifndef TESTPLAYERDETAILS_H
#define TESTPLAYERDETAILS_H

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "PlayerDetails.h"
#include "Play.h"
#include "DumbTimer.h"

class TestPlayerDetails
{
private:
  GameLoaderAVL avl;
public:
  TestPlayerDetails() { 
    PlayerDetails *pd = new PlayerDetails(&avl);
    //printStarters(pd);
    printTeams(pd);
  };

  void printThis(std::string label, const std::string (&printthis)[5]) {
    std::cout << label << " -> ";
    for (int i = 0; i < 5; i++) {
      std::cout << std::setw(30) << std::left << std::to_string(i+1) + ": " + printthis[i];
    }
    std::cout << std::endl;
  };

  void startersWholeGame(PlayerDetails *pd, std::string game) {
    std::cout << std::setw(20) << game << std::endl;
    for (int i = 0; i < 4; i++) {
      std::string playersQa[5];
      std::string playersQb[5];
      pd->getStarters(playersQa, game, game.substr(8,3), i+1);
      pd->getStarters(playersQb, game, game.substr(11,3), i+1);
      printThis("Quarter " + std::to_string(i+1) + " " + game.substr(8,3), playersQa);
      printThis("Quarter " + std::to_string(i+1) + " " + game.substr(11,3), playersQb);
    }
  }

  void printStarters(PlayerDetails *pd) {
    startersWholeGame(pd, "20150415LALSAC");
    startersWholeGame(pd, "20150415MEMIND");
    startersWholeGame(pd, "20150415MILBOS");
    startersWholeGame(pd, "20150415MINOKC");
    startersWholeGame(pd, "20150415NOPSAS");
    startersWholeGame(pd, "20150415NYKDET");
    startersWholeGame(pd, "20150415PHIMIA");
    startersWholeGame(pd, "20150415TORCHA");
  };

  void printTeamGame(PlayerDetails *pd, std::string game) {
    std::string teama = game.substr(8,3);
    std::string teamb = game.substr(11,3);
    std::vector<std::string> bencha;
    std::vector<std::string> benchb;
    std::string startersa[5];
    std::string startersb[5];
    
    pd->getAllPlayers(startersa, bencha, game, teama);
    pd->getAllPlayers(startersb, benchb, game, teamb);
    int max = (bencha.size() > benchb.size()) ? bencha.size() : benchb.size();
    if (max < 5) { max = 5; }
    std::cout << "Starters and bench for game " << game << std::endl;
    std::cout << std::setw(30) << teama << std::setw(30) << teama << std::setw(30) << teamb << std::setw(30) << teamb << std::endl;
    std::cout << std::setw(30) << "Starters" << std::setw(30) << "Bench" << std::setw(30) << "Starters" << std::setw(30) << "Bench" << std::endl;

    for (int i = 0; i < max; i++) {
      std::cout << std::setw(30);if (i < 5) { std::cout << startersa[i]; } else { std::cout << " "; }
      std::cout << std::setw(30);if (i < bencha.size()) { std::cout << bencha.at(i); } else { std::cout << " "; }
      std::cout << std::setw(30);if (i < 5) { std::cout << startersb[i]; } else { std::cout << " "; }
      std::cout << std::setw(30);if (i < benchb.size()) { std::cout << benchb.at(i); } else { std::cout << " "; }
      std::cout << std::endl;
    }
    std::cout << std::endl;
  }


  void printTeams(PlayerDetails *pd) {
    DumbTimer t("Get 8 games... starters and finishers", true);
    printTeamGame(pd, "20150415LALSAC");
    printTeamGame(pd, "20150415MEMIND");
    printTeamGame(pd, "20150415MILBOS");
    printTeamGame(pd, "20150415MINOKC");
    printTeamGame(pd, "20150415NOPSAS");
    printTeamGame(pd, "20150415NYKDET");
    printTeamGame(pd, "20150415PHIMIA");
    printTeamGame(pd, "20150415TORCHA");
    t.stop();
  }
};

#endif
