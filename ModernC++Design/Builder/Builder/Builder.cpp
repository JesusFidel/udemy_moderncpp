// Builder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;

/*1- So let's try doing exactly that.
	I'm going to begin by making a structure called HTMLElement.*/

struct HtmlElement 
{
	string _name, _text;
	vector <HtmlElement> _elements;

	const size_t indent_size = 2;

	HtmlElement() = default;

	HtmlElement(const string &name, const string &text) : _name(name), _text(text){}

	/**
	 * @brief The actual implementation of str . Basically just does the
	 *	indentation in a correct way and it does the recursive invocation so that you sort of you go through
	 *	each of the sub elements and you do SDR on them with an increased indent value and so on and so forth.
	 *	So this gets you the right structure.
	 *	
	 * 
	 * @param indent 
	 * @return string 
	 */
	string str(int indent = 0) const {
		ostringstream oss;
		string i(indent_size *indent, ' ');
		oss << i << "<" << _name << ">" << endl;

		if (_text.size() > 0) {
			oss << string(indent_size * (indent + 1), ' ') << _text << endl;
		}

		for(const auto& e : _elements){
			oss << e.str(indent + 1);
		}

		oss << i << "</" << _name << ">" << endl;
		return oss.str();
	}

};

/*2-	
 *		Now the interesting thing is how do you actually build up these elements and this is where the build
 *		pattern actually comes into play because you make something called a builder.
 *		So the HTML element here is just a utility class for modeling an HTML element in an object oriented way
 *		in C++.
 *		But to have a builder we're going to have a separate structure.
 *		I'm going to call it HtmlBuilder.

		So this structure whether it's going to do is going to allow us to first of all define the root of our
		element and then add children in a very simple fashion.
		So first of all I'll have the element called the router that's going to be at the top level element
		there's always a single element or Typically there is a single element and then we can have it in the
		constructor but we're going to do a constructed differently because remember for whoever is working
		with the builder it's inconvenient to start working with the sacred element object which is one that
		work with strings basically So I'm going to have a female build a constructor which actually takes the
		name of the root.
*/
struct HtmlBuilder{
	HtmlElement _root;

	HtmlBuilder(string root_name) {
		_root._name = root_name;
	}
	//utility func
	void add_child(string child_name, string child_text) {
		HtmlElement e{ child_name, child_text };
		_root._elements.emplace_back(e);
	}
	/* Print our HTML out after we are done working with it*/
	string str() const { return _root.str(); }

};

int main()
{

	/* 0-
		So in the previous example we actually looked at how you can build simple bits of HTML out of strings.
		But obviously this approach doesn't really scale if you want to build something large.
		So in this case what you would typically do is you would start creating object oriented structures which
		actually represent the different parts of the HTML that you're building.
	*/
	/*auto text = "hello";
	string output;
	output += "<p>";
	output += text;
	output += "</p>";
	cout << output << endl;

	string words[] = { "hello", "world" };
	ostringstream oss;
	oss << "<ul>";

	for (auto w : words) {
		oss << " <li>" << w << "</li>";
	}
	oss << "</ul>";
	cout << oss.str() << endl;*/


	/*3- Using the builder*/
	HtmlBuilder builder{ "ul" };
	builder.add_child("li", "hello");
	builder.add_child("li", "world");
	/*we're using object oriented structures to define everything.*/

	cout << builder.str() << endl;

	return 0;
}

