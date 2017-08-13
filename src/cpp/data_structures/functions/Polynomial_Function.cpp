#include <math.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include "../../../../include/internal/data_structures/functions/Polynomial_Function.hpp"
#include "../../../../include/internal/data_structures/exception/nan_exception.hpp"
#include "../../../../include/internal/util/math/math.hpp"
#include "../../../../include/internal/util/math/linear_algebra.hpp"

std::vector<float> coefficients;
int coefficients_size;

/*
Constructs Polynomial_Function from vector<float> of coefficients
*/
Polynomial_Function::Polynomial_Function(std::vector<float>& coefs) {
	coefficients_size = coefs.capacity();
	coefficients.reserve(coefficients_size);
	
	for (int i = 0; i < coefficients_size; i++) {
		coefficients[i] = coefs[i];
	}
}

/*
Destructor
*/
Polynomial_Function::~Polynomial_Function() {
	;
}

/*
Evaluates the function f(x) for some x
*/
float Polynomial_Function::f(float x) {
	float y = 0;
	
	for (int i = 0; i < coefficients_size; i++) {
		y += coefficients[i] * pow(x, i);
	}
	
	if (std::isnan(y)) {
		std::cerr << "f():\n f(" << x << ") evaluated to NaN (not a number)." <<
					 " It is possible that" << x << " is not a number or the function has an order of magnitude " <<
					 " that is either too large or too small that causes f(x) to evaluate " <<
					 " to a value that cannot be held in float" << std::endl << std::endl;
		nan_exception nan_except;
		throw nan_except;
	}
	
	return y;
}

void Polynomial_Function::display() {
	printf("$f(x) = ");
	
	for (int i = coefficients_size-1; i >= 0; i--) {
		
		if (coefficients[i] != 0) {
			if (i != coefficients_size-1) {
				if (coefficients[i] > 0) {
					printf("+");
				}
				
				if (coefficients[i] < 0) {
					printf("-");
				}
			}
		
			if (i > 1) {
				printf("%.2fx^%i", std::abs(coefficients[i]), i);
				
			} else if (i == 1) {
				printf("%.2fx", std::abs(coefficients[i]));
				
			} else {
				printf("%.2f", std::abs(coefficients[i]));
			}
		}
	}
	printf("$");
}

/*
Least Squares Curve Fit to nth order polynomial

Theorem: Ax = d  <=>  (A^-1)d = x
Where A is a nxn invertible matrix, and d and x are nx1 column vectors

1. Compute: A

2. Compute: d

3. Compute: A^-1

4. Compute: x = (A^-1)d

5. Return: x
*/
Polynomial_Function Polynomial_Function::least_squares(std::vector<Point>& points, int order) {
		int n = order + 1;
	float sum;
	std::vector< std::vector<float> > A;
	std::vector<float> x;
	std::vector<float> d;
	d.reserve(n);
	
	// 1. Compute: A
	for (int r = 0; r < n; r++) {
		std::vector<float> t;
		
		for (int c = 0, j = r; c < n; c++, j++) {
			
			// Set A[0][0] = # of points
			if (r == 0 && c == 0) {
				t.push_back(points.capacity());
			} else {
				try {
					sum = sum_x_y(points, j, 0);
					t.push_back(sum);
					
				} catch (const nan_exception& e) {
					std::cerr << "n_order_least_squares_fit():\n Sum of x^" << j <<
					"evaluates to NaN. It is possible that the x component of a point" <<
 					" in the original set of data points is not valid, too large or too small for floating point numbers." <<
					" Or, the desired order of magnitude is too large, causing x^" << j <<
					" to evaluate to a number too large to be held as a floating point number" << std::endl << std::endl;
					throw e;
				} catch (...) {
					std::cerr << "n_order_least_squares_fit():\n Unknown error" << std::endl << std::endl;
					std::exception e;
					throw e;
				}
			}
		}
		
		// 2. Compute: d
		d[r] = sum_x_y(points, r, 1);
		A.push_back(t);
	}
	
	// TODO - Compute det(A), throw error if det(A) = 0
		
	// 3. Compute: A^-1
	A = inverse(A);
	
	// 4. Compute: x = (A^-1)d
	try {
		x = mult_matrix_by_vector(A, d);
		
	} catch (const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl;
		throw std::invalid_argument("n_order_least_squares_fit():\n Could not multiply matrix A by column vector d");
		
	} catch (const nan_exception& e) {
		std::cerr << "n_order_least_squares_fit():\n Product of x = (A^-1)d failed to evaluate" <<
				     " because the returned column vector x has a value that" << 
					 " evaluated to NaN (not a number). It is possible that the initial (x,y)" <<
					 " values may be too large or too small for a floating point number, " <<
					 " or the order of magnitude is too high - causing the products of entries in the least " <<
					 " squares matrix A and column vector d to evaluate to numbers too large for floating point numbers"<< std::endl << std::endl;
		throw e;
		
	} catch (...) {
		std::cerr << "n_order_least_squares_fit():\n Unknown error as a result of" <<
					 " multiplying matrix A by column vector d" << std::endl << std::endl;
		std::exception e;
		throw e;
	}

	Polynomial_Function f(x);
	
	// 5. Return: f
	return f;
}








