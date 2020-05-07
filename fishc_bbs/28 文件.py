##   通过 help(open) 查看使用方法
##
##　open(file, mode='r', buffering=-1, encoding=None, errors=None,
##        newline=None, closefd=True, opener=None)
#
#    ========= ===============================================================
#    Character Meaning
#    --------- ---------------------------------------------------------------
#    'r'       只读（默认）
#    'w'       写，文件存在会被覆盖 （很危险，需要先判断文件是否存在）
#    'x'       创建并写入，若存在则报错
#    'a'       创建并写入；若存在，则末尾追加
#    'b'       二进制打开
#    't'       文本模式打开（默认）
#    '+'       可读写模式，添加到其他模式中使用(和r,w组合)
#    'U'       换行符支持(弃用)
#    ========= ===============================================================

## 打开文件
f = open('record.txt')      # 默认'rt'模式
print(f);       # <_io.TextIOWrapper name='record.txt' mode='r' encoding='cp936'>

## read
print(f.read()) # 会读取所有的文本，文件指针会自动下移
print(f.read()) # 已经读完，再读为空 

print(f.read(5)) # 试图读五个字符，但是这里文件指针已经指向最后文件一个字符

f.close()
f = open('record.txt')  #文件指针指向第一字符（0），

print(f.read(4))    #读取4个字符

## 文件指针位置
print(f.tell())     #文件指针(按照字节)为8 （一个中文字符占用2，英文字符1）


## 移动文件指针（字节）
f.seek(45)   # 第一个参数，偏移；第二个参数，默认文件开头0； 当前1； 文件尾，2
             # 汉字占两个字节如某个汉字在指针0处，占用0、1两个字节序号，
             # 下一个字符从2开始，若移动指针到1，就出错

## 打印
# 第一种 不推荐
f.seek(0)
ls = list(f)                # 转化成list
for each_line in ls:
    print(each_line,end='') # f文件每一行字符串都有换行，print的时候限定end='',否则会多空一行

# 第二种 推荐（第二种的简化版，官方推荐 ==》 文件也是 可迭代的对象？？）
print();print()
f.seek(0)                   # 这里必须进行重新定位(文件操作都是按当前的指针操作的)
for each_line in f:         # 文件对象也是可以迭代的，迭代值就是一行
    print(each_line,end='')

## 读行  readline、readlines
print();print()
f.seek(2)
for i in range(0,10):
    print(f.readline(),end='')

print();print()
f.seek(512)
ls = f.readlines();print(ls)    # 将文件当前指针以后的数据按行str的list
                                # 指针为文件头时 ls = f.readlines() 等于 ls = list(f) 

#f.write('I love you')           # 不可写入（因为当前文件是只读模式，修改文件模式）

## 关闭， python会自动关闭
f.close()


## 写文件
f = open('record2.txt','w')
f.write('I love you\n')

object1 = ['i hate you\n','i like you\n']  
f.writelines(object1)   # 以此将可迭代对象的元素当做行进行写入

f.close() # 不关闭，内容在缓冲区，没有保存在磁盘中
    
