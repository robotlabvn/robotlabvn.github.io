---
layout: post
category: blog
title: (Multithreading C++) 3. Multiple Threads
snippet: This tutorial introduce the Multithreading C+
tags: [Multithreading C++]
---

# I. Multiple Threads
 Multithreading in C++ allows concurrent execution of two or more parts of a program for maximum utilization of the CPU. We can create a thread using the std::thread class and wait for a thread using the std::thread::join() function. To create multiple threads, we can use a loop to create multiple thread objects and launch them


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

## Data sharing threads
Sharing data between threads is a common task in multithreading applications. When multiple threads access the same data, there is a risk of data races, which can lead to undefined behavior. To avoid data races, we need to synchronize access to shared data using mutexes, locks, or other synchronization primitives.
Here are some ways to share data between threads in C++:

- **Use mutexes:** Protect shared data with a mutex to ensure that only one thread can access the data at a time. Use std::lock_guard, std::unique_lock, std::shared_lock (C++14), or std::scoped_lock (C++17) to implement this pattern.

- **Use atomic variables:** Atomic variables provide a way to perform lock-free operations on shared data. Atomic variables are guaranteed to be modified atomically, which means that no other thread can access the variable while it is being modified.

- **Use message passing:** Message passing is a technique where threads communicate by sending messages to each other. Each thread has its own private data, and communication between threads is done by sending messages. This technique is used in languages like Go and Erlang, but it can also be implemented in C++ using libraries like Boost.Asio .

- **Use thread-safe containers:** Thread-safe containers provide a way to share data between threads without the need for explicit synchronization. These containers are designed to be used in multithreaded environments and provide thread-safe access to their contents. Examples of thread-safe containers include std::queue, std::vector, and std::map

To share data between threads in C++, the thread function must be able to access the definition of the variable that will hold the shared data. If we are using a global function for the task function, we have to use global or static variables. If we are using member functions of a class, we have to use a static class member, or global or static variables. If the task functions are lambda expressions, then they can capture a local variable by reference. However, if they capture by value, then each lambda expression, each thread, will have its own copy of the shared data, and it will not be able to see any changes that other threads make to their copies. To avoid data races and data corruption, we need to synchronize access to shared data using mutexes, locks, or other synchronization primitives. Threads can interleave their execution and interfere with each other's actions, which is one of the main reasons why writing safe multi-threaded programs is much harder than writing safe single-threaded programs

## Data races
A data race in C++ occurs when at **least two threads access a shared variable simultaneously, and at least one thread tries to modify the variable**. A race condition, on the other hand, is not necessarily bad and can be the reason for a data race. 
{% include image.html url="/assets/2023-1-1-Multithreading-C++/data_race.png" description="Data Race" width="80%" %}

However, a data race is an undefined behavior, and all reasoning about the program makes no sense anymore. When multiple threads access the same memory location concurrently, and at least one of the accesses is for writing, and the threads are not using any exclusive locks to control their accesses to that memory, the order of accesses is non-deterministic, and the computation may give different results from run to run depending on that order. The compiler and optimizer assume that there are no data races in the code and optimize it under that assumption, which may result in crashes or other completely surprising behavior. Debugging data races can be a real challenge and sometimes requires tools such as ThreadSanitizer or Concurrency Visualizer. To avoid data races, we need to synchronize access to shared data using mutexes, locks, or other synchronization primitives. Data races are a common problem in multithreaded programming, 

___Example ```data_races.cpp``` bellow:___ 

data_races.cpp
{:.filename}
```c++
// Unsynchronized threads which make conflicting accesses.
// But where is the shared memory location?
#include <thread>
#include <iostream>

void print(std::string str)
{
	// A very artificial way to display a string!
	for (int i = 0; i < 5; ++i) {
		std::cout << str[0] << str[1] << str[2] << std::endl;
	}
}

int main()
{
	std::thread thr1(print, "abc");
	std::thread thr2(print, "def");
	std::thread thr3(print, "xyz");

	// Wait for the tasks to complete
	thr1.join();
	thr2.join();
	thr3.join();
}
```
Output
{:.filename}
```
abc
abc
abc
adbefc --> Data race (add more data)
def
def
ef     --> Data race (missing data)
xyz
xyz
```
## Data races assignment 

*Write a task function that increments a global int variable 100,000 times in a for loop. Write a program that runs this function in concurrent threads. When all the threads have completed execution, print out the final value of the counter. Increase the number of threads until you see anomalous results.*

Solution

data_races.cpp
{:.filename}
```c++
```

# References
1. https://www.modernescpp.com/index.php/race-condition-versus-data-race/
2. https://en.cppreference.com/w/cpp/language/memory_model
3. https://www.modernescpp.com/index.php/c-core-guidelines-sharing-data-between-threads/
4. James Raynard, Learn Multithreading with Modern C++ Udemy.
5. https://blog.andreiavram.ro/cpp-channel-thread-safe-container-share-data-threads/



