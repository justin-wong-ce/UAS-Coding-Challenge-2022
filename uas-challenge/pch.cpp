//
// pch.cpp
//

#include "pch.h"
#include <math.h>

/*
* find_intersect_cylinder()
* Requires:
* - coordinate: point0, coordinate of the starting point of the line
* - coordinate: point1, coordinate of the ending point of the line
* - circle: circle0, the cyliner to check for intersects: pre-condition: z-coordinate = 0
* Returns:
* - int: number of intersects
*/
std::vector<Coordinate_double> find_intersect_cylinder(Coordinate point0, Coordinate point1, Circle circle0) {
	/**
	* Algorithm
	* 1. See if line intersects circle in 2D:
	*	Substitute equation of 2D line into equation of circle, then check for real discriminants
	*		discriminant > 0: 2 intersects
	*		discriminant = 0: 1 intersect
	*		discriminant < 0: No intersects
	* 2. If intersect exists, solve full quadratic equation for x, then find y with x
	* 3. Find scalar for the intersect, then use this scalar to find intersecting z-coordinate
	*/
	std::vector<Coordinate_double> intersects = std::vector<Coordinate_double>();

	// Find constants of quadratic equation
	// Equation is already expanded. Check [INSERT DOCUMENTATION LINK HERE] for how this came to be.
	double slope = (point1.y_coor - point0.y_coor) / (double) (point1.x_coor - point0.x_coor);
	double const_a = 1 + pow(slope, 2);
	double const_b = 2 * slope * (point0.y_coor - slope * point0.x_coor) - 2 * circle0.get_coordinate().x_coor - 2 * circle0.get_coordinate().y_coor * slope;
	double const_c = pow(circle0.get_coordinate().x_coor, 2) + pow((point0.y_coor - slope * point0.x_coor), 2) - 2 * circle0.get_coordinate().y_coor * (point0.y_coor - slope * point0.x_coor) + pow(circle0.get_coordinate().y_coor, 2) - pow(circle0.get_radius(), 2);

	// Find discriminants
	float discriminant = pow(const_b, 2) - (4 * const_a * const_c);		// Float to adjust for computer inaccuracies
	if (discriminant < 0) {
		return intersects;
	}
	else if (discriminant == 0) {
		double x_intersect = (0 - const_b) / (2 * const_a);
		double y_intersect = point0.y_coor + slope * (x_intersect - point0.x_coor);

		// Find intersect z-coordinate
		// Check if there is any diff between the 2 y-points first
		double z_intersect;
		if (point1.y_coor - point0.y_coor == 0) {
			z_intersect = point0.z_coor + (point1.z_coor - point0.z_coor) * (x_intersect - point0.x_coor) / (point1.x_coor - point0.x_coor);
		}
		else {
			z_intersect = point0.z_coor + (point1.z_coor - point0.z_coor) * (y_intersect - point0.y_coor) / (point1.y_coor - point0.y_coor);
		}
		intersects.push_back(Coordinate_double(x_intersect, y_intersect, z_intersect));
		return intersects;
	}
	else {
		double x_intersect0 = ((0 - const_b) + sqrt(discriminant)) / (2 * const_a);
		double y_intersect0 = point0.y_coor + slope * (x_intersect0 - point0.x_coor);
		double x_intersect1 = ((0 - const_b) - sqrt(discriminant)) / (2 * const_a);
		double y_intersect1 = point0.y_coor + slope * (x_intersect1 - point0.x_coor);

		// Find intersect z-coordinates
		double z_intersect0, z_intersect1;
		if (point1.y_coor - point0.y_coor == 0) {
			z_intersect0 = point0.z_coor + (point1.z_coor - point0.z_coor) * (x_intersect0 - point0.x_coor) / (point1.x_coor - point0.x_coor);
			z_intersect1 = point0.z_coor + (point1.z_coor - point0.z_coor) * (x_intersect1 - point0.x_coor) / (point1.x_coor - point0.x_coor);
		}
		else {
			z_intersect0 = point0.z_coor + (point1.z_coor - point0.z_coor) * (y_intersect0 - point0.y_coor) / (point1.y_coor - point0.y_coor);
			z_intersect1 = point0.z_coor + (point1.z_coor - point0.z_coor) * (y_intersect1 - point0.y_coor) / (point1.y_coor - point0.y_coor);
		}
		intersects.push_back(Coordinate_double(x_intersect0, y_intersect0, z_intersect0));
		intersects.push_back(Coordinate_double(x_intersect1, y_intersect1, z_intersect1));
		return intersects;
	}
}

/*
* find_intersect_sphere()
* Requires:
* - coordinate: point0, coordinate of the starting point of the line
* - coordinate: point1, coordinate of the ending point of the line
* - circle: circle0, the circle to check for intersects
* Returns:
* - int: number of intersects
*/
int find_intersect_sphere(Coordinate point0, Coordinate point1, Circle circle0) {
	/**
	* Algorithm
	* 1. Find equation of plane perpendicular to line
	* 
	* 2. See if the circle's midpoint is in between the 2 planes
	* - If no: find distance from closer point, and compare against radius
	* 
	* - If yes: Make a triagnle using the 3 points and use trigonmetry to calculate angle of Point0-CircleMidpoint-Point1. Then use sin() to find
	*			shortest length to line
	*			Then compare length against radius
	* 3. If length > radius, intersection = 0
	*	 If length = radius, intersection = 1
	*	 If length < radius, intersection = 2
	*/

	// Find eq. of plane perpendicular to line
	// First find the line's vector
	int vector_x = point1.x_coor - point0.x_coor;
	int vector_y = point1.y_coor - point0.y_coor;
	int vector_z = point1.z_coor - point0.z_coor;

	// Substitute point0 and point1 to find eq of the 2 planes by ax + by + cz = d
	int plane0_constant = point0.x_coor * vector_x + point0.y_coor * vector_y + point0.z_coor * vector_z;
	int plane1_constant = point1.x_coor * vector_x + point1.y_coor * vector_y + point1.z_coor * vector_z;

	// Check if circle's midpoint is in between the 2 planes
	// Check by seeing if substituing circle's mid point would yield the same pos/neg equality for both
	int plane_circle_calc = circle0.get_coordinate().x_coor * vector_x + circle0.get_coordinate().y_coor * vector_y + circle0.get_coordinate().z_coor * vector_z;
	bool in_plane = true;
	if (plane_circle_calc <= plane0_constant && plane_circle_calc <= plane1_constant ||
		plane_circle_calc >= plane0_constant && plane_circle_calc >= plane1_constant) {
		in_plane = false;
	}

	if (in_plane) {
		// Calculate lengths of sides squared
		double len_p0p1_sq = find_dist_squared(point0, point1);
		double len_p0c0_sq = find_dist_squared(point0, circle0.get_coordinate());
		double len_p1c0_sq = find_dist_squared(point1, circle0.get_coordinate());
		// Find angle first
		double len = ((len_p0p1_sq + len_p0c0_sq - len_p1c0_sq) / ((double)2 * sqrt(len_p0p1_sq) * sqrt(len_p0c0_sq)));
		len = acos(len);
		// Find len
		len = sqrt(len_p0c0_sq) * sin(len);

		// Truncate to float to leave room for computer inaccuracies
		if ((float)circle0.get_radius() > (float)len) {
			return 2;
		}
		else if ((float)circle0.get_radius() == (float)len) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		// Calculate distance
		double len = sqrt(find_dist_squared(point0, circle0.get_coordinate()));
		double len_tmp = sqrt(find_dist_squared(point1, circle0.get_coordinate()));
		len = len_tmp < len ? len_tmp : len;	// Use shorter one

		// Truncate to float to leave room for computer inaccuracies
		if ((float)circle0.get_radius() < (float)len) {
			return 0;
		}
		else {
			return 1;
		}
	}
}

/*
* find_dist_squared()
* Requires:
* - coordinate: point0, marks starting point
* - coordinate: point1, marks end point
* Returns:
* - double: distance squared
*/
double find_dist_squared(Coordinate point0, Coordinate point1) {
	return pow((point0.x_coor - point1.x_coor), 2) +
		pow((point0.y_coor - point1.y_coor), 2) +
		pow((point0.z_coor - point1.z_coor), 2);
}