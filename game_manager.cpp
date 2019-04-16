#include "game_manager.hpp"

GameManager* GameManager::_instance = 0;

GameManager* GameManager::getInstance () {
  if (_instance == 0) {
    _instance = new GameManager();
  }

  return _instance;
}

GameManager::GameManager() { }
