---
layout: post
category: blog
title: Tutorial on ROS Pluginlib
snippet: How to actually write a plugin in ROS
tags: [C++, robotics]
---
- TOC
{:toc .toc}
----------------------

One of the most useful things that you can do when developing a robotics stack is to compartmentalize your code into plugins. This is very useful when you need to write various implementations of a similar thing, and **want to be able to build/include/use only the plugins we are interested in and/or switch between implementations at run-time**. This allows you to be able to develop different implementations in parallel and save you time during compilation depending on the use case.

However I've found that most of the tutorials illustrate only the base cases where the plugins are built inside a single package (and are quite confusing: [example](http://wiki.ros.org/pluginlib/Tutorials/Writing%20and%20Using%20a%20Simple%20Plugin)). However this is eliminating a key feature of plugins -- which is that you are able to develop *independent implementations without having to compile all of the plugins*.

<div class="row">
    <div class="col">
    {% include image.html url="/assets/2020-05-12-ros-pluginlib/all-in-one.png" description="<b>Package configuration 1</b>: The base class of the plugin and the implementations all in one package. This makes it difficult to work on individual plugins without having to compile all of the other plugins and their dependencies." width="100%" %}
    </div>
    <div class="col">
        {% include image.html url="/assets/2020-05-12-ros-pluginlib/plugin-separated.png" description="<b>Package configuration 2</b>: The base class of the plugin in one package, and the plugins all in a separate package. Implementation wise, this is effectively the same as the before, as all of the plugins are all bundled in the same package thus we have to compile all the dependencies of all the plugins, regardless of the plugin being used." width="100%" %}
    </div>
</div>


The more proper usage case is illustrated as follows, where relevant plugins are packaged separately, allowing the possibility of separate compilation. This is the most helpful use case, when you design your code architecture for loading various planners, controllers, etc.  This is a quick tutorial to showcase how to set up this architecture.

{% include image.html url="/assets/2020-05-12-ros-pluginlib/ideal.png" description="<b>Package configuration 3</b>: The ideal use case described in this tutorial. Relevant plugins are packaged separately, allowing the dependencies of each plugin to be compiled only with itself, and allows you to work on one plugin without having to compile dependencies for another." width="50%" %}


<div class="tip">
<b>A note on structure:</b>

This tutorial is built around assuming that you have your base class and implementation class are in different packages, and that you may have more than one plugin packages (i.e., <b>package configuration 3</b>). You may find this structure unnecessary. Here are some suggestions if you want either of the above two scenarios while following this tutorial:

<ul>
<li> <b>Package configuration 1:</b> If you want to have base class and plugin classes in the same package, <b>follow the same steps here, except just put them all in one package (and add to the same <code>CMakeLists.txt</code> and <code>package.xml</code> as appropriate</b>).</li>
<li> <b>Package configuration 2:</b> If you find it cumbersome to have multiple plugin packages, you can just put all of your plugins inside a single plugin package. In that case, <b>ignore all the parts regarding <code>nonlinear_controller</code></b>.</li>
</ul>
</div>

This tutorial requires basic understanding of ROS, writing CMakeLists.txt, and basic proficiency of C++ and virtual abstract classes.

## Scenario
We'll first describe the scenario in the **package configuration 3** figure above.

Suppose that you have implemented a control framework, `ControlFramework`, which loads a chosen controller at runtime and applies the controller. The controller is to be chosen via a parameter at launch. Suppose you have 3 implementations to choose from: `LinearController1`, and `LinearController2`, and `NonlinearController`. All of these derive from a base virtual class that has the same function calls, however, just the algorithm that implements the function calls are different.

Suppose that `NonlinearController` has its own dependencies `noninear_dependency` that takes a long time to build... and on the days you only want to use one of the `LinearController`s, you'd like to just ignore `NonlinearController` altogether, without having to worry about installing/compiling `NonlinearController`'s dependencies.

This scenario also allows multiple people to work on multiple implementations of the same base virtual class, without having to interfere with other people's implementations.


## Code layout

We will have have 4 pieces of code in this:
* A wrapper class, `ControlFramework`, which loads the plugin at runtime depending on a parameter.
* A virtual abstract base class, `Controller`, which will contain virtual abstract functions that `ControlFramework` will call at runtime.
* The plugins `LinearController1`, `LinearController2`, and `NonlinearController`, which will derive from base class `Controller`.

These will be placed into three packages:

* `controller`, which contains the wrapper class `ControlFramework` and the virtual abstract base class `Controller`.
* `linear_controller`, which contains plugins `LinearController1` and `LinearController2`.
* `nonlinear_controller`, which contains the plugin `NonlinearController`.

#### Base class layout

To do this, we create a new virtual base class `Controller.h` in the package `controller` where we will call the plugins from, like so:

```
controller
  ├ config
  ├ include
  │  └ controller
  │     └ controlFramework.h
  │     └ Controller.h
  ├ src
  │  └ ControlFramework.cpp
  ├ CMakeLists.txt
  └ package.xml
```

#### Plugin classes layout

These are pretty standard, but notice the addition of a `plugins.xml`. Their names doesn't really matter, whatever you like as long as you are consistent:
```
linear_controller
  ├ config
  ├ include
  │  └ linear_controller
  │     └ LinearController1.h
  │     └ LinearController2.h
  ├ src
  │  └ LinearController1.cpp
  │  └ LinearController2.cpp
  ├ CMakeLists.txt
  ├ package.xml
  └ linear_controller_plugins.xml
```

```
nonlinear_controller
  ├ config
  ├ include
  │  └ nonlinear_controller
  │     └ NonlinearController.h
  ├ src
  │  └ NonlinearController.cpp
  ├ CMakeLists.txt
  ├ package.xml
  └ nonlinear_controller_plugins.xml
```

## Creating the plugins

### Base class

First, we will write the base class `Controller` and the plugins. Here, think about what you want your plugin to do. For example, we want all of the plugins to take in a current state, current input, and output the new input.

controller/include/controller/Controller.h
{:.filename}
```c++
#pragma once

#include <ros/ros.h>

namespace control {
class Controller {
public:
  Controller() {};
  virtual ~Controller() {};

  virtual bool initialize(const ros::NodeHandle& n,
                          const ros::NodeHandle& n_private) = 0;
  virtual double computeFeedback(double x, double u) = 0;
};
} //namespace control
```
We've included an initialization function, as well as our `computeFeedback` function.

### plugin packages
Now we write the derived classes. A very basic implementation is as follows:

linear_controller/include/linear_controller/LinearController1.h
{:.filename}
```c++
#pragma once

#include <ros/ros.h>
#include <controller/Controller.h>                      // Inheriting the base class
namespace control {
class LinearController1 : public Controller {
public:
  LinearController1() {};                               // Constructor
                                                        // No destructor!
  bool initialize(const ros::NodeHandle& n,               
                  const ros::NodeHandle& n_private);
  double computeFeedback(double x, double u);

private:
  // More stuff...
};
}
```

linear_controller/src/LinearController1.cpp
{:.filename}
```c++
#include <linear_controller/LinearController1.h>
#include <pluginlib/class_list_macros.h>               // Note, you must include this line

namespace control {

bool LinearController1::initialize(const ros::NodeHandle& n,               
                                   const ros::NodeHandle& n_private)
{
  // do stuff here!
  return true;
}

double LinearController1::computeFeedback(double x, double u)
{
  // do stuff here!
  return 0.0;
}
}
PLUGINLIB_EXPORT_CLASS(control::LinearController1, control::Controller)
```

Note that in the cpp file, we added `#include <pluginlib/class_list_macros.h>`. We also need to add the last line to the file:
`PLUGINLIB_EXPORT_CLASS(namespace::PluginClassName, namespace::DerivedClassName)`, which registers classes as plugins.

Now do the same for `LinearController2` and `NonlinearController`!

## Building and exporting the plugins

Okay, now we have to write the CMakeLists.txt, package.xml, and the plugin.xml's for these packages. Because these files are different packages, we're going to compile them as separate libraries and add them to the pluginlib manifest.

### Building the plugins

We first write the CMakeLists.txt for the plugin packages.
For package `linear_controller`, we add both `LinearController1` and `LinearController2` to the library that we compile, which is called `linear_controller`:

linear_controller/CMakeLists.txt
{:.filename}
```
...
include_directories(include
      ${catkin_INCLUDE_DIRS}
)

add_library(linear_controller                         # <-- the library name!
      src/LinearController1.cpp
      src/LinearController2.cpp
)

add_dependencies(linear_controller ${catkin_EXPORTED_TARGETS})
target_link_libraries(linear_controller ${catkin_LIBRARIES} )
install(TARGETS linear_controller
      LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)
```

And similarly for `nonlinear_controller`. Remember, the whole reason that we wanted separate packages for plugins is because **we want to be able to compile only the plugins we are interested in**. Here, nonlinear_controller has the dependency `nonlinear_dependency`. If we're only working with `linear_controller`, we want to not have to compile `nonlinear_controller` and it's dependencies if we wanted to.

nonlinear_controller/CMakeLists.txt
{:.filename}
```
...
find_package(catkin REQUIRED COMPONENTS
      nonlinear_dependency                           # dependencies only to nonlinear
)

catkin_package(
      INCLUDE_DIRS include
      LIBRARIES ${PROJECT_NAME}
      CATKIN_DEPENDS
        nonlinear_dependency                        # dependencies only to nonlinear
      DEPENDS
)
...
include_directories(include
      ${catkin_INCLUDE_DIRS}
)

add_library(nonlinear_controller                    # <-- the library name!
      src/NonlinearController.cpp
)

add_dependencies(nonlinear_controller ${catkin_EXPORTED_TARGETS})
target_link_libraries(nonlinear_controller ${catkin_LIBRARIES} )
install(TARGETS nonlinear_controller
      LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)
```

### Write the Plugin XML file

For each package, we have to write a plugin xml. The plugin xml should declare all of the plugins contained in that package. For `linear_controller`, this should look like:

linear_controller/linear_controller_plugins.xml
{:.filename}
```xml
<library path="lib/liblinear_controller">
  <class type="control::LinearController1" base_class_type="control::Controller">
    <description>LinearController1 for control</description>
  </class>
  <class type="control::LinearController2" base_class_type="control::Controller">
    <description>LinearController2 for control</description>
  </class>
</library>
```

here, we have 2 plugin classes declared inside this library. Note that the library path, `lib/liblibrary_name` should _match_ the library name that you've specified in the `CMakeLists.txt`.

If you've compiled a separate library inside this package (So you have two libraries that you've specified in CMakeLists.txt), you may append to this xml like such:

linear_controller/linear_controller_plugins.xml
{:.filename}
```xml
<library path="lib/liblinear_controller">
  <class type="control::LinearController1" base_class_type="control::Controller">
    <description>LinearController1 for control</description>
  </class>
  <class type="control::LinearController2" base_class_type="control::Controller">
    <description>LinearController2 for control</description>
  </class>
</library>
<!-- plugins in a separate library that you've compiled in CMakeLists.txt -->
<library path="lib/libanother_linear_controller">
  <class type="control::AnotherLinearController" base_class_type="control::Controller">
    <description>AnotherLinearController for control</description>
  </class>
</library>
```

similarly:

nonlinear_controller/nonlinear_controller_plugins.xml
{:.filename}
```xml
<library path="lib/libnonlinear_controller">
  <class type="control::NonlinearController" base_class_type="control::Controller">
    <description>NonlinearController for control</description>
  </class>
</library>
```


### Export the plugins to ROS
Now, with the plugins.xml manifests set, we venture to `package.xml` to make the plugins visible to the ROS toolchain with the export tag

linear_controller/package.xml
{:.filename}
```xml
<package>
  ...
  <export>
    <controller plugin="${prefix}/linear_controller_plugins.xml" />
  </export>
</package>
```
<div class="tip">
<b>Note:</b> The export tag has the following format:
<pre><code>base_class_package_name plugin="${prefix}/{plugins_filename}.xml"
</code></pre>
where <code>base_class_package_name</code> is the package where <b>the base class of the plugin is located</b>! In our case, this will be package <code>controller</code> which contains the <code>Controller.h</code> virtual abstract class that we have derived the plugins from.
</div>
Similarly for `nonlinear_controller`:

nonlinear_controller/package.xml
{:.filename}
```xml
<package>
  ...
  <export>
    <controller plugin="${prefix}/nonlinear_controller_plugins.xml" />
  </export>
</package>
```

### Check build/export
After you've built and exported your code, you can already check if you were successful!
Open a terminal, and use
```
rospack plugins --attrib=plugin controller
```
You should see something like..

```
controller /path/to/linear_controller_plugins.xml
controller /path/to/nonlinear_controller_plugins.xml
```

## Using the plugins

Now comes the fun part! we will use the plugins in `ControlFramework`.

We first add the appropriate headers to `ControlFramework.h`:

controller/include/controller/ControlFramework.h
{:.filename}
```c++
#pragma once

#include <ros/ros.h>
#include <pluginlib/class_loader.h>                  // Allows us to load plugins
#include <controller/Controller.h>                   // The header file for the base class

namespace control {

class ControlFramework {
public:
  ControlFramework();
  ~ControlFramework();

  bool initialize(const ros::NodeHandle& n,
                  const ros::NodeHandle& n_private);
  // More stuff...
private:
  // We'll create a flag whether it is linear or nonlinear:
  enum ControlMethod { LINEAR1, LINEAR2, NONLINEAR };

  // Here, we have to maintain a plugin loader for the entire duration of the program
  std::unique_ptr<pluginlib::ClassLoader<controller::Controller>> controller_plugin_loader_ptr_;
  // And this is the pointer to the controller
  boost::shared_ptr<Controller> controller_;

  // More stuff...
};
} // namespace control

```

and lastly, to use:

controller/src/ControlFramework.cpp
{:.filename}
```c++
#include <controller/ControlFramework.h>                 

namespace control {
bool ControlFramework::initialize(const ros::NodeHandle& n,
                                  const ros::NodeHandle& n_private)
{
  // stuff ...

  // Load the plugin loader: The syntax here is:
  // std::make_unique<pluginlib::ClassLoader<namespace::base_class_name>>
  //                        ("base_class_package_name", "namespace::base_class_name");
  controller_plugin_loader_ptr_ = std::make_unique<pluginlib::ClassLoader<controller::Controller>>
                                                      ("control", "control::Controller");

  // Here we're going to switch which controller depending on the method chosen
  // by a parameter, 'method'.
  if (method == ControlMethod.LINEAR1)
  {
    controller_ = controller_plugin_loader_ptr_->createInstance("control::LinearController1");
  } else if (method == ControlMethod.LINEAR2)
  {
    controller_ = controller_plugin_loader_ptr_->createInstance("control::LinearController2");
  } else if (method == ControlMethod.NONLINEAR)
  {
    controller_ = controller_plugin_loader_ptr_->createInstance("control::NonlinearController");
  }

  // And as we've added an initialization function to allow initialization of
  // specific methods for each specific controller
  controller_->initialize(n, n_private);
}
  // More stuff...
private:
  // Here, we have to maintain a plugin loader for the entire duration of the program
  std::unique_ptr<pluginlib::ClassLoader<controller::Controller>> controller_plugin_loader_ptr_;
  // And this is the pointer to the controller
  boost::shared_ptr<Controller> controller_;

  // More stuff...
};
} // namespace control

```

And voila! You can now use `controller_` as a normal pointer to your controller and use it as normal.


<div class="tip">
You can make the call to implementation even more general by replacing the above if-else statements by using consistent naming and string concatenation in lieu of <code>...createInstance("control::CLASS_NAME_HERE")...</code> ! Feel free to do so if you are able to make sure that your class names are consistent.
</div>
