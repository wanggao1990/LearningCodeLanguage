#include <iostream>

#pragma warning(disable:4996)

using namespace std;



class MyString
{
public:
	MyString() = default;

	MyString(const char * InitialInput)
	{
		cout << "Construct by default ";
		if (InitialInput != nullptr)
		{
			size_t len = strlen(InitialInput) + 1;
			Buffer = new char[len];
			strcpy_s(Buffer, len, InitialInput);

			fprintf(stdout, "\t\t0x%x", Buffer);
		}
		else
			Buffer = nullptr;

		cout << endl;
	}

	// 拷贝构造 深复制
	MyString(const MyString& str) 
	{
		cout << "Construct by copying ";
		if (str.Buffer != nullptr)
		{
			size_t len = strlen(str.Buffer) + 1;
			Buffer = new char[len];
			strcpy_s(Buffer, len, str.Buffer);

			fprintf(stdout, "\t\t0x%x", Buffer);
		}
		else
			Buffer = nullptr;

		cout << endl;
	}
	// 拷贝赋值 深复制
	// 通常返回this引用，否则会 构造一个临时对象，赋值后，临时对象销毁。
	MyString& operator= (const MyString& str)
	{
		cout << "Construct by copying assign";
		if (str.Buffer != nullptr) {
			size_t len = strlen(str.Buffer) + 1;
			Buffer = new char[len];
			strcpy_s(Buffer, len, str.Buffer);

			fprintf(stdout, "\t0x%x", Buffer);
			cout << endl;
		}
		else
			Buffer = nullptr;

		return *this;
	}

	// 移动构造
	MyString(MyString&& str) noexcept
	{
		cout << "Construct by move ";
		if (str.Buffer != nullptr) {
			Buffer = str.Buffer;
			str.Buffer = nullptr;

			fprintf(stdout, "\t\t0x%x", Buffer);
		}
		else
			Buffer = nullptr;
		
		cout << endl;
	}

	// 移动赋值
	MyString& operator= (MyString&& str) noexcept
	{
		cout << "Construct by move assign";
		if (str.Buffer != nullptr) {
			Buffer = str.Buffer;
			str.Buffer = nullptr;

			fprintf(stdout, "\t\t0x%x", Buffer);
		}
		else
			Buffer = nullptr;

		cout << endl;

		return *this;
	}

	~MyString()
	{
		fprintf(stdout, "Destruct memory \t\t0x%x\n", Buffer);
		if (Buffer)
		{
			delete Buffer;
		}
	}
private:
	char* Buffer;
};

MyString Copy(MyString& str)
{
	MyString tmp("aaaaa");		// 构造
	//return tmp;			     // 移动构造
	//return std::move(tmp);     // 移动构造
	return MyString(tmp);       // 构造

	//return MyString(str);  // 整个函数体就拷贝1个 (若有移动构造，就使用移动构造，否则使用拷贝构造)
	

}


void test1()
{

	MyString str("hello world!");
	cout << "============================================== " << endl;

	// 若不自己实现复制构造， 2个对象指向一个内存区，释放两次就会崩溃（浅复制）
	//   使用std::string就不存在，内部实现了拷贝构造 
	//  （但是，不能自己再实现拷贝构造函数，默认会自己调用std::string的拷贝构造）（数据深复制）
	
	// 拷贝构造
	MyString str1 = str;
	cout << "============================================== " << endl;

	// 拷贝赋值
	MyString str2;
	str2 = str;
	cout << "============================================== " << endl;

	// 移动构造
	MyString str3(std::move(str2));
	cout << "============================================== " << endl;

	// 移动赋值
	MyString str4;
	str4 = std::move(str3);
	cout << "============================================== " << endl;

	MyString str5(str);
	cout << "============================================== " << endl;

	auto ss = Copy(str5);

	// 复制构造、移动构造
	MyString str6(Copy(str));
	cout << "============================================== " << endl;

	MyString str7(std::move(Copy(str)));



	MyString str8;
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// singlton class

class Singlton1
{
public:
	static Singlton1* GetInstance()   // 静态函数 可以被外部直接域名访问
	{
		if (instance == nullptr)
		{
			instance = new Singlton1();  // 非线程安全
			cout << "create a singleton class " << hex << (void *)instance << endl;
			return instance;
		}
		else {
			cout << "return a singleton class " << hex << (void *)instance << endl;
			return instance;
		}

		cout << "return a singleton class " << hex << (void *)instance << endl;
		return instance;
	}

	//~Singlton1() {
	//	if (instance)  // 会无线调用自己，导致栈溢出
	//		delete instance;
	//	cout << "free singlton class " << hex << (void *)instance << endl;
	//};


	// 下面2种存在是，就不能有析构函数
	static void DestoryInstance(const Singlton1 * instance) {  //只能被调用一次
		cout << "Destory singlton class " << hex << (void *)instance << endl;
		if (instance)
			delete instance;
	}

	static void DestoryInstance() {  //只能被调用一次

		if (instance) {
			cout << "Destory singlton class " << hex << (void *)instance << endl;
			delete instance;
			instance = nullptr;  //避免对多次调用
		}
	}

protected:

private:

	// 不允许使用构造和复制构造函数    // c++11 使用delete声明
	Singlton1() {};
	Singlton1(const Singlton1& obj);
	const Singlton1 operator=(const Singlton1& obj);


	static Singlton1* instance; //静态成员 只能被静态函数访问
};

//Singlton1* Singlton1::instance = nullptr;
Singlton1* Singlton1::instance = new Singlton1();// 线程安全, 但是不能用 delete 实例化的对象(不能有析构函数或析构不能delete, 否者循环调用栈溢出)



class Singlton2
{
public:
	static Singlton2& GetInstance()   // 静态函数 可以被外部直接域名访问
	{
		static Singlton2 obj;
		return obj;
	}

	void SetName(const string& name) {
		this->name = name;
	}

	std::string  GetName() {
		return name;
	}

private:

	// 不允许使用构造和复制构造函数
	Singlton2() {};

	Singlton2(const Singlton1& obj);

	const Singlton2 operator=(const Singlton2& obj);

	string name;
};

void test2()
{

	Singlton1 *obj1 = Singlton1::GetInstance();
	Singlton1 *obj2 = Singlton1::GetInstance();
	Singlton1 *obj3 = Singlton1::GetInstance();

	Singlton1::DestoryInstance(); Singlton1::DestoryInstance(); Singlton1::DestoryInstance();

	//Singlton2& obj1 = Singlton2::GetInstance();  obj1.SetName("123");
	//Singlton2& obj2 = Singlton2::GetInstance();	cout << obj2.GetName().c_str() << endl;
	//Singlton2& obj3 = Singlton2::GetInstance();	cout << obj2.GetName().c_str() << endl;


}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class A
{
public:
	A() { cout << "A construct" << endl; }
	virtual ~A() { cout << "A destruct" << endl; }        // 基类虚析构必须实现
	virtual void func() { cout << "A func()" << endl; }
	char *ch = "A";
};


class AA : public virtual A
{
public:
	AA() { cout << "AA construct" << endl; }
	~AA() { cout << "AA destruct" << endl; }
	void func() { cout << "AA func()" << endl; }
	//char *ch = "AA";
};


//class B : public A
class B : public  A
{
public:
	B() { cout << "B construct" << endl; }
	~B() { cout << "B destruct" << endl; }
	void func() { cout << "B func()" << endl; }
	char *ch = "B";
};

class C : public  A
{
public:
	C() { cout << "C construct" << endl; }
	~C() { cout << "C destruct" << endl; }
	void func() { cout << "C func()" << endl; }
	char *ch = "C";
};


class D : public  B, public  C
{
public:
	D() { cout << "D construct" << endl; }
	~D() { cout << "D destruct" << endl; }

};


void test3()
{
	//B b;
	//cout << b.ch << endl;
	//b.func();
	//cout << b.A::ch << endl;
	//b.A::func();

	//A* p = new A();
	//p->func();
	//cout << p->v << endl;
	//delete p;

	//A* p = new B();
	//p->func(); cout << p->ch << endl;   //没有虚继承，输出为A的信息
	//delete p;		// 没有虚析构，不会析构B	


	//B* p = new B();
	//p->func(); cout << p->ch << endl;	
	//p->A::func(); cout << p->A::ch << endl;  //命名空间，输出A的信息
	//delete p;			


	// A增加虚析构
	//A* p = new B();
	//p->func(); cout << p->ch << endl;	
	//p->A::func(); cout << p->A::ch << endl;  //命名空间，输出A的信息
	//delete p;		 // 会正常析构B

	//  多重继承建议用虚继承，基类限定为一个备份
	//D d;
	//d.A::func();cout << d.A::ch << endl;
	//d.B::func(); cout << d.B::ch << endl;
	//d.C::func(); cout << d.C::ch << endl;

	//AA aa;
	//aa.A::func(); cout << aa.A::ch << endl;
	//aa.func(); cout << aa.ch << endl;

	//A *paa = new AA();
	//paa->A::func(); cout << paa->A::ch << endl;
	//paa->func(); cout << paa->ch << endl;
	//delete paa;

	A *aa = new AA();	// 父类指针指向子类
	aa->func(); cout << aa->ch << endl;  // 函数为非虚时，调用基类
	delete aa;
}


// POD   无类，无虚函数，无自定义构造和析构

void  test4()
{




}


// 值传递 和 引用传递，  类变量
class test {
    static int object_count;
public:
    test()
    {
        object_count++;
        print("test()");
    }
    static void print(const char *msg = 0)
    {
        if(msg) cout << msg << ": ";
        cout << "object_count = " << object_count << endl;
    }
    ~test()
    {
        object_count--;
        print("~test()");
    }
};
int test::object_count = 0;


void test5()
{
    // pass and return by value.
    auto func = [](test x) // 值传递吗，生命周期结束会导致object_count减1
    {
        x.print("x argument inside f()"); 
        return x;
    };


    auto func2 = [](const test& x) {
        x.print("x argument inside f()");
        return x;
    };


    test h;
    test::print("after construction of h");

    test h2 = func(h); //期望得到 object_count = 2， 实际是局部变量的生命周期结束会导致为0
   
    //test h2 = func2(h);
    test::print("after call to f()");


}


struct Base1 {
    virtual void foo(int);
};
struct SubClass1 : Base1 {
    void foo(int) override; // 合法
   // virtual void foo(float) override; // 非法, 父类没有此虚函数
};

void test6()
{

    class Magic {
    public:
        Magic() = default; // 显式声明使用编译器生成的构造
        Magic& operator=(const Magic&) = delete; // 显式声明拒绝编译器生成构造
        Magic(int magic_number);
    };




    class Base {
    public:
        int value1;
        int value2;

        Base()
        {
            value1 = 1;
        }

        Base(int value) : Base()
        { // 委托 Base() 构造函数.
            // 这使得构造函数可以在同一个类中一个构造函数调用另
            // 一个构造函数，从而达到简化代码的目的：
            value2 = value;
        }
    };


    /// 在传统 C++ 中，构造函数如果需要继承是需要将参数一一传递的，
    // 这将导致效率低下。C++11 利用关键字 using 引入了继承构造函数的概念：
    class Subclass : public Base {
    public:
       //  using Base::Base; // 继承构造, 否则需要显示写出实例化时对应的构造函数

        // 显示写出构造函数
        Subclass() : Base() {}
        Subclass(int v) : Base(v) {}
    };


    //Subclass s;        // 类需要无参构造函数
    Subclass s(3);    // 类需要参构造函数
    std::cout << s.value1 << std::endl;
    std::cout << s.value2 << std::endl;
}


void main1()
{
	//int a[10] = { 0,1,2,3,4,5,6,7,8,9 };
	//int (*p)[10] = &a;

	//test1();
	//test2();
	//test3();

	//test4();

   // test5();

    test6();

	system("pause");
}


class TestOperatorPoint {
public:
    // default
    TestOperatorPoint() = default;

    TestOperatorPoint(int x, int y) : 
        x(x), y(y) //参数名、成员变量可以同名
    {
    }


    // copy constructor
    TestOperatorPoint(const TestOperatorPoint& pt)
    {
        std::cout << "copy constructor" << std::endl;
        x = pt.x;
        y = pt.y;
    }


    // move constructor
    TestOperatorPoint(TestOperatorPoint&& pt)
    {
        std::cout << "move constructor" << std::endl;
        x = std::move(pt.x);  // x,y是基本类型，移动时不影响
        y = std::move(pt.y);
    }


    //// 错误的拷贝赋值
    //TestOperatorPoint operator=(const TestOperatorPoint& pt)
    //{
    //    std::cout << "wrong copy assign" << std::endl;
    //   // x = pt.x;
    //    //y = pt.y;
    //   // return *this;   // 如果不返回引用，会将*this对象进行一次拷贝赋值，
    //    return pt;       // 直接返回也会再进行一次拷贝赋值，
    //}

    // copy assign
    TestOperatorPoint& operator=(const TestOperatorPoint& pt)
    {
        std::cout << "copy assign" << std::endl;
        x = pt.x;
        y = pt.y;
        return *this;   
    }


    // move assign
    TestOperatorPoint& operator=(TestOperatorPoint&& pt)
    {
        std::cout << "move assign" << std::endl;
        x = std::move(pt.x);  // x,y是基本类型，移动时不影响； 
        y = std::move(pt.y);
        return *this;
    }


// operations

    TestOperatorPoint operator+(const TestOperatorPoint& pt)
    {
        TestOperatorPoint tmp;
        tmp.x = x + pt.x;
        tmp.y = y + pt.y;
        return tmp;     // 返回局部临时变量，编译器优化为 移动操作，不要画蛇添足
    }


    TestOperatorPoint& operator+=(const TestOperatorPoint& pt) 
    {
        x += pt.x;
        y += pt.y;
        return *this;   // 明确是对自己要修改，要返回引用。否则多一次拷贝构造。
    }

    //  输出重载
    friend std::ostream& operator<< (std::ostream& out, const TestOperatorPoint& pt);
    //{
    //    out << "[" << pt.x << ", " << pt.y << "]";
    //    return out;
    //}


//private:
    int x, y;

};

// 外部实现时，函数不要加类的作用域
std::ostream& operator<< (std::ostream& out, const TestOperatorPoint& pt)
{
    out << "[" << pt.x << ", " << pt.y << "]";
    return out;
}

// 混合类型表达式定义为普通的非成员函数(第二个参数不是同一个类类型)
template<typename T>
TestOperatorPoint operator*(const TestOperatorPoint& pt, T v)
{
    TestOperatorPoint tmp;
    tmp.x = pt.x * v;     // 会强转为TestOperatorPoint.x的成员类型
    tmp.y = pt.y * v;
    return tmp;
}

// 上面乘法运算的重载，对称性
template<typename T>
TestOperatorPoint operator*(T v, const TestOperatorPoint& pt)
{
    TestOperatorPoint tmp;
    tmp.x = pt.x * v;     // 会强转为TestOperatorPoint.x的成员类型
    tmp.y = pt.y * v;
    return tmp;
}


void testOperatorPoint()
{
    std::string str1 = "abc";
    std::string str2 = std::move(str1);


    {
        TestOperatorPoint pt1;
        TestOperatorPoint pt2(3, 4);

        TestOperatorPoint pt3(pt2);   // 拷贝构造
        pt1 = pt2;                    // 拷贝赋值，   pt1已经存在


        TestOperatorPoint pt4;
        TestOperatorPoint pt5(1, 1);
        TestOperatorPoint pt6(2, 2);

        TestOperatorPoint pt7(std::move(pt5));   // 移动构造
        pt4 = std::move(pt6);                    // 拷贝赋值，   pt4已经存在
    }

    printf("==========================================\n");

    {
        TestOperatorPoint pt1(1, 2);
        TestOperatorPoint pt2(3, 4);

        TestOperatorPoint pt3 = pt1 + pt2; // 移动构造（pt1的成员函数中临时变量进行移动构造）


        TestOperatorPoint pt4(0,0);
        pt4 += pt1;

        std::cout << pt4 << std::endl;


        TestOperatorPoint pt5 = pt4 * 3.14;

        // int类型没有定义 operator*(TestOperatorPoint)
        // 因此必须定义一个普通的非成员重载的操作符函数operator*(T v, const TestOperatorPoint& pt)
        TestOperatorPoint pt6 = 3.14 * pt4 ;  
    }

}




//////////////////////////////////////////////////////////////////////////




#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <random>

class Foo
{
public:
	Foo()
		: flag_(0)
		, thread1_(std::bind(&Foo::threadFunc1, this))
		, thread2_(std::bind(&Foo::threadFunc2, this))
	{
	}

	~Foo()
	{
		thread1_.join();
		thread2_.join();
	}

private:
	void threadFunc1()
	{
		{
			std::unique_lock<std::mutex> ul(mutex_);
			//while (0 == flag_) {
			//	std::cout << "waiting for notify..." << std::endl;
			//	cond_.wait(ul);
			//	}

			std::cout << "waiting for notify..." << std::endl;
			cond_.wait(ul);

			std::cout << flag_ << std::endl;
		}
	}

	void threadFunc2()
	{
		// 为了测试，等待3秒  
		std::this_thread::sleep_for((std::chrono::milliseconds(3000)));
		std::unique_lock<std::mutex> ul(mutex_);
		flag_ = 100;

		std::cout << " notified" << std::endl;
		cond_.notify_one();
	}

	int flag_;


	std::mutex mutex_;
	std::condition_variable cond_;

	// 必须放在 mutex和cv后面，否则内存错误
	std::thread thread1_;
	std::thread thread2_;	
	

};

int main3()
{
	Foo f;


	this_thread::sleep_for(std::chrono::seconds(5));

	system("pause");
	return 0;
}

/// 

#include <iostream>
#include <condition_variable>
#include <thread>
#include <chrono>

std::condition_variable cv;
std::mutex cv_m; // 此互斥用于三个目的：
				 // 1) 同步到 i 的访问
				 // 2) 同步到 std::cerr 的访问
				 // 3) 为条件变量 cv
int i = 0;

void waits(int id)
{
	if (id>4){
		std::this_thread::sleep_for(std::chrono::seconds(10));
	}

	std::unique_lock<std::mutex> lk(cv_m);
	std::cerr << id<< " Waiting... \n";
	cv.wait(lk, [=] {
		bool ret = i == 1;
		if (ret){
			std::cout << "notified success for id=" << id << std::endl;
		}
		else {
			std::cout << "notified failed for id=" << id << std::endl;
		}
		return ret; 
	});

	std::cerr << id << "...finished waiting. i == 1\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void signals()
{
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cerr << "Notifying all...\n";
	cv.notify_all();

	std::this_thread::sleep_for(std::chrono::seconds(3));
	{
		cout << endl;
		std::lock_guard<std::mutex> lk(cv_m);
		i = 1;

		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cerr << "Notifying again...\n\n";
	}
	cv.notify_all();

	std::this_thread::sleep_for(std::chrono::seconds(1));
	{

		std::lock_guard<std::mutex> lk(cv_m);
		i = 0;
	}
	std::this_thread::sleep_for(std::chrono::seconds(10));


	{
		std::lock_guard<std::mutex> lk(cv_m);
		i = 1;
	}
	cout << endl;
	cv.notify_all();
}

int main4()
{
	std::thread t1(waits,1), t2(waits,2), t3(waits,3);
	std::thread t5(waits, 5), t6(waits, 6);

	std::thread t4(signals);



	t1.join();
	t2.join();
	t3.join();
	t4.join();

	t5.join();
	t6.join();


	system("pause");
	return 0;
}

//////////////////////////////////////////////////////////////////////////

int main5()
{

	std::mutex mtx;

	std::thread t1([&]() {
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
		std::lock_guard<std::mutex> lg(mtx);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));

	});
	
	std::thread t2([&]() {
		std::this_thread::sleep_for(std::chrono::milliseconds(3));
		if(! mtx.try_lock())
			cout << " try failed" << endl;
		else {
			cout << " try success" << endl;
			mtx.unlock();
		}
	});

	t1.join();
	t2.join();



	system("pause");
	return 0;
}

//////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex m;
//std::condition_variable cv;
std::string dataStr;
bool ready = false;
bool processed = false;


void sleep(int sec)
{
	std::this_thread::sleep_for(std::chrono::seconds(sec));
}

void worker_thread()
{
	//sleep(5);

	cout << "  work thread..." << endl;

	// 等待直至 main() 发送数据
	std::unique_lock<std::mutex> lk(m);
	cv.wait(lk, [] {
		cout << "  worker wait , ready=" << ready << endl;
		return ready; 
	});

	// 等待后，我们占有锁。
	std::cout << "Worker thread is processing data\n";
	dataStr += " after processing";

	sleep(15);

	// 发送数据回 main()
	processed = true;
	std::cout << "Worker thread signals data processing completed\n";

	// 通知前完成手动锁定，以避免等待线程只再阻塞（细节见 notify_one ）
	lk.unlock();
	cv.notify_one();
}

int main6()
{
	std::thread worker(worker_thread);
	dataStr = "Example data";
	
	// 发送数据到 worker 线程
	{
		sleep(10);
		std::cout << "  main() signals data ready for processing\n";
		std::lock_guard<std::mutex> lk(m);
		ready = true;

	}		
	
	cout << "  main notify" << endl;
	cv.notify_one();
	//sleep(10);


	// 等候 worker
	{
		std::unique_lock<std::mutex> lk(m);
		cv.wait(lk, [] {
			cout << "  main wait, process=" << processed << endl;
			return processed; 
		});
		lk.unlock();
	}
	std::cout << "Back in main(), data = " << dataStr << '\n';

	worker.join();

	system("pause");
	return 0;
}

//////////////////////////////////////////////////////////////////////////

int main7()
{
	thread_local int j = 0;
	auto foo = []
	{
		m.lock();
		j++; // j is now 1, no matter the thread. j is local to this thread.
		m.unlock();

		cout << j << endl;
	};
	auto  func = [&]
	{
		j = 0;
		std::thread t1(foo);
		std::thread t2(foo);
		t1.join();
		t2.join();
		// j still 0. The other "j"s were local to the threads
	};

	func();

	system("pause");

	return 0;
}

//////////////////////////////////////////////////////////////////////////

#include <future>

int main8()
{
	std::future<int> f1 = std::async(std::launch::async, []() { 
		cout << "start thread " << endl;  return 8; 
	});
	std::cout << f1.get() << std::endl;  //output: 8

	std::future<void> f2 = std::async(std::launch::async, []() {
		std::cout << 8 << std::endl; 
	});
	f2.wait(); //output: 8

	std::future<void> f3 = std::async(std::launch::async, []() {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		std::cout << 9 << std::endl;
	});
	f3.wait(); //output: 9
	cout << endl;

	std::future<int> future = std::async(std::launch::async, []() {
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return 8;
	});

	std::cout << "waiting...\n";
	std::future_status status;
	do {
		status = future.wait_for(std::chrono::milliseconds(600));

		if (status == std::future_status::deferred) {
			std::cout << "deferred\n";
		}
		else if (status == std::future_status::timeout) {
			std::cout << "timeout\n";
		}
		else if (status == std::future_status::ready) {
			std::cout << "ready!\n";
			std::cout << "result is " << future.get() << std::endl;
		}
	} while (status != std::future_status::ready);

	//std::cout << "result is " << future.get() << std::endl;  // 只能调用一次

	system("pause");
	return 0;
}

//////////////////////////////////////////////////////////////////////////

#include <thread>
#include <atomic>
#include <stdio.h>
#include <list>

std::atomic_bool bIsReady = false;
std::atomic_int iCount = 20;
void threadfun1()
{
	//if (!bIsReady) {
	//	std::this_thread::yield();
	//}
	while (iCount > 0)
	{
		printf("iCount:  %d\r\n", iCount--);
	}
}

int main9()
{
	std::atomic_bool b;
	std::list<std::thread> lstThread;

	for (int i = 0; i < 10; ++i)
	{
		lstThread.push_back(std::thread(threadfun1));
	}

	for (auto& th : lstThread)
	{
		th.join();
	}

	system("pause");
	return 0;
}
//////////////////////////////////////////////////////////////////////////

std::mutex mtx;


void print_id(int id) {
	std::unique_lock<std::mutex> lck(mtx);

	std::cout << "thread " << id << " start \n";

	//while (!ready)
	//	cv.wait(lck);
	cv.wait(lck, 
		[] {return ready;
	});

	// ...
	std::cout << "thread " << id << " done \n";
}

void go() {
	std::unique_lock<std::mutex> lck(mtx);	
	sleep(3);
	ready = true;
	std::cout << "notify all\n";
	cv.notify_all();
}

int main10()
{
	std::thread threads[10];
	// spawn 10 threads:
	for (int i = 0; i < 10; ++i)
		threads[i] = std::thread(print_id, i);

	sleep(1);
	std::cout << "10 threads ready to race...\n";
	go();                       // go!

	for (auto& th : threads) th.join();


	system("pause");
	return 0;
}

//////////////////////////////////////////////////////////////////////////

int main11() {
	allocator<string> alloc;
	string* str = alloc.allocate(4); //分配10个未初始化的string

	auto itr = str;
	alloc.construct(itr, "chengdu"); //chengdu
	cout << str[0] << endl;
	itr++;
	alloc.construct(itr, "beijing"); //beijing
	cout << str[1] << endl;
	itr++;
	alloc.construct(itr, 10, 'c'); //10个c组成的字符串
	cout << str[2] << endl;
	itr++;
	alloc.construct(itr); //空字符串
	cout << str[3] << endl;

	for (int i = 0; i < 4; i++) {
		cout << str[i] << endl;
	}

	// 销毁
	while (itr != str) {
		alloc.destroy(itr--);
	}

	system("pause");
	return 0;
}

//////////////////////////////////////////////////////////////////////////

int count_c = 0;
int fib(int n)   // O(N**3)
{
	count_c ++;
	if (n <= 1)
		return 1;
	else {
		return fib(n - 1) + fib(n - 2);
	}
}


int fib2(int n)   // O(N)
{
	count_c++;
	if (n <= 1)	return 1;
	long res;
	long last = 1;
	long lastLast = 1;
	for (int i = 1; i < n; ++i)	{
		res = last + lastLast;
		lastLast = last;
		last = res;
	}
	return res;
}

int maxSubSum(const vector<int>& nums)
{
	if (nums.size() == 1)
		return nums[0];

	int maxSum = 0, thisSum = 0;

	for (auto& elem : nums)
	{
		thisSum += elem;
		if (thisSum > maxSum)
		{
			maxSum = thisSum;
		}
		else if (thisSum < 0)
		{
			thisSum = 0;
		}

	}
	return maxSum;
}


int binarySearch(const vector<int>& arr, int x)
{
	int low = 0, high = arr.size() - 1;

	while (low <= high)
	{
		int mid = (low + high) / 2;

		if (arr[mid] < x)		low = mid;
		else if (arr[mid] > x)	high = mid;
		else return mid;
	}
	return -1;
}


#include <map>
#include <unordered_map>
void mapTest()
{
	std::map<char, std::string> mymap;

	mymap['a'] = "an element";
	mymap['b'] = "another element";
	mymap['c'] = mymap['b'];

	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

	std::cout << "mymap now contains " << mymap.size() << " elements.\n";

	auto ret = mymap.insert({'a',"aaa"});  // ret => pair{elem iter, bool}

    auto e = mymap.end();
    auto retF = mymap.find('d');
 //   retF = mymap.find('e');


    int idx = std::distance(retF, mymap.end());

	
	for(const auto& it : mymap) {
		auto xx = it;
	}
	


	// 无序容器的管理(桶)
	{
		std::unordered_map<char, std::string> umap;
		umap['a'] = "an element";
		umap['b'] = "another element";
		umap['c'] = umap['b'];

		std::cout << "umap['a'] is " << umap['a'] << '\n';
		std::cout << "umap['b'] is " << umap['b'] << '\n';
		std::cout << "umap['c'] is " << umap['c'] << '\n';
		std::cout << "umap['d'] is " << umap['d'] << '\n';

		std::cout << "umap now contains " << umap.size() << " elements.\n";

		auto ret = umap.insert({ 'a',"aaa" });  // 插入失败，没有修改

		// 桶管理
		umap.bucket_count();
		umap.rehash(10);  //重组

	}
}

#include <set>
void setTest()
{
	std::vector<int> ivec;
	for (size_t i = 10; i >0; --i) {
		ivec.push_back(i);
		ivec.push_back(i);
	}

	{
		std::set<int> iset(ivec.begin(), ivec.end());
		for(auto i : iset)
			cout << i << endl;

		auto endIt = iset.end();
		auto ret = iset.find(1);
		if(ret == endIt)
			cout << " not exist" << endl;

	}

	{	
		std::multiset<int> mset(ivec.begin(), ivec.end());

		// 获multiset/multimap的多个相同元素

		auto iter = mset.find(2);   // 第一个元素为2的迭代器
		auto entries = mset.count(2); // 所有元素值为2的  (多个值连续存储)

		for (int i = 0; i < entries; i++) {
			cout << *(iter++) << endl;
		}


		//另一种方式
		auto iterRange = mset.equal_range(2);
		for (auto& it = iterRange.first; it != iterRange.second; it++ ) {
			cout << *it << endl;
		}
	}
}


void stringTest()
{
	{
		const char* arr = "abc";
		std::string tmp = "string testr!";
		std::string str = "String.";
		str.insert(3, tmp, 6,5);   //在str的3位置插入tmp从6开始的5个字符 => "Str testing."


		auto aaa = str.find("t");
		aaa = str.rfind("t");

		str.replace(str.find(' '),10 , " abcba.");  // "Str abcba"

		aaa = str.find("ab");	// 正向查找字符串"ab"   4
		aaa = str.rfind("ab");	// 逆向查找字符串"ab"   4
		aaa = str.rfind("ba");	// 逆向查找字符串"ab"   7

		aaa = str.find_first_of("rt");  // 正向查找"rt"中任意一个字符第一次出现的位置


		std::string str2 = "pi = 3.14;" ;
		auto subStr = str2.substr(str2.find_first_of("+-.0123456789"));  // "3.14;"    以数字、“.”、“+”、“-”开始
		auto vald = std::stod(subStr);
		auto valf = std::stof(subStr);

		auto val = std::stoi("123");
		val = std::stoi("123", 0, 8);    // O(0123) =>  D(83)
		val = std::stoi("123", 0, 16);   //  H(0x123)  => D(291)


	}
}


#include <memory>
void testPtr_shared()
{
	////////////////    shared_ptr
	{
		{
			std::shared_ptr<char*> pChar;  // 空指针
			pChar = std::make_shared<char*>(new char[10]);
			auto xxx = *pChar; //解引用，指向管理对象，也就是char*内存
			auto yyy = pChar.get(); // 同xxx, 返回对象指针
		}

		{
			std::shared_ptr<int> ptr1(new int(1));     // 引用计数 1
			std::shared_ptr<int> ptr2 = ptr1;   //  ptr2共享ptr1的指向对象    // 引用计数 2

			ptr2.reset();  // ptr2置为空   //引用计数 1

			int *pi = new int(2);
			ptr2.reset(pi);  // ptr2指向pi内存

		}


		{
			vector<string> v1;//空vector
			{//新作用域
				vector<string> v2 = { "f", "jf" };
				v1 = v2;//从v2拷贝元素到v1中
			}//离开作用域,v2被销毁,其中元素也被销毁
			 //v1中有2个元素,是原来v2中元素的拷贝
		}


		{
			class StrBlob {
			public:
				using size_type = std::vector<std::string>::size_type;

				//StrBlob();
				StrBlob(std::initializer_list<std::string> il) :
					data(std::make_shared<std::vector<std::string>>(il))
				{
				}  // NOTE

				size_type size() const { return data->size(); }
				bool empty() const { return data->empty(); }

				void push_back(const std::string& str) { data->push_back(str); }

				void pop_back() { check(0, "pop_back on empty StrBlob"); data->pop_back(); }

				// 这里没有修改成员对象的值，是调用成员的成员函数修改内部值
				void pop_back()const { check(0, "pop_back on empty StrBlob"); data->pop_back(); }


				//std::string& front(){	check(0, "front on empty StrBlob");	return data->front();}
				//std::string& back()	{	check(0, "back on empty StrBlob");	return data->back();}

				// const函数， 建议返回const引用
				std::string& front() const { check(0, "front on empty StrBlob");	return data->front(); }
				std::string& back() const { check(0, "back on empty StrBlob");	return data->back(); }

			private:
				std::shared_ptr<std::vector<std::string>> data;

				void check(size_type i, const std::string& msg) const
				{
					if (i >= data->size())	throw std::out_of_range(msg);
				}
			};

			{
				StrBlob strBlob = { "123","abc" };   // ref = 1
				strBlob.push_back(",.?");
				while (!strBlob.empty()) {
					auto& str = strBlob.back();   // 非const对象，先找非const函数实现，若无再找const函数
					std::cout << str << std::endl;
					strBlob.pop_back();
				}
				{
					StrBlob b = strBlob;   //ref = 2    data数据共用
					b.push_back("a");
				}

				strBlob.push_back("a");  // 两个元素 ["a","a"]

			}

			{
				const StrBlob strBlob = { "123","abc" };
				// const 对象只能使用const函数
				while (!strBlob.empty()) {
					auto& str = strBlob.back();
					str = "aaa"; // ???
					std::cout << str << std::endl;
					strBlob.pop_back();
				}
			}
		}


		{
			int *p = new int();
			*p = 1;

			delete p;  // delete后p为野指针
			{
				p = nullptr;
				delete p;    // delete一个空指针是没有错误的
			}
		}

		{
			std::shared_ptr<int> p1;     // 空指针
			//不能显示地转换
			//p = new	int(99); 
			p1 = std::make_shared<int>(22);

			//std::shared_ptr<int> p2 = new int(21); //必须使用直接初始化
			std::shared_ptr<int> p2 = std::make_shared<int>(21);
			std::shared_ptr<int> p3(new int(20));
		}

		{
			auto process = [](std::shared_ptr<int> ptr) {
				*ptr += 1;
			};

			{
				std::shared_ptr<int> p(new int(1));  // ref 1
				process(p);    // 调用时ref 2, 返回时 ref 1
				int res = *p;
			}

			{
				int *x(new int(1));
				// process(x);			// 不能从int* 转换为 shared_ptr<int>
				process(std::shared_ptr<int>(x));   // 用内置指针显示构造一个临时shared_ptr接管, 函数返回时会释放x的内存
				int res = *x;						// 未定义，x目前是一个空悬指针
			}
		}

		{
			// get()返回内置指针，用于不接受只能指针的代码， 
			std::shared_ptr<int> p(new int(1));
			int *x = p.get(); //正确,但使用时要注意,不要让它管理的指针被释放
			{//新作用域
				std::shared_ptr<int>(x);//未定义,两个独立的shared_ptr指向相同的内存
			}//程序块结束,p被销毁,它指向的内存被释放
			int foo = *p;  //未定义,p指向的内存已经被释放了
		}

		{ // 修改智能指针的底层数据，先要判断是否有其他用户使用
			std::shared_ptr<int> p(new int(1));

			std::shared_ptr<int> p2(p);

			if (!p.unique()) {
				// 不是唯一的用户，分配新的拷贝
				// p.reset(new int(2));    
				p = std::make_shared<int>(2);   // 效果同上
			}
			*p += 1; //唯一用户，可以改变，不影响其他对象的值

			std::cout << *p2 << "  " << *p << std::endl;  // 1  3
		}



		{ // 删除器 deleter


			class DataMem {
			public:
				//DataMem();
				DataMem(size_t sz) : p(new int[10]) {}
				// ~DataMem() { release(); }

				int* getPtr() { return p; }
				void release() { delete[] p;  p = nullptr; }
			private:
				int* p;
			};

			int *ptr = nullptr;
			try {

				{
					DataMem dm = DataMem(10);   // 局部对象， 无析构函数
					ptr = dm.getPtr();

					//使用代码
					// ....
					throw 1;          // 假装有异常 , 局部对象无析构函数，不会执行异常抛出后面的代码
					// ....

					//  不要忘记释放 （异常发生后不会执行，导致内存泄漏） 
					dm.release();
				}


				
				//	{
				//		DataMem dm = DataMem(10);   // 局部对象，有析构函数
				//		ptr = dm.getPtr();

				//		//使用代码
				//		// ....
				//		throw 1;          // 假装有异常 , 局部对象有析构函数，会执行析构函数（用户确保对象动态内存释放）
				//		// ....
				//	    //不要忘记释放 （异常发生后不会执行） 
				//	    dm.release();
				//	}
				

				
				{
					// 创建一个删除器作为智能指针的自定义操作参数，类型为对象指针的函数
					//  删除器原型 void funcName(DataMem* dm) {  ...;  }
					auto ReleaseMem = [](DataMem* dm)-> void {
						dm->release();
					};

					DataMem dm = DataMem(10);   // 局部对象,无析构函数
					//std::shared_ptr<DataMem> pdm(&dm, ReleaseMem);   // 局部对象,无析构函数； 删除器； 
					std::shared_ptr<DataMem> pdm(&dm, [](DataMem* dm) {dm->release(); });

					ptr = dm.getPtr();

					//使用代码
					// ....
					throw 1;          // 假装有异常 , 局部对象无析构，shared_ptr接管并负责用删除器回收内存
					// ....
				}


			}
			catch (int e) {
				std::cout << "catch throw " << e << std::endl;
			}
			catch (std::exception& e) {
				std::cout << e.what() << std::endl;
			}
		}

	}
}


void testPtr_unique()
////////////////    unique_ptr
{
	{
		std::unique_ptr<int> p1;
		p1 = std::unique_ptr<int>(new int(1));
		//p1 = std::make_unique<int>(2); //c++14

		std::unique_ptr<int> p2(new int(3));
		//p1 = p2; 不允许

		//p1 = nullptr; // 释放p1指向对象
		p1.reset();   // 释放p1指向对象,效果同上

		int *ptr = p2.release(); // 仅放弃控制权，p2为空指针，并返回指向对象的内置指针

		delete ptr; //需要自己管理内存数据
	}

	{
		std::unique_ptr<int> p3(new int(4));
		std::unique_ptr<int> p4(new int(5));
		p3.reset(p4.release());   //  p4释放控制权，返回对象指针； p3释放原有对象，接管p4的对象
	}

	{ // deleter
		class DataMem {
		public:
			//DataMem();
			DataMem(size_t sz) : p(new int[10]) {}
			//~DataMem() { release(); }

			int* getPtr() { return p; }
			void release() { delete[] p;  p = nullptr; }
		private:
			int* p;
		};

		int *ptr = nullptr;
		try {

			//{
			//	DataMem dm = DataMem(10);   // 局部对象，有析构函数
			//	ptr = dm.getPtr();
			//
			//	//使用代码
			//	// ....
			//	throw 1;
			//}


			//{
			//	auto ReleaseMem = [](DataMem* dm)-> void {
			//		dm->release();
			//	};

			//	DataMem dm = DataMem(10);   // 局部对象,无析构函数
			//	//std::shared_ptr<DataMem> pdm(&dm, [](DataMem* dm)->void {dm->release(); });


			//	std::unique_ptr<DataMem, decltype(ReleaseMem)> pdm(&dm, ReleaseMem); //使用删除器必须指定模板类型
			//	//std::unique_ptr<DataMem, void (*)(DataMem* dm)> pdm(&dm, ReleaseMem);  // 同上

			//	ptr = dm.getPtr();

			//	//使用代码
			//	// ....
			//	throw 1;          // 假装有异常 , 局部对象无析构，shared_ptr接管并负责用删除器回收内存
			//					  // ....
			//}

			{
				std::unique_ptr<DataMem> pdm1(new DataMem(10));
				ptr = pdm1->getPtr();
				
				// 移交指针控制权，指针初始化新的unique_ptr，并置空。
				//std::unique_ptr<DataMem> pdm2 = std::move(pdm1); 
				std::unique_ptr<DataMem> pdm2(std::move(pdm1));

				//类似如下
				//  std::unique_ptr<DataMem> pdm2;   
				//  pdm2.reset(pdm1.release());
				//可简写为  std::unique_ptr<DataMem> pdm2(pdm1.release());

			}
		}
		catch (int e) {
			std::cout << "catch throw " << e << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}

}

////////////////    weak_ptr

class StrBlobPtr;  //前置声明

class StrBlob {
	friend class StrBlobPtr;  // 需要前置声明

public:
	using size_type = std::vector<std::string>::size_type;

	StrBlob() = default;
	StrBlob(std::initializer_list<std::string> il) :
		data(std::make_shared<std::vector<std::string>>(il))
	{
	}

	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }

	void push_back(const std::string& str)
	{
		if (!data) {
			data = std::make_shared<std::vector<std::string>>();
		}
		data->push_back(str);
	}

	void pop_back() { check(0, "pop_back on empty StrBlob"); data->pop_back(); }

	// 这里没有修改成员对象的值，是调用成员的成员函数修改内部值
	void pop_back() const { check(0, "pop_back on empty StrBlob"); data->pop_back(); }

	// const函数， 建议返回const引用
	const std::string& front() const { check(0, "front on empty StrBlob");	return data->front(); }
	const std::string& back() const { check(0, "back on empty StrBlob");	return data->back(); }

	// 实现必须放在 StrBlobPtr类实现之后，否则出现未定义，因为只有声明
	StrBlobPtr begin();
	StrBlobPtr end();

private:
	std::shared_ptr<std::vector<std::string>> data;

	void check(size_type i, const std::string& msg) const
	{
		if (i >= data->size())	throw std::out_of_range(msg);
	}
};



class StrBlobPtr
{
public:
	StrBlobPtr() : curr(0) {}

	StrBlobPtr(StrBlob& a, std::size_t sz = 0) :
		wptr(a.data), curr(sz)   // StrBlobPtr为StrBlob友元类，可以直接访问私有数据
	{}

	//void push_back(const std::string& str) { check(0,"")->push_back(str); }
	//void pop_back() const { check(0, "pop_back on empty StrBlob")->pop_back(); }
	//// const函数， 建议返回const引用
	//const std::string& front() const { return check(0, "front on empty StrBlob")->front(); }
	//const std::string& back() const { return check(0, "back on empty StrBlob")->back(); }


	// 解引用访问当前指向vector中的元素
	std::string& deref() const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}

	// 前缀递增，返回递增后的对象的引用
	StrBlobPtr& incr()
	{
		check(curr, "increment past end of StrBlobPtr");
		++curr;
		return *this;
	}

	StrBlobPtr& operator++ ()     // 调用方式为 ++StrBlobPtr
	{
		return incr();
	}

	StrBlobPtr& operator++ (int)     // 调用方式为 StrBlobPtr++
	{
		return incr();
	}


	friend bool eq(const StrBlobPtr &lhs, const StrBlobPtr &rhs);

private:
	using SrtArr = std::vector<std::string>;

	// 检查成功 返回一个底层数据的 shared_ptr
	std::shared_ptr<SrtArr> check(std::size_t i, const std::string& msg) const
	{
		auto ret = wptr.lock(); // vector 是否被销毁?
		if (!ret)				throw std::runtime_error("unbound StrBlobPtr");
		if (i >= ret->size())	throw std::out_of_range(msg);
		return ret;
	}

	std::weak_ptr<SrtArr> wptr;  // 保存一个weak_ptr, 意味着底层数据vector可能被销毁

	std::size_t curr; // 在数组中的当前位置
};


StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this);
}

StrBlobPtr StrBlob::end()
{
	auto ret = StrBlobPtr(*this, data->size()); return ret;
}

// 该函数需要访问StrBlobPtr的私有变量，所以将其定义有友元函数
bool eq(const StrBlobPtr & lhs, const StrBlobPtr & rhs)
{
	auto l = lhs.wptr.lock(), r = rhs.wptr.lock();  
	if (l == r)
		return (!r || lhs.curr == rhs.curr);
	else
		return false;
}

bool operator != (StrBlobPtr &lhs, StrBlobPtr &rhs)
{
	return !eq(lhs, rhs);
}


void testPtr_weak()
{
	{
		std::shared_ptr<std::string> sp(new std::string("hello, world!")); // 引用计数 1

		//std::weak_ptr<std::string> wp(sp);  // wp也指向sp对象， 但不会增加引用计数， 仍为1 
		std::weak_ptr<std::string> wp = sp;   // 同上

		std::weak_ptr<std::string> wp2 = wp;   
	}

	{
		std::shared_ptr<std::string> sp = std::make_shared<std::string>("hello, world!"); // 引用计数 1	
		std::weak_ptr<std::string> wp(sp);
		wp.reset();   // wp置为空， 不会对sp有任何影响， 引用计数不变换，仍为1
	}

	{
		std::shared_ptr<std::string> sp = std::make_shared<std::string>("hello, world!"); // 引用计数 1	
		std::weak_ptr<std::string> wp(sp);

		sp.reset();   // sp置为空， 引用计数为0，释放对象。  wp指向是已经释放的内存，不能直接访问

		std::cout << wp.use_count() << std::endl; // 0
		std::cout << wp.expired() << std::endl; // true <=  use_count=0

		std::shared_ptr<std::string> p = wp.lock();  // 为空指针

	}

	{  //weak_ptr是弱引用，指向对象可能不存在，不能直接访问对象
		std::shared_ptr<std::string> sp1 = std::make_shared<std::string>("hello, world!");

		std::weak_ptr<std::string> wp;
		std::cout << wp.use_count() << std::endl; // 0
		std::cout << wp.expired() << std::endl; // true <=  use_count=0

		wp = sp1;
		std::cout << wp.use_count() << std::endl; // 1
		std::cout << wp.expired() << std::endl; // false <=  use_count!=0

		std::shared_ptr<std::string> sp2(sp1);
		std::cout << wp.use_count() << std::endl; // 2
		std::cout << wp.expired() << std::endl; // false <=  use_count!=0

		sp2.reset(); // sp2置空， 但不影响sp1
		sp1.reset();

		// 通过 lock()， 若wp对象存在，返回一个共享对象的sp,否则返回一个空sp
		if (std::shared_ptr<std::string> p = wp.lock()) {
			std::cout << *p << std::endl;    // 引用计数为2
		}//作用于结束后引用计数减为1

	}





	// 利用 weak_ptr访问对象数据，不影响对象生命周期，同时防止操作对象已经不存在的情况
	{
		try {
			//// 配合 StrBlobPtr注释的函数代码使用
			//{
			//	StrBlob sb;
			//	sb.push_back("abc");
			//	{
			//		StrBlobPtr sbp(sb);
			//		std::cout << sbp.front() << std::endl;
			//		sbp.push_back("123");
			//	}
			//	std::cout << sb.back() << std::endl;
			//}

			{
				StrBlob sb;
				sb.push_back("abc");
				sb.push_back("123");

				for (auto it = sb.begin(); it != sb.end(); it++)
					cout << it.deref() << endl;


			}

		}
		catch (int e) {
			std::cout << "catch throw " << e << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		}
	}
}


void testNew_delete()
{
	{
		int* pi = new int;
		delete pi;
	}
	{
		int* pi = new int[3];
		//delete pi;   //对于基本数据结构，也能正确。
		delete[] pi;   // 应该正确使用数组的释放方法 delete[] obj
	}
	{
		int* pi = new int[3]{ 0,1,2 };  // 列表初始化
		delete[] pi;  

		std::string* ps = new string[2]{ "abc","123" };
		//delete ps;  // 报错
		delete[] ps;   
	}

	{
		int obj = 1024;
		int obj1 = 1, obj2 = 2, obj3 = 3;
		auto p1 = new auto(obj);
		//auto p2 = new auto{obj1,obj2,obj3};  //vs2015不能编译成功
	}

	{ 
		try {
			int* pi = new int[std::numeric_limits<long long>::max()];   // 内存不够，会报错， 需要手动捕获错误 

			std::cout << pi << std::endl;
		}
		catch (std::exception& e) {
			std::cout << e.what() << endl;
		}

		{
			int* pi = new(nothrow) int[std::numeric_limits<long long>::max()];  // 内存不够， 返回空指针 
			std::cout << pi << std::endl;
		}
	}

	{// 智能指针
		{
			std::unique_ptr<int[] > up(new int[4]{ 0,1,2,3 });
			auto pi = up.get();

			int arr1 = up[1];  //可以使用下标访问

			up.reset(); //释放内存，自动调用 delete[]
		}

		{
			std::shared_ptr<int> sp(new int[4]{ 0,1,2,3 }); 
			auto pi = sp.get();
			int arr1 = pi[1];//获取元素必须用内置指针进行数组元素访问

			sp.reset(); //c++11的shared_ptr不支持管理动态数组，还需要指定删除器；c++14正常；
		}
	}
}



void testAllocate()
{
	{
		std::allocator<std::string> strAlloc;  // 创建一个string的分配器
		std::string* p = strAlloc.allocate(10);  // 分配10个为初始化的string

		auto q = p;
		strAlloc.construct(q++);
		strAlloc.construct(q++, "123");
		strAlloc.construct(q++, 10, '1');   // 10个'1'组成的字符串

		//strAlloc.destroy(p+2);  // 执行对象"111111111"的析构，但是没有释放内存； 只能对已经构造的元素进行操作；
		while (q != p) {
			strAlloc.destroy(--q);  
		}

		strAlloc.deallocate(p, 10);  // 释放内存， n必须为ps创建时的大小
	}

	{//拷贝和填充未初始化内存的算法
		std::vector<int> vi{ 0,1,2,3,4,5,6,7,8,9 };  // 10个元素的vector

		std::allocator<int> alloc;
		auto p = alloc.allocate(vi.size() * 2);  //分配一个大小为20的未初始化的int内存

		auto q = std::uninitialized_copy(vi.begin(), vi.end(), p);  // vi初始化p, 返回最后指向（第11个未初始化int内存）
		std::uninitialized_fill_n(q, vi.size(), 11);      //剩下10个未初始化int内存的用11填充   //c4996 warning

		alloc.deallocate(p, vi.size()*2 );
	}
	

}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include <bitset>

void testBit()
{
    int x = std::pow(2,31) ;
    int y = 2 << 31;
    std::bitset<32> i(x);

    auto ii = std::bitset<32>(-x);


    std::cout << i << std::endl << ii << std::endl;

    {
        unsigned char i = 0x80;
        printf("0x%x\n", ~i >> 3 + 1);  // (~i) >> (3+1)   ~i 为 0xffffff7f
    }
}

void testUnion()
{
    union
    {
        int i;
        char x[2];
    }a;

    a.x[0] = 10;
    a.x[1] = 1;
    printf("%d", a.i);

    class A {
    public:
        int m;
        void print() { cout << "A\n"; }
    };
    A *pa = 0;
    pa->print();

}


void testPointer()
{
    char * aa = "123456";
    auto p = (aa + 2)[-2]; // ==> *p = (aa+2) - 2 

    char *c[] = {"ENTER","NEW","POINT","FIRST"};
    char **cp[] = {c + 3 , c + 2 , c + 1 , c};
    char ***cpp = cp;

    printf("%s", **++cpp);
    printf("%s", *--*++cpp + 3);
    printf("%s", *cpp[-2] + 3);
    printf("%s\n", cpp[-1][-1] + 1);
}



void testDummy()
{



    testPointer();

    testUnion();

    testBit();
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class ConcurrentQueue
{
public:

    T pop()
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        while(queue_.empty()) {
            std::cout << " queue empyt , wait for push..." << std::endl;
            cond_empty_.wait(mlock);
        }
        auto val = queue_.front();
        queue_.pop();
        mlock.unlock();
        cond_full_.notify_one();
        return val;
    }

    void pop(T& item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);

        //// 不要使用if
       //  这是因为wait()从阻塞到返回，不一定就是由于notify_one()函数造成的，还有可能由于系统的
       // 不确定原因唤醒（可能和条件变量的实现机制有关），这个的时机和频率都是不确定的，被称作
       // 伪唤醒，如果在错误的时候被唤醒了，执行后面的语句就会错误，所以需要再次判断队列是否为
       //  空，如果还是为空，就继续wait()阻塞。
        //while(queue_.empty()) {
        //    std::cout << " queue empyt , wait for push..." << std::endl;

        //    // 在wait()函数之前，使用互斥锁保护了，如果wait的时候什么都没做，岂不是一直持有互斥锁？
        //    // 那生产者也会一直卡住，不能够将数据放入队列中了。所以，wait()函数会先调用互斥锁的
        //    // unlock()函数，然后再将自己睡眠，在被唤醒后，又会继续持有锁，保护后面的队列操作。而
        //    // lock_guard没有lock和unlock接口，而unique_lock提供了。这就是必须使用unique_lock的原因。
        //    cond_empty_.wait(mlock);
        //}

        // 上面的一句可以修改为
        cond_empty_.wait(mlock, [] {
            std::cout << " queue empyt , wait for push..." << std::endl;
            return queue_.empty(); 
        });


        item = queue_.front();
        queue_.pop();
        mlock.unlock();
         
        // 使用细粒度锁，尽量减小锁的范围，在notify_one()的时候，不需要处于互斥锁的保护范围内，
        // 所以在唤醒条件变量之前可以将锁unlock()
        cond_full_.notify_one();
    }

    void push(const T& item)
    {
        std::unique_lock<std::mutex> mlock(mutex_);

        while(capacity_ > 0 && queue_.size() >= capacity_) {
            std::cout << " queue no set capacity or already full. " << std::endl;
            cond_full_.wait(mlock);
        }
        queue_.push(item);
        mlock.unlock();
        cond_empty_.notify_one();
    }

    void set_capacity(int capacity)
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        capacity_ = capacity;
    }

    bool empty()
    {
        std::unique_lock<std::mutex> mlock(mutex_);
        return queue_.empty();
    }

    ConcurrentQueue() = default;
    ConcurrentQueue(const ConcurrentQueue&) = delete;            // disable copying
    ConcurrentQueue& operator=(const ConcurrentQueue&) = delete; // disable assignment

private:
    std::queue<T> queue_;
    std::mutex mutex_;
    std::condition_variable cond_empty_;
    std::condition_variable cond_full_;
    // If capacity greater than one, the queue will block on push if there are too many elements in it
    int capacity_ = 0;
};



void testConcurrentQueue()
{
    ConcurrentQueue<int> q;
    q.set_capacity(10);

    int i = 0;

    std::thread  td1 ([&q] {
        while(1)
        {
            std::cout << "print pop() = " << q.pop() << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
        }
    });


    std::thread td2([&q, &i] {

        while(1) {
            q.push(i);
            std::cout << "print push() = " <<  i++ << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

    });


    td1.join();
    td2.join();

}


////////////////////////////////////////////////
#include<array>

void testThreadDetach()
{

   if(0) {
        std::thread td1([]
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            std::cout << "thread td1 done. " << std::endl;
        });

        std::thread td2([] {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << "thread td2 done. " << std::endl;
        });

        //{ // 无序， td2先执行
        //    td1.join();
        //    td2.join();     
        //}
        //
        //

        //{ // 无序， td2先执行
        //    if(td1.joinable())  td1.join();
        //    if(td2.joinable())  td2.join();
       // }
 

       //不会阻塞， td1.join()不会等待td1退出再进行td2.join())

    }


    if(1){

        std::atomic_bool isDone = false;
        std::thread td1([&] {
            while(!isDone) {
                std::cout << "running... " << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }

            std::cout << "thread td1 done. " << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        });


        /*  方案1   使用detach    */
        {
            //  td1.detach();


            std::this_thread::sleep_for(std::chrono::seconds(10));
            isDone = true;

            // detach后不能join, 导致子线程晚于主线程结束 (若子线程访问主线程资源，导致出问题)
            // 若使用detach， 那么线程什么时候退出不可控， 这里只能使用延时等待线程退出
            //if(td1.joinable()) {
            //    td1.join();    //detach 后 这里不会执行
            // }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }


        /*  方案2   不使用detach， 线程创建后会自动执行    */
        {
            std::this_thread::sleep_for(std::chrono::seconds(10));


            isDone = true;
            // ********  注意 这种方法仅适合退出线程，若线程间有依赖关系，必须使用条件变量解决先后退出关系
            // ********       或者每个/每组线程对应使用一个bool变量控制，按照顺序依次join    (另外，多个join函数，貌似无先后执行顺序，不会阻塞， td1.join()不会等待td1退出再进行td2.join())

            // 未使用 detach 或者 join, 线程是joinable的
            if(td1.joinable()) {
                printf("wait for thread done...");
                td1.join();   
            }
        }



 

    }


    return;


    // 使用RAII技术
    if(1) {

        class thread_guard
        {
            std::thread t;

        public:
            explicit thread_guard(std::thread&& t_) : t(std::move(t_))  { }

            ~thread_guard()
            {
                if(t.joinable()) {
                    t.join();
                }
               

                std::cout << "thread td1 done. " << std::endl;
            }

            // 拷贝构造和拷贝赋值
           thread_guard (const thread_guard &) = delete;
           thread_guard& operator=(const thread_guard &) = delete;
        };

        /*
        std::atomic_bool isDone = false;


        std::thread td1([&] {
            while(!isDone) {
                std::cout << "running... " << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
            std::cout << "exit while func... " << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        });
        thread_guard  g(td1);


        std::this_thread::sleep_for(std::chrono::seconds(10));
        isDone = true;
        std::cout << "main thread done " << std::endl;  
        */



        class MainThread
        {
        public:
            MainThread()
            {
                //std::thread td1([&] {
                //    while(!isDone) {
                //        std::cout << "running... " << std::endl;
                //        std::this_thread::sleep_for(std::chrono::seconds(1));
                //    }
                //    std::cout << "exit while func... " << std::endl;
                //    std::this_thread::sleep_for(std::chrono::seconds(3));
                //});
                //g = std::make_unique<thread_guard>( td1);

                g = std::make_unique<thread_guard>(
                    std::thread([&] {
                        while(!isDone) {
                            std::cout << "running... " << std::endl;
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                        }

                        std::this_thread::sleep_for(std::chrono::seconds(5));

                        x[4] = 1;
                        std::for_each(std::begin(x), std::end(x), [](auto i) { std::cout << i << " "; });

                        isDone = false;
                    })         
                );
            }

            ~MainThread()
            {
                isDone = true;

                std::this_thread::sleep_for(std::chrono::seconds(5));

                std::cout << "exit MainThread... " << std::endl;

               // std::for_each(std::begin(x), std::end(x), [](auto i) { std::cout << i << " "; });
                std::copy(x.begin(), x.end(), std::ostream_iterator<int>(std::cout, " "));
            }

        private:
            std::atomic_bool isDone = false;
            std::unique_ptr<thread_guard>  g;


            std::array<int,5> x{0,1,1,1,0};
        };


        MainThread d;
        std::this_thread::sleep_for(std::chrono::seconds(3));



    }

}


void testThreadPrint()
{
    /*
        你有很大的几率发现打印会出现类似于From t1: From main: 64这样奇怪的打印结果。
        cout是基于流的，会先将你要打印的内容放入缓冲区，可能刚刚一个线程刚刚放入From t1:，
        另一个线程就执行了，导致输出变乱。而c语言中的printf不会发生这个问题。
    */

    auto function_1 = []
    {
        for(int i = 0; i > -100; i--)
            //   cout << "From t1: " << i << endl;
            printf("From t1: %d\n", i);
    };


    std::thread t1(function_1);

    for(int i = 0; i < 100; i++)
         //cout << "From main: " << i << endl;
         printf("From main: %d\n", i);

     t1.join();

}

void testThreadYield()
{
    std::mutex mtx;
    std::condition_variable cv;

    int cargo = 0;
    auto shipment_available = [&] { return cargo != 0; };


    auto consume = [&](int n)
    {
        for(int i = 0; i < n; ++i) {
            std::unique_lock<std::mutex> lck(mtx);
            cv.wait(lck, shipment_available);
            // consume:
            std::cout << cargo << '\n';
            cargo = 0;
        }
    };

    std::thread consumer_thread(consume, 10);

    for(int i = 0; i < 10; ++i) {
        while(shipment_available()) 
           std::this_thread::yield();

        std::unique_lock<std::mutex> lck(mtx);
        cargo = i + 1;
        cv.notify_one();
    }

    consumer_thread.join();
    
}


void testCV_1()
{
    std::condition_variable cv;
    std::mutex cv_m; // This mutex is used for three purposes:
                     // 1) to synchronize accesses to i
                     // 2) to synchronize accesses to std::cerr
                     // 3) for the condition variable cv

    int i = 0;

    auto waits = [&](int idx)
    {
        std::unique_lock<std::mutex> lk(cv_m);
        std::cerr <<  idx <<" Waiting...\n";
        cv.wait(lk, [&] { return i == 1; });

        std::cerr << idx << " ...finished waiting. i == 1\n";
    };

    auto signals = [&]
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lk(cv_m);
            std::cerr << "Notifying...\n";
        }
        cv.notify_all();  // 但是不会执行线程，因为i都不为1

        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lk(cv_m);
            i = 1;
            std::cerr << "Notifying again...\n";
        }
       // cv.notify_all();

        cv.notify_one();

        std::this_thread::sleep_for(std::chrono::seconds(1));
        cv.notify_all();
    };

    std::thread t1(waits, 1), t2(waits,2), t3(waits,3), t4(signals);
    t1.join();
    t2.join();
    t3.join();
    t4.join();

}


void testThreadWaitfor_1()
{
    std::condition_variable cv;

    int value = -1;

    auto read_value = [&](int& value)
    {
        std::cin >> value;
        cv.notify_one();
    };

    std::cout << "Please, enter an integer (I'll be printing dots): \n";
    std::thread th(read_value, std::ref(value));  // 线程默认是值传参

    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);
    while(cv.wait_for(lck, std::chrono::seconds(2)) == std::cv_status::timeout) {
        std::cout << '.' << std::endl;
    }

    std::cout << "You entered: " << value << '\n';

    th.join();
}

[[ deprecared ]]
void testThreadWaitfor_2()
{
    std::condition_variable cv;
    std::mutex cv_m;
    int i;

    auto waits = [&](int idx)
    {
        std::unique_lock<std::mutex> lk(cv_m);
        if(cv.wait_for(lk, idx*std::chrono::milliseconds(100), [&] {return i == 1; }))
            std::cerr << "Thread " << idx << " finished waiting. i == " << i << '\n';
        else
            std::cerr << "Thread " << idx << " timed out. i == " << i << '\n';
    };


    auto signals = [&]
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
        std::cerr << "Notifying...\n";
        cv.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        {
            std::lock_guard<std::mutex> lk(cv_m);
            i = 1;
        }
        std::cerr << "Notifying again...\n";
        cv.notify_all();
    };


    std::thread t1(waits, 1), t2(waits, 2), t3(waits, 3), t4(signals);


    t1.join(); t2.join(), t3.join(), t4.join();

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//    模板

//类型别名模板

template<typename T, typename U>
class MagicType {
public:
    T dark;
    U magic;
};


typedef MagicType<std::string, std::string> TrueMagicType;
//using TrueMagicType = MagicType<std::string, std::string>;

// 错误   typedef不能用于模板定义， using可以
//template<typename T>
//typedef MagicType<std::vector<T>, std::string> TrueDarkMagicType ;

template<typename T>
using TrueDarkMagicType = MagicType<std::vector<T>, std::string>;

template<typename T, typename U>
//template<typename T = int, typename U = int> // c++14不需要这么做
auto add(T x, U y) -> decltype(x + y)
{
    return x + y;
}

// 模板类 Magic 的对象，能够接受不受限制个数的 typename 作为模板的形式参数
//template<typename... Ts> class Magic;

//class Magic<> nothing; // 零参数

//class Magic<int, std::vector<int>, std::map<std::string, std::vector<int>> > darkMagic;

template<typename Require, typename... Args> class Magic; // 至少一个参数的类模板


template<typename... Ts>
void magic(Ts... args) 
{ 
    std::cout << sizeof...(args) << std::endl; // 变长模板参数个数 sizeof...(args)

}  

// 参数解包1,  使用递归的至少一个参数的变长类模板
template<typename T>
void printf1(T value)
{
    std::cout << value << std::endl;
}
template<typename T, typename... Ts>
void printf1(T value, Ts... args)     // 模板至少要一个参数 value
{
    std::cout << value << std::endl;
    // 当 sizeof...(args)为1时，调用的是printf1(T value)
    // 其他情况，递归调用 printf1(T value, Ts... args)
    printf1(args...);  
}

//// 参数解包2,  C++17 中增加了变参模板展开的支持
//template<typename T0, typename... T>
//void printf2(T0 t0, T... t)
//{
//    std::cout << t0 << std::endl;
//    if (sizeof...(t) > 0) printf2(t...);  
//}


// 参数解包3,  利用初始化列表展开
template<typename T, typename... Ts>
auto printf3(T value, Ts... args)
{
   // std::cout << value << std::endl;

    std::initializer_list<T>
    {
        ([&args] { std::cout << args << std::endl;} (), value)...
    };
}

void testTemplate()
{
    TrueMagicType a;
    TrueDarkMagicType<int> b;
    add(3, 4);


    magic(1);
    magic(2, 'a', "aaaa");


    printf1(1, 2.1, 'a', "aaa");
    printf3(1, 2.1, 'a', "aaa");
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// functional and lambda
#include <functional>


void reference(int& v)
{
    std::cout << "左值" << std::endl;
}
void reference(int&& v)
{
    std::cout << "右值" << std::endl;
}
template <typename T>
void pass1(T&& v)
{
    std::cout << "普通传参:";
    reference(v); // 始终调用 reference(int&)   对于reference函数来说，传递的（T&& v）永远是一个引用。
}

template <typename T>
void pass2(T&& v)
{
    std::cout << "             普通传参: ";
    reference(v);
    std::cout << "       std::move 传参: ";
    reference(std::move(v));
    std::cout << "    std::forward 传参: ";
    reference(std::forward<T>(v));
    std::cout << "static_cast<T&&> 传参: ";
    reference(static_cast<T&&>(v));
}

int foo(int para)
{
    return para;
}

void testRuntime()
{
    { //  Lambda表达式 和  std::function

        std::function<int(int)> func = foo;

        // 如果需要递归调用lambda,必须使用 std::function进行关联到lambda体
        int important = 10;
        std::function<int(int)> func2 = [&](int value) -> int {
            return 1 + value + important;
        };

        func2(2);
    }

    { // std::bind 和 std::placeholder

        auto foo = [](int a, int b, int c) { } ;

      // 将参数1,2绑定到函数 foo 上，但是使用 std::placeholders::_1 来对第一个参数进行占位
        auto bindFoo = std::bind(foo, std::placeholders::_1, 1, 2);
       
        // 这时调用 bindFoo 时，只需要提供第一个参数即可
        bindFoo(1);
    }


    // 
    // 左值、右值的纯右值、将亡值、右值
    // 
    /*
         左值(lvalue, left value)，顾名思义就是赋值符号左边的值。准确来说， 左值是表达式（不一定是
        赋值表达式）后依然存在的持久对象。

            右值(rvalue, right value)，右边的值，是指表达式结束后就不再存在的临时对象。 而 C++11 中为了
        引入强大的右值引用，将右值的概念进行了进一步的划分，分为：纯右值、将亡值。

                纯右值(prvalue, pure rvalue)，纯粹的右值，要么是纯粹的字面量，例如 10, true； 要么是求值结
            果相当于字面量或匿名临时对象，例如 1+2。非引用返回的临时变量、运算表达式产生的临时变量、 原
            始字面量、Lambda 表达式都属于纯右值。

                将亡值(xvalue, expiring value)，是 C++11 为了引入右值引用而提出的概念（因此在传统 C++中，
            纯右值和右值是同一个概念），也就是即将被销毁、却能够被移动的值。
    */
    {
        {
            auto foo = []() {
                std::vector<int> temp = {1, 2, 3, 4};
                // 在之前，返回临时变量temp, 会进行赋值给左值v, 之后再销毁temp。
                // 
                // 在 C++11 之后，编译器为我们做了一些工作，此处的左值 temp 会被进行此隐式右值转换， 
                // 等价于 static_cast<std::vector<int> &&>(temp)，进而此处的 v 会将 foo 局部返回的值进行移动
                // 因此在c++11中不要画蛇添足手动对临时变量返回用std::move
                return temp;
            };

            std::vector<int> v = foo();
        }
        {

            std::string lv1 = "string,"; // lv1 是一个左值
                                         // std::string&& r1 = lv1; // 非法, 右值引用不能引用左值
            std::string&& rv1 = std::move(lv1); // 合法, std::move可以将左值转移为右值
            std::cout << rv1 << std::endl; // string,

            const std::string& lv2 = lv1 + lv1; // 合法, 常量左值引用能够延长临时变量的生命周期
            // lv2 += "Test"; // 非法, 常量引用无法被修改
            std::cout << lv2 << std::endl; // string,string

            std::string&& rv2 = lv1 + lv2; // 合法, 右值引用延长临时对象生命周期
            rv2 += "Test"; // 合法, 非常量引用能够修改临时变量
            std::cout << rv2 << std::endl; // string,string,string,Test


            // rv2 虽然引用了一个右值，但由于它是一个引用，所以 rv2 依然是一个左值。
        }

        {
            class A {
            public:
                int *pointer;

                A() :pointer(new int(1))
                {
                    std::cout << "构造" << pointer << std::endl;
                }

                A(A& a) :pointer(new int(*a.pointer))
                {
                    std::cout << "拷贝" << pointer << std::endl;
                } // 无意义的对象拷贝

                A(A&& a) :pointer(a.pointer)
                {
                    a.pointer = nullptr;
                    std::cout << "移动" << pointer << std::endl;
                }

                ~A()
                {
                    std::cout << "析构" << pointer << std::endl;
                    delete pointer;
                }
            };

            // 防止编译器优化
            std::function<A(bool)> return_rvalue = [](bool test)
            {
                A a, b;
                if(test) return a; // 等价于 static_cast<A&&>(a);
                else return b;     // 等价于 static_cast<A&&>(b);
            };

            // 先构造临时对象a,b;  将b移动构造obj: 析构a,b;
            A obj = return_rvalue(false); 

            std::cout << "obj:" << std::endl;
            std::cout << obj.pointer << std::endl;
            std::cout << *obj.pointer << std::endl;

        }

        // 右值引用
        {
            std::string str = "Hello world.";
            std::vector<std::string> v;

            // 将使用 push_back(const T&), 即产生拷贝行为
            v.push_back(str);
            // 将输出 "str: Hello world."
            std::cout << "str: " << str << std::endl;

            // 将使用 push_back(const T&&), 不会出现拷贝行为
            // 而整个字符串会被移动到 vector 中，所以有时候 std::move 会用来减少拷贝出现的开销
            // 这步操作后, str 中的值会变为空
            v.push_back(std::move(str));
            // 将输出 "str: "
            std::cout << "str: " << str << std::endl;
        }


        // 完美转发
        {
            // 一个声明的右值引用其实是一个左值。这就为我们进行参数转发（传递）造成了问题：
            {
                std::cout << "传递右值:" << std::endl;
                pass1(1); // 1是右值, 但输出是左值

                std::cout << "传递左值:" << std::endl;
                int l = 1;
                pass1(l); // l 是左值, 输出左值
            }

            {
               /*
                对于 pass(1) 来说，虽然传递的是右值，但由于 v 是一个引用，所以同时也是左值。 因
                此 reference(v) 会调用 reference(int&)，输出『左值』。 而对于pass(l)而言，l是一
                个左值，为什么会成功传递给 pass(T&&) 呢？

                 这是基于引用坍缩规则的：在传统 C++ 中，我们不能够对一个引用类型继续进行引用， 
                 但 C++ 由于右值引用的出现而放宽了这一做法，从而产生了引用坍缩规则，允许我们对
                 引用进行引用， 既能左引用，又能右引用。但是却遵循如下规则：

                    函数形参类型	实参参数类型	推导后函数形参类型
                        T&	            左引用	        T&
                        T&	            右引用	        T&
                        T&&	            左引用	        T&
                        T&&	            右引用	        T&&

                  因此，模板函数中使用 T&& 不一定能进行右值引用，当传入左值时，此函数的引用将被推导为
                  左值。 更准确的讲，无论模板参数是什么类型的引用，当且仅当实参类型为右引用时，模板参
                  数才能被推导为右引用类型。 这才使得 v 作为左值的成功传递。

                   完美转发就是基于上述规律产生的。所谓完美转发，就是为了让我们在传递参数的时候， 保持
                   原来的参数类型（左引用保持左引用，右引用保持右引用）。 为了解决这个问题，我们应该使
                   用 std::forward 来进行参数的转发（传递）
               */
                //template <typename T>
                //void pass2(T&& v)
                //{
                //    std::cout << "              普通传参: ";
                //    reference(v);
                //    std::cout << "       std::move 传参: ";
                //    reference(std::move(v));
                //    std::cout << "    std::forward 传参: ";
                //    reference(std::forward<T>(v));
                //    std::cout << "static_cast<T&&> 传参: ";
                //    reference(std::forward<T>(v));
                //}


                std::cout << "传递右值:" << std::endl;
                pass2(1);
                //                传递右值:
                //             普通传参: 左值
                //       std::move 传参: 右值
                //    std::forward 传参: 右值
                //static_cast<T&&> 传参: 右值

                std::cout << "传递左值:" << std::endl;
                int v = 1;
                pass2(v);
                //传递左值:
                //             普通传参: 左值
                //       std::move 传参: 右值
                //    std::forward 传参: 左值
                //static_cast<T&&> 传参: 左值



                /*
                    无论传递参数为左值还是右值，普通传参都会将参数作为左值进行转发， 所以 std::move 总会接受到
                    一个左值，从而转发调用了reference(int&&) 输出右值引用。

                    唯独 std::forward 即没有造成任何多余的拷贝，同时完美转发(传递)了函数的实参给了内部调用的其他函数。

                    std::forward 和 std::move 一样，没有做任何事情，std::move 单纯的将左值转化为右值， std::forward 
                    也只是单纯的将参数做了一个类型的转换，从现象上来看， std::forward<T>(v) 和 static_cast<T&&>(v) 是完全一样的。
                */

                
               // int&& x = 1;
                const int& x = 1;  // // 合法, 常量左引用允许引用右值

                bool ret;
                ret = std::is_lvalue_reference<decltype( x )>::value;
                ret = std::is_lvalue_reference<decltype( (int& ) x )>::value;
                ret = std::is_lvalue_reference<decltype( (int&&) x )>::value;
                ret = std::is_lvalue_reference<decltype( std::move(x) )>::value;

                ret = std::is_rvalue_reference<decltype(x)>::value;
                ret = std::is_rvalue_reference<decltype((int&)x)>::value;
                ret = std::is_rvalue_reference<decltype((int&&)x)>::value;
                ret = std::is_rvalue_reference<decltype(std::move(x))>::value;
            }

        }
    }
}

//////////////////////////////////////////////////////////////////////////
//  tuple

void testTuple()
{
    {
        auto get_student = [](int id)
        {
            // 返回类型被推断为 std::tuple<double, char, std::string>

            if(id == 0)
                return std::make_tuple(3.8, 'A', "张三");
            if(id == 1)
                return std::make_tuple(2.9, 'C', "李四");
            if(id == 2)
                return std::make_tuple(1.7, 'D', "王五");
            return std::make_tuple(0.0, 'D', "null");
            // 如果只写 0 会出现推断错误, 编译失败
        };

        /////// 基本操作

        // c++11
        auto student = get_student(0);
        std::cout << "ID: 0, "
            << "GPA: " << std::get<0>(student) << ", "
            << "成绩: " << std::get<1>(student) << ", "
            << "姓名: " << std::get<2>(student) << '\n';

        double gpa;
        char grade;
        std::string name;

        // 元组进行拆包
        std::tie(gpa, grade, name) = get_student(1);
        std::cout << "ID: 1, "
            << "GPA: " << gpa << ", "
            << "成绩: " << grade << ", "
            << "姓名: " << name << '\n';

        //c++14 
        std::tuple<std::string, double, double, int> t("123", 4.5, 6.7, 8);
        std::cout << std::get<std::string>(t) << std::endl;
       // std::cout << std::get<double>(t) << std::endl; // 非法, 引发编译期错误;两个double,不明确
        std::cout << std::get<2>(t) << std::endl;
        std::cout << std::get<3>(t) << std::endl;


        // C++17
        // auto [x,y,z] = get_student(2);




        /////// 合并 与 遍历
        auto new_tuple = std::tuple_cat(get_student(1), std::move(t));


        for(int i = 0; i < sizeof(new_tuple); i++) {
            //std::cout << new_tuple.get<i>(new_tuple) << std::endl;
            // get<>需要常数，遍历需要c++17的variant支持
        }
    }

}

//////////////////////////////////////////////////////////////////////////
// 类模板

template<typename T>
class ThreadSafeQueue final
{
public:
    using value_type = T;
    //typedef typename std::queue<T>::size_type size_type;
    using size_type = typename std::queue<T>::size_type; 

  
   // explicit ThreadSafeQueue(typename /* 必须使用typename*/ std::queue<T>::size_type queueSizeMax 
   //              = std::numeric_limits<typename /* 必须使用typename*/ std::queue<T>::size_type>::max()):
   //   queueSizeMax_(queueSizeMax) { }  

   explicit ThreadSafeQueue(size_type queueSizeMax = std::numeric_limits<size_type>::max()):
        queueSizeMax_(queueSizeMax) { }  


   ThreadSafeQueue(const ThreadSafeQueue& src) = delete;
   ThreadSafeQueue& operator=(const ThreadSafeQueue& rhs) = delete;

   enum TQueueResult
   {
       qrNoError = 0, // returned successfully.
       qrFull,        // currently full
       qrLocked       // currently locked
   };

   size_type  getMaxSize() const { return queueSizeMax_; }

   size_type getCurrentSize() const
   {
       std::lock_guard<std::mutex> scopeLock(mutex_);
       return queue_.size();
   }

   bool isFull() const
   {
       std::lock_guard<std::mutex> scopeLock(mutex_);
       return queue_.size() == queueSizeMax_;
   }

   bool isEmpty() const
   {
       std::lock_guard<std::mutex> scopeLock(mutex_);
       return queue_.empty();
   }

   // pData为空，仅判断是都为空，效果同bool isEmpty();
   // pData不为空， 取队列中的第一个元素
   bool front(T* pData = nullptr)
   {
       std::lock_guard<std::mutex> scopeLock(mutex_);
       const bool boResult = !queue_.empty();
       if(boResult && pData) { 
           *pData = queue_.front();
       }
       return boResult;
   }

   /// push
   TQueueResult push(const T& t)
   {
       std::lock_guard<std::mutex> scopeLock(mutex_);
       if(queue_.size() >= queueSizeMax_) {
           printf("queue full\n");
           return qrFull;
       }

       queue_.push(t);
       conditionVariable_.notify_one();
       printf("push %d \n", t);
       return qrNoError;
   }

   TQueueResult push(T&& t)
   {
       std::lock_guard<std::mutex> scopeLock(mutex_);
       if(queue_.size() >= queueSizeMax_) {
           printf("queue full\n");
           return qrFull;
       }

       queue_.emplace(t);
       conditionVariable_.notify_one();
       printf("push %d \n", t);
       return qrNoError;
   }

   // pop1
   bool pop(  T* pData = nullptr)
   {
       std::unique_lock<std::mutex> scopeLock(mutex_);
       printf("wait for date...\n");
       conditionVariable_.wait(scopeLock, [this]{ return !queue_.empty(); });
       printf("extractData...\n");
       return extractData(true, pData);
   }

   // pop2
   bool pop(unsigned int timeout_ms, T* pData = nullptr)
   {
       return pop(std::chrono::milliseconds(timeout_ms), pData);
   }

   // pop2 调用模板
   template<class Rep, class Period>
   bool pop(  const std::chrono::duration<Rep, Period>& rel_time, T* pData = nullptr)
   {
       std::unique_lock<std::mutex> scopeLock(mutex_);
       return extractData(
           conditionVariable_.wait_for(scopeLock, rel_time, [this] {  return !queue_.empty(); }),
           pData
       );
   }


private:
    bool extractData(const bool boWaitResult, T* pData)
    {
        if(boWaitResult) {
            if(!queue_.empty()) 
            {
                if(pData)  *pData = std::move(queue_.front());
            }
            queue_.pop();
            return true;
        }
        return false;
    }



    std::queue<T> queue_;
   // typename /* 必须使用typename*/ std::queue<T>::size_type queueSizeMax_;
    size_type queueSizeMax_;

    std::mutex mutex_;
    std::condition_variable conditionVariable_;
};


void testThreadQueue()
{
    ThreadSafeQueue<int> tsq(10);

   std::atomic<bool> bExit = false;


   using namespace  std::chrono_literals;
   std::thread peoducer([&] {
       int i = 0;
       while (!bExit)
       {
          std::this_thread::sleep_for(3000ms);
          if( tsq.push(++i) != 0 )
              --i; // push 失败
       }
   });

   std::thread consumer([&] {

       int i;
       while(!bExit) {

          // std::this_thread::sleep_for(1200ms);
          // bool popRet = tsq.pop(&i);

          // bool popRet = tsq.pop(1200 ,&i);
           bool popRet = tsq.pop(3100, &i);

           if(popRet)
               printf("pop %d \n", i);
           else 
               printf("queue empty\n");
       }
   });


   std::this_thread::sleep_for(30s);
   bExit = true;
   peoducer.join();
   consumer.join();

}


/////// for_each
void testForEach()
{
   if(0) {
        std::vector<int> arr{0,1,2,3,4,5,6,7,8,9};

        for(auto i : arr) i++;
        for(auto i : arr) printf("%d ", i);
        std::cout << std::endl;

        for(auto& i : arr) i++;
        for(auto i : arr) printf("%d ", i);
        std::cout << std::endl;


        std::for_each(arr.begin(), arr.end(), [](auto i) {printf("%d ", i); });
        std::cout << std::endl;

        // 必须知道类型
        std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(cout, " "));
        std::cout << std::endl;
    }
}


//////////////////////////////////////////////////////////////////////////
// 可变长模板测试
#include "templat_test.h"
void test_template()
{
   // template_init();


    //constexpr int len = Sum<int, double, short>::value;
    //std::cout << len << std::endl;

    //using T = MakeIndexes<3>::type;
    //std::cout << typeid(T).name() << std::endl;

    //using T2 = MakeIndexes3<5>::type;
    //std::cout << typeid(T2).name() << std::endl;


   // AAAA::test();
   // AAAA::test_2();


   // test_delegate();

    //test_template_match();


    //debug_arg(3, 1,2,3);

    //{ 
    //    int i = sizeof(int);
    //    debug_arg(3, 5, 6, 7);
    //}

    //foo(1, 2, 3, 4, 5);
    //foo('c', 2.1, "123");


  //  print(std::cerr, 'c', 2.3, "abc");

   // errorMsg(std::cerr, 'c', 2.3, "abc");


    //int i = 1;
    //const int p = i;
    ////printTypes(1, i, p, 2.3, "1234");
    //printTypes(1, i, p, 2.3);


    test_template_compare();


    XXX::Foo<double> f; f.Bar();
    XXX::Foo<int> x; x.Bar();
}


//////////////////////////////////////////////////////////////////////////
// pointer to classs member

void test_poninter_to_member()
{
    class CLS
    {
    public:
        std::string str ="mem";

        std::string CLS::*pst;  



        char func1(int i, float f) const { return i & 0xff; }


    };

    string *ps1;        // 普通指针，ps1指向std::string
    string CLS::*ps2;   // ps2指向CLS类的string成员

    ps1 = new string("");

    CLS cls, *pcls = &cls;

    //ps2 = ps1;
    ps2 = cls.pst;

    
   // auto s = cls.*ps2;
   //  s = pcls->*ps2;

    ////////////////////////////////////

    // 指向 CLS的 成员函数， 参数是列表是(int,float),返回值是char 
 
    auto pmf = &CLS::func1;


    char c1 = (cls.*pmf)(1, 3);

    char c2 = (pcls->*pmf)(1,3);
}


////////////////////////////////////////// 
// bit-filed;
// 通常设置使用 unsigned int
struct RTP_HEADER
{
#if defined _WIN32
    unsigned int cc : 4;        // CSRC count
    unsigned int x : 1;         // header extension flag
    unsigned int p : 1;         // padding flag
    unsigned int v : 2;         // protocol version
    unsigned int pt : 7;        // payload type
    unsigned int m : 1;         // marker bit
#else
    unsigned int v : 2;         // protocol version
    unsigned int p : 1;         // padding flag
    unsigned int x : 1;         // header extension flag
    unsigned int cc : 4;        // CSRC count
    unsigned int m : 1;         // marker bit
    unsigned int pt : 7;        // payload type
#endif
};

void testBitField()
{

    int* pi = new int(0xffffffff);

    unsigned int* pui = (unsigned int *)pi;
    *pui = 0xffeeddcc;

    unsigned short* pus = (unsigned short *)pi;
    *pus = 0xbbaa;

    unsigned char* puc = (unsigned char *)pi;
    *puc = 0x09;

    *pus = 0xbbaa;
    
    struct RTP_HEADER rtp_h;
    memset(&rtp_h, 0, 1);
    memcpy(&rtp_h, pus, 1);
    memcpy(&rtp_h, pus, 2);
    rtp_h.v = 1;
    rtp_h.m = 1;
    

    struct RTP_HEADER rtp_h2;
    memset(&rtp_h, 0xcccc, 1);
    

}



//////////////////////////////////////////////////////////////////////////
///   测试练习
#include "exercise.hpp"
void testExercise()
{
    MonkeyPeach::Test();
}


//#include "pipe_guid.h"
//void test_PipeGuid()
//{
//    test_pipe_guid();
//}


#include "MyThreadPool.h"
int test_ThreadPool()
{
    using PoolSeconds = MyThreadPool::PoolSeconds;
    using ThreadPoolConfig = MyThreadPool::ThreadPoolConfig;


    MyThreadPool pool(ThreadPoolConfig{4, 5, 6, PoolSeconds(4)});
    pool.Start();
    std::this_thread::sleep_for(std::chrono::seconds(4));
    cout << "thread size " << pool.GetTotalThreadSize() << endl;
    std::atomic<int> index;
    index.store(0);
    std::thread t([&]() {
        for(int i = 0; i < 10; ++i) {
            pool.Run([&]() {
                cout << "function " << index.load() << endl;
                std::this_thread::sleep_for(std::chrono::seconds(4));
                index++;
            });
            // std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });
    t.detach();
    cout << "=================" << endl;
    return 0;

    std::this_thread::sleep_for(std::chrono::seconds(4));

    pool.Reset(ThreadPoolConfig{4, 4, 6, PoolSeconds(4)});
    std::this_thread::sleep_for(std::chrono::seconds(4));
    cout << "thread size " << pool.GetTotalThreadSize() << endl;
    cout << "waiting size " << pool.GetWaitingThreadSize() << endl;
    cout << "---------------" << endl;
    pool.ShutDownNow();
    getchar();
    cout << "world" << endl;
    return 0;
}


#include <random>
#include <mutex>
#include <map>

int test_sequence()
{
    //std::mutex mtx;
    //std::condition_variable cv;

    std::atomic_bool done = false;

    using std::default_random_engine;

    float val;

    std::thread process([&] {

        enum class EventType { NONE, CLOSE, OPEN };

        class SeqenceData
        {
        public:
            EventType add(float val)
            {
                EventType type = push(val);

                if(EventType::NONE != type) {
                    std::cout << static_cast<int>(type);
                    func_map[type]();
                }

                return type;
            }

            void addFunc(EventType type, std::function<void()>&& func)
            {
                func_map.emplace(type, std::move(func));
            }

        private:

            float lastChangeVal = -1;
            bool  is_change = false;

            int steady_count = 0;
            int count_thresh = 2;

            EventType push(float val) {
                if(lastChangeVal < 0) {
                    lastChangeVal = val;
                    return EventType::NONE;
                }

                if(std::fabs(val - lastChangeVal) > 0.5) {  // 加一个变量，判断电平高<->低变换方向
                    if( !is_change)
                        steady_count++;
                }
                else {
                    if(is_change) is_change = false;
                    return EventType::NONE;
                }

                
                if(steady_count >= count_thresh) {
                    // 直接判断高低电平变换方向
                    auto type = (val - lastChangeVal > 0) ? EventType::OPEN : EventType::CLOSE;

                    is_change = true;
                    steady_count = 0;
                    lastChangeVal = val;
                    return type;
                }
                else {
                    return EventType::NONE;
                }
            }


            std::map<EventType, std::function<void()>> func_map;
        };


        SeqenceData seqData;
        auto funcCLOSED = [] {
            std::thread([] {
                std::cout << " ========== Call Closed Func" << std::endl;
            }).detach();
        };

        seqData.addFunc(EventType::CLOSE, std::move(funcCLOSED));  



        seqData.addFunc(EventType::OPEN, [] {
            std::thread([] {
                std::cout << " ========== Call OPEN Func" << std::endl;
            }).detach();
        });


        /// 模拟占空比序列
        float high = 11;
        float low = 9;

        default_random_engine e;
        normal_distribution<float> u(0.05, 0.1); //随机数分布对象

        int flip_cnt = 10;

        int cnt = flip_cnt;
        float tmpVal = high;

        while(!done) {

            if(--cnt == 0) {
                tmpVal = tmpVal == high ? low : high;
                cnt = flip_cnt;
            }
            val = tmpVal + u(e);
            std::cout << val << std::endl;


            // 放入序列判断器中
            seqData.add(val);

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        std::cout << " exit gen thread" << std::endl;
    });




    std::this_thread::sleep_for(std::chrono::seconds(100));

    done.store(true);
    if(process.joinable())     process.join();



    return 0;
}


int main()
{
    return test_sequence();

    return test_ThreadPool();      


  //  testBitField();

    test_poninter_to_member();

    test_template();


    //testOperatorPoint();


    {
        std::thread td([]() {
            std::cout << "aaaa";
        });

        td.join();

        std::this_thread::sleep_for(std::chrono::seconds(5));
        td.join();


        testThreadQueue();
    }


    testTuple();
    testRuntime();

    testTemplate();


    testExercise();

    {
        //testThreadWaitfor_2();

        //testThreadWaitfor_1();

        //testCV_1();


        //testThreadYield();


      //  testThreadPrint();

        testThreadDetach();

     //   testConcurrentQueue();
    }

    testDummy();


	mapTest();
	setTest();

	//stringTest();

	//main11();

	{
		testPtr_shared();
		testPtr_unique();
		testPtr_weak();

		testNew_delete();
		testAllocate();
	}
	return 0;


	cout << binarySearch({ -1, 4, 6, 8, 9, 10, }, 9) << endl;

	//cout << maxSubSum({ -2}) << endl;

// 	clock_t  t1 =  clock();
//     //int res = fib(40);
// 	int res = fib2(40);
// 	//fib(10,9,8);
// 	clock_t  t2 = clock();
// 	cout << "res = " << res << ", times = " << t2 - t1 << "ms, count = " << count_c << endl;


	//class MyClass
	//{
	//public:
	//	MyClass(int num) {};
	//};

	//// 编译器会将10转换成MyClass对象
	//MyClass obj = 10;  
	//// 这里的意思应该是调用 MyClass(int num) 


	//class MyClass
	//{
	//public:
	//	explicit MyClass(int num) {};
	//};
	//MyClass obj(10);


	system("pause");

	return 0;
}
