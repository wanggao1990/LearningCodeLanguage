## 隐藏， 使得请求从代码改为浏览器的正常请求。请求数据中增加heads, 修改User-Agent.
import urllib.request
import urllib.parse
import json

content = input('请输入要翻译的内容:')

url = "http://fy.iciba.com/ajax.php?a=fy"

data = {}
data['w'] = content
if content.isalpha():
    data.update({'f':'en','t':'zh'})
else:
    data.update({'f':'zh','t':'en'})
data = urllib.parse.urlencode(data).encode('utf-8')  

## 增加head的User-Agent，避免请求被识别为代码
## 第一种，生成前增加head ： Request的headers参数修改

head = {}
# 给成员赋值，不存在的时候，添加成员
head['User-Agent']='Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)'

req = urllib.request.Request(url,data,head)
response = urllib.request.urlopen(req)    # 默认opener
html = response.read().decode("utf-8")

## 第二种，生成后添加header ： Request.add_headers方法修改
'''
req = urllib.request.Request(url,data)
req.add_header('User-Agent','Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)')

response = urllib.request.urlopen(req)
html = response.read().decode("utf-8")
'''
## 解析 获取翻译结果
mean = json.loads(html)  

status = mean['status']

if not status: #中文
    print('翻译结果：%s' % mean['content']['word_mean'][0])
else:
    print('翻译结果：%s' % mean['content']['out'])
    
    
    
######  正常使用中，固定IP一段时间内频繁请求，会被屏蔽IP,修改User-Agent无效。
#   解决方法：代理， 延迟
## 方法一: 代理
# 步骤1、proxy_support = urllib.request.ProxyHandler({'类型':'代理ip:端口号'})
# 步骤2、opener = urllib.request.build_opener(proxy_support)
# 步骤3、临时使用opener.open(url)或者 urllib.request.install(opener)修改默认opener

import urllib.request

url = "http://www.whatip.com/"

# 避免Ip不稳定，建立一个代理ip的list，随便选择

proxy_support = urllib.request.ProxyHandler({'http':'211.105.217.35:8080'})

opener = urllib.request.build_opener(proxy_support)
opener.addheaders = [('User-Agent','Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36')]

response = opener.open(url)

html = response.read().decode('utf-8')

print(html)     ##### 貌似代理失败了

## 方法二: 延时
import urllib.request
import urllib.parse
import json

import time

while True:
    content = input('请输入要翻译的内容(输入"q!"退出):')
    
    if content == 'q!':
        break
    
    url = "http://fy.iciba.com/ajax.php?a=fy"
    
    data = {}
    data['w'] = content
    if content.isalpha():
        data.update({'f':'en','t':'zh'})
    else:
        data.update({'f':'zh','t':'en'})
    data = urllib.parse.urlencode(data).encode('utf-8')  
    
    
    req = urllib.request.Request(url,data)
    req.add_header('User-Agent','Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)')
    
    response = urllib.request.urlopen(req)
    html = response.read().decode("utf-8")
    
    
    mean = json.loads(html)  
    status = mean['status']
    if not status: #中文
        print('翻译结果：%s' % mean['content']['word_mean'][0])
    else:
        print('翻译结果：%s' % mean['content']['out'])
        
    time.sleep(3)