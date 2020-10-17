#pragma once

#include <iostream>
#include <tuple>

using namespace std;

class HttpRequest;
using HttpRequestPtr = std::shared_ptr<HttpRequest>;

class Json {
public:
    class Value { };
};

class HttpRequest {
public:
    static HttpRequestPtr newHttpJsonRequest(const Json::Value &)
    {
        return HttpRequestPtr{};
    }

    static HttpRequestPtr newHttpJsonRequest(Json::Value &&)
    {
        return HttpRequestPtr{};
    }
};

template <typename T>
HttpRequestPtr toRequest(T)
{
}


template <>
inline HttpRequestPtr toRequest(const Json::Value &pJson)
{
    return HttpRequest::newHttpJsonRequest(pJson);
}

template <>
inline HttpRequestPtr toRequest(Json::Value &&pJson)
{
    return HttpRequest::newHttpJsonRequest(std::move(pJson));
}

template <>
inline HttpRequestPtr toRequest(Json::Value &pJson)
{
    return toRequest((const Json::Value &)pJson);
}


//  ref  https://www.cnblogs.com/qicosmos/p/4325949.html

// 典型的定义    
//  template <class... T>    // 可变参数类型 T 也是可变的 
//  void f(T... args) {}

//// 简单可变模板函数
//  template <class... T>
//  void f(T... args)
//  {
//      cout << sizeof...(args) << endl; //打印变参的个数
//  }


//////////////////////////////////////////////////////////////////////////
// 包展开
//// m1: 递归
//void print()
//{
//    cout << "empty" << endl;
//}
////展开函数
//template <class T, class ...Args>
//void print(T head, Args... rest)
//{
//    cout << "parameter " << head << endl;
//    print(rest...);
//}

// 可变参数求和
template<typename T>
T sum(T t)
{
    return t;
}
template<typename T, typename ... Types>
T sum(T first, Types ... rest)
{
    return first + sum<T>(rest...);
}

// 逗号表达式展开参数包
template <class T>
void printarg(T t)
{
    cout << t << endl;
}

// 逗号表达式 d = (a = b, c);   
//  b会先赋值给a，接着括号中的逗号表达式返回c的值，因此d将等于c。
// {(printarg(args), 0)...}可理解为对args每个参数执行逗号表达式(arg_n,0)，并生成可变参数初始化 {...}
// {(printarg(args), 0)...}展开成((printarg(arg1),0), (printarg(arg2),0), (printarg(arg3),0),  etc... )
// 最终会创建一个元素值都为0的数组int arr[sizeof...(Args)]
template <class ...Args>
void expand(Args... args)
{
    int arr[] = {(printarg(args), 0)...};
}

template<class F, class... Args>void expand2(const F& f, Args&&... args)
{
    // 利用完美转发
    initializer_list<int>{(f(std::forward<Args>(args)), 0)...};
}


//////////////////////////////////////////////////////////////////////////
// tuple 是带可变参数的模板类
//template< class... Types >
//class tuple;



void template_init()
{
    // 初始化列表
    auto arr = initializer_list<int>{1,2,3,4,5};



    //// 简单可变模板函数
    //f();            //0
    //f(1, 2);        //2
    //f(1, 2.5, "");  //3

    //////////////////////////////////////////////////////////////////////////
    // 包展开
    // m1: 递归
   // print(1, 2, 3, 4);
    //// 调用过程
    ////    print(1, 2, 3, 4);
    ////    print(2, 3, 4);
    ////    print(3, 4);
    ////    print(4);
    ////    print();

    // 包展开
    // 可变参数求和
   // sum(1, 2, 3, 4); //10

    //逗号表达式展开参数包
    //expand(1, 2, 3, 4);

    expand2([](auto i) {cout << i << endl; }, 1, 2.5, "test");
}


//////////////////////////////////////////////////////////////////////////

// 定义了一个基本的可变参数模板类：
//    这个Sum类的作用是在编译期计算出参数包中参数类型的size之和，
//    通过sum<int,double,short>::value就可以获取这3个类型的size之和为14。

//// 前向声明     sum类是一个可变参数模板类
//template<typename... Args>
//struct Sum;
//
////基本定义     一个部分展开的可变模参数模板类，告诉编译器如何递归展开参数包
//template<typename First, typename... Rest>
//struct Sum<First, Rest...>
//{
//    enum { value = Sum<First>::value + Sum<Rest...>::value };
//};
//
////递归终止    特化的递归终止类
//template<typename Last>
//struct Sum<Last>
//{
//    enum { value = sizeof(Last) };
//};


//// 三段式改为2段氏
////    这个前向声明要求sum的模板参数至少有一个，因为可变参数模板中的模板参数可以有0个，
////    有时候0个模板参数没有意义，就可以通过这种声明方式来限定模板参数不能为0个。
//template<typename First, typename... Rest>
//struct Sum
//{
//    enum { value = Sum<First>::value + Sum<Rest...>::value };
//};
//
//template<typename Last>
//struct Sum<Last>
//{
//    enum { value = sizeof(Last) };
//};


//////////////////////////////////////////////////////////////////////////

// 使用std::integral_constant来消除枚举定义value。
// 利用std::integral_constant可以获得编译期常量的特性，可以将前面的sum例子改为这样：

//前向声明
template<typename First, typename... Args>
struct Sum;

//基本定义
template<typename First, typename... Rest>
struct Sum<First, Rest...> :
    std::integral_constant<int, Sum<First>::value + Sum<Rest...>::value>
{
};

//递归终止
template<typename Last>
struct Sum<Last> :
    std::integral_constant<int, sizeof(Last)>
{
};



//////////////////////////////////////////////////////////////////////////
// 继承方式展开包
//整型序列的定义
template<int...>
struct IndexSeq {};

//继承方式，开始展开参数包
template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...> {};

// 模板特化，终止展开参数包的条件
template<int... Indexes>
struct MakeIndexes<0, Indexes...>
{
    using type = IndexSeq<Indexes...>;
};

//using T = MakeIndexes<3>::type;
//
//  MakeIndexes<3>: MakeIndexes<2, 2>{}
//  MakeIndexes<2, 2>: MakeIndexes<1, 1, 2>{}
//  MakeIndexes<1, 1, 2>: MakeIndexes<0, 0, 1, 2>
//  {
//      typedef IndexSeq<0, 1, 2> type;
//  }


////  非继承方式  要求必须有一个参数
template<int N, int... Indexes>
struct MakeIndexes3
{
    using type = typename MakeIndexes3<N - 1, N - 1, Indexes...>::type;
};

template<int... Indexes>
struct MakeIndexes3<0, Indexes...>
{
    typedef IndexSeq<Indexes...> type;
};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// 3可变参数模版消除重复代码

template<typename T>
T* Instance()
{
    return new T();
}

template<typename T, typename T0>
T* Instance(T0 arg0)
{
    return new T(arg0);
}

template<typename T, typename T0, typename T1>
T* Instance(T0 arg0, T1 arg1)
{
    return new T(arg0, arg1);
}

template<typename T, typename T0, typename T1, typename T2>
T* Instance(T0 arg0, T1 arg1, T2 arg2)
{
    return new T(arg0, arg1, arg2);
}

template<typename T, typename T0, typename T1, typename T2, typename T3>
T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3)
{
    return new T(arg0, arg1, arg2, arg3);
}

template<typename T, typename T0, typename T1, typename T2, typename T3, typename T4>
T* Instance(T0 arg0, T1 arg1, T2 arg2, T3 arg3, T4 arg4)
{
    return new T(arg0, arg1, arg2, arg3, arg4);
}



// 这个泛型工厂函数存在大量的重复的模板定义，并且限定了模板参数。
// 用可变模板参数可以消除重复，同时去掉参数个数的限制，代码很简洁， 
//  通过可变参数模版优化后的工厂函数如下：

template<typename T, typename...  Args>
T* Instance_2(Args&&... args)
{
    return new T(std::forward<Args>(args)...);
};

class AAAA
{
public:
    struct A
    {
        A(int) {}
    };

    struct B
    {
        B(int, double) {}
    };

    // 加3个参数
    struct C
    {
        C(int, int, int) {}
    };

    // 任意
    template<typename T>
    struct D
    {
        template <typename ...Args>
        D(const std::initializer_list<T>& X = {Args...})
        {
            for(auto& i : X) std::cout << i << " ";
            std::cout << std::endl;
        }
    };


    static void test()
    {
        A* pa = Instance<A>(1);
        B* pb = Instance<B>(1, 2);

        C* pc = Instance<C>(1, 2, 3);


        auto pd = new D<int>{1, 2, 3, 4, 5, 6};
    }


    static void test_2()
    {
        A* pa = Instance_2<A>(1);
        B* pb = Instance_2<B>(1, 2);

        C* pc = Instance_2<C>(1, 2, 3);
    }
};



//////////////////////////////////////////////////////////////////////////
// 4、可变参数模版实现泛化的delegate

// MyDelegate实现的关键是内部定义了一个能接受任意类型和个数参数的
//  “万能函数”：R(T::*m_f)(Args…)，正是由于可变模版参数的特性，
//  所以我们才能够让这个m_f接受任意参数。

template <class CLS, class FUNC, typename... Args>
class  MyDelegate
{
public:
    MyDelegate(CLS* t, FUNC(CLS::*f)(Args...)) :m_cls(t), m_func(f)
    {
        // std::cout << typeid(t).name() << std::endl;
        // std::cout << typeid(f).name() << std::endl;
    }

    FUNC operator()(Args&&... args)
    {
        return (m_cls->*m_func)(std::forward<Args>(args) ...);
    }

private:
    CLS * m_cls;
    FUNC(CLS::*m_func)(Args...);
};

template <class CLS, class FUNC, typename... Args>
MyDelegate<CLS, FUNC, Args...> CreateDelegate(CLS* cls, FUNC(CLS::*func)(Args...))
{
    return MyDelegate<CLS, FUNC, Args...>(cls, func);
}

struct A_delegate
{
    // 函数类型   (void)func(int)
    void Fun1(int i) { cout << i << endl; }
    void Fun2(int i, double j) { cout << i + j << endl; }
};

void test_delegate()
{
    A_delegate a;
    auto d1 = CreateDelegate(&a, &A_delegate::Fun1);   //创建委托
    d1(1);                                             //调用委托，将输出1

    auto d2 = CreateDelegate(&a, &A_delegate::Fun2);  //创建委托
    d2(1, 2.5);                                       //调用委托，将输出3.5

}




//////////////////////////////////////////////////////////////////////////
// 其他
// 模板重载和匹配
#include <sstream>

template <typename T> std::string debug_str(const T& t)
{
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T> std::string debug_str(T* p)
{
    std::ostringstream ret;
    ret << "pointer " << p;
    if(p)
        ret << " " << debug_str(*p);
    else
        ret << " null point";
    return ret.str();
}



// 当 std::string debug_str(const std::string& s)在后面声明，则使用模板实现
std::string debug_str(char* p)
{
    return debug_str(std::string(p));
}

std::string debug_str(const char* p)
{
    return debug_str(std::string(p));
}

std::string debug_str(const std::string& s)
{
    return ("* " + s + " *");
}

void test_template_match()
{
    //// 函数模板会自动匹配类型
    //std::cout << debug_str(1) << std::endl;
    //std::cout << debug_str(std::string("string")) << std::endl;

    //// 添加 template <typename T> std::string debug_str(T* p)
    //std::string str = "str";
    //std::cout << debug_str(str) << std::endl;
    //std::cout << debug_str(&str) << std::endl;

    //const std::string* pstr = &str;
    //std::cout << debug_str(pstr) << std::endl;

    //// 添加 std::string debug_str(const std::string& s)
    //std::cout << debug_str(std::string("string")) << std::endl;
    //std::cout << debug_str("const char*") << std::endl;


    // 期望字符串按string处理
    char* p = "char *";
    std::cout << debug_str(p) << std::endl;
    std::cout << debug_str("const char*") << std::endl;
}


//////////////////////////////////////////////////////////////////////////
/// 可变参数
#include <stdarg.h>

void debug_arg(int num, ...)
{

    va_list ap;  //声明一个va_list变量
    va_start(ap, num);  //第二个参数表示形参的个数

    for(int i = 0; i < num; i++) {
        int tmp = va_arg(ap, int);   //第二个参数表示形参类型
        std::cout << tmp << std::endl;
    }

    va_end(ap);  //用于清理
}

template <typename... Args>
void foo(const Args& ... args)
{
    printf("%d\n", sizeof...(Args));
    printf("%d\n", sizeof...(args));
}

//template <typename T, typename... Args>
//void foo(const T& t, const Args& ... rest)
//{
//    printf("%d\n", sizeof...(Args));
//    printf("%d\n", sizeof...(rest));
//}


/// 包扩展  利用 debug_str 来打印
template<typename T>
std::ostream& print(std::ostream& os, const T& t)
{
    return os << t;
}

template<typename T, typename... Args>
std::ostream& print(std::ostream& os, const T& t, const Args... rest)
{
    os << t << ", ";
    return print(os, rest...);
}

template<typename... Args>
std::ostream& errorMsg(std::ostream& os, const Args... args)
{
    return print(os, debug_str(args)...);
    // 上面一句等价于
    //   debug_str(args) 是指 对args的每一个元素执行debug_str，
    //   生成一个可变参数供print调用, 等价于
    //   print(os,  debug_str(args_1, args_2, ..., args_n));
    //
    // 不能使用debug_str(args...)， 因为debug_str不支持可变参数（当前实例的个数）。
}

//////////////////////////////////////////////////////////////////////////
///  完美转发

template<typename T>
void work(T&& t)
{
    if(is_lvalue_reference<decltype(t)>::value) printf("l_ref");
    if(is_rvalue_reference<decltype(t)>::value) printf("r_ref");

    printf("\n");

}

//template<typename T, typename... Args>
//void work(T&& t, Args&& ... rest)
//{
//    work(std::forward<T>(t));
//    work(std::forward<Args>(rest)...);
//}

template<typename... Args>
void printTypes(Args&& ... args)
{
    // work(args...);
    // work(std::forward<Args>(args)...);   

     // 不递归展开  (work(args),0)... 对args每一个元素依次使用work处理
    auto tmp = {(work(std::forward<Args>(args)),0)...};
}


//////////////////////////////////////////////////////////////////////////
/// 模板特化

//第一个版本：  函数模板特化 比较两个变量
template<typename T> int compare(const T& lhs, const T& rhs)
{
    // 这里都进行 < 比较， 要求T重载<操作符
    if(lhs < rhs)  return -1;
    else if(rhs < lhs) return 1;
    else return 0;
}

//第二个版本： 比较字符串字面常量版本， 非特化
template<size_t M, size_t N>
int compare(const char(&lhs)[M], const char(&rhs)[N])
{
    return strcmp(lhs, rhs);
}

// 比较字符串字面常量的特化版本， 需要形式一致， |||第一个版本的特化|||
// 空<>说明这是一个特化版本
// 具有2个参数是 const 引用 类型
// 首先比较类型字符串字面常量， T是 const char *,   还要一个引用，且是常引用。
template<>
int compare(const char* const & lhs, const char*  const & rhs)
{
    return strcmp(lhs, rhs);
}


void test_template_compare()
{
    // 使用第一个版本
    compare(1, 3);
    compare(std::string("123"), std::string("1234"));

    // 使用第二个版本
    compare("mom", "hi");  // 

    const char * x = "mom";
    const char * y = "hi";
    // 实参是char数组类型,  需要特化版本
    // 否则是比较 指针大小
    compare(x, y);     //  不特化时，使用第一个版本； 

}


///////////// 类模板 偏特化成员
namespace XXX {

template <typename T> struct Foo {
    // 注意这里初始化默认参数要用T()构造
    Foo(const T& t = T()) : mem(t) {}
    void Bar() { printf("原始版本\n"); }

    T mem;
    // 其他成员函数
};

// 特化 Foo<int>的成员函数 Bar
template<>
void Foo<int>::Bar() { printf("特化版本\n"); }

};