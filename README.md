# Project name : philosophers

For this project, the assignment is : 

In this project, you will learn the basics of threading a process. You will see how to create threads and you will discover mutexes.

We must create an algorithm that keeps the philosophers alive as far as possible. The programs must take several parameters:

<code>number_of_philosophers</code>: the number of philosophers around the table<br>
<code>time_to_die</code>: a number representing the time in milliseconds a philosopher has to live after a meal. If a philosopher hasn’t started eating time_to_die milliseconds after the beginning of his last meal or the beginning of the simulation, he will die.<br>
<code>time_to_eat</code>: a number representing the time in milliseconds a philosopher takes to finish his meal. During that time, the philosopher keeps his two forks in hand.<br>
<code>time_to_sleep</code>: the time in milliseconds that a philosopher spends sleeping.<br>
<code>number_of_times_each_philosopher_must_eat</code>: an optional argument that allows the program to stop if all the philosophers have eaten at least that many times. If this argument is not specified, the simulation carries on unless a philosopher dies.<br>

## Usage

In order to compile :
<code>make</code>

Execution :
<code>./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philo_must_eat]</code>

Exemple = 
<code>./philo 4 800 200 200 3</code>
