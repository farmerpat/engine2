#include "game_manager.hpp"
#include "level.hpp"
#include "sprite.hpp"

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

void GameManager::setDrawHitBoxes() {
  this->_drawHitBoxes = true;
}

void GameManager::clearDrawHitBoxes() {
  this->_drawHitBoxes = false;
}

bool GameManager::getDrawHitBoxes() {
  return this->_drawHitBoxes;
}

void GameManager::addSpriteToCurrentLevel(Sprite *s) {
  this->_currentLevel->addSprite(s);
}

void GameManager::setCurrentLevel(Level *l) {
  this->_currentLevel = l;
}

Level *GameManager::getCurrentLevel() {
  return this->_currentLevel;
}

void GameManager::setWindowRenderer(SDL_Renderer *r) {
  this->_windowRenderer = r;
}

SDL_Renderer *GameManager::getWindowRenderer() {
  return this->_windowRenderer;
}
