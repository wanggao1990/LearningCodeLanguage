
################ lambda表达式 

def ds(x):
    return x*2 +1
print(5)

f = lambda x : x*2 + 1   
print(f)                # <function <lambda> at 0x0300A8E8>

print(f(5)) # 等f(5)效于ds(5)


## 对于只调用一两次的函数，有时候没有必要去def一个函数；另外，可以提高可读性

def my_add(x,y):
    return x+y

g = lambda x,y : x + y     #  ':'前面是参数，后面是返回值

print(g(1,2))


################ filter()过滤器

# 1、 filter(None,item)  返回迭代器item为True的object
# 2、 filter(func,item)  当func(item)为True,返回item的object

filter(None,[1,0,False,True])  
ls = list(filter(None,[1,0,False,True]))  # object转化为list
print(ls) #  输出 [1,True]


# 1-11的奇数
def odd(x):
    return x%2
print(list(filter(odd,range(1,11))))

print(list( filter(lambda x: x%2, range(1,11)) ))   # lambda代替函数


###### map() 映射
## 将序列按照指定函数进行映射，如得到序列0~9的平方序列

#方法一， 函数
def fun(x):
    y = list(x)
    n = 0
    for i in x:
        global n
        y[n] = i*i
        n += 1
    return y

print(fun(range(0,10)))


#方法二，list推导式
ls = [i*i for i in range(0,10)]
print(ls)


#方法三 , map
ls = list( map(lambda x: x*x, range(0,10)) )
print(ls)

