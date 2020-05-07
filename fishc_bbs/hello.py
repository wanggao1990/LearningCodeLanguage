# 容器 	数据的封装
# 函数 	语句的封装
# 类	方法和属性的封装
#
#  模块 就是程序。  每一个.py文件都是一个模块。


def hi():
    print('I love China!')

def say():
    print('saying something!')



#def test():
#    hi()
#    say()
#
#test()  # 为了测试这2个函数

####  当导入这个模块的时候，会运行 test()，不符合我们的需求。


#  这里就是为了区分是在模块中（import）运行  module.__name__ == 'modulename‘
#  
#  还是在命令行中（__name__ == '__main__'）
#


# 在模块代码中进行测试
if __name__ == '__main__':  # 其他地方调用这个py模块，if失效； 在命令行运行
                            # 这个模块时，会把特殊变量__name__ 置为__main__

    def test():
        hi()
        say()

    
    test()  # 为了测试这2个函数
