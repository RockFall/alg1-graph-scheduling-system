#include "ScheduleSystem.h"

ScheduleSystem::~ScheduleSystem()
{
}

void ScheduleSystem::Populate()
{
	int x, y, cap, storesCount, clientCount, count;
	x = 0;
	y = 0;
	count = 0;

	int idStore = 0, idClient = 0;

	std::cin >> x >> y >> storesCount;

	Grid grid(x, y);

	for (int i = 0; i < storesCount; i++)
	{
		std::cin >> cap >> x >> y;
		CreateStore(count, cap, Vector2(x, y));
		count++;
	}

	int numClientes = 0;
	count = 0;
	std::cin >> clientCount;

	for (int i = 0; i < clientCount; i++)
	{
		int age;
		std::string state, paymentType;
		std::cin >> age >> state >> paymentType >> x >> y;
		CreateClient(count, age, state, paymentType, Vector2(x, y));
		count++;
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
