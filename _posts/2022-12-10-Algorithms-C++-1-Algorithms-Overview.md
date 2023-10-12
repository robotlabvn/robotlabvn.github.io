---
layout: post
category: blog
title: (Algorithms C++) 1. Algorithms Overview C++
snippet: This tutorial following the algorithms in C++
tags: [Algorithms C++]
---

The ```<algorithm>``` header in C++ provides a collection of functions that are designed to be used on ranges of elements. A range is any sequence of objects that can be accessed through iterators. These functions can be used for various purposes, such as searching, sorting, counting, and manipulating elements in a range


___Example ```char_find.cpp``` bellow:___ 

char_find.cpp
{:.filename}
```c++
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	string str{"Hello world"};
	cout << "String: ";
	
	for (auto c : str)
		cout << c << ",";
	cout << "\n";
	
	auto res = find(cbegin(str), cend(str), 'l');          // Search string for first occurrence of 'l'

	// Check if we found it
	if (res != cend(str)) {
		 // Access the result
		cout << "Found a matching element at index: " << res - str.cbegin() << endl;
	}
	
	cout << "At this point in the string: ";
	for (auto it = res; it != str.cend(); ++it)
		cout << *it;
	cout << endl;
}

```

___ ```Output``` bellow:___ 

```
String: H,e,l,l,o, ,w,o,r,l,d,
Found a matching element at index: 2
At this point in the string: llo world

```

We look the psuedo code of the ```std::find()``` algorithm

find.cpp
{:.filename}
```c++
//Accepts any container with elements of any type
//Iter = type of container's iterator, Elem = type of container elements

Iter find(Iter begin, Iter end, Elem target){
    for(Iter it = begin; it !=end; ++it){ //Loop over range, stopping befor "end"
        if (*it ==target){ //Is this the value we are looking for?
            return it; // return the looking target
        }
    }
    // We have reach the end of the loop
    return end;
}

```
___Example ```sort_string.cpp``` bellow:___ 
find.cpp
{:.filename}
```c++
#include <algorithm>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	vector<string> names = { "Dilbert", "PHB", "Dogbert", "Asok", "Ted", "Alice", "Wally" };
	
	cout << "Vector before sort()\n";
	for (auto name : names)
		cout << name << ", ";
	cout << endl << endl;
	// -> Dilbert, PHB, Dogbert, Asok, Ted, Alice, Wally, 
	sort(begin(names), end(names));
	
	cout << "Vector after sort()\n";
	for (auto name : names)
		cout << name << ", ";
	cout << endl;
    // -> Alice, Asok, Dilbert, Dogbert, PHB, Ted, Wally, 
}
```

---

# Predicates

In C++, a predicate is a function or a function object that returns a boolean value. It is typically used with algorithms that take input data (individual objects or containers) and a predicate, which is then called on the input data to perform a comparison or condition check

___Example  simple predicates function  ```pred_function.cpp``` bellow:___ 
pred_function.cpp
{:.filename}
```c++
#include <algorithm>
#include <iostream>
#include <vector>

bool greater(int a, int b) {
  return a > b;
}

int main() {
  std::vector<int> numbers = {5, 2, 8, 1, 9};
  std::sort(numbers.begin(), numbers.end(), greater);

  for (int number : numbers) {
    std::cout << number << " ";
  }
  std::cout << std::endl;
  // -> 9 8 5 2 1 
  return 0;
}
```

___Example  Predicates function with string ```pred_function.cpp``` bellow:___ 
pred_function.cpp
{:.filename}
```c++
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define a predicate function
bool is_shorter (const string& lhs, const string& rhs) {
    return lhs.size() < rhs.size();
 }

int main() {
	vector<string> names = { "Dilbert", "PHB", "Dogbert", "Asok", "Ted", "Alice", "Wally" };
	
	cout << "Vector before sort()\n";
	for (auto name : names)
		cout << name << ", ";
	cout << endl << endl;
	//-> Dilbert, PHB, Dogbert, Asok, Ted, Alice, Wally, 

	// Sort the data in alphabetical order
	sort(begin(names), end(names));
	
	cout << "Sorted alphabetically:" << endl;
	vector<string>::iterator it;
	for (auto name : names)
		cout << name << ", ";
	cout << endl;
	//-> Alice, Asok, Dilbert, Dogbert, PHB, Ted, Wally, 

	// Sort the data, passing the function pointer as the predicate
	sort(begin(names), end(names), is_shorter);
	
	cout << endl << "Sorted by length:" << endl;
	for (auto name : names)
		cout << name << ", ";
	cout << endl;
    // -> PHB, Ted, Asok, Alice, Wally, Dilbert, Dogbert, 
}
```

___Example  Predicates function with string and class```pred_function.cpp``` bellow:___ 

pred_function.cpp
{:.filename}
```c++
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define a predicate as a functor
class is_shorter {
public:
	// Overloaded () operator
	// Takes two strings as arguments
	// Returns true/false depending on relative string length
   bool operator () (const string& lhs, const string& rhs) {
        return lhs.size() < rhs.size();
    }
};

int main() {
	vector<string> names = { "Dilbert", "PHB", "Dogbert", "Asok", "Ted", "Alice", "Wally" };
	
	cout << "Vector before sort()\n";
	for (auto name : names)
		cout << name << ", ";
	cout << endl << endl;
	//-> Dilbert, PHB, Dogbert, Asok, Ted, Alice, Wally, 

	// Sort the data in alphabetical order
	sort(begin(names), end(names));
	
	cout << "Sorted alphabetically:" << endl;
	vector<string>::iterator it;
	for (auto name : names)
		cout << name << ", ";
	cout << endl;
	//-> Alice, Asok, Dilbert, Dogbert, PHB, Ted, Wally, 

	// Use is_shorter to sort the data
	sort(begin(names), end(names), is_shorter());
	
	cout << endl << "Sorted by length:" << endl;
	for (auto name : names)
		cout << name << ", ";
	cout << endl;

    // -> PHB, Ted, Asok, Alice, Wally, Dilbert, Dogbert, 
}
```

# Algorithms with ```_if``` versions
The <algorithm> header in C++ provides a collection of functions for various purposes, such as searching, sorting, counting, and manipulating elements in ranges. These functions can be used with different versions, including the _if versions, which operate on function objects that work on the values of the elements rather than on the elements themselves. 

Predicates in C++ algorithms are function objects or lambda expressions that return a Boolean value. They are used to define conditions for sorting, searching, or other operations on elements in a range. For example, a predicate can be used to specify the sorting order or to filter elements based on a certain condition.

___Algorithms with ```copy_if``` versions bellow:___ 

copy_if_example.cpp
{:.filename}
```c++
#include <algorithm>
#include <iostream>
#include <vector>

bool isEven(int number) {
  return number % 2 == 0;
}

int main() {
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> evenNumbers;

  // Copy only the even numbers from the numbers vector to the evenNumbers vector
  std::copy_if(numbers.begin(), numbers.end(), std::back_inserter(evenNumbers), isEven);

  // Print the even numbers
  for (int number : evenNumbers) {
    std::cout << number << " ";
  }
  // -> 2 4 6 8 10 
  return 0;
}
```

___Algorithms with ```find_if``` versions bellow:___ 

find_if_example.cpp
{:.filename}
```c++
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Functor
class ge_5 {
	public:
	// Overloaded () operator
	// Takes an std::string, returns true if more than 5 characters
    bool operator ()(const string& s) const { 
      return (s.size() > 5);
    }
};

int main() {
	// Manually coded example
	vector<string> names = { "Dilbert", "PHB", "Dogbert", "Asok", "Ted", "Alice", "Wally" };
	
	ge_5 long_enough;
	for (auto name: names) {
		if (long_enough(name)) {
			cout << "Loop: the first name with > 5 characters is \"" << name << "\"\n";
			break;
		}
	}
	//-> Loop: the first name with > 5 characters is "Dilbert"

	// Find the first element with more than 5 characters
	// Pass a functor object as predicate
	auto res = find_if(cbegin(names), cend(names), ge_5());

	// Display it
	if (res != cend(names))
		cout << "Algorithm: the first name with > 5 characters is \"" << *res << "\"\n";
    //-> Algorithm: the first name with > 5 characters is "Dilbert"
}
```



# References
1. https://en.cppreference.com/w/cpp/named_req/Predicate
2. https://cplusplus.com/reference/algorithm/
3. Example from James Raynard Learn Advanced Modern C++ Udemy.