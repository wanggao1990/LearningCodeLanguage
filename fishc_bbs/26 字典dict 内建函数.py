
dict1 ={}

## 构造
dict1.fromkeys((1,2,3))  # 构造一个含有3个键1，2，3的dict,值默认都为None

dict1.fromkeys((1,2,3),'str') # 三个键的值都为'str',可选参数是对所有键值初始化

dict1.fromkeys((1,2),'con')  # 新的dict，只有1，2两个键。不是对1，2的键值修改

print()

## 访问
dict1 = dict1.fromkeys(range(32),'赞'); print(dict1)

for eachkey in dict1.keys():
    print(eachkey,end=' ')

print()
for eachvalue in dict1.values():
    print(eachvalue,end=' ')

print()
for eachitem in dict1.items():
    print(eachitem,end=' ')

print()

## pop 、popitem

print(dict1.pop(2));print(dict1) # 弹出键为2的item

print(dict1.popitem()); # 随机弹出一个item
    
print()

# get、 in、 not in 、clear

print(dict1.get(32))  # get方法查询键的值，  不存在 返回None

print(31 in dict1)      # 键31存在?   True
print(32 not in dict1)  # 键32不存在？ True

dict1.clear();print(dict1);  # 清楚所有item
print()

# copy

dict1 = {1:'one',2:'two',3:'three'}
dict2 =  dict1.copy()                   # 浅拷贝
dict3 = dict1;                          # 引用
print(dict1,dict2,dict3)
print(id(dict1),id(dict2),id(dict3))    # 地址

dict2[4]= 'four' # dict2 插入
print(dict1,dict2,dict3)

# setdefault
dict3 = dict2
dict3.setdefault('大白');print(dict3);  # 加入一个键为''大白'，值默认为None的itme
                                        # 当加入的键已经存在，则不进行处理
dict3.setdefault('小白','一条狗');print(dict3);  
dict3.setdefault(2,'hundred');print(dict3);

# update  
dict4 = {'5':'five','6':'six'}
dict3.update(dict4);print(dict3) # 将dict4的所有item添加到dict3中
