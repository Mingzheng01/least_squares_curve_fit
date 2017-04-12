#ifndef FUNCTION_H
#define FUNCTION_H

class Function {
	public:
		
		virtual void display();
		virtual float f(float x);
		virtual std::vector<Point> f_on_domain_as_xy_points(float a, float b);	
	
	protected:
	
	private:	

};

#endif
