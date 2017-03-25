#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "..\..\include\Point.h"
#include "curve_fit\least_squares_curve_fit.cpp"
#include "data_structures\Polynomial_Function.cpp"
#include "file\file.cpp"	

void fit_n_order_curve_from_to(int order, std::string in_file_name, std::string out_file_name) {
	std::vector<Point> in_points;
	std::vector<Point> out_points;
	std::vector<float> coefs;
	int num_points;
	
	read_csv(in_points, in_file_name.c_str());
		
	try {
		coefs = n_order_least_squares_fit(in_points, order);
		
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
	
	Polynomial_Function f(coefs);
	f.display();
	
	std::vector<float> min_max;
	min_max = min_and_max_x(in_points);
	
	out_points = f.f_on_domain_as_xy_points(min_max[0], min_max[1]);
	
	write_csv(out_points, out_file_name);
}

int main(int argc, char* argv[]) {
	int order = 2;
	std::string in_file_name = "..\\..\\data\\input.csv";
	std::string out_file_name = "..\\..\\data\\output.csv";
	
	if (argc == 4) {
		in_file_name = argv[1];
		out_file_name = argv[2];
		order = atoi(argv[3]);
		
		test_data(in_file_name);
		
		try {
		fit_n_order_curve_from_to(order, in_file_name, out_file_name);
		
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