#include "SOLID.hpp"

pointList lst;
std::vector<int> seq;
std::vector<double> coordinates;

polygon1::polygon1(pointList vertices) {}
double polygon1::area() const { return 0.0; }
pointList polygon1::edges() const { return lst; }
double polygon1::randPoint() const { return 0.0; }

polygon2::polygon2(pointList vertices) {}
double polygon2::area() const { return 0.0; }
pointList polygon2::edges() const { return lst; }
double randPoint(const absGeometry& geom) { return 0.0; }

polygon3::polygon3(std::vector<double> x, std::vector<double> y) {}
double polygon3::area() const { return 0.0; }
std::vector<int> polygon3::edges() const { return seq; }

polygon3_3D::polygon3_3D(std::vector<double> x, std::vector<double> y, std::vector<double> z) {}
double polygon3_3D::area() const { return 0.0; }
std::vector<int> polygon3_3D::edges() const { return seq; }

polygon4::polygon4(std::vector<double> x, std::vector<double> y) {}
double polygon4::area() const { return 0.0; }
std::vector<int> polygon4::edges() const { return seq; }

polygon4_3D::polygon4_3D(std::vector<double> x, std::vector<double> y, std::vector<double> z) {}
double polygon4_3D::area() const { return 0.0; }
std::vector<int> polygon4_3D::edges() const { return seq; }


int main() {

	polygon1 p1(lst);
	polygon2 p2(lst);
	polygon3 p3(coordinates, coordinates);
	polygon3_3D p3_3D(coordinates, coordinates, coordinates);
	polygon4 p4(coordinates, coordinates);
	polygon4_3D p4_3D(coordinates, coordinates, coordinates);

	return 0;
}