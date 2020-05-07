
#  else 可以和while语句搭配使用

def showMaxFactor(num):  # 最大公约数
    count = num //2 
    while count>1:
        if num % count == 0:
            print("%d的最大公约数是%d" %(num,count))
            break
        count -= 1
    else:                           # 整个while循环都执行了一遍，没有break 
        print('%d是素数' % num)

num =  int(input('输入一个数:'))
showMaxFactor(num)



#  else 可以和异常语句搭配使用

try:
    int('abc')                  # 找到对应的异常，抛出错误
   # int('132')                  
except ValueError as info:      # 没有异常，执行else
    print('出错了 '+ str(info))
else:
    print('没有异常')


####  文件本来不存在， 最后关闭

try:
    f = open('data.txt')
    for each_line in f:
         print(each_line)
except OSError as info:                    
    print('文件出错啦T_T '+ str(info))
finally:
    f.close()       # 没有改文件。关闭出错

# 解决一
try:
    with open('data.txt') as f:     # with语句，会自动关闭文件
        for each_line in f:
             print(each_line)
except OSError as info:                    
    print('文件出错啦T_T '+ str(info))

# 解决二
try:
    f = open('data.txt')
    for each_line in f:
         print(each_line)
except OSError as info:                    
    print('文件出错啦T_T '+ str(info))
finally:
    if f in locals():       # 文件对象存在当前变量符号表的话，说明打开成功
        f.close()      


###  with语句处理多个项目的时候，可以用逗号隔开一条语句
#
#           with A() as a:
#               with B() as b:
#                   suite
#   改为：
#           with A() as a, B() as b:
#               suite
