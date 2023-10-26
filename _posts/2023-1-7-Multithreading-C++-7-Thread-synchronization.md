---
layout: post
category: blog
title: (Multithreading C++) 7. Thread Synchronization 
snippet: This tutorial in series of Multithreading in C++.
tags: [Multithreading C++]
---

# I. Thread Synchronization 

Example coordination between workers

```
Worker A is writing a document
Worker A need an image that Worker B is producing
Worker A cannot coutinue until Worker B has finished
```

Solution is to introduce a manger
```
B is working
A is waiting
B finishes their work
B tells manager
Manager tells A to resume 
A resumes work
```

It is the same with the coordination between threads

```
- One thread fetches the data over the network

- Another thread display a progress bar

- A third thread will process the data when the download is complete
```

{% include image.html url="/assets/2023-1-1-Multithreading-C++/thread_synchronization.png" description="Dead Lock" width="80%" %}

### 1. Communication between threads
```
The threads run concurrently:
- The data fetching thread runs continually
- The progress bar thread waits for information
- The processor thread waits until all the data has been recived
When the download is complete:
- The data fetching thread terminates
- The progress bar thread terminates
- The processor thread runs
```

## 2. Data sharing between threads
```
The downloaded data is shared by all three threads
- The data fetching thread appends to it
- The progress bar thread calculates its size
- The processor thread uses the data
Potential Data Race
- Multiple threads
- Modification
```

## 3. Coordination of Threads
```
We will use to bools to coordinate the threads
- "progress" flag
	- the fletching thread sets this when it has new data
	- the progress bar thread checks this flag
- "complete" flag 
	- the fetching thread sets this when it finishes
	- the other two threads check this flag
- Potential Data Race
	- Multiple threads
	- Modification
- Use mutexes
```

## Hot loop
A hot loop in C++ refers to a section of code that is executed repeatedly and frequently, often in a tight loop.

- We need to lock the mutex while checking a bool

```c++
//In progress bar task function
std::lock_guard data_lck(data_mutex);
while(!update_progress){
}
```

- The thread will run flat out
	- The processor core will will run at 100%
	- Other threads cannot do usefull work
	- Uses a lot of electricity

- Thr fetcher thread can not set the flag

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



# References

4. James Raynard, Learn Multithreading with Modern C++ Udemy.





