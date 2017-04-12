#include <vector>
#include <cstdio>
#include <cmath>
#include "../../../include/Point.hpp"
#include "../../../include/Sinusoidal_Function.hpp"
#include <math.h>

float A;
float W;
float O;
float B;

/*
Constructs Sinusoidal_Function from coeffients A and B
*/
Sinusoidal_Function::Sinusoidal_Function(float A, float W, float O, float B) {
	this-> A = A;
	this-> W = W;
	this-> O = O;
	this-> B = B;
}

/*
Destructor
*/
Sinusoidal_Function::~Sinusoidal_Function() {
	;
}


float Sinusoidal_Function::f(float x) {
	return A * sin(W*x - O) + B;
}


std::vector<Point> Sinusoidal_Function::f_on_domain_as_xy_points(float a, float b) {
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

void Sinusoidal_Function::display() {
	printf("$f(x)=%.2fsin(%.2fx-%.2f)+%.2f$", A, W, O, B);
}
