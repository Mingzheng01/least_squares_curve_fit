#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>
#include "../../../include/Point.h"
#include "../math/math.cpp"
#include "../math/linear_algebra.cpp"
#include "../data_structures/Exponential_Function.cpp"
#include "../file/file.cpp"

Exponential_Function get_exponential_function(std::vector<Point>& points) {

	float a_numerator = (sum_x_y_lny(points, 0, 0, 1) * sum_x_y_lny(points, 2, 0, 0)) - (sum_x_y_lny(points, 1, 0, 0) * sum_x_y_lny(points, 1, 0, 1));

	float b_numerator = (points.capacity() * sum_x_y_lny(points, 1, 0, 0) * sum_x_y_lny(points, 0, 0, 1)) - (sum_x_y_lny(points, 1, 0, 0) * sum_x_y_lny(points, 0, 0, 1));

	float denominator = (points.capacity() * sum_x_y_lny(points, 2, 0, 0)) - pow(sum_x_y_lny(points, 1, 0, 0), 2);

	float a = a_numerator / denominator;
	float b = b_numerator / denominator;

	std::cerr << a << "/" << b << std::endl;

	Exponential_Function f(a, b);

	return f;

}

Exponential_Function get_exponential_function1(std::vector<Point>& points) {
	


	float a_num_t1 = sum_x_y_lny(points, 2, 1, 0) * sum_x_y_lny(points, 0, 1, 1);
	float a_num_t2 = sum_x_y_lny(points, 1, 1, 0) * sum_x_y_lny(points, 1, 1, 1);
	
	float a_numerator = a_num_t1 - a_num_t2;

	
	float b_num_t1 =  sum_x_y_lny(points, 0, 1, 0) *  sum_x_y_lny(points, 1, 1, 1);
	float b_num_t2 =  sum_x_y_lny(points, 1, 1, 0) *  sum_x_y_lny(points, 0, 1, 1);;
	

	float b_numerator = b_num_t1 - b_num_t2;

	float den_t1 = sum_x_y_lny(points, 0, 1, 0) *  sum_x_y_lny(points, 2, 1, 0);;
	float den_t2 = pow(sum_x_y_lny(points, 1, 1, 0), 2);

	float denominator = den_t1 - den_t2;

	float a = a_numerator / denominator;
	float b = b_numerator / denominator;

	Exponential_Function f(a, b);

	return f;
}


//-------------------------------------------------------------------------------------------------------------------

void fit_exponential_curve_from_to(std::string in_file_name, std::string out_file_name) {
	std::vector<Point> in_points;
	std::vector<Point> out_points;
	std::vector<float> coefs;
	int num_points;

	read_csv(in_points, in_file_name.c_str());

	try {
		Exponential_Function f = get_exponential_function(in_points);

		f.display();

		std::vector<float> min_max;
		min_max = min_and_max_x(in_points);

		// Show f(x) on domain [min_x-10, max_x+10] to see where function is coming from and going to
		out_points = f.f_on_domain_as_xy_points(min_max[0] - in_points.capacity() / 10, min_max[1] + in_points.capacity() / 10);

		write_csv(out_points, out_file_name);

	} catch (const std::invalid_argument& e) {
		std::cerr << e.what() << std::endl << std::endl;
		throw std::invalid_argument("fit_curve():\n Least Squares Matrix failed to be computed because of improper matrix multiplication\n");

	} catch (const nan_exception& e) {
		std::cerr << "fit_curve():\n Output data either has NaN (not a number), " <<
					 "or order of magnitude for desired curve fit is too high" << std::endl << std::endl;
		throw e;

	} catch (...) {
		std::cerr << "fit_curve():\nUnknown error" << std::endl << std::endl;
		std::exception e;
		throw e;
	}

	return;
}

//-------------------------------------------------------------------------------------------------------------------
	
int main(int argc, char* argv[]) {
	std::string in_file_name;
	std::string out_file_name ;

	if (argc == 3) {
		in_file_name = argv[1];
		out_file_name = argv[2];

		try {
		fit_exponential_curve_from_to(in_file_name, out_file_name);

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
