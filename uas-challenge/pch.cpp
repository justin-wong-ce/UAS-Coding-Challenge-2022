//
// pch.cpp
//

#include "pch.h"
#include <math.h>

/*
* find_intersect_cylinder()
* Requires:
* - Coordinate: point0, coordinate of the starting point of the line
* - Coordinate: point1, coordinate of the ending point of the line
* - Circle: circle0, the sphere to check for intersects
* Returns:
* - std::vector<Coordinate_double>: Ordered intersecting points, empty if none. One closer to the starting point will be first
*/
std::vector<Coordinate_double> find_intersect_cylinder(Coordinate_double point0, Coordinate_double point1, Circle circle0) {
	/*
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
	double points_dist = find_dist_squared(point0, point1);

	// Find discriminants
	float discriminant = pow(const_b, 2) - (4 * const_a * const_c);		// Float to adjust for computer inaccuracies
	if (discriminant < 0) {
		return intersects;
	}
	else if (discriminant == 0) {
		double x_intersect = (0 - const_b) / (2 * const_a);
		double y_intersect = point0.y_coor + slope * (x_intersect - point0.x_coor);

		// Find intersecting z-coordinate
		// Check if there is any diff between the 2 y-points first
		double z_intersect;
		if (point1.y_coor - point0.y_coor == 0) {
			z_intersect = point0.z_coor + (point1.z_coor - point0.z_coor) * (x_intersect - point0.x_coor) / (point1.x_coor - point0.x_coor);
		}
		else {
			z_intersect = point0.z_coor + (point1.z_coor - point0.z_coor) * (y_intersect - point0.y_coor) / (point1.y_coor - point0.y_coor);
		}
		Coordinate_double intersect = Coordinate_double(x_intersect, y_intersect, z_intersect);

		// Check if intersect is within line
		if (find_dist_squared(intersect, point0) < points_dist && find_dist_squared(intersect, point1) < points_dist) {
			intersects.push_back(Coordinate_double(x_intersect, y_intersect, z_intersect));
		}
		return intersects;
	}
	else {
		double x_intersect0 = ((0 - const_b) + sqrt(discriminant)) / (2 * const_a);
		double y_intersect0 = point0.y_coor + slope * (x_intersect0 - point0.x_coor);
		double x_intersect1 = ((0 - const_b) - sqrt(discriminant)) / (2 * const_a);
		double y_intersect1 = point0.y_coor + slope * (x_intersect1 - point0.x_coor);

		// Find intersecting z-coordinates
		double z_intersect0, z_intersect1;
		if (point1.y_coor - point0.y_coor == 0) {
			z_intersect0 = point0.z_coor + (point1.z_coor - point0.z_coor) * (x_intersect0 - point0.x_coor) / (point1.x_coor - point0.x_coor);
			z_intersect1 = point0.z_coor + (point1.z_coor - point0.z_coor) * (x_intersect1 - point0.x_coor) / (point1.x_coor - point0.x_coor);
		}
		else {
			z_intersect0 = point0.z_coor + (point1.z_coor - point0.z_coor) * (y_intersect0 - point0.y_coor) / (point1.y_coor - point0.y_coor);
			z_intersect1 = point0.z_coor + (point1.z_coor - point0.z_coor) * (y_intersect1 - point0.y_coor) / (point1.y_coor - point0.y_coor);
		}
		Coordinate_double intersect0 = Coordinate_double(x_intersect0, y_intersect0, z_intersect0);
		Coordinate_double intersect1 = Coordinate_double(x_intersect1, y_intersect1, z_intersect1);

		// Find intersect closer to start point
		bool intersect0_closer = find_dist_squared(intersect0, point0) < find_dist_squared(intersect1, point0);
		// Check if intersect is within line
		if (find_dist_squared(intersect0, point0) < points_dist && find_dist_squared(intersect0, point1) < points_dist) {
			intersects.push_back(intersect0);
		}
		if (find_dist_squared(intersect1, point0) < points_dist && find_dist_squared(intersect1, point1) < points_dist) {
			if (intersect0_closer) {
				intersects.push_back(intersect1);
			}
			else {
				intersects.insert(intersects.begin(), intersect1);
			}
		}
		return intersects;
	}
}

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
std::vector<Coordinate_double> find_alt_route_cynlinder(Coordinate_double point0, Coordinate_double point1, Circle circle0, std::vector<Coordinate_double> intersects){
	/*
	 * Algorithm:
	 * 	1. Move 1 unit away from direction of center of circle from intersect closer to start point
	 * 	2. Find intersect from above point to end and repeat 1) for new intersect
	 * 	3. If new intersect same as old intersect, shift new intersect 1 unit perpendicular to the vector<circle_midpoint - intersect>
	 * 	4. Save starting point and moved-away intersects to result array
	 * 	5. Repeat 1, 2, 4 wtihout saving starting point
	 */
	std::vector<Coordinate_double> ret_path = std::vector<Coordinate_double>();
	ret_path.push_back(point0);
	if (intersects.size() == 0) {
		ret_path.push_back(point1);
		return ret_path;
	}
	Coordinate_double moved_away_init = move_from_circle_xy(circle0, (Coordinate_double) point0, (Coordinate_double) point1, intersects[0], ceil(circle0.get_radius() / 10.0));
	std::vector<Coordinate_double> intersect_tmp = find_intersect_cylinder(moved_away_init, point1, circle0);

	// Check if we still have intersect
	if (intersect_tmp.size() == 0) {
		ret_path.push_back(moved_away_init);
		ret_path.push_back(point1);
		return ret_path;
	}
	
	// Check if same as given intersects
	if (intersect_tmp[0] == intersects[0]) {
		moved_away_init = traverse_orthog_xy_line(point0, point1, moved_away_init, ceil(circle0.get_radius() / 10.0));
		intersect_tmp = find_intersect_cylinder(moved_away_init, point1, circle0);
	}
	ret_path.push_back(moved_away_init);

	do {
		intersect_tmp[0] = move_from_circle_xy(circle0, (Coordinate_double) point0, (Coordinate_double) point1, intersect_tmp[0], ceil(circle0.get_radius() / 10.0));
		ret_path.push_back(intersect_tmp[0]);
		intersect_tmp = find_intersect_cylinder(intersect_tmp[0], point1, circle0);
	} while (intersect_tmp.size() != 0);

	ret_path.push_back(point1);
	return ret_path;
}

/*
* find_intersect_sphere()
* Requires:
* - Coordinate: point0, coordinate of the starting point of the line
* - Coordinate: point1, coordinate of the ending point of the line
* - Circle: circle0, the circle to check for intersects
* Returns:
* - int: number of intersects
*/
int find_intersect_sphere(Coordinate point0, Coordinate point1, Circle circle0) {
	/*
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
* - Coordinate_double: point0, marks starting point
* - Coordinate_double: point1, marks end point
* Returns:
* - double: distance squared
*/
double find_dist_squared(Coordinate_double point0, Coordinate_double point1) {
	return pow((point0.x_coor - point1.x_coor), 2) +
		pow((point0.y_coor - point1.y_coor), 2) +
		pow((point0.z_coor - point1.z_coor), 2);
}

/*
 * move_from_circle_xy()
 */
Coordinate_double move_from_circle_xy(Circle circle, Coordinate_double point0, Coordinate_double point1, Coordinate_double coor, int move_by) {
	double diff_coor_x = coor.x_coor - circle.get_coordinate().x_coor;
	double diff_coor_y = coor.y_coor - circle.get_coordinate().y_coor;
	Coordinate_double pre_z_adjust = traverse_on_line(Coordinate_double(circle.get_coordinate().x_coor, circle.get_coordinate().y_coor, 0), Coordinate_double(coor.x_coor, coor.y_coor, 0), coor, move_by);
	return Coordinate_double(pre_z_adjust.x_coor, pre_z_adjust.y_coor, traverse_on_line(point0, point1, pre_z_adjust, move_by * -1).z_coor);
}

/*
 * traverse_on_line()
 */
Coordinate_double traverse_on_line(Coordinate_double point0, Coordinate_double point1, Coordinate_double curr, int move_by) {
	double diff_coor_x = point1.x_coor - point0.x_coor;
	double diff_coor_y = point1.y_coor - point0.y_coor;
	double diff_coor_z = point1.z_coor - point0.z_coor;
	double magnitude = sqrt(find_dist_squared(Coordinate_double(diff_coor_x, diff_coor_y, diff_coor_z), Coordinate(0, 0, 0)));

	return Coordinate_double(curr.x_coor + diff_coor_x * move_by / magnitude, curr.y_coor + diff_coor_y * move_by / magnitude, curr.z_coor + diff_coor_z * move_by / magnitude);
}

/*
 * traverse_orthog_line()
 */
Coordinate_double traverse_orthog_xy_line(Coordinate_double point0, Coordinate_double point1, Coordinate_double curr, int move_by) {
	double diff_coor_x = point1.x_coor - point0.x_coor;
	double diff_coor_y = point1.y_coor - point0.y_coor;
	double magnitude = sqrt(find_dist_squared(Coordinate_double(diff_coor_x, diff_coor_y, 0), Coordinate(0, 0, 0)));

	return Coordinate_double(curr.y_coor + diff_coor_y * move_by / magnitude, 0 - (curr.x_coor + diff_coor_x * move_by / magnitude), curr.z_coor);
}