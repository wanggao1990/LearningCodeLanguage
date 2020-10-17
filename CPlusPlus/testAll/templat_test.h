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

// ���͵Ķ���    
//  template <class... T>    // �ɱ�������� T Ҳ�ǿɱ�� 
//  void f(T... args) {}

//// �򵥿ɱ�ģ�庯��
//  template <class... T>
//  void f(T... args)
//  {
//      cout << sizeof...(args) << endl; //��ӡ��εĸ���
//  }


//////////////////////////////////////////////////////////////////////////
// ��չ��
//// m1: �ݹ�
//void print()
//{
//    cout << "empty" << endl;
//}
////չ������
//template <class T, class ...Args>
//void print(T head, Args... rest)
//{
//    cout << "parameter " << head << endl;
//    print(rest...);
//}

// �ɱ�������
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

// ���ű��ʽչ��������
template <class T>
void printarg(T t)
{
    cout << t << endl;
}

// ���ű��ʽ d = (a = b, c);   
//  b���ȸ�ֵ��a�����������еĶ��ű��ʽ����c��ֵ�����d������c��
// {(printarg(args), 0)...}�����Ϊ��argsÿ������ִ�ж��ű��ʽ(arg_n,0)�������ɿɱ������ʼ�� {...}
// {(printarg(args), 0)...}չ����((printarg(arg1),0), (printarg(arg2),0), (printarg(arg3),0),  etc... )
// ���ջᴴ��һ��Ԫ��ֵ��Ϊ0������int arr[sizeof...(Args)]
template <class ...Args>
void expand(Args... args)
{
    int arr[] = {(printarg(args), 0)...};
}

template<class F, class... Args>void expand2(const F& f, Args&&... args)
{
    // ��������ת��
    initializer_list<int>{(f(std::forward<Args>(args)), 0)...};
}


//////////////////////////////////////////////////////////////////////////
// tuple �Ǵ��ɱ������ģ����
//template< class... Types >
//class tuple;



void template_init()
{
    // ��ʼ���б�
    auto arr = initializer_list<int>{1,2,3,4,5};



    //// �򵥿ɱ�ģ�庯��
    //f();            //0
    //f(1, 2);        //2
    //f(1, 2.5, "");  //3

    //////////////////////////////////////////////////////////////////////////
    // ��չ��
    // m1: �ݹ�
   // print(1, 2, 3, 4);
    //// ���ù���
    ////    print(1, 2, 3, 4);
    ////    print(2, 3, 4);
    ////    print(3, 4);
    ////    print(4);
    ////    print();

    // ��չ��
    // �ɱ�������
   // sum(1, 2, 3, 4); //10

    //���ű��ʽչ��������
    //expand(1, 2, 3, 4);

    expand2([](auto i) {cout << i << endl; }, 1, 2.5, "test");
}


//////////////////////////////////////////////////////////////////////////

// ������һ�������Ŀɱ����ģ���ࣺ
//    ���Sum����������ڱ����ڼ�����������в������͵�size֮�ͣ�
//    ͨ��sum<int,double,short>::value�Ϳ��Ի�ȡ��3�����͵�size֮��Ϊ14��

//// ǰ������     sum����һ���ɱ����ģ����
//template<typename... Args>
//struct Sum;
//
////��������     һ������չ���Ŀɱ�ģ����ģ���࣬���߱�������εݹ�չ��������
//template<typename First, typename... Rest>
//struct Sum<First, Rest...>
//{
//    enum { value = Sum<First>::value + Sum<Rest...>::value };
//};
//
////�ݹ���ֹ    �ػ��ĵݹ���ֹ��
//template<typename Last>
//struct Sum<Last>
//{
//    enum { value = sizeof(Last) };
//};


//// ����ʽ��Ϊ2����
////    ���ǰ������Ҫ��sum��ģ�����������һ������Ϊ�ɱ����ģ���е�ģ�����������0����
////    ��ʱ��0��ģ�����û�����壬�Ϳ���ͨ������������ʽ���޶�ģ���������Ϊ0����
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

// ʹ��std::integral_constant������ö�ٶ���value��
// ����std::integral_constant���Ի�ñ����ڳ��������ԣ����Խ�ǰ���sum���Ӹ�Ϊ������

//ǰ������
template<typename First, typename... Args>
struct Sum;

//��������
template<typename First, typename... Rest>
struct Sum<First, Rest...> :
    std::integral_constant<int, Sum<First>::value + Sum<Rest...>::value>
{
};

//�ݹ���ֹ
template<typename Last>
struct Sum<Last> :
    std::integral_constant<int, sizeof(Last)>
{
};



//////////////////////////////////////////////////////////////////////////
// �̳з�ʽչ����
//�������еĶ���
template<int...>
struct IndexSeq {};

//�̳з�ʽ����ʼչ��������
template<int N, int... Indexes>
struct MakeIndexes : MakeIndexes<N - 1, N - 1, Indexes...> {};

// ģ���ػ�����ֹչ��������������
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


////  �Ǽ̳з�ʽ  Ҫ�������һ������
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

// 3�ɱ����ģ�������ظ�����

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



// ������͹����������ڴ������ظ���ģ�嶨�壬�����޶���ģ�������
// �ÿɱ�ģ��������������ظ���ͬʱȥ���������������ƣ�����ܼ�࣬ 
//  ͨ���ɱ����ģ���Ż���Ĺ����������£�

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

    // ��3������
    struct C
    {
        C(int, int, int) {}
    };

    // ����
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
// 4���ɱ����ģ��ʵ�ַ�����delegate

// MyDelegateʵ�ֵĹؼ����ڲ�������һ���ܽ����������ͺ͸���������
//  �����ܺ�������R(T::*m_f)(Args��)���������ڿɱ�ģ����������ԣ�
//  �������ǲ��ܹ������m_f�������������

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
    // ��������   (void)func(int)
    void Fun1(int i) { cout << i << endl; }
    void Fun2(int i, double j) { cout << i + j << endl; }
};

void test_delegate()
{
    A_delegate a;
    auto d1 = CreateDelegate(&a, &A_delegate::Fun1);   //����ί��
    d1(1);                                             //����ί�У������1

    auto d2 = CreateDelegate(&a, &A_delegate::Fun2);  //����ί��
    d2(1, 2.5);                                       //����ί�У������3.5

}




//////////////////////////////////////////////////////////////////////////
// ����
// ģ�����غ�ƥ��
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



// �� std::string debug_str(const std::string& s)�ں�����������ʹ��ģ��ʵ��
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
    //// ����ģ����Զ�ƥ������
    //std::cout << debug_str(1) << std::endl;
    //std::cout << debug_str(std::string("string")) << std::endl;

    //// ��� template <typename T> std::string debug_str(T* p)
    //std::string str = "str";
    //std::cout << debug_str(str) << std::endl;
    //std::cout << debug_str(&str) << std::endl;

    //const std::string* pstr = &str;
    //std::cout << debug_str(pstr) << std::endl;

    //// ��� std::string debug_str(const std::string& s)
    //std::cout << debug_str(std::string("string")) << std::endl;
    //std::cout << debug_str("const char*") << std::endl;


    // �����ַ�����string����
    char* p = "char *";
    std::cout << debug_str(p) << std::endl;
    std::cout << debug_str("const char*") << std::endl;
}


//////////////////////////////////////////////////////////////////////////
/// �ɱ����
#include <stdarg.h>

void debug_arg(int num, ...)
{

    va_list ap;  //����һ��va_list����
    va_start(ap, num);  //�ڶ���������ʾ�βεĸ���

    for(int i = 0; i < num; i++) {
        int tmp = va_arg(ap, int);   //�ڶ���������ʾ�β�����
        std::cout << tmp << std::endl;
    }

    va_end(ap);  //��������
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


/// ����չ  ���� debug_str ����ӡ
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
    // ����һ��ȼ���
    //   debug_str(args) ��ָ ��args��ÿһ��Ԫ��ִ��debug_str��
    //   ����һ���ɱ������print����, �ȼ���
    //   print(os,  debug_str(args_1, args_2, ..., args_n));
    //
    // ����ʹ��debug_str(args...)�� ��Ϊdebug_str��֧�ֿɱ��������ǰʵ���ĸ�������
}

//////////////////////////////////////////////////////////////////////////
///  ����ת��

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

     // ���ݹ�չ��  (work(args),0)... ��argsÿһ��Ԫ������ʹ��work����
    auto tmp = {(work(std::forward<Args>(args)),0)...};
}


//////////////////////////////////////////////////////////////////////////
/// ģ���ػ�

//��һ���汾��  ����ģ���ػ� �Ƚ���������
template<typename T> int compare(const T& lhs, const T& rhs)
{
    // ���ﶼ���� < �Ƚϣ� Ҫ��T����<������
    if(lhs < rhs)  return -1;
    else if(rhs < lhs) return 1;
    else return 0;
}

//�ڶ����汾�� �Ƚ��ַ������泣���汾�� ���ػ�
template<size_t M, size_t N>
int compare(const char(&lhs)[M], const char(&rhs)[N])
{
    return strcmp(lhs, rhs);
}

// �Ƚ��ַ������泣�����ػ��汾�� ��Ҫ��ʽһ�£� |||��һ���汾���ػ�|||
// ��<>˵������һ���ػ��汾
// ����2�������� const ���� ����
// ���ȱȽ������ַ������泣���� T�� const char *,   ��Ҫһ�����ã����ǳ����á�
template<>
int compare(const char* const & lhs, const char*  const & rhs)
{
    return strcmp(lhs, rhs);
}


void test_template_compare()
{
    // ʹ�õ�һ���汾
    compare(1, 3);
    compare(std::string("123"), std::string("1234"));

    // ʹ�õڶ����汾
    compare("mom", "hi");  // 

    const char * x = "mom";
    const char * y = "hi";
    // ʵ����char��������,  ��Ҫ�ػ��汾
    // �����ǱȽ� ָ���С
    compare(x, y);     //  ���ػ�ʱ��ʹ�õ�һ���汾�� 

}


///////////// ��ģ�� ƫ�ػ���Ա
namespace XXX {

template <typename T> struct Foo {
    // ע�������ʼ��Ĭ�ϲ���Ҫ��T()����
    Foo(const T& t = T()) : mem(t) {}
    void Bar() { printf("ԭʼ�汾\n"); }

    T mem;
    // ������Ա����
};

// �ػ� Foo<int>�ĳ�Ա���� Bar
template<>
void Foo<int>::Bar() { printf("�ػ��汾\n"); }

};