#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include "../../../include/internal/data_structures/exception/nan_exception.hpp"
#include "../../../include/internal/data_structures/functions/Exponential_Function.hpp"
#include "../../../include/internal/data_structures/functions/Logarithmic_Function.hpp"
#include "../../../include/internal/data_structures/functions/Polynomial_Function.hpp"
#include "../../../include/internal/data_structures/functions/Sinusoidal_Function.hpp"
#include "../../../include/internal/data_structures/functions/Point.hpp"
#include "../../../include/internal/util/file/file.hpp"


int main(int argc, char* argv[]) {
	int order;
	int op_code;
	std::string in_file_name;
	std::string out_file_name ;

	if (argc == 5) {

		// Read in command line arguments
		op_code = atoi(argv[1]);
		in_file_name = argv[2];
		out_file_name = argv[3];
		order = atoi(argv[4]);

		try {

			// Read input points
			std::vector<Point> in_points;
			read_csv(in_points, in_file_name.c_str());

			switch(op_code) {
				case 0 : {
					Exponential_Function e_f = Exponential_Function::least_squares(in_points);
					write_curve_to_file(in_file_name, out_file_name, e_f);
					e_f.display();
					break;
				}

				case 1 : {
					Logarithmic_Function l_f = Logarithmic_Function::least_squares(in_points);
					write_curve_to_file(in_file_name, out_file_name, l_f);
					l_f.display();
					break;
				}

				case 2 : {
					Polynomial_Function p_f = Polynomial_Function::least_squares(in_points, order);
					write_curve_to_file(in_file_name, out_file_name, p_f);
					p_f.display();
					break;
				}

				case 3 : {
					Sinusoidal_Function s_f = Sinusoidal_Function::least_squares(in_points);
					write_curve_to_file(in_file_name, out_file_name, s_f);
					s_f.display();
					break;
				}

				default: std::cerr << "Op code not recognized"; break;
			}

		} catch (const std::invalid_argument& e) {
			std::cerr << e.what() << std::endl;
			std::cerr << "main():\n Curve fit unsuccessful" << std::endl;
			return -1;

		} catch (const nan_exception& e) {
			std::cerr << e.what() << std::endl;
			std::cerr << "main():\n Curve fit unsuccessful" <<
			" because of NaN found in calculations or" <<
			" desired order of magnitude for curve fit is too high" << std::endl;
			return -1;

		} catch (...) {
			std::cerr << "main():\n Curve fit unsuccessful for unknown reason, please debug" << std::endl;
			return -1;
		}
	} else {

		std::cerr << "4 arguments requires\n";
	}

	return 0;
}
