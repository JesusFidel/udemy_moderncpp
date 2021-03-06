// 2Open-ClosedPrinciple.cpp : Defines the entry point for the console application.
//
// SingleResponsibilityPrinciple.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;

//0suppose that you are making a website which sells certain
//products and your manager wants you to be able to filter
//those products. Let's suppose that each of the products has
//certain traits like, for example, color and size

enum class Color { red, green, blue };
enum class Size { small, medium, large };

struct Product {
	string name;
	Color color;
	Size size;

};
// 1 2 3 4

//Product Filter would be the wrong way to do it, not flexible

/*
And this brings us to the open closed principle.
So the open closed principle basically states that your systems should be open to extensions so you
should be able to extend systems by inheritance for example but closed for modification.
And unfortunately what we're doing here is we're modifying existing code instead of inheriting and thereby
extending the system so let's see if we can build a better filter.
*/
struct ProductFilter
{	
	vector<Product*> by_color(vector<Product*> items, Color color)
	{
		vector<Product*> result;
		for (auto& item : items)
		{
			if (item->color == color)
			{
				result.push_back(item);
			}
		}
		return result;
	}
	vector<Product*> by_size(vector<Product*> items, Size size)
	{
		vector<Product*> result;
		for (auto& item : items)
		{
			if (item->size == size)
			{
				result.push_back(item);
			}
		}
		return result;
	}
	vector<Product*> by_size_and_color(vector<Product*> items, Size size, Color color)
	{
		vector<Product*> result;
		for (auto& item : items)
		{
			if (item->size == size && item->color == color)
			{
				result.push_back(item);
			}
		}
		return result;
	}
};

// 5 To solve the problem, we will use specification pattern: 

/*
	So the way we're going to do this is by defining two interfaces we're going to define interfaces called
	specification and filter.
	So first of all define the specification interface so template type name T and those is we using T so
	it doesn't just have to work on products it can work on any kind of type and it's going to be called
	specification. And all we gonna do here is add a single pure virtual method called is satisfied it's
	going to return and boolean is going to be called is satisfied and all it tries to do is it tries to
	check whether some item satisfies a particular specification and the specification is once again going
	to be defined through inheritance.
*/
template <typename T> struct Specification {
	
	virtual bool is_satisfied(T *item) = 0;
	//7
	AndSpecification<T> operator&&(Specification<T>&& other) {
		return AndSpecification(*this, other);
	}
};
// 5 Filter is going to define the interface that needs to be implemented by any kind of filter
// like a filter of items, for example
template <typename T> struct Filter {
	virtual vector <T*> filter(vector<T*> items, Specification<T>&spec) = 0;
};
// 5 Now a better filter is going to be implemented , to solve the problem of filtering by color, size ...etc
struct BetterFilter : Filter<Product>
{
	vector <Product*> filter(vector<Product*> items,
		Specification<Product>&spec) override
	{
		vector<Product*> result;
		for (auto& item : items) {
			if (spec.is_satisfied(item)) {
				result.push_back(item);
			}
		}

		return result;
	}
};

//5 Now we need the different specifications that we want to be able to use to actually search: (size, color or size and color)
struct ColorSpecification : Specification<Product>
{
	Color m_color;
	ColorSpecification(Color color) : m_color(color) { }

	bool is_satisfied(Product *item) override {
		return item->color == m_color;
	}

};

struct SizeSpecification : Specification<Product>
{
	Size m_size;
	explicit SizeSpecification(Size size) : m_size(size) { }

	bool is_satisfied(Product *item) override {
		return item->size == m_size;
	}

};

//6 to define a specification of size and color, a combinator should be made
//Look that SizeSpecification annd ColorSpecification are not generic. Are predefined to work in
// Size and Colors
template<typename T> struct AndSpecification : Specification<T>
{
	Specification<T>& first;
	Specification<T>& second;

	AndSpecification(Specification<T> &first, 
					 Specification<T> &second) : first(first), second(second){}

	bool is_satisfied(T *item) override {
		return first.is_satisfied(item) && second.is_satisfied(item);
	}

};

int main()
{
	//1
	Product apple{ "Apple", Color::green, Size::small };
	Product tree{ "Tree", Color::green, Size::large };
	Product house{ "House", Color::blue, Size::large };

	vector<Product*> items{ &apple, &tree, &house };

	ProductFilter pf;
	auto green_things = pf.by_color(items, Color::green);
	for (auto& item : green_things)
	{
		cout << item->name << " is green " << endl;
	}//1 2 3  4

	// 1 Until here everything is ok. but now let's suppose your manager comes back to you
	//and says, Can you also please filter by size? and you end up copying the code you've
	//written in by_color and make another one named by_size

	// 2 You have here a workable solution but the problem is that you've had to go back into a chunk of code
	// that you've already tested and maybe you already shipped to the client, so now
	// you need to introduce this binary compatibility by adding another interface member
	// to productfilter, which is not good.

	// 3 If your manager wants to filter by another thing, for example both color and size, you would want to
	// replicate another time the code and make another function. This is very problematic approach becase we have
	// because for one problem, we can have several functions with duplicated code. This bring us to the 
	// open-closed principle.

	// 4 The open-closed principle basically states that your systems should be open
	// to extensions so you should be able to extend systems by inheritance , for example,
	// but closed for modifications 
	//What we were doing here with ProductFilter methods is modifying existing code, instead of inheriting or extending
	// the system. Let's do a better filter.

	// 5 The way we are going to do this is by defining two interfaces: specification and filter

	BetterFilter bf;
	ColorSpecification green(Color::green);

	for (auto& item : bf.filter(items, green))
		cout << item->name << " is green " << endl;

	SizeSpecification large(Size::large);
	AndSpecification<Product> green_and_large(green, large);

	//7 we can do the same in a shorter manner making a combined specification with operator&&
	auto spec = ColorSpecification(Color::green)
		&& SizeSpecification(Size::large);
	// Now we do the same with spec, and it is a lot shorter because we do not need to create any 
	// of these variables. The execution is the same as above.
	for(auto& item : bf.filter(items, spec))
		cout << item->name << " is green and large\n";

	//Just to summarize, , the goal of the open-closed principle is to avoid having to jump into
	// code that you've already written.
	// Open for extension meaning that you can walways make and use specification by extending
	// by inheriting effectively but closed for modification, which means that in the context of
	// the specification pattern you would never require yourself to go back into the filter interface
	//

	getchar();
	return 0;
}

