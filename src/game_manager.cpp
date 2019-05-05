#include "include/game_manager.hpp"
#include "include/level.hpp"
#include "include/sprite.hpp"

GameManager* GameManager::_instance = 0;

GameManager* GameManager::getInstance () {
  if (_instance == 0) {
    _instance = new GameManager();
  }

  return _instance;
}

GameManager::GameManager() { }

GameManager::~GameManager() {
  for (std::vector<Mix_Chunk*>::size_type i = 0; i < this->_soundEffects.size(); i++) {
    Mix_FreeChunk(this->_soundEffects[i]);
    //delete this->_soundEffects[i];
  }
}

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

void GameManager::playSound(std::string file) {
  int fxIndex = this->getSoundEffectIndex(file);

  if (fxIndex == -1) {
    this->loadSoundEffect(file);
    fxIndex = this->getSoundEffectIndex(file);
  }

  Mix_Chunk *sfx = this->_soundEffects[fxIndex];

  if (sfx) {
    // Mix_VolumeChunk can be used to set the volume for an individual chunk.
    Mix_PlayChannel(-1, sfx, 0);
  }
}

int GameManager::getSoundEffectIndex(std::string file) {
  int index = -1;
  for (std::vector<std::string>::size_type i = 0; i < this->_soundEffectNames.size(); i++) {
    if (this->_soundEffectNames[i] == file) {
      index = i;
      break;

    }
  }

  return index;
}

// TODO: return a bool to check for success.
void GameManager::loadSoundEffect(std::string file) {
  Mix_Chunk *sfx = 0;

  sfx = Mix_LoadWAV(file.c_str());

  if (sfx) {
    this->_soundEffects.push_back(sfx);
    this->_soundEffectNames.push_back(file);
  }
}

Sprite *GameManager::getHero() {
  return this->_hero;
}

void GameManager::setHero(Sprite *s) {
  this->_hero = s;
}
