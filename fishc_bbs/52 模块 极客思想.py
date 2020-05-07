# 建议使用python自带的标准库  
# 
# 1、 documentation


# 2、shell
import timeit

print(timeit.__doc__)  #使用文档

print(dir(timeit))	# 所有方法

print(timeit.__all__)  #可调用的方法（不一定多有模块都有all方法）

from timeit import *   # 只能导入 __all__ 包含的方法


print(timeit.__file__)  # 源代码 路径


# 3、help函数