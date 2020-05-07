
## 描述符  将某种特殊类型的类的实例指派给另一个类的属性
#
#  特殊类型要求至少实现下面的一个中的一个
#   __get__(self,instance,owner)    - 访问属性，返回属性的值
#   __set__(self,instance,value)    - 在属性分配操作中调用，不返回任何值
#   __delete__(self,instance)       - 控制删除操作，不返回任何值

###############################################################################
# 回顾在属性控制中，用到了 property()函数

class C:
    def __init__(self,size=10):
        self.size = size

    def getSize(self):
        return self.size

    def setSize(self,value):
        self.size = value

    def delSize(self):
        del self.size

    x = property(getSize,setSize,delSize)

c1 = C()
print(c1.getSize())
print(c1.x)         # 这里c1.x是取值，会从property(getSize,setSize,delSize)找到匹配的函数 c1.getSize()

c1.x = 18           # 这里c1.x是赋值，对应方法 c1.setSize(18)
print(c1.size)
print(c1.getSize())
print()


###############################################################################
##### 
#####  下面开始实现 描述符
#####
class MyDecriptor:
    def __get__(self,instance,owner):
        print('getting...',self,instance,owner)

    def __set__(self,instance,value):
        print('setting...',self,instance,value)

    def __delete__(self,instance):
        print('deleting...',self,instance)


## 描述符类（至少实现了get、set、del中一个方法的类）
##  将描述类赋值给一个类的属性（静态成员属性）
##
class Test:
    x = MyDecriptor()  # 含有特殊类型的实例，指派给一个类Test的属性x  


test = Test()  # 
test.x
test.x = 'X-man'
del test.x

print()

##############################################################################
# 自己实现property描述符函数
class MyProperty:
    def __init__(self, fget = None, fset = None, fdel = None):
        self.fget = fget
        self.fset = fset
        self.fdel = fdel

    def __get__(self,instance,owner):
        return self.fget(instance)

    def __set__(self,instance,value):
        self.fset(instance,value)

    def __delete__(self,instance):
        self.fdel(instance)

class C:
    """docstring for C"""
    def __init__(self):
        self._x = None

    def getX(self):
        return self._x

    def setX(self,value):
        self._x = value

    def delX(self,value):
        del self._x

    x = MyProperty(getX,setX,delX)

        
c = C()
c.x = 'X-man'
print(c.x)
print(c._x)
del c._x

print()

##############################################################################
# 定义一个温度类，2个描述符类用于描述摄氏度和华氏度两个属性
# 要求两个属性能自动转换（给摄氏度复制，打印华氏度是自动转换后的结果）
# wald = sef

class Celsius():
    def __init__(self, value = 26.0):
        self.value = float(value)

    def __get__(self,instance,owner):
        return self.value

    def __set__(self,instance,value):
        self.value = value

class Fahrenheit:
    def __get__(self,instance,owner):
        return instance.cel*1.8 + 32

    def __set__(self,instance,value):
        instance.cel = (float(value)-32)/1.8       

class Temperature:
    cel = Celsius()
    fah = Fahrenheit()


temp = Temperature()    # 实例化对象，首先 temp成员属性 cel 通过__init__,初始化 cel.value =26, 通过set方法，得到temp.cel = 26.0
                        #             接着 temp成员属性 fah 通过__set__方法，参数通过 实例temp传递cel值，计算得到 temp.fah = 78.8
       
print(temp.cel)      # 这里是 调用cel的__get__, 输出 26
print(temp.fah)      # 这里是 调用fah的__get__, 输出 78.8

temp.cel = 30;      # 调用cel的__set__, 设置 temp.cel = 30
print(temp.fah)     # 调用fah的__set__, 设置 通过实例传递temp.cel = 30，计算temp.fah = 86， 再通过__get__返回值 

temp.fah = 86;      # 调用fah的__set__，传递数值86， 通过实例，给temp.cel赋值 30
print(temp.cel)     # 这里是 调用cel的__get__, 输出 30
