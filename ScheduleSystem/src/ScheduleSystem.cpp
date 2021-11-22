#include "ScheduleSystem.h"

#include <algorithm>

ScheduleSystem::ScheduleSystem() : clients(), stores(), grid()
{
}

ScheduleSystem::ScheduleSystem(Grid g) : clients(), stores(), grid(g)
{
}

ScheduleSystem::~ScheduleSystem()
{
}

void ScheduleSystem::Populate()
{
	// Variables that will get data from input
	// to the creation of stores and clients
	int x, y, cap, storesCount, clientsCount, id;
	int idStore = 0, idClient = 0;

	// First 2 variables -> grid size (X, Y)
	std::cin >> x >> y;

	this->grid = Grid(x, y);

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
	std::vector<std::unordered_set<int>> schedule = StartScheduling();
	std::string result = "";
	for (int i = 0; i < schedule.size(); i++)
	{
		result += std::to_string(i) + "\n";

		std::vector<int> clientsV;
		clientsV.insert(clientsV.end(), schedule[i].begin(), schedule[i].end());
		SortClientIDsByTicket(clientsV);

		result += std::to_string(clientsV[0]);
		for (int i = 1; i < clientsV.size(); i++)
		{
			result += " " + std::to_string(clientsV[i]);
		}
		result += "\n";
	}

	return result;
}

std::vector<std::unordered_set<int>> ScheduleSystem::StartScheduling() const
{
	 // Get all client Vector2's
	std::vector<Vector2> clientVectors;
	for (const auto& client : clients){
		clientVectors.push_back(client.getPosition());
	}
	// Calculates the distance from each store to all clients - complexity O(CxS)
	// 'clientsPref[x]' gives a vector of distances from Client x to each Store,
	// 'clientsPref[x][y]' gives the distance from Client x to Store y
	std::vector<std::vector<int>> clientsDist(clients.size(), std::vector<int>(stores.size()));
	for (int s = 0; s < stores.size(); s++)
	{
		std::vector<int> storeDistances = this->grid.Dijkstra(stores[s].getPosition(), clientVectors);
		if (storeDistances.size() == 0) {
			std::cout << "Error on some vector inputed" << std::endl;
			return std::vector<std::unordered_set<int>>(0, std::unordered_set<int>());
		}
		for (int c = 0; c < storeDistances.size(); c++)
		{
			clientsDist[c][s] = storeDistances[c];
		}
	}

	std::vector<Client> clientsVec = clients;
	SortClientsByTicket(clientsVec);
	return Scheduler::Schedule(clientsDist, clientsVec, stores);
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
