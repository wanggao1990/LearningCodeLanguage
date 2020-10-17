#pragma once
#include <iostream>
using namespace std;

class Base1
{
public:
	Base1() { cout << "Constrution Base1" << endl; }
	//~Base1() { cout << "Destrution Base1" << endl; }

	virtual ~Base1() { cout << "Destrution Base1" << endl; }

	virtual void f() { cout << "Base1::f" << endl; }

	virtual void g() { cout << "Base1::g" << endl; }

	virtual void h() { cout << "Base1::h" << endl; }

	void func(){ cout << "Base1::func" << endl; }
};

class Base2
{
public:
	Base2() { cout << "Constrution Base2" << endl; }
	//~Base2() { cout << "Destrution Base2" << endl; }

	virtual ~Base2() { cout << "Destrution Base2" << endl; }
	
	virtual void f() { cout << "Base2::f" << endl; }

	virtual void g() { cout << "Base2::g" << endl; }

	virtual void h() { cout << "Base2::h" << endl; }

	void func() { }
};

class Derived1 :public Base1
{
public:
	Derived1() { cout << "Constrution Derived1" << endl; }
	~Derived1() { cout << "Destrution Derived1" << endl; }

	virtual void f() { cout << "Derived1::f" << endl; }   // virtual¿ÉÐ´¿É²»Ð´

	virtual void g1() { cout << "Derived1::g1" << endl; }

	virtual void h1() { cout << "Derived1::h1" << endl; }

	void func() { cout << "Derived1::func" << endl; }

};

class Derived2 :public Base2, public Base1
{
public:
	Derived2() { cout << "Constrution Derived2" << endl; }
	~Derived2() { cout << "Destrution Derived2" << endl; }

	virtual void f()  { cout << "Derived2::f" << endl;  }

	virtual void g1() { cout << "Derived2::g1" << endl; }

	virtual void h1() { cout << "Derived2::h1" << endl; }
};
