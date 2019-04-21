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

int Sprite::getWidth(void) {
  return this->_width;
}

int Sprite::getHeight(void) {
  return this->_height;
}

// TODO: does it make more sense
// to just make RealPoint's x/y public?
// there's so much getting and setting
// by its clients and i don't know
// if the compiler is smart enough
// to optimize
void Sprite::move(float dt) {
  float x = this->_pos->X();
  float y = this->_pos->Y();
  x += this->_velocity->X() * dt;
  y += this->_velocity->Y() * dt;
  this->setPos(x, y);
}
