####### 函数参数

def my_add(num1,num2):
    '这个是函数文档, 通过.__doc__调用, 或者 help(func_name)查看'
    if not isinstance(num1,(int,float)) or not isinstance(num2,(int,float)):
        return
    return num1+num2

def my_sum(r):
    sum = 0
    for i in r:
        sum += i
    return sum

print(my_add.__doc__) # 打印函数说明文档，位于def行下的第一行字符串

print(my_add(2,3))      # 5
print(my_add(2.3,3))    # 5.5

#print(my_add(2))        # 5    默认参数
#print(my_add('a',3))    # None 没有返回或自动返回 None, 简写 return

print(my_sum(range(1-101)))  # 1-100累加
print()

#### 关键字参数

def SayDream(name,words):
    print(name,'want be', words)

SayDream('wanggao','scientist')
SayDream('scientist','wanggao') #参数填写反了，解决：关键字参数进行匹配
SayDream(words='scientist',name ='wanggao') #即给需要传递形参具体的内容


#### 默认参数

def SayDream2(name='wanggao',words='scientist'):
    print(name,'want be', words)

SayDream2() #默认参数
SayDream2('xiao ming')      #默认参数,没有关键字，默认是第一个带默认参数的形参
SayDream2(words = 'doctor') #默认参数, 用关键字参数，表示指定的形参


#### 可变参数 / 收集参数

## 用*加在形参前，类似指针，可以将可变形参看成一个tuple，多个参数用'，'分隔
def test(*params):
    print()
    print('参数的长度是：',len(params))
    print('第二个参数是：',params[1])

test(12,'wanggao','z',[2,'ab'])

#### 除可变参数，其他参数必须用关键字参数指定，否则会当成可变参数

# 为避免出错其他参数最好用默认参数
def test2(*params,exp):
    print()
    print('参数的长度是：',len(params))
    print('第二个参数是：',params[1])

#test2(12,'wanggao','z',[2,'ab'],8)  # 错误，打算给exp传递8， 但是8归并到可变参数中了
test2(12,'wanggao','z',[2,'ab'], exp = 8 ) #正确

def test3(*params,exp = 8):
    print()
    print('参数的长度是：',len(params))
    print('第二个参数是：',params[1])

test3(12,'wanggao','z',[2,'ab'])


## 若形参是元组，不能定义成 def Func((a,b),(c,d))
def disPt(pt1,pt2):
    return pow(pow(pt1[0]-pt2[0],2)+pow(pt1[1]-pt2[1],2),0.5)

print(disPt((1,0),(2,1)))   
