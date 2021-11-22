#pragma once

#include <vector>
#include <iostream>
#include <unordered_set>

#include "Scheduler.h"
#include "Client.h"
#include "Store.h"
#include "Grid.h"

// It is responsible for storage, creation, and access of clients and stores.
// Also responsible for calling the Scheduler
class ScheduleSystem
{
public:

	ScheduleSystem();
	ScheduleSystem(Grid g);
	~ScheduleSystem();

	// From input (std::cin <<), takes the information used
	// to creating Clients, Stores and the Grid
	void Populate();
	// Creates an instance of a Client and stores it into internal vector
	void CreateClient(int id, int age, std::string state, std::string paymentType, Vector2 pos);
	// Creates an instance of a Store and stores it into internal vector
	void CreateStore(int id, int cap, Vector2 pos);

	Client getClient(int id) const;

	// Return a 2D vector, each index stands for a store ID
	// and it's vector holds all scheduled clients ID
	std::string GetScheduling() const;
	std::vector<std::unordered_set<int>> StartScheduling() const;

private:
	std::vector<Client> clients;
	std::vector<Store> stores;
	Grid grid;

	// Sorts the internal vector of clients based on ticket value (bigger to smaller)
	// If two Clients have the same ticket value, the bigger is the one with lowest id
	void SortClientsByTicket(std::vector<Client>& clientsVec) const;
	void SortClientIDsByTicket(std::vector<int>& clientsVec) const;
};
