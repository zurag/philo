# philo

# Description
Dining philosophers problem is a problem created by Edsger Wybe Dijkstra in 1965 to explain the deadlock state of an operating system, which is traditionally commonly introduced in lectures on operating systems. 

One or more philosophers sit at a round table. There is a large bowl of spaghetti in the middle of the table. The philosophers alternatively eat, think, or sleep. While they are eating, they are not thinking nor sleeping; while thinking, they are not eating nor sleeping; and, of course, while sleeping, they are not eating nor thinking.
There are also forks on the table. There are as many forks as philosophers.
Because serving and eating spaghetti with only one fork is very inconvenient, a philosopher takes their right and their left forks to eat, one in each hand. When a philosopher has finished eating, they put their forks back on the table and start sleeping.
Once awake, they start thinking again. The simulation stops when a philosopher dies of starvation. Every philosopher needs
to eat and should never starve. Philosophers don’t speak with each other. Philosophers don’t know if another philosopher
is about to die. No need to say that philosophers should avoid dying!

And our mission is to write such an algorithm that avoid deadlock and effectivly synchronize philosopherse's activities
(eating, sleeping, thinking).

You can read the original description of the problem down here: [https://en.wikipedia.org/wiki/Dining_philosophers_problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## Project

-   The "philo" folder uses a mutex for each fork
-   The "philo_bonus" folder uses a semaphore

# Usage

## Installation

> ```
> git clone https://github.com/zurag/philo.git
> && cd philo\
> && cd philo && make\
> && cd ../philo_bonus && make\
> && cd ../
> ```

## Program arguments and start program

```
./philosophers <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

-   **number_of_philosophers**: The number of philosophers and also the number of forks.
-   **time_to_die** (in milliseconds): If a philosopher didn’t start eating time_to_die milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
-   **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
-   **time_to_sleep** (in milliseconds): The time a philosopher will spend sleeping.

-   **number_of_times_each_philosopher_must_eat** (optional argument): If all philosophers have eaten at least number_of_times_each_philosopher_must_eat times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

## Examples
---

The philosopher should not eat and should die!

```
./philo 1 800 200 200
```

---

No one should die!

```
./philo 5 800 200 200
```

---

No one should die and the simulation should stop when all the philosophers has eaten at least 7 times each.

```
./philo 5 800 200 200 7
```

---

No one should die!

```
./philo 4 410 200 200
```

---

A philosophers should die!

```
./philo 4 310 200 200
```
