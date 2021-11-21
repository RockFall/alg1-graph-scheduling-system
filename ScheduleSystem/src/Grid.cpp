#include "Grid.h"

#include <vector>
#include <iostream>
#include <set>

Grid::Grid(int h, int w) : width_(w), height_(h)
{
  gridGraph_ = std::vector<std::vector<int>>(w*h, std::vector<int>());
  CreateGraph();
}

int INT_MAX = 2147483647;
int Grid::Dijkstra(Vector2 sourceVec, Vector2 targetVec) const {
  if (!isValidPosition(sourceVec) || !isValidPosition(targetVec)){
    return -1;
  }

  int source = getId(sourceVec);
  int target = getId(targetVec);
  // Holds the min distance from source to each vertice
  std::vector<int> min_distance(gridGraph_.size(), INT_MAX);
  min_distance[source] = 0;
  // Set stores the "priority queue" {distance, id}
  std::set<std::pair<int, int>> active_vertices;
  active_vertices.insert({0, source});

  while (!active_vertices.empty())
  {
    // Gets first node on set
    int where = active_vertices.begin()->second;

    if (where == target) {
      int count = 0;
      /*
      for (auto vertex : min_distance)
      {
        if (count == width_) {
          std::cout << std::endl;
          count = 0;
        }
        std::cout << vertex << " ";
        count++;
      }
      std::cout << "\n------------------------" << std::endl;
      */
      return min_distance[where] - 1;
    }

    active_vertices.erase(active_vertices.begin());

    for (auto neigh : gridGraph_[where]) {
      if (min_distance[neigh] > min_distance[where] + 1)
      {
        active_vertices.erase({min_distance[neigh], neigh});
        min_distance[neigh] = min_distance[where] + 1;
        active_vertices.insert({min_distance[neigh], neigh});
      }
    }
  }

  return INT_MAX;
}

bool Grid::isValidPosition(Vector2 pos) const
{
  return pos.x < height_ && pos.x >= 0 &&
         pos.y < width_ && pos.y >= 0;
}

void Grid::CreateGraph()
{
  for (int x = 0; x < height_; x++)
  {
    for (int y = 0; y < width_; y++)
    {

      bool bottom, top;
      bottom = top = true;

      int vertexId = getId(Vector2(x, y));

      // Not Bottom
      if (x != 0)
      {
        gridGraph_[vertexId].push_back(getId(Vector2(x - 1, y)));
        bottom = false;
      }
      // Not Top
      if (x != height_-1){
        gridGraph_[vertexId].push_back(getId(Vector2(x + 1, y)));
        top = false;
      }
      // Not Left side
      if (y != 0){
        gridGraph_[vertexId].push_back(getId(Vector2(x, y - 1)));
        // And not top
        if (!top){
          gridGraph_[vertexId].push_back(getId(Vector2(x + 1, y - 1)));
        }
        // And not bottom
        if (!bottom){
          gridGraph_[vertexId].push_back(getId(Vector2(x - 1, y - 1)));
        }
      }
      // Not Right side
      if (y != width_-1){
        gridGraph_[vertexId].push_back(getId(Vector2(x, y + 1)));
        // And not top
        if (!top){
          gridGraph_[vertexId].push_back(getId(Vector2(x + 1, y + 1)));
        }
        // And not bottom
        if (!bottom){
          gridGraph_[vertexId].push_back(getId(Vector2(x - 1, y + 1)));
        }
      }
    } // end for Y
  } // end for X
}

int Grid::getId(Vector2 v) const {
  return v.x * width_ + v.y;
}
