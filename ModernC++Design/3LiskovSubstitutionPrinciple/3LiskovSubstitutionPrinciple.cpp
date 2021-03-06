// 3LiskovSubstitutionPrinciple.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;


class Rectangle {
protected:
	int width, height;
public:
	Rectangle(int width, int height) : width(width), height(height){}

	virtual int getWidth() const
	{
		return width;
	}
	virtual void setWidth(int width)
	{
		Rectangle::width = width;
	}
	virtual int getHeight() const
	{
		return height;
	}
	virtual void setHeigth(int height)
	{
		Rectangle::height = height;
	}

	virtual int area() const { return width * height; }
	
};

//2.2 Unfortunately what we've just done is we've violated Liskov Substitution principle which states
// that if you have a function with takes a base class, any derived class should be able to substituted
// into the function process without any problem. Unfortunately we are going to have a problem here
class Square : public Rectangle
{
public:
	Square(int size) : Rectangle(size, size) {}

	void setWidth(int width) override
	{
		this->width = this->height = width;
	}
	void setHeigth(int height) override
	{
		this->width = this->height = height;
	}
};

void process(Rectangle &r)
{
	int w = r.getWidth();
	r.setHeigth(10);
	cout << "Excepted area = " << (w * 10)
		<< ", got " << r.area() << endl;

}

//2.5 this is a more sensible way that would not break the Liskov Substitution principle
struct RectangleFactory
{
	static Rectangle create_rectangle(int w, int h);
	static Rectangle create_square(int size);
};

//the goal of this principle is to specify that subtypes should be
//immediately substitutable for their base types
int main()
{
	Rectangle r{ 3,4 };
	process(r);
	//Working with a rectangle, we try to get the area. We are clear setting width and height, and
	// there is not problem with the expected area. 

	//2.1 Now, lets do another class that inherits from rectangle, a square

	//2.3  Taking a look into process, we see that we setheight(10), we are overwritting the square.size
	Square sq{ 5 };
	process(sq);
	//2.4 we've broken the Liskov Substitution principle, with this example.

	//2.5 how to fix this problem?
	// the idea of inheriting a square from a rectangle is not the best idea because, in terms of
	// the language, a square is in fact a rectangle, so you can say a square should inherit from
	// a rectangle but you could do it differently, you could keep Rectangle with a boolean flag
	// saying if it is a square or not, or you can , if you want to construct squares and rectangles
	// to make a factory

	//2.6 To reiterate the idea is that you should be able to substitute a derived class, in this
	//case is square, you should be able to substitute it into any location where a base class 
	//is being used like here: process(Rectangle& r), and with this design is unfortunately impossible.

	getchar();
    return 0;
}

