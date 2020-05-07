## 要求
#   - 定制一个定时器的类 
#   - start和stop方法代表启动和停止计时器
#   - 计时器对象t1, 调用print(t1),t1均显示结果 
#   - 未启动或者已经停止计时，调用stop提示
#   - 计时器对象可以相加，如t1 + t2
#   - 有限的资源完成:
#           time模块的localtime方法获取当前时间
#           纤细介绍见http://bbs.fishc.com/thread-51326-1-2.html
#           time.localtime返回struct_time元组的时间格式
#
#           输入类名，给出信息，需要重写 __str__ 和 __repr__
#


# 其他类似模块 datetime 、timeit

import time as tm

class Timer:
    "这里也可以说明"
    def __init__(self):
         
        self.tickLable = False

        print('提示：还没有开始计时')

    def __add__(self,other):
        
        total = tm.strftime("%H:%M:%S", tm.gmtime(self.elapsed + other.elapsed))

        return '共耗时 %f , %s' % (self.elapsed + other.elapsed,total)
 
    def start(self):
                                   
        self.startTime = tm.perf_counter()  # 返回1970开始的浮点秒数 ,系统运行时间（包括睡眠），进程运行时间 
                                            # time.time , time.perf_counter, time.process_time
        self.tickLable = True;

        print('开始计时')

    def stop(self):
        
        
        if False == self.tickLable:
            print('提示：还没开始计时')
            return
        
        self.endTime = tm.perf_counter()      # time.time , time.perf_count, time.process_time

        self.elapsed =self.endTime - self.startTime;
    
        self.tickLable = False;

        print('结束计时')

    def __str__(self):              ##  调用print(instanse)时，打印该方法获取字符串
                                    ##  需要用 print(t1)   
        return 'str: 总共运行了 {0} 秒'.format(self.elapsed)

    # __repr__ = __str__              ##  在shell中，直接输入类名，打印__repr__函数返回的字符串
                                    ##  这里复制后，实际是指向str方法返回的字符串

    def __repr__(self):            
        
        return 'repr: 当前时间 %s, 总共运行了 %s'  %( tm.asctime(),  tm.strftime("%H:%M:%S", tm.gmtime(self.elapsed)))
        

t1 =  Timer()
t1.start()
tm.sleep(2.5413212132)
t1.stop()

t2 =  Timer()
t2.start()
tm.sleep(1.62513212132)
t2.stop()

print(t1 + t2)

print(t1, t2)

