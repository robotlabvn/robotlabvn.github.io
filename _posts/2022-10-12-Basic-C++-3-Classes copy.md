---
layout: post
category: blog
title: (Basic C++) 3. Classes in C++
snippet: This tutorial following the basic C++ course
tags: [Basic C++]
---
# Class definition
A class in C++ is a user-defined data type that contains data members and member functions, which can be accessed and used by creating an instance of that class. The data members can be variables (including other structures and classes), constants, and member functions, also known as methods. The member functions are used to manipulate the data members, and together, these data members and member functions define the properties and behavior of the objects in a class. The access to the members of a class is governed by the three access specifiers: __private__, __protected__, or __public__. By default, access to members of a C++ class is private. The private members are not accessible outside the class; they can be accessed only through methods of the class. The public members form an interface to the class and are accessible outside the class. Instances of a class data type are known as objects and can contain member variables, constants, member functions, and overloaded operators defined by the programmer.

Some of the advantages of using classes in C++ include:

- **Modularity:** Classes provide a way to organize code into logical units, making it easier to understand and maintain.
    
- **Encapsulation:** Classes allow you to hide the implementation details of an object, making it easier to change the implementation without affecting the rest of the program.
    
- **Abstraction:** Classes provide a way to abstract away the details of an object, allowing you to work with the object at a higher level of abstraction.
    
- **Inheritance:** Classes support inheritance, which allows you to create new classes based on existing ones, inheriting their properties and behavior.

However, using classes in C++ also has some disadvantages, such as:

- **Complexity:** Classes can be more complex to work with than simple data types, requiring careful management to avoid issues like memory leaks and dangling references.

- **Overhead:** Classes can add overhead to a program, especially when working with large objects or when using inheritance.

___Here's an example ```Rectangle.cpp``` that demonstrates the class in C++ bellow:___ 

Rectangle.cpp
{:.filename}
```c++
#include <iostream>
using namespace std;

class Rectangle {
    private:
        int width;
        int height;
    public:
        void set_values(int w, int h) {
            width = w;
            height = h;
        }
        int area() {
            return width * height;
        }
};

int main() {
    Rectangle rect;
    rect.set_values(5, 6);
    cout << "Area: " << rect.area() << endl;
    return 0;
}
```

In this example, we define a class called Rectangle that has two __private__ data members, width and height, and two __public__ member functions, set_values and area. The set_values function sets the values of width and height, while the area function calculates and returns the area of the rectangle. In the main function, we create an instance of the __Rectangle__ class called rect, set its values using the set_values function, and then print the area of the rectangle using the area function. This is just a simple example, but classes can be used to represent more complex objects and systems in C++.

<div class="tip">
<b>A note:</b> In general, the public member provide the interface of the class -> "What is does?", example: the phone. On the other hand, the private members provide the implementation of the class -> "How it does it?", example: the function inside the phone. The struct is the same as class, except all the members are public by default.
</div>

# Member function implementation
In C++, a member function is a function that has its definition or prototype within the class definition, just like any other variable. Member functions operate on objects of the class of which they are a member and have access to all the members of the class for that object. There are two ways to define member functions: 
- Inside the class definition or
- Outside the class definition using the scope resolution operator (::)

___Here's an example ```Rectangle.cpp``` example with the member function defined outside the class using the scope resolution operator (::):___ 

Rectangle.cpp
{:.filename}
```c++
#include <iostream>
using namespace std;

class Rectangle {
    private:
        int width;
        int height;
    public:
        void set_values(int w, int h);
        int area();
};

void Rectangle::set_values(int w, int h) {
    width = w;
    height = h;
}

int Rectangle::area() {
    return width * height;
}

int main() {
    Rectangle rect;
    rect.set_values(5, 3);
    cout << "Area: " << rect.area() << endl;
    return 0;
}
```
# Dereferencing a pointer in C++ 

Dereferencing a pointer in C++ allows you to access the value stored at a particular memory address. In the case of the ```this``` pointer, dereferencing it gives you access to the members of the object it points to. This can be done by using the ```*``` operator followed by the member access operator ```->``` or the dot operator ```.```.

___Example of dereferencing the ```this``` pointer to access a member function and a data member___ 

this_pointer.cpp
{:.filename}
```c++
#include <iostream>

class MyClass {
  int data;

public:
  void setData(int value) {
    (*this).data = value;  // Using the dot operator
  }

  int getData() {
    return this->data;  // Using the arrow operator
  }
};

int main() {
  MyClass obj;
  obj.setData(42);
  std::cout << obj.getData() << std::endl;  // Output: 42
  return 0;
}
```
In the above example, the __setData__ function sets the value of the __data__ member using the __this__ pointer and the dot operator. The __getData__ function returns the value of the __data__ member using the __this__ pointer and the arrow operator.

# Special member function in C++

In C++, special member functions are functions that the compiler automatically generates if they are used but not explicitly declared by the programmer. These functions are essential for managing the lifetime, construction, and destruction of objects. The main special member functions are:

- **Default constructor:** A constructor that takes no arguments. The compiler generates it only if no other constructor is explicitly declared.
  - Called after memory has been allocated for an object
  - Initializes the object's data members, using the arguments to the call
  - Can also be used to configure the object before use

- **Destructor:** A function that is called when an object is destroyed. The compiler generates a default destructor if no destructor is explicitly declared.

- **Copy constructor:** A constructor that creates a new object by copying the values from an existing object. The compiler generates a default copy constructor if no copy constructor is explicitly declared.

- **Copy assignment operator:** An operator that assigns the values of one object to another object of the same type. The compiler generates a default copy assignment operator if no copy assignment operator is explicitly declared.

- **Move constructor:** A constructor that creates a new object by "stealing" the resources (e.g., memory) from an existing object. The compiler generates a default move constructor if no move constructor is explicitly declared.

- **Move assignment operator:** An operator that assigns the values of one object to another object by "stealing" the resources from the source object. The compiler generates a default move assignment operator if no move assignment operator is explicitly declared.

___Example that demonstrates the use of special member functions:___ 

special_function.cpp
{:.filename}
```c++
#include <iostream>
#include <string>
#include <utility>

class Person {
  std::string name;

public:
  // Default constructor
  Person() {
    std::cout << "Default constructor called" << std::endl;
  }

  // Parameterized constructor
  Person(const std::string& n) : name(n) {
    std::cout << "Parameterized constructor called" << std::endl;
  }

  // Copy constructor
  Person(const Person& other) : name(other.name) {
    std::cout << "Copy constructor called" << std::endl;
  }

  // Move constructor
  Person(Person&& other) noexcept : name(std::move(other.name)) {
    std::cout << "Move constructor called" << std::endl;
  }

  // Copy assignment operator
  Person& operator=(const Person& other) {
    name = other.name;
    std::cout << "Copy assignment operator called" << std::endl;
    return *this;
  }

  // Move assignment operator
  Person& operator=(Person&& other) noexcept {
    name = std::move(other.name);
    std::cout << "Move assignment operator called" << std::endl;
    return *this;
  }

  // Destructor
  ~Person() {
    std::cout << "Destructor called" << std::endl;
  }
};

int main() {
  Person p1;  // Default constructor called
  Person p2("Alice");  // Parameterized constructor called
  Person p3 = p2;  // Copy constructor called
  Person p4 = std::move(p3);  // Move constructor called
  p1 = p4;  // Copy assignment operator called
  p2 = std::move(p4);  // Move assignment operator called
  return 0;
}
```



# References
1. https://en.wikipedia.org/wiki/C%2B%2B_classes
2. https://www.w3schools.com/cpp/cpp_classes.asp
3. https://www.geeksforgeeks.org/c-classes-and-objects/

4. https://cplusplus.com/doc/tutorial/classes/

5. https://www.programiz.com/cpp-programming/object-class