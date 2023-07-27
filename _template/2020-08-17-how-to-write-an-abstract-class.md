---
layout: post
category: blog
title: How to structure and write an abstract class
snippet: quick tutorial on abstract classes using coffee makers as an example
tags: [C++]
---

I had previously written a blog post on how to write a plugin in ROS using pluginlib, and there I created an abstract class for structuring controllers for the robot. While that was a very good use case for ROS plugins, it was too specific for robotics, and I wanted to single out the concepts of abstract classes and make it clear how to write/think about abstract classes. So in this tutorial we will talk about how to think of different types of coffee maker as an abstract class.

- TOC
{:toc .toc}

----------------------

# What is an abstract class?

An **abstract class** is a class where you don't have the implementations of the functions, but you have an idea of what it should do. You know what the inputs should be to the class, and what it should return, but how it handles those inputs and generates the outputs is not necessarily defined by the abstract class itself. To the outside world, the abstract class is kind of like *black box*, you give it some input, its derived classes or implementations all handle the inputs in some way, and then provides you with the output that you expect.

A class that implements an abstract class is called a **derived class**. The abstract class it derives from is called the **parent class** or **base class**.

An abstract class will have **virtual functions**. Virtual functions are  functions in a class that you expect to be re-defined and implemented in the derived classes. Therefore, you *can* provide an implementation to a virtual function in an abstract class, then expect the derived class to re-define it later on if need be. If not, the base class implementation is used.

```c++
virtual bool virtualFunction()
{
  //implementation (which can be overwritten by derived classes) here
}
```

**Pure virtual functions** are functions that are NOT given an implementation in the base class, so they must be implemented by the derived class. It is indicated by an `= 0` at the end of your function declaration in the function declaration.

```c++
virtual bool pureVirtualFunction() = 0;
```

# How do I write such a class?

It is very simple. We shall demonstrate with a really inane example with different types of coffee makers! We've all seen enough tutorials with shapes...

<div class="warning">
Disclaimer: This tutorial's sole purpose is to show <b>how to think about structuring your code using abstract classes and derived classes</b>. Therefore, unlike other tutorials that use shape as an example, the code in this tutorial <b>won't run</b>. Consider this tutorial a fun exercise for practicing how to compartmentalize and design code using abstract classes.
</div>

Think of it like this: a "coffee maker" adds water to coffee beans and produces coffee. How it handles the coffee beans, water, and how the process of adding water to coffee is different depending on the method.
{% include image.html url="/assets/2020-08-17-how-to-write-an-abstract-class/coffee_makers.png"
  description="Here's an interesting graphic of different coffee making methods"
  width="80%"
%}

### Writing the abstract base class

The base class will just be called `CoffeeMaker`. All types of the coffee maker will have attributes and functions described in this class. This is where we try to describe the general function and attributes of all of the children classes that will derive from this.

For example, for coffee makers, it usually suffices to include two functions:
- `prepareSetup()`
- `makeCoffee()`

The input is usually:
- coffee beans, which we will assume is of some type `beans_t` (obviously, this doesn't exist, but we'll assume this is a real type definition and is defined somewhere)
- water, which is of type `water_t`

and finally, the output is going to be:
- coffee, which is of type `coffee_t`.

Altogether now, our class definition should look something like:

coffee_makers/include/CoffeeMaker.h
{:.filename}
```c++
#pragma once

namespace cafe {

class CoffeeMaker {
public:
  CoffeeMaker() {};
  virtual ~CoffeeMaker() {};            // Notice how the destructor is declared virtual

  virtual bool prepareSetup() = 0;

  virtual coffee_t makeCoffee(beans_t& beans, water_t& water)
  {
    groundbeans_t ground = grindBeans(beans, 18);
    coffee_t coffee = pourWaterOverBeans(ground_beans, water);
  };

protected:
  groundbeans_t ground = grindBeans(beans_t& beans, double fineness);
  coffee_t coffee = pourWaterOverBeans(groundbeans_t& ground, water_t& water);
};

} //namespace cafe
```

Let's discuss a few things:
- Notice that the destructor for the `CoffeeMaker` class is declared `virtual`.
- Here, `prepareSetup()` is a _pure virtual_ function, since every coffee making setup is different and requires a different set of procedures.
- However, `makeCoffee()` is a _virtual_ function. It has a basic implementation inside it, which is to literally just grind beans and add water to beans.
- We've added two _protected_ functions in the abstract class, which are not defined in the header (but should be defined in a `.cpp` file). These are `grindBeans()` and `pourWaterOverBeans()`.

By the looks of it so far, the base class is looking like some sort of stale cold brew, since we haven't specified any properties. Let's mae some derived classes to implement some specifics.



### Writing the derived class

First up, the classic pour-over. A basic pour-over goes something like this:
1. Put pour-over dripper over a cup/carafe, either directly or on a stand
2. Put filter inside dripper
3. Heat water to some specified temperature
4. Grind coffee beans to a medium-fine grind
5. Put ground coffee into filter
4. Pour hot water slowly over coffee beans

Here's a relaxing tutorial from the guys at Hario!

<div align="center">
<iframe width="640" height="360" src="http://www.youtube.com/embed/OFLaCs99lWY" frameborder="0" allowfullscreen></iframe>
</div>

coffee_makers/include/coffee_makers/PourOver.h
{:.filename}
```c++
#pragma once

#include <coffee_makers/CoffeeMaker.h>

namespace cafe {

class PourOver : public CoffeeMaker {
public:
  PourOver() {};
  ~PourOver() {};

  bool prepareSetup();
  coffee_t makeCoffee(beans_t& beans, water_t& water);

private:
  // Here, you can declare things like.... filter, pour over cup, etc.
};

} //namespace cafe
```

Notice all the virtual declarations are gone! Now all we have to do is write the implementations of `prepareSetup()` and `makeCoffee()`, in a .cpp file, and include this header:

coffee_makers/src/PourOver.cpp
{:.filename}
```c++
#include <coffee_makers/PourOver.h>

namespace cafe {

bool PourOver::prepareSetup()
{
  // insert setup code here
}

coffee_t PourOver::makeCoffee(beans_t& beans, water_t& water)
{
  // insert how you prefer to make your pourover here
}

} //namespace cafe
```


# What is the difference between private, public, and protected inheritance?

<div class="tip">
The contents of this section is copied from <a href="https://stackoverflow.com/questions/860339/difference-between-private-public-and-protected-inheritance"> this StackOverflow answer</a>, since the top answers are pretty good and straight to the point. I renamed some members so that it is easier to understand, and added some additional commentary for completeness.
</div>




For a base class like:
```c++
class Base {
    public:
        int publicMemberInBase;
    protected:
        int protectedMemberInBase;
    private:
        int privateMemberInBase;
};
```

### In general
- Everything that is aware of `Base` is also aware that `Base` contains `publicMemberInBase`.
- Only the children (and their children) are aware that `Base` contains `protectedMemberInBase`.
- No one but `Base` is aware of `privateMemberInBase`.

By "is aware of", I mean "acknowledge the existence of, and thus be able to access".

### Inheritance
Say, a child `Child` inherits from `Base`. Then if:

- `class Child : public Base`:
  - everything that is aware of `Base` and `Child` is also aware `Child` inherits from `Base`.
  - Therefore, a pointer to `Base` can be pointed to an instance of `Child`.
- `class Child : protected Base`:
  - only `Child` and its children are aware that they inherit from `Base`.
  - Therefore, a pointer to `Base` cannot be pointed to an instance of `Child`.
- `class Child : private Base`:
  - no one other than `Child` is aware of the inheritance.
  - Therefore, a pointer to `Base` cannot be pointed to an instance of `Child`.

### Access inside inherited classes

- `class Child : public Base`:
  - `publicMemberInBase` is public to everyone
  - `protectedMemberInBase` is protected, therefore only accessible by `Child` and children of `Child`
  - `privateMemberInBase` is not accessible from `Child`, or anyone except for `Base`
- `class Child : protected Base`
  - `publicMemberInBase` is protected, therefore only accessible by `Child` and children of `Child`
  - `protectedMemberInBase` is protected, therefore only accessible by `Child` and children of `Child`
  - `privateMemberInBase` is not accessible from `Child`, or anyone except for `Base`
- `class Child : private Base`
  - `publicMemberInBase` is private, therefore can only be accessed by `Child`
  - `protectedMemberInBase` is private, therefore can only be accessed by `Child`
  - `privateMemberInBase` is not accessible from `Child`, or anyone except for `Base`
