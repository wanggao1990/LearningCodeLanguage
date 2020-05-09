package myPkgs

import (
	"encoding/json"
	"encoding/xml"
	"fmt"
	"html/template"
	"io/ioutil"
	"net/http"
	"os"
	"regexp"
	"strconv"
	"strings"
)


func TestParserXML() {

	type server struct {
		XMLName    xml.Name `xml:"server"`
		ServerName string   `xml:"serverName"`
		ServerIP   string   `xml:"serverIP"`
	}

	type Recurlyservers struct {
		XMLName     xml.Name `xml:"servers"`
		Version     string   `xml:"version,attr"`
		Svs         []server `xml:"server"`
		Description string   `xml:",innerxml"`
	}

	file, err := os.Open("./myPkgs/test/servers.xml") // For read access.
	if err != nil {
		fmt.Printf("error: %v", err)
		return
	}
	defer file.Close()
	data, err := ioutil.ReadAll(file)
	if err != nil {
		fmt.Printf("error: %v", err)
		return
	}
	v := Recurlyservers{}
	err = xml.Unmarshal(data, &v)
	if err != nil {
		fmt.Printf("error: %v", err)
		return
	}
	fmt.Println(v)
}


func TestGenXML() {


	type server struct {
		ServerName string   `xml:"serverName"`
		ServerIP   string   `xml:"serverIP"`
	}

	type Servers struct {
		XMLName     xml.Name `xml:"servers"`
		Version     string   `xml:"version,attr"`
		Svs         []server `xml:"server"`
	}

	v := &Servers{Version: "1"}
	v.Svs = append(v.Svs, server{"Shanghai_VPN", "127.0.0.1"})
	v.Svs = append(v.Svs, server{"Beijing_VPN", "127.0.0.2"})
	output, err := xml.MarshalIndent(v, "  ", "    ")
	if err != nil {
		fmt.Printf("error: %v\n", err)
	}
	os.Stdout.Write([]byte(xml.Header))  //xml.MarshalIndent或者xml.Marshal输出的信息都是不带XML头
	os.Stdout.Write(output)
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

func TestParserJson(){

	type Server struct {
		ServerName string
		ServerIP   string
	}

	type Serverslice struct {
		Servers []Server
	}

	var s Serverslice
	str := `{
				"servers":[
						{"serverName":"Shanghai_VPN","serverIP":"127.0.0.1"},
						{"serverName":"Beijing_VPN","serverIP":"127.0.0.2"}
					]
			}`
	json.Unmarshal([]byte(str), &s)
	fmt.Println(s)
}

func TestParserJsonTOInterface() {

	b := []byte(`{"Name":"Wednesday","Age":6,"Parents":["Gomez","Morticia"]}`)

	var f interface{}
	err := json.Unmarshal(b, &f)

	if err == nil {
		m := f.(map[string]interface{})
		for k, v := range m {
			switch vv := v.(type) {
			case string:
				fmt.Println(k, "is string", vv)
			case int:
				fmt.Println(k, "is int", vv)
			case float64:
				fmt.Println(k,"is float64",vv)
			case []interface{}:
				fmt.Println(k, "is an array:")
				for i, u := range vv {
					fmt.Println(i, u)
				}
			default:
				fmt.Println(k, "is of a type I don't know how to handle")
			}
		}
	}
}

func TestGenJson1(){

	type Server struct {
		ServerName string
		ServerIP   string
	}

	type Serverslice struct {
		Servers []Server
	}

	////
	//	我们看到上面的输出字段名的首字母都是大写的，如果你想用小写的首字母怎么办呢？
	// 把结构体的字段名改成首字母小写的？JSON输出的时候必须注意，只有导出的字段才会被输出，
	// 如果修改字段名，那么就会发现什么都不会输出，所以必须通过struct tag定义来实现：

	/*	 type Server struct {
	*	 	ServerName string `json:"serverName"`
	*	 	ServerIP   string `json:"serverIP"`
	*	 }
	*	 type Serverslice struct {
	*	 	Servers []Server `json:"servers"`
	*	 }
	*/

	var s Serverslice
	s.Servers = append(s.Servers, Server{ServerName: "Shanghai_VPN", ServerIP: "127.0.0.1"})
	s.Servers = append(s.Servers, Server{ServerName: "Beijing_VPN", ServerIP: "127.0.0.2"})
	b, err := json.Marshal(s)
	if err != nil {
		fmt.Println("json err:", err)
	}
	fmt.Println(string(b))
}



func TestGenJson2(){

	type Server struct {
		// ID 不会导出到JSON中
		ID int `json:"-"`

		// ServerName2 的值会进行二次JSON编码
		ServerName  string `json:"serverName"`
		ServerName2 string `json:"serverName2,string"`

		// 如果 ServerIP 为空，则不输出到JSON串中
		ServerIP   string `json:"serverIP,omitempty"`
	}

	s := Server {
		ID:         3,
		ServerName:  `Go "1.0" `,
		ServerName2: `Go "1.0" `,
		ServerIP:   ``,
	}

	b, _ := json.Marshal(s)
	os.Stdout.Write(b)
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

// 通过正则判断是否匹配
//
// 		regexp包中含有三个函数用来判断是否匹配，如果匹配返回true，否则返回false
//
// 		func Match(pattern string, b []byte) (matched bool, error error)
// 		func MatchReader(pattern string, r io.RuneReader) (matched bool, error error)
// 		func MatchString(pattern string, s string) (matched bool, error error)//

func isIP(ip string) (b bool) {
	if m, _ := regexp.MatchString("^[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}\\.[0-9]{1,3}$", ip); !m {
		return false
	}
	return true
}

func TestRegexp() {

	//str := "0135"
	//
	////if len(str) == 1 {
	////	fmt.Println("Usage: regexp [string]")
	////	os.Exit(1)
	////} else
	//if m, _ := regexp.MatchString("^[0-9]+$", str); m {
	//	fmt.Println("数字")
	//} else {
	//	fmt.Println("不是数字")
	//}


	///////

	resp, err := http.Get("http://www.baidu.com")
	if err != nil {
		fmt.Println("http get error.")
	}
	defer resp.Body.Close()
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		fmt.Println("http read error")
		return
	}

	src := string(body)

	//将HTML标签全转换成小写
	re, _ := regexp.Compile("\\<[\\S\\s]+?\\>")
	src = re.ReplaceAllStringFunc(src, strings.ToLower)

	//去除STYLE
	re, _ = regexp.Compile("\\<style[\\S\\s]+?\\</style\\>")
	src = re.ReplaceAllString(src, "")

	//去除SCRIPT
	re, _ = regexp.Compile("\\<script[\\S\\s]+?\\</script\\>")
	src = re.ReplaceAllString(src, "")

	//去除所有尖括号内的HTML代码，并换成换行符
	re, _ = regexp.Compile("\\<[\\S\\s]+?\\>")
	src = re.ReplaceAllString(src, "\n")

	//去除连续的换行符
	re, _ = regexp.Compile("\\s{2,}")
	src = re.ReplaceAllString(src, "\n")

	fmt.Println(strings.TrimSpace(src))
}

func TestRegexpCompile() {

	/*
		func Compile(expr string) (*Regexp, error)
		func CompilePOSIX(expr string) (*Regexp, error)
		func MustCompile(str string) *Regexp
		func MustCompilePOSIX(str string) *Regexp

		func (re *Regexp) Find(b []byte) []byte
		func (re *Regexp) FindAll(b []byte, n int) [][]byte
		func (re *Regexp) FindAllIndex(b []byte, n int) [][]int
		func (re *Regexp) FindAllSubmatch(b []byte, n int) [][][]byte
		func (re *Regexp) FindAllSubmatchIndex(b []byte, n int) [][]int
		func (re *Regexp) FindIndex(b []byte) (loc []int)
		func (re *Regexp) FindSubmatch(b []byte) [][]byte
		func (re *Regexp) FindSubmatchIndex(b []byte) []int
	 */


	a := "I am learning Go language"

	re, _ := regexp.Compile("[a-z]{2,4}")

	//查找符合正则的第一个
	one := re.Find([]byte(a))
	fmt.Println("Find:", string(one))

	//查找符合正则的所有slice,n小于0表示返回全部符合的字符串，不然就是返回指定的长度
	all := re.FindAll([]byte(a), -1)
	fmt.Println("FindAll", all)

	//查找符合条件的index位置,开始位置和结束位置
	index := re.FindIndex([]byte(a))
	fmt.Println("FindIndex", index)

	//查找符合条件的所有的index位置，n同上
	allindex := re.FindAllIndex([]byte(a), -1)
	fmt.Println("FindAllIndex", allindex)

	re2, _ := regexp.Compile("am(.*)lang(.*)")

	//查找Submatch,返回数组，第一个元素是匹配的全部元素，第二个元素是第一个()里面的，第三个是第二个()里面的
	//下面的输出第一个元素是"am learning Go language"
	//第二个元素是" learning Go "，注意包含空格的输出
	//第三个元素是"uage"
	submatch := re2.FindSubmatch([]byte(a))
	fmt.Println("FindSubmatch", submatch)
	for _, v := range submatch {
		fmt.Println(string(v))
	}

	//定义和上面的FindIndex一样
	submatchindex := re2.FindSubmatchIndex([]byte(a))
	fmt.Println(submatchindex)

	//FindAllSubmatch,查找所有符合条件的子匹配
	submatchall := re2.FindAllSubmatch([]byte(a), -1)
	fmt.Println(submatchall)

	//FindAllSubmatchIndex,查找所有字匹配的index
	submatchallindex := re2.FindAllSubmatchIndex([]byte(a), -1)
	fmt.Println(submatchallindex)
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////


func TestTemplate1(){
	type Person struct {
		UserName string
	}
	t := template.New("fieldname example")
	t, _ = t.Parse("hello {{.UserName}}!")   // 注意有一个点 "."
	p := Person{UserName: "Astaxie"}
	t.Execute(os.Stdout, p)
}

// 循环对象
func TestTemplate2(){
	type Friend struct {
		Fname string
	}

	type Person struct {
		UserName string
		Emails   []string
		Friends  []*Friend
	}

	f1 := Friend{Fname: "minux.ma"}
	f2 := Friend{Fname: "xushiwei"}
	t := template.New("fieldname example")
	t, _ = t.Parse(`hello {{.UserName}}!
						{{range .Emails}}    // 值
							an email {{.}}
						{{end}}			
						{{with .Friends}}   // 指针
						{{range .}}
							my friend name is {{.Fname}}
						{{end}}
						{{end}}
						`)
	p := Person{UserName: "Astaxie",
		Emails:  []string{"astaxie@beego.me", "astaxie@gmail.com"},
		Friends: []*Friend{&f1, &f2}}
	t.Execute(os.Stdout, p)
}

func TestTemplate3() {
	tEmpty := template.New("template test")
	tEmpty = template.Must(tEmpty.Parse("空 pipeline if demo: {{if ``}} 不会输出. {{end}}\n"))
	tEmpty.Execute(os.Stdout, nil)

	tWithValue := template.New("template test")
	tWithValue = template.Must(tWithValue.Parse("不为空的 pipeline if demo: {{if `anything`}} 我有内容，我会输出. {{end}}\n"))
	tWithValue.Execute(os.Stdout, nil)

	tIfElse := template.New("template test")
	tIfElse = template.Must(tIfElse.Parse("if-else demo: {{if `anything`}} if部分 {{else}} else部分.{{end}}\n"))
	tIfElse.Execute(os.Stdout, nil)
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

func TestFileDir(){
	// 创建文件夹，删除文件夹（或文件）

	os.Mkdir("astaxie", 0777)
	os.MkdirAll("astaxie/test1/test2", 0777)
	os.MkdirAll("astaxie/test2/test2", 0777)
	err := os.Remove("astaxie/test1/")
	if err != nil {
		fmt.Println(err)
	}
	os.RemoveAll("astaxie/test1/")
	os.RemoveAll("astaxie")
}

func TestFileExec(){

	// 创建和写入
	func () {
		userFile := "astaxie.txt"
		fout, err := os.Create(userFile)
		if err != nil {
			fmt.Println(userFile, err)
			return
		}
		defer fout.Close()
		for i := 0; i < 10; i++ {
			fout.WriteString("Just a test!\r\n")
			fout.Write([]byte("Just a test!\r\n"))
		}
	}()

	// 打开和读取
	func () {
		userFile := "astaxie.txt"
		fl, err := os.Open(userFile)
		if err != nil {
			fmt.Println(userFile, err)
			return
		}
		defer fl.Close()
		buf := make([]byte, 1024)
		for {
			n, _ := fl.Read(buf)
			if 0 == n {
				break
			}
			os.Stdout.Write(buf[:n])
		}
	}()


	os.Remove("astaxie.txt")
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

//字符串
/*
下面这些函数来自于strings包，这里介绍一些我平常经常用到的函数，更详细的请参考官方的文档。

	func Contains(s, substr string) bool

	字符串s中是否包含substr，返回bool值

	fmt.Println(strings.Contains("seafood", "foo"))
	fmt.Println(strings.Contains("seafood", "bar"))
	fmt.Println(strings.Contains("seafood", ""))
	fmt.Println(strings.Contains("", ""))
	//Output:
	//true
	//false
	//true
	//true
	func Join(a []string, sep string) string

	字符串链接，把slice a通过sep链接起来

	s := []string{"foo", "bar", "baz"}
	fmt.Println(strings.Join(s, ", "))
	//Output:foo, bar, baz
	func Index(s, sep string) int

	在字符串s中查找sep所在的位置，返回位置值，找不到返回-1

	fmt.Println(strings.Index("chicken", "ken"))
	fmt.Println(strings.Index("chicken", "dmr"))
	//Output:4
	//-1
	func Repeat(s string, count int) string

	重复s字符串count次，最后返回重复的字符串

	fmt.Println("ba" + strings.Repeat("na", 2))
	//Output:banana
	func Replace(s, old, new string, n int) string

	在s字符串中，把old字符串替换为new字符串，n表示替换的次数，小于0表示全部替换

	fmt.Println(strings.Replace("oink oink oink", "k", "ky", 2))
	fmt.Println(strings.Replace("oink oink oink", "oink", "moo", -1))
	//Output:oinky oinky oink
	//moo moo moo
	func Split(s, sep string) []string

	把s字符串按照sep分割，返回slice

	fmt.Printf("%q\n", strings.Split("a,b,c", ","))
	fmt.Printf("%q\n", strings.Split("a man a plan a canal panama", "a "))
	fmt.Printf("%q\n", strings.Split(" xyz ", ""))
	fmt.Printf("%q\n", strings.Split("", "Bernardo O'Higgins"))
	//Output:["a" "b" "c"]
	//["" "man " "plan " "canal panama"]
	//[" " "x" "y" "z" " "]
	//[""]
	func Trim(s string, cutset string) string

	在s字符串的头部和尾部去除cutset指定的字符串

	fmt.Printf("[%q]", strings.Trim(" !!! Achtung !!! ", "! "))
	//Output:["Achtung"]
	func Fields(s string) []string

	去除s字符串的空格符，并且按照空格分割返回slice

	fmt.Printf("Fields are: %q", strings.Fields("  foo bar  baz   "))
	//Output:Fields are: ["foo" "bar" "baz"]

 */

 func TestString(){

	 str := make([]byte, 0, 100)
	 str = strconv.AppendInt(str, 4567, 10)
	 str = strconv.AppendBool(str, false)
	 str = strconv.AppendQuote(str, "abcdefg")
	 str = strconv.AppendQuoteRune(str, '单')
	 fmt.Println(string(str))

	 a := strconv.FormatBool(false)
	 b := strconv.FormatFloat(123.23, 'g', 12, 64)
	 c := strconv.FormatInt(1234, 10)
	 d := strconv.FormatUint(12345, 10)
	 e := strconv.Itoa(1023)
	 fmt.Println(a, b, c, d, e)


	// 多字符串拼接 最好用stringbuf
 }