from tkinter import *
master = Tk()

male = IntVar()
female = IntVar()

''' Display values of checkboxes '''
def var_states():
   print("male: %d,\nfemale: %d" % (male.get(), female.get()))

# Labels
Label(master, text="Your sex:").grid(row=0, sticky=W)

Checkbutton(master, text="male", variable=male).grid(row=1, sticky=W)
Checkbutton(master, text="female", variable=female).grid(row=2, sticky=W)

# Buttons
Button(master, text='Show', command=var_states).grid(row=3, sticky=W, pady=4)
Button(master, text='Quit', command=master.quit).grid(row=4, sticky=W, pady=4)

#-----------------

mainloop()
