#pragma once

#include "Vector2.h"

class Grid
{
public:
  Grid(int w, int h);
  ~Grid() { };



private:
  int width_;
  int height_;
};
