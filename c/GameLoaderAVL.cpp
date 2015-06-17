//GameLoaderAVL -
//  Trying to reduce search times by loading the plays into an AVL tree.

#include "GameLoaderAVL.h"


//create a new GameLoader and then fill it with plays
GameLoaderAVL::GameLoaderAVL() {
  DumbTimer timer("Load in all games...", true);
  loadInAllGames();
  timer.stop();
}

//iterate through directory containing the games and load them to memory
void GameLoaderAVL::loadInAllGames() {
  DIR *dp;
  struct dirent *dirp;
  std::string line, filename;

  std::ifstream fileread;
  int currentFile = 0; 
  //can open directory
  if ((dp = opendir("../meetings/")) != NULL) { 

    //while we still have a file-name in the queue
    while ((dirp = readdir(dp)) != NULL) {
      //derive path, open it to check size
      filename = "../meetings/" + std::string(dirp->d_name);
      fileread.open(filename.c_str(), std::ios::binary | std::ios::ate);

      //if we have more than 10 bytes in there, read it
      if (fileread.tellg() > 10) {
        fileread.close();
        fileread.open(filename.c_str());

        //read play by play, add it to our vector
        int count = 0 ;
        while (getline(fileread,line)) {
          games[currentFile].playData.push_back((Play(filename, line)));
          count++;
        }
        if (count == 0) { 
          fileread.close();
          continue; 
        }
        root = AVLInsertGame(&games[currentFile], root);
        fileread.close();
        currentFile++;
      }

      //our file is empty or too small
      else { 
        fileread.close(); 
      }
    } 
  }

  closedir(dp);
  std::cout << currentFile << " files" << std::endl;
}

std::vector<Play>* GameLoaderAVL::AVLGetGame(std::string gname) {
  return AVLGetGame(&gname, root);
}

std::vector<Play>* GameLoaderAVL::AVLGetGame(std::string *gname, GameNode *n) {
  if (*gname == n->playData.front().gameTitle()) {
    return &n->playData;
  }
  else {
    return (*gname <= n->playData.front().gameTitle()) ? AVLGetGame(gname, n->left) : AVLGetGame(gname, n->right); 
  }
}

GameNode* GameLoaderAVL::AVLInsertGame(GameNode *newnode, GameNode *oldnode) {
  if (!oldnode) {
    return newnode;
  }
  else {
    if (newnode->playData.front().gameTitle() <= oldnode->playData.front().gameTitle()) {
      oldnode->left = AVLInsertGame(newnode, oldnode->left);
    } 
    else { 
      oldnode->right = AVLInsertGame(newnode, oldnode->right);
    }
  }
  oldnode->height = AVLCalcHeight(oldnode);
  return AVLBalanceNode(oldnode);
}

GameNode* GameLoaderAVL::AVLBalanceNode(GameNode* n) {
  if (std::abs(AVLHeight(n->left)) - std::abs(AVLHeight(n->right)) > 1) {
    if (AVLHeight(n->left->right) < AVLHeight(n->left->right)) {
      n->left = AVLRotateLeft(n->left);
    }
    return AVLRotateRight(n);
  }
  else if (std::abs(AVLHeight(n->right)) - std::abs(AVLHeight(n->left)) > 1) {
    if (AVLHeight(n->right->right) < AVLHeight(n->right->left)) {
      n->right = AVLRotateRight(n->right);
    }
    return AVLRotateLeft(n);
  }
  return n;
}


GameNode* GameLoaderAVL::AVLRotateRight(GameNode* n) {
  GameNode* temp = n->left;
  n->left = temp->right;
  temp->right = n;
  n->height = AVLCalcHeight(n);
  temp->height = AVLCalcHeight(temp);
  return temp;
}

GameNode* GameLoaderAVL::AVLRotateLeft(GameNode* n) {
  GameNode* temp = n->right;
  n->right = temp->left;
  temp->left = n;
  n->height = AVLCalcHeight(n);
  temp->height = AVLCalcHeight(temp);
  return temp;
}

int GameLoaderAVL::AVLHeight(GameNode *g) {
  return (g == NULL) ? -1 : g->height;
}

int GameLoaderAVL::AVLCalcHeight(GameNode *g) {
  if (g != NULL) {
    int left = (g->left == NULL) ? 0 : g->left->height;
    int right = (g->right == NULL) ? 0 : g->right->height;
    return (left > right) ? left+1 : right+1; 
  }
  else { return -1; }
}
