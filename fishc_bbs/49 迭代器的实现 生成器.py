
###### 生成器  
#
##	是迭代器的一种实现，不需要类，仅需要在实例中增加 yield 语句修饰
# 	(本身也是一个迭代器)
# 
#  协同程序：可以独立运行的独立函数调用，可以暂停和挂起，
#	在需要的时候从程序离开的地方继续或者重新开始
#	
	
def myGen():
	print("生成器被执行")

	yield 1  	#  函数中出现 yeild，这个函数就是一个生成器；程序暂停，返回1，
	yield 2 	#  下次再从这里执行


myG = myGen()
print(next(myG))
print(next(myG))
# print(next(myG))   # StopIteration
print()

myG = myGen()
for i in myG:
	print(i)
print()


def Fibs(size=20):
	a = 0
	b = 1
	n = size
	while a < n:
		a,b = b, a+b
		yield a

fibs = Fibs(50)
for i in fibs:
	print(i,end=' ')

print()


###  列表推导式
a = [i for i in range(50) if not(i%2) and i%3]; print(a);print()

a = list(filter(lambda x: not(x%2) and x%3, range(50))); print(a);print()

### 字典推导式

b = { i: i%2 == 0   for i in range(10)}; print(b);print()  # 偶数


### 集合推导式
c = { i for i in (1,2,3,4,5,4,3,2,1)}; print(b);print()  # 偶数



# 没有元组和字符串推导式
d = "i for in 'I love u'";print(d);print() 	###  i for in 'I love u'



##### 括号起来的'元组推导式' 是 生成器推导式
####
e = (i for i in range(10));print(e);print() ###  <generator object <genexpr> at 0x0031BDE0> 生成器
													
for i in  e:
	print(i,end=' ')
print()

## 生成器推导式直接作为参数，可以去掉括号
s = sum( i for i in range(100) if i%2); print(s)

s = sum(list([i for i in range(100) if i%2])); print(s)