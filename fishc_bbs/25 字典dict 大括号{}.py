
#####  字典  dict (不是序列)

brand = ['李宁','耐克','阿迪达斯']
slogan = ['一切皆有可能','Just do it','Impossible is nothong']

print('李宁的口号是：',slogan[brand.index('李宁')])



dict1 = { '李宁':'一切皆有可能','Nike':'Just do it',
          '阿迪达斯':'Impossible is nothong',360:'e,我也不知道'}

print('耐克的口号是:',dict1['Nike'])
print('360的口号是:',dict1[360])

dict2 = {1:'one',2:'two',3:'three'}
print(dict2)

# 构造
dict3 = {}  # new empty dictionary
tp1 = ('a',97);tp2 = ('b',98);tp3 = ('c',99);tp4 = ('d',100);  #4个元组
tp = (tp1,tp2,tp3,tp4)      # 4个元组，再构成一个元组
dict3 = dict(tp)            # 元组构造dist
print(dict3)

# dict(mapping) -> new dictionary initialized from a mapping object's (key, value) pairs
# 通过list和tuple构造元组，要求 元素是二元的list或者二元tuple或前两者的组合

print(dict([['0',48],['1',49],['2',50]]))  # 4个list合并成一个list，再构造dict

print(dict((['0',48],('1',49),['2',50])))  # 4个二元的list或tuple构成一个tuple，再构造dict

print(dict([('one',1),('two',2), ('three',3)])) # [('one',1),('two',2), ('three',3)]是list，元素是二元tuple
                                                 # 上述list 其实就是 zip
                                                 
print(list(enumerate(range(0,3))))      #list(enumerate(range(0,3)) 也是一个zip
print(dict(enumerate(range(0,3))))
print(dict(enumerate(['a','b','c'])))

print(dict(zip(['one', 'two', 'three'], [1, 2, 3]))) #通过zip构造


#|  dict(**kwargs) -> new dictionary initialized with the name=value pairs
#|  in the keyword argument list.  For example:  dict(one=1, two=2)

dict4 = dict(我='张三',你='李四',他='王五',最后='赵六');     #这种构造会根据键的大小排序
print(dict4)

dict4['我'] = 'wg';print(dict4);  # 修改已经存在的键的键值


dict4['她'] = 'abcd'  #### 不存在的键，会添加到dict ####
print(dict4)
