# 15.9 Demonstrate the ability to reverse engineer a binary and identify key facts about it

>RE performed in Ghidra/cli commands

**strings**
>/lib64/ld-linux-x86-64.so.2  
libc.so.6  
__printf_chk  
__cxa_finalize  
__libc_start_main  
GLIBC_2.3.4  
GLIBC_2.2.5  
_ITM_deregisterTMCloneTable  
__gmon_start__  
_ITM_registerTMCloneTable  
u+UH  
[]A\A]A^A_  
Struct contents:  
0x%x  
:*3$"  
GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0  
.shstrtab  
.interp  
.note.gnu.property  
.note.gnu.build-id  
.note.ABI-tag  
.gnu.hash  
.dynsym  
.dynstr  
.gnu.version  
.gnu.version_r  
.rela.dyn  
.rela.plt  
.init  
.plt.got  
.plt.sec  
.text  
.fini  
.rodata  
.eh_frame_hdr  
.eh_frame  
.init_array  
.fini_array  
.dynamic  
.data  
.bss  
.comment  

**Strings of interest**
>/lib64/ld-linux-x86-64.so.2   (dynamic linker)  
libc.so.6  
GLIBC_2.3.4  
GLIBC_2.2.5          (version of glibc)  
Struct contents:     (possible output)  
0x%x                (format specifier for printf)  
GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0  (compiler and os used)  

**main**
```
undefined  [16] FUN_00101060(void)

{
  undefined auVar1 [16];
  ulong in_RAX;
  
  __printf_chk(1,"Struct contents:\n%c\n0x%x\n%c\n",0x2d,0xabcd,0x41);
  auVar1._8_8_ = 0;
  auVar1._0_8_ = in_RAX;
  return auVar1 << 0x40;
}
```
>From ghidra we find a call to printf in what is what is the main() function.  
undefined auVar1 [16];  (this is the struct) we see that it was compiled down to an array of 16 bytes. The compiler optimized away the assignments to the struct and just put constants into the printf call.  

>In this version using -Os to optimize the binary the function get_char() is completely removed. However, without -Os we keep the get_char() function and see that instead of performing a modulo it '&s' num with 0xFF as this is a much faster process than modulo.   

>Also worth noting that because this was compiled on linux with gcc it is an ELF file and without optimizations it keeps debug information such as function names. This is important to know because this data greatly assists with reverse engineering efforts.