import platform
import os
import subprocess
import configparser

# Get configParsers for reading in strings from .ini
properties_config = configparser.ConfigParser()
properties_config.read("../../properties.ini")

# Get operating system names
linux_os_name_str = properties_config.get('os_names','linux_os_name_str')
mac_os_name_str = properties_config.get('os_names', 'mac_os_name_str')
windows_os_name_str = properties_config.get('os_names','windows_os_name_str')

# Get directory for executables
curve_fit_executable_directory_linux = properties_config.get('directories', 'curve_fit_executable_directory_linux')
curve_fit_executable_directory_windows = properties_config.get('directories', 'curve_fit_executable_directory_windows')

# For decoding byte array output from command line
ascii = "ascii"

#-----------------------------------------------------------------------------------------------------

def call_cpp_curve_fit(op_code,
					   in_file_name,
					   out_file_name,
					   order):

	platform_str = platform.system()

	function_name = ''

	print('Identified OS as: ' + platform_str)

	if platform_str == linux_os_name_str or platform_str == mac_os_name_str:
		command = curve_fit_executable_directory_linux + " " + op_code + " " + in_file_name + " " + out_file_name + " " + str(order)

		print(command)

		proc = subprocess.Popen([command, in_file_name, out_file_name, str(order)], shell=True, stdout=subprocess.PIPE)
		function_name = proc.stdout.read()
		function_name = function_name.decode(ascii)

	elif platform_str == windows_os_name_str:
		command = curve_fit_executable_directory + "" + op_code + " " + '\"' + in_file_name + '\"' + " " + '\"' + out_file_name + '\"' + " " + str(order)
		print(command)
		os.system(command)

	else:
		print('Could not determin OS: ' + platform_str)


	return function_name
