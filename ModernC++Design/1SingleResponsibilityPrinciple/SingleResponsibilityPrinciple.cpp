// SingleResponsibilityPrinciple.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/lexical_cast.hpp>

using namespace std;

struct Journal {
	string title;
	vector<string> entries;

	Journal(const string &tittle) : title(title){}

	void add_entry(const std::string &entry) {
		static int count = 1;
		entries.push_back(boost::lexical_cast<std::string>(count++) + ": " + entry);
	}

	//Note: definition of persistance
	/*   Persistent objects are those which survive between successive 
	 *   invocations of the program. A classic example of such an object 
	 *   is a database record. C++ doesn't support persistence directly 
	 *   (there are proposals for adding persistence and reflection to 
	 *   C++ in the future)
	 *
	 */

	// The problem with this approach is that you now have a separate concern,
	// a concern called persistence. So you are adding persistence code into your journal.
	// Imagine that you add load function.
	// Imagine that you want to use databases instead of files.
	// You would have to go thought all this code and change all the functions
	// What we do is something called: separations of concerns. We say that the Journal
	// should take care of the journal entries and the journal tittle, and we 
	// create a separate class (persistance manager)

	//This is not the correct way to go. If the way that we use to save , for example from
	// files to databases, we should have to change everything.
	void save(const string &filename)
	{
		std::ofstream ofs(filename);
		for (auto& entry : entries)
		{
			ofs << entry << std::endl;
		}
	}
	
};

//Separation of concerns, in a separate component.
struct PersistenceManager
{
	//this is a more robust and more reliable way of actually implementing
	// persistance  what happens as your persistence manager grows is that
	// if you decide that something changes, you 
	static void save(const Journal &j, const string &filename)
	{
		std::ofstream ofs(filename);
		for (auto& entry : j.entries)
		{
			ofs << entry << std::endl;
		}


	}
};

int main()
{
	//a class should have a single reason to change. In other words, a class should have
	// a primary responsibility and it should not take up other responsibilities

	Journal journal{ "Dear Diary" };
	journal.add_entry("I ate a bug");
	journal.add_entry("I cried today");

	//Instead of doing this:
	//journal.save("diary.txt");
	PersistenceManager pm;
	pm.save(journal, "diary.txt");
	getchar();
    return 0;
}

