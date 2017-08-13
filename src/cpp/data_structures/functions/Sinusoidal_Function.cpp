#include <math.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include "../../../../include/internal/data_structures/functions/Sinusoidal_Function.hpp"
#include "../../../../include/internal/util/math/math.hpp"
#include "../../../../include/internal/util/math/linear_algebra.hpp"

/*
Constructs Sinusoidal_Function from coeffients A and B
*/
Sinusoidal_Function::Sinusoidal_Function(float A, float W, float O, float B) {
	this-> A = A;
	this-> W = W;
	this-> O = O;
	this-> B = B;
}

//------------------------------------------------------------------------------

/*
Destructor
*/
Sinusoidal_Function::~Sinusoidal_Function() {
	;
}

//------------------------------------------------------------------------------

float Sinusoidal_Function::f(float x) {
	return A * sin(W*x - O) + B;
}

//------------------------------------------------------------------------------

void Sinusoidal_Function::display() {

	if (W >= 0) {

		printf("$f(x)=%.2fsin(%.2fx-%.2f)+%.2f$", A, W, O, B);
	} else {

		printf("$f(x)=%.2fsin(%.2fx%.2f)+%.2f$", A, W, O, B);
	}
}

//------------------------------------------------------------------------------

Sinusoidal_Function Sinusoidal_Function::least_squares(std::vector<Point>& points) {
	std::vector<float> min_max_y_vals = min_and_max_y(points);

	int n = points.capacity();
	float min = min_max_y_vals[0];
	float max = min_max_y_vals[1];

	// Get Amplitude and Vertical-shift
	float A = (max - min) / 2;
	float B = (max + min) / 2;

	// Get terms for matrix
	float t_0 = sum_x_y(points, 2, 0);
	float t_1 = -1 * sum_x_y(points, 1, 0);
	float t_2 = t_1;
	float t_3 = n;

	// Build rows
	std::vector<float> r_0;
	std::vector<float> r_1;
	r_0.push_back(t_0);
	r_0.push_back(t_1);
	r_1.push_back(t_2);
	r_1.push_back(t_3);

	// Put rows into matrix
	std::vector< std::vector<float> > matrix;
	matrix.push_back(r_0);
	matrix.push_back(r_1);

	// Invert the matrix
	matrix = inverse(matrix);

	// Get terms for column vecotr
	float t_4 = sum_x_arcsiny(points, 1, A, B);
	float t_5 = -1 * sum_x_arcsiny(points, 0, A, B);

	// Put terms into column vector
	std::vector<float> col_vector;
	col_vector.push_back(t_4);
	col_vector.push_back(t_5);

	// Multiply the matrix by the vector
	std::vector<float> results = mult_matrix_by_vector(matrix, col_vector);

	//Get results
	float W = results[0];
	float T = results[1];

	std::cerr << "A: " << A << "\nW: " << W << "\nT: " << T << "\nB: " << B << std::endl;

	Sinusoidal_Function f(A, W, T, B);

	return f;
}
