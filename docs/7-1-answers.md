# 7.1 Describe purpose and use of foundational Python mechanics

### Objectives

- [ ] The return statement
- [ ] Data types
- [ ] A function
- [ ] Parameters
- [ ] Scope
- [ ] Return values (return type and reference)
- [ ] Import files
- [ ] Dictionaries
- [ ] List
- [ ] Tuple
- [ ] Singleton
- [ ] The term mutable
- [ ] The term immutable


### Answers

**The return statement**
> Used to exit a function and optionally return a value/values to the caller.

**Data types**
> Determines how a value is interpretted. The meaning of data in memory is arbitrary until a data type is associated with it. Some examples of types are integers, booleans, and strings.

**A function**
> Functions represent a piece of logic that performs (generally) a single task. Accepting 0 or more inputs and producing 0 or more outputs.

**Parameters**
> Values that are passed to a function/method/class constructor. They can be optional and have default values.

**Scope**
> The 'visibility' of a variable/class/function. Generally local or global, a global scoped variable is accessable from anywhere whereas a locally scoped variable is only accessible with the same local scope.

**Return values (return type and reference)**
> Values returned by a function via the return keyword. Return values have a type and this type can be specified with the -> operator. Immutable and mutable objects are returned by value.

**Import files**
> Used to import functionality/variables/classes from different modules/files into another file.

**Dictionaries**
> Data structure that stores key-value pairs. Keys are unique and immutable and are associated with a value. 
Particulary useful for efficient lookups as a key indexes directly to its value as well as useful for representing other types of data formats such as JSON.

**List**
> Mutable collection of data items. Items in a list can be added and removed from the list, growing and shrinking to the required size. Useful for data set that have an unknown or non-fixed size due to its ability to grow. A list can also be ordered which can be necessary for many applications tho its lookup times are slower.

**Tuple**
> Immutable version of a list. Once defined it cannot be changed. Due to its immutability it can be useful when changing a piece of data would be problematic to a program. Additionally a good use for tuples is to return multiple values from a single function.

**Singleton**
> Design pattern that restricts the instantition of a class to a single object. Useful when having multiple instances of a class wouldn't make sense; such as program settings or a manager class that handles program state.

**The term mutable**
> Means that the data/object can be changed.

**The term immutable**
> Means that the data/object can NOT be changed once created.
