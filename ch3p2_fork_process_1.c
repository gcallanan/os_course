// Program for OS Course. This program forks a process and outputs the process
// and parent process IDs for both of the now two running processes.
//
// @author Gareth Callanan
//
// Tested using Ubuntu 20.04.6 LTS OS.
//
// To build and run the program from the terminal:
//  build with "cc ch3p2_fork_process_1.c -o ch3p2_fork_process_1"
//  run with: "./ch3p2_fork_process_1"
//
// The child process will sleep for 60 seconds and the parent process will wait
// for this before terminating. Run "ps -ef --forest" from a seperate terminal
// while this is happening. This will print a process tree for the system. Try
// find the two proccesses in the tree.

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("Process ID: %ld. Parent ID: %ld\n\n", (long)getpid(),
         (long)getppid());
  pid_t pid;
  printf("Forking Process. We will soon have two processes running\n");
  pid = fork();

  // ---------------- We now have two processes running ---------------
  // Task 2: Both processes output to the same terminal. Try guess which output
  // belongs to each terminal.

  // Task 1: Both processes print this line to the same terminal. Try answer the
  // following questions:
  // 1.1. What values do you expect the original process to output here?
  // 1.2. What values do you expect the new child process to output here for
  //    parent id?
  printf("Post-fork Process ID: %ld. Parent ID: %ld\n", (long)getpid(),
         (long)getppid());

  if (pid < 0) { // Error occured
    fprintf(stderr, "Fork Failed\n");
  } else if (pid == 0) { // This branch is only executed in the child process
    // The child process waits for 60 seconds. Use this time to run
    // "ps -ef --forest" from the terminal to see.
    printf("Child Process sleeping for 60 seconds\n");
    sleep(60);
    printf("Child Process Sleep Complete. ID: %ld. Parent ID: %ld\n",
           (long)getpid(), (long)getppid());
  } else { // pid > 0, This branch only executes in the parent process
    printf("Parent Process waiting until child process terminates\n");
    // Task 3: For an extra challenge, comment the "wait(NULL);" line out,
    // recompile and run the code. What do you expect to happen? Does the child
    // process parent ID change during execution? Why?
    wait(NULL);
    printf("Child Complete\n");
  }

  return 0;
}