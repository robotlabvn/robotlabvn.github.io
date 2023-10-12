---
layout: post
category: blog
title: (Multithreading C++) 1. Introduction Concurrency
snippet: This tutorial introduce the Multithreading C+
tags: [Multithreading C++]
---
concurrency_parallel

Concurrency in C++ refers to the execution of multiple tasks or operations simultaneously, either through multithreading or parallelism. C++11, C++14, and C++17 have introduced various features and libraries to support concurrent programming, making it easier to write efficient and scalable code.
-  **Multithreading:** In multithreading, multiple threads of execution run concurrently within a single program, sharing the same memory space. C++ provides a thread class, mutexes, condition variables, and other synchronization primitives to manage thread interactions and ensure data integrity.
-  **Parallelism:** Parallelism involves dividing a task into smaller subtasks that can be executed simultaneously on multiple processing units, such as CPU cores. C++17 introduced parallel algorithms in the Standard Template Library (STL), allowing most STL-based algorithms to be executed sequentially, in parallel, or vectorized

{% include image.html url="/assets/2023-1-1-Multithreading-C++/concurrency_parallel.png" description="Lambda Function Expression" width="80%" %}

C++ multithreading allows for concurrent execution of two or more parts of a program, maximizing CPU utilization. Each part of a multithreaded program is called a thread, which is a lightweight process within a process. Prior to C++11, developers had to use POSIX threads or the <pthreads> library for multithreading, which caused portability issues. C++11 introduced the std::thread class and related functions in the <thread> header, providing a standard language-provided feature set for multithreading. To create a thread in C++, you can use the std::thread class and pass a callable (an executable code) as an argument to its constructor. Once the ```std::thread``` object is created, a new thread is launched, and the code provided by the callable is executed

___Example ```char_find.cpp``` bellow:___ 

char_find.cpp
{:.filename}
```c++
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string str{"Hello world"};
	cout << "String: ";
	
	for (auto c : str)
		cout << c << ",";
	cout << "\n";
	
	auto res = find(cbegin(str), cend(str), 'l');          // Search string for first occurrence of 'l'

	// Check if we found it
	if (res != cend(str)) {
		 // Access the result
		cout << "Found a matching element at index: " << res - str.cbegin() << endl;
	}
	
	cout << "At this point in the string: ";
	for (auto it = res; it != str.cend(); ++it)
		cout << *it;
	cout << endl;
}

```




# References
1. https://www.educative.io/blog/modern-multithreading-and-concurrency-in-cpp
2. https://www.classes.cs.uchicago.edu/archive/2013/spring/12300-1/labs/lab6/
3. Ehttps://livebook.manning.com/book/c-plus-plus-concurrency-in-action/chapter-1/
4. James Raynard, Learn Multithreading with Modern C++ Udemy.
