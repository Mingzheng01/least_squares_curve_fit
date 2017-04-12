#include <vector>
#include <cstdio>
#include <cmath>
#include "../../../../include/Point.hpp"
#include "../../../../include/Sinusoidal_Function.hpp"
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

void Sinusoidal_Function::display() {
	printf("$f(x)=%.2fsin(%.2fx-%.2f)+%.2f$", A, W, O, B);
}
