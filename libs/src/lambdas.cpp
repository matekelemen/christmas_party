#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "partygoer.hpp"

/* -----------------------------------------------------------------------
CHRISTMAS PARTY ++
n random programmers attend a christmas party, at which
there are n pieces of unique snacks. Every programmer has
their own snack preference list and every programmer keeps
track of how many commits they made that year. The partygoers
can choose from the snacks in descending order of their commits.

Who is going to end up with which snack?
----------------------------------------------------------------------- */

int main() {

	// Data
	srand(time(0));
	std::vector<std::string> names		= { "Philipp", "Spencer", "Hamza","Mate" };
	std::vector<int> commits			= { 9001, rand()%20, rand()%20, rand()%20 };
	std::vector<std::string> snacks		= { "Beer","Cake","Tortillas","Leftover bread" };

	// Let there be people
	std::vector<partygoer> people(commits.size());

	for (unsigned int i = 0; i < commits.size(); ++i) {
		// Assign properties
		people[i].name = names[i];
		people[i].commits = commits[i];
		people[i].preferences = snacks;
		// Shuffle preferences
		random_shuffle(people[i].preferences.begin(), people[i].preferences.end() -1);
	}

	print(people);
	/*
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	|
	*/
	/* -----------------------------------------------------------------------
	SOLUTION
	1) Sort people within the vector in descending order by number of their commits
	2) Give the most diligent guy what he/she wants
	3) Remove that element from everyone else's preference list
	4) Next guy ...
	----------------------------------------------------------------------- */

	// Sort by commits
	std::sort(people.begin(), people.end(), [](partygoer person1, partygoer person2) {
		return person1.commits > person2.commits ? true : false;
	});

	// Assign snacks
	std::for_each(people.begin(), people.end(), [&people](partygoer& person) mutable {					// First lambda

		// Get preferred snack
		person.snack_eaten = person.preferences[0];

		// Update preference lists
			std::for_each(people.begin(), people.end(), [person] (partygoer& otherPerson) mutable {		// Third lambda
				
				if (otherPerson.snack_eaten.length() == 0) {
					std::remove(
						otherPerson.preferences.begin(),
						otherPerson.preferences.end(),
						person.snack_eaten);
				}

				return; // Nested lambda
			}); // for_each
		return; // Lambda
	}); // for_each

	print(people);



	return 0;
}














void print(std::vector<partygoer> ppl) {
	for (auto i = ppl.begin(); i != ppl.end(); ++i) {

		std::cout	<< "Name:\t\t" << i->name << "\n"
					<< "Commits:\t" << i->commits << "\n";

		if (i->snack_eaten.length() == 0) {

			std::cout << "Preference list: ";
			for (auto j = i->preferences.begin(); j != i->preferences.end(); ++j) {
				std::cout << *j << ", ";
			}
		}
		else {
			std::cout << "Snack eaten:\t" << i->snack_eaten;
		}
		std::cout << "\n\n";
	}
	std::cout << "\n\n";
	if (ppl[0].snack_eaten.length()==0) std::cout << "\nPress ENTER to find out who ends up with the leftover bread\n\n\n";
	std::cin.get();
}