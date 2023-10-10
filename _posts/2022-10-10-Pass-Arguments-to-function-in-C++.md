---
layout: post
category: blog
title: 1. How to pass arguments to functions in C++ 
snippet: This tutorial following the basic C++ course
tags: [Basic C++]
---
# 1. How to pass arguments to functions [Basic C++]
In C++, there are several ways to pass arguments to functions, each with its own characteristics and use cases:

- **Pass by Value:** When an object or built-in type is passed by value, a local copy of the argument is created within the function. Any modifications made to the copy do not affect the original object. This method is suitable for small objects that are cheap to copy and when the function does not need to modify the original object.
    
- **Pass by Address:** Also known as pass by pointer, this method involves passing the memory address of the object to the function. The function can then access and modify the object directly. This method is useful when the function needs to modify the original object or when the object is large and copying it would be expensive

- **Pass by Reference:** When an object is passed by reference, the function is given the memory address of the object itself. This saves both memory and CPU cycles, as no new memory is allocated, and no copy of the object is made. Any modifications made to the object within the function will affect the original object. This method is suitable for situations where the function needs to modify the original object and when the object is not too large.

- **Pass by Const Reference:** This method is similar to pass by reference, but the reference is marked as const. This means that the function cannot modify the value being referenced. Pass by const reference offers the same primary benefit as pass by reference (avoiding making a copy of the argument), while also guaranteeing that the function cannot change the value being referenced. This method is suitable when the function does not need to modify the original object, and the object is expensive to copy.

___Example ```pass_arguments.cpp``` bellow:___ 

pass_arguments.cpp
{:.filename}
```c++
#include <iostream>

using namespace std;

int passByValue(int y){
    cout << "Address of y is " << &y <<endl;
    y = 1; 
    return y;
}

int passByAddress(int *y){
    cout << "Address of y is " << y <<endl;
    *y = 1; // y pointer variable store the new value
    return *y;
}

int passByReference(int &y){
    cout << "Address of y is " << &y <<endl;
    y = 1;
    return y;
}

int passByConstReference(const int &y){
    // For read-only access to class objects, passing by const reference 
    // is usually more efficient than passing by value. 
    cout << "Address of y is " << &y <<endl;
    // y = 1; //--> error: assignment of read-only reference ‘y’
    return y;
}

int main(){
    // Code for Pass by Value 
    cout << "----Code for Pass by Value---- " <<endl;
    int x =2;
    cout <<  "Address of x is" << &x << endl;
    int z = passByValue(x); //z will be a copy of func's return value
    cout << "Address of z is" << &z <<endl;
    cout << "After calling func(), x = " << x <<endl;
    cout << "After calling func(), z = " << z <<endl;
    // Output:
    // Address of x is0x7ffcd9d89680  --> Differences address
    // Address of y is 0x7ffcd9d8966c --> Differences address
    // Address of z is0x7ffcd9d89684  --> Differences address
    // After calling func(), x = 2
    // After calling func(), z = 1

    // Code for Pass by Address
    cout << "----Code for Pass by Address----" <<endl;
    int a =2;
    cout <<  "Address of a is " << &a << endl;
    int b = passByAddress(&a); //z will be a copy of func's return value
    cout << "Address of b is" << &b <<endl;
    cout << "After calling func(), a = " << a <<endl;
    cout << "After calling func(), b = " << b <<endl;
    // Output:
    // Address of a is 0x7ffd8c09d010 --> Same address
    // Address of y is 0x7ffd8c09d010 --> Same address
    // Address of b is0x7ffd8c09d00c
    // After calling func(), a = 1
    // After calling func(), b = 1

     // Code for Pass by Reference
    cout << "----Code for Pass by Reference----" <<endl;
    int i =2;
    cout <<  "Address of i is " << &i << endl;
    int j = passByReference(i); // j will be a copy of func's return value
    cout << "Address of j is" << &j <<endl;
    cout << "After calling func(), i = " << i <<endl;
    cout << "After calling func(), j = " << j <<endl;
    // Output: 
    // Address of i is 0x7ffd547364e0 --> Same address
    // Address of y is 0x7ffd547364e0 --> Same address
    // Address of j is0x7ffd547364e4
    // After calling func(), i = 1
    // After calling func(), j = 1

     // Code for Pass by Const Reference
    cout << "----Code for Pass by Const Reference----" <<endl;
    int k =2;
    cout <<  "Address of k is " << &k << endl;
    int l = passByConstReference(k); // j will be a copy of func's return value
    cout << "Address of l is" << &l <<endl;
    cout << "After calling func(), k = " << k <<endl;
    cout << "After calling func(), l = " << l <<endl;
    // Output
    // Address of k is 0x7ffc52a54700 --> Same address
    // Address of y is 0x7ffc52a54700 --> Same address
    // Address of l is0x7ffc52a54704
    // After calling func(), k = 2
    // After calling func(), l = 2
    }

```

# References
1. https://www.quantstart.com/articles/Passing-By-Reference-To-Const-in-C/
2. https://www.learncpp.com/cpp-tutorial/pass-by-const-lvalue-reference/
3. https://www.ibm.com/docs/en/zos/2.4.0?topic=calls-pass-by-reference-c-only