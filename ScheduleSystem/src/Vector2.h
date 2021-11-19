#pragma once

#include <string>

// A Vector2 that hold two integer values
class Vector2 {
public:
  int x;
  int y;

  // Constructors
  Vector2() : x(0), y(0){};
  ~Vector2() {};
  Vector2(int x, int y);
  Vector2(int xy);

  // Returns the euclidian distance between two vectors
  int distance_to(const Vector2& vector2) const;

  // Operators override
  int &operator[](int index) {
		return index ? y : x;
  };
  const int &operator[](int index) const
  {
    return index ? y : x;
  };

  operator std::string() const {
    return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
  }
};
