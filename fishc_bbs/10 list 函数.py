
ls = ['中','国']

ls2 = ['abc','中',1, [1,2,'mn']]

for i in ls2:  print(i,end=' ')    # abc 中 1 [1,2,'mn']
   

ls.remove('国')  # 不需要知道其位置，只要存在即可，否则出错
print();
for i in ls:    print(i,end=' ')    # hi, 中 你 好


del ls[0]  #清除某个元素，或者一个list
print();
for i in ls:    print(i,end=' ')    #


ls = ['中','国']
a = ls.pop()     # 弹出最后一个元素
print(),print(a)
for i in ls:    print(i,end=' ')    # 中


# 切片，拷贝，深复制
print()
print()
ls = ['我','是','中','国','人']
t = ls[0:3]; print(t) 
t = ls[:3]; print(t) 
t = ls[1:]; print(t) 
t = ls[:]; print(t)    


t = ls.copy(); print(t) # 复制，同 t=ls[:]
ls.clear(); print(ls)   # 清除所有元素，结果为[], 不同于del(ls)后ls不存在
