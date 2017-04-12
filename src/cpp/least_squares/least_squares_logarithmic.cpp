#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>
#include "../../../include/Point.hpp"
#include "../../../include/Logarithmic_Function.hpp"
#include "../math/math.cpp"
#include "../math/linear_algebra.cpp"
#include "../data_structures/Logarithmic_Function.cpp"
#include "../file/file.cpp"

//-------------------------------------------------------------------------------------------------------------------

Logarithmic_Function get_logarithmic_function(std::vector<Point>& points) {
	float n = (float) points.capacity();


	float b_numerator = n * sum_y_lnx(points, 1, 1) -  (sum_y_lnx(points, 1, 0) * sum_y_lnx(points, 0, 1));


	float b_denominator = n * sum_y_lnx(points, 0, 2) - pow(sum_y_lnx(points, 0, 1),2);

	float b = b_numerator / b_denominator;

	float a_numerator = sum_y_lnx(points, 1, 0) - (b * sum_y_lnx(points, 0, 1));
		
	float a_denominator = n;

	float a = a_numerator / a_denominator;

	Logarithmic_Function f(a, b);

	return f;
}

void fit_logarithmic_curve_from_to(std::string in_file_name, std::string out_file_name) {
	std::vector<Point> in_points;
	std::vector<Point> out_points;
	std::vector<float> coefs;
	int num_points;

	read_csv(in_points, in_file_name.c_str());

	try {
		Logarithmic_Function f = get_logarithmic_function(in_points);

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
		fit_logarithmic_curve_from_to(in_file_name, out_file_name);

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
