#include <vector>
#include <cstdio>
#include <cmath>
#include "../../../../include/Point.hpp"
#include "../../../../include/Polynomial_Function.hpp"
#include <math.h>

std::vector<float> coefficients;
int coefficients_size;

/*
Constructs Polynomial_Function from vector<float> of coefficients
*/
Polynomial_Function::Polynomial_Function(std::vector<float>& coefs) {
	coefficients_size = coefs.capacity();
	coefficients.reserve(coefficients_size);
	
	for (int i = 0; i < coefficients_size; i++) {
		coefficients[i] = coefs[i];
	}
}

/*
Destructor
*/
Polynomial_Function::~Polynomial_Function() {
	;
}

/*
Evaluates the function f(x) for some x
*/
float Polynomial_Function::f(float x) {
	float y = 0;
	
	for (int i = 0; i < coefficients_size; i++) {
		y += coefficients[i] * pow(x, i);
	}
	
	if (std::isnan(y)) {
		std::cerr << "f():\n f(" << x << ") evaluated to NaN (not a number)." <<
					 " It is possible that" << x << " is not a number or the function has an order of magnitude " <<
					 " that is either too large or too small that causes f(x) to evaluate " <<
					 " to a value that cannot be held in float" << std::endl << std::endl;
		nan_exception nan_except;
		throw nan_except;
	}
	
	return y;
}

void Polynomial_Function::display() {
	printf("$f(x) = ");
	
	for (int i = coefficients_size-1; i >= 0; i--) {
		
		if (coefficients[i] != 0) {
			if (i != coefficients_size-1) {
				if (coefficients[i] > 0) {
					printf("+");
				}
				
				if (coefficients[i] < 0) {
					printf("-");
				}
			}
		
			if (i > 1) {
				printf("%.2fx^%i", std::abs(coefficients[i]), i);
				
			} else if (i == 1) {
				printf("%.2fx", std::abs(coefficients[i]));
				
			} else {
				printf("%.2f", std::abs(coefficients[i]));
			}
		}
	}
	printf("$");
}
