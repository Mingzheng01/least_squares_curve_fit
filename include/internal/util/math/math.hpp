#ifndef MATH_DEFINE_H
#define MATH_DEFINE_H

#include "../../data_structures/functions/Point.hpp"

float sum_y_lnx(std::vector<Point>& points, int j, int k);
float sum_x_y_lny(std::vector<Point>& points, int j, int k, int l);
float sum_x_y(std::vector<Point>& points, int j, int k);
std::vector<float> min_and_max_x(std::vector<Point>& points);
std::vector<float> min_and_max_y(std::vector<Point>& points);
int get_rand(int min, int max);

#endif
