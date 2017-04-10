#ifndef POLYNOMIAL_FUNCTION_H
#define POLYNOMIAL_FUNCTION_H

#include "Function.h"

class Polynomial_Function: public Function {
	public:
		Polynomial_Function(std::vector<float>& coefs);
		~Polynomial_Function();
		
		float f(float x);
		std::vector<Point> f_on_domain_as_xy_points(float a, float b);
		void display();
	
	protected:
	
	private:	
		std::vector<float> coefficients;
		int coefficients_size;
};

#endif
