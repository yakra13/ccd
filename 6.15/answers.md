# 6.15 Describe terms associated with compiling, linking, debugging, and executables

### Objectives

- [ ] Portable Executable (PE)
- [ ] Executable and Linkable Format (ELF)
- [ ] Difference between PE and ELF
- [ ] Difference between a library (shared object / DLL) and a regular executable program
- [ ] Calling convention/Application Binary Interface (ABI)


### Answers

**Portable Executable (PE)**
> Executable format used with Windows. Contains a header consisting of information such as type, size, entry point, etc.
It also contains byte code and any data or resources imbedded in the executable.

**Executable and Linkable Format (ELF)**
> Used by unix-like operating systems for executable programs, shared libraries and object code. Contains a header with information about
the file as well as sections and segments containing code, data and debugging information.

**Difference between PE and ELF**
>PE is primarily windows where ELF is primarily linux. PE files contain an additional DOS header for backwards compatibility.
PE files are little-endian where ELF files can be either endianness depending on the architecture. PE files store debugging info
in separate files whereas ELFs can store it in the file itself.

**Difference between a library (shared object / DLL) and a regular executable program**
>Libraries are collections of functions that can be shared with a running executable. Allowing the executable to not have to include
those functions in itself. Executables are ran to perform some task and its code is not available to other processes to use directly.

**Calling convention/Application Binary Interface (ABI)**
>Defines how functions are called and how parameters are passed between different modules like libraries. It standardizes the way functions interact
at the binary level to enable compatibility with different compilers/languages.
