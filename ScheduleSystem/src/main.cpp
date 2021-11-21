#include <iostream>

#include <vector>
#include <string>
#include "ScheduleSystem.h"

void TEST(int expected, int actual, std::string testName){
	if (expected == actual) {
		std::cout << testName << "\t\tPASSED!" << std::endl;
	} else {
		std::cout << testName << " \t\tFAILED!!!" << std::endl;
		std::cout << "Expected " << expected << " but was " << actual << std::endl;
	}
}

void TestClient() {
	Client c(0, 20, std::string("MG"), std::string("DINHEIRO"), Vector2(7, 4));
	TEST(40, c.getTicketValue(), "Default Ticket Score");
	c = Client(0, 20, std::string("ss"), std::string("DINHEIRO"), Vector2(7, 4));
	TEST(-1, c.getTicketValue(), "Invalid Ticket Score 01");
	c = Client(0, 20, std::string("MG"), std::string("DINHEIR"), Vector2(7, 4));
	TEST(-1, c.getTicketValue(), "Invalid Ticket Score 02");
	c = Client(0, -40, std::string("MG"), std::string("DINHEIR"), Vector2(7, 4));
	TEST(-1, c.getTicketValue(), "Invalid Ticket Score 03");
}

void TestDistances() {
	Grid g(8, 6);
	TEST(4, g.Dijkstra(Vector2(1, 4), Vector2(6, 1)), "Dijkstra Default");
	TEST(4, g.Dijkstra(Vector2(0, 0), Vector2(0, 5)), "Dijkstra Top-Border");
	TEST(6, g.Dijkstra(Vector2(0, 5), Vector2(7, 5)), "Dijkstra Left-Border");
	TEST(0, g.Dijkstra(Vector2(0, 0), Vector2(1, 0)), "Dijkstra Close       ");
		TEST(0, g.Dijkstra(Vector2(0, 0), Vector2(1, 1)), "Dijkstra Close Diagonal");
	g = Grid(20, 20);
	TEST(18, g.Dijkstra(Vector2(0, 0), Vector2(19, 19)), "Dijkstra Long Diagonal");
	TEST(-1, g.Dijkstra(Vector2(0, 0), Vector2(22, 19)), "Dijkstra Invalid 01");
	TEST(-1, g.Dijkstra(Vector2(-1, -1), Vector2(15, 19)), "Dijkstra Invalid 02");
	TEST(-1, g.Dijkstra(Vector2(20, 20), Vector2(0, 0)), "Dijkstra Invalid 03");
}

int main()
{
	TestClient();
	TestDistances();

	ScheduleSystem system;

	system.Populate();

  return 0;
}
