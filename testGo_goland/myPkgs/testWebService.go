package myPkgs

import (
	"errors"
	"fmt"
	"github.com/julienschmidt/httprouter"
	"golang.org/x/net/websocket"
	"io/ioutil"
	"log"
	"net"
	"net/http"
	"net/rpc"
	"net/rpc/jsonrpc"
	"os"
	"strconv"
	"strings"
	"time"
)

func TestParseIP(){

	addr := net.ParseIP("192.168.3.100")
	if addr == nil {
		fmt.Println("Invalid address")
	} else {
		fmt.Println("The address is ", addr.String())
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

func checkError(err error) {
	if err != nil {
		fmt.Fprintf(os.Stderr, "Fatal error: %s", err.Error())
		os.Exit(1)
	}
}

func tcpClient(i uint64){

	fmt.Println(" 【客户端】 开启客户端 " + strconv.FormatUint(i,10))

	service := "192.168.3.100:7777"
	tcpAddr, err := net.ResolveTCPAddr("tcp4", service)
	checkError(err)

	// 连接tcp服务器
	conn, err := net.DialTCP("tcp", nil, tcpAddr)
	checkError(err)

	// 发送求求数据
	_, err = conn.Write([]byte("HEAD / HTTP/1.0\r\n\r\n"))
	checkError(err)

	// 读取响应数据
	result, err := ioutil.ReadAll(conn)
	checkError(err)
	fmt.Println(" 【客户端】 响应数据 " +  string(result))

	fmt.Println(" 【客户端】 关闭客户端 " + strconv.FormatUint(i,10) + "\n")
}

func tcpServer(){

	fmt.Print("开启服务端: ")

	// 创建服务端
	service := ":7777"
	tcpAddr, err := net.ResolveTCPAddr("tcp4", service)
	checkError(err)
	fmt.Print(tcpAddr)

	// 监听接口
	listener, err := net.ListenTCP("tcp", tcpAddr)
	checkError(err)
	fmt.Println(" 开始监听: ")

	for {
		conn, err := listener.Accept()
		if err != nil {
			continue
		}
		fmt.Println(" 【服务端】 建立连接")

		//daytime := time.Now().String()
		//conn.Write([]byte(daytime)) // don't care about return value
		//conn.Close()                // we're finished with this client
		// 修改为支持并发
		//go handleClient_temp(conn)

		// 建立一个长连接
		go handleClient_long(conn)
	}
}

func handleClient_temp(conn net.Conn){
	fmt.Println(" 【服务端】 发送数据 " + time.Now().Local().String())
	defer conn.Close()
	// 接收到的请求数据
	request := make([]byte, 128)
	read_len, err := conn.Read(request)
	if err != nil {
		fmt.Println(err)
	}
	if read_len != 0 {
		if strings.TrimSpace(string(request[:read_len])) == "timestamp" {
			daytime := strconv.FormatInt(time.Now().Unix(), 10)
			// 每次读取到请求处理完毕后，需要清理request，
			// 因为conn.Read()会将新读取到的内容append到原内容之后。
			conn.Write([]byte(daytime))
		}
	}

	// 返回数据
	daytime := time.Now().String()
	conn.Write([]byte(daytime)) // don't care about return value
	// we're finished with this client
}

func handleClient_long(conn net.Conn) {
	conn.SetReadDeadline(time.Now().Add(10 * time.Second)) // set 2 minutes timeout
	request := make([]byte, 128) // set maxium request length to 128B to prevent flood attack
	defer conn.Close()  // close connection before exit
	for {
		read_len, err := conn.Read(request)

		if err != nil {
			fmt.Println(err)
			break
		}

		if read_len == 0 {
			break // connection already closed by client
		} else if strings.TrimSpace(string(request[:read_len])) == "timestamp" {
			daytime := strconv.FormatInt(time.Now().Unix(), 10)
			conn.Write([]byte(daytime))
		} else {
			daytime := time.Now().String()
			conn.Write([]byte(daytime))
		}

		request = make([]byte, 128) // clear last read content
	}
}

func TestTCP()  {
	go func() {

		///// 对应 handleClient_temp
		//time.Sleep(1 * time.Second)
		//var i uint64 = 0
		//for {
		//	time.Sleep(2 * time.Second)
		//	tcpClient(i)
		//	i += 1
		//}

		///// 对应 handleClient_long
		time.Sleep(1 * time.Second)
		var i uint64 = 0
		for i< 5 {
			//time.Sleep(2 * time.Second)
			go tcpClient(i)
			i += 1
		}
	}()

	tcpServer()

}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

func udpClient(i uint64){

	fmt.Println(" 【客户端】 开启客户端 " + strconv.FormatUint(i,10))

	service := ":1200"
	udpAddr, err := net.ResolveUDPAddr("udp4", service)
	checkError(err)

	conn, err := net.DialUDP("udp", nil, udpAddr)
	checkError(err)

	_, err = conn.Write([]byte("anything"))
	checkError(err)

	var buf [512]byte
	n, err := conn.Read(buf[0:])
	checkError(err)

	fmt.Println(string(buf[0:n]))

	fmt.Println(" 【客户端】 关闭客户端 " + strconv.FormatUint(i,10))


}

func udpServer(){
	fmt.Println(" 【客户端】 开启服务端 ")

	service := ":1200"
	udpAddr, err := net.ResolveUDPAddr("udp4", service)
	checkError(err)
	conn, err := net.ListenUDP("udp", udpAddr)
	checkError(err)
	for {
		var buf [512]byte
		_, addr, err := conn.ReadFromUDP(buf[0:])
		if err != nil {
			return
		}
		daytime := time.Now().String()
		conn.WriteToUDP([]byte(daytime), addr)
	}
}

func TestUDP(){
	go func() {
		time.Sleep(1 * time.Second)
		var i uint64 = 0
		for i< 5 {
			//time.Sleep(2 * time.Second)
			go udpClient(i)
			i += 1
		}
	}()

	udpServer()
}


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// ws
func echo(ws *websocket.Conn) {
	var err error

	for {
		var reply string

		if err = websocket.Message.Receive(ws, &reply); err != nil {
			fmt.Println("Can't receive")
			break
		}

		fmt.Println("Received back from client: " + reply)

		msg := "Received:  " + reply + " [reply]"
		fmt.Println("Sending to client: " + msg)

		if err = websocket.Message.Send(ws, msg); err != nil {
			fmt.Println("Can't send")
			break
		}
	}
}

func TestWebSocket() {
	http.Handle("/", websocket.Handler(echo))

	if err := http.ListenAndServe("192.168.3.100:1234", nil); err != nil {
		log.Fatal("ListenAndServe:", err)
	}
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

func Index(w http.ResponseWriter, r *http.Request, _ httprouter.Params) {
	fmt.Fprint(w, "Welcome!\n")
}

func Hello(w http.ResponseWriter, r *http.Request, ps httprouter.Params) {
	fmt.Fprintf(w, "hello, %s!\n", ps.ByName("name"))
}

func getuser(w http.ResponseWriter, r *http.Request, ps httprouter.Params) {
	uid := ps.ByName("uid")
	fmt.Fprintf(w, "you are get user %s", uid)
}

func modifyuser(w http.ResponseWriter, r *http.Request, ps httprouter.Params) {
	uid := ps.ByName("uid")
	fmt.Fprintf(w, "you are modify user %s", uid)
}

func deleteuser(w http.ResponseWriter, r *http.Request, ps httprouter.Params) {
	uid := ps.ByName("uid")
	fmt.Fprintf(w, "you are delete user %s", uid)
}

func adduser(w http.ResponseWriter, r *http.Request, ps httprouter.Params) {
	// uid := r.FormValue("uid")
	uid := ps.ByName("uid")
	fmt.Fprintf(w, "you are add user %s", uid)
}

func TestREST(){
	router := httprouter.New()
	router.GET("/", Index)
	router.GET("/hello/:name", Hello)

	router.GET("/user/:uid", getuser)
	router.POST("/adduser/:uid", adduser)
	router.DELETE("/deluser/:uid", deleteuser)
	router.PUT("/moduser/:uid", modifyuser)

	log.Fatal(http.ListenAndServe(":3000", router))
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// RPC

type Args struct {
	A, B int
}

type Quotient struct {
	Quo, Rem int
}

type Arith int

func (t *Arith) Multiply(args *Args, reply *int) error {
	*reply = args.A * args.B
	return nil
}

func (t *Arith) Divide(args *Args, quo *Quotient) error {
	if args.B == 0 {
		return errors.New("divide by zero")
	}
	quo.Quo = args.A / args.B
	quo.Rem = args.A % args.B
	return nil
}

// Go RPC可以利用HTTP和TCP来传递数据，利用HTTP的好处是可以直接复用net/http里面的一些函数
func rpcServer_http(){
	arith := new(Arith)
	rpc.Register(arith)
	rpc.HandleHTTP()

	err := http.ListenAndServe(":1234", nil)
	if err != nil {
		fmt.Println(err.Error())
	}
}

func rpcCLient_http(){

	serverAddress := "localhost"
	client, err := rpc.DialHTTP("tcp", serverAddress+":1234")
	if err != nil {
		log.Fatal("dialing:", err)
	}

	// Synchronous call
	args := Args{17, 8}
	var reply int
	err = client.Call("Arith.Multiply", args, &reply)
	if err != nil {
		log.Fatal("arith error:", err)
	}
	fmt.Printf("Arith: %d*%d=%d\n", args.A, args.B, reply)


	var quot Quotient
	err = client.Call("Arith.Divide", args, &quot)
	if err != nil {
		log.Fatal("arith error:", err)
	}
	fmt.Printf("Arith: %d/%d=%d remainder %d\n", args.A, args.B, quot.Quo, quot.Rem)
}

func TestRPC_HTTP(){
	go rpcServer_http()

	rpcCLient_http()
}


///////////////////////////////////////

func rpcServer_tcp(){

	arith := new(Arith)
	rpc.Register(arith)

	tcpAddr, err := net.ResolveTCPAddr("tcp", ":1234")
	checkError(err)

	listener, err := net.ListenTCP("tcp", tcpAddr)
	checkError(err)

	for {
		conn, err := listener.Accept()
		if err != nil {
			continue
		}
		rpc.ServeConn(conn)
	}
}

func rpcCLient_tcp(){

	service := ":1234"
	client, err := rpc.Dial("tcp", service)
	if err != nil {
		log.Fatal("dialing:", err)
	}
	// Synchronous call
	args := Args{17, 8}
	var reply int
	err = client.Call("Arith.Multiply", args, &reply)
	if err != nil {
		log.Fatal("arith error:", err)
	}
	fmt.Printf("Arith: %d*%d=%d\n", args.A, args.B, reply)

	var quot Quotient
	err = client.Call("Arith.Divide", args, &quot)
	if err != nil {
		log.Fatal("arith error:", err)
	}
	fmt.Printf("Arith: %d/%d=%d remainder %d\n", args.A, args.B, quot.Quo, quot.Rem)
}


func TestRPC_TCP(){
	go rpcServer_tcp()

	rpcCLient_tcp()
}

///////////////////////////////////////

func jsonRpcServer(){

	arith := new(Arith)
	rpc.Register(arith)

	tcpAddr, err := net.ResolveTCPAddr("tcp", ":1234")
	checkError(err)

	listener, err := net.ListenTCP("tcp", tcpAddr)
	checkError(err)

	for {
		conn, err := listener.Accept()
		if err != nil {
			continue
		}
		jsonrpc.ServeConn(conn)
	}
}

func jsonRpcClient() {

	service := "localhost:1234"
	client, err := jsonrpc.Dial("tcp", service)
	if err != nil {
		log.Fatal("dialing:", err)
	}
	// Synchronous call
	args := Args{17, 8}
	var reply int
	err = client.Call("Arith.Multiply", args, &reply)
	if err != nil {
		log.Fatal("arith error:", err)
	}
	fmt.Printf("Arith: %d*%d=%d\n", args.A, args.B, reply)

	var quot Quotient
	err = client.Call("Arith.Divide", args, &quot)
	if err != nil {
		log.Fatal("arith error:", err)
	}
	fmt.Printf("Arith: %d/%d=%d remainder %d\n", args.A, args.B, quot.Quo, quot.Rem)
}

func TestJsonRpc(){

	go jsonRpcServer()

	jsonRpcClient()
}