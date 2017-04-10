from pathlib import Path
import configparser
import csv

#-----------------------------------------------------------------------------------------------------

def is_valid_input_file(directory):
	in_file = Path(directory)

	if in_file.is_file():
		return True
	else:
		return False

#-----------------------------------------------------------------------------------------------------

def read_from_csv(directory):	
	# Read in from output.csv file
	output_data = open(directory)
	csv_f1 = csv.reader(output_data)

	# Declare temporary lists for holding most recent X,Y pairs from output.csv
	x = []
	y = []

	# Read in output data (best fit plot)
	for row in csv_f1:
	  x.append(float(row[0]))
	  y.append(float(row[1]))

	return [x, y]

#-----------------------------------------------------------------------------------------------------

'''
If the proper files do not exist already, make them
'''
def setup_io_file():
	all_files_found = False
	num_files_found = 0
	directories = []

	directories_config = configparser.ConfigParser()
	directories_config.read("../../ini/properties.ini")

	# All directories necessary for program to run
	in_file_directory = directories_config.get('directories', 'input_directory')
	out_file_directory = directories_config.get('directories', 'output_directory')
	log_output_directory = directories_config.get('directories', 'log_output_directory')
	exp_output_directory = directories_config.get('directories', 'exp_output_directory')
	poly_output_directory = directories_config.get('directories', 'poly_output_directory')
	sin_output_directory = directories_config.get('directories', 'sin_output_directory')

	# Put all relevant directories in a single list
	directories.append(in_file_directory)
	directories.append(out_file_directory)
	directories.append(log_output_directory)
	directories.append(exp_output_directory)
	directories.append(poly_output_directory)
	directories.append(sin_output_directory)

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
