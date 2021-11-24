#include "ScheduleSystem.h"

#include <algorithm>
#include <cmath>
#include <chrono>

ScheduleSystem::ScheduleSystem() : clients(), stores()
{
}

//ScheduleSystem::ScheduleSystem(Grid g) : clients(), stores(), grid(g)
//{ }

ScheduleSystem::~ScheduleSystem()
{
}

void ScheduleSystem::PopulateFromInput()
{
	// Variables that will get data from input
	// to the creation of stores and clients
	int x, y, cap, storesCount, clientsCount, id;
	int idStore = 0, idClient = 0;

	// First 2 variables -> grid size (X, Y)
	std::cin >> x >> y;

	// ---- STORES ----
	id = 0;
	std::cin >> storesCount;
	for (int i = 0; i < storesCount; i++)
	{
		std::cin >> cap >> x >> y;
		CreateStore(id, cap, Vector2(x, y));
		id++;
	}

	// ---- CLIENTS ----
	id = 0;
	std::cin >> clientsCount;

	for (int i = 0; i < clientsCount; i++)
	{
		int age;
		std::string state, paymentType;
		std::cin >> age >> state >> paymentType >> x >> y;
		CreateClient(id, age, state, paymentType, Vector2(x, y));
		id++;
	}
}

void ScheduleSystem::CreateClient(int id, int age, std::string state, std::string paymentType, Vector2 pos)
{
	clients.push_back(Client(id, age, state, paymentType, pos));
}

void ScheduleSystem::CreateStore(int id, int cap, Vector2 pos)
{
	stores.push_back(Store(id, cap, pos));
}

Client ScheduleSystem::getClient(int id) const {
	return clients[id];
}

std::string ScheduleSystem::GetScheduling() const{
	// Get scheduling from algorithm
	std::vector<std::unordered_set<int>> schedule = StartScheduling();

	// Generates an output string
	std::string result = "";
	for (int i = 0; i < schedule.size(); i++)
	{
		result += std::to_string(i) + "\n";

		std::vector<int> clientsV;
		clientsV.insert(clientsV.end(), schedule[i].begin(), schedule[i].end());
		SortClientIDsByTicket(clientsV);

		result += std::to_string(clientsV[0]);
		for (int j = 1; j < clientsV.size(); j++)
		{
			result += " " + std::to_string(clientsV[j]);
		}
		result += "\n";
	}

	return result;
}

std::vector<std::unordered_set<int>> ScheduleSystem::StartScheduling() const
{
	std::vector<Client> clientsVec = clients;
	// Sort all clients by it's Ticket using the ID as tie-breaker
	SortClientsByTicket(clientsVec);
	// Starts Scheduling
	return Scheduler::FindBestSchedule(clientsVec, stores);
}

void ScheduleSystem::SortClientsByTicket(std::vector<Client>& clientsVec) const {
	std::sort(clientsVec.rbegin(), clientsVec.rend(), [ ] (const Client &lhs, const Client &rhs)
	{
    if (lhs.getTicketValue() < rhs.getTicketValue())
      return true;
    if (lhs.getTicketValue() > rhs.getTicketValue())
      return false;
    if (lhs.getId() > rhs.getId())
      return true;
    if (lhs.getId() < rhs.getId())
      return false;
    return false;
  });
}

void ScheduleSystem::SortClientIDsByTicket(std::vector<int>& clientsVec) const{
	std::sort(clientsVec.rbegin(), clientsVec.rend(), [&] (const int &lhs, const int &rhs)
	{
    if (getClient(lhs).getTicketValue() < getClient(rhs).getTicketValue())
      return true;
    if (getClient(lhs).getTicketValue() > getClient(rhs).getTicketValue())
      return false;
    if (getClient(lhs).getId() > getClient(rhs).getId())
      return true;
    if (getClient(lhs).getId() < getClient(rhs).getId())
      return false;
    return false;
  });
}
