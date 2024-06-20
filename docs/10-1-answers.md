# 10.1 Describe terms and concepts associated with Operating System (OS) virtualization

### Objectives

- [ ] Processes
- [ ] CPU scheduling
- [ ] Paging tables
- [ ] Caching
- [ ] Kernel and user-mode memory

### Answers

**Processes**
> Processes are instances of an executing program. Each process is an an entity defined by the kernel and allocated resources to run a program. Each process as an associated PID used to uniquely identify it.

**CPU scheduling**
> Performed by the operating system to manage allocation of CPU time to various processes. Different scheduling algorithms can be used including: First-Come, First-Serve, Shortest Job Next, Priority Scheduling, etc. The needs of the OS will determine the best approach to scheduling but the ultimate goal is maximizing CPU utilization, fair resource allocation, and minimizing the response time for tasks.

**Paging tables**
> Data structure used in virtual memory systems to manage the mapping between virtual addresses used by a process and the physical addresses in memory. Allows a process to use more memory than is physically available by using the hard disk as an extension.

**Caching**
> Reduces the latency of memory accesses by using memory caches to store relevant or highly used data that can then be quickly accessed.

**Kernel and user-mode memory**
> Distinct memory spaces in an OS that serve different purposes and provide privilege and access control. Kernel memory is protected from direct access by user-mode processes to maintain security. The kernel runs in kernel memory and as such has unrestricted access to hardware and system resources. User-mode memory is at a lower privilege and requests are made to the kernel to perform operations for it.
