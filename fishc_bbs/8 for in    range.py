#元组、列表 都是容器

name = 'wang gao'
for i in name:
    print(i,sep = ' ',end=' ')

# print(value, ..., sep=' ', end='\n',
#                   默认分隔符为空格，end=默认每个取值后添加换行符

print()

member = ['abc','defg','hijkl']   #列表

len(member) # 元素的个数，3

for each in member:
    print(each, len(each))   # 每个元素长度

for i in range(1,101):
    if i%2==1:
        print(i,i+1)  # 两两打印

print()
print(2,3,4,5) # 逗号分隔，彼此间加空格

#############################
#### 用for in 构造 序列  

ls = (i for i in range(0,10)); print(tuple(ls)) # 构成元组的迭代器（伪元组推导式）

ls = [i*i for i in range(0,10)]; print(ls) # 构成 list (列表推导式)

ls= [(x, y) for x in range(5) for y in range(5) if x%2==0 if y%2!=0];print(ls)

### 两个list交错组合成一个新的 ['a',1,'b',2,'c',3]
mem = ['a','b','c']
dat = [1,2,3]
# 第一种 用 insert
#mem.insert(1,1);mem.insert(3,2);mem.insert(5,3);print(mem)
# 第二章 用 for
mem = [(x, y) for x in mem for y in dat if x == y];print(mem) ## 没有实现

#######################
####      range 生成一个序列，默认从0开始，到n-1,(默认步长1)

##   range(i,j)     =>              i,i+1,...,j-2,j-1
##   range(4)       =>range(0,4) => 0,1,2,3
##   range(i,j,s)   =>              i,i+s,i+2s,...,j-4s,j-2s

print()
print( range(10) )          # range(0,10)
print( list(range(10)) )    # range转list   [0,1,2,3,4,5,6,7,8,9]



# while

bingo = '你真帅'
answer=input('输入一句话：')
while True:
    if answer == bingo:
        break;
    answer=input('再输入一次：')
print('结束')

# 0-100所有奇数，continu

print();
print('0-100的奇数')
for i in range(100):
    if i%2==0:
        continue
    print(i,end=' ')

