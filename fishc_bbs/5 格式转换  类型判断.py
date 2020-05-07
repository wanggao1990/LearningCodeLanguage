#str = '520' + '1314'

#print(str)


# str()也是一个bif，  将str当做变量之后，就不能再用这个bif


#四舍五入

x = 0.6

y = int(x+0.5)

y

print(str(0.6))

print(str(2))

print(float(2))


#数据类型 type(),直接打印结果

type(str(2));

type(3.0)

# isinstance  和指定格式比较，并返回结果。

isinstance(True,bool)

isinstance(3.56,float)

isinstance(2,int)

isinstance(3,(int,float))  # 满足元组中其中一个类型，返回True
