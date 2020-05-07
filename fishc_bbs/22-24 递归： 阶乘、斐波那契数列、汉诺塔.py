
########## 递归： 阶乘、斐波那契数列、汉诺塔

##### 阶乘 n! ###

# 方法一 迭代

def factorial_1(n):
    result = n
    for i in range(2,n):
        result *= i
    return result

print(factorial_1(20));print();


# 方法二 递归
def factorial_2(n):
    if n == 2 :
        return 2
    else:
        return n*factorial_2(n-1)

print(factorial_2(20));print();


##### 斐波拉契数列 ###

# 方法一 迭代

def fib(n):
    a=1
    b=1
    sum = a + b
    print(a,b)
    for i in range(1,n):
        a = a + b
        b = a + b
        print(a,b)
        sum = sum +a+b
    return sum

print('总数 %d ' % fib(20));print();


# 方法二 递归

def fib2(n):
    if n ==1 or n ==2:
        return 1
    else:
        return fib(n-1) + fib(n-2)

print('总数 %d', fib2(20));print();

 
##### 汉诺塔 ###

#(1)当只有一个盘子的时候，只需要从将A塔上的一个盘子移到C塔上。
#(2)当A塔上有两个盘子是，先将A塔上的1号盘子（编号从上到下）移动到B塔上，
#   再将A塔上的2号盘子移动的C塔上，最后将B塔上的小盘子移动到C塔上。
#(3)当A塔上有3个盘子时，先将A塔上编号1至2的盘子（共2个）移动到B塔上（需借助C塔），
#   然后将A塔上的3号最大的盘子移动到C塔，最后将B塔上的两个盘子借助A塔移动到C塔上。
#(4)当A塔上有n个盘子是，先将A塔上编号1至n-1的盘子（共n-1个）移动到B塔上（借助C塔），
#   然后将A塔上最大的n号盘子移动到C塔上，最后将B塔上的n-1个盘子借助A塔移动到C塔上。
# 综上所述，除了只有一个盘子时不需要借助其他塔外，其余情况均一样

def hanoi(n,x,y,z):
    if n ==1:
        print(x,'-->',z)
    else:
        hanoi(n-1,x,z,y)    # n-1个盘子从x移到y
        print(x,'-->',z)    # 将最地下的最后䘝盘子从x移到z上
        hanoi(n-1,y,x,z)    # 将y上的n-1个盘子移到z


hanoi(int(input('输入汉诺塔层数:')),'X','Y','Z')

