import matplotlib

# Must run matplotlib.use() before backends so Mac does not complain
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation
import tkinter as tk
from tkinter import ttk
from tkinter import IntVar
import csv
import plot
import configparser
from tkinter import messagebox

# Global variables
#-------------------------------
gui_config = configparser.ConfigParser()
directories_config = configparser.ConfigParser()

# Read the .ini files
gui_config.read("../../ini/gui.ini")
directories_config.read("../../ini/properties.ini")

'''==================================================================================================='''

order_of_magnitude_entry = 0
plot_exponential = 0
plot_logarithmic = 0
plot_sinusoidal = 0

# Numbers
#-------------------------------
padding = 10
item_padding = 4

# Setup figure
fig = Figure(figsize=(6,4), dpi=100)
ax = fig.add_subplot(111)

# TODO - Get rid of this implementation
# Keep track of points on best fit curve to plot
poly_fits_x = []
poly_fits_y = []

# TODO - Implement arrays of Points
log_fit = []
exp_fit = []
sin_fit = []

# FUNCTIONS
#=====================================================================================================

# Set best fit matrices to empty lists
def clear_best_fits():
	global poly_fits_x
	global poly_fits_y
	global log_fit
	global exp_fit
	global sin_fit

	# Reset all of their values to empty arrays
	poly_fits_x = []
	poly_fits_y = []
	log_fit = []
	exp_fit = []
	sin_fit = []

#-----------------------------------------------------------------------------------------------------

def parse_args(order_of_magnitude_entry):
	arguments = order_of_magnitude_entry.get()

	# Clear matrix of best fits to avoid repeating plots
	clear_best_fits()

	# TODO - Plot exponential fit
	if plot_exponential.get() == 1:
		print('Fit exponential = True')
	else:
		print('Fit exponential = False')

	# TODO - Plot logarithmic fit
	if plot_logarithmic.get() == 1:
		print('Fit logarithmic = True')
	else:
		print('Fit logarithmic = False')

	# TODO - Plot sinusoidal fit
	if plot_sinusoidal.get() == 1:
		print('Fit sinusoidal = True')
	else:
		print('Fit sinusoidal = False')

	# Get list of integers from comma separated string
	lista = [x.strip() for x in arguments.split(',')]

	for i in lista:
		# Only acceppt positive integers
		try:
			if int(i) < 0:
				messagebox.showinfo("Invalid Argument", "Only enter positive integers")
				break
		except ValueError:
			messagebox.showinfo("Invalid Argument", "Only enter positive integers")
			break

		# Set best_fit_x as REPLACE_ME()[0], AND besst_fit_Y as REPLACE_ME()[1]
		ret_val = plot.REPLACE_ME(i)

		poly_fits_x.append(ret_val[0])
		poly_fits_y.append(ret_val[1])

#-----------------------------------------------------------------------------------------------------

# Display the plots
def animate(i):
	# directories
	in_file_directory = directories_config.get('directories', 'input_directory')


	x_in_list = []
	y_in_list = []

	plot_title = gui_config.get('titles', 'plot_title')

	# labels
	x_axis_label = gui_config.get('axes', 'x_axis_label')
	y_axis_label = gui_config.get('axes', 'y_axis_label')

	# Graph variables
	font_name = gui_config.get('text', 'font_name')
	font_size = gui_config.getint('text', 'font_size')
	LARGE_FONT=(font_name, font_size)

	'''
	TOOD - Make global holds current input data, and call other function
	that opens csv to update input data for live update
	'''
	input_data = open(in_file_directory)

	csv_f0 = csv.reader(input_data)

	# Read in input data (scatter plot)
	for row in csv_f0:
	  x_in_list.append(float(row[0]))
	  y_in_list.append(float(row[1]))

	ax.clear()

	# Plot the original data
	'''
	TODO - After implementing code to call C++ directly,
	Get the name of the function $f(x)=six(x)$ programmatically
	'''
	ax.plot(x_in_list,y_in_list,'ro',label="$f(x)\\approx sin(x)+x$")

	# Plot all best curves
	for i in range(len(poly_fits_x)):
		ax.plot(poly_fits_x[i],poly_fits_y[i], label="$f(x)$")

	# Give figure a title
	fig.subplots_adjust(top=0.85)
	fig.suptitle(plot_title, fontsize=14, fontweight='bold')

	# Prepare legend
	legend = ax.legend(loc='upper left', shadow=True)
	frame = legend.get_frame()
	frame.set_facecolor('0.90')

	# Set legend settings
	for label in legend.get_texts():
		label.set_fontsize('medium')

	for label in legend.get_lines():
		label.set_linewidth(1.5)

	# Set labels on graph
	ax.set_title('input.csv')
	ax.set_xlabel(x_axis_label)
	ax.set_ylabel(y_axis_label, rotation=0)

	# Position axis labels
	ax.yaxis.set_label_coords(-0.025, 1.05)
	ax.xaxis.set_label_coords(1.05, -0.025)

	# Have equal units on axis
	#ax.axis('equal')


# MAIN WINDOW Class
#=====================================================================================================
class LeastSquaresWindow(tk.Tk):
    def __init__(self,*args,**kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        container = tk.Frame(self)

        least_squares = gui_config.get('titles', 'least_squares_window_title')

        container.pack(side="top", fill="both", expand=True)

        container.grid_rowconfigure(0, weight=1)


        self.frames = {}

        frame = GraphPage(container, self)
        self.frames[GraphPage] = frame

        container.grid_columnconfigure(0, weight=1)
        frame.grid(row=0, column=0, sticky="nsew")

		# Set window title and show start page
        self.title(least_squares)
        self.show_frame(GraphPage)

	# Displays a frame
    def show_frame(self,cont):
        frame = self.frames[cont]
        frame.tkraise()


# Graph Page Class
#=====================================================================================================
class GraphPage(tk.Frame):
	def __init__(self, parent, controller):
		tk.Frame.__init__(self, parent)

		# Create graph canvas
		canvas = FigureCanvasTkAgg(fig, self)

		# Create toolbar for graph
		toolbar = NavigationToolbar2TkAgg(canvas, self)
		toolbar.update()

		# Create other frames that will go into this frame
		options_frame = Options(controller, self)
		buttons_frame = Buttons(controller, self)

		# Pack all frames into this frame
		canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
		options_frame.pack()
		buttons_frame.pack()

		# Show canvas
		canvas.show()


# Options Frame Class that will go within the Graph Page
#=====================================================================================================
class Options(tk.Frame):
	def __init__(self, parent, controller):
		tk.Frame.__init__(self, parent)

		global plot_exponential
		global plot_logarithmic
		global plot_sinusoidal
		global order_of_magnitude_entry

		# String variables from gui.ini
		input_file_name = gui_config.get('labels', 'input_file_name_label_str')
		output_file_name = gui_config.get('labels', 'output_file_name_label_str')
		order_of_magnitude_label_str = gui_config.get('labels', 'order_of_magnitude_label_str')
		logarithmic_checkbox_label_str = gui_config.get('labels', 'logarithmic_checkbox_label_str')
		exponential_checkbox_label_str = gui_config.get('labels', 'exponential_checkbox_label_str')
		sinusoidal_checkbox_label_str = gui_config.get('labels', 'sinusoidal_checkbox_label_str')

		# Set these as boolean-ish values to track checkbox values
		plot_exponential = IntVar()
		plot_logarithmic = IntVar()
		plot_sinusoidal = IntVar()

		# Create labels
		input_label = ttk.Label(self, text=input_file_name)
		output_label = ttk.Label(self, text=output_file_name)
		order_of_magnitude_label = ttk.Label(self, text=order_of_magnitude_label_str)

		# Create text entry fields
		input_entry = ttk.Entry(self)
		output_entry = ttk.Entry(self)
		order_of_magnitude_entry = ttk.Entry(self)

		# Create check boxes
		exponential_checkbox = ttk.Checkbutton(self, text=exponential_checkbox_label_str, variable=plot_exponential)
		logarithmic_checkbox = ttk.Checkbutton(self, text=logarithmic_checkbox_label_str, variable=plot_logarithmic)
		sinusoidal_checkbox  = ttk.Checkbutton(self, text=sinusoidal_checkbox_label_str, variable=plot_sinusoidal)

		# Place labels
		input_label.grid(row=0, sticky='w')
		output_label.grid(row=1, sticky='w')
		order_of_magnitude_label.grid(row=2, sticky='w', padx=item_padding, pady=item_padding),

		# Place text entry fields
		input_entry.grid(row=0, column=1, padx=item_padding, pady=item_padding)
		output_entry.grid(row=1, column=1, padx=item_padding, pady=item_padding)
		order_of_magnitude_entry.grid(row=2, column=1, padx=item_padding, pady=item_padding)

		# Place checkboxes
		exponential_checkbox.grid(row=3, column=0, padx=item_padding, pady=item_padding)
		logarithmic_checkbox.grid(row=3, column=1, padx=item_padding, pady=item_padding)
		sinusoidal_checkbox.grid(row=3, column=2, padx=item_padding, pady=item_padding)

#=====================================================================================================

class Buttons(tk.Frame):
	def __init__(self, parent, controller):
		tk.Frame.__init__(self, parent)

		# Buttons
		plot_str = gui_config.get('buttons', 'plots_str')
		clear_str = gui_config.get('buttons', 'clear_str')

		# Setup buttons
		clear_button = ttk.Button(self, text=clear_str, command=clear_best_fits)
		plot_button = ttk.Button(self, text=plot_str, command=lambda:parse_args(order_of_magnitude_entry))

		# Place buttons in frame
		clear_button.grid(row=0, column=0, padx=item_padding, pady=item_padding)
		plot_button.grid(row=0, column=1, padx=item_padding, pady=item_padding)

# START SCRIPT
#=====================================================================================================

if plot.setup_io_file() == False:
	print('Please make sure that input.csv and output.csv exist, and are in the proper folder')
	sys.exit()

app = LeastSquaresWindow()
ani = animation.FuncAnimation(fig, animate, interval=1000)
app.mainloop()
