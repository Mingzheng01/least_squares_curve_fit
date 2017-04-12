#ifndef POLYNOMIAL_FUNCTION_H
#define POLYNOMIAL_FUNCTION_H

#include "Function.hpp"

class Polynomial_Function: public Function {
	public:
		Polynomial_Function(std::vector<float>& coefs);
		~Polynomial_Function();
		
		float f(float x);
		void display();
	
	protected:
	
	private:	
		std::vector<float> coefficients;
		int coefficients_size;
};

#endif
