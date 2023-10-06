---
layout: post
category: blog
title: Advanced tips for Python
snippet: This tutorials will show some advanced tips when using python, which includes,  @property in Python , assert, and try-except in Python, The -> symbol in python,..
tags: [python]
---
# @property in Python 
In Python, the __@property__  decorator is used to define managed attributes, also known as 
properties, in classes. It allows you to access, set, and delete class 
attributes in a controlled manner without directly accessing the 
underlying data. The __@property__  decorator is the most Pythonic way to create properties and is preferred over explicit getter and setter methods.

A decorator is a powerful tool in Python that allows  programmers to modify the behavior of a function or class without  permanently modifying it. Decorators are functions that take another function as an argument and extend its behavior without explicitly modifying it. In Python, functions are first-class objects, which means that they can be used or passed as arguments. Decorators allow us to wrap another function in order to extend the behavior of the wrapped function.

Here's an example of using the __@property__  decorator to create a managed attribute:

example_property.py
{:.filename}
```python
class Circle:
    def __init__(self, radius):
        self.radius = radius

    @property
    def diameter(self):
        return 2 * self.radius

    @diameter.setter
    def diameter(self, value):
        self.radius = value / 2

    @property
    def area(self):
        return 3.14 * self.radius ** 2
```

In this example, the Circle class has a radius attribute, and we want to provide a diameter attribute that is automatically calculated based on the radius value. We also want to provide an area attribute that is calculated based on the radius. We can achieve this using the @property decorator.

The @property decorator before the diameter method allows us to access the diameter attribute as if it were a regular attribute, but the value is calculated on the fly based on the radius value.
    
The __@diameter.setter__ decorator allows us to set the diameter attribute, and when we do so, it automatically updates the radius attribute accordingly.

Similarly, the @property decorator is used for the area attribute, which provides a read-only property for the area of the circle. Here's how we can use the Circle class:

Output
{:.filename}
```python
c = Circle(5)
print(c.radius)  # Output: 5
print(c.diameter)  # Output: 10
c.diameter = 20
print(c.radius)  # Output: 10
print(c.area)  # Output: 314.0
```
---
# assert, and try-except in Python

In Python, the __assert__ statement is used to check if a given condition is true. If the condition is false, it raises an __AssertionError__ exception. The __try-except__ block, on the other hand, is used to catch and handle exceptions that occur during the execution of a program.

Here's an example that demonstrates the use of assert and try-except with the __@property__ decorator in a class representing a Circle:

example_assert_try_except.py
{:.filename}
```python
import math

class Circle:
    def __init__(self, radius):
        self.radius = radius

    @property
    def radius(self):
        return self._radius

    @radius.setter
    def radius(self, value):
        try:
            assert value > 0, "Radius must be a positive number"
            self._radius = value
        except AssertionError as error:
            print("AssertionError:", error)

    @property
    def diameter(self):
        return 2 * self.radius

    @property
    def area(self):
        return math.pi * self.radius ** 2

# Creating a Circle object with a valid radius
circle1 = Circle(5)
print(circle1.radius)   # Output: 5
print(circle1.diameter) # Output: 10
print(circle1.area)     # Output: 78.53981633974483

# Creating a Circle object with an invalid radius
circle2 = Circle(-2)
print(circle2.radius)   # Output: None (due to the assertion error in the setter method)
print(circle2.diameter) # Output: None (due to the assertion error in the setter method)
print(circle2.area)     # Output: None (due to the assertion error in the setter method)
```
In this example, we have a Circle class with a radius property that uses the @property decorator to define a getter and a setter method. The setter method includes an assert statement to check if the provided radius value is greater than 0. If the condition is true, the radius is set to the given value. If the condition is false, an AssertionError is raised with the specified error message. When we create a Circle object with a valid radius (e.g., Circle(5)), the getter and the other properties (diameter and area) work as expected, returning the calculated values. However, when we create a Circle object with an invalid radius (e.g., Circle(-2)), the assert statement in the setter method raises an AssertionError, and the getter and the other properties return None due to the exception being caught in the try-except block.

We can use google pystyle: [https://google.github.io/styleguide/pyguide.html](https://google.github.io/styleguide/pyguide.html)

Make use of built-in exception classes when it makes sense. For example, raise a ValueError to indicate a programming mistake like a violated precondition (such as if you were passed a negative number but required a positive one). Do not use assert statements for validating argument values of a public API. assert is used to ensure internal correctness, not to enforce correct usage nor to indicate that some unexpected event occurred. If an exception is desired in the latter cases, use a raise statement. For example: 

example_assert_try_except.py
{:.filename}
```python
  def connect_to_next_port(self, minimum: int) -> int:
    """Connects to the next available port.

    Args:
      minimum: A port value greater or equal to 1024.

    Returns:
      The new minimum port.

    Raises:
      ConnectionError: If no available port is found.
    """
    if minimum < 1024:
      # Note that this raising of ValueError is not mentioned in the doc
      # string's "Raises:" section because it is not appropriate to
      # guarantee this specific behavioral reaction to API misuse.
      raise ValueError(f'Min. port must be at least 1024, not {minimum}.')
    port = self._find_next_open_port(minimum)
    if port is None:
      raise ConnectionError(
          f'Could not connect to service on port {minimum} or higher.')
    assert port >= minimum, (
        f'Unexpected port {port} when minimum was {minimum}.')
    return port
```

---

# The ``->`` symbol in python
In Python, the ``->`` symbol is used to indicate the return type of a function. It is part of the function definition in Python 3.5 or later. Type annotations are optional in Python, but they can help improve code readability and maintainability by providing additional information about the types of arguments and return values. They can also help catch type-related errors during development.
In the Circle class example, we can use the -> symbol to indicate the return type of the getter methods. Here's an example:

return_type_function.py
{:.filename}
```python
import math

class Circle:
    def __init__(self, radius: float) -> None:
        self.radius = radius

    @property
    def radius(self) -> float:
        return self._radius

    @radius.setter
    def radius(self, value: float) -> None:
        try:
            assert value > 0, "Radius must be a positive number"
            self._radius = value
        except AssertionError as error:
            print("AssertionError:", error)

    @property
    def diameter(self) -> float:
        return 2 * self.radius

    @property
    def area(self) -> float:
        return math.pi * self.radius ** 2

```
In this example, we have added type annotations to the __init__, radius, diameter, and area methods to indicate their return types. The -> symbol is used after the method signature to indicate the return type of the method. For example, def ``__init__(self, radius: float) -> None``: indicates that the __init__ method takes a float argument and returns None. Note that the None return type is used for methods that do not return a value. In this example, the __init__ method and the setter methods (radius.setter) do not return a value, so their return type is None.

---
# The ``__str__`` method
In Python, the ``__str__`` method is used to define a string representation of an object. It is called by the built-in ``str()`` function and the ``print()`` function to convert an object to a string
. The ``__str__`` method should return a human-readable string that describes the object in a way that is easy to understand.

In the Circle class example, we can define the ``__str__`` method to return a string representation of the Circle object. Here's an example:

str_method.py
{:.filename}
```python
import math

class Circle:
    def __init__(self, radius):
        self.radius = radius

    @property
    def radius(self):
        return self._radius

    @radius.setter
    def radius(self, value):
        try:
            assert value > 0, "Radius must be a positive number"
            self._radius = value
        except AssertionError as error:
            print("AssertionError:", error)

    @property
    def diameter(self):
        return 2 * self.radius

    @property
    def area(self):
        return math.pi * self.radius ** 2

    def __str__(self):
        return f"Circle with radius {self.radius}"

# Create a Circle object with a valid radius
circle1 = Circle(5)
print(circle1)  # Output: Circle with radius 5

# Create a Circle object with an invalid radius
circle2 = Circle(-2)
# Output: AssertionError: Radius must be a positive number
print(circle2)  # Output: Circle with radius None
```
In this example, we have defined the ``__str__`` method to return a string that describes the Circle object. When we create a Circle object with a valid radius (e.g., Circle(5)), we can print the object using the print() function, and it will call the ``__str__`` method to convert the object to a string. The output will be "Circle with radius 5". When we create a Circle object with an invalid radius (e.g., Circle(-2)), the assert statement in the setter method raises an AssertionError, and the ``__str__`` method returns "Circle with radius None".


## References
https://www.geeksforgeeks.org/decorators-in-python/

https://realpython.com/primer-on-python-decorators/

https://www.programiz.com/python-programming/property
