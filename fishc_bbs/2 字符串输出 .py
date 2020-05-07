
temp = input("intput a integer 0-100: ")

temp = int(temp)  # 字符串按照指定的进制转换


if 0 < temp < 100:     # if temp <100 and temp > 0, C格式，等效，但繁琐
    
    print('nice, you are right\n')
else:
    print('you are so wrong!')

 
print(' 2 & 1 = ', 2&1, 'a', str(temp))

print()  #空行


# 长语句可以使用反斜杠或者括号,或者两者组合分解成多行
# 在 shell 中直接输入括号的内容
st = '1231242' \
'asdas '   \
'1\n'

print(st)

st = ('1231=242')
('121')
'asdas '\
'1\n'

print(st)


