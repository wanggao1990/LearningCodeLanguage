import urllib.request
import urllib.parse
import json

import os

def url_open(url):
    req = urllib.request.Request(url)
    req.add_header('User-Agent','Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)')
    response = urllib.request.urlopen(url)    # 默认opener
    html = response.read()   # 图片不能解码
    
    return html

def get_page(url):
    
    html = url_open(url).decode('utf-8')
    
    # 获取当前页面的图片标记数
    a = html.find('current-comment-page') + 23
    b = html.find(']',a)
    
    return html[a:b]
    
def find_img(url):
     html = url_open(url).decode('utf-8')
     img_addrs = []
     
     a = html.find('img src=')
    
     while a != -1:
         b = html.find('.jpg',a,a+255)  # 网页地址不会超过长度 255
         if b != -1:
             img_addrs.append(html[a+9:b+4])
         else:
             b = a + 9
            
         a = html.find('img src=', b)
        
     return img_addrs
     

def save_imgs(folder,img_addrs):
    for each in img_addrs:
        filename = each.split('/')[-1]  # 分隔，保留最后的一个s
        with open(filename,'wb') as f:
            img = url_open(each)
            f.write(img)
        

def download_mm(folder = 'OOXX',pages = 10):
    
    os.makedirs(folder,exist_ok = True)
    os.chdir(folder) #创建文件夹，并进入该文件夹
    
    url = "http://jandan.net/ooxx/"
    
    page_num = int(get_page(url))
    
    for i in range(pages):
        page_num -= i
        
        page_url = url + 'page-' + str(page_num) + '#comments'  #当前页面
        
        img_addrs = find_img( page_url) # 页面下所有图片的地址
        
        save_imgs(folder,img_addrs) # 保存当前页面下所有图片到指定目录
        
if __name__ =='__main__':
    
    download_mm()
    
