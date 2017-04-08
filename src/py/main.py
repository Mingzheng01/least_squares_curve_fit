import matplotlib 
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation	
import tkinter as tk
from tkinter import ttk
import csv
import plot
import configparser

from tkinter import messagebox

matplotlib.use("TkAgg")

# Strings
#-------------------------------
config = configparser.ConfigParser()
config
config.read("../../ini/properties.ini")


'''GUI STRING / NUMBERS FROM PROPERTIES FILE'''
'''==================================================================================================='''
# titles
least_squares = config.get('titles', 'least_squares_window_title')
plot_title = config.get('titles', 'plot_title')

# labels
input_file_name = config.get('labels', 'input_file_name_label_str')
output_file_name = config.get('labels', 'output_file_name_label_str')
order_of_margnitude_label_str = config.get('labels', 'order_of_margnitude_label_str')

# buttons
plot_str = config.get('buttons', 'plots_str')
clear_str = config.get('buttons', 'clear_str')

# directories
in_file_directory = config.get('directories', 'input_directory')
out_file_directory = config.get('directories', 'output_directory')
x_axis_label = config.get('axes', 'x_axis_label')
y_axis_label = config.get('axes', 'y_axis_label')

# Other variables
#-------------------------------
font_name = config.get('text', 'font_name')
font_size = config.getint('text', 'font_size')
LARGE_FONT=(font_name, font_size)
'''==================================================================================================='''


# Numbers
#-------------------------------
padding = 10
item_padding = 4

# Setup figure
fig = Figure(figsize=(6,4), dpi=100)
ax = fig.add_subplot(111)

# Keep track of points on best fit curve to plot
best_fits_x = []
best_fits_y = []

# FUNCTIONS
#=====================================================================================================

'''
TODO - This function will be replaced with code that 
calls C or C++ code and will then build the list of points
'''
def REPLACE_ME(in_file_directory, out_file_directory, order):
	# Call code that calls C++ to write out to file
	plot.curve_fit(in_file_directory,out_file_directory, order)

	# Read in from output.csv file
	output_data = open(out_file_directory)
	csv_f1 = csv.reader(output_data)

	# Declare temporary lists for holding most recent X,Y pairs from output.csv
	temp_x = []
	temp_y = []

	# Read in output data (best fit plot)
	for row in csv_f1:
	  temp_x.append(float(row[0]))
	  temp_y.append(float(row[1]))

	# Add Xs to X matrix, and Ys to Y matrix to be displayed later
	best_fits_x.append(temp_x)
	best_fits_y.append(temp_y)

	# RETURN TWO 2D matrices

#-----------------------------------------------------------------------------------------------------

# Set best fit matrices to empty lists
def clear_best_fits():
	global best_fits_x 
	global best_fits_y

	best_fits_x = []
	best_fits_y = [] 

#-----------------------------------------------------------------------------------------------------

def parse_args(arguments):
	# Clear matrix of best fits to avoid repeating plots	
	clear_best_fits() 
	
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
		REPLACE_ME(in_file_directory,out_file_directory, i)
			

#-----------------------------------------------------------------------------------------------------

# Display the plots
def animate(i):
	x_in_list = []
	y_in_list = []

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
	for i in range(len(best_fits_x)):
		ax.plot(best_fits_x[i],best_fits_y[i], label="$f(x)$")

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
	ax.yaxis.set_label_coords(-0.025,1.05)
	ax.xaxis.set_label_coords(1.05, -0.025)
	#ax.axis('equal')

	
# MAIN WINDOW Class
#=====================================================================================================
class LeastSquares(tk.Tk):
    def __init__(self,*args,**kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)

        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}

        frame = GraphPage(container, self)        
        self.frames[GraphPage] = frame   
        frame.grid(row=0, column=0, sticky="nsew") 
        
		# Set window title and show start page
        self.title(least_squares)         
        self.show_frame(GraphPage)

	# Displays a frame
    def show_frame(self,cont):
        frame = self.frames[cont]
        frame.tkraise()


# Graph Page (2D) Class
#=====================================================================================================
class GraphPage(tk.Frame):
	def __init__(self, parent, controller):
		tk.Frame.__init__(self, parent)

		# Create toolbar
		canvas = FigureCanvasTkAgg(fig, self)
		
		# Create toolbar
		toolbar = NavigationToolbar2TkAgg(canvas, self)
		toolbar.update()
		canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

		# Pack options into canvas
		f1 = Options(controller, self)
		f1.pack()

		# Show canvas
		canvas.show()


# Options Frame Class that will go within the Graph Page
#=====================================================================================================
class Options(tk.Frame):
	def __init__(self, parent, controller):
		tk.Frame.__init__(self, parent)

		'''
		TODO - Reorder code, declarations first, all .grid() calls after 
		so that it is more clear the layout
		'''

		# Create labels
		input_label = ttk.Label(self, text=input_file_name)
		output_label = ttk.Label(self, text=output_file_name)

		var1 = 1
		var2 = 2
		logarithmic_checkbox = ttk.Checkbutton(self, text="logarithmic", variable=var1)
		exponential_checkbox = ttk.Checkbutton(self, text="exponential", variable=var2)

		# Create text entry fields
		input_entry = ttk.Entry(self)
		output_entry = ttk.Entry(self)

		# Place labels
		input_label.grid(row=0, sticky='w')
		output_label.grid(row=1, sticky='w')

		# Place text entry fields
		input_entry.grid(row=0, column=1, padx=item_padding, pady=item_padding)
		output_entry.grid(row=1, column=1, padx=item_padding, pady=item_padding)

		order_of_magnitude_label = ttk.Label(self, text=order_of_margnitude_label_str)
		order_of_magnitude_label.grid(row=2, sticky='w', padx=item_padding, pady=item_padding), 

		order_of_magnitude_entry = ttk.Entry(self)
		order_of_magnitude_entry.grid(row=2, column=1, padx=item_padding, pady=item_padding) 

		logarithmic_checkbox.grid(row=3, column=0, padx=item_padding, pady=item_padding)
		exponential_checkbox.grid(row=3, column=1, padx=item_padding, pady=item_padding)

		clear_button = ttk.Button(self, text=clear_str, command=clear_best_fits)
		clear_button.grid(row=4, column=0, padx=item_padding, pady=item_padding)		

		plot_button = ttk.Button(self, text=plot_str, command=lambda:parse_args(order_of_magnitude_entry.get()))
		plot_button.grid(row=4, column=1, padx=item_padding, pady=item_padding)


# START SCRIPT
#=====================================================================================================
app = LeastSquares()
ani = animation.FuncAnimation(fig, animate, interval=1000)
app.mainloop()


