#include "../../../../include/data_structures/functions/Logarithmic_Function.hpp"
#include <math.h>
#include <cstdio>

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

void Logarithmic_Function::display() {
	printf("$f(x)=%.0f+%.0fln(x)$", a, b);
}
