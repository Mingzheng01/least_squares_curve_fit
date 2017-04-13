#ifndef FILE_H
#define FILE_H

#include "../../data_structures/functions/Point.hpp"

bool file_exists(const std::string& file_name);
int get_num_lines(const std::string& file_name);
bool read_csv(std::vector<Point>& points, const std::string& file_name);
bool write_csv(std::vector<Point>& points, const std::string& file_name);
void write_curve_to_file(std::string in_file_name, std::string out_file_name, Function& f);

#endif
