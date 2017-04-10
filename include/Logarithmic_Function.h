#ifndef Logarithmic_FUNCTION_H
#define Logarithmic_FUNCTION_H

#include "Function.h"

class Logarithmic_Function: public Function {
	public:
		Logarithmic_Function(float a, float b);
		~Logarithmic_Function();
		
		float f(float x);
		std::vector<Point> f_on_domain_as_xy_points(float a, float b);
		void display();
	
	protected:
	
	private:	
		float a;
		float b;
};

#endif
