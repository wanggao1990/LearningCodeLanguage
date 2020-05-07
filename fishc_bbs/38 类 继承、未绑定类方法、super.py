# coding = UTF-8

import random as r

#	子类			基类、父类或超类
#	class DerivrdCLassName(BaseClassName)

class Parent:

    def __init__(self):     
        print('父类构造函数')
    
    def hello(self):
        print('正在调用父类的方法')


class Child(Parent):                # 是一个继承的类

    def __init__(self):
        print('子类构造函数')

    def hello(self):                # 方法与父类同名，会覆盖父类
        print('正在调用子类的方法')
    


p = Parent()
p.hello()

p = Child()
p.hello()

print()

#########################

class Fish:
    def __init__(self):
        self.x = r.randint(0,10)
        self.y = r.randint(0,10)
        print(self.x,self.y)

    def move(self):
        self.x -= -1      
        print("我的位置是:",self.x, self.y)

class GoldFish(Fish):
    pass

class Carp(Fish):
    pass


class Salmon(Fish):
    pass


class Shark(Fish):
    
    def __init__(self):     # 可以覆盖父类
       # Fish.__init__(self) # 调用父类的方法，传递的self是shark的属性
                            # 实际是用self创建shark实例化的属性x和y
                            # 使得shark实例调用父类方法move有属于自己的x
                            # 

        super().__init__()    # 会自动从父类查找需要的属性和方法

        self.hungry = True

        
    def eat(self):
        if self.hungry:
            print('吃货的梦想就是天天有的吃！')
            self.hungry = False

        else:
            print('太撑了，吃不下了')

fish = Fish()
fish.move()
fish.move()

goldfish = GoldFish()
goldfish.move()
goldfish.move()

shark = Shark()
shark.eat()
shark.eat()
#shark.move()   # 报错 没有属性x、  构造函数被覆盖
                # 解放方法：1、调用未绑定的父类方法；
                #           2、使用super方法(还可以避免多重继承的重复调用)
shark.move()

print()

##### 多重继承

#	子类		    基类、父类或超类
#	class DerivrdCLassName(Base1, Base2, Base3)

class Base1:
    def foo1(self):
        print('我是foo1，我为Base1代言')

    def foo(self):
        print('我是foo,我是Base1')      

class Base2:
    def foo2(self):
        print('我是foo2，我为Base2代言')

    def foo(self):
        print('我是foo,我是Base2') 

class C(Base1,Base2):       # 很容易导致结构混乱
    pass                    # 如果父类有两个同名函数，会按照继承顺序调用



c = C()
c.foo1()
c.foo2()
c.foo()

c.foo       
