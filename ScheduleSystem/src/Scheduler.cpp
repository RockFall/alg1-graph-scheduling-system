#include "Scheduler.h"

#include <iostream>
#include <queue>


Scheduler::Scheduler()
{

}

Scheduler::~Scheduler()
{

}

std::vector<std::unordered_set<int>> Scheduler::Schedule(std::vector<std::vector<int>> clientsDist, std::vector<Client> storesPref, std::vector<Store> stores)
{
  return GaleShapleyModified(clientsDist, storesPref, stores);
}

std::vector<std::unordered_set<int>> Scheduler::GaleShapleyModified(std::vector<std::vector<int>> clientsDist, std::vector<Client> storesPref, std::vector<Store> stores)
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
  std::vector<int> storeWithClient(clientsDist.size(), -1);

  while(unmatchedStores.size() > 0){
    // Get unmatched Store
    int sIndex = unmatchedStores.front();
    if (clientInStore[sIndex].size() == stores[sIndex].getCapacity()){
      // If it's capacity is max, removes it form queue
      unmatchedStores.pop();
      continue;
    }
    // Get next client to propose
    int cIndex = storesPref[nextClientIndex[sIndex]].getId();
    nextClientIndex[sIndex]++;

    if (cIndex == 100){
      int a = 3;
    }

    // If this client is unmatched
    if (storeWithClient[cIndex] == -1){
      // Matches it to current 'sIndex' store
      storeWithClient[cIndex] = sIndex;
      clientInStore[sIndex].insert(cIndex);
    }
    // Else if client is matched but prefers this store than current matched store
    //   (distance from client to it's match is far than to this store)
    else {
        bool thisStoreIsNearerToClient = clientsDist[cIndex][storeWithClient[cIndex]] > clientsDist[cIndex][sIndex];
        bool sameDistanceButHasInferiorID = clientsDist[cIndex][storeWithClient[cIndex]] == clientsDist[cIndex][sIndex]
                                            && stores[storeWithClient[cIndex]].getId() > stores[sIndex].getId();
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
