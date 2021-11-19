#include <iostream>

#include <vector>
#include <string>
#include "ScheduleSystem.h"

void TEST(int expected, int actual, std::string testName){
	if (expected == actual) {
		std::cout << testName << "\t\tPASSED!" << std::endl;
	} else {
		std::cout << testName << " FAILED!!!" << std::endl;
		std::cout << "Expected " << expected << " but was " << actual << std::endl;
	}
}

void TestClient() {
	Client c(0, 20, std::string("MG"), std::string("DINHEIRO"), Vector2(7, 4));
	TEST(40, c.getTicketValue(), "Default Ticket Score");
	c = Client(0, 20, std::string("ss"), std::string("DINHEIRO"), Vector2(7, 4));
	TEST(-1, c.getTicketValue(), "Invalid Ticket Score 01");
	c = Client(0, 20, std::string("MG"), std::string("DINHEIR"), Vector2(7, 4));
	TEST(-1, c.getTicketValue(), "Invalid Ticket Score 01");
	c = Client(0, -40, std::string("MG"), std::string("DINHEIR"), Vector2(7, 4));
	TEST(-1, c.getTicketValue(), "Invalid Ticket Score 01");
}

int main()
{
	TestClient();

	ScheduleSystem system;

	system.Populate();

  return 0;
}
