<h1 align="center">
  Common Core 42 - Philosophers
</h1>

<p align="center">
<img src="https://github.com/tmatheusdiniz/42-Philosophers/releases/download/img/philo_img" width="700" hidth="150">
</P>
<p align="center">
    <b><i>This project is part of fourth milestone of the 42 cursus</i></b>
</p>
<h3 align="center">
    <a href="#-about">About</a>
    <span> · </span>
    <a href="#-usage">Usage</a>
    <span> · </span>
    <a href="#-references">References</a>
</h3>

## 📖 About

The goal of Philosophers is to write a multithreading program that simulates the famous Dinning philosophers problem.
The goal is to manage the routine of several philosophers sitting around a table:

Each philosopher eats, sleeps, and thinks in cycles.

Every philosopher isr epresented by a thread, and proper synchronization is required to avoid deadlocks and race conditions.

A monitoring system oversees all threads, ensuring that timing constraints are respected and that philosophers don’t starve.

Each action (eat, sleep, think) is associated with a timestamp, allowing precise tracking of the simulation’s progress.

This project is a practical way to explore:

Thread creation and management

Synchronization mechanisms (mutexes, semaphores, etc.)

Concurrency issues and how to handle them safely

Implementing real-time monitoring in a multithreaded environment

## 🧱 Usage

To pull files ↙️
```sh
git clone https://github.com/tmatheusdiniz/42-Philosophers

cd 42-Philosophers
```
To compile ↙️
```sh
make        # builds minishell

```
Cleanup ↙️
```make
make clean   # remove objects

make fclean  # remove all including binaries

make re      # rebuild from scratch
```
Run ↙️
```sh
./philo
```
## 📚 References

API threads documentation:

https://docs.oracle.com/cd/E26502_01/html/E35303/tlib-1.html?utm_source=chatgpt.com

Playlist from the CodeVault channel that helped me understand how to use threads in practical way:

https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2
