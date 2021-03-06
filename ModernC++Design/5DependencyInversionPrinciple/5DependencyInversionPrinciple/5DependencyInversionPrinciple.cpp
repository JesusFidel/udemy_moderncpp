// 5DependencyInversionPrinciple.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

// 1.0 Dependency Inversion principle
// A. High-level modules should not depend on low-level modules.
//    Both should depend on abstractions.
// B. Abstractions should not depend on details. 
//    Details should depend on abstractions.

// When we talk about abstractions we talk about interfaces or base classes. Essentially instead of
// depending on a concrete type what you really want is to be as general as possible.  You want to take
// an interface which provides you the necessary functionality but you do not want to depend on the concrete
// type more than you need to, because then, you're depending on the implementation details

// let's see where this could pop-up. Let's simulate relationships between people:


enum class Relationship
{
	parent,
	child,
	sibling
};

struct Person
{
	string name;
};



// low-level module, which provides functionality for data storage.
// If you want to provide Research on the data, this would be a high level module, which it may call
// resarch
//struct Relationships //This would be the low level module
//{
//	vector<tuple<Person, Relationship, Person>> relations;
//
//	//2.1 Providing API for adding elements to the relations
//	void add_parent_and_child(const Person& parent, const Person& child)
//	{
//		relations.push_back({ parent, Relationship::parent, child });
//		relations.push_back({ child, Relationship::child, parent });
//	}
//};

// 3.3 is going to provide functionality to find all the children of a particular person.
// This is only the interface
struct RelationshipBrowser
{
	virtual vector<Person> find_all_children_of(const string& name) = 0;
};

//3.4 See that now, relationships is implemented in terms of RelationshipBrowser
struct Relationships : RelationshipBrowser // low-level
{
	vector<tuple<Person, Relationship, Person>> relations;

	//2.1 Providing API for adding elements to the relations
	void add_parent_and_child(const Person& parent, const Person& child)
	{
		relations.push_back({ parent, Relationship::parent, child });
		relations.push_back({ child, Relationship::child, parent });
	}

	vector<Person> find_all_children_of(const string &name) override
	{
		vector<Person> result;
		//C++17 does not compile yet
		/*for (auto&&[first, rel, second] : relations)
		{
			if (first.name == name && rel == Relationship::parent)
			{
				result.push_back(second);
			}
		}*/
		return result;
	}
};

struct Research // high-level module
{
	//3.0 To perform the research we need to somehow get the data. Now the WORST thing to do here , 
	// the thing which breaks the dependency inversion principle is to actually take a direct dependency
	// on a low level module. Becase a high level module should not depend on a low level module.

	//  Research(const Relationships& relationships)
	//  {
	//	  Now it depends on the implementation of the low level module!!!
	//    auto& relations = relationships.relations;
	//    for (auto&& [first, rel, second] : relations)
	//    {
	//      if (first.name == "John" && rel == Relationship::parent)
	//      {
	//        cout << "John has a child called " << second.name << endl;
	//      }
	//    }
	//  }

	// 3.1 Now imagine that relationships struct changes, and it makes relations private. The high
	// level module would be completely broken. That is why the dependency inversion principle exists.
	// it protects you agains changes in the implementation.

	//3.2 to fix this, instead of having a direct dependency on some low level module, you would introduce
	// an abstraction, some sort of interface.
	// This abstraction will be called RelationshipBrowser

	//3.5 We can now rewrite the high level module, will depend on a relationshipbrowser
	// Which uses the API of RelationShipBrowser
	Research(RelationshipBrowser& browser)
	{
		for (auto& child : browser.find_all_children_of("John"))
		{
			cout << "John has a child called " << child.name << endl;
		}
	}
	//  Research(const Relationships& relationships)
	//  {
	//    auto& relations = relationships.relations;
	//    for (auto&& [first, rel, second] : relations)
	//    {
	//      if (first.name == "John" && rel == Relationship::parent)
	//      {
	//        cout << "John has a child called " << second.name << endl;
	//      }
	//    }
	//  }
};

//4.0 The conclusion is that you want to have dependencies on abstractions, meaning typically dependencies on interfaces
// rather than concrete implementations. You do not want to delve into other classes details, and start
// depending on their details, because remember at some point of time, relationships might decide to replace
// the vector by some kind of map or something , and in this case you are going to be really screwed.


int main()
{
	Person parent{ "John" };
	Person child1{ "Chris" };
	Person child2{ "Matt" };

	Relationships relationships;
	relationships.add_parent_and_child(parent, child1);
	relationships.add_parent_and_child(parent, child2);

	Research _(relationships);

	return 0;
}