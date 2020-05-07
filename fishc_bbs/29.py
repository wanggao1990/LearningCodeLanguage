#### 文件读写例子
##   文件record1.txt 是男、女对话，用若干个=组成的字符串行分成3段对话
##   将记录分别按性别和段保存在txt中
##   如 boy_1.txt,boy_2.txt,boy_3.txt  (去掉"男：")，女一样


## 第一种
def method1(file_name):
    file = open(file_name)
    boy = []
    girl = []
    count = 1

    for each_line in file:  
        if each_line[:4] != '====': # 值对前4个进行判断
            #字符串分割操作
            [role,line_spoken] = each_line.split('：',1) # 分割第一个出现的冒号，避免说话中有冒号
            if role == '男':
                boy.append(line_spoken)
            else:
                girl.append(line_spoken)
        else:
            #文件分别保存
            file_name_boy = 'boy_'+ str(count) + '.txt'
            file_name_girl = 'girl_'+ str(count) + '.txt'

            boy_file = open(file_name_boy,'w')
            girl_file = open(file_name_girl,'w')

            boy_file.writelines(boy)
            girl_file.writelines(girl)

            boy_file.close()
            girl_file.close()

            boy = []
            girl = []

            count += 1
            
    file.close()


## 第二种 ()

def method2(file_name):
    split_file(file_name)

def save_file(boy,girl,count): # 函数1
    file_name_boy = 'boy_'+ str(count) + '.txt'
    file_name_girl = 'girl_'+ str(count) + '.txt'
    
    boy_file = open(file_name_boy,'w')
    girl_file = open(file_name_girl,'w')

    boy_file.writelines(boy)
    girl_file.writelines(girl)

    boy_file.close()
    girl_file.close()


def split_file(file_name):        # 函数2
    file = open(file_name)
    boy = []
    girl = []
    count = 1

    for each_line in file:  
        if each_line[:4] != '====': # 值对前4个进行判断
            #字符串分割操作
            [role,line_spoken] = each_line.split('：',1) # 分割第一个出现的冒号，避免说话中有冒号
            if role == '男':
                boy.append(line_spoken)
            else:
                girl.append(line_spoken)
        else:
            #文件分别保存
            save_file(boy,girl,count)
            
            boy = []
            girl = []
            count += 1
   
    file.close()


### 执行
method1('record1.txt')  
#method2('record1.txt')  

