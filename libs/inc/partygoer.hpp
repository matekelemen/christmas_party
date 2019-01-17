#include <vector>
#include <string>

struct partygoer {
	std::string name;
	int commits;
	std::vector<std::string> preferences;
	std::string snack_eaten;
};



void print(std::vector<partygoer> ppl);
