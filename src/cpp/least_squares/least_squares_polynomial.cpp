#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>
#include "../../../include/Point.hpp"
#include "../../../include/Polynomial_Function.hpp"
#include "../util/math/math.cpp"
#include "../util/math/linear_algebra.cpp"
#include "../data_structures/functions/Polynomial_Function.cpp"
#include "../data_structures/functions/Function.cpp"
#include "../util/file/file.cpp"

//-------------------------------------------------------------------------------------------------------------------

/*
Least Squares Curve Fit to nth order

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
	
int main(int argc, char* argv[]) {
	int order = 2;
	std::string in_file_name;
	std::string out_file_name ;

	if (argc == 4) {
		in_file_name = argv[1];
		out_file_name = argv[2];
		order = atoi(argv[3]);

		try {
		
		// Read input points		
		std::vector<Point> in_points;
		read_csv(in_points, in_file_name.c_str());

		// Get function, write output points
		Polynomial_Function f = get_polynomial_function(in_points, order);
		write_curve_to_file(in_file_name, out_file_name, f);

		// Display function to command line
		f.display();

		} catch (const std::invalid_argument& e) {
			std::cerr << e.what() << std::endl;
			std::cerr << "main():\n Curve fit unsuccessful" << std::endl;
			return -1;

		} catch (const nan_exception& e) {
			std::cerr << "main():\n Curve fit unsuccessful" <<
			" because of NaN found in calculations or" <<
			" desired order of magnitude for curve fit is too high" << std::endl;
			return -1;

		} catch (...) {
			std::cerr << "main():\n Curve fit unsuccessful for unknown reason, please debug" << std::endl;
			return -1;
		}
	}

	return 0;
}
