
# 为False的情况，可以通过 bool()转换得到
#
# 包括  0,' ',{},[],() 等

# A and B   if A = True , return A, else B
# A or  B    if A = True , return B, else A
#   not A   if A = True , return False, else True

print(  '3 and 2 = ', 3 and 2)
print(  '3 and 5 = ', 3 and 5)
print(  '0 and 6 = ', 0 and 6)
print(  '1 and 0 = ', 1 and 0)
print(  '3 or 4 = ', 3 or 4)
print(  '3 or 0 = ', 3 or 0)
print(  'not 3 = ', not 3)
print(  'not 0 = ', not 0)

# 优先级 not > and > or 



# 二元运算符
x,y = 3,4   # x=3,y=4


# 三元运算符
if x>y:
    temp = x
else:
    temp = y

#上述if else 等同于
temp = x if x>y else y  # temp=4


# 快速交换彼此的数字
x,y = y,x
z=5
x,y,z = y,z,x    # x=4,y=5,x=3
