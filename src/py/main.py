import matplotlib 
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2TkAgg
from matplotlib.figure import Figure
import matplotlib.animation as animation	
import tkinter as tk
from tkinter import ttk
import csv
import plot

from tkinter import messagebox

matplotlib.use("TkAgg")

# Strings
#-------------------------------
least_squares = "Least Squares"
start_page = "Start Page"
graph_2d = "Graph 2D"
graph_3d = "Graph 3D"
input_file_name = "Input file name:"
output_file_name = "Output file name:"
order_of_magnitude = "Order of magnitude:"
quit = "Quit"
plot_str = "Plot"
in_file_name = "../../data/input.csv"
out_file_name = "../../data/output.csv"


# Numbers
#-------------------------------
padding = 10
item_padding = 4

# Other variables
#-------------------------------
LARGE_FONT=("Verdana", 12)

# Setup figure
fig = Figure(figsize=(6,4), dpi=100)
ax = fig.add_subplot(111)

best_fits_x = []
best_fits_y = []

# FUNCTIONS
#=====================================================================================================

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
		
		# Call code that calls C++ to write out to file
		plot.curve_fit(in_file_name, out_file_name, i)

		# Read in from output.csv file
		output_data = open(out_file_name)
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

#-----------------------------------------------------------------------------------------------------

# Display the plots
def animate(i):
	x_in_list = []
	y_in_list = []

	input_data = open(in_file_name)
	
	csv_f0 = csv.reader(input_data)

	# Read in input data (scatter plot)
	for row in csv_f0:
	  x_in_list.append(float(row[0]))
	  y_in_list.append(float(row[1]))
	

	ax.clear()	

	# Plot the original data
	ax.plot(x_in_list,y_in_list,'ro',label="$f(x)\\approx sin(x)$")	

	# Plot all best curves
	for i in range(len(best_fits_x)):
		ax.plot(best_fits_x[i],best_fits_y[i], label="$f(x)$")

	# Give figure a title
	fig.subplots_adjust(top=0.85)
	fig.suptitle('Least Squares Best Fit:', fontsize=14, fontweight='bold')
	

	# Prepare legend
	legend = ax.legend(loc='upper left', shadow=True)
	frame = legend.get_frame()
	frame.set_facecolor('0.90')
	
	# Set legend settings
	for label in legend.get_texts():
		label.set_fontsize('medium')

	for label in legend.get_lines():
		label.set_linewidth(1.5) 
	
	ax.set_title('input.csv')
	ax.set_xlabel('$x$')
	ax.set_ylabel('$y$')

	# Position axis labels
	ax.yaxis.set_label_coords(-0.025,1.05)
	ax.xaxis.set_label_coords(1.05, -0.025)
	#ax.axis('equal')

	
# MAIN WINDOW
#=====================================================================================================
class LeastSquares(tk.Tk):
    def __init__(self,*args,**kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)

        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}
		
 		# Add pages (frames) to window
        for F in (StartPage, GraphPage2D, GraphPage3D):
            frame = F(container, self)
            self.frames[F] = frame
            frame.grid(row=0, column=0, sticky="nsew")
            
        
		# Set window title and show start page
        self.title(least_squares)         
        self.show_frame(StartPage)

	# Displays a frame
    def show_frame(self,cont):
        frame = self.frames[cont]
        frame.tkraise()


# START PAGE
#=====================================================================================================
class StartPage(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self,parent)

		# Create labels
        input_label = ttk.Label(self, text=input_file_name)
        output_label = ttk.Label(self, text=output_file_name)
        order_of_magnitude_label = ttk.Label(self, text=order_of_magnitude)

		# Create text entry fields
        input_entry = ttk.Entry(self)
        output_entry = ttk.Entry(self)
        order_of_magnitude_entry = ttk.Entry(self)

        # Create buttons
        graph_2d_button = ttk.Button(self, text=graph_2d, command=lambda:controller.show_frame(GraphPage2D))
        graph_3d_button = ttk.Button(self, text=graph_3d, command=lambda:controller.show_frame(GraphPage3D))
        quit_button = ttk.Button(self, text=quit, command=self.quit)

		# Place labels
        input_label.grid(row=0, sticky='w')
        output_label.grid(row=1, sticky='w')
        order_of_magnitude_label.grid(row=2, sticky='w')

		# Place text entry fields
        input_entry.grid(row=0, column=1, padx=item_padding, pady=item_padding)
        output_entry.grid(row=1, column=1, padx=item_padding, pady=item_padding)
        order_of_magnitude_entry.grid(row=2, column=1, padx=item_padding, pady=item_padding)

		# Place buttons
        graph_2d_button.grid(row=3, column=0, sticky='w', padx=item_padding, pady=item_padding)
        graph_3d_button.grid(row=3, column=1, sticky='e', padx=item_padding, pady=item_padding)


# Graph Page (2D)
#=====================================================================================================
class GraphPage2D(tk.Frame):
	def __init__(self, parent, controller):
		tk.Frame.__init__(self, parent)

		# Create toolbar
		canvas = FigureCanvasTkAgg(fig, self)
		canvas.show()
		canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)
		toolbar = NavigationToolbar2TkAgg(canvas, self)
		toolbar.update()
		canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

		# Create Buttons
		button = ttk.Button(self, text=start_page, command=lambda:controller.show_frame(StartPage))
		button.pack()

		order_of_magnitude_label = ttk.Label(self, text=order_of_magnitude)
		order_of_magnitude_label.pack()

		order_of_magnitude_entry = ttk.Entry(self)
		order_of_magnitude_entry.pack()

		plot_button = ttk.Button(self, text=plot_str, command=lambda:parse_args(order_of_magnitude_entry.get()))
		plot_button.pack()


# Graph Page (3D)
#=====================================================================================================
class GraphPage3D(tk.Frame):
	def __init__(self, parent, controller):
		tk.Frame.__init__(self, parent)
		label = tk.Label(self, text=graph_3d, font=LARGE_FONT)
		label.pack(pady=padding, padx=padding)
		button = ttk.Button(self, text=start_page, command=lambda:controller.show_frame(StartPage))
		button.pack()


# START SCRIPT
#=====================================================================================================
app = LeastSquares()
ani = animation.FuncAnimation(fig, animate, interval=1000)
app.mainloop()


