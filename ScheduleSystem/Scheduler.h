#pragma once

#include "Client.h"
#include "Store.h"

#include <vector>
#include <unordered_set>

// Responsible for generating the schudule of clients and stores
// based on Gale Shapley algorithm to find a stable match
class Scheduler {
public:
  ~Scheduler();

  // Responsible for passing the parameters to the algorith that
  // calculates the stable matching. Returns a vector<unordered_set>
  // in which each position in the vector represents a Store and the
  // unordered_set contains all the Clients matched to this Store
  static std::vector<std::unordered_set<int>> FindBestSchedule(const std::vector<Client>& storesPref, const std::vector<Store>& stores);

private:
  Scheduler();
  // Find the stable match through a modified version of Gale Shapley's
  // algorithm that accept multiple and limited matchings per Store
  //
  // Each store prefers the Cliets with highest Ticket and each Client prefers
  // a Store closer to him. The tie-breaker is always the one with lower ID
  static std::vector<std::unordered_set<int>> GaleShapleyModified(const std::vector<Client>& storesPref, const std::vector<Store>& stores);
};
