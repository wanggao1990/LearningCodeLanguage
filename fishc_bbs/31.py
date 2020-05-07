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


####

pickle_file  = open('city_data.pkl','rb')  # 二进制读
city = pickle.load(pickle_file)

print(city)

password=input('请输入城市:')
name1=city[password]
#File1 =urllib.request.urlopen('http://m.weather.com.cn/data/'+name1+'.html')#打开url
File1 =urllib.request.urlopen('https://api.caiyunapp.com/v2/TAkhjf8d1nlSlspN/121.6544,25.1552/realtime.json')

print(File1)

weatherHTML= File1.read().decode('utf-8')#读入打开的url
weatherJSON = json.JSONDecoder().decode(weatherHTML)#创建json
weatherInfo = weatherJSON['weatherinfo']


#打印信息
print ( '城市：', weatherInfo['city'])
print ('时间：', weatherInfo['date_y'])
print ( '24小时天气：')
print ('温度：', weatherInfo['temp1'])
print ('天气：', weatherInfo['weather1'])
print ('风速：', weatherInfo['wind1'])
print ('紫外线：', weatherInfo['index_uv'])
print ('穿衣指数：', weatherInfo['index_d'])
print ('48小时天气：')
print ('温度：', weatherInfo['temp2'])
print ('天气：', weatherInfo['weather2'])
print ('风速：', weatherInfo['wind2'])
print ('紫外线：', weatherInfo['index48_uv'])
print ('穿衣指数：', weatherInfo['index48_d'])
print ('72小时天气：')
print ('温度：', weatherInfo['temp3'])
print ('天气：', weatherInfo['weather3'])
print ('风速：', weatherInfo['wind3'])
input ('按任意键退出：')
