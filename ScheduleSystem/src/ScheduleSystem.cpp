#include "ScheduleSystem.h"

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

	Grid grid(x, y);

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

	for (auto& it : clients)
		std::cout << std::string(it.second) << std::endl;
}

void ScheduleSystem::CreateClient(int id, int age, std::string state, std::string paymentType, Vector2 pos)
{
	clients.emplace(std::make_pair(id, Client(id, age, state, paymentType, pos)));
}

void ScheduleSystem::CreateStore(int id, int cap, Vector2 pos)
{
	stores.emplace(std::make_pair(id, Store(id, cap, pos)));
}
