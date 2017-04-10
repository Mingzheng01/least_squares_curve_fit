#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>
#include "../../../include/Point.h"
#include "../../../include/Sinusoidal_Function.h"
#include "../math/math.cpp"
#include "../math/linear_algebra.cpp"
#include "../data_structures/Sinusoidal_Function.cpp"
#include "../file/file.cpp"

//-------------------------------------------------------------------------------------------------------------------

void fit_sinusoidal_curve_from_to(std::string in_file_name, std::string out_file_name) {
	std::cout << "$f(x)=sin(x)$";
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
