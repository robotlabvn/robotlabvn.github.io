---
layout: post
category: blog
title: How to build a C++ project with CMake
snippet: This tutorial shows how to build a simple C++ project with CMake
tags: [C++]
---
This tutorial shows how to build a simple C++ project with CMake.
We start with the Helloworld example with structure below.

```
├── helloworld
│   ├── build
│   │   ├── **/*.so --> library files
|   |   ├── **/*.a --> executable files
│   ├── CMakeList.txt
│   ├── helloworld.cpp
│   ├── libHelloWorld.cpp
│   ├── helloworld.h
│   ├── useHello.cpp
```

To build a C++ project with CMake, you can follow these general steps:

- Step 1. **Install CMake**: Install CMake on your computer. You can download the installer from the official website or use package managers like apt-get on Ubuntu[1](https://ncona.com/2019/03/building-a-cpp-project-with-cmake/), [2](https://vnav.mit.edu/labs/lab1/cmake.html).

```
sudo apt-get install cmake
```
- Step 2. **Create a CMakeLists.txt file**: Create a CMakeLists.txt file in the root directory of your project.
This file contains the instructions for building your project. It
specifies the minimum version of CMake required, the project name, and
any subdirectories or libraries that need to be included[1](https://ncona.com/2019/03/building-a-cpp-project-with-cmake/)

CMakeLists.txt
{:.filename}
```
# Add CmakeList version
cmake_minimum_required(VERSION 2.8)
# Name of project 
project(helloworld)
# Add executable
add_executable(helloworld helloworld.cpp)

##---- Library ---
# Add library 
add_library(hello libHelloWorld.cpp)

# Add Share library 
add_library(hello_shared SHARED libHelloWorld.cpp)

# Add excutable using lib
add_executable(useHello useHello.cpp)
target_link_libraries(useHello hello_shared)
```
- Step 3. **Create a build directory**: Create a separate directory for building your project. This keeps the build files separate from your source code.

- Step 4. **Run CMake**: In the build directory, run the command `cmake /path/to/source/code`. This generates the build files based on the instructions in your CMakeLists.txt file[1](https://ncona.com/2019/03/building-a-cpp-project-with-cmake/), [3](https://jdhao.github.io/2020/12/12/build_opencv_project_with_cmake/).

```
rm -rf build
mk build
cd build
cmake ..
```

- Step 5. **Build the project**: Use the appropriate build tool to build your project. This could be
make, ninja, or another tool depending on your system and preferences.
Run the command `make` in the build directory to build the project[1](https://ncona.com/2019/03/building-a-cpp-project-with-cmake/), [3](https://jdhao.github.io/2020/12/12/build_opencv_project_with_cmake/).

```
make
```

- Step 6. **Run the program**: Once the project is built, you can run the program by navigating to the appropriate directory and running the executable file[1](https://ncona.com/2019/03/building-a-cpp-project-with-cmake/), [3](https://jdhao.github.io/2020/12/12/build_opencv_project_with_cmake/).

```
cd build
./helloworld
./useHello
```
<div class="tip">
<b>After building a C++ project in Linux:</b>

You will have one or more executable files, dynamic-load libraries, or static libraries depending on the project configuration and build settings

<ul>
<li> <b>Executable files:</b> In C++, an executable file is the final output of the compilation and linking process. It is a file that the computer can directly execute to run the program. The specific format of the executable file depends on the operating system.
In the context of Windows, executable files typically have the ".exe" extension. On the other hand, in Linux, executable files usually have no extension and use the ELF (Executable and Linkable Format) format</li>

<li> <b>Static libraries (*.o):</b> are collections of object files that are linked directly into the executable at compile time. The code in a static library is compiled into the executable file, making it self-contained and independent of external libraries. Static libraries are useful when you want to distribute a single executable file without any external dependencies. They are sometimes called archives since they are just a package of compiled object files</li>

<li> <b>Dynamic-load libraries (*.so):</b> Dynamic-load libraries in C++ are also known as shared libraries. They are collections of object files that are loaded by a program at runtime. Unlike static libraries, the code in a dynamic-load library is not compiled into the executable file. Instead, the executable file contains references to the functions and data in the library, and the library is loaded by the operating system when the program is executed</li>
</ul>
</div>

> **_NOTE:_** The main differences between .so and .dylib on macOS are:
> - File extension: .so is the shared object file extension used on Unix-based systems, while .dylib is the dynamic library extension used on macOS.
> - Object file format: The Mach-O object file format used by macOS for executables and libraries distinguishes between shared libraries and dynamically loaded modules.

> Both .so and .dylib are interchangeable as dynamic library files and either have a type as DYLIB or BUNDLE. However, it is recommended to use .dylib on macOS since it is the native dynamic library extension

---
###  Q1. What is ```#pragma once```?
```#pragma once``` is a preprocessor directive in C++ that ensures a header file is included only once in a single compilation. It serves the same purpose as include guards, but with several advantages, including less code, avoidance of name clashes, and sometimes improvement in compilation speed [1](https://en.wikipedia.org/wiki/Pragma_once)

###  Q2. What is ```#include guards```?
Include guards are a technique used in C++ to avoid compiler errors that occur when a header file is included multiple times in a program. They are also known as macro guards, header guards, or file guards. The technique involves wrapping the entire contents of a header file in preprocessor directives that check whether a particular macro has been defined. If the macro has not been defined, the header file is included, and the macro is defined. If the macro has already been defined, the header file is skipped [2](https://en.wikipedia.org/wiki/Include_guard)

___Example ```#include guards``` with structure below:___ 

grandparent.h
{:.filename}
```c++
#ifndef GRANDPARENT_H
#define GRANDPARENT_H

struct foo {
    int member;
};

#endif /* GRANDPARENT_H */

```
parent.h
{:.filename}
```c++
#include "grandparent.h"
```
child.cpp
{:.filename}
```c++
#include "grandparent.h"
#include "parent.h"
```

Here, the first inclusion of ```grandparent.h``` has the macro **GRANDPARENT_H** defined. When ```child.c``` includes ```grandparent.h``` at the second time (while including ```parent.h```), as the **#ifndef** test returns false, the preprocessor skips down to the **#endif**, thus avoiding the second definition of struct foo. The program compiles correctly.

---

### Source codes of the Helloworld
This code will print on the screen the quote ```Robotics Lab Hello World```

helloworld.cpp
{:.filename}
```c++
#include <iostream>
using namespace std;

int main(int argc, char **argv){
    cout << "Robotics Lab Hello World" <<endl;
    return 0;
}
```

### Source codes of the Helloworld using library
This code will print on the screen the quote ```Hello from library```

libHelloWorld.cpp
{:.filename}
```c++
#include <iostream>
using namespace std;

// Create a function printing the hello message
void printHello(){
    cout << "Hello from library" << endl;
}
```

libHelloWorld.h
{:.filename}
```c++
#ifndef LIBHELLOWORLD_H
#define LIBHELLOWORLD_H
//Declares a function in header fil
void printHello();
#endif
```

usehelloworld.cpp
{:.filename}
```c++
#include "libHelloWorld.h"

// Call printHello() in libHelloWorld.h
int main(int argc, char **argv){
    printHello();
    return 0;
}
```


