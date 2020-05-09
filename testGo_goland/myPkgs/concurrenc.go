package myPkgs

import (
	"runtime"
	"fmt"
	"time"
)

func say(s string) {
	for i := 0; i < 5; i++ {
		runtime.Gosched()
		fmt.Println(i, s)
	}
}

/**
我们可以看到go关键字很方便的就实现了并发编程。 上面的多个goroutine运行在同一个进程里面，共享内存数据，
不过设计上我们要遵循：不要通过共享来通信，而要通过通信来共享。

runtime.Gosched()表示让CPU把时间片让给别人,下次某个时候继续恢复执行该goroutine。

默认情况下，在Go 1.5将标识并发系统线程个数的runtime.GOMAXPROCS的初始值由1改为了运行环境的CPU核数。

 */


 ///
/*
	goroutine运行在相同的地址空间，因此访问共享内存必须做好同步。

	channel通过操作符<-来接收和发送数据

	ch <- v    // 发送v到channel ch.
	v := <-ch  // 从ch中接收数据，并赋值给v

	channel接收和发送数据都是阻塞的，除非另一端已经准备好

*/
func sum(a []int, c chan int) {
	total := 0
	for _, v := range a {
		total += v
	}
	c <- total  // send total to c
}

//////////////
//         Range和Close

func fibonacci(n int, c chan int) {
	x, y := 1, 1
	for i := 0; i < n; i++ {
		c <- x
		x, y = y, x + y
	}
	close(c)   //生产者出关闭channel
}

//////// Go里面提供了一个关键字select，通过select可以监听channel上的数据流动。
func fibonacci_2(c, quit chan int) {
	x, y := 1, 1
	for {
		select {
			case c <- x:
				x, y = y, x + y
			case <-quit:
				fmt.Println("quit")
				return
			}
	}
}

func TestGoroutine(){

	// 避免阻塞超时   select来设置超时
	c := make(chan int)
	o := make(chan bool)
	go func() {
		for {
			select {
				case v := <- c:
					println(v)
				case <- time.After(5 * time.Second):
					println("timeout")
					o <- true
					break
				}
		}
	}()
	<- o

	///////////////

	c = make(chan int)
	quit := make(chan int)
	go func() {
		for i := 0; i < 10; i++ {
			fmt.Println(<-c)
		}
		quit <- 0
	}()
	fibonacci_2(c, quit)

	return

	//////

	c = make(chan int, 10)
	go fibonacci(cap(c), c)
	for i := range c {  //  for i := range c能够不断的读取channel里面的数据,直到该channel被显式的关闭。
		fmt.Println(i)
	}
	// 在消费方可以通过语法v, ok := <-ch测试channel是否被关闭。
	// 如果ok返回false，那么说明channel已经没有任何数据并且已经被关闭。
	return

	///////////////////////////////////

	a := []int{7, 2, 8, -9, 4, 0}

	c = make(chan int)
	go sum(a[:len(a)/2], c)
	go sum(a[len(a)/2:], c)
	x, y := <-c, <-c  // receive from c

	fmt.Println(x, y, x + y)

	return

	////////////////////////////////////////

	go say("world") //开一个新的Goroutines执行
	say("hello") //当前Goroutines执行
}
