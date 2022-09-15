//
// pch.cpp
//

#include "pch.h"
#include <math.h>

/*
* find_intersect()
* Requires:
* - coordinate: point0, coordinate of the starting point of the line
* - coordinate: point1, coordinate of the ending point of the line
* - circle: circle0, the circle to check for intersects
* Returns:
* - int: number of intersects
*/
int find_intersect(Coordinate point0, Coordinate point1, Circle circle0) {
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