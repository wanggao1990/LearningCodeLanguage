ls1 = [123]
ls2 = [234]

print (ls1 > ls2)   # false

ls1 = [123,456]
ls2 = [234,123]
print (ls1 > ls2)   # false  # 从0个元素比较


ls3 = [123,456]
print( ls1 < ls2 and ls1==ls3 ) # True

ls = ls1+ls2; print(ls)  #[123,456,234,123]

ls *= 3; print(ls)


print(123 in ls) # True


ls = [123,['a','b'],456]

print( 'a' in ls)  # False,只能返回相同层次的结果

print(ls[1][0],ls[1][1])  # ls[0][1] 错误

ls[1][1] = 'c'; print(ls)  #### 修改ls中第二个元素--元组['a','b']中第二个元素

dir(list)  # 查看成员函数

ls *= 3;
l=ls.count(123)  # 出现次数 3
print(l)


print(ls.index(123))  #第一个出现123的位置

print(ls.index(123,2,5)) #第一个出现123的位置(相对于ls的0位置),并且限制范围

ls.reverse();print(ls)   #反转


ls = [8,3,5,6,9,0,4]; ls.sort();print(ls)   #排序 默认升序（归并排序）
ls.reverse();print(ls)  # ls降序

ls = [8,3,5,6,9,0,4]; ls.sort(reverse = True);print(ls)   #排序,降序 等效上两句

print(ls[::-1]) # 逆序

print()
ls = [8,3,5,6,9,0,4];
print(ls)
ls1 = ls[:]  # 拷贝，相当于深复制
ls2 = ls1    # 相当于 引用
ls.sort()
print(ls,',',ls1,',',ls2)
