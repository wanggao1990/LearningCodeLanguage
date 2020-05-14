#!/usr/bin/ruby -w
#encoding: GBK

puts "你好，Rubby"

#  puts print 都是向控制台打印字符，其中puts带回车换行符 
 
 
 # "Here Document" 是指建立多行字符串。在 << 之后，您可以指定一个字符串或标识符来终止字符串，
 # 且当前行之后直到终止符为止的所有行是字符串的值。如果终止符用引号括起，引号的类型决定了面
 # 向行的字符串类型。请注意<< 和终止符之间必须没有空格。

puts  "====================== 多行 =======================";
print <<EOF
    这是第一种方式创建here document 。
    多行字符串。
EOF
 
print <<"EOF";                # 与上面相同
    这是第二种方式创建here document 。
    多行字符串。
EOF

print <<`EOC`                 # 执行命令
    echo hi there
    echo lo there
EOC
 
print <<"foo", <<"bar"          # 您可以把它们进行堆叠
    I said foo.
foo
    I said bar.
bar

puts  "===================== BEGIN END ======================";
=begin
puts "这是主 Ruby 程序"
END { # 程序结尾调用， 和放在什么位置无关
   puts "停止 Ruby 程序"   
}
BEGIN {  #程序运行前执行， 和放在什么位置无关
   puts "初始化 Ruby 程序"
}
=end

#### 注释

#

=begin
  这也是注释
=end

puts  "==================== 数据类型 ===================="

# 基本的 Number、String、Ranges、Symbols，以及true、false和nil，
# 数据结构 Array和Hash。
=begin
123                  # Fixnum 十进制
1_234                # Fixnum 带有下划线的十进制 （下划线字符在数字字符串中被忽略。）
-500                 # 负的 Fixnum
0377                 # 八进制
0xff                 # 十六进制
0b1011               # 二进制
"a".ord              # "a" 的字符编码
?\n                  # 换行符（0x0a）的编码
12345678901234567890 # 大数

123.4                # 浮点值
1.0e6                # 科学记数法
4E20                 # 不是必需的
4e+20                # 指数前的符号

=end
 
#整型 Integer 以下是一些整型字面量 
#字面量（literal）：代码中能见到的值，数值，bool值，字符串等都叫字面量 
#如以下的0,1_000_000,0xa等 
a1=0 
 
#带千分符的整型 
a2=1_000_000 
 
#其它进制的表示 
a3=0xa 
puts a1,a2 
puts a3 
 
#puts print 都是向控制台打印字符，其中puts带回车换行符 
=begin 
			这是注释，称作：嵌入式文档注释 
			类似C#中的/**/ 
=end

#浮点型 
f1=0.0 
f2=2.1 
f3=1000000.1 
puts f3

# 加减乘除操作符：+-*/；指数操作符为**
puts 2**(1/4)#1与4的商为0，然后2的0次方为1 
puts 16**(1/4.0)#1与4.0的商为0.25（四分之一），然后开四次方根

puts 'escape using "\\"';
puts 'That\'s right';

#####    #{ expr } 替换任意 Ruby 表达式的值为一个字符串。在这里，expr 可以是任意的 Ruby 表达式。
puts ;
puts "相乘 : #{24*60*60}";

name="Ruby" 
puts name 
puts "#{name+",ok"}"

## 数组字面量通过[]中以逗号分隔定义，且支持range定义。
#
#（1）数组通过[]索引访问
#（2）通过赋值操作插入、删除、替换元素
#（3）通过+，－号进行合并和删除元素，且集合做为新集合出现
#（4）通过<<号向原数据追加元素
#（5）通过*号重复数组元素
#（6）通过｜和&符号做并集和交集操作（注意顺序）
puts ;
ary = [ "fred", 10, 3.14, "This is a string", "last element", ]
puts ary[0]
ary<<0x12
ary.each do |i|
    puts i
end

## Ruby 哈希是在大括号内放置一系列键/值对，键和值之间使用逗号和序列 => 分隔。尾部的逗号会被忽略。
puts ;
hsh = colors = { "red" => 0xf00, "green" => 0x0f0, "blue" => 0x00f }
hsh.each do |key, value|
    print key, " is ", value, "\n"
end

# s..e 和 s...e 来构造，或者通过 Range.new 来构造  
puts ;
(10..15).each do |n|     #   s..e    []
    print n, ' '
end
puts ;
(10...15).each do |n|    # s...e   [)
    print n, ' '
end

puts ;
puts ('a'..'d').to_a

puts  "\n==================== Ruby 类和对象 ===================="
# 在 Ruby 中，类和方法也可以被当作常量。

$global_variable = 10   # 全局变量

# 未初始化的实例变量的值为 nil

class Customer
	 VAR1 = 100  # 常量
   VAR2 = 200

   @@no_of_customers=0   # 类变量，静态变量
   def initialize(id, name, addr)   # 方法名总是以小写字母
      @cust_id=id	       # 实例变量， 成员变量
      @cust_name=name
      @cust_addr=addr
   end

   def display_details()
      puts "Customer id #@cust_id"   # 文本和带有符号（#）的实例变量应使用双引号标记。
      puts "Customer name #@cust_name"
      puts "Customer address #@cust_addr"
    end
    
    def total_no_of_customers()
       @@no_of_customers += 1
       puts "Total number of customers: #@@no_of_customers"
    end
    
     def print_global
      puts "全局变量在 Class1 中输出为 #$global_variable"
  	end 
end

cust1=Customer.new("1", "John", "Wisdom Apartments, Ludhiya")
cust2=Customer.new("2", "Poul", "New Empire road, Khandala")

cust1.display_details()
cust1.total_no_of_customers()
cust2.display_details()
cust2.total_no_of_customers()

cust3 = cust2


puts  "\n==================== Ruby 伪变量 ===================="
# self: 当前方法的接收器对象。
# true: 代表 true 的值。
# false: 代表 false 的值。
# nil: 代表 undefined 的值。
# __FILE__: 当前源文件的名称。
# __LINE__: 当前行在源文件中的编号。

puts  "\n==================== Ruby 运算符 ===================="


puts (1...10) === 5    # 检测是否在范围内
puts  1 == 1.0 
puts 1.eql?(1.0)       # 具有相同的类型和相等的值，
puts cust2.equal?cust3 # 具有相同的对象 id,(副本) 

a, b, c = 10, 20, 30   #并行赋值
a, b = b, c    				# 交换

# defined? 方法调用的形式来判断传递的表达式是否已定义。它返回表达式的描述字符串，如果表达式未定义则返回 nil。
foo = 42
puts defined? foo    # => "local-variable"
puts defined? $_     # => "global-variable"
puts defined? bar    # => nil（未定义）

puts defined? puts        # => "method"
puts defined? puts(bar)   # => nil（在这里 bar 未定义）
puts defined? unpack      # => nil（在这里未定义）



# 方法名称前加上类或模块名称和 . 来调用类或模块中的方法。
# 类或模块名称和两个冒号 :: 来引用类或模块中的常量

MR_COUNT = 0        # 定义在主 Object 类上的常量
module Foo
  MR_COUNT = 0
  ::MR_COUNT = 1    # 设置全局计数为 1
  MR_COUNT = 2      # 设置局部计数为 2
end
puts MR_COUNT       # 这是全局常量
puts Foo::MR_COUNT  # 这是 "Foo" 的局部常量

CONST = ' out there'
class Inside_one
   CONST = proc {' in there'}
   def where_is_my_CONST
      ::CONST + ' inside one'
   end
end
class Inside_two
   CONST = ' inside two'
   def where_is_my_CONST
      CONST
   end
end
puts Inside_one.new.where_is_my_CONST
puts Inside_two.new.where_is_my_CONST
puts Object::CONST + Inside_two::CONST
puts Inside_two::CONST + CONST
puts Inside_one::CONST
puts Inside_one::CONST.call + Inside_two::CONST



puts  "\n==================== 条件判断 ===================="

x=1
if x > 2
   puts "x 大于 2"
elsif x <= 2 and x!=0
   puts "x 是 1"
else
   puts "无法得知 x 的值"
end

$debug=1
print "debug\n" if $debug

x=1
unless x>2
   puts "x 小于 2"
 else
  puts "x 大于 2"
end

$var =  1
print "1 -- 这一行输出\n" if $var
print "2 -- 这一行不输出\n" unless $var
 
$var = false
print "3 -- 这一行输出\n" unless $var


$age =  5
case $age
when 0 .. 2
    puts "婴儿"
when 3 .. 6
    puts "小孩"
when 7 .. 12
    puts "child"
when 13 .. 18
    puts "少年"
else
    puts "其他年龄段的"
end

# 当case的"表达式"部分被省略时，将计算第一个when条件部分为真的表达式。
foo = false
bar = true
quu = false
case
when foo then puts 'foo is true'
when bar then puts 'bar is true'
when quu then puts 'quu is true'
end

## for
for i in 0..5
   print  "#{i} "
end
puts ;
(0..5).each do |i|
   print  "#{i} "
end

# break 
for i in 0..5
   if i > 2 then
      break
   end
   puts "局部变量的值为 #{i}"
end

# next    （continue）
for i in 0..5
   if i < 2 then
      next
   end
   puts "局部变量的值为 #{i}"
end

puts  "\n==================== 方法 ===================="

# 默认参数
def test(a1, a2="Perl")
   puts "编程语言为 #{a1}"
   puts "编程语言为 #{a2}"
end
test "C", "C++"
test "ruby"      # 第二个参数默认 ,     函数访问可以带括号 test("ruby") 


# 无返回值
def test
   i = 100
   j = 10
   k = 0   # 没有返回语句，默认最后一个语句的结果
end     
puts test   

# 返回值
def test
   i = 100
   j = 200
   k = 300
return i, j, k
end
var = test
print var   # 打印数组整体
puts " ",var   # 顺序打印数组元素

# 可变
def sample (*test)
   print "参数个数为 #{test.length} : "
   for i in 0...test.length
      print " #{test[i]}, "
   end
   puts;
end
sample "Zara", "6", "F"
sample "Mac", "36", "M", "MCA"


################ 模块 
$LOAD_PATH << '.'
require "support" # 引入文件 support.rb

class Decade
include Week   
   no_of_yrs=10
   def no_of_months
      puts Week::FIRST_DAY
      number=10*12
      puts number
   end
end
d1=Decade.new
puts Week::FIRST_DAY
Week.weeks_in_month
Week.weeks_in_year
d1.no_of_months

puts  "\n==================== 字符串 ===================="

name1 = "Joe"
name2 = "Mary"
puts "你好 #{name1},  #{name2} 在哪?"

x, y, z = 12, 36, 72
puts "x 的值为 #{ x }"
puts "x + y 的值为 #{ x + y }"
puts "x + y + z 的平均值为 #{ (x + y + z)/3 }"

desc1 = %Q{Ruby 的字符串可以使用 '' 和 ""。}
desc2 = %q|Ruby 的字符串可以使用 '' 和 ""。|
puts desc1
puts desc2

###

#字符编码
# Ruby 的默认字符集是 ASCII，字符可用单个字节表示。如果您使用 UTF-8 或其他现代的字符集，字符可能是用一个到四个字节表示。
# 您可以在程序开头使用 $KCODE 改变字符集，如下所示：
# $KCODE = 'u'

#myStr = String.new("THIS IS TEST")
myStr = "THIS IS TEST"
foo = myStr.downcase
puts "#{foo}"

len = myStr.length
print myStr[0, len],"\n"

puts  "\n==================== 数组 ===================="

# puts Array.new(20)
print Array.new(4, "mac"),"\n"
print Array.new(10) { |e| e = e * 2 },"\n"

puts  "\n==================== hash ===================="

H = Hash["a" => 100, "b" => 200]
puts "#{H['a']}"
puts "#{H['b']}"


$, = ", "
months = Hash.new( "month" )
months = {"1" => "January", "2" => "February"}
keys = months.keys 
puts "#{keys}"

for k,v in months do
	 print "#{k} = #{v} \n"
end

sum = 0
cutcome = {"block1" => 1000, "book2" => 1000, "book3" => 4000}
cutcome.each{|item, price| sum += price}
print "sum = " + sum.to_s

puts  "\n==================== Time 的组件 ===================="

time = Time.new
# Time 的组件 [sec,min,hour,day,month,year,wday,yday,isdst,zone]
puts "当前时间 : " + time.inspect
puts time.year    # => 日期的年份
puts time.month   # => 日期的月份（1 到 12）
puts time.day     # => 一个月中的第几天（1 到 31）
puts time.wday    # => 一周中的星期几（0 是星期日）
puts time.yday    # => 365：一年中的第几天
puts time.hour    # => 23：24 小时制
puts time.min     # => 59
puts time.sec     # => 59
puts time.usec    # => 999999：微秒
puts time.zone    # => "UTC"：时区名称

puts time.to_s
puts time.ctime
puts time.localtime
puts time.strftime("%Y-%m-%d %H:%M:%S")

# July 8, 2008
Time.local(2008, 7, 8)  
# July 8, 2008, 09:10am，本地时间
Time.local(2008, 7, 8, 9, 10)   
# July 8, 2008, 09:10 UTC
Time.utc(2008, 7, 8, 9, 10)  
# July 8, 2008, 09:10:11 GMT （与 UTC 相同）
Time.gm(2008, 7, 8, 9, 10, 11)


values = time.to_a
puts Time.utc(*values)


puts  "\n==================== 文件、目录操作 ===================="

File.open("file.txt", "r") do |file|
   # ... process the file
  # file.syswrite("ABCDEF")
   
   	puts ;
   file.rewind
   file.each_byte {|ch| putc ch; putc ?. }
   	
   	puts ;
    #IO.readlines("file.txt").each { |line| puts line}
		for line in IO.readlines("file.txt") do 
			print "#{line}"
		end
		
		puts ;
		IO.foreach("file.txt"){|block| puts block}
end

puts ;
puts File.open("file.rb") if File::exists?( "file.rb" )
puts File.file?( "file.txt" )
puts File::directory?( "/usr/local/bin" ) 
puts File::directory?( "file.txt" ) 
puts File.readable?( "file.txt" )   # => 是否可读
puts File.writable?( "file.txt" )   # => 是否可写
puts File.executable?( "file.txt" ) # => 是否可读可写可执行
puts File.zero?( "file.txt" )       # => 文件大小为0
puts File.size?( "file.txt" )						# 文件大小
puts File::ftype( "file.txt" ) 


# Dir.chdir("/usr/bin")
puts Dir.pwd
print Dir.entries("./").join(' '),"\n"

puts ; 
Dir.foreach("./") do |entry|
   puts entry
end

puts ; 
Dir["./*"]

puts ; 
Dir.mkdir("mynewdir")
Dir.mkdir( "mynewdir", 755 )
Dir.delete("testdir")

require 'tmpdir'
tempfilename = File.join(Dir.tmpdir, "tingtong")
tempfile = File.new(tempfilename, "w")
tempfile.puts "This is a temporary file"
puts tempfilename
aa = gets 
tempfile.close
File.delete(tempfilename)

require 'tempfile'
f = Tempfile.new('tingtong')
f.puts "Hello"
puts f.path
f.close