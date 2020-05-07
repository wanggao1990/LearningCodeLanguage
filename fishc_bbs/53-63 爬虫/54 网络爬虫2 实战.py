##### Python如何访问互联网 ?
#
#  urllib模块
#   
#  URL一般格式 带[]的为可选项
#  protocol://hostname[:port]/path/[;parmeters][?query]#fragement 
#  
#  protocaol= 协议：http, https,ftp,file,ed2k,...
#  hostname = 域名或IP地址（有时需要端口号，http默认端口为80）
#  path = 资源具体位置。目录或文件名
#  
#
### urllib is a package that collects several modules for working with URLs:
#
# urllib.request for opening and reading URLs 
# urllib.error containing the exceptions raised by urllib.request 
# urllib.parse for parsing URLs 
# urllib.robotparser for parsing robots.txt files 
# 
import urllib.request

## 例子：下载一个图片
#
# response = urllib.request.urlopen("http://placekitten.com/g/500/600")
# 上一句等效于下面两句
req = urllib.request.Request("http://placekitten.com/g/500/500")
response = urllib.request.urlopen(req)

# response可以当做一个文件数据
cat_img = response.read()

with open('cat_500_500.jpg','wb') as f:
	f.write(cat_img)


#查看信息
print(response.geturl());print()
print(response.info())

print(response.getcode())   # 200 正常响应



## 例子：利用有道词典翻译文本
#
#
import urllib.request
import urllib.parse
import json


content = input('请输入要翻译的内容:')

if content.isalpha():
	data =  {'f':'en','t':'zh','w':content}
else:
	data =  {'f':'zh','t':'en','w':content}
url = "http://fy.iciba.com/ajax.php?a=fy"

# data should be a buffer in the standard 
# application/x-www-form-urlencoded format. 
# The urllib.parse.urlencode() function takesa 
# mapping or sequence of 2-tuples and returns 
# a string in this format. 

data = urllib.parse.urlencode(data).encode('utf-8')  #增加模块 parse

response = urllib.request.urlopen(url,data)

html = response.read().decode("utf-8")

# print(html)      # 返回的是一个 json串

mean = json.loads(html)  # json 串转换成 dict

if mean['status'] == 1:
	print('被识别为机器翻译，访问失败！')    ## 请求失败。
else:
	print('翻译结果：%s' % mean['content']['word_mean'][0])
