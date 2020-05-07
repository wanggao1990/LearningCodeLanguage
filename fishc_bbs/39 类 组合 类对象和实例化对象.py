###  组合：
###         不用继承的方法，将多个类（横向，类之间没有多大联系）的实例组合成一个类



class Turtle():
    def __init__(self,x):
        self.num = x

class Fish():
    def __init__(self,x):
        self.num = x


class Pool():
    def __init__(self,x,y):
        self.turtle = Turtle(x)
        self.fish = Fish(y)

    def print_num(self):
        print('水池里总共有乌龟 %d 只，小鱼 %d 只' %(self.turtle.num,self.fish.num))

pool = Pool(1,10)
pool.print_num()

print()

#######  类、类对象、实例化对象

class C:
    count = 0

a = C();print(a.count)
b = C();b.count += 3;print(b.count)
c = C();print(c.count)  # 3个实例，修改一个实例的count，不会影响其他实例的count

print()
a = C();print(a.count)
C.count = 10; # 对类的count修改,后续的实例，都会发生变化
a = C();print(a.count)  # 
c = C();print(a.count)

print()

#### 类的属性和方法同名
#

#  不要在类里面定义能想到的所有特性和方法，用继承和组合进行扩展
#  属性用名词，方法用动词
class C:
    def x(self):
        print('x-man')

c = C()
c.x()
c.x = 1 # Python的变量不需要声明，这里的x是新的实例化属性
#c.x()   # 属性覆盖方法，
print()

##### 绑定: Python严格要求方法需要有实例才能被调用

class BB:
    def printBB():              # 没有传递self，只能是类的方法，
        print('no zuo no die')  # 而不是实例化对象的方法（不同于C++）

BB.printBB()

bb = BB()
##b.printBB()   #  bb实例，没有方法printBB()


class CC:   
    def setXY(self,x,y):
        self.x = x
        self.y = y
    def printXY(self):
        print(self.x, self.y)

dd = CC()
print(dd.__dict__)      # 对象的属性和方法
dd.setXY(4,5);          # 实例化后，才有属于其实例化的属性 self.x self.y
print(dd.__dict__)          

print(CC.__dict__)      # 类实例化后的拥有属性，不包含 __init__等类的属性
                        # 绑定在类中，静态

del CC          # 删除类之后，实例化对象的方法依然存在
dd.printXY()    # （类对象是静态的，只有程序退出才会销毁）
                # 尽量使用实例化的对象
