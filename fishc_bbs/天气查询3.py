#!/usr/bin/python3
# -*- coding: utf-8 -*-

import os
import urllib.request
import sys
import json
import time
#import qqlib
#from qqlib import qzone
import random
import gzip
import zlib
import re

def get_weather(city):
    reg = r'[\u4E00-\u9FA5 ]'
    #api_key="xxxx"
    #weather_url="http://api.map.baidu.com/telematics/v3/weather?location="+city+"&output=json&ak="+api_key
    #print(weather_url)
    weather_url = 'http://wthrcdn.etouch.cn/weather_mini?citykey=101010100'
    request=urllib.request.Request(weather_url, headers={'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/52.0.2743.82 Safari/537.36'})
    try:
        res = urllib.request.urlopen(request)
    except urllib.error.HTTPError as e:
        print(e.getcode())
        print(e.reason)
        print(e.geturl())
        print('-----------------')
        print(e.info())
        print(e.read())
        return 'get weather api data error....'
    data = res.read()
    if(('Content-Encoding' in res.info()) and ( res.info()['Content-Encoding'] == 'gzip')):
        #data=zlib.decompress(data, 16+zlib.MAX_WBITS)
        data = gzip.decompress(data)
        data = str(data, 'utf-8')
    #json_data = res.read().decode('utf-8')
    #print(json_data)
    json_data = json.loads(data)
    #get json data
    #check result status
    status = json_data['status']
    
    if(status == 1000):
        '''
        results=json_data['results'][0]
        pm25=results['pm25']
        weather_data=results['weather_data']
        date=weather_data[0]['date']
        weather=weather_data[0]['weather']
        wind=weather_data[0]['wind']
        temperature=weather_data[0]['temperature'].replace('~','到')
        '''
        wdata = json_data['data']

        city = wdata['city']
        aqi = int(wdata['aqi'])
        temperature = wdata['wendu']
        forecast = wdata['forecast'][0]
        date = forecast['date']
        weather = forecast['type']
        wind = forecast['fengli']
        direction = forecast['fengxiang']
        high = re.sub(reg,'',forecast['high'])
        low = re.sub(reg,'',forecast['low'])
        level = ''
        if(aqi <= 50 and aqi > 0):
            level = '优秀'
        elif(aqi <= 100 and aqi > 50):
            level = '良好'
        elif(aqi <= 150 and aqi > 100):
            level = '一般'
        elif(aqi <= 200 and aqi > 150):
            level = '很差'
        else:
            level = '很差'
        return '{},今天是{} {}, 空气质量:{}{},当前温度{}[{} ~ {} ],{}{}.'.format(city,date,weather,aqi,level,temperature,low,high,direction,wind)
    else:
        return '获取百度API失败~'

def get_today():
    api_url = "http://www.ipip5.com/today/api.php?type=json"
    #api_url='https://brisk.eu.org/api/today-history.php'
    request=urllib.request.Request(api_url, headers={'User-Agent': 'Mozilla/5.0'})
    res = urllib.request.urlopen(request)
    json_data = res.read().decode('utf-8')
    #print(json_data)
    if json_data=='':
        return '获取历史上的今天失败~'
    json_data = json.loads(json_data)

    total = len(json_data['result'])
    num = random.randint(0,total)
    today = json_data['today']
    year = json_data['result'][num]['year']
    title = json_data['result'][num]['title']

    return '{}年{} {}'.format(year,today,title)
    '''
    total=len(json_data['res'])
    num=random.randint(0,total)
    return json_data['res'][num]
    '''

weather = get_weather('beijing')
today = get_today()
text = '[天气自动播报] {}\n[历史上的今天] {}\n'.format(weather,today)
print(text)
