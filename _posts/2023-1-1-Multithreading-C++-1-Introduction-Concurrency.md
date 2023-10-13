---
layout: post
category: blog
title: (Multithreading C++) 1. Introduction Concurrency
snippet: This tutorial introduce the Multithreading C+
tags: [Multithreading C++]
---

Concurrency in C++ refers to the execution of multiple tasks or operations simultaneously, either through multithreading or parallelism. C++11, C++14, and C++17 have introduced various features and libraries to support concurrent programming, making it easier to write efficient and scalable code.
-  **Multithreading:** In multithreading, multiple threads of execution run concurrently within a single program, sharing the same memory space. C++ provides a thread class, mutexes, condition variables, and other synchronization primitives to manage thread interactions and ensure data integrity.
-  **Parallelism:** Parallelism involves dividing a task into smaller subtasks that can be executed simultaneously on multiple processing units, such as CPU cores. C++17 introduced parallel algorithms in the Standard Template Library (STL), allowing most STL-based algorithms to be executed sequentially, in parallel, or vectorized

{% include image.html url="/assets/2023-1-1-Multithreading-C++/concurrency_parallel.png" description="Concurency Parallel" width="80%" %}

C++ multithreading allows for concurrent execution of two or more parts of a program, maximizing CPU utilization. Each part of a multithreaded program is called a thread, which is a lightweight process within a process. Prior to C++11, developers had to use POSIX threads or the ```<pthreads>``` library for multithreading, which caused portability issues. C++11 introduced the std::thread class and related functions in the ```<thread>``` header, providing a standard language-provided feature set for multithreading. To create a thread in C++, you can use the ```std::thread``` class and pass a callable (an executable code) as an argument to its constructor. Once the ```std::thread``` object is created, a new thread is launched, and the code provided by the callable is executed

{% include image.html url="/assets/2023-1-1-Multithreading-C++/hardware_concurrency.png" description="Concurency" width="80%" %}

## History of C++ Concurrency
C++11 was the first C++ standard to introduce concurrency, including threads, the C++ memory model, conditional variables, and atomic operations. C++11 and C++14 have the basic building blocks for creating concurrent and parallel programs. With C++17, we have the parallel algorithms from the Standard Template Library (STL), which means that most STL-based algorithms can be executed sequentially, parallel, or vectorized


{% include image.html url="/assets/2023-1-1-Multithreading-C++/history_concurrency_C++.png" description="Concurency" width="80%" %}

## Launching a Thread


___Example ```thread_ex.cpp``` bellow:___ 

thread_ex.cpp
{:.filename}
```c++
#include <iostream>
#include <thread>

void threadFunction() {
    std::cout << "This is a separate thread" << std::endl;
}

int main() {
    std::thread newThread(threadFunction);

    std::cout << "This is the main thread" << std::endl;

    newThread.join(); // Wait for the new thread to finish

    std::cout << "All threads have completed their work" << std::endl;

    return 0;
}

```




# References
1. https://www.educative.io/blog/modern-multithreading-and-concurrency-in-cpp
2. https://www.classes.cs.uchicago.edu/archive/2013/spring/12300-1/labs/lab6/
3. Ehttps://livebook.manning.com/book/c-plus-plus-concurrency-in-action/chapter-1/
4. James Raynard, Learn Multithreading with Modern C++ Udemy.
