---
layout: post
category: blog
title: (Algorithms C++) 2. Lambda Expressions in C++
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
# An Assignment

<div class="tip">
<b>An Assignment:</b> Write a function that takes a vector of int as argument and uses a range-for loop to print out the elements of the vector. Write a program that calls this function. Check that your program compiles and runs correctly. Modify your program so that it sorts the elements in descending order, with the largest element first. For example, if the vector elements are 1, 2, 3, 4, 5, the result would be 5, 4, 3, 2, 1. Use a suitable standard algorithm with a lambda expression as predicate.
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

# Lambda Expressions Practical

Without Lambda expression
___Example ```Without_Lambda.cpp``` bellow:___ 

Without_Lambda.cpp
{:.filename}
```c++

#include <string>
#include <iostream>

using namespace std;

// Case-insensitive string equality. Returns true if lhs and rhs are equal, otherwise false
bool equal_strings(const string& lhs, const string& rhs) {
    // If the two strings have different lengths
    if (lhs.size() != rhs.size())                                              
        return false;

    // If the two strings have the same lengths...
    auto lit=cbegin(lhs);
    auto rit = cbegin(rhs);

    while (lit != cend(lhs) && rit != cend(rhs)) {          // Iterate over both strings
        if (toupper(*lit) != toupper(*rit))                   // Convert to upper case and compare
            return false;                                     // Characters are different
        ++lit;
        ++rit;
    }
    return true;                                              // No differences found
}

void test(const string& str1, const string& str2) {
    cout << str1 << " and " << str2 << " are" << 
             (equal_strings(str1, str2) ? "" : " not")
             << " equal" << endl;
}

int main() {
    test("lambda", "Lambda"); //->  lambda and Lambda are equal
    test("lambda", "lambada");//-> lambda and lambada are not equal
}
```
With Lambda expression

With_Lambda.cpp
{:.filename}
```c++

#include <string>
#include <algorithm>
#include <iostream>

using namespace std;

bool equal_strings(const string& lhs, const string& rhs) {
    // Call equal() algorithm function using a lambda expression
    return equal(cbegin(lhs), cend(lhs), cbegin(rhs), cend(rhs),
               		           [] (char lc, char rc) { return toupper(lc) == toupper(rc); }
    );
}

void test(const string& str1, const string& str2) {
    cout << str1 << " and " << str2 << " are" << 
             (equal_strings(str1, str2) ? "" : " not")
             << " equal" << endl;
}

int main() {
    test("lambda", "Lambda"); //->  lambda and Lambda are equal
    test("lambda", "lambada");//-> lambda and lambada are not equal
}

```

# Lambda Expression and Variables

The capture clause of a lambda expression is used to specify which variables are captured and whether they are captured by value or by reference. The capture clause is optional, and if it is not specified, the lambda expression cannot capture any variables from the surrounding scope.

Example_Capture.cpp
{:.filename}
```c++

#include <iostream>

using namespace std;

int global{99};                                  // Non-local variable

int main() {                                     // Scope containing the lambda expression
	static int answer{42};                       // Static variable in containing scope
	const int one{1};                            // Local variable in containing scope
	const int& r_one{one};                       // Local variable in containing scope
	
	[]() {                                       // Start of lambda body
		cout << global << endl;                  // Lambda body can access non-local variables
		cout << answer << endl;                  // Lambda body can access static variables
		// Does not compile with Visual C++
		//cout << one << endl;                   // Lambda body can read local variables, provided...
		// Does not compile with Visual C++, gcc or clang
		//cout << r_one << endl;                 // Lambda body can read local variables, provided...
	};                                           // End of lambda body
}                                                // End of scope containing the lambda expression

```

Example capture_lambda
Example_Capture_lambda.cpp
{:.filename}
```c++

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

using namespace std;

int main() {
	vector<string> words{ "a", "collection", "of", "words", "with", "varying", "lengths" };

	int n{5};
	// Find the first element with more than 5 characters
	auto res = find_if(cbegin(words), cend(words), 
				[n] (const string& str) { return str.size() > n; }         // Lambda captures local variable n
	);

	// Display it
	if (res != cend(words)) {
		cout << R"(The first word which is more than )" << n << R"( letters long is ")";
		cout << *res << R"(")" << endl;
	}
}
	// -> The first word which is more than 5 letters long is "collection"
```

# Capture in Lambda Expression

In C++, a lambda expression can capture variables from the surrounding scope using an implicit or explicit capture. Implicit capture, denoted by ```[=]``` or ```[&]```, captures all variables by value or reference, respectively. Explicit capture, denoted by ```[var]``` or ```[&var]```, captures a specific variable by value or reference.

There are a few considerations when choosing between implicit and explicit captures:

 - Error-proneness: Explicit capture is generally considered less error-prone, especially when dealing with heavy objects. Implicit capture can lead to unintended side effects if the captured variables are modified outside the lambda. 

 - Encapsulation and safety: Explicit capture allows you to access only the variables you need, which can help the compiler detect when you access a variable you shouldn't. It also keeps the local state of the method (its invariants, for the lifetime of the function during its execution) safer.

 - Functionality and implementation: Implicit and explicit captures are functionally and implementation-wise identical. The choice between them depends on the specific requirements of your code.

 - Best practices: As a matter of style, it is recommended to always capture ```*this``` explicitly, even in the presence of capture-defaults. 

___Explicit capture ```Explicit_capture.cpp``` bellow:___ 
Explicit_capture.cpp.cpp
{:.filename}
```c++

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int main() {
	vector<string> words{ "a", "collection", "of", "words", "with", "varying", "lengths" };

	int max{5}, idx{-1};                                // Add another variable for the index of the match
	
	auto res = find_if(cbegin(words), cend(words),
					// Explicit capture, capture idx by reference 
					[max, &idx] (const string& str) { ++idx; return str.size() > max; } 
	 );

	if (res != cend(words)) {
		cout << R"(The first word which is more than )" << max << R"( letters long is ")";
		cout << *res << R"(")" << endl;
		cout << "Its index is " << idx << endl;
	}
	// The first word which is more than 5 letters long is "collection"
	// Its index is 1
}

```

In C++, a lambda expression can capture the ```*this``` pointer by value or by reference to access the members of the current object. Capturing ```*this``` by value is important in scenarios where the lambda expression is asynchronously dispatched from a non-static member function, as the pointer might not be valid when the function runs.

___Capture This ```capture_this.cpp``` bellow:___ 
capture_this.cpp
{:.filename}
```c++
#include <iostream>

using namespace std;

class Test {
	int time{10};                                   // Data member
public:
	void countdown() {                              // Member function which calls a lambda expression
		[this] () {        			                // Capture class object by reference
			if (time > 0)
				cout << time << endl;
			else if (time == 0)
				cout << "Liftoff!" << endl;
			--time;
		}();			 			   			// Call the lambda function
	}
};

int main() {
	Test test;
	for (int i = 0; i < 12; ++i)
		test.countdown();
}

```
Output.cpp
{:.filename}
```c++
10
9
8
7
6
5
4
3
2
1
Liftoff!
```

# References
1. https://www.geeksforgeeks.org/lambda-expression-in-c/
2. https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
3. https://www.programiz.com/cpp-programming/lambda-expression
4. Example from James Raynard Learn Advanced Modern C++ Udemy.
5. https://learn.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170
6. https://en.cppreference.com/w/cpp/language/lambda
