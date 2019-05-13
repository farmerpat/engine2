#ifndef TEXTURED_SPRITE_HPP
#define TEXTURED_SPRITE_HPP

#include <string>
#include "sprite.hpp"

class TexturedSprite : public Sprite {
  public:
    TexturedSprite(RealPoint, int, int, std::string, SDL_Renderer*);
    virtual ~TexturedSprite();
    // TexturedSprite and PrimitiveSprite
    // will need their own render and update functions.
    // children e.g. HeroSprite can override update
    // and grab playerInput from global GameManager
    // primitive sprites will not move at all by default
    // but other descendents of TexturedSprite will have to
    // implement update based on a path of some kind.
    // a path basically starts at the original position
    // and is a collection of points that it will move to,
    // and it will keep track of its curren target point.
    // i guess AI will try to come up with intelligent next points
    // will need some kind of a "move toward" function to work way
    // toward a target point
    void render(SDL_Renderer*);
    // TODO:
    // i think update only gets called on Controllers. e.g. this could/should?
    // be removed
    void update(float);
    SDL_Texture *getTexture();

  protected:
    SDL_Texture *_texture = 0;

};
#endif
