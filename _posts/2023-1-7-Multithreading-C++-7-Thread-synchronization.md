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

## Hot loop Avoidance
- To avoid it, unlock the mutex inside the loop

```
std::unique_lock<std::mutex> data_lck(data_mutex);

while(!updata_progress){
	data_lck.unlock();
	std::this_thread::sleep_for(10ms);
	data_lck.lock();
}
```

- Sleeping allows other threads to use the core

- The fetcher thread can set the flag





## Example threads coordination practical

__Example ```progress_bar.cpp``` bellow:__

progress_bar.cpp
{:.filename}
```c++
// Simulation of a program which performs a download
//
// One thread featches the data
// Another thread displays a progress bar
// A third thread processes the data when the download is complete
//
// Implemented using bools to communicate between the threads
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>

using namespace std::literals;

// Shared variable for the data being fetched
std::string sdata;

// Flags for thread communication
bool update_progress = false;
bool completed = false;

// Mutexes to protect the shared variables
std::mutex data_mutex;
std::mutex completed_mutex;

// Data fetching thread
void fetch_data()
{
	for (int i = 0; i < 5; ++i) {
		std::cout << "Fetcher thread waiting for data..." << std::endl;
		std::this_thread::sleep_for(2s);

		// Update sdata, then notify the progress bar thread
		std::lock_guard<std::mutex> data_lck(data_mutex);
		sdata += "Block" + std::to_string(i+1);
		std::cout << "sdata: " << sdata << std::endl;
		update_progress = true;
	}

	std::cout << "Fetch sdata has ended\n";

	// Tell the progress bar thread to exit
	// and wake up the processing thread
	std::lock_guard<std::mutex> completed_lck(completed_mutex);
	completed = true;
}

// Progress bar thread
void progress_bar()
{
	size_t len = 0;

	while (true) {
		std::cout << "Progress bar thread waiting for data..." << std::endl;

		// Wait until there is some new data to display
		std::unique_lock<std::mutex> data_lck(data_mutex);
		while (!update_progress) {
			data_lck.unlock();
			std::this_thread::sleep_for(10ms);
			data_lck.lock();
		}

		// Wake up and use the new value
		len = sdata.size();

		// Set the flag back to false
		update_progress = false;
		data_lck.unlock();

		std::cout << "Received " << len << " bytes so far" << std::endl;

		// Terminate when the download has finished
		std::lock_guard<std::mutex> completed_lck(completed_mutex);
		if (completed) {
			std::cout << "Progress bar thread has ended" << std::endl;
			break;
		}
	}
}

void process_data()
{
	std::cout << "Processing thread waiting for data..." << std::endl;

	// Wait until the download is complete
	std::unique_lock<std::mutex> completed_lck(completed_mutex);   // Acquire lock

	while (!completed) {
		completed_lck.unlock();
		std::this_thread::sleep_for(10ms);
		completed_lck.lock();
	}

	completed_lck.unlock();

	std::lock_guard<std::mutex> data_lck(data_mutex);
	std::cout << "Processing sdata: " << sdata << std::endl;

	// Process the data...
}

int main()
{
	// Start the threads
	std::thread fetcher(fetch_data);
	std::thread prog(progress_bar);
	std::thread processor(process_data);

	fetcher.join();
	prog.join();
	processor.join();
}
```



# References

4. James Raynard, Learn Multithreading with Modern C++ Udemy.





