#ifndef LEAST_SQUARES_INCLUDED
#define LEAST_SQUARES_INCLUDED

#include "../data_structures/functions/Point.hpp"

Exponential_Function get_exponential_function(std::vector<Point>& points);
Logarithmic_Function get_logarithmic_function(std::vector<Point>& points);
Polynomial_Function get_polynomial_function(std::vector<Point>& points, int order);
Sinusoidal_Function get_sinusoidal_function(std::vector<Point>& points);

#endif
