#连续赋值

a=b=c=d=10   # 所有值都为10

# 操作符 同c

e=10

e += 1  # e = 11
e -= 2  # e = 9
e /= 3  # e = 3.0
e *= 4  # e = 12.0


# 除法 "/"， 取整"//" ， 取余"%"

10/2  #5.0

10//2 #5

10 % 2 # 0

9.0 /3 # 3.0

9.0 // 3 # 3.0

9.0 % 3 # 0.0

9.1 % 3 # 0.099999999999999964  可以理解为0.1

#  可以理解为 除法 对 所有数值有效，实际除法运算
# 取整、取余 应该对整数有效。

# 幂操作 **
2**3  # 8
3**4  # 81
-3**-2 # 0.11111111111


# 运算优先级 符号>比较>逻辑>赋值

#逻辑操作符 and or not 同c/c++中的  && || ~
