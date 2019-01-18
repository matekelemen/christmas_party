#include <iostream>
#include <array>
#include <vector>
#include <algorithm>

void print(std::vector<int>& vec) {
	std::cout << "\n\n\n";
	for (auto i = vec.begin(); i != vec.end(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << "\n";
}
static int n;
void mod_with_static(int x);
void some_function();







int main() {
	/* ---------------------------------------------------
	FUNCTORS
	--------------------------------------------------- */
	// Classes that overload operator()
	





	// Define a functor
	class mod_n {											// Functor definition
	private:
		int n_;												// Member variable
	public:
		mod_n(int n) : n_(n) {};							// Constructor
		int operator() (int x) const { return x % n_; };	// Overload operator()
	};
	












	// Call a functor
	mod_n functor1(3);										// Initialise functors with
	mod_n functor2(5);										// different values

	for (int i = 0; i < 10; ++i) {
		std::cout << "  "
			<< functor1(i) << "\t" 
			<< functor2(i) << "\n";
	}















	// You don't have to create an instance
	// of a functor to be able to use it
	std::vector<int> v1 = { 1, 4, 9, 16, 25, 36, 49, 64, 81, 100 };
	std::vector<int> v2(v1.size());

	std::transform(v1.begin(), v1.end(), v2.begin(), mod_n(4));
	print(v2);












	// Function instead of functor
	some_function();


	// Return
	return 0;
}




/* ------------------------------------------------------------
BENEFIT OVER FUNCTIONS
To replace functors with functions, we would need a static
variable that can be modified outside the scope of the function
but can be used by it.
------------------------------------------------------------ */
//static int n;										// Declare a static variable
//...
void mod_with_static(int x) {						// Define the function
	std::cout << x % n << " "; 
}	
//...
void some_function() {

	n = 7;											// Give some value to the
													// static variable
	//...
	std::vector<int> vec = { 6, 28, 496 };
	std::for_each(vec.begin(), vec.end(), mod_with_static);

}


/* ------------------------------------------------------------
Passing the parameter to the function doesn't work
------------------------------------------------------------ */
/*
int mod_with_pass(int x, int n) { return x % n; }

void some_other_function() {

	std::vector<int> vec = { 6, 28, 496 };
	// Too few arguments in function call
	std::for_each(vec.begin(), vec.end(), mod_with_pass(4));

	print(vec);
}
*/