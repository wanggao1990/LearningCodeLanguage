package myPkgs

import (
	"net/http"
	"fmt"
	"strings"
	"log"
	"html/template"
	"regexp"
	"time"
	"crypto/md5"
	"io"
	"strconv"
	"os"
	"io/ioutil"
	"bytes"
	"mime/multipart"
)

func sayhelloName_4_1(w http.ResponseWriter, r *http.Request) {
	r.ParseForm()       //解析url传递的参数，对于POST则解析响应包的主体（request body）
	//注意:如果没有调用ParseForm方法，下面无法获取表单的数据
	fmt.Println(r.Form) //这些信息是输出到服务器端的打印信息
	fmt.Println("path", r.URL.Path)
	fmt.Println("scheme", r.URL.Scheme)
	fmt.Println(r.Form["url_long"])
	for k, v := range r.Form {
		fmt.Println("key:", k)
		fmt.Println("val:", strings.Join(v, ""))
	}
	fmt.Fprintf(w, "Hello astaxie!\n") //这个写入到w的是输出到客户端的
}

func login_4_1(w http.ResponseWriter, r *http.Request) {
	fmt.Println("method:", r.Method) //获取请求的方法
	if r.Method == "GET" {
		t, _ := template.ParseFiles("./myPkgs/html/login.gtpl")
		log.Println(t.Execute(w, nil))
	} else {
		r.ParseForm()   // 解析表单，默认是不解析的。所以必须加

		//请求的是登录数据，那么执行登录的逻辑判断

		//fmt.Println("username:", r.Form["username"])   // 或 r.FormValue("username")，会进行解析
		//fmt.Println("password:", r.Form["password"])
		//fmt.Println(r)

		fmt.Println(r.RemoteAddr)
		fmt.Println(r.Host)
		fmt.Println(r.Proto)
		fmt.Println(r.RequestURI)
		fmt.Println(r.Cookies())
		fmt.Println(r.Header)

		for k,v := range r.Form{
			fmt.Printf("[%s] = %s\n", k,v[0])
		}

		fmt.Fprintf(w, "登录信息为 username = %s, password = %s",r.Form["username"], r.Form["password"] )
	}

	fmt.Println("")
}


func login_4_2(w http.ResponseWriter, r *http.Request) {
	fmt.Println("method:", r.Method) //获取请求的方法
	if r.Method == "GET" {
		t, _ := template.ParseFiles("./myPkgs/html/login.gtpl")
		log.Println(t.Execute(w, nil))
	} else {
		r.ParseForm() // 解析表单，默认是不解析的。所以必须加

		// 必填字段
		if len(r.Form["username"][0])==0{
			fmt.Fprint(w,"<html>alert('username is empty')</html>")
		}

		if m, _ := regexp.MatchString("^\\p{Han}+$", r.Form.Get("realname")); !m {
			fmt.Fprint(w,"不为中文")
		}

		if m, _ := regexp.MatchString("^[a-zA-Z]+$", r.Form.Get("engname")); !m {
			fmt.Fprint(w,"不为英文")
		}

		if m, _ := regexp.MatchString(`^([\w\.\_]{2,10})@(\w{1,}).([a-z]{2,4})$`, r.Form.Get("email")); !m {
			fmt.Println("邮箱错误")
		}

		if m, _ := regexp.MatchString(`^(1[3|4|5|8][0-9]\d{4,8})$`, r.Form.Get("mobile")); !m {
			fmt.Println("手机号错误")
		}


		//验证15位身份证，15位的是全部数字
		if m, _ := regexp.MatchString(`^(\d{15})$`, r.Form.Get("usercard")); !m {
			fmt.Println("身份证号错误")
		}

		//验证18位身份证，18位前17位为数字，最后一位是校验位，可能为数字或字符X。
		if m, _ := regexp.MatchString(`^(\d{17})([0-9]|X)$`, r.Form.Get("usercard")); !m {
			fmt.Println("身份证号错误")
		}
	}
}

/* 避免动态网站XSS */
// 对XSS最佳的防护应该结合以下两种方法：
// 一是验证所有输入数据，有效检测攻击(这个我们前面小节已经有过介绍);
// 另一个是对所有输出数据进行适当的处理，以防止任何已成功注入的脚本在浏览器端运行。

// 	func HTMLEscape(w io.Writer, b []byte) //把b进行转义之后写到w
// 	func HTMLEscapeString(s string) string //转义s之后返回结果字符串
// 	func HTMLEscaper(args ...interface{}) string //支持多个参数一起转义，返回结果字符串
func login_4_3(w http.ResponseWriter, r *http.Request) {
	fmt.Println("method:", r.Method) //获取请求的方法
	if r.Method == "GET" {
		t, _ := template.ParseFiles("./myPkgs/html/login.gtpl")
		log.Println(t.Execute(w, nil))
	} else {
		r.ParseForm()   // 解析表单，默认是不解析的。所以必须加
		////请求的是登录数据，那么执行登录的逻辑判断
		//fmt.Println("username:", r.Form["username"])   // 或 r.FormValue("username")，会进行解析
		//fmt.Println("password:", r.Form["password"])
		//fmt.Println(r)

		/* 输出*/
		fmt.Println("username:", template.HTMLEscapeString(r.Form.Get("username"))) //输出到服务器端
		fmt.Println("password:", template.HTMLEscapeString(r.Form.Get("password")))

		template.HTMLEscape(w, []byte(r.Form.Get("username"))) //输出到客户端
	}

	fmt.Println("")
}

/*避免重复提交表单*/
// 在模版里面增加了一个隐藏字段token，这个值我们通过MD5(时间戳)来获取唯一值，然后我们把这个值存储到
// 服务器端(session来控制，我们将在第六章讲解如何保存)，以方便表单提交时比对判定。
func login_4_4(w http.ResponseWriter, r *http.Request) {
	fmt.Println("method:", r.Method) //获取请求的方法
	if r.Method == "GET" {
		currTime := time.Now().Unix()
		h := md5.New()
		io.WriteString(h, strconv.FormatInt(currTime,10))
		token := fmt.Sprintf("%x", h.Sum(nil))
		fmt.Println(token)

		t, _ := template.ParseFiles("./myPkgs/html/login.gtpl")
		t.Execute(w, token)

	} else {
		r.ParseForm()
		token := r.Form.Get("token")
		if token != "" {
			fmt.Println("验证token的合法性")
		} else {
			fmt.Println("不存在token报错")
		}
		fmt.Println("username length:", len(r.Form["username"][0]))
		fmt.Println("username:", template.HTMLEscapeString(r.Form.Get("username"))) //输出到服务器端
		fmt.Println("password:", template.HTMLEscapeString(r.Form.Get("password")))
		template.HTMLEscape(w, []byte(r.Form.Get("username"))) //输出到客户端
	}

	fmt.Println("")
}


/*  文件上传 */
func test_4_5(w http.ResponseWriter, r *http.Request){
	fmt.Println("method:", r.Method) //获取请求的方法
	if r.Method == "GET" {
		crutime := time.Now().Unix()
		h := md5.New()
		io.WriteString(h, strconv.FormatInt(crutime, 10))
		token := fmt.Sprintf("%x", h.Sum(nil))

		t, _ := template.ParseFiles("./myPkgs/html/upload.gtpl")
		t.Execute(w, token)
	} else {

		fmt.Println(r)
		fmt.Println("content length: ", r.ContentLength)

		r.ParseMultipartForm(r.ContentLength /*32 << 20*/)
		file, handler, err := r.FormFile("uploadfile")

		fmt.Println("file length: ", handler.Size)

		defer file.Close()

		if err != nil {
			fmt.Println(err)
			return
		}

		fmt.Fprintf(w, "%v", handler.Header)
		f, err := os.OpenFile("./myPkgs/test/"+handler.Filename, os.O_WRONLY|os.O_CREATE, 0666)  // 此处假设当前目录下已存在test目录
		defer f.Close()

		if err != nil {
			fmt.Println(err)
			return
		}

		io.Copy(f, file)
	}
}


// 模拟客户端上传文件
func PostFile(filename string, targetUrl string) error {
	bodyBuf := &bytes.Buffer{}
	bodyWriter := multipart.NewWriter(bodyBuf)

	//关键的一步操作
	fileWriter, err := bodyWriter.CreateFormFile("uploadfile", filename)
	if err != nil {
		fmt.Println("error writing to buffer")
		return err
	}

	//打开文件句柄操作
	fh, err := os.Open(filename)
	if err != nil {
		fmt.Println("error opening file")
		return err
	}
	defer fh.Close()

	//iocopy
	_, err = io.Copy(fileWriter, fh)
	if err != nil {
		return err
	}

	contentType := bodyWriter.FormDataContentType()
	bodyWriter.Close()

	resp, err := http.Post(targetUrl, contentType, bodyBuf)
	if err != nil {
		return err
	}
	defer resp.Body.Close()
	resp_body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		return err
	}
	fmt.Println(resp.Status)
	fmt.Println(string(resp_body))
	return nil
}


func Test_4(){

	http.HandleFunc("/", sayhelloName_4_1)       //设置访问的路由
	http.HandleFunc("/login1", login_4_1)         //设置访问的路由
	http.HandleFunc("/login2", login_4_2)         //设置访问的路由
	http.HandleFunc("/login3", login_4_3)         //设置访问的路由
	http.HandleFunc("/login", login_4_4)         //设置访问的路由
	http.HandleFunc("/upload", test_4_5)
	err := http.ListenAndServe(":3000", nil) //设置监听的端口
	if err != nil {
		log.Fatal("ListenAndServe: ", err)
	}

}
