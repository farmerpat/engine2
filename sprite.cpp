#include "sprite.hpp"

Sprite::Sprite(RealPoint pos) {
  this->setPos(pos);
  RealPoint vel(0.0, 0.0);
  this->setVelocity(vel);
}

Sprite::Sprite(RealPoint pos, int w, int h) {
  this->setPos(pos);
  this->_width = w;
  this->_height = h;
  RealPoint vel(0.0, 0.0);
  this->setVelocity(vel);
}

Sprite::~Sprite(void) {
  if (this->_pos) {
    delete this->_pos;
  }

  if (this->_velocity) {
    delete this->_velocity;
  }

  if (this->_hitbox) {
    delete this->_hitbox;
  }

  if (this->_controller) {
    delete this->_controller;
  }
}

bool Sprite::isActive() {
  return this->_active;
}

void Sprite::setActive() {
  this->_active = true;
}

void Sprite::clearActive() {
  this->_active = false;
}

RealPoint *Sprite::getPos(void) {
  return this->_pos;
}

void Sprite::setPos(RealPoint pos) {
  if (!this->_pos) {
    this->_pos = new RealPoint();
  }

  this->_pos->setX(pos.X());
  this->_pos->setY(pos.Y());
}

void Sprite::setPos(float x, float y) {
  if (!this->_pos) {
    this->_pos = new RealPoint();
  }

  this->_pos->setX(x);
  this->_pos->setY(y);
}

RealPoint *Sprite::getVelocity() {
  return this->_velocity;
}

void Sprite::setVelocity(float x, float y) {
  if (!this->_velocity) {
    this->_velocity = new RealPoint();
  }

  this->_velocity->setX(x);
  this->_velocity->setY(y);
}

void Sprite::setVelocity(RealPoint vel) {
  if (!this->_velocity) {
    this->_velocity = new RealPoint();
  }

  this->_velocity->setX(vel.X());
  this->_velocity->setY(vel.Y());
}

// TODO: does it make more sense
// to just make RealPoint's x/y public?
// there's so much getting and setting
// by its clients and i don't know
// if the compiler is smart enough
// to optimize
void Sprite::move(float dt) {
  GameManager *gm = GameManager::getInstance();
  float x = this->_pos->X();
  float y = this->_pos->Y();
  x += this->_velocity->X() * dt;
  y += this->_velocity->Y() * dt;

  if (this->_bounded) {
    if (y < 0) {
      y = 0;
    } else if(y > (gm->getScreenHeight() - (this->getHeight() * this->_yScale))) {
      y = gm->getScreenHeight() - (this->getHeight() * this->_yScale);
    }

    if (x < 0) {
      x = 0;
    } else if (x > (gm->getScreenWidth() - (this->getWidth() * this->_xScale))) {
      x = gm->getScreenWidth() - (this->getWidth() * this->_xScale);
    }
  }

  this->setPos(x, y);
}

int Sprite::getWidth(void) {
  return this->_width;
}

int Sprite::getHeight(void) {
  return this->_height;
}

std::string Sprite::getTag() {
  return this->_tag;
}

void Sprite::setTag(std::string t) {
  this->_tag = t;
}

SDL_Rect Sprite::getGlobalHitBox() {
  SDL_Rect ghb;

  if (this->_hitbox) {
    int x = this->_hitbox->x + (int)this->_pos->X();
    int y = this->_hitbox->y + (int)this->_pos->Y();
    ghb.x = x;
    ghb.y = y;
    ghb.w = this->_hitbox->w;
    ghb.h = this->_hitbox->h;
  }

  return ghb;
}

SDL_Rect *Sprite::getHitBox() {
  return this->_hitbox;
}

void Sprite::setHitBox(SDL_Rect hb) {
  if (!this->_hitbox) {
    this->_hitbox = new SDL_Rect();
  }

  this->_hitbox->x = hb.x;
  this->_hitbox->y = hb.y;
  this->_hitbox->w = hb.w;
  this->_hitbox->h = hb.h;
}

void Sprite::collisionHandler(Sprite *other) { }

int Sprite::getLayer() {
  return this->_layer;
}

void Sprite::setLayer(int l) {
  this->_layer = l;
}

void Sprite::setBounded() {
  this->_bounded = true;
}

void Sprite::clearBounded() {
  this->_bounded = false;
}

void Sprite::setXScale(int s) {
  this->_xScale = s;
}

void Sprite::setYScale(int s) {
  this->_yScale = s;
}

int Sprite::getXScale() {
  return this->_xScale;
}

int Sprite::getYScale() {
  return this->_yScale;
}
