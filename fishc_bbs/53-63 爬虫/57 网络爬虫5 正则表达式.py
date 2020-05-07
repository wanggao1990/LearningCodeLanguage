### 通过正则表达式获取IP

import re

## search 从字符串中搜索模式第一次出现的位置范围：查找模式需要用原始字符，r‘’表示； 查找不到，返回None
print(re.search(r'baidu','http://www.baidu.com'))  #位置范围  [11，16）

'http://www.baidu.com'.find('baidu');  # 返回的是 起始位置

## 通配符 "."   除换行符外所有字符。

print(re.search(r'.','http://www.baidu.com'))   # 找到 [0,1）, "h“
print(re.search(r'du.','http://www.baidu.com')) # 找到 [14,17）, "du.“

print(re.search(r'\.','http://www.baidu.com'))  # 找到 [10,11）, ".“  # 查找点号

## ”\d“  任何数字
print(re.search(r'\d','http://www.baidu123.com'))       # 找到 [16,17）, "1“  
print(re.search(r'\d\d\d','http://www.baidu123.com'))   # 找到 [16,19）, "123“   # 连续匹配



## ip地址 尝试

#  若按照 \d\d\d \. \d\d\d . \d\d\d . \d\d\d 查找， 那么只能 每个字段都要是三位数（IP地址字段0-255）

print(re.search(r'\d\d\d\.\d\d\d\.\d\d\d\.\d\d\d','http://192.168.11.100/html'))  # None
print(re.search(r'\d\d\d\.\d\d\d\.\d\d\.\d\d\d','http://192.168.11.100/html'))   # 可以找到

print(re.search(r'\d\d\d\.\d\d\d\.\d\d\d\.\d\d\d','http://192.168.111.100/html'))  
# 找到 [7, 22), match='192.168.111.100'

## "[]" 创建一个字符类，匹配任何一个字符，都算匹配 (元素中间 不加，)

print(re.search(r'[aeiou]','I love http://www.baidu123.com'))  # 找到 “o”   # 区分大小写

print(re.search(r'[a-z]','I love http://www.baidu123.com'))   # 匹配 a-z的任意一个字母， "I"
print(re.search(r'[0-9]','I love http://www.baidu123.com'))   # 匹配 0-9的任意一个数字， "1"
print(re.search(r'[2-9]','I love http://www.baidu123.com'))   # 匹配 2-9的任意一个数字， "2"

print(re.search(r'[0-255]','188')) # 查找是针对字符，这里匹配 0,1,2或5的4个数字任意一个数字，"1"
print(re.search(r'[0-2][0-5][0-5]','188')) # None，数字对于字符来说，只有 ‘0’-‘9’字符

# 匹配 0-255 的数字 , "|"逻辑或的意思
#   [01]\d\d ： 百位是0或1，十位和个位可以是任意数字          0-199
#   2[0-4]\d ： 百位是2，十位是0-4时， 个位可以是任意数字     200-249
#   25[0-5]\d ：百位是2，十位是5，个位只能是 0-5             250-254
print(re.search(r'[01]\d\d|2[0-4]\d|25[0-5]\d|','188')) # [0,3) "188"

##  *{n} 匹配*字符n次；   *{m,n} 匹配*字符m-n次
print(re.search(r'ab{3}c','abbbc'))   # 匹配a、b三次、c ,  [0,5) "abbbc"   

print(re.search(r'ab{3,10}c','abbbbbbbbc'))   # 匹配a、b(3-10次)、c ,  [0,10) "abbbbbbbbc"   


## 匹配 ip地址 

ip = '192.168.1.1'

print(re.search(r'[01]\d\d|2[0-4]\d|25[0-5]\.',ip))   # 匹配100-255的3位数

print(re.search(r'[01]{0,1}\d{0,1}\d{0,1}|2[0-4]\d|25[0-5]\.',ip))   # 匹配1-255的3位数

print(re.search(r'([01]\d\d|2[0-4]\d|25[0-5]\.){3}[01]\d\d|2[0-4]\d|25[0-5]',ip))  #None

##  “()“ 分组， 小组先匹配（包括数字和 "\."），匹配三次，最后匹配一次数字;  grop(0..N)分组结果

# 要求位数 必须是三位

ip = '192.168.0.123'

print(re.search(r'([01]\d\d|2[0-4]\d|25[0-5]\.){3}([01]\d\d|2[0-4]\d|25[0-5])',ip))  #None

print(re.search(r'([0,1]{0,1}\d{0,1}\d{0,1}|2[0-4]\d|25[0-5]\.){3}([0,1]{0,1}\d{0,1}\d{0,1}|2[0-4]\d|25[0-5]\.)',ip))  # 192

# 或 “|” 只能在 ()或[]中有效
res = re.search(r'(([0,1]{0,1}\d{0,1}\d{0,1}|2[0-4]\d|25[0-5])\.){3}([0,1]{0,1}\d{0,1}\d{0,1}|2[0-4]\d|25[0-5]\.)',ip)   
#  为什么需要数字先分组，再和点分组，再匹配3次，最后匹配一个数字  ？？？？？(不然 点和250-255在一起匹配)
print(res)  # 192.168.0.123  （最后一组括号 可以不需要）










