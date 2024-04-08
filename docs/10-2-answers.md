# 10.2 Describe the following terms and concepts

### Objectives

- [ ] File systems
- [ ] The boot process


### Answers

**File systems**
> File systems are used by OSs to organize and store data generally on hard drives or 'permanent' storage media. More complex file systems handle things like security and encryption. Common types are FAT, NTFS, ext, and APFS depending on the platform. Most file systems use the concept of folders and file to organize data and use a table to locate data 'on disk'.

**The boot process**
> -BIOS/UEFI Initilization handles initializing various hardware such as the cpu and memory and performs a POST to check for hardware errors
-BIOS passes control to the Boot Loader installed, such as GRUB, which is loaded from storage to memory, at which point an OS can be selected from a menu if multiple are installed. It then loads that OSs kernel into memory.
-The kernel takes over and loads necessary drivers to mount the root file system then initializes any necessary hardware components before finally mounting the root file system.
-Next the init process begins generally using systemd
-Any scripts needed are executed to start system services and daemons.
-Next the user space is initialized launching login manager or shell, at which point a user is able to login