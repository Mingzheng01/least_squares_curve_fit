#ifndef Logarithmic_FUNCTION_H
#define Logarithmic_FUNCTION_H

#include "Function.hpp"

class Logarithmic_Function: public Function {
	public:
		Logarithmic_Function(float a, float b);
		~Logarithmic_Function();
		
		float f(float x);
		void display();
	
	protected:
	
	private:	
		float a;
		float b;
};

#endif
