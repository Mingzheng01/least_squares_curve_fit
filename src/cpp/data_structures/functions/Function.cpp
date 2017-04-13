#include <vector>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include "../../../../include/internal/data_structures/functions/Function.hpp"
#include "../../../../include/internal/data_structures/exception/nan_exception.hpp"

Function::Function() {

}

float Function::f(float x) {
	return x;
}

std::vector<Point> Function::f_on_domain_as_xy_points(float a, float b) {
	std::vector<Point> f_of_x;
	
	if (a > b) {
		throw std::invalid_argument("f_on_domain_as_xy_points(): Invalid domain, a must be less than or equal to b");
	}
	
	for (int x = a; x <= b; x++) {
		Point p;
		p.x = x;
		
		try {
			p.y = f(x);
		} catch (const nan_exception& e) {
			std::cerr << "f_on_domain_as_xy_points():\n f(" << p.x << ") evaluated to NaN" << std::endl << std::endl;
		}
		
		f_of_x.push_back(p);
	}
	
	return f_of_x;
}

void Function::display() {
	std::cout << "$f(x)=x$";
}
