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

4 - Time limits: You will implement timeouts for how long a philosopher can stay whitout eat, and if this time is reached the philo must die.

5 - Synchronization:

Ensuring that threads synchronize properly (for instance, waiting until both forks are available before eating) is a crucial aspect of the project. This prevents inconsistent states where a philosopher is trying to eat without having the necessary forks.

# Lessons Learned:
The Philosophers project helps students understand essential principles of multithreading, resource management, and synchronization. It emphasizes how careful planning is required to ensure that systems with multiple concurrent operations run smoothly and without conflicts. This project is a stepping stone to understanding more complex synchronization mechanisms in real-world operating systems.

# Resources

-> Book: Linux Programming Interface, chapter 30: THREADS: THREAD SYNCHRONIZATION

-> https://youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2&si=fAhbIlfEUVEfEf35

-> https://www.codequoi.com/en/threads-mutexes-and-concurrent-programming-in-c/

-> https://suspectedoceano.notion.site/Philosophers-b1bf3c57eee6420cafa7d0900b3d3216

-> https://youtu.be/VSkvwzqo-Pk?si=FNaMjthVtC0ee4_M

-> https://medium.com/@ridwaneelfilali/philosophers-the-dinning-problem-8ea3c0fc8cc7

-> https://www.man7.org/tlpi/code/online/dist/threads/simple_thread.c.html

-> https://www.personal.kent.edu/~rmuhamma/OpSystems/Myos/threads.htm

# Run Philosophers

1 - full command
```bash
git clone https://github.com/gkomba/Philosophers.git
```

2 - Arguments

*./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]*

Tests
```bash
./philo 1 800 200 200
```
- Philosopher should not eat and should die.
```bash
./philo 5 800 200 200
```
 - No Philosopher should die.
```bash
./philo 5 800 200 200 7
```
 - No Philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
```bash
./philo 4 410 200 200
```
 - No Philosopher should die.
```bash
./philo 4 310 200 100
```
 - One Philosopher should die.
