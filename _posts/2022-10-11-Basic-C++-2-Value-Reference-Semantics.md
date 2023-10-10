---
layout: post
category: blog
title: [Basic C++] 2. Value and Reference Semantic in C++ 
snippet: This tutorial following the basic C++ course
tags: [Basic C++]
---

In C++, there are two main approaches to handling data and objects: value semantics and reference semantics. These approaches determine how objects are accessed, copied, and modified.

- **Value Semantics:** In value semantics, objects are treated as independent entities with their own copies of data. When an object is passed as an argument to a function or assigned to another object, a new copy of the object's data is created. Modifying the copy does not affect the original object. Value semantics are the default in C++, and they are used for built-in types and user-defined types that do not explicitly use reference semantics.
    
- **Reference Semantics:** In reference semantics, objects are not copied when passed as arguments or assigned to other objects. Instead, a reference or pointer to the original object is used. Any modifications made to the object through the reference or pointer will affect the original object. Reference semantics provide more efficient access to objects and are often used for large objects or when the original object needs to be modified.

___Here's an example ```value_reference_sematics.cpp``` that demonstrates the difference between value and reference semantics in C++ bellow:___ 

value_reference_sematics.cpp
{:.filename}
```c++
#include <iostream>

void modifyValue(int value) {
    value = 10;
}

void modifyReference(int& value) {
    value = 10;
}

int main() {
    int x = 5;

    // Value semantics
    modifyValue(x);
    std::cout << "After modifyValue: " << x << std::endl;  // Output: 5

    // Reference semantics
    modifyReference(x);
    std::cout << "After modifyReference: " << x << std::endl;  // Output: 10

    return 0;
}
```
# Pros and Cons of Value Semantics:
## Pros of Value Semantics:

- **Speed:** Value semantics can be faster in certain situations because accessing an object is usually more frequent than copying the object. With value semantics, you have an actual object, which can be accessed directly, rather than a pointer to an object that requires an extra level of indirection.

- **Simplicity:** Value semantics provide a simpler and more intuitive way of working with objects. Each object has its own copy of data, making it easier to reason about the program's behavior and avoid issues like dangling references or memory leaks.

## Cons of Value Semantics:

- **Memory Overhead:** Value semantics can lead to increased memory usage when working with large objects. Each copy of an object requires its own memory space, which can be inefficient in terms of memory usage.

- **Copying Overhead:** Copying objects with value semantics can be expensive, especially for large objects. This overhead can impact performance, especially in situations where objects are frequently copied.

- **Lack of Dynamic Binding:** Value semantics do not provide dynamic binding, which means that when you pass an object by value, you lose the ability to access derived class functionality through a base class pointer or reference. Dynamic binding is only available when you pass by pointer or pass by reference.

# Pros and Cons of Semantics:
## Pros of Reference Semantics:

- **Flexibility:** Reference semantics provide flexibility and dynamic binding. When you pass an object by reference or by pointer, you can access derived class functionality through a base class pointer or reference, enabling polymorphism and runtime flexibility.

- **Efficiency:** Passing by reference is more efficient than passing by value because it avoids the overhead of copying the entire object. In general, using references and pointers is encouraged for better performance.

- **Clarity:** References can provide clearer code semantics in some situations. For example, when a function modifies its argument, using a reference makes it more obvious that the argument is being passed destructively.

## Cons of Reference Semantics:

- **Indirection:** Reference semantics add an extra layer of indirection to access the object's data. This can lead to slightly slower performance compared to value semantics, especially for small objects where the overhead of indirection is more significant than the cost of copying the object. 

- **Complexity:** References and pointers can be more complex to work with than simple values. They require careful management to avoid issues like dangling references or memory leaks.

<div class="tip">
<b>A note:</b> In general, value semantics are suitable for situations where the benefits of having an actual object outweigh the potential drawbacks of increased memory usage and copying overhead. They are often used for small objects, local objects, and objects that do not require dynamic binding. reference semantics are suitable for situations where the benefits of flexibility and efficiency outweigh the potential drawbacks of indirection and complexity. They are often used for large objects, objects that require dynamic binding, and situations where the cost of copying the object is high.
</div>



# References
1. https://isocpp.org/wiki/faq/value-vs-ref-semantics
2. https://akrzemi1.wordpress.com/2012/02/03/value-semantics/
3. https://www.oreilly.com/library/view/c-high-performance/9781787120952/2691c361-dd30-4733-aa24-b66edffd8968.xhtml
4. http://bioinfo3d.cs.tau.ac.il/group/c++-faq/value-vs-reference-semantics.html