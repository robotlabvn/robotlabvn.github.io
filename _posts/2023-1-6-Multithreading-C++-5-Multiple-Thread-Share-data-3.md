---
layout: post
category: blog
title: (Multithreading C++) 6. Deadlock and Livelock
snippet: This tutorial in series of Mutex and Multiple Threads working with Share data.
tags: [Multithreading C++]
---

# I. Deadlock
<div class="tip">
<b>Deadlock is the second most problem in multi-threading code, after data races</b>
</div>


A mutual deadlock in C++ occurs when two or more threads are blocked and waiting for each other to release a resource. 
Deadlocks can occur due to a wrong order of acquiring locks, which can be avoided by acquiring locks in an agreed order. It can happen by following reasons:

- Two or more threads are waiting for each other

- Thread A waits for thread B to do something

- Thread B is waiting for A to do something

- Theads A and B are waiting for an event that can never happen

{% include image.html url="/assets/2023-1-1-Multithreading-C++/dead_lock.png" description="Dead Lock" width="80%" %}

It can occur when waiting for:

- The result of a computation performed by another thread

- A message sent by another thread

- A GUI event produced by another thread




## Example of dead lock in C++

__Example ```dead_lock.cpp``` bellow:__

dead_lock.cpp
{:.filename}
```c++
// Mutual deadlock
// Two threads wait for the other to unlock a mutex
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
	std::cout << "Thread A trying to lock mutex 1...\n";
	std::lock_guard<std::mutex> lck_guard(mut1);		// Acquire lock on mut1
	std::cout << "Thread A has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "Thread A trying to lock mutex 2...\n";
	std::lock_guard<std::mutex> lck_guard2(mut2);		// Wait for lock on mut2
	std::cout << "Thread A has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "Thread A releases all its locks\n";
}

void funcB()
{
	std::cout << "Thread B trying to lock mutex 2...\n";
	std::lock_guard<std::mutex> lck_guard1(mut2);	    // Acquire lock on mut2
	std::cout << "Thread B has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "Thread B trying to lock mutex 1...\n";
	std::lock_guard<std::mutex> lck_guard2(mut1);	    // Wait for lock on mut1
	std::cout << "Thread B has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "Thread B releases all its locks\n";
}

int main()
{
	std::thread thrA(funcA);
	std::thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
```

## Deadlock avoidance

<div class="tip">
<b>Simple way to avoid deadlock</b>
<ul>
<li> <b>Both threads try to acquire the locks in the same order</b> Thread A and Thread B both try to lock the mutex1 first -> The successful thread then tries to lock the mutex2. But this is not ideal (Relies on the programmer, may not feasible in large programs</li>

<li> <b>Minimize shared state and synchronization:</b>Restructure or divide the resource so that threads can work asynchronously. This can help avoid contention and reduce the likelihood of deadlock </li>

</ul>
</div>

__Example ```deadlock_avoidance.cpp``` bellow:__

deadlock_avoidance.cpp
{:.filename}
```c++
// Avoid deadlock by writing the threads
// so that they lock the mutexes in the same order
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
	std::cout << "Thread A trying to lock mutex 1...\n";
	std::lock_guard<std::mutex> lck_guard(mut1);        // Acquire lock on mut1
	std::cout << "Thread A has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "Thread A trying to lock mutex 2...\n";
	std::lock_guard<std::mutex> lck_guard2(mut2);       // Wait for lock on mut2
	std::cout << "Thread A has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);                  // Do some work
	std::cout << "Thread A releases all its locks\n";
}

void funcB()
{
	std::cout << "Thread B trying to lock mutex 1...\n";
	std::lock_guard<std::mutex> lck_guard1(mut1);       // Acquire lock on mut1
	std::cout << "Thread B has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);                  // Do some work
	std::cout << "Thread B trying to lock mutex 2...\n";
	std::lock_guard<std::mutex> lck_guard2(mut2);	    // Wait for lock on mut2
	std::cout << "Thread B has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "Thread B releases all its locks\n";
}

int main()
{
	std::thread thrA(funcA);
	std::thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
```

# I. Deadlock Practical
The Dining Philosophers problem is a classic problem in computer science that illustrates synchronization issues in a multi-threaded environment. The problem states that there are five philosophers sitting around a circular table, each with their own plate and a fork between each plate. The philosophers alternate between thinking and eating, and can only eat when they have both a left and right fork. After an individual philosopher finishes eating, he will put down both forks. The problem is how to design a regimen (a concurrent algorithm) such that no philosopher will starve; i.e., each can forever continue to alternate between eating and thinking, assuming that no philosopher can know when others may want to eat or think.

{% include image.html url="/assets/2023-1-1-Multithreading-C++/dining_philosophers_problem.png" description="dining_philosophers_problem" width="80%" %}

## Code implementation

- A separate thread for each philosopher

- Each fork has an associated mutex

```c++
// A mutex prevents more than one philosopher picking up the same fork
std::mutex fork_mutex[nforks];

//  A pholosopher theard can only pick up a fork if it can lock the corresponding mutex
//Try to pick up the left fork
fork_mutex[lfork].lock();

// Try to pic up the right fork
fork_mutex[rfork].lock();

// Succeeded - This philosopher can now eat
//
```

## Deadlock problem -> The philosophers are blocked indefinitely.

deadlock_dining_philosophers.cpp
{:.filename}
```c++
// Dining philosophers problem (part 1)
//
// 5 philosophers sit at a round table which has 5 forks on it.
// A philosopher has a fork at each side of them.
// A philosopher can only eat if they can pick up both forks.
// If a philosopher picks up the fork on their right,
// that prevents the next philosopher from picking up their left fork.
//
// All the philosophers pick up their left fork at the same time
// They wait to pick up their right fork (which is also their neighbour's left fork)
// Their neighbour is waiting to pick up their own right fork
// All the philosophers are waiting for their neighbour
//
// The philosophers are blocked indefinitely.
// Deadlock
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <chrono>

using namespace std::literals;

// Some data about the problem
constexpr int nforks = 5;
constexpr int nphilosophers = nforks;
std::string names[nphilosophers] = {"A", "B", "C", "D", "E"};

// Keep track of how many times a philosopher is able to eat
int mouthfuls[nphilosophers] = {0};

// A philosopher who has not picked up both forks is thinking
constexpr auto think_time = 2s;

// A philosopher has picked up both forks is eating
constexpr auto eat_time = 1s;

// A philosopher who has picked up one fork will put it down again
// if they cannot pick up the other fork they need
constexpr auto time_out = think_time;

// A mutex prevents more than one philosopher picking up the same fork
// A philosopher thread can only pick up a fork if it can lock the corresponding mutex
std::mutex fork_mutex[nforks];

// Mutex to protect output
std::mutex print_mutex;

// Functions to display information about the 'nth' philosopher

// Interactions with a fork
void print(int n, const std::string& str, int forkno)
{
	std::lock_guard<std::mutex> print_lock(print_mutex);
	std::cout << "Philosopher " << names[n] << str << forkno << '\n';
}

// The philosopher's state
void print(int n, const std::string& str)
{
	std::lock_guard<std::mutex> print_lock(print_mutex);
	std::cout << "Philosopher " << names[n] << str << '\n';
}

// Thread which represents a dining philosopher
void dine(int phil_no)
{
	// Philosopher A has fork 0 on their left
	// and fork 1 on their right
	// Philosopher B has fork 1 on their left
	// and fork 2 on their right
	// ...
	// Philosopher E has fork 4 on their left
	// and fork 0 on their right
	//
	// Each philosopher must pick up their left fork first
	int lfork = phil_no;
	int rfork = (phil_no+1) % nforks;

	
	print(phil_no, "\'s left fork is number ", lfork);
	print(phil_no, "\'s right fork is number ", rfork);
	print(phil_no, " is thinking...");

	std::this_thread::sleep_for(think_time);

	// Make an attempt to eat
	print(phil_no, " reaches for fork number ", lfork);

	// Try to pick up the left fork
	fork_mutex[lfork].lock();
	print(phil_no, " picks up fork ", lfork);
	print(phil_no, " is thinking...");

	// Succeeded - now try to pick up the right fork
	std::this_thread::sleep_for(think_time);

	print(phil_no, " reaches for fork number ", rfork);

	fork_mutex[rfork].lock();

	// Succeeded - this philosopher can now eat
	print(phil_no, " picks up fork ", rfork);
	print(phil_no, " is eating...");
	
	std::this_thread::sleep_for(eat_time);

	print(phil_no, " puts down fork ", lfork);
	print(phil_no, " puts down fork ", rfork);
	print(phil_no, " is thinking...");

	fork_mutex[lfork].unlock();
	fork_mutex[rfork].unlock();
	std::this_thread::sleep_for(think_time);
}

int main()
{
	// Start a separate thread for each philosopher
	std::vector<std::thread> philos;

	for (int i = 0; i < nphilosophers; ++i) {
		philos.push_back(std::move(std::thread{dine, i}));
	}

	for (auto& philo: philos)
		philo.join();

	// How many times were the philosophers able to eat?
	for (int i = 0; i < nphilosophers; ++i) {
		std::cout << "Philosopher " << names[i];
		std::cout << " had " << mouthfuls[i] << " mouthfuls\n";
	}
}
```

Ouput of dining_philosophers.cpp
{:.filename}
```
Philosopher A's left fork is number 0
Philosopher A's right fork is number 1
Philosopher C's left fork is number 2
Philosopher C's right fork is number 3
Philosopher A is thinking...
Philosopher C is thinking...
Philosopher B's left fork is number 1
Philosopher B's right fork is number 2
Philosopher B is thinking...
Philosopher D's left fork is number 3
Philosopher D's right fork is number 4
Philosopher D is thinking...
Philosopher E's left fork is number 4
Philosopher E's right fork is number 0
Philosopher E is thinking...
Philosopher C reaches for fork number 2
Philosopher C picks up fork 2
Philosopher B reaches for fork number 1
Philosopher B picks up fork 1
Philosopher C is thinking...
Philosopher A reaches for fork number 0
Philosopher A picks up fork 0
Philosopher A is thinking...
Philosopher D reaches for fork number 3
Philosopher D picks up fork 3
Philosopher B is thinking...
Philosopher D is thinking...
Philosopher E reaches for fork number 4
Philosopher E picks up fork 4
Philosopher E is thinking...
Philosopher C reaches for fork number 3
Philosopher A reaches for fork number 1
Philosopher B reaches for fork number 2
Philosopher D reaches for fork number 4
Philosopher E reaches for fork number 0
```

## std::scoped_lock
Another solution is lock mutiple mutexes in a single operation. C++ provides library feature for this is ```std::scope_lock```. ```std::scoped_lock``` is a mutex wrapper that provides a convenient RAII-style mechanism for owning one or more mutexes for the duration of a scoped block.  ```std::scoped_lock ```can lock several mutexes at the same time, with a deadlock prevention mechanism, while ```std::lock_guard``` is limited to a single mutex.

__Example scoped_lock__

scoped_lock.cpp
{:.filename}
```c++
// Use std::scoped_lock to avoid deadlock
// All the mutexes are locked in a single operation
// Requires C++17 compiler
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>	

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
	std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
	std::scoped_lock scoped_lck(mut1, mut2);
	std::cout << "Thread A has locked mutexes 1 and 2\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread A releasing mutexes 1 and 2...\n";
}

void funcB()
{
	std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
	std::scoped_lock scoped_lck(mut2, mut1);
	std::cout << "Thread B has locked mutexes 2 and 1\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

int main()
{
	std::thread thrA(funcA);
	std::thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
```

## std::adopt_lock

std::adopt_lock is an option that can be used with ```std::unique_lock``` to indicate that the mutex is already locked and that the ```std::unique_lock``` should assume ownership of the lock without attempting to lock the mutex again. This is useful when you need to transfer ownership of a lock from one ```std::unique_lock``` object to another or when you want to initialize a ```std::unique_lock``` object with an already locked mutex.

__Example adopt_lock__

adopt_lock.cpp
{:.filename}
```c++
// Use std::adopt_lock to avoid deadlock
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
	std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
	std::lock(mut1, mut2);				               // Lock both mutexes
	std::cout << "Thread A has locked mutexes 1 and 2\n";
	
	// Adopt the locks
	std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);   // Associate each mutex
	std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);   // with a unique_lock
	std::cout << "Thread A has adopted the locks\n";
	
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread A releasing mutexes 1 and 2...\n";
}

void funcB() {
	std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
	lock(mut2, mut1);				               // Lock both mutexes
	std::cout << "Thread B has locked mutexes 2 and 1\n";
	
	// Adopt the locks
	std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);   // with a unique_lock
	std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);   // Associate each mutex
	std::cout << "Thread B has adopted the locks\n";
	
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

int main() {
	std::thread thrA(funcA);
	std::thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
```

Ouput of adopt_lock.cpp
{:.filename}
```
Thread A trying to lock mutexes 1 and 2...
Thread B trying to lock mutexes 2 and 1...
Thread A has locked mutexes 1 and 2
Thread A has adopted the locks
Thread A releasing mutexes 1 and 2...
Thread B has locked mutexes 2 and 1
Thread B has adopted the locks
Thread B releasing mutexes 2 and 1...
```

## std::defer_lock
```std::defer_lock``` is an option that can be used with ```std::unique_lock```to indicate that the mutex should not be locked upon construction of the ```std::unique_lock``` object. This is useful when you need to lock multiple mutexes in a specific order to avoid deadlock.

__Example defer_lock__
defer_lock.cpp
{:.filename}
```c++
// Use std::defer_lock to avoid deadlock
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
    std::unique_lock<std::mutex> uniq_lk1(mut1, std::defer_lock);	// Associate mutex with lock...
    std::unique_lock<std::mutex> uniq_lk2(mut2, std::defer_lock);	// ...but don’t lock it yet
	
	std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
    std::lock(uniq_lk1, uniq_lk2);								    // Now lock both of them
	std::cout << "Thread A has locked mutexes 1 and 2\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread A releasing mutexes 1 and 2...\n";
}

void funcB() {
    std::unique_lock<std::mutex> uniq_lk2(mut2, std::defer_lock);	// Associate mutex with lock...
    std::unique_lock<std::mutex> uniq_lk1(mut1, std::defer_lock);	// ...but don’t lock it yet
	
	std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
    std::lock(uniq_lk2, uniq_lk1);									// Now lock both of them
	std::cout << "Thread B has locked mutexes 2 and 1\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "Thread B releasing mutexes 2 and 1...\n";
}

int main() {
	std::thread thrA(funcA);
	std::thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
```

Ouput of defer_lock.cpp
{:.filename}
```
Thread A trying to lock mutexes 1 and 2...
Thread A has locked mutexes 1 and 2
Thread B trying to lock mutexes 2 and 1...
Thread A releasing mutexes 1 and 2...
Thread B has locked mutexes 2 and 1
Thread B releasing mutexes 2 and 1...
```

## std::try_lock
```std::try_lock```is a C++ function that attempts to lock multiple mutexes simultaneously without blocking. It is a non-blocking alternative to ```std::lock```, which blocks until all mutexes are locked. If ```std::try_lock``` is successful in locking all mutexes, it returns immediately -1 and the caller can proceed with the critical section. If ```std::try_lock``` fails to lock one or more mutexes, it releases any locks that it has acquired and returns a 0-based index of the first mutex that it failed to lock.

__Example try_lock__

try_lock.cpp
{:.filename}
```c++
// Use std::defer_lock to avoid deadlock
#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

void funcA()
{
    std::unique_lock<std::mutex> uniq_lk1(mut1, std::defer_lock);   // Associate mutex with lock...
    std::unique_lock<std::mutex> uniq_lk2(mut2, std::defer_lock);   // ...but don’t lock it yet
	
	std::cout << "Thread A trying to lock mutexes 1 and 2...\n";
    
	// Now lock both of them
	auto idx = std::try_lock(uniq_lk1, uniq_lk2);
	if (idx != -1) {
		std::cout << "try_lock failed on mutex with index " << idx << '\n';
	}
	else {
		std::cout << "Thread A has locked mutexes 1 and 2\n";
		std::this_thread::sleep_for(50ms);
		std::cout << "Thread A releasing mutexes 1 and 2...\n";
	}
}

void funcB() {
    std::unique_lock<std::mutex> uniq_lk2(mut2, std::defer_lock);   // Associate mutex with lock...
    std::unique_lock<std::mutex> uniq_lk1(mut1, std::defer_lock);   // ...but don’t lock it yet
	
	std::cout << "Thread B trying to lock mutexes 2 and 1...\n";
    
	// Now lock both of them
	auto idx = std::try_lock(uniq_lk2, uniq_lk1);
	if (idx != -1) {
		std::cout << "try_lock failed on mutex with index " << idx << '\n';
	}
	else {
		std::cout << "Thread B has locked mutexes 2 and 1\n";
		std::this_thread::sleep_for(50ms);
		std::cout << "Thread B releasing mutexes 2 and 1...\n";
	}
}

int main() {
	std::thread thrA(funcA);
	std::thread thrB(funcB);
	
	thrA.join(); thrB.join();
}
```
Ouput of try_lock.cpp
{:.filename}
```
Thread B trying to lock mutexes 2 and 1...
Thread B has locked mutexes 2 and 1
Thread A trying to lock mutexes 1 and 2...
try_lock failed on mutex with index 0
Thread B releasing mutexes 2 and 1...
```
<div class="tip">
<b>Main points on avoiding deadlock:</b>
<ul>
<li> <b>Avoid waiting for other threads when your thread holds a lock,</b> because that thread may need your lock before it can proceed.</li>

<li> <b>Try to avoid waiting for other threads in general,</b> because the other thread may be waiting for your thread.  </li>

<li> <b>Avoid nested locks.</b> If your thread already has a lock on a mutex, do not lock other mutexes.  </li>

<li> <b>If you do need to lock multiple mutexes, </b> do it all in a single operation. </li>

<li> <b>If your thread is inside a critical section, </b> , avoid calling functions unless you are absolutely certain that the function is not going to lock.</li>

</ul>
</div>

# References
1. https://vorbrodt.blog/2019/10/12/avoiding-deadlocks-the-c-way/
2. https://www.technical-recipes.com/2015/creating-and-avoiding-deadlock-conditions-in-c/
3. https://en.wikipedia.org/wiki/Dining_philosophers_problem
4. James Raynard, Learn Multithreading with Modern C++ Udemy.
5. https://en.cppreference.com/w/cpp/thread/lock_tag
6. https://cplusplus.com/reference/mutex/defer_lock/





