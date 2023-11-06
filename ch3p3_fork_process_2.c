// Program for OS Course. This program shows how variables are shared when a
// fork occurs.
//
// @author Gareth Callanan
//
// Tested using Ubuntu 20.04.6 LTS OS
//
// To build and run the program from the terminal:
//  build with "cc ch3p3_fork_process_2.c -o ch3p3_fork_process_2"
//  run with: "./ch3p3_fork_process_2"
//
// The sum variable is modified in different places and by different processes.
// Try guess what the value of sum at each different print statment before
// running the code.

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int sum = 100;

  printf("Process ID: %ld.\n", (long)getpid());
  printf("1. Sum Value: %i\n", sum);
  sum = sum + 10;
  printf("2. Sum Value: %i\n", sum);
  pid_t pid;
  printf("Forking Process\n");
  pid = fork();

  // ---------------- We now have two processes running ---------------

  printf("Post-fork Process ID: %ld. Parent ID: %ld\n", (long)getpid(),
         (long)getppid()); // All processes execute this line

  if (pid < 0) { // Error occured
    fprintf(stderr, "Fork Failed");
  } else if (pid == 0) { // This block only executes in the child process
    sum = sum + 20;
    // Question 1: What do you expect the value of sum to be here?
    // a) 100
    // b) 120
    // c) 130
    // d) 150
    printf("3. Sum Value (in child process): %i\n", sum);
  } else { // pid > 0, This block only executes in the parent process
    sum = sum + 30;
    // Question 2: What do you expect the value of sum to be here?
    // a) 100
    // b) 120
    // c) 130
    // d) 140
    // e) 150
    printf("4. Sum Value (in parent process): %i\n", sum);
  }



  if (pid > 0) { // This block only executes in the parent process
    wait(NULL); // Wait for child thread to finish executing
    printf("Child Complete\n");
    sum = sum + 40;
    // Question 3: What do you expect the value of sum to be here?
    // a) 170
    // b) 180
    // c) 200
    printf("5. Sum Value (in parent process): %i\n", sum);
  }

  return 0;
}