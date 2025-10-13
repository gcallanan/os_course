// Program for OS Course. This program forks a process. The child process
// replaces itself with the "ls" command using exec. The parent process waits
// for the child to finish and then prints "Done".
//
// @author Gareth Callanan
//
// Tested using Ubuntu 20.04.6 LTS OS.
//
// To build and run the program from the terminal:
//  build with "cc ch3p4_fork_exec.c -o ch3p4_fork_exec"
//  run with: "./ch3p4_for_exec"
//
// Task: Observe how exec replaces the child process image with "ls".
// Try answer the following questions:
// 1. What happens to the child process after exec is called?
// 2. What does the parent process do while the child runs "ls"?

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  printf("Process ID: %ld. Parent ID: %ld\n\n", (long)getpid(),
         (long)getppid());
  pid_t pid;
  printf("Forking Process. Child will run 'ls' using exec\n");
  pid = fork();

  if (pid < 0) { // Error occurred
    fprintf(stderr, "Fork Failed\n");
    return 1;
  } else if (pid == 0) { // Child process
    printf("Child Process: Executing 'ls' using exec\n");
    execlp("ls", "ls", NULL);
    // If exec fails, print error and exit
    perror("execlp failed");
    return 1;
  } else { // Parent process
    printf("Parent Process: Waiting for child to finish\n");
    wait(NULL);
    printf("Child process complete - Program Done\n");
  }

  return 0;
}
