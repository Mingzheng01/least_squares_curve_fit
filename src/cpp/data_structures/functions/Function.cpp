#include <vector>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include "../../../../include/internal/data_structures/functions/Function.hpp"
#include "../../../../include/internal/data_structures/exception/nan_exception.hpp"

// TODO - Implement to_string();

Function::Function() {

	// Place holder function
}

float Function::f(float x) {
	return x;
}

std::vector<Point> Function::f_on_domain_as_xy_points(std::vector<Point>& points) {
	std::vector<Point> f_of_x;
	int n = points.capacity();	
	
	for (int i = 0; i < n; i++) {
		Point p;
		p.x = points[i].x;
		
		try {
			p.y = f(p.x);
		} catch (const nan_exception& e) {
			std::cerr << "f_on_domain_as_xy_points():\n f(" << p.x << ") evaluated to NaN" << std::endl << std::endl;
		}
		
		f_of_x.push_back(p);
	}
	
	return f_of_x;
}

void Function::display() {
	std::cout << "$undefined$";
}
