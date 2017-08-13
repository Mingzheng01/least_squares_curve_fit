cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CURRENT_BINARY_DIR "bin")

project(least_squares_curve_fit)

# Causes infinite loop, must manually create bin directory
# add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(
	bin/curve_fit
	src/cpp/curve_fit/curve_fit.cpp
	src/cpp/data_structures/functions/Exponential_Function.cpp
	src/cpp/data_structures/functions/Logarithmic_Function.cpp
	src/cpp/data_structures/functions/Polynomial_Function.cpp
	src/cpp/data_structures/functions/Sinusoidal_Function.cpp
	src/cpp/data_structures/functions/Function.cpp
	src/cpp/data_structures/exception/nan_exception.cpp
	src/cpp/util/math/math.cpp
	src/cpp/util/math/linear_algebra.cpp
	src/cpp/util/file/file.cpp
)
