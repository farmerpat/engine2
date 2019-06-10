#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SDL.h"
#include "real_point.hpp"
#include "util.hpp"
#include "controller.hpp"
#include "game_manager.hpp"
#include <string>
#include <memory>

class Sprite {
  protected:
    RealPoint *_pos = 0;
    int _width;
    int _height;
    RealPoint *_velocity = 0;
    std::string _tag = "";
    bool _active = true;
    bool _alive = true;
    bool _bounded = false;
    int _xScale = 1;
    int _yScale = 1;
    bool _isAggregate = false;

    SDL_Rect *_hitbox = 0;
    int _layer = 0;
    // TODO: add std::string _group (or is _layer/_tag good enough?)

  public:
    Controller *_controller = 0;
    Controller *_aiController = 0;
    Sprite(RealPoint);
    Sprite(RealPoint, int, int);
    bool isActive();
    void setActive();
    void clearActive();
    void setBounded();
    void clearBounded();
    void kill();
    bool isAlive();
    bool offScreen();

    void setXScale(int);
    void setYScale(int);
    int getXScale();
    int getYScale();
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

    void setWidth(int);
    void setHeight(int);
    int getWidth(void);
    int getHeight(void);
    virtual void render(SDL_Renderer*) = 0;

    std::string getTag();
    void setTag(std::string);

    // calculates where the "real" hitbox
    // is, as hitbox coords are the offset
    // from _pos
    SDL_Rect getGlobalHitBox();
    SDL_Rect *getHitBox();
    void setHitBox(SDL_Rect);

    // NOTE: passing unique_ptr(s) by reference
    // may result in problems...think on whether
    // or not a better solutions exists.
    // should they be shared_ptr instead? that seems
    // computationally expensive...
    virtual void collisionHandler(std::unique_ptr<Sprite>&);
    virtual bool isCollidingWith(std::unique_ptr<Sprite>&);
    bool isAggregate();

    int getLayer();
    void setLayer(int);
};

#endif
