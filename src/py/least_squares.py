from tkinter import *
import sys
import plot

def show_entry_fields():
	in_file_name = e1.get()
	out_file_name = e2.get()
	
	#TEMPORARY
	in_file_name = '../../data/input.csv'
	out_file_name = '../../data/output.csv'
	plot.plot(in_file_name, out_file_name, int(e3.get()))
		
# Main window
master = Tk()
Label(master, text="Input file name: ").grid(row=0)
Label(master, text="Output file name:").grid(row=1)
Label(master, text="Order to curve:").grid(row=2)

e1 = Entry(master)
e2 = Entry(master)
e3 = Entry(master)

e1.grid(row=0, column=1)
e2.grid(row=1, column=1)
e3.grid(row=2, column=1)

Button(master, text='Quit', command=master.quit).grid(row=3, column=0, sticky=W, pady=4)
Button(master, text='Plot', command=show_entry_fields).grid(row=3, column=1, sticky=W, pady=4)

mainloop()