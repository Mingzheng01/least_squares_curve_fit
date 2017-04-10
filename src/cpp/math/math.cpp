#include <vector>
#include <math.h>
#include "../../../include/Point.h"
#include "../exception/nan_exception.cpp"

//-------------------------------------------------------------------------------------------------------------------

/*

 n
---
\  
/     (yi)^j * ln^k(xi)
---
i=1

*/
float sum_y_lnx(std::vector<Point>& points, int j, int k) {
	int n = points.capacity();
	float sum = 0;
	
	for (int i = 0; i < n; i++) {
		sum += pow(points[i].y, j) * pow(log(points[i].x), k);
	}
	
	if (isnan(sum)) {
		std::cerr << "sum_x_y_lnx(): Sum of x^k *ln^n(x) evaluated to NaN (not a number)." <<
					 " It is possible that a given point in the data set has a a value" <<
					 " that is not a number, too large or too small for a floating point number" <<
					 " Or the desired order of magnitudes k or m are too large, causing the product" <<
					 " of x^k * y^m to exceed the maximum value for a floating point number" << std::endl << std::endl;
		nan_exception nan_except;
		throw nan_except;
	}
	
	return sum;
}

//-------------------------------------------------------------------------------------------------------------------

/*

 n
---
\  
/     (xi)^j * (yi)^k  * ln^l(yi)
---
i=1

*/
float sum_x_y_lny(std::vector<Point>& points, int j, int k, int l) {
	int n = points.capacity();
	float sum = 0;
	
	for (int i = 0; i < n; i++) {
		
		float x = pow(points[i].x, j);
		float z = pow(points[i].y, k);
		float y = pow(log(points[i].y), l);

		//std::cerr << x << " * " << y << " * " << z << std::endl;
		
		sum += (float) (x * y * z);
	}
	
	if (isnan(sum)) {
		std::cerr << "sum_x_y_lny(): Sum of x^k * y^m *ln^n(y) evaluated to NaN (not a number)." <<
					 " It is possible that a given point in the data set has a a value" <<
					 " that is not a number, too large or too small for a floating point number" <<
					 " Or the desired order of magnitudes k or m are too large, causing the product" <<
					 " of x^k * y^m to exceed the maximum value for a floating point number" << std::endl << std::endl;
		nan_exception nan_except;
		throw nan_except;
	}
	
	return sum;
}

//-------------------------------------------------------------------------------------------------------------------

/*

 n
---
\  
/     (xi)^k * (yi)^m 
---
i=1

*/
float sum_x_y(std::vector<Point>& points, int j, int k) {
	int n = points.capacity();
	float sum = 0;
	
	for (int i = 0; i < n; i++) {
		sum += pow(points[i].x, j) * pow(points[i].y, k);
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

//-------------------------------------------------------------------------------------------------------------------

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

//-------------------------------------------------------------------------------------------------------------------

int get_rand(int min, int max) {

     if (min < max == false) {
	min = -10;
        max = 10;
     }

     return rand() % (max - min) + min + 1; 

}
