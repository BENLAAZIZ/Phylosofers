#      42 Philosophers   #
The "42 Philosophers" project is a classic exercise in the 42 Network that challenges you to solve the dining philosophers problem using threads and synchronization techniques. This project delves into the complexities of threading, processes, and managing shared memory spaces. Inspired by the famous "philosophers' dinner" thought experiment, the project tasks you with implementing a solution where multiple philosophers must share a limited number of resources (such as forks) without encountering deadlocks or starvation. Through this project, you'll gain a deep understanding of synchronization, resource management, and the intricacies of concurrent programming.

![filo](https://github.com/user-attachments/assets/3ff984fb-8ea9-4248-983c-36f6bced307b)



<img width="1786" alt="Screen Shot 2024-09-01 at 4 29 40 PM" src="https://github.com/user-attachments/assets/ca8a5e99-5c71-4715-bb1e-e6eee17e0830">


## what is a pthread mutex and why we need it in this projet ?!

### `pthread mutex` 

A  ` pthread mutex ` (short for POSIX thread mutex) is a synchronization primitive used in multithreaded programming to protect shared resources from concurrent access. Here’s a breakdown of what it is and why it’s essential for your project:

* `Mutex` stands for “mutual exclusion.” It ensures that only one thread can access a critical section of code at a time.
  
* In C, a pthread mutex is defined using the pthread_mutex_t type. You can lock and unlock a mutex using pthread_mutex_lock and pthread_mutex_unlock functions, respectively1.

### Why do we need it in this project ?

1. `Avoiding Deadlocks`: Proper use of mutexes can help avoid deadlocks by ensuring that threads acquire and release locks in a consistent order.

2. `Synchronizing Threads`: Mutexes help synchronize the execution of threads, ensuring that critical sections of code are executed in a controlled manner.

<img width="1689" alt="Screen Shot 2024-09-01 at 4 36 44 PM" src="https://github.com/user-attachments/assets/883ad216-c574-43fd-b1d6-020a3f782436">
