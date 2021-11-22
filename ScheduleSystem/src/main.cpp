#include <iostream>

#include <vector>
#include <string>
#include "ScheduleSystem.h"

void TEST(int expected, int actual, std::string testName){
	if (expected == actual) {
		std::cout << testName << "\t\t\tPASSED!" << std::endl;
	} else {
		std::cout << testName << "\t\tFAILED!!!" << std::endl;
		std::cout << "Expected " << expected << " but was " << actual << std::endl;
	}
}

void TestClient() {
	Client c(0, 20, std::string("MG"), std::string("DINHEIRO"), Vector2(7, 4));
	TEST(40, c.getTicketValue(), "Default Ticket Score\t");
	c = Client(0, 20, std::string("ss"), std::string("DINHEIRO"), Vector2(7, 4));
	TEST(-1, c.getTicketValue(), "Invalid Ticket Score 01\t");
	c = Client(0, 20, std::string("MG"), std::string("DINHEIR"), Vector2(7, 4));
	TEST(-1, c.getTicketValue(), "Invalid Ticket Score 02\t");
	c = Client(0, -40, std::string("MG"), std::string("DINHEIR"), Vector2(7, 4));
	TEST(-1, c.getTicketValue(), "Invalid Ticket Score 03\t");
}

void TestDistances() {
	Grid g(8, 6);
	std::vector<Vector2> vecs;
	vecs.push_back(Vector2(6, 1)); // Dijkstra Default
	vecs.push_back(Vector2(0, 5)); // Dijkstra Top-Border
	vecs.push_back(Vector2(7, 5)); // Dijkstra Left-Border
	vecs.push_back(Vector2(1, 0)); // Dijkstra Close
	vecs.push_back(Vector2(1, 1)); // Dijkstra Close Diagonal
	vecs.push_back(Vector2(8, 0)); // Dijkstra Bottom

	TEST(4, g.Dijkstra(Vector2(1, 4), vecs)[0], "Dijkstra Default\t");
	TEST(4, g.Dijkstra(Vector2(0, 0), vecs)[1], "Dijkstra Top-Border\t");
	TEST(6, g.Dijkstra(Vector2(0, 5), vecs)[2], "Dijkstra Left-Border\t");
	TEST(0, g.Dijkstra(Vector2(0, 0), vecs)[3], "Dijkstra Close\t\t");
	TEST(0, g.Dijkstra(Vector2(0, 0), vecs)[4], "Dijkstra Close Diagonal\t");
	TEST(5, g.Dijkstra(Vector2(8, 6), vecs)[4], "Dijkstra Bottom\t");

	g = Grid(20, 20);
	vecs.clear();
	vecs.push_back(Vector2(19, 19));
	TEST(18, g.Dijkstra(Vector2(0, 0), vecs)[0], "Dijkstra Long Diagonal\t");
	vecs.push_back(Vector2(0, 0));
	TEST(0, (g.Dijkstra(Vector2(21, 21), vecs).size() > 0), "Dijkstra Invalid 01\t");
	TEST(0, (g.Dijkstra(Vector2(-1, -1), vecs).size() > 0), "Dijkstra Invalid 02\t");
	vecs.push_back(Vector2(0, -1));
	TEST(0, (g.Dijkstra(Vector2(12, 16), vecs).size() > 0), "Dijkstra Invalid 03\t");
}

void TestScheduling(){
	ScheduleSystem system(Grid(40, 20));
	system.CreateStore(0, 2, Vector2(10, 10));
	system.CreateStore(1, 2, Vector2(0, 10));
	system.CreateClient(0, 10, "MG", "DINHEIRO", Vector2(0, 0));
	system.CreateClient(1, 10, "MG", "DINHEIRO", Vector2(0, 19));
	system.CreateClient(2, 10, "MG", "DINHEIRO", Vector2(0, 11));
	system.CreateClient(3, 10, "MG", "DINHEIRO", Vector2(10, 11));
	system.CreateClient(4, 10, "MG", "DINHEIRO", Vector2(39, 0));
	std::string schedule = system.GetScheduling();
	TEST(0, schedule.compare("0\n0 3\n1\n1 2\n"), "Scheduling Same Ticket&Dist");

	system = ScheduleSystem(Grid(10, 3));
	system.CreateStore(0, 2, Vector2(10, 10));
	system.CreateStore(1, 2, Vector2(0, 10));

}

int main()
{
	//TestClient();
	//TestDistances();
	//TestScheduling();

	ScheduleSystem system;

	std::cout << "Enter data:" << std::endl;
	system.Populate();
	std::string out = system.GetScheduling();
	std::cout << out << std::endl;

	return 0;
}
