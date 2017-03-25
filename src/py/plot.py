import matplotlib.pyplot as plt
import csv
import platform
import os

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


def plot(in_file_name, out_file_name, order):
	curve_fit(in_file_name, out_file_name, order)

	input_data = open(in_file_name)
	best_fit = open(out_file_name)
	
	csv_f0 = csv.reader(input_data)
	csv_f1 = csv.reader(best_fit)

	x_0 = []
	y_0 = []

	x_1 = []
	y_1 = []

	for row in csv_f0:
	  x_0.append(float(row[0]))
	  y_0.append(float(row[1]))

	for row in csv_f1:
	  x_1.append(float(row[0]))
	  y_1.append(float(row[1]))

	plt.plot(x_0, y_0, 'ro')
	plt.plot(x_1, y_1)
	plt.show()
