#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>
#include "../../../include/Point.hpp"
#include "../util/math/math.cpp"
#include "../util/math/linear_algebra.cpp"
#include "../data_structures/functions/Exponential_Function.cpp"
#include "../data_structures/functions/Function.cpp"
#include "../util/file/file.cpp"

Exponential_Function get_exponential_function(std::vector<Point>& points) {

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

	a = exp(a);

	Exponential_Function f(a, b);

	return f;
}


//-------------------------------------------------------------------------------------------------------------------
	
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
		Exponential_Function f = get_exponential_function(in_points);
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
