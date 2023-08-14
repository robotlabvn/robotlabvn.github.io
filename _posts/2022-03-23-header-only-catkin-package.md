---
layout: post
category: blog
title: Header-only catkin package
snippet: How to setup and use a header-only catkin package
tags: [C++, robotics]
---

In the header only package:

header_only_package/CMakeLists.txt
{:.filename}
```
cmake_minimum_required(VERSION 3.1)

project(header_only_package)

set(CMAKE_CXX_STANDARD 17)

find_package(catkin REQUIRED)
catkin_package(
  INCLUDE_DIRS include
)

include_directories(include ${catkin_INCLUDE_DIRS})
add_definitions(${catkin_DEFINITIONS})

install(DIRECTORY include ${PROJECT_NAME}/
DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
FILES_MATCHING PATTERN "*.h"
)

```

header_only_package/package.xml
{:.filename}
``` xml
<package>
  <name>header_only_package</name>
  <version>0.0.0</version>
  <description>The header_only_package package</description>
  <author email="email@gmail.com">Name</author>
  <maintainer email="email@gmail.com">Name</maintainer>
  <license>BSD-3</license>

  <buildtool_depend>catkin</buildtool_depend>
</package>

```


In the package that uses it:

using_header_only_package/CMakeLists.txt
{:.filename}
```
...
find_package(catkin REQUIRED COMPONENTS
      ...
      header_only_package
)
...
```

You do not have to include `header_only_package` in the `using_header_only_package/package.xml` manifest.
