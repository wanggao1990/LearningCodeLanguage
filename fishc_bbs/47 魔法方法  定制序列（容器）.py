#### Python基于序列的三大容器：  List、Tuple、String

# 协议 Protocols，规定那些方法必须要定义
# 
# 1、若定制容器不可变，只需定义__len__()和__getitem__()方法
# 2、若定制容器可变，定义__len__()和__getitem__()之外，还需要定制
# 		__setitem__()和__delitem__()两个方法
# 		

## 编写一个不可变的自定义列表，要求记录列表中每个元素被访问的次数

class List:
	def __init__(self,*args):
		self.ls = list(args)   # 或者 self.ls = [x for x in args]

		self.count =[]

		# for i in range(len(self.ls)):
		# 	self.count.append(0);
	
		for item in self.ls:
		 	self.count.append([item,0]);

	def __len__(self):
		return len(self.ls)

	def __getitem__(self,key):
		self.count[key][1] += 1
		return self.ls[key]

ls = List('a','b','c','d','e','f','g')

ls[2];ls[2];ls[3];ls[1];
ls[4];ls[1];ls[6];ls[5];
ls[4];ls[0];ls[0];ls[2];

print(ls.count)

