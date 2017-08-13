#include "../../../../include/internal/data_structures/functions/Logarithmic_Function.hpp"
#include "../../../../include/internal/util/math/math.hpp"
#include <math.h>
#include <cstdio>

/*
Constructs Logarithmic_Function from coeffients A and B
*/
Logarithmic_Function::Logarithmic_Function(float a, float b) {
	this-> a = a;
	this-> b = b;
}

//------------------------------------------------------------------------------

/*
Destructor
*/
Logarithmic_Function::~Logarithmic_Function() {
	;
}

//------------------------------------------------------------------------------


float Logarithmic_Function::f(float x) {
	return a + b * log(x);
}

//------------------------------------------------------------------------------

void Logarithmic_Function::display() {

	if (a >= 0) {
		printf("$f(x)=%.1fln(x)+%.1f$", b, a);
	} else {
		printf("$f(x)=%.1fln(x)-%.1f$", b, a);
	}
}

//------------------------------------------------------------------------------

Logarithmic_Function Logarithmic_Function::least_squares(std::vector<Point>& points) {
	float n = (float) points.capacity();

	float b_numerator = n * sum_y_lnx(points, 1, 1) -  (sum_y_lnx(points, 1, 0) * sum_y_lnx(points, 0, 1));

	float b_denominator = n * sum_y_lnx(points, 0, 2) - pow(sum_y_lnx(points, 0, 1),2);

	float b = b_numerator / b_denominator;

	float a_numerator = sum_y_lnx(points, 1, 0) - (b * sum_y_lnx(points, 0, 1));

	float a_denominator = n;

	float a = a_numerator / a_denominator;

	// TODO - throw error if either A or B is NaN

	Logarithmic_Function f(a, b);

	return f;
}
