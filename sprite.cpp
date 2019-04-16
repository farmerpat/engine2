#include "sprite.hpp"

Sprite::Sprite(SDL_Point pos) {
  this->setPos(pos);
}

Sprite::Sprite(SDL_Point pos, int w, int h) {
  this->setPos(pos);
  this->_width = w;
  this->_height = h;
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
}

SDL_Point *Sprite::getPos(void) {
  return this->_pos;
}

void Sprite::setPos(SDL_Point pos) {
  if (!this->_pos) {
    this->_pos = new SDL_Point();
  }

  this->_pos->x = pos.x;
  this->_pos->y = pos.y;
}

void Sprite::setPos(int x, int y) {
  if (!this->_pos) {
    this->_pos = new SDL_Point();
  }

  this->_pos->x = x;
  this->_pos->y = y;
}

int Sprite::getWidth(void) {
  return this->_width;
}

int Sprite::getHeight(void) {
  return this->_height;
}

