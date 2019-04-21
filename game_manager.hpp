#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "player_input.hpp"
#include "real_point.hpp"
#include "SDL.h"

class GameManager {
  private:
    int _screenWidth = 0;
    int _screenHeight = 0;
    static GameManager *_instance;
    GameManager();
    // (sh|c)ould make a Game class that's a friend
    // to just set window information

  public:
    static GameManager* getInstance();
    int currentLevelIndex = -1;
    char numberOfPlayers = 1;
    RealPoint heroPosition = { 0.0, 0.0 };
    PlayerInput playerInput;
    void setScreenWidth(int);
    void setScreenHeight(int);
    int getScreenWidth();
    int getScreenHeight();
};

#endif
