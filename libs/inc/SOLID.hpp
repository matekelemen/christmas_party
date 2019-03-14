#ifndef SOLID
#define SOLID

#include <vector>
#include <array>

/* SOLID ---------------------------------------------
- Single Responsibility
- Open/Closed Principle
- Liskov Substitution
- Interface-Segregation
- Dependency Inversion
--------------------------------------------------- */

// Just to make life easier --------------------------
using pointList = std::vector<std::array<double, 2>>;
///////////////////////////////////////////////////////


// Base class ----------------------------------------
class absGeometry {
public:
	virtual double area() const = 0;
};
///////////////////////////////////////////////////////






// Single Responsibility (bad example) ---------------
// task: pick a random point in a polygon
class polygon1 : public absGeometry{

private:
	pointList vertices_;

public:
	polygon1(pointList vertices);
	double area() const;
	pointList edges() const;
	double randPoint() const;
};
///////////////////////////////////////////////////////







// Single Responsibility (better example) ------------
class polygon2 : public absGeometry {

private:
	pointList vertices_;

public:
	polygon2(pointList vertices);
	double area() const;
	pointList edges() const;
};

double randPoint(const absGeometry& geom);
///////////////////////////////////////////////////////






// Open/Closed Principle (Better example) ------------
class polygon3 : public absGeometry {

protected:
	std::vector<double> x_;
	std::vector<double> y_;

public:
	polygon3() {}
	polygon3(std::vector<double> x, std::vector<double> y);
	double area() const;
	std::vector<int> edges() const;
};


// polygon3_3D expands polygon3
class polygon3_3D : private polygon3 {

protected:
	std::vector<double> z_;

public:
	polygon3_3D(std::vector<double> x, std::vector<double> y, std::vector<double> z);
	double area() const;
	std::vector<int> edges() const;
};


//double randPoint(const absGeometry& geom);
///////////////////////////////////////////////////////









// Liskov Substitution --------------------------------
/*
class absGeometry {
public:
	virtual double area() const = 0;
};
*/

class absPolygon : public absGeometry {
protected:
	std::vector<double> x_;
	std::vector<double> y_;
public:
	virtual double area() const = 0;
	virtual std::vector<int> edges() const = 0;
};

class polygon4 : private absPolygon {
public:
	polygon4(std::vector<double> x, std::vector<double> y);
	double area() const;
	std::vector<int> edges() const;
};

class polygon4_3D : private absPolygon {
protected:
	std::vector<double> z_;
public:
	polygon4_3D(std::vector<double> x, std::vector<double> y, std::vector<double> z);
	double area() const;
	std::vector<int> edges() const;
};


//double randPoint(const absGeometry& geom);
///////////////////////////////////////////////////////






// Interface Segregation ------------------------------




#endif