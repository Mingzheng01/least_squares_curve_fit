import matplotlib

# Must run matplotlib.use() before backends so Mac does not complain
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation
import tkinter as tk
from tkinter import ttk
from tkinter import IntVar
from tkinter import StringVar
import plot
import configparser
from tkinter import messagebox
import file_io

# Main Window Class
#=====================================================================================================
class LeastSquaresWindow(tk.Tk):
    def __init__(self, *args,**kwargs):
        tk.Tk.__init__(self, *args, **kwargs)

		# Get configParsers for reading in strings from .ini 
        properties_config = configparser.ConfigParser()
        properties_config.read("../../ini/properties.ini")

		# Read in title
        least_squares = properties_config.get('titles', 'least_squares_window_title')
	
        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)
        container.grid_rowconfigure(0, weight=1)

        self.frames = {}
        frame = GraphPage(container, self, properties_config)
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
	def __init__(self, parent, controller, properties_config):
		tk.Frame.__init__(self, parent)

		# font related
		font_name = properties_config.get('text', 'font_name')
		font_size = properties_config.getint('text', 'font_size')
		LARGE_FONT=(font_name, font_size)
		
		# titles
		plot_title = properties_config.get('titles', 'plot_title')

		# Set up figure and plot for plotting
		fig = Figure(figsize=(6,4), dpi=100)
		ax = fig.add_subplot(111)

		# Create graph canvas
		canvas = FigureCanvasTkAgg(fig, self)

		# Give figure a title
		fig.subplots_adjust(top=0.85)
		fig.suptitle(plot_title, fontsize=14, fontweight='bold')

		# Have equal units on axis
		#ax.axis('equal')

		# Create toolbar for graph
		toolbar = NavigationToolbar2TkAgg(canvas, self)
		toolbar.update()

		# Create other frames that will go into this frame
		options_frame = Options(controller, self, properties_config, canvas, ax)
		buttons_frame = Buttons(controller, self, properties_config, options_frame, canvas, ax)

		# Plot original data
		buttons_frame.plot_fits(properties_config, options_frame, canvas, ax)

		# Pack all frames into this frame
		canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
		options_frame.pack()
		buttons_frame.pack()

		# Show canvas
		canvas.show()


# Options Frame Class that will go within the Graph Page
#=====================================================================================================

class Options(tk.Frame):
	def __init__(self, parent, controller, properties_config, canvas, ax):
		tk.Frame.__init__(self, parent)

		# String variables from gui.ini
		input_file_name_label_str = properties_config.get('labels', 'input_file_name_label_str')
		order_of_magnitude_label_str = properties_config.get('labels', 'order_of_magnitude_label_str')
		logarithmic_checkbox_label_str = properties_config.get('labels', 'logarithmic_checkbox_label_str')
		exponential_checkbox_label_str = properties_config.get('labels', 'exponential_checkbox_label_str')
		sinusoidal_checkbox_label_str = properties_config.get('labels', 'sinusoidal_checkbox_label_str')
		item_padding = properties_config.get('padding', 'item_padding')
		default_input_directory = properties_config.get('directories', 'input_directory')	
		self.input_file_directory = default_input_directory

		# Create labels
		input_label = ttk.Label(self, text=input_file_name_label_str)
		order_of_magnitude_label = ttk.Label(self, text=order_of_magnitude_label_str)

		self.input_directory = StringVar()
		
		# Create text entry fields
		self.input_entry = ttk.Entry(self, textvariable=self.input_directory)
		self.order_of_magnitude_entry = ttk.Entry(self)
		self.input_directory.set(default_input_directory)

		# Set these as boolean-ish values to track checkbox values
		self.plot_exponential = IntVar()
		self.plot_logarithmic = IntVar()
		self.plot_sinusoidal = IntVar()

		# Create check boxes
		exponential_checkbox = ttk.Checkbutton(self, text=exponential_checkbox_label_str, variable=self.plot_exponential)
		logarithmic_checkbox = ttk.Checkbutton(self, text=logarithmic_checkbox_label_str, variable=self.plot_logarithmic)
		sinusoidal_checkbox  = ttk.Checkbutton(self, text=sinusoidal_checkbox_label_str, variable=self.plot_sinusoidal)

		# Place labels
		input_label.grid(row=0, sticky='w')
		order_of_magnitude_label.grid(row=2, sticky='w', padx=item_padding, pady=item_padding),

		# Place text entry fields
		self.input_entry.grid(row=0, column=1, padx=item_padding, pady=item_padding)
		self.order_of_magnitude_entry.grid(row=2, column=1, padx=item_padding, pady=item_padding)

		# Place checkboxes
		exponential_checkbox.grid(row=3, column=0, padx=item_padding, pady=item_padding)
		logarithmic_checkbox.grid(row=3, column=1, padx=item_padding, pady=item_padding)
		sinusoidal_checkbox.grid(row=3, column=2, padx=item_padding, pady=item_padding)

#=====================================================================================================

class Buttons(tk.Frame):
	def __init__(self, parent, controller, properties_config, options_frame, canvas, ax):
		tk.Frame.__init__(self, parent)

		# Buttons
		plot_str = properties_config.get('buttons', 'plots_str')
		clear_str = properties_config.get('buttons', 'clear_str')
		item_padding = properties_config.get('padding', 'item_padding')

		# Setup buttons
		clear_button = ttk.Button(self, text=clear_str, command=lambda:self.clear_all(properties_config, options_frame, canvas, ax))
		plot_button = ttk.Button(self, text=plot_str, command=lambda:self.plot_fits(properties_config, options_frame, canvas, ax))

		# Place buttons in frame
		clear_button.grid(row=0, column=0, padx=item_padding, pady=item_padding)
		plot_button.grid(row=0, column=1, padx=item_padding, pady=item_padding)

#-----------------------------------------------------------------------------------------------------

	# Set best fit matrices to empty lists
	def clear_all(self, properties_config, options_frame, canvas, ax):
		ax.clear()

		# labels
		x_axis_label = properties_config.get('axes', 'x_axis_label')
		y_axis_label = properties_config.get('axes', 'y_axis_label')

		# Set labels on graph
		ax.set_title(options_frame.input_directory.get())
		ax.set_xlabel(x_axis_label)
		ax.set_ylabel(y_axis_label, rotation=0)

		# Position axis labels
		ax.yaxis.set_label_coords(-0.025, 1.05)
		ax.xaxis.set_label_coords(1.05, -0.025)

		canvas.draw()

#-----------------------------------------------------------------------------------------------------

	def plot_fits(self, properties_config, options_frame, canvas, ax):
		# For accessing x, y, and function names by index number, respectively
		x = 0
		y = 1
		n = 2

		self.clear_all(properties_config, options_frame, canvas, ax)

		input_file_directory = options_frame.input_entry.get()

		if file_io.is_valid_input_file(input_file_directory) == False:	
			messagebox.showinfo("Invalid Argument", "The input file is not a valid CSV file")
			return
	
		org_data = plot.original_data(input_file_directory)

		# Plot original data
		if len(org_data) > 0:
			ax.plot(org_data[x], org_data[y],'ro', label=org_data[n])

		# Get desired polynomial order of magnitude from text entry
		order = options_frame.order_of_magnitude_entry.get()

		# Make sure the user typed something
		if order != '':
			
			try:
				# Convert string to integer (will error out if letters are entered)
				order = int(order)

				# Only acceppt integers between 0 and 10 inclusive
				if order > 10 or order < 0:
					raise ValueError()

				# Get the polynomial data
				else:
					poly_fit = plot.polynomial_fit(input_file_directory, order)

				# If data points came back, plot them
				if len(poly_fit) > 0:
					ax.plot(poly_fit[x], poly_fit[y], 'b', label=poly_fit[n])

			except ValueError:
				messagebox.showinfo("Invalid Argument", "Only enter integers between 0-10")


		exp_fit = []
		log_fit = []
		sin_fit = []

		# Get data exponential, logarthmic, and sinusoidal data from csv files
		# If the check boxes are checked, and data came back, plot the respective curve
		if options_frame.plot_exponential.get() == 1:			
			exp_fit = plot.exponential_fit(input_file_directory)

			if len(exp_fit) > 0:	
				ax.plot(exp_fit[x], exp_fit[y], 'g',label=exp_fit[n])

		if options_frame.plot_logarithmic.get() == 1:
			log_fit = plot.logarithmic_fit(input_file_directory)

			if len(log_fit) > 0:		
				ax.plot(log_fit[x], log_fit[y], 'm', label=log_fit[n])

		if options_frame.plot_sinusoidal.get() == 1:		
			sin_fit = plot.sinusoidal_fit(input_file_directory)

			if len(sin_fit) > 0:
				ax.plot(sin_fit[x], sin_fit[y], 'k',label=sin_fit[n])
	

		# Prepare legend
		legend = ax.legend(loc='upper left', shadow=True)
		frame = legend.get_frame()
		frame.set_facecolor('0.90')

		# Set legend settings
		for label in legend.get_texts():
			label.set_fontsize('medium')

		for label in legend.get_lines():
			label.set_linewidth(1.5)

		canvas.draw()

# START SCRIPT
#=====================================================================================================
if file_io.setup_io_file() == False:
	messagebox.showinfo('Please make sure that input.csv and output.csv exist, and are in the proper folder')
	sys.exit()

app = LeastSquaresWindow()
app.mainloop()
