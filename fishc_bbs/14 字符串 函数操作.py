
# Python 里面没有字符概念，只有字符串，C语言中单个字符也是字符串

str1 = 'i love you very much'

print(str1[:6])   #字符串前6个字符  str1[:6] = 'i love '

print(str1[1])  # 查询某个字符，以字符串形式存在   str1[1] = ' '

str1 = str1[:6] + '插入的字符' + str1[6:]  #原来的str1指向内存 没有被指向，会被释放

str1 = str1.capitalize(); print(str1);  #英文字符首字母大写,返回一个复制内存

str1 = 'I Love You Very Very Much !'
str2 = str1.casefold(); print(str2);  # 小写字符串中所有大写的字符

str2 = str1.center(50); print(str2);  #用指定长度，居中

print(str1.count('e'));  # 查询字符串'e'的个数  3
print(str1.count('er'));  # 查询字符串'er'的个数 2

print(str1.endswith(' !'))       # 是否以指定字符串结尾（可选范围） True
print(str1.endswith('e',0,6))    # 是否以指定字符串结尾（范围[0-6) ） True
print(str1.startswith('I ',0,6)) # 是否以指定字符串开始（范围[0-6) ） True

str1 = 'I\tLove\tYou\tVery\tMuch!'
print(str1.expandtabs()) # 将制表位用空格代替； 可选范围

print(str1.find('Lo')); # 查找字符串的未知，找不到返回-1 ；可选范围；rfind逆序
                        # 类似 " 'Lo' in str1 "语句，只返回 false和true 

print(str1.index('Lo'));  # 同find； 可选范围，但范围内找不到会抛出异常；rindex逆序

str1 = str1.replace('\t',' '); print(str1); # 替换；可选 前指定个数

#逻辑判断
print();
print('Re323vC'.isalnum());  # 至少有一个字符，且都是字母或数字 ，返回True；否则False
print('asKJxHb'.isalpha());  # 至少有一个字符，且都是字母       ，返回True；否则False
print('2115623'.isdecimal());# 字符串只包含 十进制数字，返回True；否则False
print('2115623'.isdigit());  # 字符串只包含 数字，      返回True；否则False
print('2115623'.isnumeric());# 字符串只包含 数字字符，  返回True；否则False
print('       '.isspace());  # 字符串只包含 空格，      返回True；否则False
print('8v9 x88c'.islower()); # 字符串字母都是小写，返回True；否则False
print('89 D88C'.isupper());  # 字符串字母都是大写，返回True；否则False
print('2 Cx 1 Cc32 王'.istitle());# 字符串中所有单词都是大写开头，返回True；否则False
print();
print('i lOve yoU, babY!'.title());# 返回标题化字符串,每个单词首字母改为大写,，其他都为小写
print('8s9 a8D3vF'.swapcase());  # 字母大小写转换

print();print(' love'.join('1234')); # 1234每个字符被插入 love 
print();
print('  i love you.   '.lstrip()) # 去掉左侧空格
print('  i love you.   '.rstrip()) # 去掉右侧空格
print('#...abcde..feg ..#'.strip('.# ')) # 去掉字符串首尾指定字符串(多次重复实现)，默认' '
print();
print('abcdefg'.partition('cde')); #字符串分隔成3元组 （'ab','cde','fg'）
print('ab,cde,fg'.split(','));  #指定分隔符，分隔字符串形成list ['ab','cde','fg']
print('ab<>cde<>fg'.split('<>',1));   # 仅分隔第一个分隔符
print('abc\nde\r\nfeg\n'.splitlines()) #默认以换行符分隔成list   

trans = str.maketrans('a','1');print(trans); # 替换表是 dict
print('aaabbbbaaaacccc'.translate(trans))    # 用'1'(49) 替换 'a'(97)

dic = {97:49};
print('aaabbbbaaaacccc'.translate(dic))  # 同上2句，用asic码描述

print('123'.zfill(10))   # 指定长度右对齐，前面用0填充，符号最前
print('-1.23'.zfill(10))
# 基本所有操作，都可以有 逆序查找方法，添加‘r’在函数名前

