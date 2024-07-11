# 6.1 Describe the purpose and use of C programming fundamentals

### Objectives

- [ ] Return values (return type and reference)
- [ ] The main( ) function
- [ ] The return statement
- [ ] Header files
- [ ] Keywords (static and extern)
- [ ] Pointers
- [ ] An array
- [ ] C preprocessor
- [ ] Casting
- [ ] Control flow
- [ ] Endianness
- [ ] Multi-byte vs. Unicode character sets
- [ ] Multi-threading
- [ ] Hashing
- [ ] Macro guards
- [ ] Data types
- [ ] Functions and procedures
- [ ] Parameters
- [ ] Scope


### Answers

**Return values (return type and reference)**   
>Values returned from a function. Returned via the return keyword or as a reference.
A reference will modify the variable passed in to a function where as returning will not modify the value and return a new value.

**The main( ) function**    
>This is the standard entry point for execution. Has optional parameters to recieve command line arguments.

**The return statement**    
>Used to return from a function. Can return a single value or nothing.

**Header files**    
>Files with a .h extension. Used for many things but primarily forward declarations, preprocessor defines, and includes.

**Keywords (static and extern)**    
>Static within a function will cause the statically defined variable to keep its value between function calls.
A static function or 'global' variable will only be seen in the file its declared in.
Extern will declare functions or variables as global allowing them to be used in scopes outside of their declaration.

**Pointers**    
>Pointers hold memory addresses as opposed to values. The type of a pointer, int, float, etc; dictates the type of the value at that memory address.

**An array**    
>A series of consecutive memory address with values of the same type. The array variable itself is a pointer to the front of the array and '[]' are used
to index into the array and dereference the value at that memory address offset.

**C preprocessor**  
>Performs tasks prior to actual compilation of the code. Things like includes and defines will be processed first.

**Casting**     
>Since the data at any memory allocation has no meaning without an associated type casting allows you to change how the data is interpreted.

**Control flow**    
>This is the concept of using things like 'if/else' and loops to control how a process will execute based on different conditions.

**Endianness**      
>The order of the bytes to determine the value it represents. Also dictates the order of the bytes when transmitted over a network. 

**Multi-byte vs. Unicode character sets**       
>used to represents written characters. Designed to be backwards compatible. Multi-byte character sets allow use of thousands of different characters
needed to represent various languages where the unicode set only supports the alphabet, numbers, and standard punctuation.

**Multi-threading**         
>This allows you to place functions into separate threads that can be processed near simultaneously. This is often used in a client/server architecture.

**Hashing**     
>A procedure to generate a unique identifier for some input data. Typically used to identify some data (such as malware) or to act as a key as with a dictionary structure.

**Macro guards**    
>These are preprocessor commands used to guard against including the same file multiple times (possibly causing an inclusion loop), and to prevent
redefinition of defines.

**Data types**      
>How the computer should interpret a piece of data. Such as an integer or floating point number or character.

**Functions and procedures**    
>Blocks of code that should typically perform a single action or procedure. Can recieve multiple inputs but typically return a single output.

**Parameters**      
>Values or references that can be passed into a function.

**Scope**       
>Refers to the 'visibility' of a variable or function. Either local or global. Variables and functions in the global scope can be accessed from any other scope
but those in a local scope; such as when declared within an if statement, are only visible within that scope.
