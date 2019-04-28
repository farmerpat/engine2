#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SDL.h"
#include "real_point.hpp"
#include "util.hpp"
#include "controller.hpp"
#include "game_manager.hpp"
#include <string>

class Sprite {
  protected:
    RealPoint *_pos = 0;
    int _width;
    int _height;
    RealPoint *_velocity = 0;
    std::string _tag = "";
    bool _active = true;
    bool _bounded = false;
    int _xScale = 1;
    int _yScale = 1;

    SDL_Rect *_hitbox = 0;
    int _layer = 0;
    // TODO: add std::string _group (or is _layer/_tag good enough?)

  public:
    Controller *_controller = 0;
    Sprite(RealPoint);
    Sprite(RealPoint, int, int);
    bool isActive();
    void setActive();
    void clearActive();
    void setBounded();
    void clearBounded();

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

    virtual void collisionHandler(Sprite*);

    int getLayer();
    void setLayer(int);
};

#endif
