#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <memory>
#include <algorithm>
#include "SDL.h"
#include "textured_sprite.hpp"
#include "game_manager.hpp"
#include "controller.hpp"
#include "hero_controller.hpp"
#include "level_controller.hpp"

class LevelController;

class Level {
  public:
    Level(SDL_Renderer*);
    virtual ~Level();
    void update(float);
    void resolveCollisions();
    void removeDeadSprites();
    virtual void render(SDL_Renderer*);
    void addBackgroundElement(std::unique_ptr<Sprite>);
    void addSprite(std::unique_ptr<Sprite>);
    void addUiElement(std::unique_ptr<Sprite>);
    std::unique_ptr<Sprite> &getSpriteByTag(std::string);
    std::vector<std::unique_ptr<Sprite>> const &getSprites();

  protected:
    std::vector<std::unique_ptr<Sprite>> _backgroundElements;
    std::vector<std::unique_ptr<Sprite>> _sprites;
    std::vector<std::unique_ptr<Sprite>> _uiElements;
    void renderBackgroundElements(SDL_Renderer*);
    void renderSprites(SDL_Renderer*);
    void renderUiElements(SDL_Renderer*);
    LevelController *_levelController = 0;

};
#endif
