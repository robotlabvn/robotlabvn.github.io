---
layout: post
category: blog
title: (Multithreading C++) 5. Mutex and Multiple Threads working with Share data (Part 2)
snippet: This tutorial introduce the Multithreading C+
tags: [Multithreading C++]
---

# I. Timeout and Mutexes

```std::timed_mutex``` is a C++ class that provides a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads. Here are some key points about ```std::timed_mutex``` 
- It is defined in the <mutex> header and is available since C++11.

- It is a time lockable object that is designed to signal when critical sections of code need exclusive access, just like a regular mutex, but additionally supporting timed try-lock requests.

- It has two additional members: ```try_lock_for``` and ```try_lock_until```, which allow for timed try-lock requests. It is guaranteed to be a standard-layout class.

- All lock and unlock operations on the std::timed_mutex follow a single total order, with all visible effects synchronized between the lock operations and previous unlock operations on the same object.

- It is useful for synchronizing access to shared resources in a multithreaded environment when a thread needs to wait for a certain amount of time to acquire the lock.


## Example of try_lock_for in C++

__Example ```try_lock_for``` bellow:__

try_lock_for.cpp
{:.filename}
```c++
// Example of std::timed_mutex try_lock_for() member function
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

std::timed_mutex the_mutex;

void task1()
{
	std::cout << "Task1 trying to lock the mutex\n";
	the_mutex.lock();
	std::cout << "Task1 locks the mutex\n";
	std::this_thread::sleep_for(5s);
	std::cout << "Task1 unlocking the mutex\n";
	the_mutex.unlock();
}

void task2()
{
	std::this_thread::sleep_for(500ms);
	std::cout << "Task2 trying to lock the mutex\n";

	// Try for 1 second to lock the mutex
	while (!the_mutex.try_lock_for(1s)) {
		// Returned false
		std::cout << "Task2 could not lock the mutex\n";

		// Try again on the next iteration
	}

	// Returned true - the mutex is now locked

	// Start of critical section
	std::cout << "Task2 has locked the mutex\n";
	// End of critical section

	the_mutex.unlock();
}

int main()
{
	std::thread thr1(task1);
	std::thread thr2(task2);

	thr1.join(); thr2.join();
}

```

## Example of try_lock_until in C++

__Example ```try_lock_until``` bellow:__

try_lock_until.cpp
{:.filename}
```c++
// Example of std::timed_mutex try_lock_until() member function
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

std::timed_mutex the_mutex;

void task1()
{
	std::cout << "Task1 trying to get lock\n";
	the_mutex.lock();
	std::cout << "Task1 locks the mutex\n";
	std::this_thread::sleep_for(5s);
	std::cout << "Task1 unlocking the mutex\n";
	the_mutex.unlock();
}

void task2()
{
	std::this_thread::sleep_for(500ms);
	std::cout << "Task2 trying to lock the mutex\n";
	auto deadline = std::chrono::system_clock::now() + 900ms;

	// Try until "deadline" to lock the mutex
	while (!the_mutex.try_lock_until(deadline)) {
		// Returned false
		// Update "deadline" and try again
		deadline = std::chrono::system_clock::now() + 900ms;
		std::cout << "Task2 could not lock the mutex\n";
	}

	// Returned true - the mutex is now locked

	// Start of critical section
	std::cout << "Task2 has locked the mutex\n";
	// End of critical section

	the_mutex.unlock();
}

int main()
{
	std::thread thr1(task1);
	std::thread thr2(task2);

	thr1.join(); thr2.join();
}
```

## Using the std::unique_lock with option try for
__Example ```unique_lock_try_for``` bellow:__

unique_lock_try_for.cpp
{:.filename}
```c++
// Example of std::unique_lock's try_lock_for() member function
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

std::timed_mutex the_mutex;

void task1()
{
	std::cout << "Task1 trying to lock the mutex\n";
	std::lock_guard<std::timed_mutex> lck_guard(the_mutex);
	std::cout << "Task1 locks the mutex\n";
	std::this_thread::sleep_for(5s);
	std::cout << "Task1 unlocking the mutex\n";
}

void task2()
{
	std::this_thread::sleep_for(500ms);
	std::cout << "Task2 trying to lock the mutex\n";

	std::unique_lock<std::timed_mutex> uniq_lck(the_mutex, std::defer_lock);

	// Try for 1 second to lock the mutex
	while (!uniq_lck.try_lock_for(1s)) {
		// Returned false
		std::cout << "Task2 could not lock the mutex\n";

		// Try again on the next iteration
	}

	// Returned true - the mutex is now locked

	// Start of critical section
	std::cout << "Task2 has locked the mutex\n";
	// End of critical section
}

int main()
{
	std::thread thr1(task1);
	std::thread thr2(task2);

	thr1.join(); thr2.join();
}
```

The C++ <chrono> library provides several clock types that can be used to measure time in various ways. Here are some key points about the clocks: The <chrono> library defines three main types of clocks: system_clock, steady_clock, and high_resolution_clock.

- **System_clock measures** Unix Time, which is the time since 00:00:00 Coordinated Universal Time (UTC), Thursday, 1 January 1970, not counting leap seconds. It is the system-wide real-time clock (wall-clock) and has the auxiliary functions to_time_t and from_time_t to convert time points into dates.

- **Steady_clock** provides a monotonic clock that will never be adjusted. It goes at a uniform rate and is the preferred clock to wait for a time duration or until a time point.

- **High_resolution_clock** provides the smallest possible tick period and is useful for measuring short durations.

All clock classes provide access to the current time_point.

# II. Mutiple Reader and Single Writer
Multiple Reader and Single Writer (MRSW) is a common problem in concurrent programming that can be found in many real-world applications. Here are some examples of MRSW in financial and audio/video buffer and database:
- **Financial:**
In a financial system, multiple clients may need to read data from the same database table while only one client can write to it. This is a classic example of MRSW. In a financial trading system, multiple threads may need to read market data while only one thread can write to it.
- **Audio/Video Buffer:**
In an audio or video streaming application, multiple threads may need to read data from the buffer while only one thread can write to it. This is another example of MRSW. In an Icecast audio streaming application, a buffer is always necessary to handle the packet-switched nature of networks
- **Database:**
In a database system, multiple clients may need to read data from the same table while only one client can write to it. This is a classic example of MRSW. In a database system, table buffer performance can be improved by optimizing the buffer size and reducing the number of table accesses.

In a database system, multiple threads may need to read data from the buffer while only one thread can write to it.

# III.Shared Mutexes
```std::shared_mutex``` is a C++ class that provides a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads. Here are some key points about ```std::shared_mutex```:
- It is defined in the ```shared_mutex``` header and is available since C++17.

- It is a type of mutex that allows multiple threads to share ownership of a mutex for non-exclusive access.
It provides two levels of access: shared and exclusive. Multiple threads can acquire shared access, but only one thread can hold exclusive access.

- It is useful for synchronizing access to shared resources in a multithreaded environment when multiple threads need to read the shared resource, but only one thread can write to it.

- It has several member functions, ```lock()``` and ```unlock()``` are used for **exclusive** access, while ```lock_shared()``` and ```unlock_shared()``` are used for **shared** access, ```try_lock()``` and ```try_lock_shared()``` are used to attempt to lock the mutex without blocking.

- All lock and unlock operations on the ```std::shared_mutex``` follow a single total order, with all visible effects synchronized between the lock operations and previous unlock operations on the same object.

```c++
// Share_mutex usage
std::shared_mutex sharemut;
void write(){
	std::lock_guard guard(sharemut); //Write thread with exclusive block
	...
}

void read(){
	std::shared_lock sh_lck(sharemut); // Read thread with share block
}

```

## Share mutex
__Example ```shared_mutex.cpp``` bellow:__

shared_mutex.cpp
{:.filename}
```c++
// Shared mutex example
// Requires C++17
// (for C++14, use std::shared_timed_mutex)
// The write thread uses an exclusive lock
// The read thread uses a shared lock
#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <vector>

std::shared_mutex shmut;

// Shared variable
int x = 0;

void write()
{
	std::lock_guard<std::shared_mutex> lck_guard(shmut);

	// Start of critical section
	++x;
	// End of critical section
}

void read()
{
	std::shared_lock<std::shared_mutex> lck_guard(shmut);

	// Start of critical section
	using namespace std::literals;
	std::this_thread::sleep_for(100ms);
	// End of critical section
}

int main()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 20; ++i)
		threads.push_back(std::thread(read));

	threads.push_back(std::thread(write));
	threads.push_back(std::thread(write));

	for (int i = 0; i < 20; ++i)
		threads.push_back(std::thread(read));

	for (auto& thr : threads)
		thr.join();
}
```

<div class="tip">
<b>Pros and Cons of std::shared_mutex</b>
<ul>
<li> <b>Use more memory than std::mutex</b> Slower than std::mutex</li>

<li> <b>Recommendation</b> Reader threads greatly outnumber of writer threads, and read operations take along time  </li>

</ul>
</div>

# IV. Shared Data Initialization
Shared data can have different forms in a program:
- Global variables can be accessed by any code in the program.

```c++
// Global variable declaration
int a = 5; //Can be accessed from other files by using the extern keyword.

// Function to print the value of the global variable
void printGlobalVariable() {
  std::cout << "The value of the global variable is: " << a << std::endl;
}

```

- Static variables at namespace scope can be accessed by any code that can see their declaration.

```c++
// Static variable declaration at namespace scope
static int a = 5; // Cannot be accessed from other files.

// Function to print the value of the static variable
void printStaticVariable() {
  std::cout << "The value of the static variable is: " << a << std::endl;
}

```

- A class member declared static can be accessed by any code that calls its member functions.

```c++
class MyClass {
  public:
    static int staticVariable;
    static void staticFunction() {
      std::cout << "The value of the static variable is: " << staticVariable << std::endl;
    }
};

int MyClass::staticVariable = 5;
```

- Local variables declared static can be accessed by any code that calls the function containing them.

```c++
void myFunction() {
  // Declare a static local variable
  static int count = 0;

  // Increment the value of the static local variable
  count++;

  // Print the value of the static local variable
  std::cout << "The value of the static local variable is: " << count << std::endl;
}

int main() {
  // Call the function multiple times to see the effect of the static local variable
  myFunction();
}
```

Static local variables in C++11 have been standardized: 

- Only one thread can initialize the variable, and if any other thread reaches that declaration, it will be blocked.
- The second thread must wait until the first thread has finished initializing the variable, and then it will use the initial value that the first thread gave to it.
- All threads will see this variable as having the same initial value, and the threads are all synchronized internally by the implementation, and there is no data race.
- This only applies when initializing the static variable.
- If we want to modify it later on, then it is just like any other shared data, and we have to protect it to prevent a data race.

## Singleton Class
The Singleton design pattern in C++ is a creational design pattern that ensures only one object of its kind exists and provides a single point of access to it for any other code. Singleton has almost the same pros and cons as global variables, and it can be recognized by a static creation method, which returns the same cached object.

### Classical Singleton class -> has data race

classic_singleton.h
{:.filename}
```c++
// Singleton class definition
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

class Singleton {
	// Pointer to unique instance
	static Singleton *single;
	
	// The constructor is private
	Singleton() { std::cout << "Initializing Singleton" << std::endl;}
public:
	// The copy and move operators are deleted
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
	
	// Static member function to obtain the Singleton object
	static Singleton* get_Singleton();
};

#endif //Singleton_H
```

classic_singleton.cc
{:.filename}
```c++
// Classic Singleton class implementation
#include "classic_singleton.h"

// Static member function to obtain the Singleton object
Singleton* Singleton::get_Singleton()
{
    if (single == nullptr)
        single = new Singleton;
    return single;
}
```

classic_singleton_main.cc
{:.filename}
```c++
// Test program for classic Singleton
#include "classic_singleton.h"
#include <thread>
#include <vector>

Singleton* Singleton::single = nullptr;

void task()
{
	Singleton* single = Singleton::get_Singleton();
	std::cout << single << std::endl;
}

int main()
{
	std::vector<std::thread> threads;
	
	for (int i = 0; i < 10; ++i)
		threads.push_back(std::thread(task));
	
	for (auto& thr : threads)
		thr.join();
}
```

### C++11 Singleton Class -> Good practice

cpp11_singleton.h
{:.filename}
```c++
// Singleton class definition
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

class Singleton {
  public:
	// The copy and move operators are deleted
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;
	
	Singleton() { std::cout << "Initializing Singleton\n";}
};

// Function to obtain the Singleton object
Singleton& get_Singleton();

#endif //SINGLETON_H
```

cpp11_singleton.cc
{:.filename}
```c++
// Singleton class implementation (Meyers Singleton)
// Uses C++11's guarantees about initializing static variables
#include "cpp11_singleton.h"

// Function to obtain the Singleton object
Singleton& get_Singleton()
{
    // Initialized by the first thread that executes this code
	static Singleton single;
	return single;
}
```

cpp11_singleton_main.cc
{:.filename}
```c++
// Test program for classic Singleton
// Test program for Meyers Singleton
#include "cpp11_singleton.h"
#include <thread>
#include <vector>

void task()
{
	Singleton& single = get_Singleton();
	std::cout << &single << std::endl;
}

int main()
{
	std::vector<std::thread> threads;
	
	for (int i = 0; i < 10; ++i)
		threads.push_back(std::thread(task));
	
	for (auto& thr : threads)
		thr.join();
}
```

# V. Thread-local variable lifetimes
## Thread-local variable
In C++, thread-local variables are variables that have thread storage duration, meaning that each thread that accesses a thread-local variable has its own, independently initialized copy of the variable.
```
Global and namespace scope
- Always constructed at or befor the first use in a translation unit
- It is safe to use them in dynamic libraries (DLLs)

Local variables
- Initialized in the same way as static local variables

In all cases
- Destroyed when the thread completes its execution
```

## Example 
We can make a random number engine thread-local, this ensures that each thread generates the same sequence -> Useful for testing.

```c++
//Thread-local random number engine
std::thread_local mt19937 mt;
void func()
{
	std::uniform_real_distribution<double>dist(0,1); //Double in range 0 to 1
	for(int i =0; i <10; i++){						//Generate 10 numbers
		std::out << dist(mt) << ", ";
	}
}
```

__Thread-local random number engine ```thread_local.cpp``` bellow:__

thread_local.cpp
{:.filename}
```c++
// Thread-local random number engine
// Ensures that each thread generates the same sequence
// (Useful for testing)
#include <random>
#include <thread>
#include <iostream>

// Thread-local random number engine
thread_local std::mt19937 mt;

void func()
{
	std::uniform_real_distribution<double> dist(0, 1);   // Doubles in the range 0 to 1

	for (int i = 0; i < 10; ++i)                         // Generate 10 random numbers
		std::cout << dist(mt) << ", ";
}

int main()
{
	std::cout << "Thread 1's random values:\n";
	std::thread thr1(func);
	thr1.join();

	std::cout << "\nThread 2's random values:\n";
	std::thread thr2(func);
	thr2.join();
	std::cout << '\n';
}
```

# VI. Lazy Initialization
Lazy initialization is a technique that delays the creation of an object or the calculation of a value until the first time it is needed. It is useful when the creation of the object is expensive, and you want to defer it as late as possible, or even skip it entirely.
# VII. Double-checked Locking
Double-checked locking is used to reduce the overhead of acquiring a lock by testing the locking criteria first and acquiring the lock only if the check indicates that locking is required. It is commonly used for lazy initialization, which is a tactic for delaying the object initialization until the first time it is accessed. In multi-threaded environments, initialization is usually not thread-safe, so locking is required to protect the critical section. Since only the first access requires locking, double-checked locking is used to avoid locking overhead of subsequent accesses


# References
1. https://en.cppreference.com/w/cpp/thread/timed_mutex
2. https://cplusplus.com/reference/mutex/timed_mutex/
3. https://en.cppreference.com/w/cpp/thread/timed_mutex/try_lock_until
4. James Raynard, Learn Multithreading with Modern C++ Udemy.
5. https://en.cppreference.com/w/cpp/chrono/system_clock
6. https://en.cppreference.com/w/cpp/chrono
7. https://en.cppreference.com/w/cpp/thread/shared_mutex
8. https://en.cppreference.com/w/cpp/thread/shared_mutex/lock
9. https://refactoring.guru/design-patterns/singleton/cpp/example
10. https://en.wikipedia.org/wiki/Lazy_initialization




