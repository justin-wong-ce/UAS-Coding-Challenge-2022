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
	int result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 2);

	// 1 Intersect
	p0 = Coordinate(0, 10, 0);
	p1 = Coordinate(30, 10, 0);
	c0 = Circle(Coordinate(12, 0, 0), 10);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 1);

	// 0 Intersects
	p0 = Coordinate(0, -10, 0);
	p1 = Coordinate(15, 15, 0);
	c0 = Circle(Coordinate(10, -5, 0), 4);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 0);
}

TEST(Out_Of_Plane, Intersections) {
	// 1 Intersect
	Coordinate p0 = Coordinate(-2, -2, 0);
	Coordinate p1 = Coordinate(-5, 0, -5);
	Circle c0 = Circle(Coordinate(0, -2, 0), 3);
	int result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 1);

	p0 = Coordinate(5, 0, 0);
	p1 = Coordinate(0, 0, 0);
	c0 = Circle(Coordinate(-10, 0, 0), 11);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 1);

	// 0 Intersects
	p0 = Coordinate(5, 6, 8);
	p1 = Coordinate(5, 4, 9);
	c0 = Circle(Coordinate(0, 4, 9), 2);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 0);

	p0 = Coordinate(2, 0, 0);
	p1 = Coordinate(3, 4, 5);
	c0 = Circle(Coordinate(-1, -5, -9), 4);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 0);
}

TEST(Touching_Plane, Intersections) {
	// 1 Intersect
	Coordinate p0 = Coordinate(-2, 0, 0);
	Coordinate p1 = Coordinate(-5, 0, 0);
	Circle c0 = Circle(Coordinate(-2, 2, 2), 3);
	int result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 1);

	// 0 Intersects
	p0 = Coordinate(2, 0, 0);
	p1 = Coordinate(3, 4, 5);
	c0 = Circle(Coordinate(-1, -5, -9), 4);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 0);
}

TEST(In_Plane, Intersections) {
	// 2 Intersects
	Coordinate p0 = Coordinate(5, 0, 0);
	Coordinate p1 = Coordinate(-5, 0, 0);
	Circle c0 = Circle(Coordinate(0, -4, 0), 5);
	int result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 2);

	p0 = Coordinate(5, 0, 0);
	p1 = Coordinate(-5, 0, 0);
	c0 = Circle(Coordinate(0, -1, 0), 2);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 2);

	p0 = Coordinate(5, 0, 0);
	p1 = Coordinate(-5, 0, 0);
	c0 = Circle(Coordinate(0, 0, 0), 2);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 2);

	p0 = Coordinate(5, 5, 5);
	p1 = Coordinate(-5, -4, -6);
	c0 = Circle(Coordinate(0, -1, 0), 6);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 2);

	// 1 Intersect
	p0 = Coordinate(5, 0, 0);
	p1 = Coordinate(-5, 0, 0);
	c0 = Circle(Coordinate(0, -5, 0), 5);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 1);

	p0 = Coordinate(4, 0, 8);
	p1 = Coordinate(-4, 0, 0);
	c0 = Circle(Coordinate(2, 1, 2), 3);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 1);

	// 0 Intersects
	p0 = Coordinate(5, 0, 0);
	p1 = Coordinate(-5, 0, 0);
	c0 = Circle(Coordinate(0, -20, 0), 5);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 0);

	p0 = Coordinate(5, 4, 8);
	p1 = Coordinate(3, 6, 7);
	c0 = Circle(Coordinate(0, -2, 0), 5);
	result = find_intersect(p0, p1, c0);

	ASSERT_EQ(result, 0);
}

// Fails, to check time taken
TEST(Profiling_20000_Calls, Intersections) {
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
		find_intersect(*coors[i], *coors[i + 20000], Circle(*coors[i + 40000], rads[i]));
	}
	end = std::clock();
	std::cerr << "PROFILING: Time taken = " << (end - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
}