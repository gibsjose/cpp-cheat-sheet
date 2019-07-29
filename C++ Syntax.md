# C++ Syntax Cheat Sheet

## Table of Contents

<!-- TOC depthFrom:1 depthTo:6 withLinks:1 updateOnSave:0 orderedList:0 -->

- [C++ Syntax Cheat Sheet](#c-syntax-cheat-sheet)
	- [Table of Contents](#table-of-contents)
	- [1.0 C++ Classes](#10-c-classes)
		- [1.1 Class Syntax](#11-class-syntax)
			- [1.1.1 Class Declaration (`.h` file)](#111-class-declaration-h-file)
			- [1.1.2 Class Definition (`.cpp` file)](#112-class-definition-cpp-file)
			- [1.1.3 Class Utilization (Another `.cpp` file)](#113-class-utilization-another-cpp-file)
			- [1.1.4 Getters and Setters](#114-getters-and-setters)
		- [1.2 Inheritance](#12-inheritance)
			- [1.2.1 `Rectangle` Declaration (`.h` file)](#121-rectangle-declaration-h-file)
			- [1.2.2 `Rectangle` Definition (`.cpp` file)](#122-rectangle-definition-cpp-file)
			- [1.2.3 `Rectangle` Utilization (Another `.cpp` file)](#123-rectangle-utilization-another-cpp-file)
		- [1.3 Class polymorphism](#13-class-polymorphism)
			- [1.3.1 Motivation](#131-motivation)
			- [1.3.2 Virtual functions](#132-virtual-functions)
		- [1.4 Special methods(constructor, destructor, ...)](#14-special-methods)
			- [1.4.1 Constructor, destructor pair](#141-constructor-destructor-pair)
				- [1.4.1.1 Use of `explicit` in Constructors](#1411-use-of-explicit-in-constructors)
				- [1.4.1.2 Member initializer list](#1412-member-initializer-list)
			- [1.4.2. `new` and `delete`](#142-new-and-delete)
			- [1.4.3. Copy constructor, copy assignment](#143-copy-constructor-and-copy-assignment)
			- [1.4.4. Move constructor, move assignment](#144-move-constructor-and-move-assignment)
		- [1.5 Operator overloading](#15-operator-overloading)
		- [1.6 Templates](#16-templates)
	- [2.0 General C++ Syntax](#20-general-c-syntax)
		- [2.1 Namespaces](#21-namespaces)
		- [2.2 References/Pointers](#22-references-and-pointers)
		- [2.3 Keywords](#23-keywords)
			- [2.3.1 General keywords](#231-general-keywords)
			- [2.3.2 Storage class specifiers](#232-storage-class-specifiers)
			- [2.3.3  `const` and `dynamic` Cast Conversion](#233-const-and-dynamic-cast-conversion)
		- [2.4 Preprocessor tokens](#24-preprocessor-tokens)
		- [2.5 Strings ](#25-strings-stdstring)
		- [2.6 Iterators](#26-iterators-stditerator)
		- [2.7 Exceptions](#27-exceptions-stdexception)
		- [2.8 Lambdas](#28-lambdas)

<!-- /TOC -->


## 1.0 C++ Classes
### 1.1 Class Syntax
#### 1.1.1 Class Declaration (`.h` file)
Here's a simple class representing a polygon, a shape with any number of sides.

The class *declaration* typically goes in the `.h` file. The *declaration* gives the class name, any classes it may extend, declares the members and methods, and declares which members/methods are public, private, or protected.
```c++
#include <string>

class Polygon {

// Private members and methods are only accessible via methods in the class definition
private:
    int num_sides;    	// Number of sides

// Protected members and methods are only accessible in the class definition or by classes who extend this class
protected:
    std::string name;   // Name of the polygon

// Public members and methods are accessible to anyone who creates an instance of the class
public:
    // Constructors
    Polygon(const int num_sides, const std::string &name);  // <--- This constructor takes the number of sides and name as arguments

    // Getters and Setters
    const int GetNumSides(void) const;
    void SetNumSides(const int num_sides);

    const std::string & GetName(void) const;
    void SetName(const std::string &name);
    
}; // <--- Don't forget the semicolon!
```

#### 1.1.2 Class Definition (`.cpp` file)
```c++
#include <string>	// explicit is better then implicit 

#include "Polygon.h"    // <--- Obtains the class declaration

// Constructor
// You must scope the method definitions with the class name (Polygon::)
Polygon::Polygon(const int num_sides, const std::string &name) {
    this->num_sides = num_sides;	// 'this' refers to the instance of the class. Members are accessed via pointers
    this->name = name;
}

// Get the number of sides
const int Polygon::GetNumSides(void) const {
    return this->num_sides;
}

// Set the number of sides
void Polygon::SetNumSides(const int num_sides) {
    this->num_sides = num_sides;
}

// Get the polygon name
const std::string & Polygon::GetName(void) const {
    return this->name;
}

// Set the polygon name
void Polygon::SetName(const std::string &name) {
    this->name = name;
}
```

#### 1.1.3 Class Utilization (Another `.cpp` file)
```c++
#include <string>
#include <iostream>

#include "Polygon.h"    // <--- Obtains the class declaration

int main(int argc, char *argv[]) {
    // Create a polygon with 4 sides and the name "Rectangle"
    Polygon polygon = Polygon(4, "Rectangle");

    // Check number of sides -- Prints "Rectangle has 4 sides"
    std::cout << polygon.GetName() << " has " << polygon.GetNumSides() << " sides"<< std::endl;

    // Change number of sides to 3 and name to "Triangle"
    polygon.SetNumSides(3);
    polygon.SetName("Triangle");
}
```

#### 1.1.4 Getters and Setters
A shortcut often used for Getters/Setters is to define them in the class declaration (`.h`) file as follows:
```c++
#include <string>

class Car {
private:
	int year;
	std::string make;

public:
	const int GetYear(void) const { return this->year; }
	void SetYear(const int year) { this->year = year; }
	const std::string & GetMake(void) const { return this->make; }
	void SetMake(const std::string &make) { this->make = make; }
};
```

Another important consideration: If you have getters and setters for all of your members, you may want to reconsider the design of your class. It is more often than not that having getters and setters for every member is indicative of poor planning of the class design and interface. Getters are very common, but setters should be used more carefully. Should you have set the variable in the constructor? Is it set somewhere else in another method, perhaps even indirectly?

### 1.2 Inheritance
A class can extend another class, meaning that the new class inherits all of the data from the other class, and can also override its methods, add new members, etc. Inheritance is the key feature required for polymorphism.
P. S. it is very important for a beginner not to overuse this feature(because human's brain tends to create hierarchies, 
even where it is not needed). There are some good alternatives like [composition](https://en.wikipedia.org/wiki/Composition_over_inheritance) and [aggregation](https://stackoverflow.com/a/269535)

**Example:** the class `Rectangle` can inherit the class `Polygon`. You would then say that `Rectangle` extends `Polygon`, or that class `Rectangle` is a sub-class of `Polygon`. In plain English, this means that a `Rectangle` is a more specialized version of a `Polygon`.

#### 1.2.1 `Rectangle` Declaration (`.h` file)
```c++
#include <string> 		// explcit is better then implicit

#include "Polygon.h"	// <--- You must include the declaration in order to extend the class

class Rectangle: public Polygon {
private:			// <--- The members 'num_sides' and 'name' are already inherited from Polygon
	int length;
	int width;

public:
	// Constructors
	Rectangle(const std::string &name);
	Rectangle(const std::string &name, const int length, const int width);

	// Getters and Setters	<--- The methods 'GetNumSides()', 'SetNumSides()', 'GetName()' and 'SetName()' are already inherited from Polygon
	const int GetLength(void) const { return this->length; }
	void SetLength(const int) { this->length = length; }

	const int GetWidth(void) const { return this->width; }
	void SetWidth(const int) { this->width = width; }

	// Other Methods
	const int Area(void) const;
};
```

#### 1.2.2 `Rectangle` Definition (`.cpp` file)
```c++
#include <string>		// uses std::string

#include "Rectangle.h"	// <--- Only need to include 'Rectangle', since 'Polygon' is included in 'Rectangle.h'

// This constructor calls the superclass (Polygon) constructor and sets the name and number of sides to '4', and then sets the length and width
Rectangle::Rectangle(const std::string &name, const int length, const int width) : Polygon(4, name) {
	this->length = length;
	this->width = width;
}

// This constructor calls the superclass (Polygon) constructor, but sets the length and width to a constant value
Rectangle::Rectangle(const std::string &name) : Polygon(4, name) {
	this->length = 1;
	this->width = 1;
}

// Compute the area of the rectangle
const int Rectangle::Area(void) const {
	return this->length * this->width;
}
```

#### 1.2.3 `Rectangle` Utilization (Another `.cpp` file)
```c++
#include <iostream>

#include "Rectangle.h"

int main(int argc, char *argv[]) {
	Rectangle rectangle = Rectangle("Square", 6, 6);

	// Prints "Square has 4 sides, and an area of 36"
	std::cout << rectangle.GetName() << " has " << rectangle.GetNumSides() 
						<< " sides, and an area of " << rectangle.Area() << std::endl;
}
```

### 1.3 Class polymorphism
The same name, that has many forms, could be used in different usecases. It is often used when there are hierarchy of classes related with inheritance.
#### 1.3.1 Motivation
Let's extend previous exercises and create hierarchy of geometrical figures(pretty logical decision)
```c++
#include <cmath> 	// needed for PI constant

class Shape
{
	// empty class for hierarchy logic 
	// there are no methods since all
	// shapes are using different area 
	// calculation formulas
};

class Rectangle : public Shape {
	// private by default
	double length;
	double width;
public:
	Rectangle(double width, double length) // using the same names is legal
	:width{width}, length{length} {} // using member initializer list
	
	double area() const {	// const means it won't change the class members
		return length * width;	
	}
};

class Circle : Shape {
	double radius;
public:
	Circle(double radius) 
	:radius{radius} {}
	
	double area() const {
		return M_PI * radius * radius; // pi*r^2
	}
};
```
We are glad to build our hierarchy, but something is illogical here. We discover common pattern: all of classes in hierarchy are using the same function 'area', how can we generalize it? So let's notice: every Shape has the area, so i don't care what shape i am using, i want to have it's area. Recall the definition of polymorphism at the beginning of the item. 
So here comes the solution:
#### 1.3.2 Virtual functions
We want to achieve something like this:
```c++
Rectangle rct {2, 5};
Shape* some_unknown_shape = &rct;

some_unkown_shape->area(); // must be 10
```
But how do we do it if `area` function is used only with object it is invoked on, like `rct` in previous example?
C++ solution is:
```c++
#include <cmath> 

class Shape {
public:
	virtual double area() const
	{
		// some default implementation
	}
};

class Rectangle : public Shape {
	// private by default
	double length;
	double width;
public:
	Rectangle(double width, double length) // using the same names is legal
	:width{width}, length{length} {} // using member initializer list
	
	double area() const override { // override reminds that it is virtual method
		return length * width;	
	}
};

class Circle : public Shape {
	double radius;
public:
	Circle(double radius) 
	:radius{radius} {}
	
	double area() const override {
		return M_PI * radius * radius; // pi*r^2
	}
};

int main()
{
	Rectangle rct {2, 5};
	Shape* some_unknown_shape = &rct;

	some_unknown_shape->area(); // is 10	
}
```
This is so-called runtime polymorphism, it is named so because of the time of it's invocation -  the decision of what version of `area` to use(Circle or maybe Rectangle version or others?) is made during the program run. It is implemented using [this](https://www.learncpp.com/cpp-tutorial/125-the-virtual-table/) mechanism. In a nutshell: it is a little more expensive to use, but it's usefulness is overwhelming.

This was runtime polymorphism, there are also compiletime polymorphism([here is more on differences between them](https://www.geeksforgeeks.org/polymorphism-in-c/)).

So now it is ok. Is it? There is no limit of perfection. Note that we don't have default implementation to area function.
How do we declare that we want this function in all our child classes? C++ solution is `pure virtual function`:
```c++
class Shape {
public:
	virtual double area() const = 0;
};
```
Rest of code behaves the same. Object of class Shape can't be created, it makes sense, why do we need an object that only promises a function, not giving it? It is called `interface` in wide meaning of this word, or `abstract class` in c++ interpretation. It promises a function `area`, so all child classes must have it.

### 1.4 Special methods
All this methods are used to manage class lifetime.
- **Constructor** performs creation of an object from given data. Establishes [class invariant](https://softwareengineering.stackexchange.com/a/32755).
- **Destructor** performs deletion of an object. Removes class invariant.

Briefly **class invariant** is a statement that holds true from creation to deletion of an object.
Other methods like: **copy constructor, move constructor, copy assignment, move assignment** are used for specific reasons, explained later in this item. 
#### 1.4.1 Constructor, destructor pair
Meaning of this methods was explained above, here are some syntax:
##### 1.4.1.1 Use of `explicit` in Constructors
The keyword `explicit` should be used in single-argument constructors to avoid the following situation. Consider the class `Array`:
```c++
class Array {
	int size;
public:
	Array(int size) {	// constructor
		this->size = size;
	}
	
	~Array() {		// destructor
		// do some cleanup
		// Note: destructors only needed(basically)
		// to clean something that was allocated
		// from the heap with new operator
		// (new explained later)
	}
};
```

The following is now legal but ambiguous:
```c++
Array array = 12345;
```

It ends up being the equivalent of this:
```c++
Array array = Array(12345);
```

That's fine, one would suppose, but what about the following:
```c++
// Method PrintArray is defined as: Array::Print(const Array &array)
array.Print(12345);
```

Uh-oh. That's now legal, compilable code, but what does it mean? It is extremely unclear to the user.

To fix this, declare the single-argument `Array` constructor as `explicit`:
```c++
class Array {
	int size;
public:
	explicit Array(int size) {
		this->size = size;
	}
	
	~Array() { 
		//... 
	}
};
```

Now you can only use the print method as follows:
```c++
array.Print(Array(12345));
```
##### 1.4.1.2 Member initializer list
In previous example, we could've used simpler notation for initializing members:
```c++
class MemberInitializedArray
{
	int size1;
	int size2;
public:
	explicit Array(int s1, int s2)
	: size1{s1}, size2{s2}	// init members
	{
	
	}
};
```
#### 1.4.2 `new` and `delete`
Before moving on, we should consider two special "functions" in c++. 
When you declare a variable
```c++
int a = 3;
```
it uses memory, memory of your pc, your RAM. But there are two types of standard memory(in program): heap and stack.
`a` is allocated on the stack, program decides how many and where on the stack allocate this memory. 
But what if we want to decide when to allocate memory manually? There are some great flexibility features come with this decision. So here it goes:
```c++
int* a = new int {3};	// allocation
```
But with great power comes great responsibility. **We need to deallocate it manually**:
```c++
delete a;		// manual deallocation
```
More on [this](https://www.geeksforgeeks.org/new-and-delete-operators-in-cpp-for-dynamic-memory/) topic.
There are also `new[]` and `delete[]` for arrays, explained in the link.
#### 1.4.3 Copy constructor and copy assignment
Sometimes there are a need for such statements:
```c++
MyClass a {1};
MyClass b {a};	// first
MyClass c = a;	// second
```
It could be accomplished with **copy constructor**(first) and **copy assignment operator**(second).
```c++
class MyClass {
	int data;
public:
	MyClass(int i) :i{i} {}
	
	MyClass(const MyClass& mc)	// first
	: i{mc.i} {}
	
	MyClass& opeartor=(const MyClass& mc)	// second
	{
		i = mc.i;
	}
};
```
We used `operator` notation here, it will be explained soon. Now you could just see the result and how to implement it.
#### 1.4.4 Move constructor and move assignment
And sometimes we have a situation when class that we initializing from(recall **copy constructor**) won't be used in the future. All data it maintains can be moved from it to our current object.
```c++
class Movable {
	SomeClass* data_ptr;
public:
	Movable(SomeClass data)
	:data_ptr{new SomeClass {data}} {}
	
	Movable(Movable&& mvbl) {	// first
	
		data_ptr = mvbl.data_ptr;	// just assign allocated memory, no need to copy
						// mvbl will be deleted after this call
						
		mvbl.data_ptr = nullptr;	// and assign it to nullptr
						// so that it can't acces "our" data anymore
	}
	
	Movable& operator=(Movable&& mvbl) {	//second
		data_ptr = mvbl.data_ptr;
		mvbl.data_ptr = nullptr;
	}
	
	~Movable() {
		delete data_ptr;	// non-empty destructor example
	}
};
```
It is called **move constructor**(first) and **move assignment**(second).
And usecases are:
```c++
Movable some_func() {
	// ...
}

int main()
{
	Movable b {some_func()};		// first
	Movable a = some_func();		// second
}
```
It invokes because `some_func` returns object that won't be used anywhere else, it is deleted right after the call, so we use this opportunity and take it's data for ourselves.


P. S. Idiom called [`copy-and-swap`](https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom), it is better to know it, as it is proved to be very useful through the years.
### 1.5 Operator Overloading
It is pretty essential for human to use this notation for arithmetic operations:
```c++
int a = 6;
int b = 3;

int c = a + b;
int d = a - b;
int e = a * b;
int f = a / b;
```
the other version of this is:
```c++
int a = 6, b = 3;

int c = add(a, b);
int c = subtract(a, b);
int c = multiply(a, b);
int c = divide(a, b);
```
Which do you like better? First version is more intuitive as for me. The same logic stands behind `operator`s in c++. One of the mottos in c++ is "Create your classes to function as harmoniously as the built-in types". So let's create harmonious
class complex with support for basic arithmethic.
```c++
class Complex {
	double re {}; // real part, default is 0.0 
	double im {}; // imaginary part, default is 0.0
public:
	Complex(double re, double im) :re{re}, im{im} {}
	
	// just declarations
	friend Complex operator+(const Complex& fst, const Complex& snd);	// friend is a function that could reach
	friend Complex operator-(const Complex& fst, const Complex& snd);	// private members of a class
	friend Complex operator*(const Complex& fst, const Complex& snd);
	friend Complex operator/(const Complex& fst, const Complex& snd);
};

// and now definitions
Complex operator+(const Complex& fst, const Complex& snd)
{
	return {fst.re + snd.re, fst.im + snd.im};
}

Complex operator-(const Complex& fst, const Complex& snd)
{
	return {fst.re - snd.re, fst.im - snd.im};
}

Complex operator*(const Complex& fst, const Complex& snd)
{
	return {fst.re * snd.re - fst.im * snd.im, 	// just formula
		fst.re * snd.im + fst.im * snd.re};
}

Complex operator/(const Complex& fst, const Complex& snd)
{
	double denominator = snd.re * snd.re + snd.im * snd.im;		// another formula
	return {(fst.re * snd.re + fst.im * snd.im) / denominator, 
		(fst.im * snd.re - fst.re * snd.im) / denominator};		
}

// usage
int main()
{
	Complex a {1, 2};
	Complex b {5, 3};
	
	Complex c = a + b;	// 6 + 5i
	Complex d = a - b;	// -4 - 1i
	Complex e = a * b;	// -1 + 13i
	Complex f = a / b;	// 0.323529 + 0.205882i
}
```
Oh, that's good, but what about output, how could we output it?
It turns out that output is an operator too. Remember `std::cout << something` ? That's an right shift operator, but it is used to denote the output, and `std::cout` is just the global instance of class `std::ostream`. So we could just provide this operator for our own class:
```c++
#include <iostream>

class Complex {
	// ...
public:
	// ...
	
	friend std::ostream& operator<<( std::ostream& os, const Complex& cpx);
};

// implementation
std::ostream& operator<<( std::ostream& os, const Complex& cpx)
{
	os << cpx.re;
	( cpx.im < 0 ? os : os << '+' ) << cpx.im << 'i' << '\n';

	return os;
}

int main()
{
	Complex a {1, 2};
	Complex b {5, 3};
	
	std::cout << a + b;	
	std::cout << a - b;
	std::cout << a * b;
	std::cout << a / b;
}
```
There are also left shift operator denoting input, recall `std::cin >> something;`. About different kinds of operators, you can read [here](http://en.cppreference.com/w/cpp/language/operators).

### 1.6 Templates
Let's try to write `add` function from previous item.
```c++
double add(double fst, double snd)
{
	return fst + snd;
}
```
Cool, but this won't work with `int`, and many other types! Templates is a mechanism that allows generalizing of the function, that works with every type that supports `operator+`, here is the notation:
```c++
template <typename T>		// T is the name of a type
T add(const T& fst, const T& snd)	
// using const reference, because it is more efficient for large objects
{
	return fst + snd;	// if T don't support +, it will fail
}

// usage
int main()
{
	add(3, 5);		// int version
	add(3.45f, 5.0f);	// float version
	
	Complex a {1, 2};	// class from previous item
	Complex b {5, 3};
	add(a, b);	// works because of support of operator+
}
```
So this how we do generic code in c++. It saves a lot of time, try it! This approach could be used almost everywhere, for example:
```c++
template <typename T>
class Storage {
	T field;
public:
	Storage( const T& field) :field{field} {}
};

// usage
int main()
{
	Storage<int> st {3};
	Storage<Storage<int>> stst {st};
}
```
So this what happens when you use:
```c++
std::vector<int> vec;
```
There are a lot of usefulness in templates. It is one of the main technics of modern c++ development. Read more, like [this](https://www.geeksforgeeks.org/templates-cpp/) and [that](http://en.cppreference.com/w/cpp/language/templates).

Also the new feature is coming to c++20, named [concepts](https://cppdepend.com/blog/?p=524).

## 2.0 General C++ Syntax
### 2.1 Namespaces

### 2.2 References and Pointers
are used to store the address of the varibale/object in memory. So having the pointer or reference, you could do the same operations as that of object being pointed to.
```c++
int a = 3;
int b = 5;

int* aptr = &a;		// & operator gets the address of variable a
int* bptr = &b;		// int * is a type of pointer to int

int c = *aptr + *bptr;	// * opeartor used to get the value of the object that 
			// is being pointed to
int d = a + b;		// c and d are equal at the end of the day
```
Think of pointer as the abstraction that knows where to find an object, but don't own it.
The references are about the same, but they use more convenient syntax, but some [limitations](https://stackoverflow.com/questions/57483/what-are-the-differences-between-a-pointer-variable-and-a-reference-variable-in) apply. The main difference is that refernce can't be reassigned and must be assigned at initialization:
```c++
int a = 3;
int b = 5;

int& aref = a;		// & means reference type
int& bref = b;	

int c = aref + bref;	// simple addition syntax 

int d = a + b;		// c and d are equal at the end of the day
```
Also pointers are used in arrays like that:
```c++
#include <iostream>

int arr[] = { 9, 5, 8, 2 };		// array storage is contiguous
int size = 4;

for(int i = 0; i < size; i++) std::cout << arr[i] << ' ';	// 9 5 8 2
std::cout << '\n';

int* ptr = arr;		// ptr points to first element of an array
for(int i = 0; i < size; i++) std::cout << *(ptr + i) << ' ';	// 9 5 8 2
std::cout << '\n'

ptr = arr;		// reassignment of pointer, can't be preformed with reference
for(int i = 0; i < size; i++) std::cout << *(ptr++) << ' ';	// 9 5 8 2
std::cout << '\n'
```
This loops are equivalent, moreover first-second are implemented in the same way. First loop is just convenience syntax for second. Notice, that pointers can be incremented. Also there are a special pointer, called `nullptr`.
```c++
double* ptr = nullptr;	// means it points to nowhere

double a = *ptr;	// this is a huge error, DON'T DO THIS
```

### 2.3 Keywords
[Reference](http://en.cppreference.com/w/cpp/keyword)

#### 2.3.1 General Keywords
[`asm`](http://en.cppreference.com/w/cpp/language/asm)
[`auto`](http://en.cppreference.com/w/cpp/language/auto)
[`const`](http://en.cppreference.com/w/cpp/language/cv)
[`constexpr` (*since C++11*)](http://en.cppreference.com/w/cpp/language/constexpr)
[`explicit`](http://en.cppreference.com/w/cpp/language/explicit)
[`export` (*until C++11*)](http://en.cppreference.com/w/cpp/keyword/export)
[`extern` (*language linkage*)](http://en.cppreference.com/w/cpp/language/language_linkage)
[`friend`](http://en.cppreference.com/w/cpp/language/friend)
[`inline`](http://en.cppreference.com/w/cpp/language/inline)
[`mutable`](http://en.cppreference.com/w/cpp/language/cv)
[`noexcept` (*operator*)](http://en.cppreference.com/w/cpp/language/noexcept)
[`noexcept` (*function specifier*)](http://en.cppreference.com/w/cpp/language/noexcept_spec)
[`nullptr`](http://en.cppreference.com/w/cpp/language/nullptr)
[`override`](http://en.cppreference.com/w/cpp/language/override)
[`static` (*class member specifier*)](http://en.cppreference.com/w/cpp/language/static)
[`template`](http://en.cppreference.com/w/cpp/language/templates)
[`this`](http://en.cppreference.com/w/cpp/language/this)
[`virtual` (*function specifier*)](http://en.cppreference.com/w/cpp/language/virtual)
[`virtual` (*base class specifier*)](http://en.cppreference.com/w/cpp/language/derived_class)
[`volatile`](http://en.cppreference.com/w/cpp/language/cv)

#### 2.3.2 Storage Class Specifiers
[Reference](http://en.cppreference.com/w/cpp/language/storage_duration)
* `auto` (*until C++11*)
* `register` (*until C++17*)
* `static`
* `extern`
* `thread_local` (*since C++11*)

#### 2.3.3 `const` and `dynamic` Cast Conversion
* [`const_cast`](http://en.cppreference.com/w/cpp/language/const_cast)
* [`dynamic_cast`](http://en.cppreference.com/w/cpp/language/dynamic_cast)

### 2.4 Preprocessor Tokens
* `#if`: Preprocessor version of `if(...)`
* `#elif`: Preprocessor version of `else if(...)`
* `#else`: Preprocessor version of `else`
* `#endif`: Used to end an `#if`, `#ifdef`, or `#ifndef`
* `defined()`: Returns true if the macro is defined
* `#ifdef`: Same as `#if defined(...)`
* `#ifndef`: Same as `#if !defined(...)`
* `#define`: Defines a text macro. See [here](http://en.cppreference.com/w/cpp/preprocessor/replace) for full explanation, including macro functions and predefined macros.
* `#undef`: Un-defines a text macro
* `#include`: Includes a source file
* `#line`: Changes the current file name and line number in the preprocessor
* `#error`: Prints an error message and stops compilation
* `#pragma`: Non-standard, used instead of header guards (`#ifndef HEADER_H` ...)

### 2.5 Strings (`std::string`)
[Reference](http://en.cppreference.com/w/cpp/string/basic_string)

### 2.6 Iterators (`std::iterator<...>`)
[Reference](http://en.cppreference.com/w/cpp/concept/Iterator)

### 2.7 Exceptions (`std::exception`)
[Reference](http://en.cppreference.com/w/cpp/error/exception)

### 2.8 Lambdas

