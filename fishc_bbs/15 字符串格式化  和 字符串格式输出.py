##################################    格式化    #################################

######################### 1、字符串格式化
# 第一种， 位置参数 和 关键字对应 (元组元素 个数可以多余使用的个数，不能越界)
#  {0}{1}{2} 分别对应元组（'wanggao','1','2'）的元素
str1 = 'Hello,{0}. You id is No.{1}'.format('wanggao','1','2');print(str1)
str1 = 'Hello,{1}. You id is No.{2}'.format('wanggao','1','2');print(str1)

# 第二种，直接用'='标识 ， 元素一一对应
str1 = 'Hello,{name}. You id is No.{num}'.format(name='wanggao',num='1');
print();print(str1)

# 前两种混用， 未知参数必须在前面(对应的关键字同样在前面)
str1 = 'Hello,{0}. You id is No.{num}'.format('abc',name='wanggao',num='1');
print();print(str1)

print('{{0}}'.format('wg'));  #无效
print('{0}'.format('{wg}')); # 打印大括号

# 格式化符号
str1 = '{0:10.1f}{1}'.format(27.58,'Gb') # 第一个关键字，按一位小数位输出（四舍五入）
print();print(str1)                      # 数值总宽度10

str1 = '{0:010.1f}{1}'.format(-27.58,'Gb') # 第一个关键字，按一位小数位输出（四舍五入）
print(str1)                               # 数值总宽度10，前面用0填充（同C语言）


######################### 2、字符串格式化输出
print( '%c' %97)  #指定格式输出   数字97 用%c ASIC 输出 ; 后面的输出关键字是tuple
print( '%c' %(97,))

print( '%c, %s' %(97,'wang gao'))
print('%d + %d = %d' % (4, 5, 4+5) )

print('Dec(%d) + Oct(%o) = Hex(%X)' % (4, 9, 4+9) )  # 进制，大小写

print('%f + %f = %10.3e' % (4,9,4+9))# 科学计数法，小数位个数，位宽，
                                     # (+)正数显示符号，(-)左对齐等，补零左对齐无效

print('%#o' % 11) # 明确输出 8进制格式  0o13（八进制没有大写）
print('%#X' % 11) # 明确输出16进制格式  0XB (大写)
print('%#x' % 11) # 明确输出16进制格式  0xB (小写)  

# 位置参数对应dict的键值，并且以指定格式输出（比较格式化符号）
print('%(0)03d  %(st)c  %(fl)08.2f' %{'0':2,'st':97,'fl':-25.6156})

input("enter any key: ")
