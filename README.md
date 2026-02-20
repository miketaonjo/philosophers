# Philosophers – Concurrent Programming with Threads & Mutexes in C

Philosophers is a concurrent programming project based on Edsger Dijkstra’s famous Dining Philosophers problem.
The objective is to design a synchronization algorithm using threads and mutexes to prevent race conditions, starvation, and deadlocks under strict timing constraints.
The project focuses on multithreading, shared resource protection, precise timing control, and lifecycle management of concurrent entities

Overview

- Language: C
- Concurrency Model: POSIX threads (pthreads)
- Synchronization: Mutexes
- Problem Type: Resource contention simulation
- Constraints: No philosopher communication
- Synchronization: Shared resource locking
- Time Management: Millisecond-precision timing
- Focus: Deadlock avoidance, starvation prevention, race condition control


## Problem description

We must create an algorithm that keeps the philosophers alive as far as possible. The programs must take several parameters:

<code>number_of_philosophers</code>: the number of philosophers around the table<br>
<code>time_to_die</code>: a number representing the time in milliseconds a philosopher has to live after a meal. If a philosopher hasn’t started eating time_to_die milliseconds after the beginning of his last meal or the beginning of the simulation, he will die.<br>
<code>time_to_eat</code>: a number representing the time in milliseconds a philosopher takes to finish his meal. During that time, the philosopher keeps his two forks in hand.<br>
<code>time_to_sleep</code>: the time in milliseconds that a philosopher spends sleeping.<br>
<code>number_of_times_each_philosopher_must_eat</code>: an optional argument that allows the program to stop if all the philosophers have eaten at least that many times. If this argument is not specified, the simulation carries on unless a philosopher dies.<br>

## Installation
```bash
git clone <repository_url>
cd philosophers/philo
make
```

## Execution
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]
```

## Exemples
```bash
./philo 4 800 200 200
```
