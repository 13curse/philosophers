## Philosophers 🍝

This project is all about simulating the classic Dining Philosophers problem using threads, mutexes, and (for the bonus) processes and semaphores. 
The challenge is to manage concurrency and synchronization so that philosophers can eat, think, and sleep without starving or causing deadlocks.

## Features

**Concurrent simulation:** Each philosopher is a thread.

**Fork management:** Forks are shared resources, protected by mutexes.

**Precise timing:** Each philosopher must eat, sleep, and think according to strict timing rules.

**Death detection:** The simulation stops immediately if a philosopher dies of starvation.

**No data races:** All shared resources are properly protected.

**Accurate logging:** All state changes (taking forks, eating, sleeping, thinking, dying) are logged with timestamps.

**Argument parsing:** The program takes command-line arguments to configure the simulation.

## Bonus

**Process-based simulation:** Philosophers are separate processes instead of threads.

**Semaphore-based fork management:** Forks are managed using semaphores.

**All forks in the middle:** Bonus mode changes the fork management model.

**No global variables:** All data is managed without global state.

## Getting Started

**Prerequisites**

• C compiler (e.g., gcc or clang)

• Make

**Installation**

Clone the repository:

```git clone <your-repository-url>```
```cd philo```

Build the project:

```make```

# or

```make re```

Run the simulation

```./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]```

• ```number_of_philosophers```: Number of philosophers (and forks).

• ```time_to_die```: Time (ms) before a philosopher dies if they don't start eating.

• ```time_to_eat```: Time (ms) a philosopher spends eating.

• ```time_to_sleep```: Time (ms) a philosopher spends sleeping.

• ```number_of_times_each_philosopher_must_eat (optional)```: If provided, simulation ends when each philosopher has eaten at least this many times.

Example

```./philo 5 800 200 200```

**Usage**

• Philosophers alternate between **eating**, **sleeping**, and **thinking**.

• Each philosopher must pick up **two forks** (mutexes) to eat.

• If a philosopher doesn't eat in time, they **die** and the simulation **stops**.

Logs are printed in the format:

```timestamp_in_ms X has taken a fork```

```timestamp_in_ms X is eating```

```timestamp_in_ms X is sleeping```

```timestamp_in_ms X is thinking```

```timestamp_in_ms X died```

where X is the philosopher number.

## Bonus Features

**Process-based simulation:** Run ```./philo_bonus``` with the same arguments.

**Forks managed by semaphores:** All forks are in the middle and managed by a semaphore.

**Each philosopher is a process:** Improved isolation and synchronization.

## Project Structure
```
philo/
├── Makefile
├── *.h
├── *.c
└── README.md
philo_bonus/
├── Makefile
├── *.h
├── *.c
```

## Authors
@sbehar
