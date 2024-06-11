# 10.4 Describe terms and concepts associated with concurrency

### Objectives

- [ ] thread safe
- [ ] thread id
- [ ] Locking (mutex, semaphore, etc)
- [ ] Threading (thread vs pthread)
- [ ] fork
- [ ] join
- [ ] create
- [ ] exit
- [ ] detach
- [ ] self
- [ ] Race conditions
- [ ] conditional variables
- [ ] Deadlocks
- [ ] atomics
- [ ] Scheduling algorithms, i.e ., round robin, shortest job first, priority scheduling, etc.

### Answers

**thread safe**
> Refers to code or data structures that can be safely used by multiple threads/processes without causing race conditions, deadlocks, or data corruption.

**thread id**
> Used to differentiate threads in a multithreaded process. Generally assigned by the OS's thread scheduler.

**Locking (mutex, semaphore, etc)**
> Locking is a mechanism to control access to shared resources by multiple threads. A mutex locks a resource to a single thread and blocks any other thread from accessing it until it is released. Semaphores allow a specified number of threads access to a resource instead of just one. A spinlock will cause a thread to wait in a loop and repeatedly check until the resource is available.

**Threading (thread vs pthread)**
> Threading is a technique to run concurrent executions within a single process. Threads run within the same memory space and share the same resources. It allows a program to perform multiple task simultaneously. A pthread or POSIX thread is a specific type of thread associated with unix-like systems.

**fork**
> A fork creates a new process by duplicating an existing process. The newly created process or child process runs in its own memory space.

**join**
> A join causes a thread to wait until another thread/process is complete.

**create**
> Creates a new thread.

**exit**
> Terminates a thread, releasing any resources it may have held.

**detach**
> Detaches a thread/process from its parent thread/process allowing it to continue to execute even if its parent is terminated.

**self**
> Returns the thread ID of the calling thread.

**Race conditions**
> A situation where the result of two threads/processes operating on a shared resource depends on the relative order of those threads/processes.

**conditional variables**
> Mechanism to allow threads to suspend execution until some condition is true. Must be associated with a mutex to avoid race conditions.

**Deadlocks**
> Occurs when two or more processes/threads are unable to continue execution because each is waiting for the other to release a resource.

**atomics**
> Operations guaranteed to be executed as a single indivisible unit of operation. Ensures shared data is accessed and modified safely by multiple threads without race conditions.

**Scheduling algorithms, i.e ., round robin, shortest job first, priority scheduling, etc.**
> Used to manage allocation of resources to processes/threads. Round robin assigns each process a fixed amount of time in a circular queue. Shortest job first selects the process with the smallest execution time. Priority scheduling assigns priorities to a process and selects the highest priority. First-come first-served executes processes in the order received.
