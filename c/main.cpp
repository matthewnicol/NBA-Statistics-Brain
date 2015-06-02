#include "GameHolder.h"
#include "Play.h"
#include "DerivePlayersOnCourt.h"
#include <iostream>

void testPlayToString(GameHolder &games); 
void testFindPlayersOnCourt(GameHolder &games); 

int main()
{
  GameHolder games;

  //TESTING STUFF
    //testPlayToString(games);
    //testFindPlayersOnCourt(games)

}


void testPlayToString(GameHolder &games) {
  Play p1 = games.getPlayNumber(30);
  Play p2 = games.getPlayNumber(3000);
  std::cout << "PLAY 1: " << p1.toString() << std::endl;
  std::cout << "PLAY 2: " << p2.toString() << std::endl;
  std::cout << "PLAY1 < PLAY2 " << (p1 < p2) << std::endl;
  std::cout << "PLAY1 > PLAY2 " << (p1 > p2) << std::endl;
  std::cout << "PLAY1 == PLAY2 " << (p1 == p2) << std::endl;
  std::cout << "PLAY1 <= PLAY2 " << (p1 <= p2) << std::endl;
  std::cout << "PLAY1 >= PLAY2 " << (p1 >= p2) << std::endl;
  std::cout << "PLAY1 != PLAY2 " << (p1 != p2) << std::endl;
}

void testFindPlayersOnCourt(GameHolder &games) {
  DerivePlayersOnCourt p;
  std::vector<std::string> charlotteStarters = p.getStarters(games, 20150415, "CHA");
  std::vector<std::string> torontoStarters = p.getStarters(games, 20150415, "TOR");

  std::cout << "Trying to find the starters for Charlotte and Toronto in their 15/04/2015 game" << std::endl;
  std::cout << std::endl << "Charlotte" << std::endl;

  for (std::string players : charlotteStarters) {
    std::cout << "Player: " << players << std::endl;
  }

  std::cout << std::endl << "Toronto" << std::endl;
  for (std::string players : torontoStarters) {
    std::cout << "Player: " << players << std::endl;
  }
}
