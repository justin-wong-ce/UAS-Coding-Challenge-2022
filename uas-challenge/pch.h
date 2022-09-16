//
// pch.h
//

#pragma once

#include "gtest/gtest.h"
#include <vector>

class Coordinate_double {
public:
	double x_coor;
	double y_coor;
	double z_coor;
	Coordinate_double(double x, double y, double z)
		: x_coor(x), y_coor(y), z_coor(z)
	{}

	bool operator == (const Coordinate_double& rhs) const {
			return x_coor == rhs.x_coor &&
				x_coor == rhs.x_coor &&
				z_coor == rhs.z_coor;
	}
};

class Coordinate {
public:
	int x_coor;
	int y_coor;
	int z_coor;
	Coordinate(int x, int y, int z)
		: x_coor(x), y_coor(y), z_coor(z)
	{}

	operator Coordinate_double() {
		return Coordinate_double(x_coor, y_coor, z_coor);
	}

	bool operator == (const Coordinate& rhs) const {
		return x_coor == rhs.x_coor &&
			x_coor == rhs.x_coor &&
			z_coor == rhs.z_coor;
	}
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
* - Coordinate: point0, coordinate of the starting point of the line
* - Coordinate: point1, coordinate of the ending point of the line
* - Circle: circle0, the sphere to check for intersects
* Returns:
* - std::vector<Coordinate_double>: Ordered intersecting points, empty if none. One closer to the starting point will be first
*/
std::vector<Coordinate_double> find_intersect_cylinder(Coordinate_double point0, Coordinate_double point1, Circle circle0);

/*
* find_alt_route_cynlinder()
* Requires:
* - Coordinate: point0, coordinate of the starting point of the line
* - Coordinate: point1, coordinate of the ending point of the line
* - Circle: circle0, the sphere to check for intersects
* - std::vector<Coordinate_double>: intersects, list of sorted intersects with the intersect closer to the start point in front
* Returns:
* - std::vector<Coordinate_double>: intersecting points, empty if none
*/
std::vector<Coordinate_double> find_alt_route_cynlinder(Coordinate_double point0, Coordinate_double point1, Circle circle0, std::vector<Coordinate_double> intersects);

/*
* find_intersect_sphere()
* Requires:
* - Coordinate: point0, coordinate of the starting point of the line
* - Coordinate: point1, coordinate of the ending point of the line
* - Circle: circle0, the sphere to check for intersects
* Returns:
* - int: number of intersects
*/
int find_intersect_sphere(Coordinate point0, Coordinate point1, Circle circle0);

/*
* find_dist_squared()
* Requires:
* - Coordinate_double: point0, marks starting point
* - Coordinate_double: point1, marks end point
* Returns:
* - double: distance squared
*/
double find_dist_squared(Coordinate_double point0, Coordinate_double point1);

/*
 * move_from_circle_xy()
 */
Coordinate_double move_from_circle_xy(Circle circle, Coordinate_double point0, Coordinate_double point1, Coordinate_double coor, int move_by);

/*
 * traverse_on_line()
 */
Coordinate_double traverse_on_line(Coordinate_double point0, Coordinate_double point1, Coordinate_double curr, int move_by);

/*
 * traverse_orthog_line()
 */
Coordinate_double traverse_orthog_xy_line(Coordinate_double point0, Coordinate_double point1, Coordinate_double curr, int move_by);