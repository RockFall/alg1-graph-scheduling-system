#pragma once

#include <unordered_map>
#include <iostream>

#include "Client.h"
#include "Store.h"
#include "Grid.h"

class ScheduleSystem {
public:
	std::unordered_map<int, Client> clients;
	std::unordered_map<int, Store> stores;

	ScheduleSystem() { };

	~ScheduleSystem();

	void Populate();

	void CreateClient(int id, int age, std::string state, std::string paymentType, Vector2 pos);
	void CreateStore(int id, int cap, Vector2 pos);
};
