
#  Tk + interface = Tkinter

import tkinter as tk

app = tk.Tk()   # top-level 或者 root 窗口

app.title("Tkinter Demo")

theLabel = tk.Label(app,text = "我的第二个窗口程序")  # 字符串
theLabel.pack() # 自动调整位置



app.mainloop()  # 窗口主事件循环
