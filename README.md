# Least Squares Curve Fit
This repository features a C++ and Python implementation of the least squares curve fitting technique.

## Installation

Assuming that you have the C++ compiled `g++` and Python 3 Interpreter `python3` installed, take the
following steps to install the application.

`git clone https://github.com/N02870941/least_squares_curve_fit.git`

`cd least_squares_curve_fit`

`mkdir bin`

`cmake .`

`make`

`pip3 install matplotlib`

## User Interface
The Graphical User Interface (GUI) is written in *Python*, using the [Tkinter](https://docs.python.org/2/library/tkinter.html) and [Matplotlib](http://matplotlib.org/) libraries. I chose to write the frontend in Python for simplicity and for the purpose of faster development. A sample photo of the general output of the program follows:

![GUI](doc/img/demo.png)

## Data Model / Calculations
All of the functions that do the actual calculations are written in *C++* . I chose to write them in *C++* for a variety of reasons.

1. Speed. it is fast
2. Difficulty, it is more challenging to write
3. I will port the algorithms to [CUDA C](http://www.nvidia.com/object/cuda_home_new.html) for even more optimization

All of the functions that do the calculations are written in the source code. This way, you can step through each phase of the process of the [least squares](https://en.wikipedia.org/wiki/Least_squares) algorithm. Note, this implementation is a proof of concept.
