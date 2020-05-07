####### 内嵌函数和闭包

def saying():
    var = 'hello'
    print(var)

var = 'hi'
saying();print(var);  # 打印 'hello'和'hi'


def saying2():
    global var      # 不是声明一个变量，说明变量var是全局变量
    var = 'hello'   # 函数体上一层就是global, 同样可以用nonlocal.
    print(var)      # 若变量在全局，在函数的函数中修改，就不能用nonlocal
    
saying2();print(var);  # 打印 'hello', 'hello'
print()

############# 内嵌函数（函数内部定义函数）

def func1():
    print('func1调用...')

    def func2():
        print('func2()调用...')   # 在fun1中定义，就只能在func1中调用

    func2()  # func1()调用func2()，注意缩进

#func2();  # 错误
func1()

############# 闭包 closure

##### 函数名
def funct(x):
    print(x*x);
    
f = funct; res = f(5);print();     # f代替了函数名字，类似C语言的函数指针

##### 试图计算 3*5
def funX(x):
    def funY(y):    # funX()函数的作用域中定义了一个内置函数funY()
        return x*y  # 内置函数，使用了funX()作用域变量x ，称funY()是一个闭包
    return funY     # 这里返回的是函数名

fun = funX(3); print(fun,type(fun)) # fun可以理解是funY的函数指针(参数和funX关联)
res = fun(5);print(res)             # fun(5)就是调用funY(5)
res = funX(3)(5);print(res)         # 等同于上2句

##### 试图计算 5*5 
def fun1():
    x = 5
    def fun2():
        x *= x    
        return x
    return fun2()

# fun1()    # 提示 x *= x 这一句的x没有定义就使用

### 在Python3之前，用容器（栈中实现）解决 5*5 
def fun1():
    x = [5]
    def fun2():
        x[0] *= x[0]
        return x[0]
    return fun2()

res = fun1();print(res);  # 单个元素的list，访问用ls[0]

### Python3 使用关键字
x =10
def fun1():
    x = 5
    def fun2():
        nonlocal x  # 说明x不是局部变量,（个人臆测:仅在上一层寻找x，上一层没有就报错）
        #global x    # 也可以用 global说明，从最外层一次寻找，若修改值会造成结构混乱，阅读性差
        x *= x
        return x
    return fun2()

print(fun1());print()


##### 小题目
def funX():
    x = 5
    def funY():
        nonlocal x
        x += 1
        return x
    return funY     # 注意返回的是函数名

a = funX();print(a)  # a是函数 funY 的'别名'

print('1 -',a())
print('2 -',a())
print('3 -',a())

# 上面3条输出，依次是什么 ？？？

# 第一条 肯定是 6 ，x = x+1,  x =6
#
# 后面2条，a已经确定，且a没有被重新复制，funX就不会释放，x不会初始化 (调用一次funX，x就重置为5)
# 也就是说，a只声明一次，x就只声明并定义一次 x=5, 后面重复调用funY, 仅是对x修改3次
# 第二次调用，x加1，x = 7; 第三次调用再加1，x=8.  输出为 6 、7、 8
#

b=funX();   # 创建一个b
print(a())  # 9     a还存在
print(b())  # 6     b独立于a

a= funX();  # a被重新复制，原来a对应的funX释放； x 会初始化
print(a())  # 6

