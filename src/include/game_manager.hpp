#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <string>
#include <vector>
#include "SDL.h"
#include "SDL_mixer.h"
#include "player_input.hpp"
#include "real_point.hpp"
class Level;
class Sprite;

class GameManager {
  private:
    std::vector<Mix_Chunk*> _soundEffects;
    std::vector<std::string> _soundEffectNames;

    int _screenWidth = 0;
    int _screenHeight = 0;
    static GameManager *_instance;
    GameManager();
    bool _drawHitBoxes = false;
    Level *_currentLevel = 0;
    Sprite *_hero = 0;
    SDL_Renderer *_windowRenderer = 0;
    // (sh|c)ould make a Game class that's a friend
    // to just set window information
    int getSoundEffectIndex(std::string);

  public:
    static GameManager* getInstance();
    ~GameManager();
    int currentLevelIndex = -1;
    char numberOfPlayers = 1;
    //RealPoint heroPosition = { 0.0, 0.0 };
    PlayerInput playerInput;
    void setScreenWidth(int);
    void setScreenHeight(int);
    int getScreenWidth();
    int getScreenHeight();
    void setDrawHitBoxes();
    void clearDrawHitBoxes();
    bool getDrawHitBoxes();
    void addSpriteToCurrentLevel(Sprite*);
    void setCurrentLevel(Level*);
    Level *getCurrentLevel();
    void setWindowRenderer(SDL_Renderer*);
    SDL_Renderer *getWindowRenderer();
    void playSound(std::string);
    void loadSoundEffect(std::string file);
    Sprite *getHero();
    void setHero(Sprite*);

};
#endif
