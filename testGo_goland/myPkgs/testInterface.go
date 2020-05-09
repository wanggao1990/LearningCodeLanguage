package myPkgs

import (
	"fmt"
	"strconv"
	"reflect"
)

type Human struct {
	name string
	age int
	phone string
}
type Student struct {
	Human //匿名字段Human
	school string
	loan float32
}
type Employee struct {
	Human //匿名字段Human
	company string
	money float32
}

//Human实现SayHi方法
func (h Human) SayHi() {
	fmt.Printf("Hi, I am %s you can call me on %s\n", h.name, h.phone)
}

//Human实现Sing方法
func (h Human) Sing(lyrics string) {
	fmt.Println("La la la la...", lyrics)
}

//Employee重载Human的SayHi方法
func (e Employee) SayHi() {
	fmt.Printf("Hi, I am %s, I work at %s. Call me on %s\n", e.name,
		e.company, e.phone)
}

// Interface Men被Human,Student和Employee实现
// 因为这三个类型都实现了这两个方法
type Men interface {
	SayHi()
	Sing(lyrics string)
}

////
type MyStu struct {   // 接口实际类似于实现方法的集合
	Men
	country string
}
func (s *MyStu) SayHi() {
	fmt.Println("Mysru saying hi, come from ", s.country)
}
//Human实现Sing方法
func (s *MyStu) Sing(song string) {
	fmt.Printf("La la la la... %s \n", song)
}

////
// interface的变量可以持有任意实现该interface类型的对象，这给我们编写函数(包括method)提供了一些额外的思考，
// 我们是不是可以通过定义interface参数，让函数接受各种类型的参数。
// 通过这个方法 Human 实现了 fmt.Stringer

// 否则会输出类似于  {Bob 39 000-7777-XXX}
func (h Human) String() string {
	return "《"+h.name+" - "+strconv.Itoa(h.age)+" years -  ✆ " +h.phone+"》"
}


////////////////////////////////////////////////////////

type Element interface{}
type List [] Element
type Person struct {
	name string
	age int
}
//定义了String方法，实现了fmt.Stringer
func (p Person) String() string {
	return "(name: " + p.name + " - age: "+strconv.Itoa(p.age)+ " years)"
}

///////////////////////////////////////////////////////////////////////////////////////////////////
/**
		反射， reflection,    能检查程序在运行时的状态

		t := reflect.TypeOf(list)    //得到类型的元数据,通过t我们能获取类型定义里面的所有元素
		v := reflect.ValueOf(list)   //得到实际的值，通过v我们获取存储在里面的值，还可以去改变值

		tag := t.Elem().Field(0).Tag  //获取定义在struct里面的标签
		name := v.Elem().Field(0).String()  //获取存储在第一个字段里面的值
 */

func TestInterface(){

	////////////

	list := make(List, 3)
	list[0] = 1 // an int
	list[1] = "Hello" // a string
	list[2] = Person{"Dennis", 70}

	for index, element := range list {

		fmt.Println(index, element)

		//// Comma-ok断言  value, ok = element.(T)，
		//// 这里value就是变量的值，ok是一个bool类型，element是interface变量，T是断言的类型。
		///  如果element里面确实存储了T类型的数值，那么ok返回true，否则返回false。
		if value, ok := element.(int); ok {
			fmt.Printf("list[%d] is an int and its value is %d\n", index, value)
		} else if value, ok := element.(string); ok {
			fmt.Printf("list[%d] is a string and its value is %s\n", index, value)
		} else if value, ok := element.(Person); ok {
			fmt.Printf("list[%d] is a Person and its value is %s\n", index, value)
		} else {
			fmt.Printf("list[%d] is of a different type\n", index)
		}

		////   `element.(type)`语法不能在switch外的任何逻辑里面使用
		switch value := element.(type) {
			case int:		fmt.Printf("list[%d] is an int and its value is %d\n", index, value)
			case string:	fmt.Printf("list[%d] is a string and its value is %s\n", index, value)
			case Person:	fmt.Printf("list[%d] is a Person and its value is %s\n", index, value)
			default:		fmt.Println("list[%d] is of a different type", index)
		}
	}
	fmt.Println("")

	// 反射
	var xx float64 = 3.4
	v := reflect.ValueOf(xx)
	fmt.Println("type:", v.Type())
	fmt.Println("kind is float64:", v.Kind() == reflect.Float64)
	fmt.Println("value:", v.Float())

	p := reflect.ValueOf(&xx)   // 反射修改，必须用引用，否则报错
	v = p.Elem()
	v.SetFloat(7.1)
	fmt.Println("value:", v.Float(), ", x: ", xx)

	return

	/////////////////////////////////////////////////////////

	Bob := Human{"Bob", 39, "000-7777-XXX"}
	fmt.Println("This Human is : ", Bob)

	//////

	// 定义a为空接口
	var em interface{} = nil
	var num int = 5
	s := "Hello world"
	// a可以存储任意类型的数值
	em = num; fmt.Println(em)
	em = s; fmt.Println(em)


	return
	/////


	mike := Student{Human{"Mike", 25, "222-222-XXX"}, "MIT", 0.00}
	paul := Student{Human{"Paul", 26, "111-222-XXX"}, "Harvard", 100}
	sam := Employee{Human{"Sam", 36, "444-222-XXX"}, "Golang Inc.", 1000}
	tom := Employee{Human{"Tom", 37, "222-444-XXX"}, "Things Ltd.", 5000}

	//定义Men类型的变量i
	var i Men

	//i能存储Student
	i = mike
	fmt.Println("This is Mike, a Student:")
	i.SayHi()
	i.Sing("November rain\n")

	//i也能存储Employee
	i = tom
	fmt.Println("This is tom, an Employee:")
	i.SayHi()
	i.Sing("Born to be wild\n")

	//定义了slice Men
	fmt.Println("Let's use a slice of Men and see what happens")
	x := make([]Men, 3)
	//这三个都是不同类型的元素，但是他们实现了interface同一个接口
	x[0], x[1], x[2] = paul, sam, mike

	for _, value := range x{
		value.SayHi()
	}

	fmt.Println("")

	myStu := MyStu{country:"china" }
	myStu.SayHi()
	myStu.Sing("hello")
}


////////////////////////////////////////////////////

type Stringer interface {
	String() string
}

type Mystruct interface {

}
type Mystruct2 struct {

}
func (this *Mystruct2) String() string {
	return ""
}

func TestInterface2()  {
	var v Mystruct
	var v2 Mystruct2
	v = &v2

	if sv, ok := v.(Stringer); ok {
		fmt.Printf("%v implements String(): %v\n", sv.String(),ok)
	}
}