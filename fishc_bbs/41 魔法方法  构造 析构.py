
### __init__(self[, ...])
#
#   类在实例化对象时，被自动调用的隐含函数

class Retangle:
    def __init__(self,x,y):         # 只能返回None
        self.x = x                  # 只有在需要初始化的时候，才重写
        self.y = y

    def getPeri(self):
        return 2*(self.x + self.y)

    def getArea(self):
        return self.x * self.y

rect = Retangle(3,4)
print(rect.getPeri())
print(rect.getArea())

### __new__(cls[, ...])
#
#   类在实例化对象时，被自动调用的第一个方法
#   第一个是类，后面的参数全部传给 __init__.  主要用于继承不可变对象

class CapStr(str):
    def __new__(cls,string):
        string = string.upper()
        return str.__new__(cls,string)

a = CapStr('I love You!')
print(a)


### __del__(self)
#
#  对象被销毁时，（垃圾回收机制）被销毁。  不等同于 del(object)

class C:

    def __new__(cls):
        print("我的__new__方法")
    
    def __init__(self):
        print('我的__init__方法，我被调用了')

    def __del__(self):
        print('我的__del__方法，我被调用了')

c1 = C()
c2 = c1
c3 = c2
del c3
del c2
del c1   # 当所有应用被删除时，才会析构
