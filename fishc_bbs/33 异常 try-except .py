####  异常处理

#   第一种形式
#   try:
#       检测范围
#   except Exception[as reason]:
#       出现异常后的处理代码

try:
    int('abc')      # 没有对该错误类型进行捕捉直接trac back，
    num = 1 + '1'   # 捕捉到第一个异常，try的后续代码就不再执行
    f = open('我是一个文件.txt')
    print(f.read())
    f.close()
except OSError as errorInfo:                    # 详细的错误信息
    print('文件出错啦T_T => ' + str(errorInfo))
except TypeError as errorInfo:                  # 一个try可以对应多个except语句
    print('文件出错啦T_T => ' + str(errorInfo))


try:
    num = 1 + '1'

    f = open('我是一个文件.txt')
    print(f.read())
    f.close()
except (OSError,TypeError):          # 小括号，统一处理多类异常             
    print('文件出错啦T_T')


#   第二种形式
#   try:
#       检测范围
#   except Exception[as reason]:
#       出现异常后的处理代码
#   finally:
#       无论如何都会执行的代码
try:
    f = open('我是一个文件.txt','w')
    print(f.write('我存在了'))
    num = 1+'1'                     # 遇到错误，文件没有关闭
    f.close()
except (OSError,TypeError):                    
    print('文件出错啦T_T')
finally:
    f.close()                       # 本来文件不存在，就不能关闭，怎么处理？


## raise 手动给出异常
    
raise ZeroDivisionError('除数为0的异常')   # ZeroDivisionError: 除数为0的异常
