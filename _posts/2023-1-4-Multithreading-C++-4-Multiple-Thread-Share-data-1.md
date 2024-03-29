---
layout: post
category: blog
title: (Multithreading C++) 4. Mutex and Multiple Threads working with Share data (Part 1)
snippet: This tutorial introduce the Multithreading C+
tags: [Multithreading C++]
---

# I. Critical section 
In C++, a critical section is a segment of code that is executed by multiple concurrent threads or processes and which accesses shared resources. A critical section can be any section of code where shared resources are accessed, and it typically consists of two parts: the entry section and the exit section.  The entry section is where a process requests access to the critical section, and the exit section is where it releases the resources and exits the critical section.

To prevent data races in C++, critical sections can be protected using synchronization mechanisms such as mutexes, locks, and thread-safe data structures.

- **Mutexes** can be used to protect any shared resource, including variables, data structures, and I/O streams.

- **Locks** are synchronization objects that can be used to protect shared resources from being accessed simultaneously by multiple threads.

- **Thread-safe data** structures are data structures that are designed to be accessed by multiple threads simultaneously without causing data races

# II. Mutex (MUTual EXclusion )
A mutex is a synchronization primitive that can be used to protect shared data from being simultaneously accessed by multiple threads. A mutex is a lockable object that is designed to signal when critical sections of code need exclusive access, preventing other threads with the same access from modifying the shared data. In C++, a mutex is implemented as a class, ```std::mutex```, which provides two member functions: ```lock()``` and ```unlock()```. 

- When a thread locks a mutex, no other thread can access the shared data until the mutex is unlocked. If a thread tries to lock a mutex that is already locked by another thread, the thread will block until the mutex is unlocked. 

- Mutexes can be used to protect shared resources from simultaneous access by multiple threads or processes. Mutexes are used to prevent data races and ensure that only one thread can access the shared data at a time. Mutexes can be expensive to use, and it is essential to use them judiciously to avoid performance degradation. 

- A thread locks the mutex when it enters the critical section.

- A thread unlocks the mutex when it leaves the critical section.

```
Thread Synchroniztion with Mutex
- Thread A locks the mutex
- Thread A enters the critical section
- Thread B, C,.. wait until they can lock the mutex
- Thread A leaves the critical section
- Thread A unlock the mutex
- One of threads B,C,.. can now lock the mutex and enter the critical section.
```
## std::mutex Class
The ```std::mutex ```class is a synchronization primitive in C++ that can be used to protect shared data from being simultaneously accessed by multiple threads. The class provides member functions, ```lock()```, ```try_lock()``` and ```unlock()```, which can be used to lock, tries to lock the mutex -> returns immediately if not successful and unlock the mutex, respectively.


## Example of multiple threads with mutex in C++

___Example ```unscramble.cpp``` bellow:___ 

unscramble.cpp
{:.filename}
```c++
// Use a mutex to avoid scrambled output
#include <iostream>
#include <mutex>
#include <thread>
#include <string>

// Global mutex object
std::mutex task_mutex;

void task(const std::string& str)
{
	for (int i = 0; i < 5; ++i) {
		// Lock the mutex before the critical section
		task_mutex.lock();

		// Start of critical section
		std::cout << str[0] << str[1] << str[2] << std::endl;
		// End of critical section

		// Unlock the mutex after the critical section
		task_mutex.unlock();
	}
}

int main()
{
	std::thread thr1(task, "abc");
	std::thread thr2(task, "def");
	std::thread thr3(task, "xyz");

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
abc
abc
def
def
def
def
def
xyz
xyz
xyz
xyz
xyz
```
{% include image.html url="/assets/2023-1-1-Multithreading-C++/mutex.png" description="Mutex example from James" width="80%" %}

## std::mutex::trylock()

The ```std::mutex::try_lock()``` function is a member function of the std::mutex class in C++ that attempts to lock the mutex without blocking. The function returns immediately and tries to acquire the lock. If the lock is acquired successfully, the function returns true, and if the lock is not acquired, the function returns false. The ```std::mutex::try_lock()``` function can be used to avoid blocking when acquiring a lock on a mutex.

```c++
// Keep trying to get the lock
while(!the_mutex.try_lock()){
	// Could not lock the mutex
	// Try again later
	std::this_thread::sleep_for(100ms);
}
	// Finally locked the mutex
	// Can now execute in the critical section
```

___Example try_lock() the mutex```try_lock_mutex.cpp``` bellow:___ 

try_lock_mutex.cpp
{:.filename}
```c++
// Example of calling try_lock() in a loop until the mutex is locked
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std::literals;

std::mutex the_mutex;

void task1()
{
	std::cout << "Task1 trying to lock the mutex" << std::endl;
	the_mutex.lock();
	std::cout << "Task1 has locked the mutex" << std::endl;
	std::this_thread::sleep_for(500ms);
	std::cout << "Task1 unlocking the mutex" << std::endl;
	the_mutex.unlock();
}

void task2()
{
	std::this_thread::sleep_for(100ms);
	std::cout << "Task2 trying to lock the mutex" << std::endl;
	while (!the_mutex.try_lock()) {
		std::cout << "Task2 could not lock the mutex" << std::endl;
		std::this_thread::sleep_for(100ms);
	}
	std::cout << "Task2 has locked the mutex" << std::endl;
	the_mutex.unlock();
}

int main()
{
	std::thread thr1(task1);
	std::thread thr2(task2);
	
	thr1.join();
	thr2.join();
}
```
Output
{:.filename}
```
Task1 trying to lock the mutex
Task1 has locked the mutex
Task2 trying to lock the mutex
Task2 could not lock the mutex
Task2 could not lock the mutex
Task2 could not lock the mutex
Task2 could not lock the mutex
Task1 unlocking the mutex
Task2 has locked the mutex
```

# III. Internally Synchronized Class
When multiple threads access the same memory location concurrently, and at least one of them modifies that memory location, we need to synchronize these accesses to prevent a data race. 

- The containers in the C++ standard library need to be synchronized and we can lock a mutex before calling any of the member functions on a shared C++ library container to prevent a data race.

- We can also write classes that provide their synchronization, where the class takes the responsibility for preventing the data race. One way to do that is to have a mutex as a data member, and the member functions of this class will lock the mutex before they access any of the class's internal data and then unlock it afterward.

### Wrapper for std::vector

```
+ std::vector acts as a memory location
- We may need to lock a mutex before calling its member function
+ Alternatively, we could write an internally synchronized wrapper for it.
+ A class which
	- Has an std::vector data member
	- Has an std::mutex data member
	- Member functions which lock the mutex before accessing the std::vector
	- Then unlock the mutex after accessing it
+ An internally synchronized class
```
```c++
//Very simplistic thread-safe vector class
class Vector{
	std::mutex mut;			// Mutex as private class data member
	std::vector<int> vec;	// Shared data -mutex protects access to it
	public:
		void push_back(const int& i){
			mut.lock(); 		//Lock the mutex
			vec.push_back(i);	//Critical section
			mut.unlock();		//Unlock the mutex
		}
	};
```

___Example A class which is internally without mutex bellow:___ 

without_mutex.cpp
{:.filename}
```c++
// A class which is internally synchronized
// The member functions lock a mutex before they access a data member
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <chrono>

using namespace std::literals;

class Vector {
	std::mutex mut;
	std::vector<int> vec;
public:
	void push_back(const int& i)
	{
		//mut.lock();

		// Start of critical section
		vec.push_back(i);

		// End of critical section
		//mut.unlock();
	}

	void print() {
		//mut.lock();

		// Start of critical section
		for (auto i : vec) {
			std::cout << i << ", ";
		}

		// End of critical section
		//mut.unlock();
	}
};

void func(Vector& vec)
{
	for (int i = 0; i < 5; ++i) {
		vec.push_back(i);
		std::this_thread::sleep_for(50ms);
		vec.print();
	}
}

int main()
{
	Vector vec;

	std::thread thr1(func, std::ref(vec));
	std::thread thr2(func, std::ref(vec));
	std::thread thr3(func, std::ref(vec));

	thr1.join(); thr2.join(); thr3.join();
}
```

Scramble Ouput
{:.filename}
```
0, 0, 
end print section
0, 0, 
0, 0, 1, 
end print section
end print section
start print section
0, 0, 1, 1, 1, 
end print section
start print section
0, 0, 1, 1, 1, 2, 
end print section
start print section
0, 0, 1, 1, 1, 2, 2, 
end print section
start print section
0start print section, 
0, 0, 1, 1, 1, 2, 2, 2, 
0, end print section
1, 1, 1, 2, 2, 2, 
end print section
start print section
0, 0, 1073744080, 32544, 1, 2, 2, 2, 3, 
end print section
start print section
0, 0, 1073744080, 32544, 1, 2, 2, 2, 3, 3, 
end print section
start print section
0, 0, 1073744080, 32544, 1, 2, 2, 2, 3, 3, 4, 
end print section
start print section
0, 0, 1073744080, 32544, 1, 2, 2, 2, 3, 3, 4, 4, 
end print section
start print section
0, 0, 1073744080, 32544, 1, 2, 2, 2, 3, 3, 4, 4, 4, 
end print section
start print section
start print section0, 0, 1073744080, 32544, 1, 2, 2, 2, 3, 3, 4, 4, 4, 
end print section
0, 0, 1073744080, 32544, 1, 2, 2, 2, 3, 3, 4, 4, 4, 
end print section
```

__Example A class which is internally synchronize bellow:__

internal_sync_class.cpp
{:.filename}
```c++
// A class which is internally synchronized
// The member functions lock a mutex before they access a data member
#include <thread>
#include <mutex>
#include <vector>
#include <iostream>
#include <chrono>

using namespace std::literals;

class Vector {
	std::mutex mut;
	std::vector<int> vec;
public:
	void push_back(const int& i)
	{
		mut.lock();

		// Start of critical section
		vec.push_back(i);

		// End of critical section
		mut.unlock();
	}

	void print() {
		mut.lock();

		// Start of critical section
		for (auto i : vec) {
			std::cout << i << ", ";
		}

		// End of critical section
		mut.unlock();
	}
};

void func(Vector& vec)
{
	for (int i = 0; i < 5; ++i) {
		vec.push_back(i);
		std::this_thread::sleep_for(50ms);
		vec.print();
	}
}

int main()
{
	Vector vec;

	std::thread thr1(func, std::ref(vec));
	std::thread thr2(func, std::ref(vec));
	std::thread thr3(func, std::ref(vec));

	thr1.join(); thr2.join(); thr3.join();
}
```

Stable Ouput
{:.filename}
```
start print section
0, 0, 0, 
end print section
start print section
0, 0, 0, 
end print section
start print section
0, 0, 0, 1, 1, 
end print section
start print section
0, 0, 0, 1, 1, 1, 
end print section
start print section
0, 0, 0, 1, 1, 1, 
end print section
start print section
0, 0, 0, 1, 1, 1, 2, 
end print section
start print section
0, 0, 0, 1, 1, 1, 2, 2, 2, 
end print section
start print section
0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 
end print section
start print section
0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 
end print section
start print section
0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 
end print section
start print section
0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 
end print section
start print section
0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 
end print section
start print section
0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 
end print section
start print section
0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 
end print section
start print section
0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 
end print section
```
# IV. Lock guard
## Mutex problem with the exception is thrown 
To protect a critical section, we can use a mutex or a lock. We lock the mutex before entering the critical section and unlock it afterwards. However, if an exception is thrown while the thread is in the critical section, the code will jump out of the try block into the catch block, and the code that follows will not be executed. This means that the unlock function is **NEVER** called, and the mutex is left in a locked state. 
```c++
try{
	task_mutex.lock(); //Lock the mutex before the critical section
	//Critical section thrown an exception

	task_mutex.unlock(); // NEVER get called
}
catch(std::exeption&e ){
 ....
}
// -> MUTEX will be left locked state -> Error: device or resource busy
```
So, when the exception is thrown, we have the stack unwinding process:

- The destructors are called, for all objects in scope.

- The program flow jumps into the catch handler.

- The unlock() call is never executed, and 

- The mutex remains in a locked state.

When a thread locks a mutex, any other thread that wants to lock that mutex will wait indefinitely, causing the threads to be blocked. If any code has called join() on those blocked threads, such as the``` main() ``` function, then that code will also be blocked. As a result, the entire program will be blocked, and the threads will not be able to proceed. 


<div class="tip">
<b>Drawback of std::mutex:</b>
<ul>
<li> <b>Calling lock() requires corresponding call unlock() </b> If NOT the mutex remaining locked after the thread exits</li>

<li> <b>Unlock must always be called, even if</b>There are multiple paths through the critical section, An exception thrown</li>

<li> <b>Relies to the programmer to get it right</b> </li>

<li> <b>Due to these reasons, we do not normally use std::mutex</b> </li>
</ul>
</div>

## So what should we use? -> Mutex Wrapper Class
A mutex wrapper class is a class that holds a mutex and an associated object, providing a convenient way to lock and unlock the mutex when accessing the object. the wrapper classes for mutexes in C++ provide the following benefits:
- They have a mutex object as a private member and are defined in the same header as the mutex class
- They use the RAII idiom to manage resources, where the resource is a mutex that is locked
- The constructor acquires the resource by locking the mutex, and the destructor releases the resource by unlocking the mutex
- Objects of this class are created on the stack, and when the object goes out of scope, the destructor is called, and the mutex is unlocked
- This guarantees that objects are destroyed when the scope in which they were declared ends, and it is possible to acquire the resource in the constructor and release it in the destructor
- This is even more useful in the presence of exceptions, whose unusual control flow is often the source of resources not being released under exceptional flows

## std::lock_guard
```std::lock_guard``` is a C++ class that provides a convenient RAII-style mechanism for owning a mutex for the duration of a scoped block. ```std::lock_guard``` is a useful tool for synchronizing access to shared resources in a multithreaded environment. It provides a convenient way to lock and unlock a mutex when accessing an object, ensuring that only one thread can access the object at a time. It is simple to use and has less likelihood for incorrect use than other mutex wrapper classes.

__Example use std::lock_guard to avoid scrambled output:__

lock_guard.cpp
{:.filename}
```c++
// Use std::lock_guard to avoid scrambled output
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>

using namespace std::literals;

std::mutex print_mutex;

void task(std::string str)
{
	for (int i = 0; i < 5; ++i) {
		try {
			// Create an std::lock_guard object
			// This calls print_mutex.lock()
			std::lock_guard<std::mutex> lck_guard(print_mutex);

			// Start of critical section
			std::cout << str[0] << str[1] << str[2] << std::endl;

			// Critical section throws an exception
			throw std::exception();
			// End of critical section

			std::this_thread::sleep_for(50ms);
		}  // Calls ~std::lock_guard
		catch (std::exception& e) {
			std::cout << "Exception caught: " << e.what() << '\n';
		}
	}
}

int main()
{
	std::thread thr1(task, "abc");
	std::thread thr2(task, "def");
	std::thread thr3(task, "xyz");

	thr1.join(); thr2.join(); thr3.join();
}
```

Output
{:.filename}
```
abc
Exception caught: std::exception
def
Exception caught: std::exception
def
Exception caught: std::exception
def
Exception caught: std::exception
def
Exception caught: std::exception
def
Exception caught: std::exception
xyz
Exception caught: std::exception
abc
Exception caught: std::exception
xyz
Exception caught: std::exception
xyz
Exception caught: std::exception
xyz
Exception caught: std::exception
xyz
Exception caught: std::exception
abc
Exception caught: std::exception
abc
Exception caught: std::exception
abc
Exception caught: std::exception
```
The exceptions are being caught and different threads are executing. Other threads are able to lock the mutex and perform their own critical section without scrambled output.

## std::unique_lock()
In general, std::lock_guard is simpler and easier to use, while std::unique_lock is more flexible and provides more functionality. If the mutex needs to be locked for the entire scope of a block, std::lock_guard is preferred. If the mutex needs to be locked for only part of the scope of a block or if more advanced functionality is needed, std::unique_lock is preferred.

- It is used to ensure that a mutex is locked for the duration of a critical section, and it is automatically released when the unique_lock object goes out of scope.

- It is more flexible than ```std::lock_guard``` because it can be constructed with or without taking the mutex immediately, and it can adopt a current lock that is already locked by a thread.

- It is useful for synchronizing access to shared resources in a multithreaded environment, and it can be used to avoid deadlocks and complexity that can arise from using too many mutexes.

__Example use std::unique_lock() to avoid scrambled output:__

unique_lock.cpp
{:.filename}
```c++
// Use std::unique_lock to avoid scrambled output
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>

using namespace std::literals;

std::mutex print_mutex;

void task(std::string str)
{
    for (int i = 0; i < 5; ++i) {
		// Create an std::unique_lock object
        // This calls print_mutex.lock()
        std::unique_lock<std::mutex> uniq_lck(print_mutex);
		
		// Start of critical section
        std::cout << str[0] << str[1] << str[2] << std::endl;
		// End of critical section
		
		// Unlock the mutex
		uniq_lck.unlock();

        std::this_thread::sleep_for(50ms);
    } // Calls ~std::unique_lock
}

int main()
{
	std::thread thr1(task, "abc");
	std::thread thr2(task, "def");
	std::thread thr3(task, "xyz");
	
	thr1.join(); thr2.join(); thr3.join();
}
```

Output
{:.filename}
```
abc
def
xyz
abc
def
xyz
abc
def
xyz
abc
def
xyz
abc
def
xyz
```

The ```std::unique_lock``` class has several constructors that allow for different ways of locking a mutex. The second argument of the constructor is optional and specifies the locking strategy. Here are some of the available options:

- ```std::defer_lock:``` The mutex is not locked on construction. The caller must lock the mutex manually using the lock() method.

- ```std::try_to_lock:``` The mutex is locked if possible, but the constructor does not block if the mutex is already locked by another thread. If the mutex is not locked, it is locked by the constructor.

- ```std::adopt_lock:``` The mutex is assumed to be already locked by the calling thread. The constructor does not lock the mutex, but instead adopts the lock.

<div class="tip">
<b>std::lock_guard vs std::unique_lock</b>
<ul>
<li> <b>std::unique_lock is much more flexible, but:</b> Slower and requires slighly more storage</li>

<li> <b>Recommendation</b>use lock_guard to lock mutex for entire scope, unique_lock for unlock wihin the scope, use unique_lock if you need more extra features. </li>

</ul>
</div>
# References
1. https://learn.microsoft.com/en-us/cpp/cppcx/wrl/criticalsection-class?view=msvc-170
2. https://en.cppreference.com/w/cpp/thread/mutex/try_lock
3. https://cplusplus.com/reference/mutex/mutex/try_lock/
4. James Raynard, Learn Multithreading with Modern C++ Udemy.
5. https://blog.andreiavram.ro/cpp-channel-thread-safe-container-share-data-threads/



