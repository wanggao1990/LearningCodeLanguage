package myPkgs

import (
	"encoding/json"
	"fmt"
	"io"
	"log"
	"os"
	"reflect"
	"strings"
)

func testDecoder(){

	const jsonStream = ` 
        { "Name" : "Ed" , "Text" : "Knock knock." } 
        { "Name" : "Sam" , "Text" : "Who's there?" } 
        { "Name" : "Ed" , "Text" : "Go fmt." } 
        { "Name" : "Sam" , "Text" : "Go fmt who?" } 
        { "Name" : "Ed" , "Text" : "Go fmt yourself!" } 
    `
	type Message struct {
		Name , Text string
	}
	dec := json.NewDecoder ( strings.NewReader ( jsonStream ) )
	for {
		var m Message
		if err := dec.Decode( &m ) ; err == io.EOF {
			break
		} else if err != nil {
			log.Fatal ( err )
		}
		fmt.Printf ( "%s: %s \n" , m. Name , m. Text )
	}

	fmt.Println("\n")
}

func testMarshall(){
	type ColorGroup struct {
		ID     int
		Name   string
		Colors [] string
	}
	group := ColorGroup {
		ID :     1 ,
		Name :   "Reds" ,
		Colors : [] string { "Crimson" , "Red" , "Ruby" , "Maroon" } ,
	}
	b , err := json.Marshal ( group )
	if err != nil {
		fmt.Println("error:", err )
	}
	os.Stdout.Write(b)

	fmt.Println("\n")
}

func testUnMarshal(){
	var jsonBlob = [] byte ( ` [ 
        { "Name" : "Platypus" , "Order" : "Monotremata" } , 
        { "Name" : "Quoll" ,     "Order" : "Dasyuromorphia" } 
    ] ` )
	type Animal struct {
		Name  string
		Order string
	}
	var animals [] Animal
	err := json.Unmarshal( jsonBlob , &animals )   //  json转struct
	if err != nil {
		fmt.Println ( "error:" , err )
	}
	fmt.Printf ( "%+v" , animals )

	fmt.Println("\n")
}


func TestJson(){
	testDecoder()
	testMarshall()
	testUnMarshal()
}


func TestJsonReflext(){
	type User struct {
	    Name   string "user name" //这引号里面的就是tag
	    Passwd string "user passsword"
	}
	user := &User{"chronos", "pass"}
	s := reflect.TypeOf(user).Elem() //通过反射获取type定义
	for i := 0; i < s.NumField(); i++ {
	 	fmt.Println(s.Field(i).Tag) //将tag输出出来
	}
	fmt.Println("")

	type S struct {
		F string `species:"gopher" color:"blue"`
	}
	s2 := S{}
	st := reflect.TypeOf(s2)
	field := st.Field(0)
	fmt.Println(field.Tag.Get("color"), field.Tag.Get("species"))
}


