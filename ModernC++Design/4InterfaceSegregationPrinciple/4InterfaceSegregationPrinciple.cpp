// 4InterfaceSegregationPrinciple.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;
//0. The idea of the interface segregation principle is basically to get you to not create interfaces
// which are too large and which require implementors to maybe implement too much

//1. Imagine that you want to an interface for scanning, printing and faxing documents, so you could
// be tempted to just put all of those operations into a single interface in something called machine.


#include <vector>
struct Document;

//1.1 Interace of Machine, which is too large 
//struct IMachine
//{
//  virtual void print(Document& doc) = 0;
//  virtual void fax(Document& doc) = 0;
//  virtual void scan(Document& doc) = 0;
//};
// MultiFunctionPrinter
//struct MFP : IMachine
//{
//  void print(Document& doc) override;
//  void fax(Document& doc) override;
//  void scan(Document& doc) override;
//};

//2.0 Theh problem that you typically encounter is , what happens if you need to implement just a printer.
// or just a scanner, because you only have this machine interface to work with. If we put all the interfaces
// together you are sending the client the message that you've got the scanner which can also print, which isn't true
// but you are giving them the API anyway simply because the interface that's been defined for handling all of this
//stuff is just too big. What we really need is to segregate the interfaces because no client would
// require always to implement both print,scan and fax as well.

//2.1 Instead of a large interface, you would prefer the following approach, segregating the interfaces


// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much

struct IPrinter
{
	virtual void print(Document& doc) = 0;
};

struct IScanner
{
	virtual void scan(Document& doc) = 0;
};

struct IFax
{
	virtual void fax(Document& doc) = 0;
};


struct Printer : IPrinter
{
	void print(Document& doc) override;
};

struct Scanner : IScanner
{
	void scan(Document& doc) override;
};

struct Fax : IFax
{
	void fax(Document& doc) override;
};

//2.3 Here we define the segregated interface
struct IMachine : IPrinter, IScanner, IFax { };

//3.0 Decorator
struct Machine : IMachine
{
	IPrinter& printer;
	IScanner& scanner;
	IFax& faxMachine;

	Machine(IPrinter& printer, IScanner& scanner, IFax& fax) :
			printer{ printer },
			scanner{ scanner },
			faxMachine{ fax }
	{
	}

	void print(Document& doc) override {
		printer.print(doc);
	}
	void scan(Document& doc) override { 
		scanner.scan(doc);  
	};

	void fax(Document& doc) override { 
		faxMachine.fax(doc);
	};

	
};

int main()
{
	return 0;
}
