#include <vector>
#include <cstdio>
#include <cmath>
#include "../../../include/Point.hpp"
#include "../../../include/Logarithmic_Function.hpp"
#include <math.h>


float a;
float b;

/*
Constructs Logarithmic_Function from coeffients A and B
*/
Logarithmic_Function::Logarithmic_Function(float a, float b) {
	this-> a = a;
	this-> b = b;
}

/*
Destructor
*/
Logarithmic_Function::~Logarithmic_Function() {
	;
}


float Logarithmic_Function::f(float x) {
	return a + b * log(x);
}


std::vector<Point> Logarithmic_Function::f_on_domain_as_xy_points(float a, float b) {
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

void Logarithmic_Function::display() {
	printf("$f(x)=%.0f+%.0fln(x)$", a, b);
}
