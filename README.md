# Philosophers: Dining Problem Solution

This **Philosophers** project is my eighth project at Codam. It tackles the classic Philosophers dining problem, where each philosopher at a round table has one fork but needs two to eat. To eat a philosopher needs access to it's own fork and the fork of the person next them, however this must not be in use. Tackling this problem introduces the concepts of multithreading and mutex locks.


## Project Highlights

- **Multi-threading**: The project introduces multi-threading, allowing each philosopher to act independently.
- **Mutex Locks**: It teaches the use of mutex locks to protect shared data and prevent race conditions.
- **Concurrency Management**: Understanding how to manage concurrent processes and maintain data integrity.

## The Project

The **Philosophers** project is structured to simulate the dining philosophers problem efficiently:

- **Core Functionality**: Each philosopher is represented by a thread, and mutexes are used to manage access to shared resources (forks).
- **Time Management**: The program tracks the time each philosopher spends eating, thinking, and sleeping to ensure they follow the rules of the problem.
- **Monitoring**: Each philosopher can not communicate with the others, therefor a monitor needs to check if the philisophers are still alive and communicate to the threads if the program has come to an end.

### Challenges

Developing **Philosophers** presented several challenges:

- Implementing proper synchronization to prevent deadlocks and ensure all philosophers can eat.
- Managing thread creation and termination efficiently.
- Proper error managment for failure of creating threads.
- Debugging mutex lock problems.

### How to Run

To run the **Philosophers** program, use the following parameters:
*note: This project was developed for macOS.*

1. `number_of_philosophers`: The number of philosophers and forks.
2. `time_to_die`: The time (in milliseconds) a philosopher can go without eating before dying.
3. `time_to_eat`: The time (in milliseconds) it takes for a philosopher to eat.
4. `time_to_sleep`: The time (in milliseconds) a philosopher spends sleeping.
5. `(OPTIONAL) number_of_times_each_philosopher_must_eat`: The number of times each philosopher must eat before the simulation ends.

```
bash
make
./philosophers 5 800 200 200
```

## Conclusion

The **Philosophers** project enhanced my understanding of multi-threading and concurrency in C. It was a valuable learning experience in managing shared resources and ensuring program stability. Feel free to explore the code and use it as a reference or inspiration for your own projects.
