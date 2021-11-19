#pragma once

#include "Vector2.h"

class Store {
public:
  Store(int id, int maxCap, Vector2 pos);
  ~Store();

private:
  int id_;
  int maxCapacity_;
  Vector2 position_;

};
