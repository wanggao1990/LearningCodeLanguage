
ls1 = ['abc','def','hij']
ls2 = ['中','国']
ls3 = [1,2,3,4,5]
ls4 = ['abc','中',1, [1,2,'mn']]


print(ls1(1))


for i in ls4:
    print(i,end=' ')    # abc 中 1 [1,2,'mn']

print();

### append() 将参数作为一个元素增加到列表的末尾

ls = ['中','国']
ls.append(',')

print(ls)
for i in ls:    print(i,end=' ')    # 中 国 
    

### extend() 将参数作为一个列表去扩展列表的末尾

# ls.extend('你','好')  # 错误
ls.extend(['你','好'])  # 参数是list
print()
for i in ls:    print(i,end=' ')  # 中 国  你 好

### insert()  在指定位置插入
ls.insert(0,'hi,')  # 基于0的插入
print()
for i in ls:    print(i,end=' ')    # hi, 中 国  你 好
