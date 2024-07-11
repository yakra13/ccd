# 18.3 Demonstrate knowledge of alternative C libraries to glibc

### Objectives

- N/A


### Answers

**Demonstrate knowledge of alternative C libraries to glibc**
> There are several alternatives to glibc depending on the needs of the project.

***musl***
    > lightweight, fast, and simple standard library for Linux-based systems. It is designed to be more efficient and easier to understand than glibc  
***uClibc***
    > smaller C standard library intended for embedded systems and small-footprint Linux systems  
***Newlib***
    > Newlib is a C library designed for use on embedded systems; developed by Red Hat  
***Bionic***
    > C standard library developed for the Android operating system  
***dietlibc***
    > small C library designed to be efficient and minimize the binary size  

**Example Use musl**

Working with musl is generally very similar to glibc.

>sudo apt update  
>sudo apt install musl musl-tools

```
#include <stdio.h>  
int main()
{  
    printf("Hello, world.\n");  
    return 0;  
}
```

>musl-gcc -o hello hello.c  

