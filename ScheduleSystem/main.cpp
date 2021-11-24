#include <iostream>

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include "ScheduleSystem.h"
#include "Grid.h"

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
/*
void TestDistances() {
	Grid g(8, 6);
	std::vector<Vector2> vecs;
	vecs.push_back(Vector2(6, 1)); // Grid Default
	vecs.push_back(Vector2(0, 5)); // Grid Top-Border
	vecs.push_back(Vector2(7, 5)); // Grid Left-Border
	vecs.push_back(Vector2(1, 0)); // Grid Close
	vecs.push_back(Vector2(1, 1)); // Grid Close Diagonal
	vecs.push_back(Vector2(8, 0)); // Grid Bottom

	TEST(4, g.Dijkstra(Vector2(1, 4), vecs)[0], "Grid Default\t\t");
	TEST(4, g.Dijkstra(Vector2(0, 0), vecs)[1], "Grid Bottom\t\t");
	TEST(6, g.Dijkstra(Vector2(0, 5), vecs)[2], "Grid Left-Border\t");
	TEST(0, g.Dijkstra(Vector2(0, 0), vecs)[3], "Grid Close\t\t");
	TEST(0, g.Dijkstra(Vector2(0, 0), vecs)[4], "Grid Close Diagonal\t");
	TEST(5, g.Dijkstra(Vector2(8, 6), vecs)[5], "Grid Top\t\t");

	g = Grid(20, 20);
	vecs.clear();
	vecs.push_back(Vector2(19, 19));
	TEST(18, g.Dijkstra(Vector2(0, 0), vecs)[0], "Grid Long Diagonal\t");
	vecs.push_back(Vector2(0, 0));
	TEST(0, (g.Dijkstra(Vector2(21, 21), vecs).size() > 0), "Grid Invalid 01\t\t");
	TEST(0, (g.Dijkstra(Vector2(-1, -1), vecs).size() > 0), "Grid Invalid 02\t\t");
	vecs.push_back(Vector2(0, -1));
	TEST(0, (g.Dijkstra(Vector2(12, 16), vecs).size() > 0), "Grid Invalid 03\t\t");
}
*/
void TestScheduling(){

	ScheduleSystem system = ScheduleSystem();

	system.CreateStore(0, 2, Vector2(10, 10));
	system.CreateStore(1, 2, Vector2(0, 10));
	system.CreateClient(0, 10, "MG", "DINHEIRO", Vector2(0, 0));
	system.CreateClient(1, 10, "MG", "DINHEIRO", Vector2(0, 19));
	system.CreateClient(2, 10, "MG", "DINHEIRO", Vector2(0, 11));
	system.CreateClient(3, 10, "MG", "DINHEIRO", Vector2(10, 11));
	system.CreateClient(4, 10, "MG", "DINHEIRO", Vector2(39, 0));
	std::string schedule = system.GetScheduling();
	TEST(0, schedule.compare("0\n0 3\n1\n1 2\n"), "Scheduling Same Ticket&Dist");

	system = ScheduleSystem();
	system.CreateStore(0, 3, Vector2(7, 6));
	system.CreateStore(1, 3, Vector2(4, 2));
	system.CreateClient(0, 20, "MG", "DINHEIRO", Vector2(7, 4));
	system.CreateClient(1, 30, "SP", "DINHEIRO", Vector2(4, 8));
	system.CreateClient(2, 70, "RN", "DINHEIRO", Vector2(8, 4));
	system.CreateClient(3, 30, "RS", "DEBITO", Vector2(3, 5));
	system.CreateClient(4, 18, "SP", "DINHEIRO", Vector2(3, 0));
	system.CreateClient(5, 26, "RS", "DEBITO", Vector2(5, 6));
	system.CreateClient(6, 94, "RN", "CREDITO", Vector2(5, 0));
	schedule = system.GetScheduling();
	TEST(0, schedule.compare("0\n2 1 5\n1\n4 3 0\n"), "Scheduling Default Behaviour");

	system = ScheduleSystem();
	system.CreateStore(0, 3, Vector2(1, 1));
	system.CreateStore(1, 2, Vector2(5, 7));
	system.CreateClient(0, 18, "RS", "DINHEIRO", Vector2(0, 0));
	system.CreateClient(1, 20, "RN", "DINHEIRO", Vector2(0, 0));
	system.CreateClient(2, 30, "RJ", "DINHEIRO", Vector2(0, 0));
	system.CreateClient(3, 50, "MG", "DEBITO", Vector2(0, 0));
	system.CreateClient(4, 50, "MG", "DEBITO", Vector2(0, 0));
	system.CreateClient(5, 50, "MG", "DEBITO", Vector2(0, 0));
	schedule = system.GetScheduling();
	TEST(0, schedule.compare("0\n0 1 2\n1\n3 4\n"), "Ticket preference\t");

	auto t1 = std::chrono::high_resolution_clock::now();
	system = ScheduleSystem();
	for (int i = 0; i < 1000; i++)
	{
		system.CreateStore(i, 1, Vector2(0, 0));
	}
	for (int i = 0; i < 1000; i++)
	{
		system.CreateClient(i, 42, "RS", "DEBITO", Vector2(100000, 100000));
	}
	schedule = system.GetScheduling();
	auto t2 = std::chrono::high_resolution_clock::now();
	/* Getting number of milliseconds as an integer. */
  auto ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	TEST(1, ms_int.count() < 5000 , "Big data10^3 < 5s\t");

	t1 = std::chrono::high_resolution_clock::now();
	system = ScheduleSystem();
	for (int i = 0; i < 1000; i++)
	{
		system.CreateStore(i, 10, Vector2(0, 0));
	}
	for (int i = 0; i < 10000; i++)
	{
		system.CreateClient(i, 42, "RS", "DEBITO", Vector2(100000, 100000));
	}
	schedule = system.GetScheduling();
	t2 = std::chrono::high_resolution_clock::now();
	/* Getting number of milliseconds as an integer. */
  ms_int = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	TEST(1, ms_int.count() < 5000 , "Big data 10^4 < 5s\t");
}

enum RUNTYPE
{
	TEST_MODE,
	DEBUG_MODE,
	LAUNCH_MODE
};

int main()
{
	RUNTYPE runType = RUNTYPE::LAUNCH_MODE;

	switch (runType)
	{
	case LAUNCH_MODE: {
		// Default work of program
		ScheduleSystem system;
		system.PopulateFromInput();
		std::string out = system.GetScheduling();
		std::cout << out << std::endl;
		break;
	}
	case DEBUG_MODE: {
	  // Generates an output .txt file at the end
		ScheduleSystem system;
		system.PopulateFromInput();
		std::string out = system.GetScheduling();
		std::ofstream outFile("out.txt");
  	outFile << out;
  	outFile.close();
		break;
	}
	case TEST_MODE: {
		TestClient();
		//TestDistances();
		TestScheduling();
		break;
	}
	default:
		break;
	}
	return 0;
}
