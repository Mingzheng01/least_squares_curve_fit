import configparser
import util.file.file_io as file_io
import util.command_line.replace_me as replace_me

#-----------------------------------------------------------------------------------------------------

properties_config = configparser.ConfigParser()
properties_config.read("../../properties.ini")

# All directories necessary for program to run
in_file_directory = properties_config.get('directories', 'input_directory')
out_file_directory = properties_config.get('directories', 'output_directory')
log_output_directory = properties_config.get('directories', 'log_output_directory')
exp_output_directory = properties_config.get('directories', 'exp_output_directory')
poly_output_directory = properties_config.get('directories', 'poly_output_directory')
sin_output_directory = properties_config.get('directories', 'sin_output_directory')

# Get op codes for running different curve fits
EXPONENTIAL_LEAST_SQUARES_OP_CODE = str(properties_config.get('curve_fit_op_codes','EXPONENTIAL_LEAST_SQUARES_OP_CODE'))
LOGARIMTHIC_LEAST_SQUARES_OP_CODE = str(properties_config.get('curve_fit_op_codes','LOGARITHMIC_LEAST_SQUARES_OP_CODE'))
POLYNOMIAL_LEAST_SQUARES_OP_CODE  = str(properties_config.get('curve_fit_op_codes','POLYNOMIAL_LEAST_SQUARES_OP_CODE'))
SINUSOIDAL_LEAST_SQUARES_OP_CODE  = str(properties_config.get('curve_fit_op_codes','SINUSOIDAL_LEAST_SQUARES_OP_CODE'))

#-----------------------------------------------------------------------------------------------------

def original_data(input_directory, original_data_name):
	org_data = file_io.read_from_csv(input_directory)
	org_data.append(original_data_name)
	return org_data

#-----------------------------------------------------------------------------------------------------

def exponential_fit(input_directory):
	function_name = replace_me.call_cpp_curve_fit(EXPONENTIAL_LEAST_SQUARES_OP_CODE,
												  input_directory,
												  exp_output_directory,
												  -1)

	exp_fit = file_io.read_from_csv(exp_output_directory)
	exp_fit.append(function_name)
	return exp_fit

#-----------------------------------------------------------------------------------------------------

def logarithmic_fit(input_directory):
	function_name = replace_me.call_cpp_curve_fit(LOGARIMTHIC_LEAST_SQUARES_OP_CODE,
												  input_directory,
												  log_output_directory,
												  -1)

	log_fit = file_io.read_from_csv(log_output_directory)
	log_fit.append(function_name)
	return log_fit

#-----------------------------------------------------------------------------------------------------

def polynomial_fit(input_directory, order_of_magnitude):
	function_name = replace_me.call_cpp_curve_fit(POLYNOMIAL_LEAST_SQUARES_OP_CODE,
												  input_directory,
												  poly_output_directory,
												  order_of_magnitude)

	poly_fit = file_io.read_from_csv(poly_output_directory)
	poly_fit.append(function_name)
	return poly_fit

#-----------------------------------------------------------------------------------------------------

def sinusoidal_fit(input_directory):
	function_name = replace_me.call_cpp_curve_fit(SINUSOIDAL_LEAST_SQUARES_OP_CODE,
											      input_directory,
												  sin_output_directory,
												  -1)

	sin_fit = file_io.read_from_csv(sin_output_directory)
	sin_fit.append(function_name)
	return sin_fit
