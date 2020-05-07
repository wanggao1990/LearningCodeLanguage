import re

## "\"和另一个字符组成的特殊函数， 和+、*等组合可以解除特殊功能

# \序号  1-99引用序号对应子组匹配的字符串   三位数0开头，八进制

# \A    匹配字符串的开始位置，同 [^  ]

# \Z    匹配字符串的结束位置，同 [  $]

# \b    单词边界，单词定义为Unidcode的字母或下横线字符组合的字符串 (其他字符都是单词的边界)
# \B    非单词边界   py\B  会匹配 "python" "py3", 不会匹配 “py “ “py.“ ”py!“
print(re.findall(r'\bFishC\b','FishC.com!FishC_com(FishC)')) # 匹配第一个和第二个

# \d    在Unicode模式下匹配0-9和其他数字字符， 八位、ASIC下仅匹配 0-9中的字符
# \D    与\d 作用相反 [^\d]
print(re.findall(r'\D','1a2b')) # ['a', 'b']

# \s    匹配Unicode模式的空白字符包括\t \n \r \f \v和其他空白字符，ASIC下仅匹配\t\n\r\f\v
# \S    与\s 作用相反 [^\s]

# \w    匹配Unicode模式的字符，包括数字和下横线； ASIC下仅匹配 [a-zA-Z0-9]
# \W    与\w 作用相反 [^\w]
print(re.findall(r'\w','中国 you u_8')) # ['中', '国', 'y', 'o', 'u', 'u', '_', '8']

# 转义符号(在字符串中)   "\b"退格 “\u”或“\U”在Unicode才能识别   


## 需要重复利用某个正则表达式，需要先编译，再使用，避免重复建立
p = re.compile(r"[A-Z]")
print(type(p))              # <class '_sre.SRE_Pattern'> 模式对象

print(p.search("I Love You"))   # "I"
print(p.findall("I Love You"))  # ['I', 'L', 'Y']


## 编译标志 修改正则表达式的工作方式
# ASCII, A        # \w,\b,\s,\d只能匹配asic字符
# DOTALL, S       # "."能匹配所有字符，包括换行符
# IGNORECASE, I   # 匹配的时候不区分大小写
# LOCALE, L       # 支持当前语言设置
# MULTILINE, M    # 多行匹配，影响$和^
# VERBOSE, x      # 启用详细的正则表达式，忽略空白（除字符类[]和转移字符的空格），可以使用注释

charref = re.compile(r"""
&[#]                # 开始数字引用
(
      0[0-7]+       # 八进制
    | [0-9]+        # 十进制
    | x[0-9a-fA-F]+ # 十六进制
)
;                   # 结尾分号
""", re.VERBOSE)

charref = re.compile('&#(0[0-7]+|[0-9]+|x[0-9a-fA-F]+);') # 可读性差
