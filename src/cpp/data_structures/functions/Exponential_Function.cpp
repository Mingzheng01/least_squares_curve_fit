#include "../../../../include/internal/data_structures/functions/Exponential_Function.hpp"
#include "../../../../include/internal/util/math/math.hpp"
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

	if (A == 1 && B != 1) {
		printf("$f(x)=e^{%.0fx}$", B);

	} else if (A != 1 && B == 1) {
		printf("$f(x)=%.0fe^{x}$", B);
	} else {
		printf("$f(x)=%.0fe^{%.0fx}$", A, B);
	}
}

/*
* A ≡ e^a
* B ≡ b
*/

Exponential_Function Exponential_Function::least_squares(std::vector<Point>& points) {
	// Compute common denominator for both 'a' and 'b'
	float den_t1 = sum_x_y_lny(points, 0, 1, 0) * sum_x_y_lny(points, 2, 1, 0);;
	float den_t2 = pow(sum_x_y_lny(points, 1, 1, 0), 2);
	float denominator = den_t1 - den_t2;

	// Compute numberator for coefficient 'a'
	float a_num_t1 = sum_x_y_lny(points, 2, 1, 0) * sum_x_y_lny(points, 0, 1, 1);
	float a_num_t2 = sum_x_y_lny(points, 1, 1, 0) * sum_x_y_lny(points, 1, 1, 1);
	float a_numerator = a_num_t1 - a_num_t2;

	// Compute numberator for coefficient 'b'
	float b_num_t1 =  sum_x_y_lny(points, 0, 1, 0) * sum_x_y_lny(points, 1, 1, 1);
	float b_num_t2 =  sum_x_y_lny(points, 1, 1, 0) * sum_x_y_lny(points, 0, 1, 1);;
	float b_numerator = b_num_t1 - b_num_t2;

	// Compute 'a' and 'b'
	float a = a_numerator / denominator;
	float b = b_numerator / denominator;

	// Compute A and B
	float A = exp(a);
	float B = b;

	// TODO - throw error if either A or B is NaN

	// f(x) = A*e^(Bx)
	Exponential_Function f(A, B);

	return f;
}
