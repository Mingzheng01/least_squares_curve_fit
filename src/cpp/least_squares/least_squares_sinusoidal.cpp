#define _USE_MATH_DEFINES
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>
#include "../../../include/Point.hpp"
#include "../../../include/Sinusoidal_Function.hpp"
#include "../math/math.cpp"
#include "../math/linear_algebra.cpp"
#include "../data_structures/Sinusoidal_Function.cpp"
#include "../file/file.cpp"

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

	// It shud take half a period to get from min to max
	float expected_distance = abs(points[min_index].x + (period_int / 2));
	float actual_distance = abs(points[max_index].x - points[min_index].x);

	std::cerr << "expected distance: " << expected_distance << std::endl;
	std::cerr << "true distance: " << actual_distance << std::endl;

	O = abs(actual_distance - expected_distance);

	std::cerr << "O: " << O << std::endl;

	Sinusoidal_Function f(A, W, O, B);

	return f;
}

//-------------------------------------------------------------------------------------------------------------------

void fit_sinusoidal_curve_from_to(std::string in_file_name, std::string out_file_name) {
	std::vector<Point> in_points;
	std::vector<Point> out_points;
	std::vector<float> coefs;
	int num_points;

	read_csv(in_points, in_file_name.c_str());

	try {
		Sinusoidal_Function f = get_sinusoidal_function(in_points);

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
		fit_sinusoidal_curve_from_to(in_file_name, out_file_name);

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
