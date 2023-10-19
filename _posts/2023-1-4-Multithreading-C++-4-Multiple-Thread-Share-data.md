---
layout: post
category: blog
title: (Multithreading C++) 4. Multiple Threads working with Share data
snippet: This tutorial introduce the Multithreading C+
tags: [Multithreading C++]
---

# I. Critical section 
In C++, a critical section is a segment of code that is executed by multiple concurrent threads or processes and which accesses shared resources. A critical section can be any section of code where shared resources are accessed, and it typically consists of two parts: the entry section and the exit section.  The entry section is where a process requests access to the critical section, and the exit section is where it releases the resources and exits the critical section.

To prevent data races in C++, critical sections can be protected using synchronization mechanisms such as mutexes, locks, and thread-safe data structures.

- **Mutexes** can be used to protect any shared resource, including variables, data structures, and I/O streams.

- **Locks** are synchronization objects that can be used to protect shared resources from being accessed simultaneously by multiple threads.

- **Thread-safe data** structures are data structures that are designed to be accessed by multiple threads simultaneously without causing data races

# II. Mutex


## Example of multiple threads in C++

___Example ```multiple_threads.cpp``` bellow:___ 

multiple_threads.cpp
{:.filename}
```c++
// Example of starting multiple threads
#include <iostream>
#include <thread>
#include <chrono>

void hello(int num)
{
	// Add a delay
	std::this_thread::sleep_for(std::chrono::seconds(num));
	std::cout << "Hello from thread " << num << '\n';
}

int main() {
	// Start 3 threads
	std::cout << "Starting 3 threads:\n";
	std::thread thr1(hello, 1);
	std::thread thr2(hello, 2);
	std::thread thr3(hello, 3);
	
	// Wait for the threads to finish
	thr1.join();
	thr2.join();
	thr3.join();
}
```
Output
{:.filename}
```
Hello from thread 1
Hello from thread 2
Hello from thread 3
```

<div class="tip">
<b> But using join() in 2 times is not elegant, we can try other ways bellow</b>
</div>


# References
1. https://learn.microsoft.com/en-us/cpp/cppcx/wrl/criticalsection-class?view=msvc-170

4. James Raynard, Learn Multithreading with Modern C++ Udemy.
5. https://blog.andreiavram.ro/cpp-channel-thread-safe-container-share-data-threads/



