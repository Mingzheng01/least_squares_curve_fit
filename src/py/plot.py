import matplotlib.pyplot as plt
import csv
import platform
import os
import collections
import numpy as np
from pathlib import Path
import configparser

# http://www.programming-techniques.com/2011/09/numerical-methods-inverse-of-nxn-matrix.html

windows = 'Windows'
mac = 'Darwin'
linux = 'Linux'
Unix = 'Unix'

'''==================================================================================================='''

directories_config = configparser.ConfigParser()
directories_config.read("../../ini/properties.ini")

# All directories necessary for program to run
in_file_directory = directories_config.get('directories', 'input_directory')
out_file_directory = directories_config.get('directories', 'output_directory')
log_output_directory = directories_config.get('directories', 'log_output_directory')
exp_output_directory = directories_config.get('directories', 'exp_output_directory')
poly_output_directory = directories_config.get('directories', 'poly_output_directory')
sin_output_directory = directories_config.get('directories', 'sin_output_directory')

# Put them in a list
directories = []
directories.append(in_file_directory)
directories.append(out_file_directory)
directories.append(log_output_directory)
directories.append(exp_output_directory)
directories.append(poly_output_directory)
directories.append(sin_output_directory)

'''==================================================================================================='''


'''
If the proper files do not exist already, make them
'''
def setup_io_file():
	global directories

	all_files_found = False
	num_files_found = 0

	# See if input.csv and output.csv already exist
	# If not, make them

	# TODO - Change print statements to log statements

	for i in range(len(directories)):
		in_file = Path(directories[i])

		if in_file.is_file():
			num_files_found = num_files_found + 1
			print("Exists: " + directories[i])

		else:
			in_file = open(directories[i], 'w')
			in_file.close();
			num_files_found = num_files_found + 1
			print("Created: " + directories[i])

	if num_files_found == len(directories):
		all_files_found = True


	return all_files_found

#-----------------------------------------------------------------------------------------------------

'''
TODO - This function will be replaced with code that
calls C or C++ code and will then build the list of points
'''
def REPLACE_ME(order):
	# Call code that calls C++ to write out to file
	call_cpp_curve_fit(in_file_directory, out_file_directory, order)

	# Read in from output.csv file
	output_data = open(out_file_directory)
	csv_f1 = csv.reader(output_data)

	# Declare temporary lists for holding most recent X,Y pairs from output.csv
	temp_x = []
	temp_y = []

	# Read in output data (best fit plot)
	for row in csv_f1:
	  temp_x.append(float(row[0]))
	  temp_y.append(float(row[1]))

	return [temp_x, temp_y]

#-----------------------------------------------------------------------------------------------------

def call_cpp_curve_fit(in_file_name, out_file_name, order):
	platform_str = platform.system()

	print('Identified OS as: ' + platform_str)

	# TODO - Implement for other OS later
	if platform_str == windows:
		command = '..\\cpp\\main' + " " + '\"' + in_file_name + '\"' + " " + '\"' + out_file_name + '\"' + " " + str(order)
		print(command)
		os.system(command)

	if platform_str == linux:
		command = '../cpp/./main' + " " + '\"' + in_file_name + '\"' + " " + '\"' + out_file_name + '\"' + " " + str(order)
		print(command)
		os.system(command)

	if platform_str == mac:
		command = '../cpp/./main' + " " + '\"' + in_file_name + '\"' + " " + '\"' + out_file_name + '\"' + " " + str(order)
		print(command)
		os.system(command)

	else:
		print('Could not determin OS: ' + platform_str)
