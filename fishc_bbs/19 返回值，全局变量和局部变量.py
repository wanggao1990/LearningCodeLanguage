####### 返回值，全局变量和局部变量

# 函数没有返回值，默认会返回None （程序没有返回值是，隐含 return 或 return None）
def hello():
	print('hello world!')     

temp = hello();
print(temp)         # None
print(type(temp))   # <class 'NoneType'>

# 返回值
def back():
    return [1,'Python',3.14]    # 指定返回list

def back2():
    return  1,'Python',3.14     # 没有指定格式，返回值（一个或多个）默认 tuple

print(back2());                 # （1,'Python',3.14）
print(type(back2()));print()    # tuple


# 局部变量和全局变量
def discounts(price, rate):
    final_price = price * rate
    print('全局变量old_price的值：',old_price)  
    return final_price

old_price = float(input('请输入原价:'))
rate = float(input('请输入折扣率:'))      
new_price = discounts(old_price,rate) # 全局old_price先定义后使用，其作用范围覆盖函数
print('打折后的价格是:',new_price)

# print('局部变量final_price的值:',final_price)   # 没有定义，区分局部变量作用范围

def discounts2(price, rate):
    final_price = price * rate
    old_price = 50;
    print('修改后old_price的值1:',old_price) # 和全局变量同名，会覆盖全局变量的作用域
    return final_price                      # 理解为定义了一个局部变量（思考：局部中修改全局变量？）

old_price = float(input('请输入原价:'))
rate = float(input('请输入折扣率:'))      
new_price = discounts(old_price,rate)
print('修改后old_price的值1:',old_price)     #这里仍然是全局变量的值
print('打折后的价格是:',new_price)
