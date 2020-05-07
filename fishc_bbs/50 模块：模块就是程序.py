# 容器 	数据的封装
# 函数 	语句的封装
# 类	方法和属性的封装
#
#  模块 就是程序。  每一个.py文件都是一个模块。


def say():
    print('I love China!')


# 在当前目录下 保存 hello.py 文件。
# import hell0
# 执行 hi(),  提示 不存在 hi。
#  需要命名空间， hello.hi()才能正常执行。
#  
#  类似 import time  所有相关函数需要通过 time.函数名 调用
#  


## 第一种： import 模块名
import hello 
hello.hi()
print()

## 第二种：from 模块名 import 函数名  
# 
# 还有一种通配符 from 模块名 import *  加载所有函数，不需要命名空间 
#  但是容易造成不同模块同名函数混淆。不建议用这种方式
from hello import say,hi
say()
hi()
print()

## 第三种：import 模块名 as 新名字
#
# 名字简写，也避免了多个模块同名函数混淆 
import hello as hl 
hl.say()
hl.hi()
