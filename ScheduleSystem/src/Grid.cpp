#include "Grid.h"

#include <vector>
#include <iostream>
#include <unordered_map>
#include <set>

Grid::Grid() : width_(0), height_(0)
{
  gridGraph_ = std::vector<std::vector<int>>(0, std::vector<int>());
}

Grid::Grid(int h, int w) : width_(w+1), height_(h+1)
{
  gridGraph_ = std::vector<std::vector<int>>(width_*height_, std::vector<int>());
  CreateGraph();
}

int INT_MAX = 2147483647;
std::vector<int> Grid::Dijkstra(Vector2 sourceVec, std::vector<Vector2> targets) const {
  // Holds the minimun distance found to each target
  std::vector<int> distanceToTargets = std::vector<int>(targets.size());
  // Holds all targets yet to find
  std::unordered_map<int, std::vector<int>> targetToFind;
  // Conversion from Vector2 to Grig graph vertex id
  int source = getId(sourceVec);

  // CHECKS IF ALL VECTORS HAVE VALID POSITION ON GRID
  if (!isValidPosition(sourceVec)){
    return std::vector<int>();
  } else {
    for (int i = 0; i < targets.size(); i++)
    {
      if (!isValidPosition(targets[i])){
        return std::vector<int>();
      }
      // Inserts all targets to 'targetToFind' <gridId, realId>
      targetToFind[getId(targets[i])].push_back(i);
    }
  }

  // Holds the min distance from source to each vertice
  std::vector<int> min_distance(gridGraph_.size(), INT_MAX);
  min_distance[source] = 0;
  // Set stores the "priority queue" {distance, id}
  std::set<std::pair<int, int>> active_vertices;
  active_vertices.insert({0, source});

  while (!active_vertices.empty() && !targetToFind.empty())
  {
    // Gets first node on set
    int where = active_vertices.begin()->second;



    if (targetToFind.find(where) != targetToFind.end()) {
      for (auto t : targetToFind[where]){
        distanceToTargets[t] = min_distance[where] - 1;
      }
      targetToFind.erase(where);
      if (targetToFind.empty()){
        return distanceToTargets;
      }
      /* PRINT ALL TILES OF GRID
      int count = 0;
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

  return distanceToTargets;
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
