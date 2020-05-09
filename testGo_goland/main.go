
package main

import (
	"fmt"
	"os"
	"./database"
	//"MyUtil"
	"math"
	"strconv"
	"./myPkgs"
)

func max1(a, b int) (c int) {
	if a > b {
		return a
	}
	return b
}

func max2(a, b int) (c int) {
	if a > b {
		c = a
	}
	c = b
	return
}

//返回 A+B 和 A*B
func SumAndProduct1(A, B int) (int, int) {
	return A+B, A*B
}

// 官方建议
func SumAndProduct2(A, B int) (add int, Multiplied int) {
	add = A+B
	Multiplied = A*B
	return
}

func myfunc(arg ...int) {
	for _, n := range arg {
		fmt.Printf("And the number is: %d\n", n)
	}

	for i := 0; i < 5; i++ {
		defer fmt.Printf("%d \n", i)
	}
}

//////  函数作为变量
type testInt func(int) bool // 声明了一个函数类型

func isOdd(integer int) bool {
	if integer%2 == 0 {
		return false
	}
	return true
}
func isEven(integer int) bool {
	if integer%2 == 0 {
		return true
	}
	return false
}
// 声明的函数类型在这个地方当做了一个参数
func filter(slice []int, f testInt) []int {
	var result []int
	for _, value := range slice {
		if f(value) {
			result = append(result, value)
		}
	}
	return result
}

//////

var user = os.Getenv("GOPATH")

func init() {
	if user == "" {
		panic("no value for $USER")
	}else {
		fmt.Println("value for $USER = ", user, "\n")
	}



}

func throwsPanic(f func()) (b bool) {
	defer func() {
		if x := recover(); x != nil {
			b = true
		}
	}()

	f() //执行函数f，如果f中出现了panic，那么就可以恢复回来
	return
}

func f(){
	panic("nothing,,,,")
}


//////////////////

type person struct {
	name string
	age int
}


type Human struct {
	name string
	age int
	weight int
}

// 类似于继承， Student 继承了Human的所有字段, Student对象还能访问Human的所有字段
type Student1 struct {
	Human  					// 匿名字段，那么默认Student就包含了Human的所有字段
	speciality string
}

type Skills []string

type Student2 struct {
	Human  					// 匿名字段，那么默认Student就包含了Human的所有字段
	Skills					// 匿名字段，自定义的类型string slice
	int    					// 内置类型作为匿名字段
	speciality string
}


type Employe struct {
	name 	string
	age 	int
	phone 	string
}

type Employee struct {
	Employe
	speciality 	string
	phone 		string  // 雇员的phone字段
}

//////////////////////////////////////////////////////////////////////////////////////////
/* 面向对象 */
type Rectangle struct {
	width, height float64
}

//将Rectangle的对象（如r1,r2）作为参数传入函数计算面积
func area(r Rectangle) float64 {
	return r.width*r.height
}

///////////////////////

type Circle struct {
	radius float64
	center [2]int64
}

func (r Rectangle) area() float64 {
	return r.width*r.height
}

// method是附属在一个给定的类型上的，
// 他的语法和函数的声明语法几乎一样，只是在func后面增加了一个receiver(也就是method所依从的主体)。
func (c Circle) area() float64 {        // 值传递
	c.center = [2]int64{5,5}
	return c.radius * c.radius * math.Pi
}

func (c *Circle) mulpate()  {        // 值传递
	c.center = [2]int64{0,0}
}

///////////////////////
const(
	WHITE = iota
	BLACK
	BLUE
	RED
	YELLOW
)

type Color byte   // Color作为byte的别名

// 定义一个别名
type Box struct {
	width, height, depth float64
	color Color
}

type BoxList []Box //a slice of boxes     // slice是引用

// Volume()定义了接收者为Box，返回Box的容量
func (b Box) Volume() float64 {
	return b.width * b.height * b.depth
}

//  setColor(c Color)，把Box的颜色改为c   // 注意这里是 引用
func (b Box) SetColor(c Color) {
	b.color = c
}

func (bl BoxList) BiggestColor() Color {
	v := 0.00
	k := Color(WHITE)
	for _, b := range bl {
		if bv := b.Volume(); bv > v {
			v = bv
			k = b.color
		}
	}
	return k
}

func (bl BoxList) PaintItBlack() {      //clice是引用
	for i := range bl {
		bl[i].SetColor(BLACK)
	}
}

func (c Color) String() string {
	strings := []string {"WHITE", "BLACK", "BLUE", "RED", "YELLOW"}
	return strings[c]
}


////  method 继承

type Human22 struct {
	name string
	age int
	phone string
}
type Student22 struct {
	Human22 //匿名字段
	school string
}
type Employee22 struct {
	Human22 //匿名字段
	company string
}
//在human上面定义了一个method
func (h *Human22) SayHi() {
	fmt.Printf("Hi, I am %s you can call me on %s\n", h.name, h.phone)

}

//Employee的method重写Human的method
func (e *Employee22) SayHi() {
	fmt.Printf("Hi, I am %s, I work at %s. Call me on %s\n", e.name,
		e.company, e.phone) //Yes you can split into 2 lines here.
}


/////////////////////////////////////////////////////

func testMap() {
	m := make(map[string]int)
	for i := 0; i<5; i+=1 {
		m[strconv.Itoa(i)] = i  +10
	}

	for i := -3; i<8; i+=1 {
		if k, ok := m[strconv.Itoa(i)]; ok {
			fmt.Println("找到 key = ", strconv.Itoa(i), ", value = " ,k)
		} else {
			fmt.Println("未找到 key = ", strconv.Itoa(i),)
		}
	}
}

func main(){


	myPkgs.Test_3_2()

	//myPkgs.TestMysql()
	//myPkgs.Test_4();
	//database.TestMysql()
	return
	/////////////////

	//myPkgs.TestCrypto()
	//myPkgs.TestSHA_MD5()
	//myPkgs.Test_MD5_SALT()
	//myPkgs.TestBased64()
	return
	/////


	//myPkgs.TestJsonRpc()
	//myPkgs.TestRPC_TCP()
	//myPkgs.TestRPC_HTTP()
	//myPkgs.TestREST()
	//myPkgs.TestWebSocket()
	//myPkgs.TestUDP()
	//myPkgs.TestTCP()
	//myPkgs.TestParseIP()
	return
	/////////////////

	//myPkgs.TestString()
	//myPkgs.TestFileExec()
	//myPkgs.TestFileDir()
	//myPkgs.TestTemplate3()
	//myPkgs.TestTemplate2()
	//myPkgs.TestTemplate1()
	//myPkgs.TestRegexpCompile()
	//myPkgs.TestRegexp()
	//myPkgs.TestGenJson2()
	//myPkgs.TestGenJson1()
	//myPkgs.TestParserJsonTOInterface()
	//myPkgs.TestParserJson()
	//myPkgs.TestGenXML()
	//myPkgs.TestParserXML()
	return
	////////////

	myPkgs.TestMutex()
	//myPkgs.TestCK()
	return
	/////////

	myPkgs.TestJson()
	myPkgs.TestJsonReflext()
	return

	database.TestMysql()
	myPkgs.Test_4()
	myPkgs.Test_3_2()
	myPkgs.TestGoroutine()
	myPkgs.TestInterface()
	myPkgs.TestInterface2()

	////

	testMap()
	myPkgs.TestDateANdTime()

	return

	////////

	mark := Student22{Human22{"Mark", 25, "222-222-YYYY"}, "MIT"}
	sam := Employee22{Human22{"Sam", 45, "111-888-XXXX"}, "Golang Inc"}

	mark.SayHi()
	sam.SayHi()
	sam.Human22.SayHi()

	return

	////////

	boxes := BoxList {
		Box{4, 4, 4, RED},
		Box{10, 10, 1, YELLOW},
		Box{1, 1, 20, BLACK},
		Box{10, 10, 1, BLUE},
		Box{10, 30, 1, WHITE},
		Box{20, 20, 20, YELLOW},
	}

	fmt.Printf("We have %d boxes in our set\n", len(boxes))
	fmt.Println("The volume of the first one is", boxes[0].Volume(), "cm³")
	fmt.Println("The color of the last one is",boxes[len(boxes)-1].color.String())
	fmt.Println("The biggest one is", boxes.BiggestColor().String())

	fmt.Println("Let's paint them all black")
	boxes.PaintItBlack()
	fmt.Println("The color of the second one is", boxes[1].color.String())

	fmt.Println("Obviously, now, the biggest one is", boxes.BiggestColor().String())

	return

	////////

	r1 := Rectangle{12, 2}
	r2 := Rectangle{9, 4}
	c1 := Circle{10,[2]int64{0,0}}
	c2 := Circle{25,[2]int64{10,10}}

	fmt.Println("Area of r1 is: ", r1.area())
	fmt.Println("Area of r2 is: ", r2.area())
	fmt.Println("Area of c1 is: ", c1.area())
	fmt.Println("Area of c2 is: ", c2.area(),c2.center)
	c2.mulpate()
	fmt.Println("Area of c2 is: ", c2.area(),c2.center)

	return

	r11 := Rectangle{12, 2}
	r22 := Rectangle{9, 4}
	fmt.Println("Area of r1 is: ", area(r11))
	fmt.Println("Area of r2 is: ", area(r22))

	return

	Bob := Employee{Employe{"Bob", 34, "777-444-XXXX"}, "Designer", "333-222"}
	fmt.Println(Bob.phone)				// 默认是自己的成员变量phone，相当于重载了父类
	fmt.Println(Bob.Employe.phone)		// 也可以直接通过Employe访问父类的phone
	return

	allen := Student2{Human:Human{"Mark", 25, 120}, speciality:"Computer Science"}
	allen.Skills = []string{"anatomy"}
	allen.int = 3
	fmt.Println(allen)
	return

	//mark := Student2{Human:Human{"Mark", 25, 120}, "Computer Science"}
	//mark.Human.age -= 1

	//fmt.Println(mark)

	var p1  = person {"wg",12}
	var p2  = person {  age:15, name:"waf",}
	var p3  = new(person);p3.age=12;p3.name="xxx"
	fmt.Println(p1,p2,p3)

	return

	throwsPanic(f)

	///////
	slice := []int {1, 2, 3, 4, 5, 7}
	fmt.Println("slice = ", slice)
	odd := filter(slice, isOdd)    // 函数当做值来传递了
	fmt.Println("Odd elements of slice are: ", odd)
	even := filter(slice, isEven)  // 函数当做值来传递了
	fmt.Println("Even elements of slice are: ", even)

 	/////

	fmt.Println(max2(10,12))

	fmt.Println(SumAndProduct2(2,4))

	myfunc(1,2,3,4,5,6,7,8)


	fmt.Println("Hello, world or 你好，世界 or καλημ ́ρα κóσμ or こんにちはせかい\n")
	//fmt.Println(MyUtil.Add(10,20))

	var arr1  = [5]int {1,2,3,4,5}
	var slic1 = []int{1,2,3,4,5}
	var slic2 = arr1[1:3]

	fmt.Println(arr1,slic1, slic2)

	arr1[0] = 10
	fmt.Println(arr1,slic1, slic2)

	if x := 8; x > 10 {
		fmt.Println(x, " is greater than 10")
	} else {
		fmt.Println(x, " is less than 10")
	}
}