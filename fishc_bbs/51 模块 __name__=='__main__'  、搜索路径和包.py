
def c2f(cel):
	return cel *1.8 +32

def f2c(fah):
	return (fah-32)/1.8



# # 测试这2个模块

# def test():
# 	print("测试：0摄氏度 = %.2f华氏度" % c2f(0))
# 	print("测试：0华氏度 = %.2f摄氏度" % f2c(0))


# test()  # 为了测试这2个函数

# ####  当调用这个模块的时候，会运行 test()，不符合我们的需求。


#################################################################################
#  这里就是为了区分是在导入（import）后的模块中运行  ( module.__name__ == 'modulename‘   )
#  
#  还是在当前模块中运行（__name__ == '__main__'）
#


# 在模块代码中进行测试
if __name__ == '__main__':  # 其他地方调用这个py模块，if失效； 在命令行运行
                            # 这个模块时，会把特殊变量__name__ 置为__main__

	def test():
		print("测试：0摄氏度 = %.2f华氏度" % c2f(0))
		print("测试：0华氏度 = %.2f摄氏度" % f2c(0))

	test() 

#################################################################################
### 搜索路径
#
import sys
print(sys.path)

	# ['E:\\ProgramData\\Python\\fishc_bbs', 
	# 'E:\\Program Files\\Python\\Python35-32\\python35.zip', 
	# 'E:\\Program Files\\Python\\Python35-32\\DLLs', 
	# 'E:\\Program Files\\Python\\Python35-32\\lib', 
	# 'E:\\Program Files\\Python\\Python35-32', 
	# 'E:\\Program Files\\Python\\Python35-32\\lib\\site-packages']

#
# 默认会在上述路径中查找要import的py文件
# 
import os
currentDir = os.getcwd(); print(currentDir)

sys.path.append(currentDir)   # 对 sys.path 增加当前目录； 该修改仅在当前模块中有效。




#################################################################################
### 包 （package）
#
#  当有大量的py文件时，不可能全部导入，因此有了包的概念
#  1、创建一个文件夹，存放相关的模块，文件夹的名字就是包的名字
#  2、在文件夹中创建一个__init__.py的文件，内容可以为空
#  3、将相关模块文件放入到该文件夹下
#
#  导入的时候 增加一层文件夹名 ， 如 'import folder.module as ml'
#  								再调用相关函数，  ’ml.func()‘即可

import pk1.hello as my
my.hi()