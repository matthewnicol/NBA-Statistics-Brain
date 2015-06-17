#include "GameLoaderAVL.h"
#include <vector>
#include "Play.h"
#include "DumbTimer.h"
#include <iostream>

int main()
{
  GameLoaderAVL games;
  DumbTimer t("fetch 1 game...", true);
  games.AVLGetGame("20061222DENSAC");
  t.stop();
}

