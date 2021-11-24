#pragma once

#include <vector>
#include <iostream>
#include <unordered_set>

#include "Scheduler.h"
#include "Client.h"
#include "Store.h"

// Creates and stores Client and Store instances:
//   from Input with PopulateFromInput()
//   or direct insertion through CreateClient();CreateStore()
// Also responsible for generating the schedule through GetSchedule()
class ScheduleSystem
{
public:
std::vector<Client> clients;
	std::vector<Store> stores;

	// --- CONSTRUCTORS ---
	ScheduleSystem();
	//ScheduleSystem(Grid g);
	~ScheduleSystem();

	// From input (std::cin <<), takes the information used
	// to create Clients and Stores
	void PopulateFromInput();
	// Creates an instance of a Client and stores it into internal vector
	void CreateClient(int id, int age, std::string state, std::string paymentType, Vector2 pos);
	// Creates an instance of a Store and stores it into internal vector
	void CreateStore(int id, int cap, Vector2 pos);

	Client getClient(int id) const;

	// Returns a string of the resulting Schedule in the template:
	// i.e. (0       // store ID
	//       4 3 5   // clients ID - sorted by ticket
	//       1
	//       2 1 0)
	std::string GetScheduling() const;

private:

	//Grid grid;

	// Sorts the internal vector of clients based on ticket value (bigger to smaller)
	//  - if two Clients have the same ticket value, the bigger is the one with lowest id
	void SortClientsByTicket(std::vector<Client>& clientsVec) const;
	void SortClientIDsByTicket(std::vector<int>& clientsVec) const;

	// Send all useful information to the Scheduler and returns the generated Schedule
	std::vector<std::unordered_set<int>> StartScheduling() const;
};
