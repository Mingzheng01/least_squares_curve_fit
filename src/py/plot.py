import configparser
import replace_me
import file_io

# http://www.programming-techniques.com/2011/09/numerical-methods-inverse-of-nxn-matrix.html

#-----------------------------------------------------------------------------------------------------

directories_config = configparser.ConfigParser()
directories_config.read("../../ini/properties.ini")

# All directories necessary for program to run
in_file_directory = directories_config.get('directories', 'input_directory')
out_file_directory = directories_config.get('directories', 'output_directory')
log_output_directory = directories_config.get('directories', 'log_output_directory')
exp_output_directory = directories_config.get('directories', 'exp_output_directory')
poly_output_directory = directories_config.get('directories', 'poly_output_directory')
sin_output_directory = directories_config.get('directories', 'sin_output_directory')

#-----------------------------------------------------------------------------------------------------

def original_data(input_directory):
	org_data = file_io.read_from_csv(input_directory)
	org_data.append("$f(x)=sin(x)+x$")
	return org_data

#-----------------------------------------------------------------------------------------------------

def polynomial_fit(input_directory, order):
	# Call code that calls C++ to write out to file
	function_name = replace_me.call_cpp_curve_fit('least_squares_polynomial', input_directory, poly_output_directory, order)

	poly_fit = file_io.read_from_csv(poly_output_directory)
	poly_fit.append(function_name)
	return poly_fit

#-----------------------------------------------------------------------------------------------------

def exponential_fit(input_directory):
	function_name = replace_me.call_cpp_curve_fit('least_squares_exponential', input_directory, exp_output_directory, '')

	exp_fit = file_io.read_from_csv(exp_output_directory)
	exp_fit.append(function_name)
	return exp_fit

#-----------------------------------------------------------------------------------------------------

def logarithmic_fit(input_directory):
	function_name = replace_me.call_cpp_curve_fit('least_squares_logarithmic', input_directory, log_output_directory, '')

	log_fit = file_io.read_from_csv(log_output_directory)
	log_fit.append(function_name)
	return log_fit

#-----------------------------------------------------------------------------------------------------

def sinusoidal_fit(input_directory):
	function_name = replace_me.call_cpp_curve_fit('least_squares_sinusoidal', input_directory, sin_output_directory, '')

	sin_fit = file_io.read_from_csv(sin_output_directory)
	sin_fit.append(function_name)
	return sin_fit

