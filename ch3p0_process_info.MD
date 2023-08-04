# Linux Process Information

This file goes through some command line functions to query and analyse processes on the linux operating system. This file was written by Gareth Callanan and is intended for use in the operating systems course. Everything here has been tested on a system running the "Ubuntu 20.04.6 LTS" Operating System. Ubuntu is distribution of the Linux OS.

All these commands are intended to be run from the terminal.

## The Process Tree

In order to view a tree of all processes running on the OS, type "ps -ef –forest" into the command line. There should be two top level processes that all other threads are spawned from
1. kthreadd with PID 2 - all kernel threads/processes originate from kthreadd process
2. init with PID 1 - all user space processes are executed from this thread. NOTE: In the tree format, not all user space processes look like they are children of INIT, however if you look at the parent IDs, you should see that they all eventually trace back to a process ID of 1 (which is the init process).

Now lets try create a process with subprocesses.
1. You need to have the "stress" tool installed. On the ubuntu OS, it can be installed by running "sudo apt-get install stress" on the terminal.
2. From the terminal, run "stress -c 20". This will launch a process with 20 sub-processes that will each keep the CPU busy.
3. Run "ps -ef –forest" from a different terminal and try find the stress process and its sub processes. What are their Process IDs (PIDs)? If you rerun "stress -c 20" do the PIDs change?

## Process Information

Now lets try examine individual processes. This section assumes you have stopped the stress tool from running that you started in the previous section.
1. From the terminal, run "stress -c 20".
2. In a different terminal run "ps -ef –forest" and find the PID of the parent stress process and its children. (The stress tool also displayes the parent PID when you execute the step above)
3. In this terminal navigate to the "proc" directory by running "cd /proc". The proc file system is a pseudo-filesystem that contains all information about processes running on the system.
4. View all the processes in the proc directory by running "ls" in the terminal. This displays all directories in the proc directory. Each process will have its own directory. The PIDs for the stress process and its children should be displayed among the files. Once a process is terminated, the corresponding directory in /proc is deleted.
5. Navigate to one of these process directories using "cd PID" where PID is the number/pid found in step 2 above.
6. View all the files in this PID directory by running "ls" from the terminal. The file "cmdline" should show the command typed into the terminal to launch the process. The file "status" should show process status information.
7. View the cmdline file contents with "cat cmdline". You should expect something similar to "stress -c 20" as output. Exactly what you typed in the command line.
8. View the status file contents with "cat status". The output contains lots of information. THe "State" field shows what state the process is in. IF its the parent stress process we expect the state to be "S (Sleeping)" while if its one of the child threads, we expect it to be "R (running)"

## Clean up

Remeber to stop the "stress -c 20" program from running as it will be using all your CPU cycles (and drain you laptop battery if you are using it).