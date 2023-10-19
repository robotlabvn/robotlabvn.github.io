---
layout: post
category: blog
title: (Multithreading C++) 2. Getting Started with Threads
snippet: This tutorial introduce the Multithreading C+
tags: [Multithreading C++]
---

# I. System Thread interface
The C++ thread class uses the system implementation to perform threading, and there are situations where the system implementation needs to be used directly. This is because the C++ standard is designed to be available on every possible machine, and some systems are limited. Some useful features that are **NOT** available in standard C++ include setting the priority of a thread. Setting the priority of a thread can be useful when a thread is doing something important or needs to be done quickly. On the other hand, setting a lower share of processor time for a thread can be useful when the thread is doing something that is not very important and can wait. It is possible to pin a thread to a specific processor core, which is useful in finance, where a dedicated processor core and a thread for each stock ticker are used to guarantee that the code managing each ticker symbol is always running and always available. In C++11 threads, setting CPU affinity programmatically is possible using the ```native_handle``` method of a ```std::thread```.

## 1. native_handle() in C++
The ```native_handle()``` function in C++ is a member function of the ```std::thread``` class that returns the implementation-defined underlying thread handle. This handle can be used to access implementation-specific information associated with the thread. The ```native_handle() ```function can be used to enable real-time scheduling of C++ threads on a POSIX system.


## Example of native_handle() in C++

___Example ```native_handle.cpp``` bellow:___ 

native_handle.cpp
{:.filename}
```c++
// Example with thread handle
#include <thread>
#include <iostream>

// Task function
void hello() {
	std::cout << "Hello, Thread!" << std::endl;
}

int main() {
	// Create an std::thread object
	std::thread thr(hello);

	// Display the child thread's native handle
	std::cout << "Hello thread has native handle " << thr.native_handle() << '\n';

	// Wait for the thread to complete
	thr.join();

	// Display the child thread's native handle again
	std::cout << "Hello thread now has native handle " << thr.native_handle() << '\n';
}

```
Output
{:.filename}
```
Hello thread has native handle 000000EC -> Has a pointer,  the thread object is connected
Hello, Thread!
Hello thread has native handle 00000000 -> Reset the pointer, the thread object is not connected to any execution thread.
```
## 2. std::thread ID
The std::thread::id class is a lightweight, trivially copyable class that serves as a unique identifier of ```std::thread``` and ```std::jthread```. The ```std::thread::get_id()``` function is an observer function that returns the id of the current thread. The ```std::thread::id``` class can be used to identify a thread associated with a specific object.

## Example of thread ID in C++

___Example ```thread_id.cpp``` bellow:___ 

thread_id.cpp
{:.filename}
```c++
// Example with thread ID
#include <thread>
#include <iostream>

// Task function
// Displays the thread's ID
void hello() {
	std::cout << "Hello from thread with ID " << std::this_thread::get_id() << '\n';
}

int main() {
	// Display the main thread's ID
	std::cout << "Main thread has ID " << std::this_thread::get_id() << '\n';
	
	// Create an std::thread object
	std::thread thr(hello);
	
	// Display the child thread's ID
	std::cout << "Hello thread has ID " << thr.get_id() << '\n';
	
	// Wait for the thread to complete
	thr.join();
	
	// Display the child thread's ID again
	std::cout << "Hello thread now has ID " << thr.get_id() << '\n';
}
```

## 3. Pausing Thread with sleep_for()
In C++, the ```std::this_thread::sleep_for()``` function can be used to pause the current thread for a specified duration. The function takes a single argument that specifies the duration of time for which the execution of the thread must be suspended. 

## Example of pausing thread sleep_for

___Example ```thread_sleep.cpp``` bellow:___ 

thread_sleep.cpp
{:.filename}
```c++
// Example of pausing a thread
#include <thread>
#include <iostream>

using namespace std::literals;

void hello() {
	//std::this_thread::sleep_for(std::chrono::seconds(2));
	std::this_thread::sleep_for(2s);
	std::cout << "Hello, Thread!\n";
}

int main() {
	// Create an std::thread object
	std::cout << "Starting thread...\n";
	std::thread thr(hello);
	
	// Wait for the thread to complete
	thr.join();
}
```

# II. C++ Thread Class
RAII (Resource Acquisition Is Initialization) is a C++ programming technique that binds the life cycle of a resource that must be acquired before use (e.g., memory, threads) to the lifetime of an object. The idea is that the resource is acquired during object creation and released during object destruction, ensuring that the resource is always properly managed and preventing resource leaks.
```std::thread``` does not follow RAII principles, but there have been proposals to modify it to do so. In the meantime, users of ```std::thread ```should make sure to join or detach the thread before the ```std::thread``` object is destroyed to prevent program termination.

This means that the class takes ownership of the resource in its constructor and releases it in its destructor. Examples of classes that follow this idiom include ```unique_ptr```, which owns allocated memory, and ```fstream```, which owns a file handle. Similarly, the ```std::thread``` class owns an execution thread, and only one object can be bound to a system execution thread at any given time. Therefore, it is not possible to copy ```std::thread``` objects because doing so would result in two objects being bound to the same system resource simultaneously.

## std::thread and Move Semantics
The std::thread class is designed to be move-only, which means that we can move objects but not copy them. When we move an object, we transfer ownership of the execution thread to the new object. For example, if we move object "a" into object "b", then object "b"object "b" now becomes the owner of the execution thread, and we need to call join on object "b", not object "a". Object "a" is now empty. It is not associated with any execution thread, and we should not call ```join()``` on it.

## Passing a std::thread Object
When passing a std::thread object as a function argument, it is necessary to use **pass by move**. If a named object (an lvalue) is being passed, it must be put inside a call to ```std::move()``` to cast it to an rvalue. Alternatively, a temporary std::thread object can be passed. This is because ```std::thread``` objects are move-only, meaning that they can be moved but not copied. 

```c++
//Function talking a thread object as argument
void func(std::thread thr);

//Pass a named object
//Use std::move() to cast it to rvalue
std::thread thr(..);
func(std::move(thr));

//Pass a temporary object
func(std::thread(...));
```
__Example of passing a std::thread object to a function__

pass_thread_by_move.cpp
{:.filename}
```c++
// Example of passing a std::thread object to a function
#include <thread>
#include <iostream>

// The task function
void hello() {
	using namespace std::literals;
	std::this_thread::sleep_for(1s);
	std::cout << "Hello, Thread!\n";
}

// Function taking a thread object as argument
// The object must be moved into the argument
void func(std::thread thr) { // it is better practice to add &&in the: void func(std::thread&& thr) to make sure you input the rvalue. 
	std::cout << "Received thread with ID " << thr.get_id() << std::endl;

	// The function argument now "owns" the system thread
	// It is responsible for calling join()
	thr.join();
}

int main() {
	// std::thread is a move-only object
	std::thread thr(hello);

	// Display the child thread's ID
	std::cout << "Hello thread has ID " << thr.get_id() << '\n';

	// Pass a named object using std::move()
	func(std::move(thr));

	// Pass a temporary object
	//func(std::thread(hello));
}
```

Ouput
{:.filename}
```
Hello thread has ID 19324 --> Same ID
Received thread with ID 19324 --> Same ID
Hello, Thread! --> reveal after 1s
```
## Returning a std::thread Object

```c++
//Function returning a std::thread object
std::thred func(){
	//Return a local variable
	std::thread thr(..);
	// --> DON'T do that return std::move(thr); -> make compiler confuse

	//Return a temporary object
	return std::thread(..) ;
}	
```

return_thread.cpp
{:.filename}
```c++
// Example of returning a std::thread object from a function
#include <thread>
#include <iostream>
#include <chrono>

// Task function for the thread
void hello() {
	std::cout << "Hello, Thread!\n";
}

// Function returning a std::thread object
std::thread func() {
	// Start the thread
	std::thread thr(hello);

	// Return a local variable
	return thr;

	// Return a temporary object
	// return std::thread(hello);
}

int main() {
	// Call a function which return an std::thread object
	std::thread thr = func();
	std::cout << "Received thread with ID " << thr.get_id() << '\n';

	// Our thr object now "owns" the system thread
	// It is responsible for calling join()
	thr.join();
}
```

Ouput
{:.filename}
```
Received thread with ID 19324 
Hello, Thread! 
```
## Threads and Exceptions
When an exception is thrown in a single-threaded code, the destructors are called for all the objects in the scope where the exception is thrown. The program will then try to find a suitable handler and move up the stack to destroy all the objects there. If it reaches the top of the stack without finding a handler, it will terminate the program. The process is similar with threads, but each thread has its own execution stack. If the program reaches the top of the thread's execution stack without finding a handler, it will terminate the entire program. With the std::thread class, there is no way for other threads in the program to catch the exception.
When working with threads and exceptions in C++, there are several things to keep in mind.:

- Main will not catch exceptions thrown from other threads.
- The C++ standard supports transporting an exception between threads.
- When a thread throws an exception, it is not caught by main
- The current exception is said to be in flight from the time it's thrown until the exception handler that catches it returns
- If the program gets to the top of the thread's execution stack without finding a handler, then it will terminate the entire program
- With the std::thread class, there is no way for other threads in the program to catch the exception.
- To handle an exception, a try/catch block can be used in the thread where the exception is thrown.

__Example of a thread which throws an exception__
exceptions_thread.cpp
{:.filename}
```c++
// Example of a thread which throws an exception
#include <thread>
#include <iostream>

// Task function
void hello() {
	try {
		// Throw an exception
		throw std::exception();
	}
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
	}
	std::cout << "Hello, Thread!\n";
}

int main() {
	// Create an std::thread object
	std::thread thr(hello);
	thr.join();

	// Check that the program is still running
	std::cout << "Finished\n";
}
```


# References
1. https://en.cppreference.com/w/cpp/thread/thread/native_handle
2. https://cplusplus.com/reference/thread/thread/native_handle/
3. https://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/thread/thread/native_handle.html
4. James Raynard, Learn Multithreading with Modern C++ Udemy.
5. https://en.cppreference.com/w/cpp/thread/thread/id
6. https://en.cppreference.com/w/cpp/thread/get_id
7. https://cplusplus.com/reference/thread/thread/id/



