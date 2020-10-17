#include "cls.h"

#include "shape.h"

int main1()
{
	//Base1 b1;
	//Base2 b2;
	//Derived1 d1;
	//Derived2 d2;
	//// 大小与函数列表有关
	//cout << "sizeof(Base1) = " << sizeof(Base1) << " sizeof(b1) = " << sizeof(b1) << endl;
	//cout << "sizeof(Base2) = " << sizeof(Base2) << " sizeof(b2) = " << sizeof(b2) << endl;
	//cout << "sizeof(Derived1) = " << sizeof(Derived1) << " sizeof(d1) = " << sizeof(d1) << endl;
	//cout << "sizeof(Derived2) = " << sizeof(Derived2) << " sizeof(d1) = " << sizeof(d1) << endl;

	//Derived1 d;  // d 能直接调用Derived1的所有函数、Base1的非虚函数，间接调用base1的虚函数
	//d.f();        // Derived::f
	//d.g1();		  // Derived::g1
	//d.Base1::f(); // Base1::f 
	//d.func();

	//Derived1 *d = new Derived1(); // 同上
	//d->f();	         // Derived::f
	//d->g1();		 // Derived::g1
	//d->Base1::f();   // Base1::f
	//d->func();		 // Derived1::func   重载
	//d->Base1::func();// Base1::func		 间接调用，显示调用

	//Base1 *b = new Derived1(); // b 只能调用Base1的函数，但是虚函数会被动态绑定
	//b->f();		// Derived1::f 
	//b->g();		// Base1::g
	//b->func();	// Base1::func

	//Base1 *b = new Base1(); // 显然只能调用base1的函数
	//b->f();   // Base1::f
	//b->g();   // Base1::g
	//b->func();// Base1::func

	//
	//Base1 *b = new Base1(); 
	//delete b; // 不论基类析构函数是否为虚函数，都会执行函数体

	//Base1 *b = new Derived1(); 
	//delete b; // 当基类析构函数为虚时，才会析构父类;    否则，只执行基类的析构函数

	//Derived1 *d = new Derived1();
	//delete d;	// 不论基类析构函数是否为虚函数，都会执行函数体



	//Derived2 d2;//直接调用Derived2的函数，间接调用父类函数
	//d2.f();         // Derived2::f
	//d2.Base1::f();  // Base1::f
	//d2.Base2::f();  // Base2::f

	//Derived2 *d2 = new Derived2();//直接调用Derived2的函数，间接调用父类函数
	//d2->f();        // Derived2::f
	//d2->Base1::f(); // Base1::f
	//d2->Base2::f(); // Base2::f
	//delete d2;

	//Base1 *d2 = new Derived2();// 调用base1的函数和Derived2重写的函数，
	//d2->f();		    // 子类重写 Derived2::f
	//d2->Base1::f();   // 间接调用父类虚函数 Base1::f    
	//d2->g();		    // 直接调用父类虚函数 Base1::g    
	//d2->func();		// 直接调用父类非虚函数 Base1::func
	//delete d2;        //其中一个父类析构函数必须为虚函数

	return 0;
}


void main2()
{
	Point<int> pt(0, 0);

	Rectangle<int> rt(0, 0, 10, 10);
	cout << rt.br();
}

int main()
{
	//main1();

	main2();
}