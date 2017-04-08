#include <exception>
#include "../../../include/Point.h"
#include "math.cpp"
#include "linear_algebra.cpp"

/*
* http://mathworld.wolfram.com/LeastSquaresFittingLogarithmic.html
*/
std::vector<float> logarithmic_least_squares_fit(std::vector<Point>&points) {
	float b;
	float a;
	int n;		// number of points

	// Compute B
		// Compute Numerator

		// Compute Denominator

		// Divide

	// Compute A


	// Put A in position 0, put B in position 1

	// Return vector
}


/*
Least Squares Curve Fit to nth order

Theorem: Ax = d  <=>  (A^-1)d = x
Where A is a nxn matrix, and d and x are nx1 column vectors

1. Compute: A

2. Compute: d

3. Compute: A^-1

4. Compute: x = (A^-1)d

5. Return: x
*/
std::vector<float> n_order_least_squares_fit(std::vector<Point>& points, int order) {
		
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
	
	// 5. Return: x 
	return x;
}
