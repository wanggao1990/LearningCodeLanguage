# label button

import tkinter as tk

##
root = tk.Tk()

textLabel = tk.Label(root, text="限制内容！")
textLabel.pack(side='left')

photo = tk.Image(file = "timg.gif") # BitmapImage can be used for X11 bitmap data. 
                                    # PhotoImage can be used for GIF and PPM/PGM color bitmaps. 
imageLabel = tk.Label(root,image = photo)
imageLabel.pack(side='right')

root.mainloop()


