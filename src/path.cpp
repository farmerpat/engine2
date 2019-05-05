#include "include/path.hpp"

Path::Path() { }

Path::~Path() {
  for (std::vector<RealPoint*>::size_type i = 0; i < this->_nodes.size(); i++) {
    delete this->_nodes[i];
  }

  this->_nodes.erase(this->_nodes.begin(), this->_nodes.end());
  this->_nodes.shrink_to_fit();
}

void Path::addNode(RealPoint p) {
  RealPoint *pt = new RealPoint();
  pt->setX(p.X());
  pt->setY(p.Y());
  this->_nodes.push_back(pt);
}

void Path::advance() {
  if (this->_current < (this->_nodes.size() - 1)) {
    this->_current++;
  }
}

void Path::rewind() {
  if (this->_current > 0) {
    this->_current--;
  }
}

RealPoint *Path::getCurrentPoint() {
  return this->_nodes[this->_current];
}
