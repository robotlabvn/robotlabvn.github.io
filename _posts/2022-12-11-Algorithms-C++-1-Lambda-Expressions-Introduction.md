---
layout: post
category: blog
title: (Algorithms C++) 2. Lambda Expressions Introduction C++
snippet: This tutorial following the algorithms in C++
tags: [Algorithms C++]
---

In C++, a lambda expression is a convenient way to define an anonymous function object or functor. It was introduced in C++11 and allows you to create inline functions for short snippets of code that are not going to be reused and therefore do not require a name. Lambda expressions are often used to encapsulate a few lines of code that are passed to algorithms or asynchronous functions, improving code readability and maintainability

A lambda expression can be defined in its simplest form as follows:

{% include image.html url="/assets/2022-12-10-Algorithms-C++/lambda_function.png" description="Lambda Function Expression" width="60%" %}

The return type in lambda expressions is usually evaluated by the compiler itself, and you don't need to specify it explicitly. The ```→return-type``` part can also be ignored in many cases. However, in some complex situations, such as conditional statements, the compiler may not be able to determine the ```return``` type, and explicit specification is required

## A functor
A functor, or function object, is a C++ class that acts like a function. It is an object that can be treated as though it is a function or function pointer. Functors are most commonly used along with STLs in a scenario where a function requires more information than it can accept as a parameter. Functors are objects that can be called like a function by overloading the function call operator (). They can be used to encapsulate a few lines of code that are not going to be reused and therefore do not require a name. Functors can simplify tasks and improve efficiency in many cases


___Example ```functor.cpp``` bellow:___ 

functor.cpp
{:.filename}
```c++

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Define a functor for the predicate
class is_odd {
  public:
    bool operator () (const int n) const { return (n % 2 == 1); }
};

int main() {
	vector<int> vec {3, 1, 4, 1, 5, 9};

	// Pass a functor object
	auto odd_it = find_if(cbegin(vec), cend(vec), is_odd());

	// odd_it will be an iterator to the first odd element (if there is one)
	if (odd_it != cend(vec))
		cout << "First odd element is: " << *odd_it << endl;	
	//-> First odd element is: 3

}
```
We can simplify this code by using Lambda expression

___Example ```lambda.cpp``` bellow:___ 

lambda.cpp
{:.filename}
```c++

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
	vector<int> vec {3, 1, 4, 1, 5, 9};

	// Pass a lambda expression
	auto odd_it = find_if(cbegin(vec), cend(vec),
							[](int n) { return (n % 2 == 1); }
	);

	// odd_it will be an iterator to the first odd element (if there is one)
	if (odd_it != cend(vec))
		cout << "First odd element is: " << *odd_it << endl;	
	//-> First odd element is: 3

}
```

<div class="tip">
<b>A Assignment:</b> Write a function that takes a vector of int as argument and uses a range-for loop to print out the elements of the vector. Write a program that calls this function. Check that your program compiles and runs correctly. Modify your program so that it sorts the elements in descending order, with the largest element first. For example, if the vector elements are 1, 2, 3, 4, 5, the result would be 5, 4, 3, 2, 1. Use a suitable standard algorithm with a lambda expression as predicate.
Display the elements of the vector after sorting them. Check that your program still compiles and runs correctly.
</div>

___Example ```Assignment.cpp``` bellow:___ 

Assigment.cpp
{:.filename}
```c++

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void print_vec(vector<int>& vec){
    for(int i=0; i < vec.size(); i++){
		cout << vec[i] << " ";
	};
	cout <<endl; 
}

int main() {
	vector<int> vec {3, 1, 4, 1, 5, 9};
    //Before sorting
    cout <<"Before sorting " << endl;
	print_vec(vec);
    // -> 3 1 4 1 5 9 

	// Pass a lambda expression
    sort(vec.begin(), vec.end(),
							[](int a, int b) { return (a > b); }
	);
    
    //Print vector elements
    cout <<"After sorting " << endl;
	print_vec(vec);
	// -> 9 5 4 3 1 1 
}

```

# References
1. https://www.geeksforgeeks.org/lambda-expression-in-c/
2. https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
3. https://www.programiz.com/cpp-programming/lambda-expression
4. Example from James Raynard Learn Advanced Modern C++ Udemy.