#include <vector>
#include "../../../include/Point.h"
#include "../exception/nan_exception.cpp"
#include <math.h>

/*

 n
---
\  
/     (xi)^k * (yi)^m 
---
i=0

*/
float sum_x_y(std::vector<Point>& points, int k, int m) {
	int n = points.capacity();
	float sum = 0;
	
	for (int i = 0; i < n; i++) {
		sum += pow(points[i].x, k) * pow(points[i].y, m);
	}
	
	if (isnan(sum)) {
		std::cerr << "sum_x_y(): Sum of x^k * y^m evaluated to NaN (not a number)." <<
					 " It is possible that a given point in the data set has a a value" <<
					 " that is not a number, too large or too small for a floating point number" <<
					 " Or the desired order of magnitudes k or m are too large, causing the product" <<
					 " of x^k * y^m to exceed the maximum value for a floating point number" << std::endl << std::endl;
		nan_exception nan_except;
		throw nan_except;
	}
	
	return sum;
}

std::vector<float> min_and_max_x(std::vector<Point>& points) {
	float min = 0;
	float max = 0;
	float cur = 0;
	int length = points.capacity();
	std::vector<float> min_and_max;

	for (int i = 0; i < length; i++) {
		if (points[i].x < min) {
			min = points[i].x;
		}  
		
		if (points[i].x > max) {
			max = points[i].x;
		}
	}

	min_and_max.push_back(min);
	min_and_max.push_back(max);
	
	return min_and_max;
}
