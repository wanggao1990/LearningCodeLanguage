import scrapy

from tutorial.items import DmozItem   #  不能写 tutorial/items;  类比 os.path

class DmozSpider(scrapy.Spider):
    
    name = "dmoz" # 确定的，唯一的

    allowed_domain = ['dmoztools.net']  # 限制爬虫范围
    start_urls = [
        'http://dmoztools.net/Science/Math/Publications/Books/',
        'http://dmoztools.net/Shopping/Visual_Arts/Digital_Art/'
        ]


    def parse(self,response):
        ## 第一种  3个list，再一一对应
        
        filename = response.xpath(
           '//*[@class="site-item "]/div[3]/a/div[1]/text()'
           ).extract()

        site = response.xpath(
           '//*[@class="site-item "]/div[3]/a/@href'
           ).extract()

        desc = response.xpath(
           '//*[@class="site-item "]/div[3]/div[1]/text()'
           ).extract() 

        # print('===============================================================')
        
        items = []
        
        for i in range(len(filename)):
            description = desc[2*i].lstrip()
            description = description.rstrip()
            # print(filename[i])
            # print(site[i])
            # print(description)
            # print()
            
            item = DmozItem()
            
            item['title'] = filename[i]
            item['link'] = site[i]
            item['desc'] = description
            
            items.append(item)
            
        return items

        # print('===============================================================')



       ## 第二种  先找到项的list，再一次提取三个属性

        # selc = scrapy.selector.Selector(response)
        # 
        # sites = selc.xpath('//*[@class="site-item "]/div[3]')

        # for site in sites:
        #     
        #    filename = site.xpath('a/div[1]/text()').extract()

        #     site = site.xpath('a/@href').extract() # 不需要text(), 不是标签
     
        #     desc = site.xpath('div[1]/text()').extract()
        #     
        #                 #  有span，会提取2个字符串，选择第一个
        #                 #  另外，应该去掉前、后的空格换行等。

        #       print(filename,site,desc)

#        with open(filename,'wb') as f:
#            f.write(response.body)


        
