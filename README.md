# Philosophers

# Short descrition

Philosophers is the project that will make you find out about thread and mutexes, and how you can syncronize operations that occur at the same time on the operation system.

Is a classic exercise in concurrent programming, designed to teach students about threads, mutexes, and the principles of synchronization in a system where multiple operations occur simultaneously.

It is based on the famous Dining Philosophers Problem, originally formulated by Edsger Dijkstra, which explores the challenges of resource sharing and deadlocks in concurrent processes.

# Key Concepts in the Philosophers Project:
1 - The Problem:

Imagine a group of philosophers seated around a table. Between each pair of philosophers, there is a fork. The philosophers alternate between thre activities: thinking, eating and sleeping.
In order to eat, a philosopher must pick up the two forks adjacent to them (one on their left and one on their right).
The challenge lies in coordinating the philosophers such that no two neighboring philosophers are holding the same fork at the same time, without leading to deadlock (where no one can eat because each philosopher is holding one fork and waiting for the other).

2 - Concurrency and Threads:

A thread of execution is a logical sequence of instructions within a process that is automatically managed by the operating system kernel. A regular sequential program has a single thread, but modern operating systems allow us to create multiple threads in our programs, all of which run in parallel.

Each of a process's threads has its own context: its own ID, its own stack, its own instruction pointer, its own processor register. But because all threads are part of the same process, they share the same virtual memory address space: the same code, the same heap, the same shared libraries, and the same open file descriptors.

Each philosopher is represented by a thread, which allows multiple philosophers to think, eat and sleep concurrently.
Threads run independently, and you need to ensure that operations (like picking up and putting down forks) are synchronized to avoid race conditions (where multiple threads access shared resources at the same time).

3 - Mutexes:

Mutexes (short for mutual exclusion locks) are used to manage access to the shared resources (forks in this case). They ensure that only one philosopher can hold a fork at any given time.
By locking the fork when a philosopher picks it up and unlocking it when they put it down, mutexes prevent other philosophers from picking up the same fork simultaneously.
Deadlocks and Starvation:

The main challenges in the project are race conditions (where two or more access shared resources at same time) and deadlocks (where all threads are waiting indefinitely for a resource) this problem is the beggining of another problem, the starvation (where some philosophers never get a chance to eat because others monopolize the forks).
The project teaches techniques to avoid these issues, such as:
Ordering resource acquisition: Philosophers might be required to pick up the forks in a specific order.

Time limits: You will implement timeouts for how long a philosopher can stay whitout eat, and if this time is reached the philo must die.

Synchronization:

Ensuring that threads synchronize properly (for instance, waiting until both forks are available before eating) is a crucial aspect of the project. This prevents inconsistent states where a philosopher is trying to eat without having the necessary forks.

# Lessons Learned:
The Philosophers project helps students understand essential principles of multithreading, resource management, and synchronization. It emphasizes how careful planning is required to ensure that systems with multiple concurrent operations run smoothly and without conflicts. This project is a stepping stone to understanding more complex synchronization mechanisms in real-world operating systems.

