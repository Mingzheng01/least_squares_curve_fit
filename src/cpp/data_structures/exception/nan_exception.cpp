#include <exception>

class nan_exception: public std::exception {
  virtual const char* what() const throw() {
    return "Not a number";
  }
};