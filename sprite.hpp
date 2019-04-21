#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SDL.h"
#include "real_point.hpp"
#include "util.hpp"
#include "controller.hpp"

class Sprite {
  protected:
    RealPoint *_pos = 0;
    int _width;
    int _height;
    RealPoint *_velocity = 0;
    // Level can be responsible for detecting collisions for each sprite,
    // and each sprite can be sent an array of pointers to sprites
    // that it is colliding with. similar to Controller, can have a CollisionHandler
    // class that is either null or will allow the sprite to deal with it itself.

    // https://wiki.libsdl.org/SDL_IntersectRect
    // https://wiki.libsdl.org/SDL_HasIntersection
    SDL_Rect *_hitbox = 0;

  public:
    Controller *_controller = 0;
    Sprite(RealPoint);
    Sprite(RealPoint, int, int);
    // made virtual because deleting a child instance,
    // say TexturedSprite via a Sprite*, won't call
    // textured sprite destructor (e.g. will leak memory)
    virtual ~Sprite(void);
    RealPoint *getPos(void);
    void setPos(RealPoint);
    void setPos(float, float);

    RealPoint *getVelocity(void);
    void setVelocity(float, float);
    void setVelocity(RealPoint);
    void move(float);

    int getWidth(void);
    int getHeight(void);
    virtual void render(SDL_Renderer*) = 0;

};

#endif
