
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

#######
####### 属性访问
#
#   getattr         试图获取一个不存在的属性是的行为
#   getattribute    属性被访问时的行为（找不到再调用 getattr）
#   setattr         属性被设置时的行为
#   delattr         属性被删除时的行为

class C:
    def __getattribute__(self,name):
        print('getattribute')
        return super().__getattribute__(name)   ### 基类方法, object类

    def __getattr__(self,name):
        print('getattr')

    def __setattr__(self,name,value):
        print('setattr')
        return super().__setattr__(name,value)  

    def __delattr__(self,name):
        print('delattr')
        return super().__delattr__(name) 

c = C()
c.x       # 访问，首先执行 __getattribute__； 没有该属性，再执行 __getattr__

c.x = 1  # __setattr__
c.x      # __getattribute__ 可以访问

del c.x  # __delattr__


##### 容易陷入死循环陷阱,
##
##      init中进行赋值，调用setattr, 再setattr中又进行赋值。。导致陷入无限递归死循环

class Retangle:
    "矩形类"
    def __init__(self,width=0,height=0):
        self.width = width
        self.height = height

    def __setattr__(self,name,value):       # 返回值都是
        if name == 'square':
            self.width = value
            self.height = value
        else:     
        ## 解决1  self.name = value           #################################
           # super().__setattr__(name,value)  #### 推荐用 super() 基类方法  ###
                                              ################################
        ## 解决2
            self.__dict__[name] = value

    def __getattr__(self,name):         # super没有改方法
         #print( '该属性不存在')
         return '该属性不存在'

    def getArea(self):
        return self.height * self.width

print()
rl = Retangle(4,5)   # 直接懵逼。。。self.4 = 5。  构造函数 和 setattr冲突
#print(rl.getArea())        

rl = Retangle('square',5)   # width = 'square',  height = 5
print(rl.getArea())         # 重复5个 'square'
print()

rl.square = 10    # 调用__setattr__， 并将width和height赋值10，并没有属性square
print(rl.width)
print(rl.height)
print(rl.getArea())

print();
print(rl.zz)        #### 没有改属性,首先打印 getattr的函数体内容，函数返回为None，
rl.zz = 10          #### 继续打印None  （解决：函数体不是打印，是返回字符串）
print(rl.zz)
print(rl.__dict__)          # 3个属性 zz, height, width
print(len(rl.__dict__))     # 属性个数


print(dir(super))   ####### supper 没有 __getattr__
