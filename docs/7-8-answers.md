# 7.8 Describe the terms and fundamentals associated with object-oriented programming using Python

### Objectives

- [ ] Adapter design pattern
- [ ] The keyword "super"
- [ ] Initialization function of a constructor
- [ ] Bridge design pattern
- [ ] Object
- [ ] Difference between an object when discussing a class
- [ ] Advantages to object-oriented programming
- [ ] Class
- [ ] The keyword "self"
- [ ] Inheritance
- [ ] The getter and setter functions
- [ ] Attributes of a class
- [ ] Factory design pattern
- [ ] Singleton design pattern


### Answers

**Adapter design pattern**
> Primarily when adding new components to an existing system. This pattern creates a bridge between the new and old by translating the new interface to the appropriate method in the existing system.

**The keyword "super"**
> Allows access to methods and attributes of a superclass/parent class from a subclass/child class.

**Initialization function of a constructor**
>  __init__() is the initialization function in python. It is called after the class object has been created.

**Bridge design pattern**
> Separates an objects abstraction from its implementation. Allowing them to vary independantly. The abstraction defines the high-level functionality. Where the implemntation defines the low-level functionality. Effectively you have an interface which defines what methods must be implemented. Then the abstraction is used to control any class inherits from that interface.

**Object**
> A collection of data and methods that represent some real-world entity. They are instances of a class that acts as the definition of the object.

**Difference between an object when discussing a class**
> A class is a blueprint for an object whereas the object is essentially a copy of it in memory. Multiple objects can exist as instances of a class allowing those objects to perform the same actions (methods) but maintain different data (attribute) values.

**Advantages to object-oriented programming**
> This highly depends on who you ask... modularity, encapsulation (hiding implementation details), conceptually it attempts to model a program in a similar way to how humans model the world which can be useful for a given project.

**Class**
> The description or structure of what an object looks like (its attributes and methods).

**The keyword "self"**
> Allows reference to a specific object's attributes or methods as opposed to a static 'class level' version.

**Inheritance**
> The concept that a subclass inherits all of the logic and attributes of its superclass. This way logic need only be written once and then more specific logic is written for the class inheriting from the more generic class.

**The getter and setter functions**
> Functions called when assigning(setter) or retrieving(getter) an attribute. They allow for the programmer to run logic automatically whenever a value is assigned or retrieved. 

**Attributes of a class**
> Class level attributes are shared amongst all object instances of a class. Changing a class attribute in one object will 'change' it for all objects of that class.

**Factory design pattern**
> Provides an interface/factory for creating objects in a superclass but allows different types of objects to be created based on the input provided.

**Singleton design pattern**
> This pattern dictates that a class may have only 1 instance of itself at any time. Particularly useful when conceptually it wouldn't make sense for more than one to exist.
