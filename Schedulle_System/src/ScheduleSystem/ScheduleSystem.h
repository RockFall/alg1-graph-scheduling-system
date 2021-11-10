#pragma once

#include <map>

class Client;
class Store;

class ScheduleSystem {
public:
	//std::map<int, Client> clients;
	//std::map<int, Store> stores;

	ScheduleSystem() { };

	~ScheduleSystem();

	void Populate();

};