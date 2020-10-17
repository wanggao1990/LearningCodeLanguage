#pragma once

#include <iostream> 
using namespace std; 

#include "math.h"

template<typename T >
class Point
{
public:
	Point(T x, T y): _x(x), _y(y) {}

	~Point(){}

	T getX() { return _x; }
	T getY() { return _y; }

	Point operator+ (const Point& pt) const { return Point(_x + pt._x, _y + pt._y); }
	Point operator- (const Point& pt) const { return Point(_x - pt._x, _y - pt._y); }

	void operator+= (const Point& pt) const { _x += pt._x, _y += pt._y; }
	void operator-= (const Point& pt) const { _x -= pt._x, _y -= pt._y; }

	template<typename T >
	friend std::ostream& operator <<(std::ostream& out, const Point<T>& pt);

	//void showXY() { cout << "Point: (" << _x << "," << _y << ")" << endl; }

private:
	T _x, _y;
};

template<typename T >
std::ostream& operator <<(std::ostream& out, const Point<T>& pt)
{
	out << "(" << pt.getX() << ", " << pt.getY() << ")";
	return out;
}

template<typename T >
class Size {
public:
	Size(T w, T h) :_w(w), _h(h) {}

	T getWidth() { return _w; }
	T getHeight() { return _h; }

	Size operator+ (const Size& sz) { return Point(_w + sz._w, _h + sz._h); }
	Size operator- (const Size& sz) { return Point(_w - sz._w, _h - sz._h); }

	void operator+= (const Size& sz) { _w += sz._w, _h += sz._h; }
	void operator-= (const Size& sz) { _w -= sz._w, _h -= sz._h; }


	template<typename T >	
	friend std::ostream& operator <<(std::ostream& out, const Size<T>& sz);

private:
	T _w, _h;

};

template<typename T >	
std::ostream& operator<< (std::ostream& out, const Size<T>& sz)
{
	out << "[" << sz.getWidth() << ", " << sz.getHeight() << "]";
	return out;
}




template<typename T >
class Rectangle :public Point<T>, public Size<T> {
public:
	Rectangle(T x, T y, T w, T h) :Point(x,y), _w(w), _h(h) { }

	Rectangle(const Point& tl, const Point& br) : Point(tl) {	_w = br._x - tl._x,	_h = br._y - tl._y;	}

	Rectangle(const Point& tl, const Size& sz) : Point(tl), Size(sz) {	_w = sz.getWidth(), _h = sz.getHeight();	}

	Point tl() { return Point(getX(), getY()); }
	Point br() { return tl + Point(_w, _h); }

	T getArea() { return _w*_h; }
	T getGirth() { return 2 * (_w + _h); }
	T getSize() {return }

private:
	T	_w, _h;
};

template<typename T >
class Circle :public Point<T> {
public:
	Circle(T x, T y, T r) : _r(r) { }

	Circle(const Point& tl, T r) :_r(r) { }

	double getArea() { return 3.14 * _r * _r; }
	
private:
	T	_r;
};