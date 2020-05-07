
# 元组， 不能修改， 因此不能 排序等需要修改元素的操作

t = (1,2,3,4,5,6,7,8)

print(t[1],t[4])   # 访问同list

#拷贝 同 list

t1 = t[5:];  print(t1)   # 输出 (6，7，8)

t2 = t[:3]; print(t2)   # 输出 (0,1,2)

# t[0] = 0   # 不能修改


temp = (1); print(type(temp))  # ()可以是函数，或者元组， 优先是函数括号 'int'

temp = 1,2,3; print(type(temp))  # <class 'tuple'> #逗号连接的数据，默认是tuple

temp = []; print(type(temp))  # <class 'list'>

temp = (); print(type(temp))  # <class 'tuple'>

temp = (1,); print(type(temp))  # <class 'tuple'>   区分与 temp = (1);
temp = 1, ; print(type(temp))   # <class 'tuple'>   区分与 temp = (1);

print(8*(8)) # 64

print(8* (8,))  # 8个元组拼接成一个新的元组 （8，8，8，8，8，8，8，8，8）

t = ('a','b','c','d')

t = t[:2] + ('x',) + t[2:]  # 3个元组拼接形成新的元组t， t原来指向元组被释放
                            # 添加的x 必须为 ('x',) ，逗号不好

print(t) #('a', 'b', 'x', 'c', 'd')

#del(t[0]); # 删除元组的元素出错
del(t);     # 删除元组t，t就不再存在

#元组删除第i元素，只能用切片组合
t= (1,2,3,4,5); t = t[:2] + t[3:]; print(t)  # (1, 2, 4, 5)
