# 将列表、元祖、词典、字符串等转化成数据类型 （正向简单，逆向复杂）

import pickle

import urllib.request
import json


my_list = [123,3.14,'Win',['another list']]

pickle_file = open('my_list.pkl','wb')  # 二进制写

pickle.dump(my_list,pickle_file)

pickle_file.close()



pickle_file = open('my_list.pkl','rb')  # 二进制读
my_list2 = pickle.load(pickle_file)

print(my_list2)


#### 天气
pickle_file  = open('city_data.pkl','rb')  # 二进制读
city = pickle.load(pickle_file)

print(city)

password=input('请输入城市:')
name1=city[password]
#File1 =urllib.request.urlopen('http://www.m.weather.com.cn/data/cityinfo/'+name1+'.html')#打开url

File1 =urllib.request.urlopen('http://www.weather.com.cn/data/cityinfo/101010100.html')


weatherHTML= File1.read().decode('utf-8')#读入打开的url
weatherJSON = json.JSONDecoder().decode(weatherHTML)#创建json
weatherInfo = weatherJSON['weatherinfo']


#打印信息
print ('城市：', weatherInfo['city'])
print ('时间：', weatherInfo['ptime'])
print ('天气：', weatherInfo['weather'])
print ('温度：', weatherInfo['temp1'],'~', weatherInfo['temp2'])

input ('按任意键退出：')
