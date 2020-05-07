import random

secret = random.randint(1,10);

temp = input('输入一个数字：')

#判断字符串temp的所有字符的类型

temp.isdigit() #数字

temp.isalnum() # 所有字符都是数字或者字母，为真返回 Ture，否则返回 False。

temp.isalpha()  # 所有字符都是字母，为真返回 Ture，否则返回 False。

temp.isdigit()  #   所有字符都是数字，为真返回 Ture，否则返回 False。

temp.islower()  #  所有字符都是小写，为真返回 Ture，否则返回 False。

temp.isupper()  # 所有字符都是大写，为真返回 Ture，否则返回 False。

temp.istitle()  #   所有单词都是首字母大写，为真返回 Ture，否则返回 False。

temp.isspace() # 所有字符都是空白字符，为真返回 Ture，否则返回 False


temp = int(temp);

a=0;

while temp != secret and a<8 :
    if temp == secret:
        print('123123')
    else:
        if temp > secret:
            print('大了')
        else:
            print('小了')
    a += 1
    
    temp = input('输入一个数字：')
    temp=int(temp);
            
print('结束')


