#include "game_manager.hpp"

GameManager* GameManager::_instance = 0;

GameManager* GameManager::getInstance () {
  if (_instance == 0) {
    _instance = new GameManager();
  }

  return _instance;
}

GameManager::GameManager() { }

void GameManager::setScreenWidth (int w) {
  // should probably have an assertion of some kind for w>=0
  this->_screenWidth = w;
}

void GameManager::setScreenHeight (int h) {
  this->_screenHeight = h;
}

int GameManager::getScreenWidth() {
  return this->_screenWidth;
}

int GameManager::getScreenHeight() {
  return this->_screenHeight;
}
