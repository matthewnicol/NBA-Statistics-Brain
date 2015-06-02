//GameLoader -
//  Go through the meetings folder (../meetings/) and insert every game file from the
//  directory into memory. Record the time it takes, how many plays/games we have loaded
//  for debugging purposes.
//
//  After games are loaded, pass the object to a GameHolder object so that it can handle
//  things like searching etc without having to worry about the logic for loading the file.
//
//  This module is pretty much complete.

#include "GameLoader.h"

//create a new GameLoader and then fill it with plays
GameLoader::GameLoader() {
  totalGames = totalEmptyGames = totalPlays = 0;
  std::cout << "Loading in all games. Just a minute..." << std::endl;

  clock_t t1, t2;
  t1=clock();

  loadInAllGames();

  t2=clock();
  loadTime = ((float)t2-(float)t1) / CLOCKS_PER_SEC;
  std::cout << "Done." << std::endl;
}

//iterate through directory containing the games and load them to memory
void GameLoader::loadInAllGames() {
  DIR *dp;
  struct dirent *dirp;
  std::string line, filename;

  std::ifstream fileread;
  
  //can open directory
  if ((dp = opendir("../meetings/")) != NULL) { 

    //while we still have a file-name in the queue
    while ((dirp = readdir(dp)) != NULL) {
      totalGames++;
      //derive path, open it to check size
      filename = "../meetings/" + std::string(dirp->d_name);
      fileread.open(filename.c_str(), std::ios::binary | std::ios::ate);

      //if we have more than 10 bytes in there, read it
      if (fileread.tellg() > 10) {
        fileread.close();
        fileread.open(filename.c_str());

        //read play by play, add it to our vector
        while (getline(fileread,line)) {
          totalPlays++;
          allplays.push_back((Play(filename, line)));
        }

        fileread.close();

      }

      //our file is empty or too small
      else { 
        totalEmptyGames++;
        fileread.close(); 
      }
    } 
  }

  closedir(dp);
}

//pass the games out
std::vector<Play>& GameLoader::getPlays() {
  return allplays;
}

//Display statistics about database size, load times.
void GameLoader::summary() {
  std::cout << std::endl << "LOAD STATISTICS:" << std::endl;
  std::cout << totalGames << " games found..." << std::endl;
  std::cout << totalEmptyGames << " of them are empty..." << std::endl;
  std::cout << totalPlays << " plays found..." << std::endl;
  std::cout << loadTime << " seconds taken to load database" << std::endl;
  std::cout << std::endl;
}
