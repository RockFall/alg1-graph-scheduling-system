#pragma once

#include "Client.h"
#include "Store.h"

#include <vector>
#include <unordered_set>

class Scheduler {
public:
  ~Scheduler();

  static std::vector<std::unordered_set<int>> Schedule(std::vector<std::vector<int>> clientsDist, std::vector<Client> storesPref, std::vector<Store> stores);

private:
  Scheduler();
  static std::vector<std::unordered_set<int>> GaleShapleyModified(std::vector<std::vector<int>> clientsDist, std::vector<Client> storesPref, std::vector<Store> stores);
};
