import matplotlib.pyplot as plt
import csv
import platform
import os
import collections
import numpy as np

# http://www.programming-techniques.com/2011/09/numerical-methods-inverse-of-nxn-matrix.html

windows = 'Windows'
mac = 'Mac'
linux = 'Linux'
Unix = 'Unix'

def curve_fit(in_file_name, out_file_name, order):
	platform_str = platform.system()
	
	# TODO - Implement for other OS later
	if platform_str == windows:
		command = '..\\cpp\\main' + " " + '\"' + in_file_name + '\"' + " " + '\"' + out_file_name + '\"' + " " + str(order)
		print(command)
		os.system(command)

	if platform_str == linux:
		command = '../cpp/./main' + " " + '\"' + in_file_name + '\"' + " " + '\"' + out_file_name + '\"' + " " + str(order)
		print(command)
		os.system(command)

