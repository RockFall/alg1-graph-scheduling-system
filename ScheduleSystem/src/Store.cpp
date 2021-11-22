#include "Store.h"

Store::Store(int id, int maxCap, Vector2 pos)
  : id_(id), maxCapacity_(maxCap), position_(pos)
{

}

Store::~Store()
{

}

Vector2 Store::getPosition() const {
  return this->position_;
}

int Store::getId() const {
  return this->id_;
}

int Store::getCapacity() const {
  return this->maxCapacity_;
}
