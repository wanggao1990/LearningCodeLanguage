# 函数、对象、模块

def MyFirstFunc():
    print('my first function')
    print('i feel gratitude...')
    print('i wanna thank CCTV...')


def MySecondFunc(name):
    print(name + ', I love you!')

def my_add(num1,num2): 
    return num1+num2

def my_sum(r):
    sum = 0
    for i in r:
        sum += i
    return sum

MyFirstFunc()

MySecondFunc('wanggao')

print(my_add(2,3))      # 5
print(my_add(2))        # 5    默认参数
print(my_add(2.3,3))    # 5.5  
print(my_add('a',3))    # 出错 ，没有类型判断

print(my_sum(range(1,101)))   # 1-100 累加

