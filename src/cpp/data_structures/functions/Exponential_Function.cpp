#include "../../../../include/data_structures/functions/Exponential_Function.hpp"
#include <math.h>
#include <cstdio>

/*
Constructs Exponential_Function from coeffients A and B
*/
Exponential_Function::Exponential_Function(float A, float B) {
	this-> A = A;
	this-> B = B;
}

/*
Destructor
*/
Exponential_Function::~Exponential_Function() {
	;
}


float Exponential_Function::f(float x) {
	return A * exp(B * x);
}

void Exponential_Function::display() {
	printf("$f(x)=%.0fe^{%.0fx}$", A, B);
}
