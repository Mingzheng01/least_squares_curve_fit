#include "../../../../include/data_structures/exception/nan_exception.hpp"

const char* nan_exception:: what() const throw() {
	return "Not a number";
}

