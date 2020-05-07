# {}默认是dict
num ={}
print(type(num)) # <class 'dict'>

num = {1,2,3,4}; print(type(num));   # <class 'set'>

num2 = {1,2,3,4,5,5,5,4,3,2,1}
print(num2);                   # 集合元素唯一，会自动去掉重复的元素

print(len(num2))                # 集合的元素个数


# num2[2]   ######### 不支持索引，因为集合无序.
            # TypeError: 'set' object does not support indexing


set1 = set();print(set1,type(set1));  # 不是{}, 而是set()


set1 = set([1,2,3,4,5]);print(set1); # 用可迭代对象构造set

# 怎么用的代码实现构造 set

num1 = [1,2,3,4,5,5,5,4,3,2,1,0]
temp = []
for each in num1:
    if each not in temp:
        temp.append(each)
        
print();print(temp)                 # 仅去掉重复的值，整体顺序不变
num1 = list(set(temp));print(num1)  # 有其他对象进行构造set,元素会进行排序

# in、not in等逻辑判断
print(2 in num1);print(6 not in num1);

# add,remove 添加和移除元素
num1 = set(num1)
num1.add(6);print(num1);num1.remove(0);print(num1)

# 不可变集合（不能进行增删）
a = frozenset([1,2,3,4]); print(a)  #  frozenset({1, 2, 3, 4})

