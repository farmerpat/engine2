#include "path_controller.hpp"
#include <iostream>

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
  // newPos is supposed to be currentPos + velocity * dt

  //std::cout << "before " << this->_sprite->getPos()->X() << std::endl;
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
  int targetX = this->_path->getCurrentPoint()->X();
  int targetY = this->_path->getCurrentPoint()->Y();
  int currentX = this->_sprite->getPos()->X();
  int currentY = this->_sprite->getPos()->Y();

  // just to get things moving, don't worry about accuracy tolerance yet,
  // and "know" that we're only moving to the right here.
  // right now the slowest we can move anything is 1 pixel per frame...
  // what do?
  // implement our own point that we round to SDL_Point ?
  // make this a data member we can specify
  // or change to be based on a timer
  float speed = 100;
  // when we're on the last node, we just hang here right now.
  if (targetX == currentX && targetY == currentY) {
    this->_path->advance();
    targetX = this->_path->getCurrentPoint()->X();
    targetY = this->_path->getCurrentPoint()->Y();

  }

  RealPoint newPos;
  //newPos.x = ((currentX + (speed*dt)) > targetX) ? targetX : currentX + speed*dt;
  //speed *= dt;
  float newX;

  if ((currentX + (speed*dt)) > targetX) {
    newX = targetX;
  } else {
    newX = currentX + (speed*dt);
  }

  newPos.setX(newX);
  //newPos.setX(((currentX + (speed*dt)) > targetX) ? targetX : (currentX + (speed * dt)));
  newPos.setY(currentY);

  this->_sprite->setPos(newPos);
  //std::cout << "after " << newPos.X() << std::endl;
}
