// 0IntroductionToModernCppDesignPatterns.cpp : Defines the entry point for the console application.
//

/*
So what are design patterns:
Well quite simply the design patterns are common architectural approaches 
that people have observed throughout the years and decided to catalog them 
and give them common names so that we can then talk between one another and 
refer to the same patterns using the same words.

*/
#include "stdafx.h"

//Key Concepts

/*Curiously Recurring Template Pattern*/
/*Essentially, the idea is simple: an inheritor passes itself as a
template argument to its base class:
struct Foo : SomeBase<Foo>
 {
 ...
 }
why one would ever do that? Well,
one reason is to be able to access a typed this pointer inside a base class
implementation.

*/

int main()
{
    return 0;
}


/*
Sumary of SOLID design principles

The Single Responsibility Principle:
Basically this idea that A-class should only have one reason to change and it's also related to something
called separation of concerns in that if you have a system which is handling different kinds of concerns
it makes sense to put them in different classes so that these can be refactored independently for example
or replaced by something else.


Open closed principle: 
we talked about this idea that the classes should be open for extension and closed for modification.
So essentially the idea here is that if you're coming back into an already written or you test the class
and modifying things in order to extend functionality This is probably not the best way to go and you
should consider using the object oriented paradigm and inheritance instead of just modifying existing
code.

Liskov substitution principle the idea that you should always be able to substitute
a base type for a subtype and we looked at the situation where the violation of this principle leads
to rather unpleasant results.

Then we talked about the interface segregation principle the idea that you shouldn't be putting too
much into an interface.
In the case of swithe That's a protocol that you shouldn't be overloading and you should split a protocol
into separate protocols separate interfaces and thereby you don't force the implementor to put lots
of stubs and throwing exceptions out if not implemented methods.
So this is also related to something called the jargony which is this idea of you ain't going to need
it.
Meaning that you are going to need certain methods implemented so why force other people to implement
the interface in the first place.
Now finally we looked at the dependency inversion principle.
Nothing to do with dependency injection.
Basically this idea that high level modules should not depend on low level ones that you should abstractions
instead and have everything done through abstraction.
So we looked at how code can be refactor to do exactly that.


*/