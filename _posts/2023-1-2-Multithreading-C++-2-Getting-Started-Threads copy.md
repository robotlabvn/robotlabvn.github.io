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
Ouput
{:.filename}
```
Exception caught: std::exception
Hello, Thread!
Finished
```

There are several reasons why we need to use threads and exceptions in C++. Here are some of the main reasons:

- **To improve performance:** Using threads can improve the performance of a program by allowing it to execute multiple tasks simultaneously.

- **To handle errors gracefully:** When working with databases or APIs, it is common to encounter errors related to invalid queries. In such cases, it is important to handle the errors gracefully to prevent the program from crashing. One way to handle such errors is to use a try-catch block to catch any exceptions that may be thrown when executing the query.

- **To prevent program crashes:** When an exception is thrown in a parent thread, it can cause the entire program to crash if not handled properly. By using a try-catch block to catch the exception, the program can continue running and the user can be notified of the error.

- **To transport exceptions between threads:** In some cases, it may be necessary to transport exceptions between threads. The C++ standard supports transporting an exception from one thread to another, enabling you to catch an exception in one thread and then make the exception appear to be thrown in a different thread.

- **To propagate exceptions across threads:** If you need to catch an exception in a worker thread and re-throw it in the main thread that’s waiting for the worker to finish, you can use ```std::future```

# III. Safely destroying an std::thread object
To safely destroy an std::thread object in C++, here are some best practices to follow:

- Call join() or detach(): Before destroying an std::thread object, it is important to ensure that the thread has completed its execution. This can be done by calling join() or detach() on the thread object. If a std::thread object is destroyed without being joined or detached, the program will terminate.

- Use RAII: One way to ensure that an std::thread object is safely destroyed is to use RAII (Resource Acquisition Is Initialization) by creating a wrapper class that manages the thread object. The wrapper class can ensure that the thread is joined or detached before the object is destroyed.

- Use a mutex: Operations on an std::thread object are not thread-safe themselves, so it is important to use a mutex to ensure that only one thread can access the object at a time.

- Use a flag: To stop a thread gracefully, it is recommended to use a flag that is checked periodically by the thread. When the flag is set, the thread can exit gracefully.


## detach()

```join()``` is used to wait for a thread to complete before continuing with the rest of the program, while ```detach()``` allows a thread to continue executing independently. If a ```std::thread``` object is destroyed without being joined or detached, the program will terminate. It is important to use ```join()``` or ```detach()``` to ensure that the executing thread completes its work before continuing in your code.

__join():__

- When join() is called, the calling thread will block until the thread of execution has completed.

- join() is used to wait for a thread to complete before continuing with the rest of the program.

- If a std::thread object is still joinable when it's destroyed, an exception will be thrown.

- join() does not kill the thread; it waits until the thread's main function returns.



__detach():__

- When detach() is called, the thread of execution is "detached" from the thread object and is no longer represented by a thread object.

- detach() allows a thread to continue executing independently, but you can no longer join the thread.

- detach() is used for one-off independent tasks that you don't care about the result of.

- If a std::thread object is destroyed without being joined or detached, the program will terminate

{% include image.html url="/assets/2023-1-1-Multithreading-C++/detach.png" description="Detaching a Thread" width="80%" %}


__Example of a detach__
detach_thread.cpp
{:.filename}
```c++
// std::thread and detach()
#include <thread>
#include <iostream>

// Callable object - thread entry point
void hello()
{
	std::cout << "Hello, Thread!\n";
}

int main()
{
	// Create an std::thread object
	std::thread thr(hello);
	
	// Detach the child thread
	thr.detach();
	
	// Continue executing without waiting for the child thread
}
```
To catch an exception thrown in a parent thread in C++, a **try-catch block** can be used. However, if the parent thread is waiting for a child thread to complete using join(), the exception may be thrown in both the parent and child threads. To handle this situation, the **try-catch block** should be placed around the join() method call. If an exception is thrown in a child thread, it will be propagated to the parent thread, and the parent thread will throw the same exception.

__Safely destroying an std::thread object by join()__
thread_except_safe.cpp
{:.filename}
```c++
// Safely destroying an std::thread object
// when an exception is thrown (verbose)
#include <thread>
#include <iostream>

// Callable object - thread entry point
void hello()
{
	std::cout << "Hello, Thread!\n";
}

int main()
{
	// Create an std::thread object
	std::thread thr(hello);
	
	try {
		// Code that might throw an exception
		throw std::exception();

		// No exception if we got here - call join() as usual
		thr.join();
	}
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
		thr.join();                           // Call join() before thr's destructor is called
	}
} // Calls ~thr()
```
<div class="tip">
<b> But using join() in 2 times is not elegant, we can try other ways bellow</b>
</div>

## std::jthread vs std::thread
```std::jthread``` is a new class introduced in **C++20** that provides the same functionality as std::thread, but with some additional features. Here are some differences between ```std::jthread``` and std::thread:

- **RAII:** ```std::jthread``` follows RAII (Resource Acquisition Is Initialization) by having its destructor call join(). This means that the thread is automatically joined when the ```std::jthread``` object is destroyed, ensuring that the thread has completed its execution before the object is destroyed.
    
- **Requesting thread interruption:** ```std::jthread``` provides a mechanism for requesting that a thread stop executing. This is done using the ```request_stop()``` method, which sets a flag that can be checked by the thread to determine whether it should stop executing.

- **Thread safety:** ```std::jthread``` is thread-safe, meaning that it can be safely accessed by multiple threads at the same time.

- **Ease of use:** ```std::jthread``` provides a simpler and more intuitive interface than ```std::thread``` making it easier to use and less prone to errors.

__A std::jthread object is safely destroyed__
jthread_except_safe.cpp
{:.filename}
```c++
// A std::jthread object is safely destroyed
// when an exception is thrown
// Requires a compiler which supports C++20
#include <thread>
#include <iostream>

// Callable object - thread entry point
void hello()
{
	std::cout << "Hello, Thread!\n";
}

int main()
{
	try {
		// Create an std::jthread object
		std::jthread thr(hello);
		
		// Code that might throw an exception
		throw std::exception();

		// std::jthread's destructor will call join() if necessary
	}
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
	}
}
```

## Use RAII (Resource Acquisition Is Initialization)
One way to ensure that an ```std::thread``` object is safely destroyed is to use RAII (Resource Acquisition Is Initialization) by creating a wrapper class that manages the thread object. The wrapper class can ensure that the thread is joined or detached before the object is destroyed. 

```
+ RAII Solution
	- Wrap the std::thread object inside a class
	- the class's destructor calls join() on the std::thread object.
+ An std::thread object can only be joined once
+ The joinable() member function
	- Return false
	- If join() or detach() have already been called
	- Or if the thread object is not associated with an execution thread
+ Returns true if we need to call join()
```

__Uses a wrapper class for std::thread__
use_RAII__thread_guard.cpp
{:.filename}
```c++
// Uses a wrapper class for std::thread
// Ensures safe destruction when an exception is throw
#include <thread>
#include <iostream>

class thread_guard {
	std::thread thr;
public:
	// Constructor takes rvalue reference argument (std::thread is move-only)
	explicit thread_guard(std::thread&& thr): thr(std::move(thr)) {
	}

	// Destructor - join the thread if necessary
	~thread_guard()
	{
		if (thr.joinable())
			thr.join();
	}

	thread_guard(const thread_guard&) = delete;       // Deleted copy operators prevent copying
	thread_guard& operator=(const thread_guard&) = delete;

	// The move assignment operator is not synthesized
};

// Callable object - thread entry point
void hello()
{
	std::cout << "Hello, Thread!\n";
}

int main()
{
	try {
		std::thread thr(hello);
		thread_guard tguard{std::move(thr)};

		//thread_guard tguard{std::thread(hello)};

		// Code which might throw an exception
		throw std::exception();

	} // Calls ~thread_guard followed by ~thread

	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
	}
}
```
Ouput
{:.filename}
```
Hello, Thread!
Exception caught: std::exception
```
# References
1. https://en.cppreference.com/w/cpp/thread/thread/native_handle
2. https://cplusplus.com/reference/thread/thread/native_handle/
3. https://www.enseignement.polytechnique.fr/informatique/INF478/docs/Cpp/en/cpp/thread/thread/native_handle.html
4. James Raynard, Learn Multithreading with Modern C++ Udemy.
5. https://en.cppreference.com/w/cpp/thread/thread/id
6. https://en.cppreference.com/w/cpp/thread/get_id
7. https://cplusplus.com/reference/thread/thread/id/
8. Good book: C++ Concurrency in Action (Anthony Williams) 
9. https://en.cppreference.com/w/cpp/language/raii



