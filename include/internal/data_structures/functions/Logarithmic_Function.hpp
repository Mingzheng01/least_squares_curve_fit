#ifndef Logarithmic_FUNCTION_H
#define Logarithmic_FUNCTION_H

#include "Function.hpp"

class Logarithmic_Function: public Function {
	public:
		Logarithmic_Function(float a, float b);
		~Logarithmic_Function();
		
		float f(float x);
		void display();
		static Logarithmic_Function least_squares(std::vector<Point>& points);
	
	protected:
	
	private:	
		float a;
		float b;
};

#endif
