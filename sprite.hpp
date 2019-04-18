#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SDL.h"
#include "util.hpp"
#include "controller.hpp"

class Sprite {
  protected:
    SDL_Point *_pos = 0;
    int _width;
    int _height;
    SDL_Point *_velocity = 0;
    // Level can be responsible for detecting collisions for each sprite,
    // and each sprite can be sent an array of pointers to sprites
    // that it is colliding with. similar to Controller, can have a CollisionHandler
    // class that is either null or will allow the sprite to deal with it itself.

    // https://wiki.libsdl.org/SDL_IntersectRect
    // https://wiki.libsdl.org/SDL_HasIntersection
    SDL_Rect *_hitbox = 0;

  public:
    Controller *controller = 0;
    Sprite(SDL_Point);
    Sprite(SDL_Point, int, int);
    // made virtual because deleting a child instance,
    // say TexturedSprite via a Sprite*, won't call
    // textured sprite destructor (e.g. will leak memory)
    virtual ~Sprite(void);
    SDL_Point *getPos(void);
    void setPos(SDL_Point);
    void setPos(int, int);
    int getWidth(void);
    int getHeight(void);
    virtual void render(SDL_Renderer*) = 0;

};

#endif
