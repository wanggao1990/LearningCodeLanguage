# coding = UTF-8
# Python中类命名约定以大写字母开头  封装 多态 继承

####

class Ball:
    " 类是说明文档：一个简单的类例子 "
    # 属性
    #name = []

    # 方法

    def __init__(self,name):    # 重写其构造函数（显式），隐含只有self
        self.name = name        # 构造函数，只能返回None
    
    def setName(self,name):         # self类似c++中的this指针
        self.name = name            # 没有定义属性name，被添加到类中
    
    def kick(self):             
        print('我叫%s,谁踢我' %self.name)
        
    def run(self):
        print('我正在飞快的向前跑...')


#### 私有化 (概念同C++)，
#
# 定义私有变量或方法，在其变量名和方法名前加两个下划线"__"即可

class Person:
    __name = "大哥"

    def getName(self):            # 定义一个函数返回
        return self.__name
  

if __name__ == '__main__':  # 其他地方调用这个py模块，if失效； 在命令行运行
                            # 这个模块时，会把特殊变量__name__ 置为__main__

    a = Ball('球a')  # 这里需要一个参数，默认构造函数 __init__(self)被重写，需要参数
    a.kick()

    per = Person()
    #per.name        # 提示乜有name这个成员变量
    per.getName()

    print(per._Person__name)    # “伪私有”，私有化的成员名称变为 “_类名__成员名”
                                #  这里仍然可以访问
