---
layout: post
category: blog
title: (Modern C++) 5. Array, Vector and String
snippet: This tutorial following the basic C++ course
tags: [Modern C++]
---
# Array definition
In modern C++, arrays can be created using fixed-size containers such as ```std::array``` or variable-sized containers such as ```std::vector```. ```std::array``` is a container that encapsulates fixed-size arrays and is part of the C++ Standard Library. It provides the same performance and accessibility as a C-style array, but with the benefits of a standard container, such as knowing its own size, supporting assignment, and random access iterators. 

___Here's an example of how to create and initialize a ```std::array```:___

Array.cpp
{:.filename}
```c++
#include <array>
#include <iostream>

int main() {
  std::array<int, 5> arr = {1, 2, 3, 4, 5};

  for (int i = 0; i < arr.size(); ++i) {
    std::cout << arr[i] << " ";
  }

  return 0;
}
// Output; Elements in array: 1 2 3 4 5 
```

Or a simple way

Array.cpp
{:.filename}
```c++
#include <iostream>

int main() {
  // Declare and initialize an array
  int numbers[] = {1, 2, 3, 4, 5};

  // Access and print array elements
  for (int i = 0; i < 5; i++) {
    std::cout << numbers[i] << " ";
  }

  return 0;
}
// Output; Elements in array: 1 2 3 4 5 
```
## Dynamic Array
In C++, a dynamic array is a resizable array that can be modified during program runtime. Unlike regular arrays, which have a fixed size, dynamic arrays can grow or shrink as needed. Dynamic arrays are created using the new keyword and can be deleted using the ```delete``` keyword

Dynamic_Array.cpp
{:.filename}
```c++
#include <iostream>

int main() {
  // Create a dynamic array of 5 integers
  int* dynamicArray = new int[5];

  // Initialize the dynamic array with values
  for (int i = 0; i < 5; i++) {
    dynamicArray[i] = i;
  }

  // Print the contents of the dynamic array
  for (int i = 0; i < 5; i++) {
    std::cout << dynamicArray[i] << " "; //Output: 0 1 2 3 4
  }
  std::cout << std::endl;

  // Modify an element of the dynamic array
  dynamicArray[2] = 10;

  // Print the modified dynamic array
  for (int i = 0; i < 5; i++) {
    std::cout << dynamicArray[i] << " "; ////Output: 0 1 10 3 4 
  }
  std::cout << std::endl;

  // Free up the memory used by the dynamic array
  delete[] dynamicArray;

  return 0;
}
```

# Vector definition
In C++, a vector is a dynamic array-like container that can change in size. It is part of the C++ Standard Template Library (STL) and is defined in the ```<vector>``` header file. Vectors are similar to arrays, but they provide additional functionality, such as automatic resizing and various member functions for easy manipulation of the elements.

Vector.cpp
{:.filename}
```c++
#include <iostream>
#include <vector>

using namespace std;

int main() {

	vector<int> vec;                            // No general way to initialize vector elements in C++03  
	vec.push_back(4);                           // Therefore we create an empty vector, then add elements
	vec.push_back(2);                           // push_back adds a new element after the last element
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(1);

	cout << "Element with index 0 has value " << vec[0] << endl;     // The first element in vec - this will be equal to 4
	cout << "Element with index 2 has value " << vec[2] << endl;     // The third element in vec - this will be equal to 3
	cout << "Element with index 4 has value " << vec[4] << endl;     // The fourth element in vec - this will be equal to 1
	
	cout << "The size of vector is :" << vec.size() <<endl;
	cout << endl << "Modifying element with index 2 to have value 6" << endl;
	vec[2] = 6;                                 // Changes the third element in vec from 3 to 6

	
	cout << endl << "Printing out all elements: " << endl;
	
	// The size() member function returns the number of elements
	int i;
	for (i = 0; i < vec.size(); ++i) {
		cout << "Element with index " << i << " has value " << vec[i] << endl;
	}

	//Shorter way
	vector<int> vec1{0, 1, 2, 3, 4};
	cout << endl << "Printing out all elements: " << endl;
	
	// The size() member function returns the number of elements
	int i;
	for (i = 0; i < vec1.size(); ++i) {
		cout << "Element with index " << i << " has value " << vec1[i] << endl;
	}

}
```

Output
{:.filename}
```c++
Element with index 0 has value 4
Element with index 2 has value 3
Element with index 4 has value 1
The size of vector is :5

Modifying element with index 2 to have value 6

Printing out all elements: 
Element with index 0 has value 4
Element with index 1 has value 2
Element with index 2 has value 6
Element with index 3 has value 4
Element with index 4 has value 1

Printing out all elements: 
Element with index 0 has value 0
Element with index 1 has value 1
Element with index 2 has value 2
Element with index 3 has value 3
Element with index 4 has value 4
```
## Vector representation push_back(), pop_back(),  iterators for traversing the elements:
Vector_representation.cpp
{:.filename}
```c++
#include <iostream>
using namespace std;
#include <vector>

int main() {
    std::vector<int> numbers; // Declaration
    numbers = {1, 2, 3, 4, 5}; // -> 1 2 3 4 5 
    numbers.push_back(6); // Adding 6 to the end of the vector -> 1 2 3 4 5 6 
    numbers.pop_back(); // Removing the last element -> 1 2 3 4 5 
    numbers.erase(numbers.begin() + 2); // Removing the third element -> 1 2 4 5 
    //iterators for traversing the elements:
    for (auto it = numbers.begin(); it != numbers.end(); ++it) {
        std::cout << *it << " "; // Printing the elements -> 1 2 4 5 
    }
    return 0;
}
```

# String
In C++, a string is a sequence of characters used to store and manipulate text or other types of data. There are two main ways to represent strings in C++: 
- using C-style character arrays and the std::string class. C-style character arrays: These are one-dimensional arrays of characters terminated by a null character ('\0'). C-style strings are inherited from the C language and are less advanced than the std::string class, but they are still widely used for their efficiency and simplicity. Here's an example of a C-style string in C++:

String.cpp
{:.filename}
```c++
#include <iostream>
using namespace std;

int main() {
    char greeting[] = "Hello";
    cout << "Greeting message: " << greeting << endl; // Greeting message: Hello
    //cout << "Greeting size: " << greeting.size() << endl; // error: request for member 'size' in 'greeting', which is of non-class type 'char [6]'
    return 0;
}
```
- ```std::string class```: This is a part of the C++ Standard Library and provides a more advanced and convenient way to work with strings. To use the std::string class, you need to include the <string> header. Here's an example of a std::string in C++:
Example of ```std::string class```

String.cpp
{:.filename}
```c++
#include <iostream>
#include <string>
using namespace std;

int main() {
    string greeting = "Hello";
    cout << "Greeting message: " << greeting << endl;    // Greeting message: Hello
    cout << "Greeting size: " << greeting.size() << endl;// Greeting size: 5
    return 0;
}
```
## String search with ```str.find()``` function

String_search.cpp
{:.filename}
```c++
#include <iostream>
#include <string>

using namespace std;

int main() {
	string str ("Hello world");
	cout << "The string is \"" << str << "\"" << endl;
	cout << "First occurrence of \'o\' is at index " << str.find('o') << endl;     // Returns 4
	cout << "First occurrence of \"or\" is at index " << str.find("or") << endl;   // Returns 7

	cout << "Does 'O' occur in the string? ";
	
	if (str.find('O') == string::npos)
		cout << "No" << endl;
	else
		cout << "Yes" << endl;
}
```
Output
```
The string is "Hello world"
First occurrence of 'o' is at index 4
First occurrence of "or" is at index 7
Does 'O' occur in the string? No
```

# References
1. https://hsf-training.github.io/hsf-training-cpp-webpage/03-arrays-and-vectors/index.html
2. https://learn.microsoft.com/en-us/cpp/cpp/arrays-cpp?view=msvc-170
3. https://en.cppreference.com/w/cpp/container/array
4. https://cplusplus.com/doc/tutorial/dynamic/
5. https://cplusplus.com/reference/vector/vector/
6. https://www.programiz.com/cpp-programming/vectors
7. https://cplusplus.com/reference/string/string/