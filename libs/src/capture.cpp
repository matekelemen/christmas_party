#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <cmath>
#include <string>


void print(std::vector<double>& vec) {
	std::cout << "\n";
	for (auto i = vec.begin(); i != vec.end(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << "\n";
}

void print(std::array<double, 2>& vec) {
	std::cout << "\n";
	for (auto i = vec.begin(); i != vec.end(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << "\n";
}

void print(std::vector<std::array<double, 2>>& vec) {
	std::cout << "\n\n\n";
	for (auto i = vec.begin(); i != vec.end(); ++i) {
		print(*i);
	}
	std::cout << "\n";
}

void print(std::vector<std::string>& vec) {
	std::cout << "\n";
	for (auto i = vec.begin(); i != vec.end(); ++i) {
		std::cout << *i << " ";
	}
	std::cout << "\n";
}





int main() {

	std::vector<std::array<double, 2>> vectors(4);
	vectors = {
	{3,4},
	{5,12},
	{7,24},
	{8, 15}
	};

	/* -----------------------------------------------------------------
	A lambda expression opens up a new scope
	->	By default, non-static variables in the scope of the caller can
	not be accessed.
	If we want to use those variables, we have to pass them to the lambda,
	this is what the square brackets [] are for. (normal brackets like the
	ones this text is in, are used to pass variables from the function
	that called the lambda, eg.: std::for_each)
	----------------------------------------------------------------- */


	// No capture [] ------------------------------------------------------
	std::for_each(vectors.begin(), vectors.end(), [](std::array<double, 2>& vec) {
		// no captures, pass by reference
		std::swap(vec[0], vec[1]);
	});

	print(vectors);










	// Capture by value [var1, var2, ...] ---------------------------------
	double pi = 3.14159265;

	std::for_each(vectors.begin(), vectors.end(), [pi](std::array<double, 2>& vec) {
		// Captured pi by value
		double temp = vec[0];
		vec[0] = cos(pi) * vec[0] + sin(pi) * vec[1];
		vec[1] = -sin(pi) * temp + cos(pi) * vec[1];
	});

	print(vectors);
	











	// Capture by reference [&var1, &var2, ...] ----------------------------
	double lengthSum = 0;

	std::for_each(vectors.begin(), vectors.end(), [&lengthSum](std::array<double, 2> vec) {
		// Captured lengthSum by reference
		lengthSum += hypot(vec[0], vec[1]);
	});

	std::cout << lengthSum << "\n";













	/* -----------------------------------------------------------------
	[]							- no capture						
	[var1, var2, ...]			- capture by value
	[&var1, &var2, ...]			- capture by reference
	[=]							- capture everything by value
	[&]							- capture everything by reference
	[=, &var1, &var2, ...]		- capture everything by value, except 
								  the specified ones, those by reference
	[&, var1, var2, ...]		- capture everything by reference, except
								  the specified ones, those by value
	----------------------------------------------------------------- */













	/* -----------------------------------------------------------------
	MUTABILITY
	By default, if a variable is captured by value, it is a const and
	its value can not be changed within the scope of the lambda.
	Such a variable can only be tinkered with if the mutable keyword is 
	used. 
	[]() mutable {}
	[]() mutable ->return_type {}
	Naturally, a variable which was captured by reference can be 
	modified by default.
	----------------------------------------------------------------- */




















	// Return types
	std::vector<std::string> angles(4);

	std::transform(vectors.begin(), vectors.end(), angles.begin(), [](std::array<double, 2> vec) ->std::string {
		return std::to_string(atan2(vec[1], vec[0]));
	});

	print(angles);

	// Most of the time, the return type is deduced by the compiler
	// In case of multiple returns, you might have to specify it
	// 
	// auto can be used as return type


	return 0;
}