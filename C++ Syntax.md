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
		- [1.3 Polymorphism](#13-polymorphism)
		- [1.4 Templates](#14-templates)
		- [1.5 Constructor/Destructor/Copy Constructor](#15-constructordestructorcopy-constructor)
			- [1.5.1 Use of `explicit` in Constructors](#151-use-of-explicit-in-constructors)
		- [1.6 Initialization Lists](#16-initialization-lists)
		- [1.7 Operator Overloading](#17-operator-overloading)
	- [2.0 General C++ Syntax](#20-general-c-syntax)
		- [2.1 Namespaces](#21-namespaces)
		- [2.2 References/Pointers](#22-referencespointers)
		- [2.3 Keywords](#23-keywords)
			- [2.3.1 `const`](#231-const)
			- [2.3.2 `volatile`](#232-volatile)
			- [2.3.3 `inline`](#233-inline)
		- [2.4 Strings (find, erase, etc)](#24-strings-find-erase-etc)
		- [2.5 Iterators](#25-iterators)
		- [2.6 Exceptions](#26-exceptions)

<!-- /TOC -->


## 1.0 C++ Classes
### 1.1 Class Syntax
#### 1.1.1 Class Declaration (`.h` file)
Here's a simple class representing a polygon, a shape with any number of sides.

The class *declaration* typically goes in the `.h` file. The *declaration* gives the class name, any classes it may extend, declares the members and methods, and declares which members/methods are public, private, or protected.
```c++
class Polygon {

// Private members and methods are only accessible via methods in the class definition
// Another option is 'protected', which are members and methods only accessible in the class definition or by classes who extend this class
private:
    int num_sides;    	// Number of sides
    std::string name    // Name of the polygon

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
#include "Polygon.h"    // <--- Obtains the class declaration

// Constructor
// You must scope the method definitions with the class name (Polygon::)
Polygon::Polygon(const int num_sides, const std::string &name) {
    this->num_sides = num_side;	// 'this' refers to the instance of the class. Members are accessed via pointers
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

**Example:** the class `Rectangle` can inherit the class `Polygon`. You would then say that `Rectangle` extends `Polygon`, or that class `Rectangle` is a sub-class of `Polygon`. In plain English, this means that a `Rectangle` is a more specialized version of a `Polygon`.

#### 1.2.1 `Rectangle` Declaration (`.h` file)
```c++
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
Rectangle::Area(void) const {
	return this->length * this->width;
}
```

#### 1.2.3 `Rectangle` Utilization (Another `.cpp` file)
```c++
#include "Rectangle.h"

int main(int argc, char *argv[]) {
	Rectangle rectangle = Rectangle("Square", 6, 6);

	// Prints "Square has 4 sides, and an area of 36"
	std::cout << rectangle.GetName() << " has " << rectangle.GetNumSides() << " sides, and an area of " << rectangle.Area() << std::endl;
}
```

### 1.3 Polymorphism

### 1.4 Constructor/Destructor/Copy Constructor
#### 1.4.1 Use of `explicit` in Constructors
The keyword `explicit` should be used in single-argument constructors to avoid the following situation. Consider the class `Array`:
```c++
class Array {
public:
	Array(int size) {
		this->size = size;
	}

private:
	int size;
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
public:
	explicit Array(int size) {
		this->size = size;
	}
};
```

Now you can only use the print method as follows:
```c++
array.Print(Array(12345));
```

### 1.4 Initialization Lists

### 1.5 Operator Overloading
[Reference](http://en.cppreference.com/w/cpp/language/operators)

### 1.6 Templates
[Reference](http://en.cppreference.com/w/cpp/language/templates)

## 2.0 General C++ Syntax
### 2.1 Namespaces

### 2.2 References and Pointers

### 2.3 Keywords
[Reference](http://en.cppreference.com/w/cpp/keyword)

#### 2.3.1 General Keywords
[`asm`](http://en.cppreference.com/w/cpp/language/asm)
[`auto`](http://en.cppreference.com/w/cpp/language/auto)
[`cont`](http://en.cppreference.com/w/cpp/language/cv)
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

### 2.4 Strings (`std::string`)
[Reference](http://en.cppreference.com/w/cpp/string/basic_string)

### 2.5 Iterators (`std::iterator<...>`)
[Reference](http://en.cppreference.com/w/cpp/concept/Iterator)

### 2.6 Exceptions (`std::exception`)
[Reference](http://en.cppreference.com/w/cpp/error/exception)
