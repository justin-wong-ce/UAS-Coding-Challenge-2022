//
// pch.h
//

#pragma once

#include "gtest/gtest.h"
#include <vector>

class Coordinate {
public:
	int x_coor;
	int y_coor;
	int z_coor;
	Coordinate(int x, int y, int z)
		: x_coor(x), y_coor(y), z_coor(z)
	{}
};

class Coordinate_double {
public:
	double x_coor;
	double y_coor;
	double z_coor;
	Coordinate_double(double x, double y, double z)
		: x_coor(x), y_coor(y), z_coor(z)
	{}
};

class Circle {
private:
	Coordinate coor;
	int radius;

public:
	Circle(Coordinate coor, int radius)
	: coor(coor), radius(radius)
	{}
	Coordinate get_coordinate() {
		return coor;
	}
	int get_radius() {
		return radius;
	}
};

/*
* find_intersect_cylinder()
* Requires:
* - coordinate: point0, coordinate of the starting point of the line
* - coordinate: point1, coordinate of the ending point of the line
* - circle: circle0, the sphere to check for intersects
* Returns:
* - int: number of intersects
*/
std::vector<Coordinate_double> find_intersect_cylinder(Coordinate point0, Coordinate point1, Circle circle0);

/*
* find_intersect_sphere()
* Requires:
* - coordinate: point0, coordinate of the starting point of the line
* - coordinate: point1, coordinate of the ending point of the line
* - circle: circle0, the sphere to check for intersects
* Returns:
* - int: number of intersects
*/
int find_intersect_sphere(Coordinate point0, Coordinate point1, Circle circle0);

/*
* find_dist_squared()
* Requires:
* - coordinate: point0, marks starting point
* - coordinate: point1, marks end point
* Returns:
* - double: distance squared
*/
double find_dist_squared(Coordinate point0, Coordinate point1);