#ifndef SINUSOIDAL_FUNCTION_H
#define SINUSOIDAL_FUNCTION_H

#include "Function.hpp"

class Sinusoidal_Function: public Function {
	public:
		Sinusoidal_Function(float A, float W, float O, float B);
		~Sinusoidal_Function();
		
		float f(float x);
		void display();
	
	protected:
	
	private:	
		float A;
		float W;
		float O;
		float B;
};

#endif
