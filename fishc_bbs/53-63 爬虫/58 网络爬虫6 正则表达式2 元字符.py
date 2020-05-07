import re

## re.findall()  查找所有匹配的字符串的list

##正则表达式 元字符
# . ^ $ * + {} [] \ | ()

# "."  匹配换行符意外的所有字符 （设置re.DOTALL后可匹配换行符）

# "|"  或

# "^"  从开始位置匹配字符串
print(re.search(r'^123','123abc')) # <_sre.SRE_Match object; span=(0, 3), match='123'>
print(re.search(r'^abc','123abc')) # None

# "$"  匹配到字符串结束位置
print(re.search(r'abc$','123abc')) # <_sre.SRE_Match object; span=(0, 3), match='123'>
print(re.search(r'123$','123abc')) # None

# "\"  
# 1、解除特殊字符  “\.” 表示字符“.”
# 2、 \1-99  引用序号对应的子组（用"()"括起来的）所匹配的字符串
# 3、 \d     表示0-9的数字字符
# 4、 \0212  0开始+数字， 表示八进制

print(re.search(r'(123)\1','123abc')) # None
print(re.search(r'(123)\1','123123')) # match='123123'

# [] 字符集合, 其中“.”就是.字符; 其中\是转义符; "^"表示取反，放在首位；
print(re.search(r'.','123abc'))     # 1
print(re.search(r'\.','123.abc'))   # .
print(re.search(r'[.]','123.abc'))  # .

print(re.findall(r'[0-9a-z]','123.abc'))  # ['1', '2', '3', 'a', 'b', 'c']
print(re.findall(r'[a-z]','123.abc'))  # ['a', 'b', 'c']

print(re.findall(r'[^a-z]','123.abc\n'))  # 取a-z以外的字符，['1', '2', '3', '.', '\n']
print(re.findall(r'[a-z^]','123.abc\n'))  # ['a', 'b', 'c']
print(re.findall(r'[a-z^]','123.abc\n^'))  # ['a', 'b', 'c', '^']

# {m}匹配前面的字符或者子组m次，  {m,n}匹配 m到n次
print(re.search(r'(ab){3}','123.ababababc\n^')) # 'ababab'

# “*” 匹配0次或者无穷多次    等价于 "{0,}"
# "+" 匹配1次或者无穷多次    等价于 "{1,}"   
# "?" 匹配0次或者1次        等价于 "{0,1}"   
# 上述三个都是贪婪模式，尽可能匹配多次；  和?组合就是非贪婪模式  *? 0次， +? 1 次， ?? 0次

print(re.search(r'ab*','123.abbc'))     # abb
print(re.search(r'ab*','123.abbbbc'))   # abbbb  
print(re.search(r'ab*','123.abbc'))     # abb

#.+表示尽可能匹配多（至少一个）的字符，<.+>表示前后用<>包围
print(re.search(r'<.+>','<123><3.1415><abc>'))  # <123><3.1415><abc>
print(re.search(r'<.+?>','<123><3.1415><abc>')) # 第一个就满足<123>