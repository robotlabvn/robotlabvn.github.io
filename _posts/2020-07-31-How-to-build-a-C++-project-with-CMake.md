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
|   |   ├── **/*.a --> excutable files
│   ├── CMakeList.txt
│   ├── helloworld.cpp
│   ├── libHelloWorld.cpp
│   ├── helloworld.h
│   ├── useHello.cpp
```

To build a C++ project with CMake, you can follow these general steps:

1. **Install CMake**: Install CMake on your computer. You can download the installer from the official website or use package managers like apt-get on Ubuntu[1](https://ncona.com/2019/03/building-a-cpp-project-with-cmake/), [2](https://vnav.mit.edu/labs/lab1/cmake.html).

```
sudo apt-get install cmake
```
2. **Create a CMakeLists.txt file**: Create a CMakeLists.txt file in the root directory of your project.
This file contains the instructions for building your project. It
specifies the minimum version of CMake required, the project name, and
any subdirectories or libraries that need to be included[1](https://ncona.com/2019/03/building-a-cpp-project-with-cmake/)


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
3. **Create a build directory**: Create a separate directory for building your project. This keeps the build files separate from your source code.

4. **Run CMake**: In the build directory, run the command `cmake /path/to/source/code`. This generates the build files based on the instructions in your CMakeLists.txt file[1](https://ncona.com/2019/03/building-a-cpp-project-with-cmake/), [3](https://jdhao.github.io/2020/12/12/build_opencv_project_with_cmake/).

```
cd build
cmake ..
```

5. **Build the project**: Use the appropriate build tool to build your project. This could be
make, ninja, or another tool depending on your system and preferences.
Run the command `make` in the build directory to build the project[1](https://ncona.com/2019/03/building-a-cpp-project-with-cmake/), [3](https://jdhao.github.io/2020/12/12/build_opencv_project_with_cmake/).

```
make
```

6. **Run the program**: Once the project is built, you can run the program by navigating to the appropriate directory and running the executable file[1](https://ncona.com/2019/03/building-a-cpp-project-with-cmake/), [3](https://jdhao.github.io/2020/12/12/build_opencv_project_with_cmake/).

```
cd build
./helloworld
./useHello
```