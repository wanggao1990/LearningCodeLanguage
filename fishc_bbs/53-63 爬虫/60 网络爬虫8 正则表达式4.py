import re

## search() 模块的方法，对象的方法; 不会立即返回结果
# re.search(pattern, string, flags=0)   # flags 匹配模式
# regex.search(string[, pos[, endpos]]) # 查找其实和结束位置

res = re.search(r' (\w+) (\w+)','I love you') # ' love you' #通过子组()捕获结果
print(res)              # <_sre.SRE_Match object; span=(1, 10), match=' love you'>
print(res.groups())     # ('love', 'you')
print(res.group(0))     # ' love you'
print(res.group(1))     # 'love'
print(res.group(2))     # 'love'

print(res.start())  # 1
print(res.end())    # 10
print(res.span())   # （1，10）

## findall() （没有字子组）所有匹配结果以list返回；   有子组就？？？？
# 例子1 下载图片 贴吧 女神
import urllib.request
import os

#url = "https://tieba.baidu.com/p/5103208585"
url = "https://tieba.baidu.com/p/5089097170"

req = urllib.request.urlopen(url)
html =req.read().decode("utf-8")


# p = r'<img class="BDE_Image".+?src="[^"]+jpg"'   #未分组，获取的 '<img ... jpg"'
p = r'<img class="BDE_Image".+?src="([^"]+\.jpg)'  # 分组 获取的 ‘http...jpg'

urlList = re.findall(p,html)

folder = "女神吧"
os.makedirs(folder, exist_ok=True) # 标记，存在则不处理
os.chdir(folder)   # 创建文件夹，并进入该文件夹

for each_url in urlList:
    flie_name = each_url.split('/')[-1]   # 分隔后是list,取最后一个
   
    '''
    with open(flie_name,'wb') as f:
        data = urllib.request.urlopen(each_url).read()
        f.write(data)
    '''
    
    urllib.request.urlretrieve(each_url,flie_name,None)   # 自动下载文件到当前目录


## 如果匹配中只有一个子组(),会将匹配的子组以list返回;  多个()时，返回多个（有层次）
#  例：查找网页中的的代理ip地址

for i in range(10):
    #== 打开网页
    url = "http://www.kuaidaili.com/" + "proxylist/" + str(i)
    
    req = urllib.request.urlopen(url)
    html =req.read().decode("utf-8")
    
    #== 建立正则式
    
    # 由于子组，返回结果不是我们需要的
    # p = r'(([01]?\d?\d?|2[0-4]\d|25[0-5])\.){3}([01]?\d?\d?|2[0-4]\d|25[0-5])' 
    
    # 解决1：增加最外一层，返回结果的list元素为tuple,第一个就是完全的结果 group(0)
    # p = r'((([01]?\d?\d?|2[0-4]\d|25[0-5])\.){3}([01]?\d?\d?|2[0-4]\d|25[0-5]))'
  
    # 解决2：扩展语法   (?:...)不分组  （建议使用该方法，相对上一个可读行要差一点）
    p = r'(?:(?:[01]?\d?\d?|2[0-4]\d|25[0-5])\.){3}(?:[01]?\d?\d?|2[0-4]\d|25[0-5])' 
     
    #== 查询
    ipList = re.findall(p,html)
    # 若有子组，结果是list，其元素tuple对应group(0),group(1),group(2),group(3),..
   
    #== 打印
    for ip in ipList:
        print(ip)
        
    # for ip in ipList:
    #     print(ip[0])  # group(0)

