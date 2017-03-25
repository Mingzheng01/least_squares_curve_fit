#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "../../../include/Point.h"

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

bool test_data(const std::string& file_name) {
	
	int a = 0;
	int b = 360;
	float pi = 3.14159265;
	
	std::vector<Point> points;
	points.reserve(b+1);
	
	// f(x) = x^3 + 2x - 7
	// f(x) = sin(x)
	for (int i = 0; i <= b; i++) {
		//points[i].x = i;
		//points[i].y = i*i*i + 2*i - 7;

		points[i].x = i;
		points[i].y = sin(i * pi / 180) * 180 / pi;
	}
	
	write_csv(points, file_name);
}



