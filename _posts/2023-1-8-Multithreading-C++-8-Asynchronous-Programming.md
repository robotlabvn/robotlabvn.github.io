---
layout: post
category: blog
title: (Multithreading C++) 9. Asynchronous Programming
snippet: This tutorial in series of Multithreading in C++.
tags: [Multithreading C++]
---

# I. Synchronous and Asynchronous Programming

Synchronous and asynchronous programming are two different approaches to executing code. Here are the key differences between the two: 

- **Synchronous Programming**
Tasks are executed in order, one after the other, and cannot be interrupted until they are finished. Synchronous programs can be slower than asynchronous programs, as tasks must wait for each other to finish before starting.

- **Asynchronous Programming**
Tasks can be executed simultaneously and independently of each other. Asynchronous programming is the multitasker, moving from one to-do to the other and alerting the system when each task is complete.





## Example integer operation with show the data race

__Example ```integer_operation.cpp``` the 10 threads with 100,000 increments that should give a final result of 1 million but the result will diferrent bellow:__

integer_operation.cpp
{:.filename}
```c++
// A shared variable is modified by multiple threads
// Integer operations take a single instruction
// Is there a data race?
#include <thread>
#include <iostream>
#include <vector>

int counter = 0;

void task()
{
    for (int i = 0; i < 100'000; ++i) {
        ++counter;
    }
}

int main()
{
    std::vector<std::thread> tasks;

    for (int i = 0; i < 10; ++i)
        tasks.push_back(std::thread(task));

    for (auto& thr: tasks)
        thr.join();

    std::cout << counter << '\n';
}

```


Output
{:.filename}
```c++
258413 // data races -> the 10 threads with 100,000 increments that should give a final result of 1 million but the result will diferrent
```


# References
1. https://en.cppreference.com/w/cpp/atomic/atomic_flag/atomic_flag
2. https://en.cppreference.com/w/cpp/atomic/atomic_flag
3. https://learn.microsoft.com/en-us/cpp/standard-library/atomic?view=msvc-170
4. James Raynard, Learn Multithreading with Modern C++ Udemy.





