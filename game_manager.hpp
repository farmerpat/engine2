#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "player_input.hpp"
#include "real_point.hpp"
#include "SDL.h"

class GameManager {
  private:
    static GameManager *_instance;
    GameManager();

  public:
    static GameManager* getInstance();
    int currentLevelIndex = -1;
    char numberOfPlayers = 1;
    RealPoint heroPosition = { 0.0, 0.0 };
    PlayerInput playerInput;
};

#endif
