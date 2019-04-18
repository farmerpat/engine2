#include "path_controller.hpp"

PathController::PathController(Sprite* s, Path* p) {
  this->_sprite = s;
  this->_path = p;
}

PathController::~PathController() {
  if (this->_path) {
    delete this->_path;
  }
}

void PathController::update(float dt) {
  // look at where the sprite is.
  // loot at the current node.
  // if the sprite is where the current node
  // wants it to be, update the path to point
  // to the next node
  // move sprite toward current node
  //
  //we have to use maths to figure out how fast to move
  //or just a speed?
  //start with a speed.
  int targetX = this->_path->getCurrentPoint()->x;
  int targetY = this->_path->getCurrentPoint()->y;
  int currentX = this->_sprite->getPos()->x;
  int currentY = this->_sprite->getPos()->y;

  // just to get things moving, don't worry about accuracy tolerance yet,
  // and "know" that we're only moving to the right here.
  // right now the slowest we can move anything is 1 pixel per frame...
  // what do?
  // implement our own point that we round to SDL_Point ?
  float speed = 1;
  // when we're on the last node, we just hang here right now.
  if (targetX == currentX && targetY == currentY) {
    this->_path->advance();
    targetX = this->_path->getCurrentPoint()->x;
    targetY = this->_path->getCurrentPoint()->y;

  }

  SDL_Point newPos;
  //newPos.x = ((currentX + (speed*dt)) > targetX) ? targetX : currentX + speed*dt;
  //speed *= dt;
  newPos.x = ((currentX + speed) > targetX) ? targetX : currentX + speed;
  newPos.y = currentY;

  this->_sprite->setPos(newPos);
}
