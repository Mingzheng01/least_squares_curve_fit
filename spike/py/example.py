import collections
import plot
import csv

def get_input_and_output_coordinates(in_file_directory,out_file_directory, order):
	# Call code that calls C++ to write out to file
	plot.curve_fit(in_file_directory,out_file_directory, order)

	# Read in from output.csv file
	output_data = open(out_file_directory)
	csv_f1 = csv.reader(output_data)

	# Declare temporary lists for holding most recent X,Y pairs from output.csv
	temp_x = []
	temp_y = []

	all_x = []
	all_y = []

	# Read in output data (best fit plot)
	for row in csv_f1:
	  temp_x.append(float(row[0]))
	  temp_y.append(float(row[1]))

	all_x.append(temp_x)
	all_y.append(temp_y)

	#input
	x = [1,2,3,4]
	y = [1,4,9,16]

	InputData = collections.namedtuple('InputData', ['x_values', 'y_values'])
	input_data = InputData(x,y)

	BestFits = collections.namedtuple('BestFits', ['list_of_x_values', 'list_of_y_values'])
	
	best_fits = BestFits(all_x, all_y)

	return (input_data, best_fits)

def main():
	ret_val = get_input_and_output_coordinates("../../data/input.csv", "../../data/output.csv", 2)

	input_values = ret_val[0]

	input_x = input_values.x_values
	input_y = input_values.y_values

	print("input:\n------")
	for i in range(len(input_x)):
		print(str(input_x[i]) + "," + str(input_y[i]))


	print("\n")

	print("input:\n------")
	best_fits = ret_val[1]


	for i in range(len(best_fits.list_of_x_values)):
		temp_x = best_fits.list_of_x_values[i]
		temp_y = best_fits.list_of_y_values[i]
		

		print("output # " + str(i))
		for j in range(len(temp_x)):
			print(str(temp_x[j]) + "," + str(temp_y[j]))

#----------------------------------------------------------------------

main()	















