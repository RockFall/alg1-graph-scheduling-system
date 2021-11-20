#include "Grid.h"

#include <vector>
#include <set>

Grid::Grid(int w, int h) : width_(w), height_(h)
{
  gridGraph_ = std::vector<std::vector<int>>(w*h, std::vector<int>());
  CreateGraph();
}

int INT_MAX = 2147483647;
int Grid::dijkstra(const std::vector<std::vector<int>> &graph, Vector2 sourceVec, Vector2 targetVec) {
  int source = getId(sourceVec);
  int target = getId(targetVec);
  // Holds the min distance from source to each vertice
  std::vector<int> min_distance(graph.size(), INT_MAX);
  min_distance[source] = 0;
  std::set<std::pair<int, int>> active_vertices;
  active_vertices.insert({0, source});

  while (!active_vertices.empty())
  {
    int where = active_vertices.begin()->second;
    if (where == target)
      return min_distance[where];
    active_vertices.erase(active_vertices.begin());
    for (auto neigh : graph[where])
      if (min_distance[neigh] > min_distance[where] + 1)
      {
        active_vertices.erase({min_distance[neigh], neigh});
        min_distance[neigh] = min_distance[where] + 1;
        active_vertices.insert({min_distance[neigh], neigh});
      }
    }
    return INT_MAX;
}

void Grid::CreateGraph()
{
  for (int x = 0; x < width_; x++)
  {
    for (int y = 0; y < height_; y++)
    {
      if (x == 0)
      {
        if (y == 0)
        gridGraph_[0].push_back()
        else

      }
    }


  }

}

int Grid::getId(Vector2 v){
  return v.x * width_ + v.y;
}

