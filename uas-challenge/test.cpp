#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>

TEST(Given_2D_Cases, Intersections) {
	// 2 Intersects
	Coordinate p0 = Coordinate(0, -10, 0);
	Coordinate p1 = Coordinate(15, 15, 0);
	Circle c0 = Circle(Coordinate(9, 3, 0), 5);
	int result0 = find_intersect_sphere(p0, p1, c0);
	std::vector<Coordinate_double> result1 = find_intersect_cylinder(p0, p1, c0);
	ASSERT_EQ(result0, 2);
	ASSERT_EQ(result1.size(), 2);

	ASSERT_EQ(round(result1[0].x_coor * 100) / 100, round(10.64 * 100) / 100);
	ASSERT_EQ(round(result1[0].y_coor * 100) / 100, round(7.73 * 100) / 100);
	ASSERT_EQ(round(result1[0].z_coor * 100) / 100, round(0 * 100) / 100);

	ASSERT_EQ(round(result1[1].x_coor * 100) / 100, round(5.6 * 100) / 100);
	ASSERT_EQ(round(result1[1].y_coor * 100) / 100, round(-0.67 * 100) / 100);
	ASSERT_EQ(round(result1[1].z_coor * 100) / 100, round(0 * 100) / 100);

	// 1 Intersect
	p0 = Coordinate(0, 10, 0);
	p1 = Coordinate(30, 10, 0);
	c0 = Circle(Coordinate(12, 0, 0), 10);
	result0 = find_intersect_sphere(p0, p1, c0);
	result1 = find_intersect_cylinder(p0, p1, c0);
	ASSERT_EQ(result0, 1);
	ASSERT_EQ(result1.size(), 1);

	ASSERT_EQ(round(result1[0].x_coor * 100) / 100, round(12 * 100) / 100);
	ASSERT_EQ(round(result1[0].y_coor * 100) / 100, round(10 * 100) / 100);
	ASSERT_EQ(round(result1[0].z_coor * 100) / 100, round(0 * 100) / 100);

	// 0 Intersects
	p0 = Coordinate(0, -10, 0);
	p1 = Coordinate(15, 15, 0);
	c0 = Circle(Coordinate(10, -5, 0), 4);
	result0 = find_intersect_sphere(p0, p1, c0);
	result1 = find_intersect_cylinder(p0, p1, c0);
	ASSERT_EQ(result0, 0);
	ASSERT_EQ(result1.size(), 0);
}

TEST(Two_Intersections, Intersections_Cylinder) {
	Coordinate p0 = Coordinate(0, -10, 0);
	Coordinate p1 = Coordinate(15, 15, 15);
	Circle c0 = Circle(Coordinate(9, 3, 0), 5);
	std::vector<Coordinate_double> result = find_intersect_cylinder(p0, p1, c0);
	ASSERT_EQ(result.size(), 2);

	ASSERT_EQ(round(result[0].x_coor * 100) / 100, round(10.64 * 100) / 100);
	ASSERT_EQ(round(result[0].y_coor * 100) / 100, round(7.73 * 100) / 100);
	ASSERT_EQ(round(result[0].z_coor * 100) / 100, round(10.64 * 100) / 100);

	ASSERT_EQ(round(result[1].x_coor * 100) / 100, round(5.6 * 100) / 100);
	ASSERT_EQ(round(result[1].y_coor * 100) / 100, round(-0.67 * 100) / 100);
	ASSERT_EQ(round(result[1].z_coor * 100) / 100, round(5.6 * 100) / 100);

	p0 = Coordinate(0, -10, 0);
	p1 = Coordinate(3, 20, 8);
	c0 = Circle(Coordinate(2, 8, 0), 7);
	result = find_intersect_cylinder(p0, p1, c0);
	ASSERT_EQ(result.size(), 2);

	ASSERT_EQ(round(result[0].x_coor * 100) / 100, round(2.5 * 100) / 100);
	ASSERT_EQ(round(result[0].y_coor * 100) / 100, round(14.98 * 100) / 100);
	ASSERT_EQ(round(result[0].z_coor * 100) / 100, round(6.66 * 100) / 100);

	ASSERT_EQ(round(result[1].x_coor * 100) / 100, round(1.11 * 100) / 100);
	ASSERT_EQ(round(result[1].y_coor * 100) / 100, round(1.06 * 100) / 100);
	ASSERT_EQ(round(result[1].z_coor * 100) / 100, round(2.95 * 100) / 100);
}

TEST(One_Intersection, Intersections_Cylinder) {
	Coordinate p0 = Coordinate(0, 10, 0);
	Coordinate p1 = Coordinate(30, 10, -8);
	Circle c0 = Circle(Coordinate(12, 0, 0), 10);
	std::vector<Coordinate_double> result = find_intersect_cylinder(p0, p1, c0);
	ASSERT_EQ(result.size(), 1);

	ASSERT_EQ(round(result[0].x_coor * 100) / 100, round(12 * 100) / 100);
	ASSERT_EQ(round(result[0].y_coor * 100) / 100, round(10 * 100) / 100);
	ASSERT_EQ(round(result[0].z_coor * 100) / 100, round(-3.2 * 100) / 100);
}

TEST(No_Intersection, Intersections_Cylinder) {
	Coordinate p0 = Coordinate(0, 10, 0);
	Coordinate p1 = Coordinate(3, -8, 2);
	Circle c0 = Circle(Coordinate(12, 0, 0), 10);
	std::vector<Coordinate_double> result = find_intersect_cylinder(p0, p1, c0);
	ASSERT_EQ(result.size(), 0);

	p0 = Coordinate(4, 87, 0);
	p1 = Coordinate(-9, -8, 2);
	c0 = Circle(Coordinate(10, 0, 0), 7);
	result = find_intersect_cylinder(p0, p1, c0);
	ASSERT_EQ(result.size(), 0);

	p0 = Coordinate(12, 15, -16);
	p1 = Coordinate(-9, -8, 2);
	c0 = Circle(Coordinate(10, 0, 0), 7);
	result = find_intersect_cylinder(p0, p1, c0);
	ASSERT_EQ(result.size(), 0);
}

TEST(Out_Of_Plane, Intersections_Sphere) {
	// 1 Intersect
	Coordinate p0 = Coordinate(-2, -2, 0);
	Coordinate p1 = Coordinate(-5, 0, -5);
	Circle c0 = Circle(Coordinate(0, -2, 0), 3);
	int result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 1);

	p0 = Coordinate(5, 0, 0);
	p1 = Coordinate(0, 0, 0);
	c0 = Circle(Coordinate(-10, 0, 0), 11);
	result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 1);

	// 0 Intersects
	p0 = Coordinate(5, 6, 8);
	p1 = Coordinate(5, 4, 9);
	c0 = Circle(Coordinate(0, 4, 9), 2);
	result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 0);

	p0 = Coordinate(2, 0, 0);
	p1 = Coordinate(3, 4, 5);
	c0 = Circle(Coordinate(-1, -5, -9), 4);
	result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 0);
}

TEST(Touching_Plane, Intersections_Sphere) {
	// 1 Intersect
	Coordinate p0 = Coordinate(-2, 0, 0);
	Coordinate p1 = Coordinate(-5, 0, 0);
	Circle c0 = Circle(Coordinate(-2, 2, 2), 3);
	int result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 1);

	// 0 Intersects
	p0 = Coordinate(2, 0, 0);
	p1 = Coordinate(3, 4, 5);
	c0 = Circle(Coordinate(-1, -5, -9), 4);
	result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 0);
}

TEST(In_Plane, Intersections_Sphere) {
	// 2 Intersects
	Coordinate p0 = Coordinate(5, 0, 0);
	Coordinate p1 = Coordinate(-5, 0, 0);
	Circle c0 = Circle(Coordinate(0, -4, 0), 5);
	int result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 2);

	p0 = Coordinate(5, 0, 0);
	p1 = Coordinate(-5, 0, 0);
	c0 = Circle(Coordinate(0, -1, 0), 2);
	result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 2);

	p0 = Coordinate(5, 0, 0);
	p1 = Coordinate(-5, 0, 0);
	c0 = Circle(Coordinate(0, 0, 0), 2);
	result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 2);

	p0 = Coordinate(5, 5, 5);
	p1 = Coordinate(-5, -4, -6);
	c0 = Circle(Coordinate(0, -1, 0), 6);
	result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 2);

	// 1 Intersect
	p0 = Coordinate(5, 0, 0);
	p1 = Coordinate(-5, 0, 0);
	c0 = Circle(Coordinate(0, -5, 0), 5);
	result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 1);

	p0 = Coordinate(4, 0, 8);
	p1 = Coordinate(-4, 0, 0);
	c0 = Circle(Coordinate(2, 1, 2), 3);
	result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 1);

	// 0 Intersects
	p0 = Coordinate(5, 0, 0);
	p1 = Coordinate(-5, 0, 0);
	c0 = Circle(Coordinate(0, -20, 0), 5);
	result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 0);

	p0 = Coordinate(5, 4, 8);
	p1 = Coordinate(3, 6, 7);
	c0 = Circle(Coordinate(0, -2, 0), 5);
	result = find_intersect_sphere(p0, p1, c0);

	ASSERT_EQ(result, 0);
}

TEST(Profiling_10000_Calls_Cylinder, Intersections_Cylinder) {
	Coordinate* coors[30000];
	int rads[10000];
	int GRID_MAX = 1000;
	for (int i = 0; i < 30000; i++) {
		if (i < 10000) {
			rads[i] = rand() % (GRID_MAX / 20);
		}
		coors[i] = new Coordinate(rand() % GRID_MAX, rand() % GRID_MAX, rand() % GRID_MAX);
	}

	std::clock_t start, end;
	start = std::clock();
	for (int i = 0; i < 10000; i++) {
		find_intersect_cylinder(*coors[i], *coors[i + 10000], Circle(*coors[i + 20000], rads[i]));
	}
	end = std::clock();
	std::cerr << "PROFILING: Time taken = " << (end - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
}

TEST(Profiling_20000_Calls_Sphere, Intersections_Sphere) {
	Coordinate* coors[60000];
	int rads[20000];
	int GRID_MAX = 1000;
	for (int i = 0; i < 60000; i++) {
		if (i < 20000) {
			rads[i] = rand() % (GRID_MAX / 20);
		}
		coors[i] = new Coordinate(rand() % GRID_MAX, rand() % GRID_MAX, rand() % GRID_MAX);
	}

	std::clock_t start, end;
	start = std::clock();
	for (int i = 0; i < 20000; i++) {
		find_intersect_sphere(*coors[i], *coors[i + 20000], Circle(*coors[i + 40000], rads[i]));
	}
	end = std::clock();
	std::cerr << "PROFILING: Time taken = " << (end - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
}