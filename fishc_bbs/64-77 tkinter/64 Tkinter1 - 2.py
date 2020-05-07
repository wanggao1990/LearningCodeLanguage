# 用对象的形式编程

import tkinter as tk


class App:

    def __init__(self,master):
        frame = tk.Frame(master)
        frame.pack(side = tk.LEFT, padx = 10, pady = 10)  # 默认 顶层 居中

        self.hi_there = tk.Button(frame, text='打招呼',fg='blue', bg = 'white' ,command = self.say_hi)
        self.hi_there.pack()

    def say_hi(self):
        print("大家好")


root = tk.Tk()
app = App(root)

root.mainloop()

