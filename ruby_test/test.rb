#!/usr/bin/ruby -w
#encoding: GBK

puts "��ã�Rubby"

#  puts print ���������̨��ӡ�ַ�������puts���س����з� 
 
 
 # "Here Document" ��ָ���������ַ������� << ֮��������ָ��һ���ַ������ʶ������ֹ�ַ�����
 # �ҵ�ǰ��֮��ֱ����ֹ��Ϊֹ�����������ַ�����ֵ�������ֹ���������������ŵ����;�������
 # ���е��ַ������͡���ע��<< ����ֹ��֮�����û�пո�

puts  "====================== ���� =======================";
print <<EOF
    ���ǵ�һ�ַ�ʽ����here document ��
    �����ַ�����
EOF
 
print <<"EOF";                # ��������ͬ
    ���ǵڶ��ַ�ʽ����here document ��
    �����ַ�����
EOF

print <<`EOC`                 # ִ������
    echo hi there
    echo lo there
EOC
 
print <<"foo", <<"bar"          # �����԰����ǽ��жѵ�
    I said foo.
foo
    I said bar.
bar

puts  "===================== BEGIN END ======================";
=begin
puts "������ Ruby ����"
END { # �����β���ã� �ͷ���ʲôλ���޹�
   puts "ֹͣ Ruby ����"   
}
BEGIN {  #��������ǰִ�У� �ͷ���ʲôλ���޹�
   puts "��ʼ�� Ruby ����"
}
=end

#### ע��

#

=begin
  ��Ҳ��ע��
=end

puts  "==================== �������� ===================="

# ������ Number��String��Ranges��Symbols���Լ�true��false��nil��
# ���ݽṹ Array��Hash��
=begin
123                  # Fixnum ʮ����
1_234                # Fixnum �����»��ߵ�ʮ���� ���»����ַ��������ַ����б����ԡ���
-500                 # ���� Fixnum
0377                 # �˽���
0xff                 # ʮ������
0b1011               # ������
"a".ord              # "a" ���ַ�����
?\n                  # ���з���0x0a���ı���
12345678901234567890 # ����

123.4                # ����ֵ
1.0e6                # ��ѧ������
4E20                 # ���Ǳ����
4e+20                # ָ��ǰ�ķ���

=end
 
#���� Integer ������һЩ���������� 
#��������literal�����������ܼ�����ֵ����ֵ��boolֵ���ַ����ȶ��������� 
#�����µ�0,1_000_000,0xa�� 
a1=0 
 
#��ǧ�ַ������� 
a2=1_000_000 
 
#�������Ƶı�ʾ 
a3=0xa 
puts a1,a2 
puts a3 
 
#puts print ���������̨��ӡ�ַ�������puts���س����з� 
=begin 
			����ע�ͣ�������Ƕ��ʽ�ĵ�ע�� 
			����C#�е�/**/ 
=end

#������ 
f1=0.0 
f2=2.1 
f3=1000000.1 
puts f3

# �Ӽ��˳���������+-*/��ָ��������Ϊ**
puts 2**(1/4)#1��4����Ϊ0��Ȼ��2��0�η�Ϊ1 
puts 16**(1/4.0)#1��4.0����Ϊ0.25���ķ�֮һ����Ȼ���Ĵη���

puts 'escape using "\\"';
puts 'That\'s right';

#####    #{ expr } �滻���� Ruby ���ʽ��ֵΪһ���ַ����������expr ����������� Ruby ���ʽ��
puts ;
puts "��� : #{24*60*60}";

name="Ruby" 
puts name 
puts "#{name+",ok"}"

## ����������ͨ��[]���Զ��ŷָ����壬��֧��range���塣
#
#��1������ͨ��[]��������
#��2��ͨ����ֵ�������롢ɾ�����滻Ԫ��
#��3��ͨ��+�����Ž��кϲ���ɾ��Ԫ�أ��Ҽ�����Ϊ�¼��ϳ���
#��4��ͨ��<<����ԭ����׷��Ԫ��
#��5��ͨ��*���ظ�����Ԫ��
#��6��ͨ������&�����������ͽ���������ע��˳��
puts ;
ary = [ "fred", 10, 3.14, "This is a string", "last element", ]
puts ary[0]
ary<<0x12
ary.each do |i|
    puts i
end

## Ruby ��ϣ���ڴ������ڷ���һϵ�м�/ֵ�ԣ�����ֵ֮��ʹ�ö��ź����� => �ָ���β���Ķ��Żᱻ���ԡ�
puts ;
hsh = colors = { "red" => 0xf00, "green" => 0x0f0, "blue" => 0x00f }
hsh.each do |key, value|
    print key, " is ", value, "\n"
end

# s..e �� s...e �����죬����ͨ�� Range.new ������  
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

puts  "\n==================== Ruby ��Ͷ��� ===================="
# �� Ruby �У���ͷ���Ҳ���Ա�����������

$global_variable = 10   # ȫ�ֱ���

# δ��ʼ����ʵ��������ֵΪ nil

class Customer
	 VAR1 = 100  # ����
   VAR2 = 200

   @@no_of_customers=0   # ���������̬����
   def initialize(id, name, addr)   # ������������Сд��ĸ
      @cust_id=id	       # ʵ�������� ��Ա����
      @cust_name=name
      @cust_addr=addr
   end

   def display_details()
      puts "Customer id #@cust_id"   # �ı��ʹ��з��ţ�#����ʵ������Ӧʹ��˫���ű�ǡ�
      puts "Customer name #@cust_name"
      puts "Customer address #@cust_addr"
    end
    
    def total_no_of_customers()
       @@no_of_customers += 1
       puts "Total number of customers: #@@no_of_customers"
    end
    
     def print_global
      puts "ȫ�ֱ����� Class1 �����Ϊ #$global_variable"
  	end 
end

cust1=Customer.new("1", "John", "Wisdom Apartments, Ludhiya")
cust2=Customer.new("2", "Poul", "New Empire road, Khandala")

cust1.display_details()
cust1.total_no_of_customers()
cust2.display_details()
cust2.total_no_of_customers()

cust3 = cust2


puts  "\n==================== Ruby α���� ===================="
# self: ��ǰ�����Ľ���������
# true: ���� true ��ֵ��
# false: ���� false ��ֵ��
# nil: ���� undefined ��ֵ��
# __FILE__: ��ǰԴ�ļ������ơ�
# __LINE__: ��ǰ����Դ�ļ��еı�š�

puts  "\n==================== Ruby ����� ===================="


puts (1...10) === 5    # ����Ƿ��ڷ�Χ��
puts  1 == 1.0 
puts 1.eql?(1.0)       # ������ͬ�����ͺ���ȵ�ֵ��
puts cust2.equal?cust3 # ������ͬ�Ķ��� id,(����) 

a, b, c = 10, 20, 30   #���и�ֵ
a, b = b, c    				# ����

# defined? �������õ���ʽ���жϴ��ݵı��ʽ�Ƿ��Ѷ��塣�����ر��ʽ�������ַ�����������ʽδ�����򷵻� nil��
foo = 42
puts defined? foo    # => "local-variable"
puts defined? $_     # => "global-variable"
puts defined? bar    # => nil��δ���壩

puts defined? puts        # => "method"
puts defined? puts(bar)   # => nil�������� bar δ���壩
puts defined? unpack      # => nil��������δ���壩



# ��������ǰ�������ģ�����ƺ� . ���������ģ���еķ�����
# ���ģ�����ƺ�����ð�� :: ���������ģ���еĳ���

MR_COUNT = 0        # �������� Object ���ϵĳ���
module Foo
  MR_COUNT = 0
  ::MR_COUNT = 1    # ����ȫ�ּ���Ϊ 1
  MR_COUNT = 2      # ���þֲ�����Ϊ 2
end
puts MR_COUNT       # ����ȫ�ֳ���
puts Foo::MR_COUNT  # ���� "Foo" �ľֲ�����

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



puts  "\n==================== �����ж� ===================="

x=1
if x > 2
   puts "x ���� 2"
elsif x <= 2 and x!=0
   puts "x �� 1"
else
   puts "�޷���֪ x ��ֵ"
end

$debug=1
print "debug\n" if $debug

x=1
unless x>2
   puts "x С�� 2"
 else
  puts "x ���� 2"
end

$var =  1
print "1 -- ��һ�����\n" if $var
print "2 -- ��һ�в����\n" unless $var
 
$var = false
print "3 -- ��һ�����\n" unless $var


$age =  5
case $age
when 0 .. 2
    puts "Ӥ��"
when 3 .. 6
    puts "С��"
when 7 .. 12
    puts "child"
when 13 .. 18
    puts "����"
else
    puts "��������ε�"
end

# ��case��"���ʽ"���ֱ�ʡ��ʱ���������һ��when��������Ϊ��ı��ʽ��
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
   puts "�ֲ�������ֵΪ #{i}"
end

# next    ��continue��
for i in 0..5
   if i < 2 then
      next
   end
   puts "�ֲ�������ֵΪ #{i}"
end

puts  "\n==================== ���� ===================="

# Ĭ�ϲ���
def test(a1, a2="Perl")
   puts "�������Ϊ #{a1}"
   puts "�������Ϊ #{a2}"
end
test "C", "C++"
test "ruby"      # �ڶ�������Ĭ�� ,     �������ʿ��Դ����� test("ruby") 


# �޷���ֵ
def test
   i = 100
   j = 10
   k = 0   # û�з�����䣬Ĭ�����һ�����Ľ��
end     
puts test   

# ����ֵ
def test
   i = 100
   j = 200
   k = 300
return i, j, k
end
var = test
print var   # ��ӡ��������
puts " ",var   # ˳���ӡ����Ԫ��

# �ɱ�
def sample (*test)
   print "��������Ϊ #{test.length} : "
   for i in 0...test.length
      print " #{test[i]}, "
   end
   puts;
end
sample "Zara", "6", "F"
sample "Mac", "36", "M", "MCA"


################ ģ�� 
$LOAD_PATH << '.'
require "support" # �����ļ� support.rb

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

puts  "\n==================== �ַ��� ===================="

name1 = "Joe"
name2 = "Mary"
puts "��� #{name1},  #{name2} ����?"

x, y, z = 12, 36, 72
puts "x ��ֵΪ #{ x }"
puts "x + y ��ֵΪ #{ x + y }"
puts "x + y + z ��ƽ��ֵΪ #{ (x + y + z)/3 }"

desc1 = %Q{Ruby ���ַ�������ʹ�� '' �� ""��}
desc2 = %q|Ruby ���ַ�������ʹ�� '' �� ""��|
puts desc1
puts desc2

###

#�ַ�����
# Ruby ��Ĭ���ַ����� ASCII���ַ����õ����ֽڱ�ʾ�������ʹ�� UTF-8 �������ִ����ַ������ַ���������һ�����ĸ��ֽڱ�ʾ��
# �������ڳ���ͷʹ�� $KCODE �ı��ַ�����������ʾ��
# $KCODE = 'u'

#myStr = String.new("THIS IS TEST")
myStr = "THIS IS TEST"
foo = myStr.downcase
puts "#{foo}"

len = myStr.length
print myStr[0, len],"\n"

puts  "\n==================== ���� ===================="

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

puts  "\n==================== Time ����� ===================="

time = Time.new
# Time ����� [sec,min,hour,day,month,year,wday,yday,isdst,zone]
puts "��ǰʱ�� : " + time.inspect
puts time.year    # => ���ڵ����
puts time.month   # => ���ڵ��·ݣ�1 �� 12��
puts time.day     # => һ�����еĵڼ��죨1 �� 31��
puts time.wday    # => һ���е����ڼ���0 �������գ�
puts time.yday    # => 365��һ���еĵڼ���
puts time.hour    # => 23��24 Сʱ��
puts time.min     # => 59
puts time.sec     # => 59
puts time.usec    # => 999999��΢��
puts time.zone    # => "UTC"��ʱ������

puts time.to_s
puts time.ctime
puts time.localtime
puts time.strftime("%Y-%m-%d %H:%M:%S")

# July 8, 2008
Time.local(2008, 7, 8)  
# July 8, 2008, 09:10am������ʱ��
Time.local(2008, 7, 8, 9, 10)   
# July 8, 2008, 09:10 UTC
Time.utc(2008, 7, 8, 9, 10)  
# July 8, 2008, 09:10:11 GMT ���� UTC ��ͬ��
Time.gm(2008, 7, 8, 9, 10, 11)


values = time.to_a
puts Time.utc(*values)


puts  "\n==================== �ļ���Ŀ¼���� ===================="

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
puts File.readable?( "file.txt" )   # => �Ƿ�ɶ�
puts File.writable?( "file.txt" )   # => �Ƿ��д
puts File.executable?( "file.txt" ) # => �Ƿ�ɶ���д��ִ��
puts File.zero?( "file.txt" )       # => �ļ���СΪ0
puts File.size?( "file.txt" )						# �ļ���С
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