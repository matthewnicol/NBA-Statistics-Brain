#ifndef GAMELOADERAVL_H
#define GAMELOADERAVL_H
#include <vector>
#include <string>
#include <sys/types.h>
#include <dirent.h>
#include <fstream>
#include <iostream>

#include "Play.h"
#include "DumbTimer.h"

struct GameNode {
  std::vector<Play> playData;  
  int height;
  GameNode* left = NULL;
  GameNode* right = NULL;
};

class GameLoaderAVL
{
private:
  GameNode games[15000];
  GameNode *root = NULL;
  GameNode* AVLInsertGame(GameNode *newnode, GameNode *oldnode);
  GameNode* AVLRotateLeft(GameNode* n);
  GameNode* AVLRotateRight(GameNode *n);
  GameNode* AVLBalanceNode(GameNode *n);
  int AVLHeight(GameNode* g);
  int AVLCalcHeight(GameNode* g);
  void loadInAllGames();
  std::vector<Play> *AVLGetGame(std::string *gname, GameNode *n);
public:
  std::vector<Play> *AVLGetGame(std::string gname);
  GameLoaderAVL();

  std::vector<Play*> operator()(std::string game, std::string team, int quarter);
  std::vector<Play*> operator()(std::string game, std::string team);
  std::vector<Play*> operator()(std::string game, int quarter);
};

#endif

