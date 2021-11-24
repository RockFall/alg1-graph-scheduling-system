#include "Scheduler.h"

#include <iostream>
#include <queue>
#include <chrono>

Scheduler::Scheduler()
{

}

Scheduler::~Scheduler()
{

}

std::vector<std::unordered_set<int>> Scheduler::FindBestSchedule(const std::vector<Client>& storesPref, const std::vector<Store>& stores)
{
  return GaleShapleyModified(storesPref, stores);
}


// Calculates the distance between two points in a 2D Grid
int DistanceBetween(Client c, Store s){
  return s.getPosition().grid_distance_to(c.getPosition());
}

std::vector<std::unordered_set<int>> Scheduler::GaleShapleyModified(const std::vector<Client>& storesPref, const std::vector<Store> & stores)
{
  // Starts with all stores
  std::queue<int> unmatchedStores;
  // Hold what is the next client on store's pref list
  std::vector<int> nextClientIndex;
  for (const auto& s : stores){
    unmatchedStores.push(s.getId());
    nextClientIndex.push_back(0);
  }
  // client[sIndex] gives the client matched to sIndex
  std::vector<std::unordered_set<int>> clientInStore(stores.size(), std::unordered_set<int>());
  // store[cIndex] gives the store macthed to cIndex
  std::vector<int> storeWithClient(storesPref.size(), -1);

  while (!unmatchedStores.empty())
  {
    // Get unmatched Store
    int sIndex = unmatchedStores.front();
    if (clientInStore[sIndex].size() == stores[sIndex].getCapacity() ||
        nextClientIndex[sIndex] >= storesPref.size()){
      // If it's capacity is max or already matched with all clients, removes it form queue
      unmatchedStores.pop();
      continue;
    }
    // Get next client to propose
    Client currClient = storesPref[nextClientIndex[sIndex]];
    int cIndex = currClient.getId();
    nextClientIndex[sIndex]++;

    // If this client is unmatched
    if (storeWithClient[cIndex] == -1){
      // Matches it to current 'sIndex' store
      storeWithClient[cIndex] = sIndex;
      clientInStore[sIndex].insert(cIndex);
    }
    // Else if client is matched but prefers this store than current matched store
    //   (distance from client to it's match is far than to this store)
    else {
      bool thisStoreIsNearerToClient = DistanceBetween(currClient, stores[storeWithClient[cIndex]]) > DistanceBetween(currClient, stores[sIndex]);
      bool sameDistanceButHasInferiorID = DistanceBetween(currClient, stores[storeWithClient[cIndex]]) == DistanceBetween(currClient, stores[sIndex]) && stores[storeWithClient[cIndex]].getId() > stores[sIndex].getId();
      if (thisStoreIsNearerToClient || sameDistanceButHasInferiorID)
      {
        // Removes client from old store
        clientInStore[storeWithClient[cIndex]].erase(cIndex);
        unmatchedStores.push(storeWithClient[cIndex]);

        // And adds it to the new one
        clientInStore[sIndex].insert(cIndex);
        storeWithClient[cIndex] = sIndex;
      }
    }
  }
  return clientInStore;
}
