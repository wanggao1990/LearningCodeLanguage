## Scarpy 为爬去网站数据，提取结构性数据而编写的应用框架。
#  可用在数据挖掘，信息处理和存储数据等一系列的程序中。
#     网络抓取， 获取API返回的数据，通用的网络爬虫
#
#  python 3.5.3  先升级pip，再下载各种文件，逐步安装，最后pip install Scrapy

# 使用步骤： 
#
#   1、创建一个Scrapy项目
#       cnd: scapy startproject projName 
#   
#   2、定义一个Item容器
#       保存爬到的数据的容器，使用方法和python的字典类似
#       额外的保护机制来避免拼写错误导致的未定义字段错误
#       对需要保存的数据建立模型，用于存放在自定义的Item容器中
# 
#   3、编写爬虫
#       Spider是用用户编写用于从网站上爬去数据的类
#       包含一个用于下载的初始URL,然后是如何跟进网页中的链接以及如何分析页面中的内容，
#       还有提取生成Item的方法
#       
#       进入工程目录，cmd: scrapy crawl spiderName , 获取内容
# 
#   4、存储内容
#       Scrapy Selectors,是一种基于XPath 和 CSS 的表达式机制，四种基本方法：
#           xpath(): 传入xpath表达式，返回该表达式对应的所有节点的selector list
#           css():   传入csss表达式，返回该表达式对应的所有节点的selector list
#           extract():序列化该节点为unicode字符串并返回list
#           css():   根据传入的正则表达式对数据进行提取,返回unicode字符串列表list
# 
#       进入工程目录，cmd: scrapy shell "http://dmoztools.net/Shopping/Visual_Arts/Digital_Art/"
#           response.body       网页的body
#           response.headers    网页的header
# 
#       数据筛选：
#       XPath 是一门在网页中查找特定信息的语言，要比正则表达式容易些
#             /html/head/title: 选择html文档中<head>标签内的<title>元素
#             /html/head/title/text(): 选择上述<title>元素的文字
#             //td: 选择所有<td>元素
#             //td[@class="mine"]: 选择所具有class="mine"属性的div元素
# 
#           另外 ，response.xpath() ==  response.selector.xpath()
# 
#           response.xpath('//title') => 
#               [Selector xpath = '//title' date = '<title>DMOZ - Shopping: Visual Art: Dig'>]
#           
#           response.xpath('//title').extract() => 
#               ['<title>DMOZ - Shopping: Visual Art: Digitil Art</title>'] 
#           
#           response.xpath('//title/text()') => 
#               [Selector xpath = '//title/text()' date = '<title>DMOZ - Shopping: Visual Art: Digital Ar'>]
#           
#           response.xpath('//title/text()').extract( => 
#               ['DMOZ - Shopping: Visual Art: Digital Ar']         
#         
#           在一个Item在 <div calss = "site-item ">,下面又有3个div
#             第三个div[3] <dv class = "title-and-desc>，包含2个标签 a和div 
#                  a包含超链接URL，超链接名称； div（即div[1],也可以用全称）中//text()是描述   
#                  虽然a和div同级，但是 div[3]//div[1]//text 的结果同 div[3]//a//text相同
#                  a标签有两个属性 target 和 href，  我们需要提取href ,  利用 a/@href 即可
#   
#           
#           提取, name， url， desc：
#               name =>  
#                   response.xpath('//*[@class="site-item "]/div[3]/a/div[1]/text()').extract()
#                                                    div[1] == div[@class="site-descr "] 
# 
#               url =>  
#                   response.xpath('//*[@class="site-item "]//div[3]//a//@href').extract()
# 
#               desc =>  
#                   response.xpath('//*[@class="site-item "]/div[3]/*[@class="site-descr "]/text()').extract()    
#                   response.xpath('//*[@class="site-item "]/div[3]/div[1]/text()').extract()      
#                        # div[3]下只有一个div，div[1]可以直接写div
#                        #  另外 有一个span标签，或提取一个空白，相当于一个desc有2个字符串


#          shell下提取完毕，exit()退出，修改 Spider文件，写入分析提取的方法
#          
#           最后运行程序   cmd: scrapy crawl spiderName
# 
#            每个查找结果用 Item容器保存，并返回一个list，并保存为json格式
#               from tutorial.items import DmozItem 
#                   item = DmozItem()
#                   item['title'] = filename[i]
#                   item['link'] = site[i]
#                   item['desc'] = description

#           保存 cmd: scrapy crawl dmoz -o items.json -t json