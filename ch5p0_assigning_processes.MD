# Process Scheduling

This file was written by Gareth Callanan and is intended for use in the operating systems course.

In this document we go through some commands for assigning priorities to different processes in the linux system as well as assigning these processes to different cores in a multiprocessor system. All tests were performed on a 12 core system running the "Ubuntu 20.04.6 LTS" OS however a system with 4 cores should also work.

The following 4 programs are required to be installed to run all these tests:
1. numactl - used for assigning processors to specific cores. Install from terminal with `sudo apt-get install numctl`
2. lstopo - used to generate a diagram of your systems topology. Install from terminal with `sudo apt-get install hwloc`. It is not too important if you cannot install this program.
3. htop - a useful way to show CPU utilisation from the command line. Install with `sudo apt-get install htop`. If you do not want to install that you should be able to open a system monitor from the gui and view CPU utilisation.
4. stress - used for starting a number of processes that keep the CPU busy. Install with `sudo apt-get install stress`

This script is designed to demonstrate scheduling concepts from the Linux system perspective. It is good to read section "5.7.1: Example Linux Scheduling" in the global edition of Siberschatz's Operating System Concepts textbook before running these commands to understand what is happening.

This commands in this file make use of the ch5p1_busy_loop.c program. Compile this program with: `cc ch5p1_busy_loop.c -o ch5p1_busy_loop` from the terminal  before running any other commands. Make sure to run the terminal commands from this repository directory as many of the commands will look for the ch5p1_busy_loop binary.

## System Information

In order to view a diagram of your systems CPU topology, run `lstopo` from the command line. The diagram should show a number of CPU cores equal to the number in your processor. Each core can have more than one thread (marked as a PU on the diagram). Linux sees each thread as a seperate processor. So for example, a 6 core CPU with 2 threads per core will look like a 2*6=12 cores to the operating system.

To view the CPU load, run `htop` from the terminal. Htop should constantly update with the CPU utilisation. Keep this terminal open while running the rest of the commands in this file as it will be interesting. If you run the command `stress -c 20`, you should see all your processors reach 100% utilisation in htop.

To view the system context switches type `watch vmstat -s`. The watch command makes the vmstat command get called every 2 seconds so you can see the context switch counter going up.

## Assigning to Cores

The numactl allows you to assign processes to specific cores. Lets test it out. With htop running, launch "stress -c 20" in the terminal. This launches 20 processes that each keep the CPU busy. You should expect to see all your processors reach 100% utilisation. Stop the running of stress and run the command "numactl -C 0,1,2 stress -c 20". "numactl -C 0,1,2 COMMAND" says run the COMMAND but only allow its processes to execute on core 0,1 and 2. You should expect to see far fewer cores busy on htop.

Now lets try run the busy loop in different configurations:
1. Run `time numactl -C 0 ./ch5p1_busy_loop` from the terminal. The "time" command will report the time it takes for the commands that follow to complete execution. How long does the script take to run?
2. Now try run two versions of ch5p1_busy_loop but from two different terminals. Run `time numactl -C 0 ./ch5p1_busy_loop` from one terminal and `time numactl -C 1 ./ch5p1_busy_loop` from a second terminal. Try execute the scripts at exactly the same time. These scripts should execute at the same time on different cores, each taking as long as the execution in point 1 above to complete. Does this occur?
3. Now try scheduling these processes to run on the same core. Run `time numactl -C 0 ./ch5p1_busy_loop` in one terminal and `time numactl -C 0 ./ch5p1_busy_loop` from a second terminal. You should expect the processes to share the same CPU core and take twice as long to execute. Is this the case?

## Process Nice Levels

Linux uses the "completly fair scheduler" for assigning normal process priorities. A process can be assigned a nice level from -20 to +19. Processing time is scheduled proportionally depending on the nice level with lower nice levels receiving more processing time (read more on this in the textbook if you want to know more).

Lets try investigate how the nice level affects program execution time when two processes are assigned to the same CPU core:
1. Run the commands `time numactl -C 0 nice -n 0 ./ch5p1_busy_loop` and `time numactl -C 0 nice -n 0 ./ch5p1_busy_loop` in two seperate terminals at the same time. Both processes run with the same priority, so they should finish at the same time. 
2. Run the commands `time numactl -C 0 nice -n 0 ./ch5p1_busy_loop` and `time numactl -C 0 nice -n 2 ./ch5p1_busy_loop` in two seperate terminals at the same time. The process with the higher nice value should get more CPU time allocated and finish slightly sooner. Does your experiment match with this statement? How long does each process take to finish?
3. Run the commands `time numactl -C 0 nice -n 0 ./ch5p1_busy_loop` and `time numactl -C 0 nice -n 15 ./ch5p1_busy_loop` in two seperate terminals at the same time. The process with the much higher nice value should get much more processing time and finish much sooner. Does your experiment match with this statement? How long does each process take to finish?

## Linux "Real Time" Scheduling

Linux also has soft real time scheduling priorities. These can be set using `chrt PRIORITY` instead of "nice". In this case PRIORITY can be between 0 and 100 with 100 being the highest priority (the inverse of nice from what I can tell). Run similar experiments as in the section above using `time numactl -C 0 sudo chrt PRIORITY ./ch5p1_busy_loop` experimenting with changing the PRIORITY value. Unlike with nice, a process with higher priority should get almost all processing time. Read more about these in your textbook.


