
# int()、float()、str()、len()、tuple()、list() 等函数调用时，就创建一个相应的实例

print( type(len) )
print( type(dir) )
print( type(int) )
print( type(list))

a = int('123')
b = int('456')
print( a + b )


class New_int(int):
    def __add__(self,other):
        return int.__sub__(self,other)

    def __sub__(self,other):
        return int.__add__(self,other)

a = New_int(3)
b = New_int(5)
print( a + b)
print( a - b)

class Try_int(int):
    def __add__(self, other):
        return self + other

    def __sub__(self, other):
        return self - other

a = Try_int(3)
b = Try_int(4)
#print(a+b)      # 无限递归


class Try_int(int):
    def __add__(self, other):
        return int(self) + int(other)

    def __sub__(self, other):
        return int(self) - int(other)

a = Try_int(3)
b = Try_int(5)
print(a+b)      # 无限递归

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

print(divmod(5,3))     # 返回一个元组 divmod(a,b) = (a // b, a % b)
