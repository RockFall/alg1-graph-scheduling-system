#pragma once

#include "Vector2.h"

class Store {
public:
  Store(int id, int maxCap, Vector2 pos);
  ~Store();

  Vector2 getPosition() const;
  int getCapacity() const;
  int getId() const;

private:
  int id_;
  int maxCapacity_;
  Vector2 position_;

};
