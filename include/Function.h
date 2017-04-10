#ifndef FUNCTION_H
#define FUNCTION_H

class Function {
	public:
		
		virtual void display() = 0;
		virtual float f(float x) = 0;
		virtual std::vector<Point> f_on_domain_as_xy_points(float a, float b) = 0;	
	
	protected:
	
	private:	

};

#endif
