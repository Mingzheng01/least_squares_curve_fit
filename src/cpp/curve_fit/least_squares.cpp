
// C / C++ language dependencies
#include <vector>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <stdexcept>
#include "../../../include/data_structures/exception/nan_exception.hpp"
#include "../../../include/data_structures/functions/Exponential_Function.hpp"
#include "../../../include/data_structures/functions/Logarithmic_Function.hpp"
#include "../../../include/data_structures/functions/Polynomial_Function.hpp"
#include "../../../include/data_structures/functions/Sinusoidal_Function.hpp"
#include "../../../include/data_structures/functions/Point.hpp"
#include "../../../include/util/math/linear_algebra.hpp"
#include "../../../include/util/math/math.hpp"


/*

// To compile and link correctly with g++ / c++ compiler


c++ -o ../../../bin/curve_fit curve_fit.cpp ../data_structures/functions/Exponential_Function.cpp ../data_structures/functions/Logarithmic_Function.cpp ../data_structures/functions/Polynomial_Function.cpp ../data_structures/functions/Sinusoidal_Function.cpp ../data_structures/functions/Function.cpp


*/


/*
* A ≡ e^a
* B ≡ b
*/
Exponential_Function get_exponential_function(std::vector<Point>& points) {

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


//-------------------------------------------------------------------------------------------------------------------


Logarithmic_Function get_logarithmic_function(std::vector<Point>& points) {
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

//-------------------------------------------------------------------------------------------------------------------

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
Polynomial_Function get_polynomial_function(std::vector<Point>& points, int order) {
		
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

//-------------------------------------------------------------------------------------------------------------------

Sinusoidal_Function get_sinusoidal_function(std::vector<Point>& points) {
	std::vector<float> min_max_y_vals = min_and_max_y(points);

	float min = min_max_y_vals[0];
	float max = min_max_y_vals[1];

	float A = (max - min) / 2;
	float B = (max + min) / 2;

	int n = points.capacity();

	Point start = points[0];
	Point finish;

	// Find the next time the first value repeats
	for (int i = 1; i < n; i++) {
		if (points[i].y == start.y) {
			finish = points[i];
			break;
		}
	}

	// TODO - Error handling if value does no repeat

	// Find distance between the repeatinting y value
	float period = finish.x - start.x;

	// Multiply it by 2 so it reflects a ful period
	period = abs(period * 2);

	float W = (2 * M_PI) / period;


	int period_int = (int) period;

	// Locate first min

	int min_index;
	for (int i = 0; i < period_int-1; i++) {
		if (points[i].y == min) {
			min_index = i;
			break;
		}
	}
	
	int max_index;
	for (int i = min_index; i < period_int-1; i++) {
		if (points[i].y > points[i+1].y) {
			max_index = i;
		}

		if (points[i].y < points[i+1].y) {
			break;
		}
	}	

	// It shoud take half a period to get from min to max
	float expected_distance = abs(points[min_index].x + (period_int / 2));
	float actual_distance = abs(points[max_index].x - points[min_index].x);

	std::cerr << "expected distance: " << expected_distance << std::endl;
	std::cerr << "true distance: " << actual_distance << std::endl;

	float O = abs(actual_distance - expected_distance);

	std::cerr << "O: " << O << std::endl;

	Sinusoidal_Function f(A, W, O, B);

	return f;
}

