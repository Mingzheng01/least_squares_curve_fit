#ifndef NAN_EXCEPTION_H
#define NAN_EXCEPTION_H

#include <exception>

class nan_exception: public std::exception {

	public:
		virtual const char* what() const throw();
};

#endif
