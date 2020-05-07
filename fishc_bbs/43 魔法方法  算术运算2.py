
# int()、float()、str()、len()、tuple()、list() 等函数调用时，就创建一个相应的实例

#######  算术运算符 
##
##  __add__(self, other)	    定义加法的行为：+
##  __sub__(self, other)	    定义减法的行为：-
##  __mul__(self, other)	    定义乘法的行为：*
##  __truediv__(self, other)	    定义真除法的行为：/
##  __floordiv__(self, other)	    定义整数除法的行为：//
##  __mod__(self, other)	    定义取模算法的行为：%
##  __divmod__(self, other)	    定义当被 divmod() 调用时的行为
##  __pow__(self, other[, modulo])  定义当被 power() 调用或 ** 运算时的行为
##  __lshift__(self, other)	    定义按位左移位的行为：<<
##  __rshift__(self, other)	    定义按位右移位的行为：>>
##  __and__(self, other)	    定义按位与操作的行为：&
##  __xor__(self, other)	    定义按位异或操作的行为：^
##  __or__(self, other)	            定义按位或操作的行为：|


class New_int(int):              #覆盖原来的方法
    def __add__(self,other):
        return int.__sub__(self,other)

    def __sub__(self,other):
        return int.__add__(self,other)


a = New_int('5');print(a);
b = New_int(3);print(a+b)
print()

####### 反运算
# arg1 op arg2, 当arg1不支持op，将执行arg2的反op运算

class Nint(int):
    def __radd__(self,other):
        return int.__sub__(self,other)

    def __rsub__(self,other):
        return int.__sub__(self,other) # self在前   执行 self-other

a = Nint(5);b=Nint(3)
print(a+b)      # 结果8。 a 可以进行 __add__
print(1+b)      # 结果2。 1不行， 因此执行 b的__radd__ ,这里已经重写为减法 即3-1 


class Nint2(int):
    def __radd__(self,other):
        return int.__sub__(self,other)
    def __rsub__(self,other):
        return int.__sub__(other,self)  # self在后    执行 other-self

a = Nint(5);  print( 3 - a);  # 反运算，5 - 3
a = Nint2(5); print( 3 - a);  # 反运算，3 - 5  

####### 增量算符
##   += 、 -=、 /=、 *= 、...

####### 一元操作算符
##  正号 +x 、 负号 -x、 绝对值 abs(x)、 按位取反 ~x

####### 类型转换
##  complex()、int()、float()、round()

