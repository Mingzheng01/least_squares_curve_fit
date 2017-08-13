#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include "../../../../include/internal/data_structures/functions/Function.hpp"
#include "../../../../include/internal/data_structures/functions/Point.hpp"
#include "../../../../include/internal/data_structures/exception/nan_exception.hpp"
#include "../../../../include/internal/util/math/math.hpp"

bool file_exists(const std::string& file_name) {
	bool exit_status = false;
	std::ifstream file(file_name.c_str());

	if (file.good() == true) {
		exit_status = true;
	}

	file.close();

	return exit_status;
}

int get_num_lines(const std::string& file_name) {
	int count = -1;

	if (file_exists(file_name) == true) {
		std::ifstream in_file(file_name.c_str());
		std::string str;

		count = 0;

		while (std::getline(in_file, str)) {
			count++;
		}
	}

	return count;
}

bool read_csv(std::vector<Point>& points, const std::string& file_name) {
	bool exit_status = false;

	if (file_exists(file_name) == true) {
		std::ifstream in_file(file_name.c_str());
		points.reserve(get_num_lines(file_name));
		float x;
		float y;
		int index_of_comma;
		int last_index;
		std::string line;

		for (int i = 0; std::getline(in_file, line); i++) {
			index_of_comma = line.find(',', 0);
			last_index = line.length()-1;

			points[i].x = atof(line.substr(0, index_of_comma).c_str());
			points[i].y = atof(line.substr(index_of_comma+1, last_index).c_str());
		}

		in_file.close();

		exit_status = true;
	}

	return exit_status;
}

bool write_csv(std::vector<Point>& points, const std::string& file_name) {
	bool exit_status = false;
	int size;

	std::ofstream output_file;
	output_file.open(file_name.c_str());

	// Write each point in form x,y to next line
	for (int i = 0, size = points.capacity(); i < size; i++) {
		output_file << points[i].x << "," << points[i].y << "\n";
	}

	output_file.close();
	exit_status = true;

	return exit_status;
}




void write_curve_to_file(std::string in_file_name, std::string out_file_name, Function& f) {
	std::vector<Point> in_points;
	std::vector<Point> out_points;
	std::vector<float> coefs;
	int num_points;

	read_csv(in_points, in_file_name.c_str());

	try {

		std::vector<float> min_max;
		min_max = min_and_max_x(in_points);

		// Show f(x) on domain [min_x-10, max_x+10] to see where function is coming from and going to
		//out_points = f.f_on_domain_as_xy_points(min_max[0] - in_points.capacity() / 10, min_max[1] + in_points.capacity() / 10);
	
		out_points = f.f_on_domain_as_xy_points(in_points);

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



