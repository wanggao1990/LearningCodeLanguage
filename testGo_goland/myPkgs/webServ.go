package myPkgs

import (
	"io/ioutil"
	"net/http"
	"fmt"
	"strings"
	"log"
)

type MyMux struct {
}

func (p *MyMux) ServeHTTP(w http.ResponseWriter, r *http.Request) {
	if r.URL.Path == "/" {
		sayhelloName(w, r)
		return
	}
	http.NotFound(w, r)
	return
}

func sayhelloName(w http.ResponseWriter, r *http.Request) {

	r.ParseForm()  //解析参数，默认是不会解析的
	fmt.Println(r.Form)  //这些信息是输出到服务器端的打印信息
	fmt.Println("path", r.URL.Path)
	fmt.Println("scheme", r.URL.Scheme)
	fmt.Println(r.Form["url_long"])
	for k, v := range r.Form {
		fmt.Println("key:", k, ", val:", strings.Join(v, ""))
	}
	fmt.Fprintf(w, "Hello astaxie!都是") //这个写入到w的是输出到客户端的

	fmt.Println("")
}

type myHandle struct {

}

func (this *myHandle)ServeHTTP(w http.ResponseWriter, r *http.Request) {
	fmt.Println("request: \n\t", w)

}


func testPost(w http.ResponseWriter, r *http.Request) {

	if r.Method == "GET" {
		fmt.Fprintf(w, "use POST method.")
	}else if r.Method == "POST"{
		result, _:= ioutil.ReadAll(r.Body)
		r.Body.Close()
		fmt.Printf("%s\n", result)
	}
}

func Test_3_2() {


	//mux := &MyMux{}
	//http.ListenAndServe(":3000", mux)
	//return

	//http.HandleFunc("/", testPost) //设置访问的路由

	http.HandleFunc("/", sayhelloName) //设置访问的路由
	err := http.ListenAndServe(":3000", nil) //设置监听的端口
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}
}