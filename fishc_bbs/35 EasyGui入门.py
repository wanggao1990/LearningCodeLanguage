import easygui

# from easygui import *
# 全部加入后，可以不用写命名空间， 如 msgbox('..')即可

import easygui as gui    # 给一个包命名空间的别名,为了简写函数

# easygui.msgbox('嘿嘿~')


import sys

while 1:
    # 消息框,默认为ok按钮,可改写按钮上的文字，且点击后返回设定文字 
    res = gui.msgbox('欢迎进入第一个EasyGui界面小游戏',
                     image='timg.gif',ok_button = 'okkk') #参数 image 仅支持 gif图像

    if res != 'okkk':   # 按钮返回字符串 OK
        sys.exit(0)

    msg = "你想学什么知识呢?"
    title = "小游戏互动"
    choices = ['贪念爱',"编程",'OOXX','琴棋书画']

    choice = gui.choicebox(msg,choices = choices) # 不想输入第二个参数标题，可以用关键字参数选定第三个参数 

    #choice = gui.choicebox(msg,title,choices)   # 选择OK，结果是 choice中的一个字符串；
                                                # 否则是 None

    gui.msgbox("你的选择是：" + str(choice),"结果")  # 这里必须用str转
                                                    # 可以打印 None
    
    msg = "希望重新开始游戏吗?"
    title = "请选择"

    res = gui.ccbox(msg,title)    # 显示 Continue/Cancle对话框 (结果为 1 或者 0)

    if  res:
        pass                    # 什么都不干,直接进入下一个循环
    else:
        sys.exit(0)

