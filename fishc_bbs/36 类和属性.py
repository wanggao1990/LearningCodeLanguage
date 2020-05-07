# Python中类命名约定以大写字母开头  封装 多态 继承

####

class Turtle:
    " 类是说明文档：一个简单的类例子 "

    # 属性
    color = 'green'
    weight = 10
    legs = 4
    shell = True
    mouth = '大嘴'

    # 方法
    def climb(self):                # self类似c++中的this指针，实例化对象的标记
        print('我正在用',self.legs,'条腿努力的向前爬...')
        
    def run(self):
        self.text = 'self text'
        print('我正在飞快的向前跑...')
        
    def bite(self):
        print('咬死你,咬死你！')
        
    def eat(self):
        print('有吃的，真满足^_^')
        
    def sleep(self):
        print('困了，睡了，晚安Zzzz')


#### 继承
class MyList(list):   ### 类 MyList 继承于 list
    pass


#### 多态
class A: 
    def fun(self):
        print('我是A.')

class B: 
    def fun(self):
        print('我是B.')

if __name__ == '__main__':  # 其他地方调用这个py模块，if失效； 在命令行运行
                            # 这个模块时，会把特殊变量__name__ 置为__main__
    tt = Turtle()
    tt.climb()
    tt.run()

### 类属性和实例化后属性
                        # 类似c++静态属性和方法，可以直接以类名调用

    print(Turtle.legs)  # 类属性，属于类的静态属性，修改后，所有属性都会变化
    #print(Turtle.text) # 实例化后的属性text,不能使用

    list2 = MyList()
    list2.append('a')
    list2.append(1)
    print(list2)

    print()
    a =A();b=B()
    a.fun()
    b.fun()
