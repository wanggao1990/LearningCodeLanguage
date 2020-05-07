## 一些相关的内置函数

### issubcalss(class, classinfo)
##
##  检查 class是否为classinfo（多个类的元组）的子类

class A:
    pass

class B(A):
    pass

class C(B):
    pass

class D(A):
    pass

print(issubclass(B,A))      # True
print(issubclass(C,A))      # True
print(issubclass(C,B))      # True
print(issubclass(C,D))      # False
print(issubclass(C,(A,B)))  # True

print(issubclass(C,object)) # 所有类 都继承于 object
print()

### isinstance(object, classinfo)
##
##    检查实例object是否属于class（或多各类的元组）

b = B()
print(isinstance(b,B))      # True
print(isinstance(b,A))      # True
print(isinstance(b,C))      # False
print(isinstance(b,(A,B)))  # True
print()

### hasattr(object, name)
##
##    测定对象object中是否有属性name

class C:
    def __init__(self,x = 0):
        self.x = x

c = C()
print(hasattr(c,'x')) # 属性用字符串

### getattr(object, name [, default])
##
##    获取对象object中属性name的值
##   (没有该属性：会返回可选参数，若果没有可选参数，返回false)
print(getattr(c,'x'))                       # True
#print(getattr(c,'y'))                       # 报错
print(getattr(c,'y','你访问的属性不存在'))   # 返回任何形式的可选参数
print()

### setattr(object, name , value)
##
##    设定对象object中属性name的值
##   (没有该属性, 给对象增加该属性，并赋值)
setattr(c,'x',1)
print(getattr(c,'x'))

setattr(c,'y',2)        # 没有属性y， 会给对象c 增加这个属性y，并赋值2
print(getattr(c,'y'))

### delattr(object, name)
##
##    删除对象object中属性name的值
##   (没有该属性, 抛出异常)

delattr(c,'y') 
print(hasattr(c,'y'))   # 已经被删除，不存在属性y
print()

### property(fget=None, fset=None,fdel=None,doc=None,)
##
##  通过属性设置属性

class C:
    def __init__(self,size = 10):
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
print(c1.x)         # 这里c1.x是取值，会从property(getSize,setSize,delSize)知道匹配的函数 c1.getSize()
c1.x = 18           # 这里c1.x是赋值，对应方法 c1.setSize(18)
print(c1.size)
print(c1.getSize())
del c1.x; # print(c1.size)   # 删除了，不存在
