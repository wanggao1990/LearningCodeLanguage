## Python如何访问互联网 ?
#
####   urllib模块。
#   
#  URL一般格式 带[]的为可选项
#  protocol://hostname[:port]/path/[;parmeters][?query]#fragement 
#  
#  protocaol= 协议：http, https,ftp,file,ed2k,...
#  hostname = 域名或IP地址（有时需要端口号，http默认端口为80）
#  path = 资源具体位置。目录或文件名
#  

######################################
# urllib is a package that collects several modules for working with URLs:
#
# urllib.request for opening and reading URLs 
# urllib.error containing the exceptions raised by urllib.request 
# urllib.parse for parsing URLs 
# urllib.robotparser for parsing robots.txt files 
# 
import urllib.request

request = urllib.request.urlopen('http://wwww.baidu.com')

html = request.read()

html = html.decode("utf-8")

print(html)
