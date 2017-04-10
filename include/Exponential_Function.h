#ifndef EXPONENTIAL_FUNCTION_H
#define EXPONENTIAL_FUNCTION_H

#include "Function.h"

class Exponential_Function: public Function {
	public:
		Exponential_Function(float A, float B);
		~Exponential_Function();
		
		float f(float x);
		std::vector<Point> f_on_domain_as_xy_points(float a, float b);
		void display();
	
	protected:
	
	private:	
		float A;
		float B;
};

#endif
