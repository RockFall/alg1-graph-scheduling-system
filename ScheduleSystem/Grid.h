#pragma once

#include "Vector2.h"

#include <vector>

class Grid
{
public:
  Grid();
  Grid(int w, int h);
  ~Grid() { };

  std::vector<int> Dijkstra(Vector2 source, std::vector<Vector2> targets) const;

private:
  // Graph of a grid -> A vector representing each tile and holds a vector of it's neighbours
  std::vector<std::vector<int>> gridGraph_;
  int width_;
  int height_;

  int getId(Vector2 v) const;
  bool isValidPosition(Vector2 pos) const;
  void CreateGraph();
};
