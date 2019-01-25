#include <iostream>
#include <cmath>
const double pi = 3.141592653589793238462643383279502884;

/* -----------------------------------------------------------
BASIC EXAMPLE FOR POLICY BASED DESIGN, TO ACCOMPANY THE THEORY
----------------------------------------------------------- */



// Derived classes are the hosts
// Host class: sets the requirements for policies and combines them
template <class policy_geometry, class policy_material>
class physicsBody : private policy_geometry, private policy_material {

public:
	physicsBody(double characteristicLength) : policy_geometry(characteristicLength) {}
	double mass() {
		return policy_geometry::volume() * policy_material::density();
	}

};


// Base classes represent policies
// Policy: implements the requirements of the host class
// Geometry policies --------------------------------------------------


class sphere {
private:
	double radius_;
public:
	sphere(double radius) : radius_(radius) {}
	double volume() { return 4 / 3 * radius_*radius_*radius_*pi; }
};


class cube {
private:
	double edge_;
public:
	cube(double edge) : edge_(edge) {}
	double volume() { return edge_ * edge_ * edge_; }
};


// Material policies --------------------------------------------------


class aluminum {
private:
	double density_;
public:
	aluminum() : density_(2700) {}
	double density() { return density_; }
};


class plastic {
private:
	double density_;
protected:
	plastic() : density_(1700) {}
	double density() { return density_; }
};










// Main ---------------------------------------------------------------
int main() {
	// Create an instance of the host object
	physicsBody<cube, aluminum> body1(1);
	std::cout << body1.mass() << std::endl;



	// Create a type of body
	typedef physicsBody<sphere, plastic> billiardBall;
	// Create an instance of a type of body
	billiardBall body2(0.03);
	std::cout << body2.mass() << std::endl;


	return 0;
}