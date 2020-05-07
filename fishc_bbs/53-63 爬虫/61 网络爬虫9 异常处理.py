# 网络异常处理 URLError ，其子集 HTTPError （同时捕捉是，将HTTP放在前面检测）

import urllib.request
import urllib.error

## 

req = urllib.request.Request("http://www.baidu.com")

try:
    urllib.request.urlopen(req)
except urllib.error.URLError as e:
    print(e.reason)
else:
    print('conneted!')   # 没有错误抛出时执行。
 
 ##   
    
req = urllib.request.Request("http://www.baidu-oxox-wanggao.com")
try:
    urllib.request.urlopen(req)
except urllib.error.HTTPError as e:
    print(e.reason)
    print(e.code())
    print(e.read())  
# else:
#     print('conneted!')   # 没有错误抛出时执行。

## 异常处理， 同时捕捉是，将HTTP放在前面检测）

# 第一种
try:
    pass
except urllib.error.HTTPError as e:
    pass
except urllib.error.URLError as e:
    pass
    
# 第二种 推荐
try:
    pass
except urllib.error.URLError as e:
    if  hasattr(e,'reason'):
         print(e.reason)
    elif hasattr(e,'code'):
         print(e.code)
else:
    # everything is fine
    pass
    
