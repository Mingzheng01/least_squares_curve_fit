#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>
#include "../../../include/Point.hpp"
#include "../util/math/math.cpp"
#include "../util/math/linear_algebra.cpp"
#include "../data_structures/functions/Logarithmic_Function.cpp"
#include "../data_structures/functions/Function.cpp"
#include "../util/file/file.cpp"

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

int main(int argc, char* argv[]) {
	std::string in_file_name;
	std::string out_file_name ;

	if (argc == 3) {
		in_file_name = argv[1];
		out_file_name = argv[2];

		try {
		
		// Read input points		
		std::vector<Point> in_points;
		read_csv(in_points, in_file_name.c_str());

		// Get function, write output points
		Logarithmic_Function f = get_logarithmic_function(in_points);
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
