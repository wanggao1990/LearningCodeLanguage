#include "cls.h"

#include "shape.h"

int main1()
{
	//Base1 b1;
	//Base2 b2;
	//Derived1 d1;
	//Derived2 d2;
	//// ��С�뺯���б��й�
	//cout << "sizeof(Base1) = " << sizeof(Base1) << " sizeof(b1) = " << sizeof(b1) << endl;
	//cout << "sizeof(Base2) = " << sizeof(Base2) << " sizeof(b2) = " << sizeof(b2) << endl;
	//cout << "sizeof(Derived1) = " << sizeof(Derived1) << " sizeof(d1) = " << sizeof(d1) << endl;
	//cout << "sizeof(Derived2) = " << sizeof(Derived2) << " sizeof(d1) = " << sizeof(d1) << endl;

	//Derived1 d;  // d ��ֱ�ӵ���Derived1�����к�����Base1�ķ��麯������ӵ���base1���麯��
	//d.f();        // Derived::f
	//d.g1();		  // Derived::g1
	//d.Base1::f(); // Base1::f 
	//d.func();

	//Derived1 *d = new Derived1(); // ͬ��
	//d->f();	         // Derived::f
	//d->g1();		 // Derived::g1
	//d->Base1::f();   // Base1::f
	//d->func();		 // Derived1::func   ����
	//d->Base1::func();// Base1::func		 ��ӵ��ã���ʾ����

	//Base1 *b = new Derived1(); // b ֻ�ܵ���Base1�ĺ����������麯���ᱻ��̬��
	//b->f();		// Derived1::f 
	//b->g();		// Base1::g
	//b->func();	// Base1::func

	//Base1 *b = new Base1(); // ��Ȼֻ�ܵ���base1�ĺ���
	//b->f();   // Base1::f
	//b->g();   // Base1::g
	//b->func();// Base1::func

	//
	//Base1 *b = new Base1(); 
	//delete b; // ���ۻ������������Ƿ�Ϊ�麯��������ִ�к�����

	//Base1 *b = new Derived1(); 
	//delete b; // ��������������Ϊ��ʱ���Ż���������;    ����ִֻ�л������������

	//Derived1 *d = new Derived1();
	//delete d;	// ���ۻ������������Ƿ�Ϊ�麯��������ִ�к�����



	//Derived2 d2;//ֱ�ӵ���Derived2�ĺ�������ӵ��ø��ຯ��
	//d2.f();         // Derived2::f
	//d2.Base1::f();  // Base1::f
	//d2.Base2::f();  // Base2::f

	//Derived2 *d2 = new Derived2();//ֱ�ӵ���Derived2�ĺ�������ӵ��ø��ຯ��
	//d2->f();        // Derived2::f
	//d2->Base1::f(); // Base1::f
	//d2->Base2::f(); // Base2::f
	//delete d2;

	//Base1 *d2 = new Derived2();// ����base1�ĺ�����Derived2��д�ĺ�����
	//d2->f();		    // ������д Derived2::f
	//d2->Base1::f();   // ��ӵ��ø����麯�� Base1::f    
	//d2->g();		    // ֱ�ӵ��ø����麯�� Base1::g    
	//d2->func();		// ֱ�ӵ��ø�����麯�� Base1::func
	//delete d2;        //����һ������������������Ϊ�麯��

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