#ifndef EXPONENTIAL_FUNCTION_H
#define EXPONENTIAL_FUNCTION_H

#include "Function.hpp"

class Exponential_Function: public Function {
	public:
		Exponential_Function(float A, float B);
		~Exponential_Function();
		
		float f(float x);
		void display();
		static Exponential_Function least_squares(std::vector<Point>& points);
	
	protected:
	
	private:	
		float A;
		float B;
};

#endif
