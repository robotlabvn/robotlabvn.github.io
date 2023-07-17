---
layout: post
category: blog
title: Building multiple ROS nodes in one package
snippet: How to setup and export multiple libraries and executable from one package
tags: [C++, robotics]
---

Sometimes it's convenient to build multiple nodes into a single package, if multiple nodes share libraries. In this post we'll discuss some use cases for including multiple packages in the `CMakeLists.txt` file.

### Build two libraries without executables
Here's an example where we build a library called `alpha` and a separate library called `beta`, which uses the library `alpha`.

CMakeLists.txt
{:.filename}
```
# alpha
add_library(alpha
      src/Alpha.cpp
)

target_link_libraries(alpha
      ${catkin_LIBRARIES}
)

# beta
add_library(beta
      src/Beta.cpp
)

target_link_libraries(beta
      alpha
      ${catkin_LIBRARIES}
)
```

### Build a third library with an executable
This example builds a library `omega` which has an executable associated with it, and also depends on `alpha`.

CMakeLists.txt
{:.filename}
```
# omega
add_library(omega
      src/Omega.cpp
)

add_executable(omega_node_executable
      src/omega_main.cpp
      src/Omega.cpp
)

target_link_libraries(omega_node_executable
			alpha
      ${catkin_LIBRARIES}
)
```

So far, this will build `alpha`, `beta`, and `omega` into the project namespace `${PROJECT_NAME}`. Therefore, if you go into `.../devel/lib/${PROJECT_NAME}`, you should see them there. If you wish to build, say `alpha`, directly under the `${PROJECT_NAME}`, add this:

CMakeLists.txt
{:.filename}
```
set_target_properties(alpha
  PROPERTIES OUTPUT_NAME ${PROJECT_NAME}
)
```
This will build `alpha` directly into `${PROJECT_NAME}`.

### Export libraries to be used by other packages
To export libraries to be used by other packages, first add libraries to the `catkin_package` specification, and then install the targets:

CMakeLists.txt
{:.filename}
```
catkin_package(
      INCLUDE_DIRS include
      LIBRARIES ${PROJECT_NAME} alpha beta
      CATKIN_DEPENDS
      DEPENDS
)
...

install(TARGETS alpha beta
      ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
      LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
      RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
```
