---
layout: post
category: blog
title: (Basic C++) 4. Pointer and Memory
snippet: This tutorial following the basic C++ course
tags: [Basic C++]
---
# Pointer definition

In C++, a pointer is a variable that stores the memory address of another variable. This can be either on stack or on the heap.
Pointers are used extensively in C++ for various purposes, including:

- **Memory management:** Pointers allow you to allocate and deallocate memory dynamically, which is useful when working with data structures whose size and shape are not known at compile-time. In modern C++, smart pointers are preferred over raw pointers for memory management, as they provide safer and more efficient memory handling. 

- **Passing functions to other functions:** Pointers can be used to pass functions as arguments to other functions, enabling you to create more flexible and reusable code.

- **Iterating over elements in arrays or other data structures:** Pointers can be used to traverse and manipulate elements in arrays or other data structures.

```c++
// To create the pointer variable, we put a * after the type name
int *p        // the type of p is pointer to int

// Stack Memory
// To initialize a pointer variable, we assign an address to it 
int i{1};     // i is a stack varible
int *p1 = &i; // p1 is a pointer to int. Its value is the address of i.
cout << p1 << endl; // Displays the address of i // p1 = 005DCDD
cout << *p1 << endl; // Displays the value of i // *p1 = 1 

// Heap Memory
int *p2 = new int;     // p2 points to memory allocated from the heap
int *p3 = new int{36}; // p3 points to int with initial value 36 (C++ 11)
// int *p3 = new int(36); //older version of C++

cout << *p2 << endl; // Displays the address of i // *p2 = -8786785657 -> strange value because not initialize
cout <<  *p3 << endl; // Displays the value of i // *p3 = 36

```

___Here's an example ```Pointer.cpp``` that demonstrates the class in C++ bellow:___ 

Rectangle.cpp
{:.filename}
```c++
int main() {
  int num = 10; // A variable of type int
  int* ptr; // A pointer variable that points to an int

  ptr = &num; // Assign the address of num to the pointer

  cout << "Value of num: " << num << endl; // Output: 10
  cout << "Address of num: " << &num << endl; // Output: Memory address of num
  cout << "Value of ptr: " << ptr << endl; // Output: Memory address of num

  // Dereferencing the pointer to access the value it points to
  cout << "Value pointed to by ptr: " << *ptr << endl; // Output: 10

  return 0;
}
```


<div class="tip">
<b>Stack and heap are two types of memory used in computer programs for different purposes.</b>
Here are the key differences between stack and heap memory allocation:
<ul>
<li> <b>Stack Memory Allocation:</b> 
- Stack memory is used for local variables and function call information.

- Memory allocation and deallocation are automatic and managed by the compiler.

- Stack memory is allocated in a contiguous block and is not resizable.

- Access to stack memory is faster compared to heap memory.

- Stack memory is limited and can lead to a stack overflow error if it is filled completely.
</li>

<li> <b>Heap Memory:</b>

    - Heap memory is used for dynamically allocated memory, such as objects and arrays.

    - Memory allocation and deallocation are manual, using new and delete operators or smart pointers.

    - Heap memory is flexible and can be resized.

    - Access to heap memory is slower compared to stack memory.

    - Heap memory can become fragmented as blocks of memory are allocated and freed.
 </li>

</ul>
</div>




# References
1. https://www.w3schools.com/cpp/cpp_pointers.asp
2. https://cplusplus.com/doc/tutorial/pointers/
3. https://www.geeksforgeeks.org/cpp-pointers/
4. https://learn.microsoft.com/en-us/cpp/cpp/pointers-cpp?view=msvc-170
5. https://youtu.be/5OJRqkYbK-4