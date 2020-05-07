##
## list、tuple、dict、str等都是可迭代object，都支持迭代操作


#####  set不能随机访问,只能用迭代器进行元素访问
for each in {1,2,3,4,5,5,5,4,3,2,1}:
    print(each, end= ' ')
print()
print()

for i in "china":
	print(i) 

##### dict = { key1:value1, key2:value2, ...}
#
#   value = dict[key]

links = {'百度':"http://www.baidu.com",
		 '腾讯':"http://www.tencent.com.",
		 '淘宝':"http://www.taobao.com"}

for each in links: 	
	print( "%s -> %s" %(each, links[each]) )


#####   迭代器对象提供两个内建函数  iter() next(), 都是魔法方法
##

string = 'China'
it = iter(string);
print(next(it))
print(next(it))
print(next(it))
print(next(it))
print(next(it))
#print(next(it))		# 抛出StopIteration，迭代次数多于元素个数
print()


it = iter(string)
while True:
	try:
		each = next(it)
	except StopIteration:
		break
	print(each)


###  给一个对象创建迭代器，需要重写其魔法方法 __iter__(), __next__()

class Fibs:
	def __init__(self,n=10):
		self.a = 0
		self.b = 1
		self.n = n

	def __iter__(self):
		return self 		# 本身就是迭代器

	def __next__(self):
		self.a , self.b = self.b , self.a + self.b
		
		if self.a > self.n:
			raise StopIteration

		return self.a


fibs = Fibs()

for each in fibs:
	if each <20:			# 没有给定参数n，无穷输出
		print(each)
	else:
		break

fibs = Fibs(100)
for each in fibs:			# 根据给定值，输出
	print(each)

print()

###  给一个对象创建迭代器，需要重写其魔法方法 __iter__(), __next__()
##   写一个Rev的类，功能同reversed()相同
#			（built-in函数 reversed(seq)返回的是一个反向的迭代器）
	
class MyRev:
	def __init__(self,data):
		self.data = data
		self.index = len(data)

	def __iter__(self):
		return self

	def __next__(self):
		if self.index == 0:
			raise StopIteration

		self.index -= 1

		return self.data[self.index]


myRev = MyRev("Contribution!")

print(myRev)  # 函数返回逆序的结果 myRev 是一个 object，可以转换成 list、tuple等对象

# print(list(myRev))  # 这里执行之后，迭代对象已经是StopIteration， 在后续的 for 就不在执行

for each in myRev:
	print(each)

# print(list(myRev))  # 若先进行for，再执行这一句，则为空
