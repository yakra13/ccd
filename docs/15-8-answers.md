# 15.8 Describe how to identify data structures in static analysis

### Objectives

- N/A


### Answers


**Describe how to identify data structures in static analysis**
> For structures allocated on the heap finding a call to malloc followed by a series of assignments to the address returned by malloc with offsets can be indicative of a data structure. If the offset amounts differ this is indicative of a struct like object in memory. For example, a char followed by a long and then an int. Whereas if the offsets are the same it is more likely to be an array.

> For structures allocated on the stack it can be less obvious that it is a data structure versus a series of variables defined in a function. In this case finding other examples of stack allocation in the same pattern can indicate it is a struct like object as well as how the data is passed to functions or used in context.

> In the case where a struct is padded identifying how the offsets address a chunk of memory compared to how it accesses/uses that memory can be indicative of a data structure. For example, if a memory location has an offset of 2 bytes from the next location but the first memory location is accessed as a single byte this indicates a char followed by a byte of padding. Combined with the approaches above this is an indicator of a data structure.