#include "include/player_bullet_sprite.hpp"

//*****************************************************************************
// TODO:
// have to add a controller that doesn't change position, but that will destroy
// if it goes off-screen
//*****************************************************************************
PlayerBulletSprite::PlayerBulletSprite(RealPoint pos, RealPoint vel, SDL_Renderer *ren) :
  TexturedSprite(pos, 2, 8, "assets/player_bullet_single_frame.png", ren) {
    int scale = 2;

    this->_hitbox = new SDL_Rect();
    this->_hitbox->x = 0;
    this->_hitbox->y = 0;
    this->_hitbox->w = 2*scale;
    this->_hitbox->h = 8*scale;
    this->setLayer(1);
    this->setTag("player_bullet");
    this->setXScale(scale);
    this->setYScale(scale);
    this->setVelocity(vel);
    this->_controller = new PlayerBulletController(this);
}
