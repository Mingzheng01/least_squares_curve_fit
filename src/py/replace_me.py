import platform
import os
import subprocess
import sys

windows = 'Windows'
mac = 'Darwin'
linux = 'Linux'
Unix = 'Unix'

#-----------------------------------------------------------------------------------------------------

def call_cpp_curve_fit(which_fit, in_file_name, out_file_name, order):
	platform_str = platform.system()

	function_name = ''

	# TODO - turn file_names into file objects, and get absolute path to compensate for different folder lvls between py and cpp

	print('Identified OS as: ' + platform_str)

	if platform_str == windows:
		command = '..\\cpp\\curve_fit\\' + "" + which_fit + " " + '\"' + in_file_name + '\"' + " " + '\"' + out_file_name + '\"' + " " + str(order)
		print(command)
		os.system(command)

	elif platform_str == linux:
		command = '../../bin/./curve_fit' + " " + which_fit + " " + in_file_name + " " + out_file_name + " " + str(order)

		print(command)

		proc = subprocess.Popen([command, in_file_name, out_file_name, str(order)], shell=True, stdout=subprocess.PIPE)
		function_name = proc.stdout.read()

		function_name = function_name.decode('ascii')

	elif platform_str == mac:
		command = '../cpp/curve_fit/./'+ which_fit + " " + '\"' + in_file_name + '\"' + " " + '\"' + out_file_name + '\"' + " " + str(order)
		print(command)
		os.system(command)	

	else:
		print('Could not determin OS: ' + platform_str)


	return function_name
