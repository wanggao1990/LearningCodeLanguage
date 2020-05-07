# list、tuple、str  统称 序列(能迭代)

# 1 通过索引获得
# 2 默认索引值都是从0开始
# 3 分片方法获得元素的集合
# 4 操作符 （重复 拼接 关系）


## str,tuple => list

# 不带参数 空列表
a = list(); print(a)
# str转list,str每个字符都成为list元素 ['1', 'a', '2', 'b', '3', 'c']
a='1a2b3c'; a= list(a); print(a)
# tuple转list，每个元素都成为list元素 [1, 1, 2, 3, 5, 8, 13, 21]
a=(1,1,2,3,5,8,13,21); a= list(a); print(a) 


## str,list => tuple
a = tuple(); print(a)
a='1a2b3c';            a = tuple(a); print(a); # ('1', 'a', '2', 'b', '3', 'c')
a=[1,'abc',['x','y']]; a = tuple(a); print(a); # (1, 'abc', ['x','y'])

## tuple,list => str   直接加“”
a = str();print(a)
a= ['1', 'a', 2];      a = str(a); print(a); # 经过str(a)   a = "[['1', 'a', 2]]" , 打印后不带""
a= [1,'abc',['x','y']]; a = str(a); print(a); # 同上 "[1, 'abc', ['x', 'y']]" 

### len ：   str - 字符的个数；   tuple,list -> 元素的个数
st = 'a2 c2m';              print(len(st))  # 6
tp = (1,'abc',['x','y']);    print(len(tp)) # 3
ls = [1,'abc',['x','y']];   print(len(ls))  # 3


### max/min :  返回字符asic最大/小的值 （要求list和tuple中的元素类型相同）
print(max( 'x2 skc az8' ))   # 'z'  
print(max(['as','cx','xz'])) # 'xz'  元素是字符串，字符串比较最大
print(max( (1,42,123) ))     # 123

print(min([2,4,-20,3,23,-9])) # -20
print(min(('as','cx','xz')))  # 'as'

### sum : 求和(序列元素只能是数值)，可选参数附加
print(sum([2,4,-20,3,23,-9])) # 3
print(sum((2,4,-20,3,23,-9),8)) # 3+8 =11

### sorted： 排序（默认升序）    
numbers = [21,-8,12,6,3,4,9,45]
print(sorted(numbers));         # 同 numbers.sort()

### reversed:  返回结果的迭代器，再用list构造
numbers = [21,-8,12,6,3,4,9,45]
print(list(reversed(numbers)));  # 同 numbers.reverse()]
print(list(enumerate(numbers))); # 枚举，结果是list，元素是tuple，

### zip
a=[1,2,3,4,5,6,7,8];b=[4,5,6,7,8];
zip(a,b)                # 打包   [(1, 4), (2, 5), (3, 6), (4, 7), (5, 8)]
x,y = zip(*zip(a,b)) ;  # 解包   x=[1,2,3,4,5],y=[4,5,6,7,8]

