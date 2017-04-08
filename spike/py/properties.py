import ConfigParser

config = ConfigParser.ConfigParser()
config
config.read("properties.ini")

# titles
least_squares = config.get('titles', 'least_squares_window_title')

# labels
input_file_name = config.get('labels', 'input_file_name_label_str')
output_file_name = config.get('labels', 'output_file_name_label_str')
order_of_magnitude = config.get('labels', 'order_of_margnitude_label_str')

# buttons
plot_str = config.get('buttons', 'plots_str')
clear_str = config.get('buttons', 'clear_str')

# directories
in_file_directory = config.get('directories', 'input_directory')
out_file_directory = config.get('directories', 'output_directory')
x_axis_label = config.get('axes', 'x_axis_label')
y_axis_label = config.get('axes', 'y_axis_label')

print(least_squares)
print(input_file_name)
print(output_file_name)
print(order_of_magnitude)
print(plot_str)
print(clear_str)
print(in_file_directory)
print(out_file_directory)
print(x_axis_label)
print(y_axis_label)

