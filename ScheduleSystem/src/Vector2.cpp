#include "Vector2.h"
#include <cmath>

Vector2::Vector2(int x, int y)
{
  this->x = x;
  this->y = y;
}

Vector2::Vector2(int xy)
{
  this->x = xy;
  this->y = xy;
}

int Vector2::distance_to(const Vector2& vector2) const {
	return std::sqrt((x - vector2.x) * (x - vector2.x) + (y - vector2.y) * (y - vector2.y));
}
